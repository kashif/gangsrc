/* GANG Software
 * GEOM/imagegl/ScreenDump.C
 * Copyright (C) 2002 Nicholas Schmitt <nick@gang.umass.edu>
 * Wed Sep 18 16:39:46 2002
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include "image/Common.H"
#include "ScreenDump.H"

namespace imagegl {

ScreenDump::
ScreenDump( ::Display *display )
    :
    _transparent(false),
    _display(display)
{
}

ScreenDump::
~ScreenDump()
{
}

void
ScreenDump::
write(
  base::String const &filename,
  uint x, uint y,
  image::Writer &writer )
{
  if ( x == 0 || y == 0 )
  {
    throw io::WriteException( io::WriteException::ERROR, filename );
  }

  image::Image geom;
  geom.xsize = x;
  geom.ysize = y;
  geom.mode = (_transparent ? image::Image::RGBA : image::Image::RGB );

  uint N = 0;
  if ( geom.mode == image::Image::RGB ) { N = 3U; }
  else if ( geom.mode == image::Image::RGBA ) { N = 4U; }
  else { DIE(); }

  geom.buffer = new char unsigned[ N * geom.xsize * geom.ysize ];
  DIE_IF(geom.buffer == (char unsigned *)0);

  try
  {
    export_( geom );
    writer.write( filename, geom );
  }
  catch ( io::WriteException const &e )
  {
    delete [] geom.buffer;
    throw e;
  }

  delete [] geom.buffer;
}

void
ScreenDump::
export_( image::Image &geom )
{
  ::opengl::PixMap *pixmap =
    new ::opengl::PixMap( geom.xsize, geom.ysize, _display );
  pixmap->make_current();

  set_window_size( geom.xsize, geom.ysize );

  base::Color3 const &c = background_color();
  glClearColor( c[0], c[1], c[2], 1.0 );
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  draw();

  // block until all GL execution is complete
  glFinish();

  if ( geom.mode == image::Image::RGBA )
  {
    glReadPixels( 0, 0,
                  geom.xsize, geom.ysize,
                  GL_RGBA, GL_UNSIGNED_BYTE, geom.buffer );

    if (_transparent)
    {
      // transparent background

      // read depth data
      float *depth = new float [geom.xsize*geom.ysize];
      glReadPixels( 0, 0, geom.xsize, geom.ysize,
                    GL_DEPTH_COMPONENT, GL_FLOAT, depth );
      // set background pixels (where depth==1.0) to transparent
      uint i;
      for ( i = 0; i < geom.xsize*geom.ysize; i++)
      {
        if ( depth[i] == 1.0 )
        { geom.buffer[4*i+3] = 0x00; }
        else
        { geom.buffer[4*i+3] = 0xff; }
      }
      delete depth;

    }
    image::reverse(geom);
  }
  else if ( geom.mode == image::Image::RGB )
  {
    glReadPixels( 0, 0,
                  geom.xsize, geom.ysize,
                  GL_RGB, GL_UNSIGNED_BYTE, geom.buffer );
    image::reverse(geom);
#if 0
    // NOTE: alternate using GL_RGBA instead of GL_RGB
    // (GL_RGB seems buggy on SGI)
    unsigned char *buffer = new unsigned char[ 4 * geom.xsize * geom.ysize ];
    DIE_IF(buffer == (char unsigned *)0);

    glReadPixels( 0, 0,
                  geom.xsize, geom.ysize,
                  GL_RGBA, GL_UNSIGNED_BYTE, buffer );

    // copy buffer to buffer -- in REVERSE ORDER
    uint j;
    for ( j = 0; j < geom.ysize; j++ )
    {
      uint j1 = geom.ysize - j - 1;
      uint i;
      for ( i = 0; i < geom.xsize; i++ )
      {
        geom.buffer[3*(j*geom.xsize + i) + 0] =
          buffer[4*(j1*geom.xsize + i) + 0];
        geom.buffer[3*(j*geom.xsize + i) + 1] =
          buffer[4*(j1*geom.xsize + i) + 1];
        geom.buffer[3*(j*geom.xsize + i) + 2] =
          buffer[4*(j1*geom.xsize + i) + 2];
      }
    }
    delete [] buffer;
#endif
  }
  else { DIE(); }

  delete pixmap;

  // restore context
  make_current();
  set_window_size( area_width(), area_height() );
}

} // namespace imagegl

/* GANG Software
 * GEOM/imagegl/ScreenLoad.C
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

#include <GL/gl.h>
#include <GL/glu.h>
#include "ScreenLoad.H"

namespace imagegl {

ScreenLoad::
ScreenLoad()
    :
    _image(),
    _enable(false),
    _on_top(false)
{
}

ScreenLoad::
~ScreenLoad()
{
  clear();
}

void
ScreenLoad::
clear()
{
  if ( _image.buffer != (char unsigned *)0 )
  {
    delete [] _image.buffer;
    _image = image::Image();
  }
  _enable = false;
}

void
ScreenLoad::
read(
  base::String const &filename,
  image::Reader &reader,
  bool on_top )
{
  clear();

  // read file into buffer
  _image.mode = image::Image::RGB;
  reader.read( filename, _image );

  // reverse the geom
  image::reverse(_image);

  if ( _image.buffer == (char unsigned *)0 ||
       _image.xsize == 0U || _image.ysize == 0U )
  {
    throw base::Exception("ScreenLoad::read(): bad geom");
  }
  _enable = true;
  _on_top = on_top;
}

void
ScreenLoad::
draw() const
{
  if ( ! _enable ) { return; }
  if ( _image.buffer == (char unsigned *)0 ||
       _image.xsize == 0U || _image.ysize == 0U )
  {
    throw base::Exception("ScreenLoad::draw(): bad geom");
  }

  // set the matrices
  glMatrixMode( GL_PROJECTION );
  glPushMatrix();

  glLoadIdentity();
  gluOrtho2D( 0.0, GLfloat(area_width()), 0.0, GLfloat(area_height()) );

  glMatrixMode( GL_MODELVIEW );
  glPushMatrix();
  glLoadIdentity();

  // center the geom on the screen
  GLfloat x = 0.5 * (float(area_width()) - float(_image.xsize));
  GLfloat y = 0.5 * (float(area_height()) - float(_image.ysize));
  glRasterPos3f( x, y, 0.0);

  // if position is off the screen, put the geom in the
  // lower left corner
  GLboolean valid;
  glGetBooleanv( GL_CURRENT_RASTER_POSITION_VALID, &valid );
  if (! valid)
  {
    glRasterPos3f( 0.0, 0.0, 0.0);
  }

  if (!_on_top)
  {
    // disable depth testing
    glPushAttrib(GL_DEPTH_BITS);
    glDisable(GL_DEPTH_TEST);
  }

  // draw the geom on screen
  uint mode = 0;
  if ( _image.mode == image::Image::RGB )
  { mode = GL_RGB; }
  else if ( _image.mode == image::Image::RGBA )
  { mode = GL_RGBA; }
  else { DIE(); }

  glDrawPixels( _image.xsize, _image.ysize, mode, GL_UNSIGNED_BYTE,
                _image.buffer );

  if (!_on_top)
  {
    // restore depth testing
    glPopAttrib();
  }
  // restore the matrices
  glMatrixMode( GL_PROJECTION );
  glPopMatrix();
  glMatrixMode( GL_MODELVIEW );
  glPopMatrix();
}

} // namespace imagegl

/* GANG Software
 * GEOM/opengl/PixMap.C
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

#include "base/System.H"
#include "base/Exception.H"
#include "PixMap.H"

namespace opengl {

PixMap::
PixMap( uint width, uint height, Display *display )
    :
    _pixmap((Pixmap)0),
    _glx_pixmap((GLXPixmap)0),
    _context((GLXContext)0)
{
  _display = display;
  if (_display == (Display *)0)
  {
    _display = XOpenDisplay((char *)0);
  }
  DIE_IF( _display == (::Display *)0 );

#if defined(__sgi)
  // NOTE: should do more error checking
  int const attrList[] =
      {
        GLX_RGBA,
        GLX_RED_SIZE,   8,
        GLX_GREEN_SIZE, 8,
        GLX_BLUE_SIZE,  8,
        GLX_DEPTH_SIZE, 1,
        None
      };

  XVisualInfo *visual = glXChooseVisual(_display, 0, (int *)attrList);
#endif

#if !defined(__sgi)
  // man XVisualInfo
  XVisualInfo vinfo_template =
    {
      0,
      0,
      0,
      1,
      0,
      0,
      0,
      0,
      0,
      24
    };

  int nitems_return;

  XVisualInfo *visual = XGetVisualInfo(
    _display, 0, &vinfo_template, &nitems_return );
#endif

  if (visual == (XVisualInfo *)0)
  {
    throw base::Exception("could not choose visual");
  }

//  WARN( "visual 0x%x", visual->visualid );

  // create an X pixmap
  _pixmap = XCreatePixmap( _display, DefaultRootWindow(_display),
                           width, height, visual->depth );

  // create an off-screen GLX pixmap from the X pixmap
  _glx_pixmap = glXCreateGLXPixmap( _display, visual, _pixmap );

  // create a GLX rendering context
  _context = glXCreateContext(_display, visual, 0, False);
}

PixMap::
~PixMap()
{
  // destroy the GLX rendering context
  glXDestroyContext(_display, _context);
  _context = (GLXContext)0;

  // destroy the GLX pixmap
  glXDestroyGLXPixmap(_display, _glx_pixmap);
  _glx_pixmap = (GLXPixmap)0;

  // destroy the X pixmap
  XFreePixmap(_display, _pixmap);
  _pixmap = (Pixmap)0;

}

void
PixMap::
make_current()
{
  // attach the GLX context to the GLX pixmap
  glXMakeCurrent(_display, _glx_pixmap, _context);
}

} // namespace opengl

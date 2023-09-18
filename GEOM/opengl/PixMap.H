/* GANG Software
 * GEOM/opengl/PixMap.H
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

#ifndef opengl_PixMap_INCLUDED
#define opengl_PixMap_INCLUDED

#include <X11/Xlib.h>
#include <GL/glx.h>

namespace opengl {

class PixMap
{

public:
  // constructor
  PixMap( uint width, uint height, Display *display );

  // destructor
  virtual ~PixMap();

  void make_current();

protected:

private:

  Display *_display;

  Pixmap _pixmap;

  GLXPixmap _glx_pixmap;

  GLXContext _context;


  // disabled copy constructor
  PixMap( PixMap const & );
  // disabled assignment operator
  PixMap &operator=( PixMap const & );

};

} // namespace opengl

#endif // opengl_PixMap_INCLUDED

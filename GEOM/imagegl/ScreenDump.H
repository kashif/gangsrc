/* GANG Software
 * GEOM/imagegl/ScreenDump.H
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

#ifndef imagegl_ScreenDump_INCLUDED
#define imagegl_ScreenDump_INCLUDED

#include "base/Color3.H"
#include "io/Ostream.H"
#include "opengl/PixMap.H"
#include "image/Writer.H"

namespace imagegl {

class ScreenDump
{

public:
  // constructor
  ScreenDump( Display *display );

  // destructor
  virtual ~ScreenDump();

  void write(
    base::String const &filename, 
    uint width, uint height,
    image::Writer &writer );

  void export_( image::Image &geom );

  void transparent( bool b )
    { _transparent = b; }

protected:

private:

  virtual void set_window_size(uint x, uint y) = 0;
  virtual void draw() = 0;
  virtual void make_current() = 0;
  virtual uint area_width() const = 0;
  virtual uint area_height() const = 0;
  virtual base::Color3 const &background_color() const = 0;

  bool _transparent;
  ::Display *_display;

  // disabled copy constructor
  ScreenDump( ScreenDump const & );
  // disabled assignment operator
  ScreenDump &operator=( ScreenDump const & );

};

} // namespace imagegl

#endif // imagegl_ScreenDump_INCLUDED

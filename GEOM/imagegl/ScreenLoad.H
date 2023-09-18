/* GANG Software
 * GEOM/imagegl/ScreenLoad.H
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

#ifndef imagegl_ScreenLoad_INCLUDED
#define imagegl_ScreenLoad_INCLUDED

#include "image/Common.H"
#include "image/Reader.H"

namespace imagegl {

class ScreenLoad
{

public:
  // constructor
  ScreenLoad();

  // destructor
  virtual ~ScreenLoad();

  void read( base::String const &filename, image::Reader &reader,
             bool on_top = false );
  void draw() const;

  void clear();
  void enable( bool state = true ) 
    { _enable = state; }

protected:

private:
  virtual uint area_width() const = 0;
  virtual uint area_height() const = 0;

  image::Image _image;

  // if true, draw
  bool _enable;
  // if true, draw geom in front
  bool _on_top;
  
  // disabled copy constructor
  ScreenLoad( ScreenLoad const & );
  // disabled assignment operator
  ScreenLoad &operator=( ScreenLoad const & );

};

} // namespace imagegl

#endif // imagegl_ScreenLoad_INCLUDED

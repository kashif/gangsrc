/* GANG Software
 * WIDGET/widget/cmd/Window.H
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

#ifndef widget_cmd_Window_INCLUDED
#define widget_cmd_Window_INCLUDED

#include "Widget.H"

namespace widget {
namespace cmd {

class Window
  :
    public Widget
{

public:
  // constructor
  Window() {}

  // destructor
  virtual ~Window() {}


  virtual void set_title( char const * ) = 0;
  virtual uint width() const = 0;
  virtual uint height() const = 0;
  virtual uint x_position() const = 0;
  virtual uint y_position() const = 0;
  virtual void resize( uint width, uint height ) = 0;
  virtual void reposition( uint x, uint y ) = 0;
  virtual void raise( bool state = true ) = 0;
  virtual void raise_show( bool state = true ) = 0;
  virtual void toggle_raise_show() = 0;

  // connection functions
  virtual void show( bool state = true )
    { Widget::show(state); }
  virtual bool showing() const
    { return Widget::showing(); }
  virtual void set_sensitive( bool state = true )
    { Widget::set_sensitive(state); }
protected:

private:

  // disabled copy constructor
  Window( Window const & );

  // disabled assignment operator
  Window &operator=( Window const & );

};

} // namespace cmd
} // namespace widget

#endif // widget_cmd_Window_INCLUDED

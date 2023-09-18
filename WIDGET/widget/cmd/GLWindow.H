/* GANG Software
 * WIDGET/widget/cmd/GLWindow.H
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

#ifndef widget_cmd_GLWindow_INCLUDED
#define widget_cmd_GLWindow_INCLUDED

#include "Window.H"

namespace widget {
namespace cmd {

class GLWindow
  :
    virtual public Window
{

public:
  // constructor
  GLWindow() {}

  // destructor
  virtual ~GLWindow() {}

  virtual uint area_width() const = 0;
  virtual uint area_height() const = 0;
  virtual void make_current() = 0;
  virtual void draw_screen() const = 0;
  virtual void enable_draw(bool) = 0;

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
  GLWindow( GLWindow const & );

  // disabled assignment operator
  GLWindow &operator=( GLWindow const & );

};

} // namespace cmd
} // namespace widget

#endif // widget_cmd_GLWindow_INCLUDED

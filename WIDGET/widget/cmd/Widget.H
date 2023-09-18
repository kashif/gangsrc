/* GANG Software
 * WIDGET/widget/cmd/Widget.H
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

#ifndef widget_cmd_Widget_INCLUDED
#define widget_cmd_Widget_INCLUDED

#include "base/System.H"
#include "widget/ui/Widget.H"

namespace widget {
namespace cmd {

class Widget
  :
    virtual public widget::ui::Widget
{

public:
  // constructor
  Widget() {}

  // destructor
  virtual ~Widget() {}

  virtual void show( bool state = true ) {}
  virtual bool showing() const { return true; }
  virtual void set_sensitive( bool state = true ) {}

protected:

private:

  // disabled copy constructor
  Widget( Widget const & );

  // disabled assignment operator
  Widget &operator=( Widget const & );

};

} // namespace cmd
} // namespace widget

#endif // widget_cmd_Widget_INCLUDED

/* GANG Software
 * WIDGET/widget/cmd/String.H
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

#ifndef widget_cmd_String_INCLUDED
#define widget_cmd_String_INCLUDED

#include "base/String.H"
#include "widget/ui/String.H"
#include "Widget.H"

namespace widget {
namespace cmd {

class String
  :
    virtual public widget::ui::String,
    public Widget
{

public:
  // constructor
  String() {}

  // destructor
  virtual ~String() {}

  virtual void set( char const *a )
    { if (a == (char *)0) { _.erase(); } else { _ = a; } }
  virtual void set_blocked( char const *a )
    { set(a); }
  virtual char const *get() const
    { return _.c_str(); }

  // connection functions
  virtual void show( bool state = true )
    { Widget::show(state); }
  virtual bool showing() const
    { return Widget::showing(); }
  virtual void set_sensitive( bool state = true )
    { Widget::set_sensitive(state); }

protected:

private:

  base::String _;

  // disabled copy constructor
  String( String const & );

  // disabled assignment operator
  String &operator=( String const & );

};

} // namespace cmd
} // namespace widget

#endif // widget_cmd_String_INCLUDED

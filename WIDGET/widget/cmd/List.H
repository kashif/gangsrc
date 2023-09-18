/* GANG Software
 * WIDGET/widget/cmd/List.H
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

#ifndef widget_cmd_List_INCLUDED
#define widget_cmd_List_INCLUDED

#include "base/String.H"
#include "base/vector.H"
#include "widget/ui/List.H"
#include "Choice.H"

namespace widget {
namespace cmd {

class List
  :
    virtual public widget::ui::List,
    public Choice
{

public:
  // constructor
  List() {}

  // destructor
  virtual ~List() {}

  virtual bool selected() const
    { return true; }
  virtual uint item_count() const
    { return _.size(); }
  virtual void append( char const *s )
    { _.push_back(s); }
  virtual void append_blocked( char const *s )
    { append(s); }
  virtual void remove( uint n )
    { _.erase( _.begin() + n ); }

  // connection functions
  virtual void show( bool state = true )
    { Widget::show(state); }
  virtual bool showing() const
    { return Widget::showing(); }
  virtual void set_sensitive( bool state = true )
    { Widget::set_sensitive(state); }
protected:

private:
  base::vector<base::String> _;

  // disabled copy constructor
  List( List const & );

  // disabled assignment operator
  List &operator=( List const & );

};

} // namespace cmd
} // namespace widget

#endif // widget_cmd_List_INCLUDED

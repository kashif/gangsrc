/* GANG Software
 * WIDGET/widget/ui/List.H
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

#ifndef widget_ui_List_INCLUDED
#define widget_ui_List_INCLUDED

#include "Choice.H"

namespace widget {
namespace ui {

class List
  :
    virtual public Choice
{

public:
  // constructor
  List() {}

  // destructor
  virtual ~List() {}

  virtual bool selected() const = 0;
  virtual uint item_count() const = 0;
  virtual void append(char const *) = 0;
  virtual void append_blocked(char const *) = 0;
  virtual void remove( uint ) = 0;

protected:

private:

  // disabled copy constructor
  List( List const & );

  // disabled assignment operator
  List &operator=( List const & );

};


} // namespace ui
} // namespace widget

#endif // widget_ui_List_INCLUDED

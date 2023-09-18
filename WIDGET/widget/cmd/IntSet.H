/* GANG Software
 * WIDGET/widget/cmd/IntSet.H
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

#ifndef widget_cmd_IntSet_INCLUDED
#define widget_cmd_IntSet_INCLUDED

#include "base/Array.H"
#include "widget/ui/IntSet.H"
#include "Widget.H"

namespace widget {
namespace cmd {

class IntSet
  :
    virtual public widget::ui::IntSet,
    public Widget
{

public:
  // constructor
  IntSet( uint n )
    { _.allocate(n); _.set(0); }

  // destructor
  virtual ~IntSet() {}

  virtual void set( int const a[] )
    { _ = a; }
  virtual void set_blocked( int const a[] )
    { set(a); }
  virtual void get( int a[] ) const
    { _.export_(a); }
  virtual void set_sensitive( bool state = true )
    { Widget::set_sensitive(state); }
  virtual void set_sensitive( uint n, bool state ) {}
  virtual void set_bounds( uint n, int lower, int upper ) {}

  // connection functions
  virtual void show( bool state = true )
    { Widget::show(state); }
  virtual bool showing() const
    { return Widget::showing(); }
protected:

private:

  base::Array<int> _;

  // disabled copy constructor
  IntSet( IntSet const & );

  // disabled assignment operator
  IntSet &operator=( IntSet const & );

};

} // namespace cmd
} // namespace widget

#endif // widget_cmd_IntSet_INCLUDED

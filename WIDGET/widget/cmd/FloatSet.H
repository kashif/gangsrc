/* GANG Software
 * WIDGET/widget/cmd/FloatSet.H
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

#ifndef widget_cmd_FloatSet_INCLUDED
#define widget_cmd_FloatSet_INCLUDED

#include "base/Array.H"
#include "widget/ui/FloatSet.H"
#include "Widget.H"

namespace widget {
namespace cmd {

class FloatSet
  :
    virtual public widget::ui::FloatSet,
    public Widget
{

public:
  // constructor
  FloatSet( uint n )
    { _.allocate(n); _.set(0); }

  // destructor
  virtual ~FloatSet() {}

  virtual void set( float const a[] )
    { _ = a; }
  virtual void set_blocked( float const a[] )
    { set(a); }
  virtual void get( float a[] ) const
    { _.export_( a ); }
  virtual void set_sensitive( bool state = true )
    { Widget::set_sensitive(state); }
  virtual void set_sensitive( uint n, bool state ) {}
  virtual void set_bounds( uint n, float lower, float upper ) {}

  // connection functions
  virtual void show( bool state = true )
    { Widget::show(state); }
  virtual bool showing() const
    { return Widget::showing(); }
protected:

private:

  base::Array<float> _;

  // disabled copy constructor
  FloatSet( FloatSet const & );

  // disabled assignment operator
  FloatSet &operator=( FloatSet const & );

};

} // namespace cmd
} // namespace widget

#endif // widget_cmd_FloatSet_INCLUDED

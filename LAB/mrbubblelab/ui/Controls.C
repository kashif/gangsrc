/* GANG Software
 * LAB/mrbubblelab/ui/Controls.C
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

#include "lab/kernel/Evaluator.H"
#include "Controls.H"

namespace mrbubblelab {
namespace ui {

Controls::
Controls()
   :
    ::widget::ui::Dialog()
{
}

Controls::
~Controls()
{
}

void
Controls::
normalshift_cb()
{
  normalshift( normalshift_w()->get() );
  load_surface();
}


void
Controls::
set( parser::KeyParser const &data )
{
  // set widgets from data

  // coefficient
  coefficient_w()->set( data.get( "coefficient" ).c_str() );

  // exponent
  exponent_w()->set( data.get("exponent" ).c_str() );

  // u0
  u0_w()->set( data.get( "u0" ).c_str() );

  // uprime0
  uprime0_w()->set( data.get( "uprime0" ).c_str() );

  // normalshift
  float x;
  lab::kernel::Evaluator::evaluator()->evaluate( x, data.get("normalshift") );
  normalshift_w()->set( x );

  // initial_integrator_count
  initial_integrator_count_w()->set(
    data.get("initial_integrator_count").c_str() );

  // integrator_count
  integrator_count_w()->set(
    data.get("integrator_count").c_str() );
}

void
Controls::
get( parser::KeyParser &data ) const
{
  // set data from widgets

  // coefficient
  data.set("coefficient", coefficient_w()->get() );

  // exponent
  data.set("exponent", exponent_w()->get() );

  // u0
  data.set("u0", u0_w()->get() );

  // uprime0
  data.set("uprime0", uprime0_w()->get() );

  // normalshift
  base::String s;
  s.to_string( normalshift_w()->get() );
  data.set("normalshift", s);

  // initial_integrator_count
  data.set("initial_integrator_count", initial_integrator_count_w()->get());

  // integrator_count
  data.set("integrator_count", integrator_count_w()->get());
}

} // namespace ui
} // namespace mrbubblelab

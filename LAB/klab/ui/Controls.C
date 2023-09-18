/* GANG Software
 * LAB/klab/ui/Controls.C
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

#include "eval/Eval.H"
#include "lab/kernel/Evaluator.H"
#include "klab/kernel/Exception.H"
#include "Controls.H"

namespace klab {
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
reset_lambda_cb()
{
  lambda_w()->set_blocked( 1.0f );
  lambda( 1.0 );
  load_surface();
}

void
Controls::
lambda_cb()
{
  lambda( lambda_w()->get() );
  load_surface();
}

void
Controls::
set( parser::KeyParser const &data )
{
  Real x;
  using ::klab::kernel::Exception;

  // lambda
  try { lab::kernel::Evaluator::evaluator()->evaluate( x, data.get("lambda").c_str() ); }
  catch ( base::Exception const & )
  { throw Exception( Exception::ERR_LAMBDA ); }
  lambda_w()->set_blocked((float)x);

  // potential
  potential_x_w()->set(data.get("potential_x").c_str() );
  potential_y_w()->set(data.get("potential_y").c_str() );

  // initial conditions
  zstart_w()->set( data.get("zstart").c_str() );
  initial_x_w()->set(data.get("initial_x").c_str() );
  initial_y_w()->set(data.get("initial_y").c_str() );

  // integrator_count
  integrator_count_w()->set(
    data.get("integrator_count").c_str() );
  initial_integrator_count_w()->set(
    data.get("initial_integrator_count").c_str() );

  // polylen, basislen
  polynomial_length_w()->set( data.get("polynomial_length").c_str() );
}

void
Controls::
get( parser::KeyParser &data ) const
{
#if 0
  data().set("name", name_w()->get() );
#endif

  base::String s;
  s.to_string( lambda_w()->get() );
  data.set("lambda", s);

  // zstart
  data.set("zstart", zstart_w()->get() );


  data.set("initial_integrator_count",
                   initial_integrator_count_w()->get() );

  data.set("integrator_count",
                   integrator_count_w()->get() );

  data.set("polynomial_length",
                   polynomial_length_w()->get() );

  // cmc potential
  data.set("potential_x", potential_x_w()->get() );
  data.set("potential_y", potential_y_w()->get() );

  // cmc initial condition
  data.set("initial_x", initial_x_w()->get() );
  data.set("initial_y", initial_y_w()->get() );
}


} // namespace ui
} // namespace klab

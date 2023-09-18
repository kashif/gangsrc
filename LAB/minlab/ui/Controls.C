/* GANG Software
 * LAB/minlab/ui/Controls.C
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
#include "minlab/kernel/Exception.H"
#include "Controls.H"

namespace minlab {
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
set( parser::KeyParser const &data )
{
  using minlab::kernel::Exception;

  uint n;
  double x;

  if ( ! data.get("initial_integrator_count").empty() )
  {
    try {
      lab::kernel::Evaluator::evaluator()->evaluate( n, data.get("initial_integrator_count") );
    }
    catch ( base::Exception const & )
    { throw( Exception(Exception::ERR_INITIAL_INTEGRATOR_COUNT) ); }
    initial_integrator_count_w()->set( (int)n );
  }

  if ( ! data.get("integrator_count").empty() )
  {
    try { lab::kernel::Evaluator::evaluator()->evaluate( n, data.get("integrator_count") ); }
    catch ( base::Exception const & )
    { throw( Exception(Exception::ERR_INTEGRATOR_COUNT) ); }
    integrator_count_w()->set( (int)n );
  }

  if ( ! data.get("associate").empty() )
  {
    try { lab::kernel::Evaluator::evaluator()->evaluate( x, data.get("associate") ); }
    catch ( base::Exception const & )
    { throw( Exception(Exception::ERR_ASSOCIATE) ); }
    associate_slider_w()->set_blocked( (float)x );
  }

  if (data.get("mode") == "spinor" )
  {
    notebook_surf_data_w()->set( 0U );
    zstart_spinor_w()->set( data.get("zstart").c_str() );
    spinor1_w()->set( data.get("spinor1").c_str() );
    spinor2_w()->set( data.get("spinor2").c_str() );
    spinor0_init_w()->set( data.get("Xstart1").c_str() );
    spinor1_init_w()->set( data.get("Xstart2").c_str() );
    spinor2_init_w()->set( data.get("Xstart3").c_str() );
  }
  else if (data.get("mode") == "weierstrass" )
  {
    notebook_surf_data_w()->set( 1U );
    zstart_weierstrass_w()->set(
      data.get("zstart").c_str() );
    weierstrass1_w()->set(
      data.get("weierstrass_g").c_str() );
    weierstrass2_w()->set(
      data.get("weierstrass_f").c_str() );
    weierstrass0_init_w()->set(
      data.get("Xstart1").c_str() );
    weierstrass1_init_w()->set(
      data.get("Xstart2").c_str() );
    weierstrass2_init_w()->set(
      data.get("Xstart3").c_str() );
  }
  else
  {
    DIE();
  }
}

void
Controls::
get( parser::KeyParser &data ) const
{
  // ui => data

  // domain type
  int mode = notebook_surf_data_w()->get();

  if ( mode == 0 )
  {
    data.set("mode", "spinor");

    data.set("zstart",
      zstart_spinor_w()->get());

    data.set("spinor1",
      spinor1_w()->get());

    data.set("spinor2",
      spinor2_w()->get());

    data.set("Xstart1",
      spinor0_init_w()->get());

    data.set("Xstart2",
      spinor1_init_w()->get());

    data.set("Xstart3",
      spinor2_init_w()->get());

  }
  else if ( mode == 1 )
  {
    data.set("mode", "weierstrass");

    data.set("zstart",
      zstart_weierstrass_w()->get());

    data.set("weierstrass_g",
      weierstrass1_w()->get());

    data.set("weierstrass_f",
      weierstrass2_w()->get());

    data.set("Xstart1",
      weierstrass0_init_w()->get());

    data.set("Xstart2",
      weierstrass1_init_w()->get());

    data.set("Xstart3",
      weierstrass1_init_w()->get());
  }
  else
  {
    DIE();
  }

  base::String s;
  s.to_string( initial_integrator_count_w()->get());
  data.set("initial_integrator_count", s);

  s.to_string( associate_slider_w()->get() );
  data.set("associate", s);

  s.to_string( integrator_count_w()->get());
  data.set("integrator_count", s);

}

void
Controls::
parameter_reset_cb()
{
  associate_slider_w()->set_blocked( 0.0f );
  set_associate( 0.0f );
  load_surface();
}

void
Controls::
associate_slider_cb()
{
  set_associate( associate_slider_w()->get() );
  load_surface();
}

} // namespace ui
} // namespace minlab

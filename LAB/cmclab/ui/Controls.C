/* GANG Software
 * LAB/cmclab/ui/Controls.C
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

#include "base/System.H"
#include "base/Regex.H"
#include "eval/Eval.H"
#include "lab/kernel/Evaluator.H"
#include "cmclab/kernel/Exception.H"
#include "Controls.H"

namespace cmclab {
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
parameter_notebook_cb()
{
  uint n = parameter_notebook_w()->get();

  if ( n == 0 )
  {
    // S3
    set_lambda_S3();
  }
  else if ( n == 1 )
  {
    // R3
    set_lambda_R3();
  }
  else if ( n == 2 )
  {
    // H3
    set_lambda_H3();
  }
  else
  {
    DIE();
  }
}

// R3

void
Controls::
reset_R3_cb()
{
  lambda_R3_w()->set_blocked( 0.0f );
  set_lambda_R3( 1.0 );

  normalshift_w()->set_blocked( 1.0f );
  set_normalshift( 1.0f );

  load_surface();
}

void
Controls::
set_lambda_R3()
{
  set_lambda_R3( lambda_R3_w()->get() );
  load_surface();
}

void
Controls::
lambda_R3_cb()
{
  set_lambda_R3();
}

void Controls::lambda_button0_cb() { lambda_R3_w()->set( 0.0f ); }
void Controls::lambda_button1_cb() { lambda_R3_w()->set( 0.25f ); }
void Controls::lambda_button2_cb() { lambda_R3_w()->set( 0.5f ); }
void Controls::lambda_button3_cb() { lambda_R3_w()->set( 0.75f ); }

void
Controls::
normalshift_cb()
{
  set_normalshift( normalshift_w()->get() );
  load_surface();
}

void Controls::normalshift_button0_cb() { normalshift_w()->set( 1.0f ); }
void Controls::normalshift_button1_cb() { normalshift_w()->set( 0.0f ); }
void Controls::normalshift_button2_cb() { normalshift_w()->set( -1.0f ); }

void
Controls::
mean_curvature_cb()
{
  set_mean_curvature( mean_curvature_w()->get() );
  load_surface();
}

// S3

void
Controls::
reset_S3_cb()
{
  lambda0_S3_w()->set_blocked( 0.0f );
  lambda1_S3_w()->set_blocked( 0.25f );
  set_lambda_S3( 0.0f, 0.25f );
  load_surface();
}

void
Controls::
set_lambda_S3()
{
  float lambda0 = lambda0_S3_w()->get();
  float lambda1 = lambda1_S3_w()->get();

  set_lambda_S3( lambda0, lambda1 );
  load_surface();
}

void
Controls::
lambda0_S3_cb()
{
  set_lambda_S3();
}

void
Controls::
lambda1_S3_cb()
{
  set_lambda_S3();
}

void Controls::lambda_button00_cb() { lambda0_S3_w()->set( 0.0f ); }
void Controls::lambda_button01_cb() { lambda0_S3_w()->set( 0.25f ); }
void Controls::lambda_button02_cb() { lambda0_S3_w()->set( 0.5f ); }
void Controls::lambda_button03_cb() { lambda0_S3_w()->set( 0.75f ); }

void Controls::lambda_button10_cb() { lambda1_S3_w()->set( 0.0f ); }
void Controls::lambda_button11_cb() { lambda1_S3_w()->set( 0.25f ); }
void Controls::lambda_button12_cb() { lambda1_S3_w()->set( 0.5f ); }
void Controls::lambda_button13_cb() { lambda1_S3_w()->set( 0.75f ); }

// H3

void
Controls::
reset_H3_cb()
{
  lambda0_H3_w()->set_blocked( 0.8f );
  lambda1_H3_w()->set_blocked( 0.0f );
  set_lambda_H3( 0.8f );
  load_surface();
}

void
Controls::
set_lambda_H3()
{
  std::complex<float> x(
    lambda0_H3_w()->get(),
    lambda1_H3_w()->get() );
  set_lambda_H3( x );
  load_surface();
}

void
Controls::
lambda0_H3_cb()
{
  set_lambda_H3();
}

void
Controls::
lambda1_H3_cb()
{
  set_lambda_H3();
}


void
Controls::
inc_lambda_R3(float dx)
{
//  stop_motion();

  uint n = parameter_notebook_w()->get();
  if ( n != 1 ) { return; }

  float x = lambda_R3_w()->get();
  lambda_R3_w()->set(x + dx);
}

void
Controls::
toggle_normalshift()
{
//  stop_motion();

  uint n = parameter_notebook_w()->get();
  if ( n != 1 ) { return; }

  float x = normalshift_w()->get();
  x = ( x == 0.0f ? 1.0f : 0.0f );
  normalshift_w()->set(x);
}

void
Controls::
set( parser::KeyParser const &data )
{
  using cmclab::kernel::Exception;

  Real x;

  // lambda parameter
  base::vector<base::String> v;
  if ( base::match( "^R3[ \n\r\t]+(.+)$", data.get("lambda"), v ) )
  {
    // R^3
    float lambda;
    try { lab::kernel::Evaluator::evaluator()->evaluate( lambda, v[1] ); }
    catch( base::Exception const & )
    { throw Exception( Exception::ERR_LAMBDA ); }
    parameter_notebook_w()->set_blocked(1);
    lambda_R3_w()->set_blocked( lambda );
  }
  else if ( base::match( "^S3[ \n\r\t]+(.+);[ \n\r\t]+(.+);?$",
                         data.get("lambda"), v ) )
  {
    // S^3
    float lambda;
    try { lab::kernel::Evaluator::evaluator()->evaluate( lambda, v[1] ); }
    catch ( base::Exception const & )
    { throw Exception( Exception::ERR_LAMBDA ); }
    lambda0_S3_w()->set_blocked( lambda );

    try { lab::kernel::Evaluator::evaluator()->evaluate( lambda, v[2] ); }
    catch ( base::Exception const & )
    { throw Exception( Exception::ERR_LAMBDA ); }
    parameter_notebook_w()->set_blocked(0);
    lambda1_S3_w()->set_blocked( lambda );
  }
  else if ( base::match( "^H3[ \n\r\t]+(.+)$",
                         data.get("lambda"), v ) )
  {
    // H3
    Complex lambda;
    try { lab::kernel::Evaluator::evaluator()->evaluate( lambda, v[1] ); }
    catch ( base::Exception const & )
    { throw Exception( Exception::ERR_LAMBDA ); }

    parameter_notebook_w()->set_blocked(2);
    lambda0_H3_w()->set_blocked( (float)std::real(lambda) );
    lambda1_H3_w()->set_blocked( (float)std::imag(lambda) );
  }
  else
  {
    throw Exception( Exception::ERR_LAMBDA );
  }


  // mean curvature
  // NOTE: should check if 0
  try { lab::kernel::Evaluator::evaluator()->evaluate( x, data.get("mean_curvature") ); }
  catch ( base::Exception const & )
  { throw Exception( Exception::ERR_MEAN_CURVATURE ); }
  mean_curvature_w()->set_blocked( (float)x );

  // normal shift
  int n;
  try { lab::kernel::Evaluator::evaluator()->evaluate( n, data.get("normalshift") ); }
  catch ( base::Exception const & )
  { throw Exception( Exception::ERR_NORMAL_SHIFT ); }

  // NOTE BUG
  // this should be blocked, because if it is being read from
  // a file, it will try to export the surface before the surface
  // is computed (crash)
  normalshift_w()->set_blocked( n );

  // potential
  potential_w()->set(data.get("potential").c_str() );
  potential_variable_w()->set(
    data.get("potential_variable").c_str() );

  // zstart
  zstart_w()->set( data.get("zstart").c_str() );


  // xstart
  xstart_w()->set(data.get("xstart").c_str() );

  // integrator_count
  integrator_count_w()->set(
    data.get("integrator_count").c_str() );
  initial_integrator_count_w()->set(
    data.get("initial_integrator_count").c_str() );

  // polylen, basislen
  polynomial_length_w()->set(
    data.get("polynomial_length").c_str() );
  basis_length_w()->set( data.get("basis_length").c_str() );

  // iwasawa method
  if ( data.get("iwasawa_method") == "cholesky" )
  {
    iwasawa_method_w()->set( 0U );
  }
  else if ( data.get("iwasawa_method") == "qr" )
  {
    iwasawa_method_w()->set( 1U ); }
  else
  {
    throw( Exception( Exception::ERR_IWASAWA_METHOD ) );
  }

  // one-column
  if ( data.get("one_column") == "false" )
  {
    one_column_w()->set( false );
  }
  else if ( data.get("one_column") == "true" )
  {
    one_column_w()->set( true );
  }
  else
  {
    throw( Exception( Exception::ERR_TWO_COLUMN ) );
  }

  // birkhoff
  if ( data.get("birkhoff") == "false" )
  {
    birkhoff_w()->set( false );
  }
  else if ( data.get("birkhoff") == "true" )
  {
    birkhoff_w()->set( true );
  }
  else
  {
    throw( Exception( Exception::ERR_BIRKHOFF ) );
  }
}

void
Controls::
get( parser::KeyParser &data ) const
{
#if 0
  dataset( "name", name_w()->get() );
#endif

  uint n = parameter_notebook_w()->get();

#if 0
  char const *space[] = {"S3", "R3", "H3"};
  data.set("geometry", space[n] );
#endif


  if (n == 0)
  {
    // S^3
    base::String s( "S3 " );

    // associate
    base::String t;
    t.to_string( lambda0_S3_w()->get() );
    s += t;
    s += "; ";
    t.to_string( lambda1_S3_w()->get() );
    s += t;
    data.set("lambda", s);
  }
  else if (n == 1)
  {
    // R^3

    base::String s( "R3 " );

    // associate
    base::String t;
    t.to_string( lambda_R3_w()->get() );
    s += t;
    data.set("lambda", s);

    // mean curvature
    t.to_string( mean_curvature_w()->get() );
    data.set("mean_curvature", t);

    // normal shift
    t.to_string( normalshift_w()->get() );
    data.set("normalshift", t);
  }
  else if (n == 2)
  {
    // H^3
    base::String s( "H3 " );

    Complex x(
      lambda0_H3_w()->get(),
      lambda1_H3_w()->get() );

    base::String t;
    t.to_string( x );
    s += t;

    data.set("lambda", s );
  }
  else
  {
    DIE();
  }

  // zstart
  data.set("zstart", zstart_w()->get() );


  data.set("initial_integrator_count",
                   initial_integrator_count_w()->get() );

  data.set("integrator_count",
                   integrator_count_w()->get() );

  data.set("polynomial_length",
                   polynomial_length_w()->get() );

  data.set("basis_length",
                   basis_length_w()->get() );

  n = iwasawa_method_w()->get();
  DIE_IF(n != 0 && n != 1 );
  data.set("iwasawa_method", ( n == 0 ? "cholesky" : "qr" ) );

  bool b = one_column_w()->get();
  data.set("one_column", ( b ? "true" : "false" ) );

  b = birkhoff_w()->get();
  data.set("birkhoff", ( b ? "true" : "false" ) );

  // cmc potential
  data.set("potential", potential_w()->get() );

  data.set("potential_variable",
                   potential_variable_w()->get() );

  // cmc initial condition
  data.set("xstart", xstart_w()->get() );
}

} // namespace ui
} // namespace cmclab

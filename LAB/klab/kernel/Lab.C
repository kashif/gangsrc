/* GANG Software
 * LAB/klab/kernel/Lab.C
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

#include <sys/types.h>
#include <time.h>
#include <fstream>
#include "parser/KeyParser.H"
#include "base/Timer.H"
#include "loop/Common.H"
#include "loop/EvalLoop.H"
#include "loop/Birkhoff.H"
#include "Lab.H"

// NOTE -- THIS IS INEFFICIENT BECAUSE IT USES UNTWISTED ALGORITHMS
// TO COMPUTE TWISTED LOOPS

namespace klab {
namespace kernel {

char const *Lab::_about_info =
"Created by Nick Schmitt";

Lab::
Lab()
    :
    lab::kernel::Lab(),
    _data(),
    _potential_x(),
    _potential_y(),
    _zstart(0.0),
    _initial_x(),
    _initial_y(),
    _integrator_count(),
    _initial_integrator_count(),
    _polylen(),
    _lambda(0.0),
    _factorizer( (Birkhoff *)0 ),
    _sym(),
    _multidata(),
    _multiop()
{

  _potential_x.set_variable_name("x");
  _potential_y.set_variable_name("y");
  initialize_data();

  initialize();
}


Lab::
~Lab()
{
  if ( _factorizer != (Birkhoff *)0 ) { delete _factorizer; }
}

void
Lab::
set_state_from_data()
{
  uint tmp_uint;

  // initial condition
  Complex z0;
  try { evaluate( z0, data().get("zstart") ); }
  catch ( base::Exception const & )
  { throw Exception( Exception::ERR_ZSTART ); }

  initial_condition( z0, data().get("initial_x"),
                     data().get("initial_y") );

  // lambda parameter
  Real lambda_;
  try { evaluate( lambda_, data().get("lambda") ); }
  catch ( base::Exception const & )
  { throw Exception( Exception::ERR_LAMBDA ); }
  lambda( lambda_ );

#if 0
  // X_start
  // ??? uses potential's _time_parameter
  _potential.set_time_variable( "" );
  _potential.set_time_parameter( 0.0 );
#endif

  //-----------------------------------
  // potential functions

  _potential_x.set( data().get("potential_x") );
  _potential_y.set( data().get("potential_y") );

  //-----------------------------------
  // KLab parameters

  // integrator_count
  try { evaluate( tmp_uint, data().get("integrator_count") ); }
  catch ( base::Exception const & )
  { throw Exception( Exception::ERR_INTEGRATOR_COUNT ); }
  if( tmp_uint < 1 )
  { throw Exception( Exception::ERR_INTEGRATOR_COUNT_VAL ); }
  integrator_count( tmp_uint );

  // initial_integrator_count
  try { evaluate( tmp_uint, data().get("initial_integrator_count") ); }
  catch ( base::Exception const & )
  { throw Exception( Exception::ERR_INITIAL_INTEGRATOR_COUNT ); }
  if( tmp_uint < 1 )
  {
    throw Exception(
      Exception::ERR_INITIAL_INTEGRATOR_COUNT_VAL );
  }
  initial_integrator_count( tmp_uint );

  // polynomial_length
  try { evaluate( tmp_uint, data().get("polynomial_length") ); }
  catch ( base::Exception const & )
  { throw Exception( Exception::ERR_POLYNOMIAL_LENGTH ); }
  if( tmp_uint < 1 || tmp_uint % 2 != 0 )
  { throw Exception( Exception::ERR_POLYNOMIAL_LENGTH_VAL ); }
  polynomial_length( tmp_uint );
}

void
Lab::
initialize()
{
//  _data->set_defaults();
}

void
Lab::
initialize_data()
{
  _integrator_count = 1;
  _initial_integrator_count = 100;
  _polylen = 20;
  _zstart = 0.0;
  _factorizer = (Birkhoff *)0;
  _potential_x.clear_data();
  _potential_y.clear_data();
}

void
Lab::
initial_condition(
  Complex const &z,
  base::String const &x,
  base::String const &y )
{
  _zstart = z;
  _initial_x = x;
  _initial_y = y;
}

void
Lab::
initial_condition(
  Complex &z,
  base::String &x,
  base::String &y )
{
  z = _zstart;
  x = _initial_x;
  y = _initial_y;
}

void
Lab::
start_all_v(
  uint vertex_count,
  uint edge_count,
  uint thread_count )
{
  // we need a separate copy for each thread of:
  // (1) potential
  // (2) Integrate
  // (3) Birkhoff

  bool const _upper_tri = false;

  // set initial conditions for surface computation

  if ( _polylen < 1 )
  { throw Exception( Exception::ERR_POLYLEN ); }

  if ( _polylen % 2 != 0 )
  { throw Exception( Exception::ERR_POLYLEN_PARITY ); }


  if ( _factorizer != (Birkhoff *)0 )
  {
    delete _factorizer;
  }
  _factorizer = new Birkhoff( polynomial_length(), _upper_tri );

  _multiop.clear();
  _multiop.reserve(thread_count);
  
  // initialize _multiop
  MultiOp O;

  uint i;
  for ( i = 0; i < thread_count; i++ )
  {
    O._potential_x = new EvalLoop(_potential_x);
    O._potential_y = new EvalLoop(_potential_y);
    O._integrator_x = new Integrator( O._potential_x, _polylen);
    O._integrator_y = new Integrator( O._potential_y, _polylen);
    O._factorizer = new Birkhoff( _polylen, _upper_tri );
    _multiop.push_back(O);
  }

  // initialize _multidata
  MultiData M;
  _multidata.fill( M, vertex_count );
  for ( i = 0; i < vertex_count; i++ )
  {
    _multidata[i].gx.allocate(_polylen);
    _multidata[i].gx.identity();
    _multidata[i].gy.allocate(_polylen);
    _multidata[i].gy.identity();
    _multidata[i].potential_x.allocate(_polylen);
    _multidata[i].potential_y.allocate(_polylen);
    _multidata[i].F.allocate(_polylen);
    _multidata[i].F.identity();
  }
}

void
Lab::
end_all_v(
  uint vertex_count,
  uint edge_count,
  uint thread_count )
{
  cleanup();
}

void
Lab::
cleanup()
{
  // clear old version
  base::vector<MultiOp>::iterator i;
  for ( i = _multiop.begin(); i != _multiop.end(); i++ )
  {
    delete (*i)._potential_x;
    delete (*i)._potential_y;
    delete (*i)._integrator_x;
    delete (*i)._integrator_y;
    delete (*i)._factorizer;
  }
  _multiop.clear();
}

void
Lab::
compute_segment(
  Complex &z,
  Complex const &dz,
  Potential &potential_x,
  Potential &potential_y,
  Loop4 &gx,
  Loop4 &gy,
  Loop4 &F,
  uint steps,
  uint thread_id )
{
  /*
    This is the heart of the computation.
    Performs one step of calculation, doing
      (1) integration
      (2) Birkhoff factorization
    (Sym formula computation is computed later)
  */

  {
  // set (x, y) to the real and imaginary parts of z
  Real x = z.real();
  Real y = z.imag();

  // perform x integration one step
  _multiop[thread_id]._integrator_x->
    integrate( x, potential_x, gx, dz.real(), steps );

  // perform y integration one step
  _multiop[thread_id]._integrator_y->
    integrate( y, potential_y, gy, dz.imag(), steps );

  // update z
  z = Complex(x, y);

  // COMPUTE g = inverse(gy) * gx

  // allocate g
  Loop4 *g = new Loop4(_polylen);

  // set g = inverse(gy)
  g->classical_adjoint(gy);

  // Compute inverse(gy) * gx; put result into g
  g->mul( *g, gx );

  Loop4 *g_plus = new Loop4(_polylen);

  try
  {
    // perform Birhoff factorization on g; put the result into g_plus
    _multiop[thread_id]._factorizer->factor_plus_minus( *g_plus, *g );
  }
  catch (int r)
  {
    delete g;

    // check for an error in the factorization
    delete g_plus;
    throw ( Exception( Exception::ERR_FACTORIZATION ) );
  }

#if 0
  std::cerr << "g=\n";
  g->printM( std::cerr );
  std::cerr << "gplus=\n";
  g_plus->printM( std::cerr );
#endif

  delete g;

  // compute F := gy * g_plus
  F.mul(gy, *g_plus );

  // deallocate the temporary loop g_plus
  delete g_plus;
  }
}

void
Lab::
initial_condition(
  Loop4 &gx0,
  Loop4 &gy0 )
{
  // NOTE: this "EvalLoop" is not a potential but an initial loop
  EvalLoop L;

  // set the "EvalLoop" L to _initial_x
  try
  {
    L.set( _initial_x );
  }
  catch ( base::Exception )
  { throw Exception( Exception::ERR_XSTART_SYNTAX ); }

  // evaluate L into gx0
  try
  {
    L.evaluate( gx0, _zstart );
  }
  catch ( base::Exception )
  { throw Exception( Exception::ERR_XSTART_EVAL ); }


  // set the "EvalLoop" L to _initial_y
  try
  {
    L.set( _initial_y );
  }
  catch ( base::Exception )
  { throw Exception( Exception::ERR_YSTART_SYNTAX ); }

  // evaluate L into gx0
  try
  {
    L.evaluate( gy0, _zstart );
  }
  catch ( base::Exception )
  { throw Exception( Exception::ERR_YSTART_EVAL ); }

#if 0
  // normalize X so that det(X)=1
  // by multiplying X by 1/sqrt(det(X))

  // allocate t
  t.allocate( _polylen + 1 );

  // t = det(X)
  X.det(t);

  // t = 1/t
  t.inv_pos();

  // t = sqrt(t)
  t.sqrt_pos();

  // X *= t
  X.mul( t );

  // deallocate t
  t.deallocate();
#endif
}

void
Lab::
start_v(
  Complex const &z0,
  uint k0,
  uint thread_id )
{
  // Initialize data for computing a surface.

  // Set the initial value for z (the point in the domain)
  _multidata[k0].z = _zstart;

  // Set the initial value for gx and gy
  // (the solution of the diff eq)
  initial_condition( _multidata[k0].gx, _multidata[k0].gy );

  // Set the initial value for potential_x (the x potential)

  _multiop[0]._potential_x->
    evaluate( _multidata[k0].potential_x, _multidata[k0].z );

  _multiop[0]._potential_y->
    evaluate( _multidata[k0].potential_y, _multidata[k0].z );

  // NOTE: F is not computed here because it not needed

  // compute the first segement
  compute_segment(
    _multidata[k0].z, z0 - _zstart,
    _multidata[k0].potential_x,
    _multidata[k0].potential_y,
    _multidata[k0].gx, _multidata[k0].gy,
    _multidata[k0].F,
    _initial_integrator_count,
    thread_id );
}

void
Lab::
step_v(
  Complex const &z0,
  Complex const &z1,
  uint k0,
  uint k1,
  uint thread_id )
{
  Complex dz;

  dz = z1 - z0;

  _multidata[k1].z = _multidata[k0].z;
  _multidata[k1].potential_x = _multidata[k0].potential_x;
  _multidata[k1].potential_y = _multidata[k0].potential_y;
  _multidata[k1].gx = _multidata[k0].gx;
  _multidata[k1].gy = _multidata[k0].gy;

  // NOTE: F is not copied because F is not needed

  DIE_IF( math::isnan( _multidata[k0].gx.col1().row1().data()[0]) );
  DIE_IF( math::isnan( _multidata[k0].gy.col1().row1().data()[0]) );

  compute_segment(
    _multidata[k1].z, dz,
    _multidata[k1].potential_x,
    _multidata[k1].potential_y,
    _multidata[k1].gx, _multidata[k1].gy,
    _multidata[k1].F,
    _integrator_count,
    thread_id );
}

void
Lab::
export_fn_v(
  base::vector<Real> &v,
  uint k )
{
  math::Vector3<Real> v0;
  _sym.compute( v0, _multidata[k].F, _lambda );

  v[0] = v0[0];
  v[1] = v0[1];
  v[2] = v0[2];
}

} // namespace kernel
} // namespace klab

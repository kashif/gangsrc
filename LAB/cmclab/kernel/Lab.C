/* GANG Software
 * LAB/cmclab/kernel/Lab.C
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
#include "base/Regex.H"
#include "parser/KeyParser.H"
#include "base/Timer.H"
#include "Lab.H"

namespace cmclab {
namespace kernel {

char const *Lab::_about_info =
"Created by Nick Schmitt";

Lab::
Lab()
    :
    lab::kernel::Lab(),
    _data(),
    _geometry(PARABOLIC)
{
  initialize();

  _potential.set_variable_name("z");
  initialize_data();
}


Lab::
~Lab()
{
}

void
Lab::
set_state_from_data()
{
  uint tmp_uint;

  // initial condition z
  try { evaluate( _zstart, data().get("zstart") ); }
  catch( base::Exception const & )
  { throw Exception( Exception::ERR_ZSTART ); }


  Real tmp_real;

  // mean curvature
  try { evaluate( tmp_real, data().get("mean_curvature") ); }
  catch( base::Exception const & )
  { throw Exception( Exception::ERR_MEAN_CURVATURE ); }
  set_mean_curvature(tmp_real);

  // lambda parameter
  base::vector<base::String> v;
  if ( base::match( "^R3[ \n\r\t]+(.+)$", data().get("lambda"), v ) )
  {
    // R^3
    Real lambda;
    try { evaluate( lambda, v[1] ); }
    catch( base::Exception const & )
    { throw Exception( Exception::ERR_LAMBDA ); }
    set_lambda_R3( lambda );
    spaceform( geom::SpaceForm() );
  }
  else if ( base::match( "^S3[ \n\r\t]+(.+);[ \n\r\t]+(.+);?$",
                         data().get("lambda"), v ) )
  {
    // S^3
    Real lambda0;
    try { evaluate( lambda0, v[1] ); }
    catch( base::Exception const & )
    { throw Exception( Exception::ERR_LAMBDA ); }

    Real lambda1;
    try { evaluate( lambda1, v[2] ); }
    catch( base::Exception const & )
    { throw Exception( Exception::ERR_LAMBDA ); }

    set_lambda_S3( lambda0, lambda1 );
    spaceform( geom::SpaceForm(3U, geom::SpaceForm::SPACEFORM_S) );
  }
  else if ( base::match( "^H3[ \n\r\t]+(.+)$",
                         data().get("lambda"), v ) )
  {
    // H3
    Complex lambda;
    try { evaluate( lambda, v[1] ); }
    catch( base::Exception const & )
    { throw Exception( Exception::ERR_LAMBDA ); }

    set_lambda_H3( lambda );
    spaceform( geom::SpaceForm(3U, geom::SpaceForm::SPACEFORM_H) );
  }
  else
  {
    throw Exception( Exception::ERR_LAMBDA );
  }

  // normal shift
  try { evaluate( tmp_real, data().get("normalshift") ); }
  catch( base::Exception const & )
  { throw Exception( Exception::ERR_NORMAL_SHIFT ); }
  set_normalshift(tmp_real);

  // initial condition X
  // introduce time variable into _xstart
  _xstart.clear_data();
  if ( ! time_varname().empty() )
  { _xstart.set_time( time(), time_varname() ); }

  try
  {
    _xstart.set( data().get("xstart") );
  }
  catch ( base::Exception )
  { throw Exception( Exception::ERR_XSTART ); }

  // potential
  _potential.clear_data();
  _potential.set_variable_name( data().get("potential_variable") );
  _potential.set_time( time(), time_varname() );

  _potential.set( data().get("potential"), true );

  //-----------------------------------
  // cmc parameters

  // integrator_count
  try { evaluate( tmp_uint, data().get("integrator_count") ); }
  catch( base::Exception const & )
  { throw Exception( Exception::ERR_INTEGRATOR_COUNT ); }
  if( tmp_uint < 1 )
  { throw Exception( Exception::ERR_INTEGRATOR_COUNT_VAL ); }
  integrator_count( tmp_uint );

  // initial_integrator_count
  try { evaluate( tmp_uint, data().get("initial_integrator_count") ); }
  catch( base::Exception const & )
  { throw Exception( Exception::ERR_INITIAL_INTEGRATOR_COUNT ); }
  if( tmp_uint < 1 )
  { throw Exception( Exception::ERR_INITIAL_INTEGRATOR_COUNT_VAL ); }
  initial_integrator_count( tmp_uint );

  // polynomial_length
  try { evaluate( tmp_uint, data().get("polynomial_length") ); }
  catch( base::Exception const & )
  { throw Exception( Exception::ERR_POLYNOMIAL_LENGTH ); }
#if 0
  if( tmp_uint < 1 || tmp_uint % 2 != 0 )
  { throw Exception( Exception::ERR_POLYNOMIAL_LENGTH_VAL ); }
#endif
  polynomial_length( tmp_uint );

  // basis_length
  try { evaluate( tmp_uint, data().get("basis_length") ); }
  catch( base::Exception const & )
  { throw Exception( Exception::ERR_BASIS_LENGTH ); }
#if 0
  if( tmp_uint < 2 || tmp_uint % 2 != 0 )
  { throw Exception( Exception::ERR_BASIS_LENGTH_VAL ); }
#endif
  basis_length( tmp_uint );

#if 0
  uint rows = 2*polynomial_length() + 1;
  uint cols = basis_length() / 2;

  if ( rows < cols )
  { throw Exception( Exception::ERR_BASIS_POLY_RATIO ); }
#endif

  // iwasawa method
  if ( data().get("iwasawa_method") == "cholesky" )
  { iwasawa_method(0); }
  else if (data().get("iwasawa_method") == "qr" )
  { iwasawa_method(1); }
  else
  { throw Exception( Exception::ERR_IWASAWA_METHOD ); }

  // iwasawa method
  if ( data().get("one_column") == "true" )
  { one_column(true); }
  else if (data().get("one_column") == "false" )
  { one_column(false); }
  else
  { throw Exception( Exception::ERR_TWO_COLUMN ); }

  // birkhoff
  if ( data().get("birkhoff") == "true" )
  { birkhoff(true); }
  else if ( data().get("birkhoff") == "false" )
  { birkhoff(false); }
  else
  { throw Exception( Exception::ERR_BIRKHOFF ); }
}

void
Lab::
initialize()
{
#if 0
  _time = 0.0;
  _time_varname = base::String();
#endif
  _data.reset();
}

void
Lab::
initialize_data()
{
  _integrator_count = 1;
  _initial_integrator_count = 100;
  _polylen = 20;
  _basislen = 40;
  _zstart = 0.0;
  _iwasawa_method = 1;
  _one_column = false;
  _birkhoff = false;
  _potential.clear_data();
}

void
Lab::
start_all_v(
  uint vertex_count,
  uint edge_count,
  uint thread_count )
{
  // we need a separate copy for each thread of:
  // (1) cmc_potential
  // (2) Integrate
  // (3) Iwasawa

  // set initial conditions for surface computation
#if 0
  if ( _polylen < 1 )
  { throw Exception( Exception::ERR_POLYLEN ); }

  if ( _polylen % 2 != 0 )
  { throw Exception( Exception::ERR_POLYLEN_PARITY ); }

  if ( _basislen < 1 )
  { throw Exception( Exception::ERR_BASISLEN ); }

  if ( _basislen % 2 != 0 )
  { throw Exception( Exception::ERR_BASISLEN_PARITY ); }

  if ( 2*_polylen+1 < _basislen/2 )
  { throw Exception( Exception::ERR_POLYLEN_BASISLEN ); }
#endif
  // initialize multiop
  _multiop.clear();
  _multiop.reserve(thread_count);

  // NOTE: inefficient: threadcount==2 even for a single processor
  uint i;
  for ( i = 0; i < thread_count; i++ )
  {
    MultiOp M;
    M._potential = new EvalLoop(_potential);
    M._integrator = new Integrator( M._potential, _polylen);
    M._iwasawa = new RIwasawa( _polylen, _basislen, _birkhoff, _one_column );
    _multiop.push_back(M);
  }

  // initialize MultiData
  MultiData M;
  _multidata.fill( M, vertex_count );
  for ( i = 0; i < vertex_count; i++ )
  {
    _multidata[i].X.allocate(_polylen);
    _multidata[i].F.allocate(_polylen);
    _multidata[i].xi.allocate(_polylen);
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
  // clear _multiop
  base::vector<MultiOp>::iterator i;
  for ( i = _multiop.begin(); i != _multiop.end(); i++ )
  {
    delete (*i)._potential;
    delete (*i)._integrator;
    delete (*i)._iwasawa;
  }
  _multiop.clear();

  // deallocate xi since it's no longer needed
  {
  uint i;
  for ( i = 0; i < _multidata.size(); i++ )
  {
    _multidata[i].xi.allocate(0);
  }
  }
}

void
Lab::
start_v(
  Complex const &z0,
  uint k0,
  uint thread_id )
{
  //---------------------------
  // initial value

  _multidata[k0].z = _zstart;
  _xstart.evaluate( _multidata[k0].X, _zstart );

  _multiop[thread_id]._potential->evaluate( _multidata[k0].xi,
                                         _multidata[k0].z );

  // NOTE: F is not computed because it is not needed
  // (should have option of not storing F at all)
  compute_segment(
    _multidata[k0].z, z0 - _zstart,
    _multidata[k0].xi, _multidata[k0].X, _multidata[k0].F,
    _multidata[k0].metric,
    _initial_integrator_count,
    thread_id );

//  _multidata[k0].dump(std::cerr);

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
  _multidata[k1].xi = _multidata[k0].xi;
  _multidata[k1].X = _multidata[k0].X;

  // NOTE: F is not copied because F is not needed

  DIE_IF( math::isnan(_multidata[k0].X.col1().row1().data()[0]) );

  compute_segment(
    _multidata[k1].z, dz,
    _multidata[k1].xi, _multidata[k1].X, _multidata[k1].F,
    _multidata[k1].metric,
    _integrator_count,
    thread_id );

//  _multidata[k1].dump(std::cerr);
}

void
Lab::
export_fn_v(
  base::vector<Real> &v,
  uint k )
{
  if ( _geometry == PARABOLIC )
  {
    _lambda0 = exp2pii(_lambda_R3);
  }
  else if ( _geometry == ELLIPTIC )
  {
    _lambda0 = exp2pii(_lambda0_S3);
    _lambda1 = exp2pii(_lambda1_S3);
  }
  else if ( _geometry == HYPERBOLIC )
  {
    _lambda0 = _lambda_H3;
  }

  // NOTE: exp2pii is inefficient

  GeometryType n = _geometry;

  if ( n == PARABOLIC )
  {
    // parabolic R^3
    if (v.size() != 3U)
    {
      throw Exception( Exception::ERR_SPACEFORM );
    }

    math::Vector3<Real> v0;

    _sym.R3( v0, _multidata[k].F,  _mean_curvature, _lambda0, _normalshift );

    v[0] = v0[0];
    v[1] = v0[1];
    v[2] = v0[2];
  }
  else if ( n == ELLIPTIC )
  {
    // elliptic S^3

    if (v.size() != 4U)
    {
      throw Exception( Exception::ERR_SPACEFORM );
    }

    math::VectorX<Real,4U> v0;

    _sym.S3( v0, _multidata[k].F, _lambda0, _lambda1 );

    v[0] = v0[0];
    v[1] = v0[1];
    v[2] = v0[2];
    v[3] = v0[3];
  }
  else if ( n == HYPERBOLIC )
  {
    // hyperbolic H^3

    if (v.size() != 4U)
    {
      throw Exception( Exception::ERR_SPACEFORM );
    }

    if ( math::effectively_zero( std::abs(_lambda0) - 1.0) )
    {
      throw base::Exception( "lambda is on the unit circle" );
    }
    math::VectorX<Real,4U> v0;

    _sym.H3( v0, _multidata[k].F, _lambda0 );

    v[0] = v0[0];
    v[1] = v0[1];
    v[2] = v0[2];
    v[3] = v0[3];
  }
  else
  {
    DIE();
  }
}


void
Lab::
compute_segment(
  Complex &z,
  Complex const &dz,
  Potential &xi,
  Loop4 &X,
  Loop4 &F,
  Real &metric,
  uint steps,
  uint thread_id )
{
  // integrate one step
  _multiop[thread_id]._integrator->integrate( z, xi, X, dz, steps );

  // perform Iwasawa decomposition
  _multiop[thread_id]._iwasawa->factor( F, X );
}

void
Lab::
set_lambda_R3( Real lambda )
{
  _geometry = PARABOLIC;
  _lambda_R3 = lambda;
}


void
Lab::
set_lambda_S3( Real lambda0, Real lambda1 )
{
  _geometry = ELLIPTIC;
  _lambda0_S3 = lambda0;
  _lambda1_S3 = lambda1;
}

void
Lab::
set_lambda_H3( Complex const &lambda )
{
  _geometry = HYPERBOLIC;
  _lambda_H3 = lambda;
}

Complex
Lab::
exp2pii( Real r )
{
  Complex lambda;
  if ( r == trunc(r) )
  {
    lambda = 1.0;
  }
  else
  {
    double angle = (2*math::pi)*r;
    lambda = Complex( math::cos(angle), math::sin(angle) );
  }
  return lambda;
}

void
Lab::
MultiData::
dump( std::ostream &o ) const
{
  o << "-------------------------------\n";
  o << "z=";
  base::printM(o, z);
  o << "\n";

  o << "X=";
  X.printM(o);
  o << "\n";

  o << "F=";
  F.printM(o);
  o << "\n";
}

} // namespace kernel
} // namespace cmclab

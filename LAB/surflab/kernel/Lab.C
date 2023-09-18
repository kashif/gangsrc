/* GANG Software
 * LAB/surflab/kernel/Lab.C
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

#include "base/String.H"
#include "base/Regex.H"
#include "math/VectorX.H"
#include "Lab.H"

namespace surflab {
namespace kernel {

char const *Lab::_about_info =
"Created by Nick Schmitt";

Lab::
Lab()
    :
    lab::kernel::Lab(),
    surflab::ui::Ui(),
    _data(),
    _multidata(),
    _multiop(),
    _varname1(),
    _varname2()
{
}

Lab::
~Lab()
{
}

void
Lab::
set_state_from_data()
{
  geom::SpaceForm::Space s;

  // geometry
  if ( data().get("geometry") == "parabolic" )
  {
    s = geom::SpaceForm::SPACEFORM_R;
  }
  else if ( data().get("geometry") == "hyperbolic" )
  {
    s = geom::SpaceForm::SPACEFORM_H;
  }
  else if ( data().get("geometry") == "elliptic" )
  {
    s = geom::SpaceForm::SPACEFORM_S;
  }
  else
  { throw Exception(Exception::ERR_GEOMETRY); }

  // dimension
  uint d;
  try {
//    data().get("dim").to_number( d );
    evaluate( d, data().get("dim") );
  }
  catch (base::Exception const &)
  { throw Exception(Exception::ERR_DIM); }

  geom::SpaceForm ss(d, s);
  spaceform( ss );

  // variable names
  if ( base::match( "^[a-zA-Z_][a-zA-Z0-9_]*$", data().get("var1") ) )
  { _varname1 = data().get("var1"); }
  else
  { throw Exception(Exception::ERR_VARNAME); }


  if ( base::match( "^[a-zA-Z_][a-zA-Z0-9_]*$", data().get("var2") ) )
  { _varname2 = data().get("var2"); }
  else
  { throw Exception(Exception::ERR_VARNAME); }

  // surface parametrization X
  _surf_expr0.clear();


  eval::Evaluator<Complex> E;


  uint i;
  for ( i = 0; i < dim(); i++ )
  {
    eval::Expression<Complex> e;
    e.create_variable( _varname1 );
    e.create_variable( _varname2 );

    // introduce the time variable
    if ( ! time_varname().empty() )
    {
      e.create_variable( time_varname() );
    }

    base::String x;
    x.to_string( i+1 );
    x = "x" + x;

    try { E.evaluate( e, data().get(x) ); }
    catch ( base::Exception const & )
    { throw Exception(Exception::ERR_SYNTAX, i); }

    _surf_expr0.push_back(e);
  }
}

void
Lab::
function(
  base::vector<Real> &v,
  Complex const &z,
  uint thread_id )
  throw( base::Exception )
{
  DIE_IF( v.size() != dim() );

  Complex w;

  uint i;
  for ( i = 0; i < dim(); i++ )
  {
    _multiop[thread_id]._surf_expr[i].set_variable( _varname1, z.real() );
    _multiop[thread_id]._surf_expr[i].set_variable( _varname2, z.imag() );

    // set the time variable to _time
    if ( ! time_varname().empty() )
    {
      _multiop[thread_id]._surf_expr[i].set_variable(
        time_varname(), time() );
    }

    try {
      _multiop[thread_id]._evaluator.evaluate(
        w, _multiop[thread_id]._surf_expr[i] );
    }
    catch ( base::Exception const & )
    { throw Exception(Exception::ERR_SYNTAX, i); }

    if (math::isnan(w.real()))
    { throw Exception(Exception::ERR_MATH, i); }

    v[i] = w.real();
  }
}

void
Lab::
start_all_v(
  uint vertex_count,
  uint edge_count,
  uint thread_count )
{
  DIE_IF( thread_count == 0 );
  DIE_IF(_surf_expr0.size() != dim() );
  WARN_IF( vertex_count == 0, "vertex_count == 0" );

  // initialize _multidata
  MultiData m;
  m._surface.fill( 0.0, dim() );
  _multidata.fill( m, vertex_count );

  // initialize _multiop
  MultiOp o;
  o._surf_expr = _surf_expr0;
  _multiop.fill( o, thread_count );
}

void
Lab::
end_all_v(
  uint vertex_count,
  uint edge_count,
  uint thread_count )
{
  _multiop.clear();
}

void
Lab::
start_v(
  std::complex<Real> const &z0,
  uint k0,
  uint thread_id )
{
  DIE_IF( k0 >= _multidata.size() );
  _multidata[k0]._domain[0] = z0.real();
  _multidata[k0]._domain[0] = z0.imag();
  function( _multidata[k0]._surface, z0, thread_id );
}

void
Lab::
step_v(
  std::complex<Real> const &z0,
  std::complex<Real> const &z1,
  uint k0,
  uint k1,
  uint thread_id )
{
  DIE_IF( k0 >= _multidata.size() );
  DIE_IF( k1 >= _multidata.size() );
  _multidata[k1]._domain[0] = z0.real();
  _multidata[k1]._domain[0] = z0.imag();
  function( _multidata[k1]._surface, z1, thread_id );
}

void
Lab::
export_fn_v(
  base::vector<Real> &v,
  uint k )
{
  DIE_IF( k >= _multidata.size() );
  DIE_IF( v.size() != _multidata[k]._surface.size() );
  v = _multidata[k]._surface;
}

} // namespace kernel
} // namespace surflab

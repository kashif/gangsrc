/* GANG Software
 * LAB/minlab/kernel/Lab.C
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
#include "math/Math.H"
#include "math/VectorX.H"
#include "base/String.H"
#include "Lab.H"

namespace minlab {
namespace kernel {

char const *Lab::_about_info =
"Created by Nick Schmitt";

Lab::
Lab()
    :
    lab::kernel::Lab(),
    LabBase(),
    ui::Ui(),
    _data(),
    _surf_expr0(),
    _surf_expr(),
    _evaluator(),
    _varname()
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
  /*
    Sets the internal state of *this from mdata.
  */

  eval::Evaluator<Complex> E;

  initialize_data();

  // variable names
  if ( base::match( "^[a-zA-Z_][a-zA-Z0-9_]*$", data().get("varname") ) )
  {
    _varname = data().get("varname");
  }
  else
  {
    throw Exception(
      Exception::ErrorCode(Exception::ERR_VARNAME));
  }

  if ( base::String::compare_nocase( data().get("mode"), "spinor" ) == 0 )
  {
    _mode = SPINOR;
  }
  else if ( base::String::compare_nocase( data().get("mode"), "weierstrass" ) == 0 )
  {
    _mode = WEIERSTRASS;
  }
  else
  {
    throw Exception(Exception::ERR_MODE);
  }

  // set _zstart
  try { evaluate( _zstart, data().get("zstart") ); }
  catch ( base::Exception const & )
  { throw Exception(Exception::ERR_ZSTART); }

  if ( _mode == SPINOR )
  {
    // spinor data 1
    _surf_expr0.first.clear();
    _surf_expr0.first.create_variable( _varname );

    // introduce the time variable
    if ( ! time_varname().empty() )
    {
      _surf_expr0.first.create_variable( time_varname() );
    }

    try { E.evaluate( _surf_expr0.first, data().get("spinor1") ); }
    catch ( base::Exception const & )
    { throw Exception(Exception::ERR_SPINOR1); }

    // spinor data 2
    _surf_expr0.second.clear();
    _surf_expr0.second.create_variable( _varname );

    // introduce the time variable
    if ( ! time_varname().empty() )
    {
      _surf_expr0.second.create_variable( time_varname() );
    }

    try { E.evaluate( _surf_expr0.second, data().get("spinor2") ); }
    catch ( base::Exception const & )
    { throw Exception(Exception::ERR_SPINOR2); }
  }
  else
  {
    // weirstrass data 1
    _surf_expr0.first.clear();
    _surf_expr0.first.create_variable( _varname );

    // introduce the time variable
    if ( ! time_varname().empty() )
    {
      _surf_expr0.first.create_variable( time_varname() );
    }

    try { E.evaluate( _surf_expr0.first, data().get("weierstrass_g") ); }
    catch ( base::Exception const & )
    { throw Exception(Exception::ERR_WEIERSTRASS_G); }

    // weirstrass data 1
    _surf_expr0.second.clear();
    _surf_expr0.second.create_variable( _varname );

    // introduce the time variable
    if ( ! time_varname().empty() )
    {
      _surf_expr0.second.create_variable( time_varname() );
    }

    try { E.evaluate( _surf_expr0.second, data().get("weierstrass_f") ); }
    catch ( base::Exception const & )
    { throw Exception(Exception::ERR_WEIERSTRASS_F); }
  }

  // integrator_count
  try { evaluate( _integrator_count, data().get("integrator_count") ); }
  catch ( base::Exception const & )
  { throw Exception(Exception::ERR_INTEGRATOR_COUNT); }

  // initial_integrator_count
  try { evaluate( _initial_integrator_count,
                  data().get("initial_integrator_count") ); }
  catch ( base::Exception const & )
  { throw Exception(Exception::ERR_INITIAL_INTEGRATOR_COUNT); }

  // Xstart1
  try { evaluate( _Xstart[0], data().get("Xstart1") ); }
  catch ( base::Exception const & )
  { throw Exception(Exception::ERR_XSTART1); }

  // Xstart2
  try { evaluate( _Xstart[1], data().get("Xstart2") ); }
  catch ( base::Exception const & )
  { throw Exception(Exception::ERR_XSTART2); }

  // Xstart3
  try { evaluate( _Xstart[2], data().get("Xstart3") ); }
  catch ( base::Exception const & )
  { throw Exception(Exception::ERR_XSTART3); }
}

void
Lab::
integration_function(
  math::VectorX<Complex,3U> &y,
  Complex const &z,
  uint thread_id )
{
  // evaluate v1
  Complex v1;

  _surf_expr[thread_id].first.set_variable( _varname, z );

  if ( ! time_varname().empty() )
  {
    _surf_expr[thread_id].first.set_variable( time_varname(), time() );
  }

  try {
    _evaluator[thread_id].evaluate( v1, _surf_expr[thread_id].first );
  }
  catch ( base::Exception const & )
  { throw Exception(Exception::ERR_INTEGRAND); }


  // evaluate v2
  Complex v2;

  _surf_expr[thread_id].second.set_variable( _varname, z );

  if ( ! time_varname().empty() )
  {
    _surf_expr[thread_id].second.set_variable( time_varname(), time() );
  }

  try {
    _evaluator[thread_id].evaluate( v2, _surf_expr[thread_id].second ); }
  catch ( base::Exception const & )
  { throw Exception(Exception::ERR_INTEGRAND); }

  if ( _mode == SPINOR )
  {
    // v1 = s1
    // v2 = s2
    y[0] = math::sqr(v1);
    y[1] = v1 * v2;
    y[2] = math::sqr(v2);
  }
  else if ( _mode == WEIERSTRASS )
  {
    // v1 = g
    // v2 = f
    y[0] = v2;
    y[1] = v1 * v2;
    y[2] = v1 * y[1];
  }
  else
  {
    DIE();
  }
}

void
Lab::
start_all_v(
  uint vertex_count,
  uint edge_count,
  uint thread_count )
{
  // initialize _evaluator
  // initialize _surf_expr
  uint i;
  for ( i = 0; i < thread_count; i++ )
  {
    _evaluator.push_back( eval::Evaluator<Complex>() );
    _surf_expr.push_back(_surf_expr0);
  }

  // baseclass version
  LabBase::start_all_v(vertex_count, edge_count, thread_count);
}

} // namespace kernel
} // namespace minlab

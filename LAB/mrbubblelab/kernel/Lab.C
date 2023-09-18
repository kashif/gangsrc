/* GANG Software
 * LAB/mrbubblelab/kernel/Lab.C
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
#include "math/VectorX.H"
#include "Lab.H"

namespace mrbubblelab {
namespace kernel {

char const *Lab::_about_info =
"Created by Nick Schmitt";

Lab::
Lab()
    :
    lab::kernel::Lab(),
    _data(),
    _mrbubble(),
    _surface()                 
{

  _integrator_count = 3U;
}

Lab::
~Lab()
{
}

void
Lab::
set_state_from_data()
{
  try { evaluate( _coefficient, data().get("coefficient") ); }
  catch ( base::Exception const & )
  { throw Exception(Exception::ERR_COEFFICIENT); }

  try { evaluate( _exponent, data().get("exponent") ); }
  catch ( base::Exception const & )
  { throw Exception(Exception::ERR_EXPONENT); }

  try { evaluate( _u0, data().get("u0") ); }
  catch ( base::Exception const & )
  { throw Exception(Exception::ERR_U0); }

  try { evaluate( _uprime0, data().get("uprime0") ); }
  catch ( base::Exception const & )
  { throw Exception(Exception::ERR_UPRIME0); }

  try { evaluate( _normalshift, data().get("normalshift").c_str() ); }
  catch ( base::Exception const & )
  { throw Exception(Exception::ERR_NORMALSHIFT); }

  try { evaluate( _initial_integrator_count,
                  data().get("initial_integrator_count") ); }
  catch ( base::Exception const & )
  { throw Exception(Exception::ERR_INITIAL_INTEGRATOR_COUNT); }

  try { evaluate( _integrator_count, data().get("integrator_count") ); }
  catch ( base::Exception const & )
  { throw Exception(Exception::ERR_INTEGRATOR_COUNT); }
}

void
Lab::
start_all_v(
  uint vertex_count,
  uint edge_count,
  uint thread_count )
{
  DIE_IF( thread_count == 0 );

  // initialize _surface
  {
     MrBubble::Data tmp;
     tmp.X.set(0.0);
     tmp.N.set(0.0);
     _surface.fill( tmp, vertex_count);
  }

  // initialize _mrbubble
  uint i;
  for ( i = 0; i < thread_count; i++ )
  {
    // NOTE: memory leak if MrBubble constructor throws an exception
    _mrbubble.push_back(
      new MrBubble( _coefficient, _exponent, _u0, _uprime0 ) );
  }
}

void
Lab::
end_all_v(
  uint vertex_count,
  uint edge_count,
  uint thread_count )
{
  // deallocate _mrbubble
  uint i;
  for ( i = 0; i < thread_count; i++ )
  {
    delete _mrbubble[i];
  }
  _mrbubble.clear();
}

void
Lab::
start_v(
  Complex const &z0,
  uint k0,
  uint thread_id )
{
  _mrbubble[thread_id]->start(
    _surface[k0],
    z0, _initial_integrator_count );
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
  _surface[k1] = _surface[k0];
  _mrbubble[thread_id]->step(
    _surface[k1],
    z1,
    _integrator_count );
}

void
Lab::
export_fn_v(
  base::vector<Real> &v,
  uint k )
{
  DIE_IF( v.size() != 3U );

  math::VectorX<Real,3U> f;
  // f = X + shift*N
  f.mul_add( _surface[k].X, _normalshift, _surface[k].N );
  v[0] = f[0];
  v[1] = f[1];
  v[2] = f[2];
}

} // namespace kernel
} // namespace mrbubblelab

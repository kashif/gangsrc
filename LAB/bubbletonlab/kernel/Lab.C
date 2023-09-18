/* GANG Software
 * LAB/bubbletonlab/kernel/Lab.C
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

namespace bubbletonlab {
namespace kernel {

char const *Lab::_about_info =
"Created by Nick Schmitt";

Lab::
Lab()
    :
    lab::kernel::Lab(),
    _normalshift(1.0),
    _data(),
    _bubbletonlab(),
    _center(),
    _size()
{

  initialize_data();
}

Lab::
~Lab()
{
}

void
Lab::
initialize_data()
{
  _center.clear();
  _size.clear();
  _normalshift = 1.0;
}

void
Lab::
set_state_from_data()
{
  initialize_data();

  // center and size
  base::vector<base::String> center_str;
  base::split( center_str, data().get("center"), ';' );

  base::vector<base::String> size_str;
  base::split( size_str, data().get("size"), ';' );

  // NOTE: does not deal with empty strings
  // e.g. upon input "2; 3;"
  if( center_str.size() != size_str.size() )
  { throw Exception(Exception::ERR_COUNT); }

  uint i;
  for ( i = 0; i < center_str.size(); i++ )
  {
    Complex x;

    WARN_IF(center_str[i].empty());

    try { evaluate( x, center_str[i] ); }
    catch ( base::Exception const & )
    { throw Exception(Exception::ERR_CENTER); }
    _center.push_back(x);


    WARN_IF(size_str[i].empty());

    try { evaluate( x, size_str[i] ); }
    catch ( base::Exception const & )
    { throw Exception(Exception::ERR_SIZE); }
    _size.push_back(x);
  }

  // normalshift
  try { evaluate( _normalshift, data().get("normalshift") ); }
  catch ( base::Exception const & )
  { throw Exception(Exception::ERR_NORMAL_SHIFT); }
}

void
Lab::
function(
  MultiData &y,
  Complex const &z,
  uint thread_id )
  throw( base::Exception )
{
  // compute point on bubbletonlab
#if 0
  math::VectorX<Real,3U> X;
  math::VectorX<Real,3U> N;
#endif
  _bubbletonlab[thread_id]->compute( y.X, y.N, z );
}

void
Lab::
start_all_v(
  uint vertex_count,
  uint edge_count,
  uint thread_count )
{
  DIE_IF( thread_count == 0 );

  // initialize _domain_vect
  {
    math::VectorX<Real,2U> tmp;
    tmp.set(0.0);
    _domain_vect.fill( tmp, vertex_count );
  }

  // initialize _surface
  {
    MultiData tmp;
    tmp.X.set(0.0);
    tmp.N.set(0.0);
    _surface.fill( tmp, vertex_count);
  }

  // initialize _bubbletonlab
  uint i;
  for ( i = 0; i < thread_count; i++ )
  {
    // NOTE: memory leak if Bubbleton constructor throws an exception
    _bubbletonlab.push_back( new Bubbleton( _center, _size ) );
  }
}

void
Lab::
end_all_v(
  uint vertex_count,
  uint edge_count,
  uint thread_count )
{
  // deallocate _bubbletonlab
  uint i;
  for ( i = 0; i < thread_count; i++ )
  {
    delete _bubbletonlab[i];
  }
  _bubbletonlab.clear();
}

void
Lab::
start_v(
  std::complex<Real> const &z0,
  uint k0,
  uint thread_id )
{
  _domain_vect[k0][0] = z0.real();
  _domain_vect[k0][1] = z0.imag();
  function( _surface[k0], z0, thread_id );
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
  _domain_vect[k1][0] = z1.real();
  _domain_vect[k1][1] = z1.imag();
  function( _surface[k1], z1, thread_id );
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
} // namespace bubbletonlab

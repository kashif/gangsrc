/* GANG Software
 * LAB/minlab/kernel/LabBase.C
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

#include "LabBase.H"

namespace minlab {
namespace kernel {

Complex const LabBase::I(0.0, 1.0);

LabBase::
LabBase()
    :
    lab::kernel::LabBase2(),
    _mode(NONE),
    _integrator_count(0),
    _initial_integrator_count(0),
    _zstart(0.0),
    _Xstart(),
    _multidata(),
    _lambda(1.0)
{
}

LabBase::
~LabBase()
{
}


void
LabBase::
set_associate( double theta )
{
  // computes projection C^3 --> R^3

  // theta family paramter is lambda = exp(2 pi i * theta)
  // so whole loop is [0,1).

  if ( theta == trunc(theta) )
  {
    _lambda = 1.0;
  }
  else
  {
    double angle = (2*math::pi)*theta;
    _lambda = Complex( math::cos(angle), math::sin(angle) );
  }
}


void
LabBase::
initialize_data()
{
  _integrator_count = 10;
  _initial_integrator_count = 200;
  _zstart = 0.0;
  _Xstart.set( 0.0 );
}

void
LabBase::
compute_segment(
  math::VectorX<Complex,3U> &S,
  Complex &z,
  Complex const &dz,
  uint steps,
  uint thread_id )
{
  Integrator integrator(this, thread_id);

  integrator._mode = _mode;

  Complex z2 = z + dz;

  math::VectorX<Complex,3U> s;
  integrator.compute( s, z, z2, steps );

  S += s;
  z += dz;

  if ( math::isnan(S[0]) || math::isnan(S[1]) ||
       math::isnan(S[2]) || math::isnan(z) )
  {
    throw base::Exception("nan");
  }
}

void
LabBase::
export_fn_v(
  base::vector<Real> &v,
  uint k )
{
  to_real( v, _multidata[k].S );
}

int
LabBase::
to_real(
  base::vector<Real> &v,
  math::VectorX<Complex,3U> const &S ) const
{
  Complex v11 = _lambda * S[0];
  Complex v12 = _lambda * S[1];
  Complex v22 = _lambda * S[2];
  v[0] = 0.5 * math::chop( std::real(v11 - v22) );
  v[1] = 0.5 * math::chop( -std::imag(v11 + v22) );
  v[2] = 0.5 * math::chop( std::real(2.0*v12) );
  return 0;
}

void
LabBase::
start_all_v(
  uint vertex_count,
  uint edge_count,
  uint thread_count )
{
  DIE_IF( thread_count == 0 );

  MultiData m;
  m.z = 0.0;
  _multidata.fill( m, vertex_count );
}

void
LabBase::
start_v(
  Complex const &z0,
  uint k0,
  uint thread_id )
{
  // initialize z from _zstart
  _multidata[k0].z = _zstart;

  // initialize S from X
  _multidata[k0].S[0] = _Xstart[0] - I*_Xstart[1];
  _multidata[k0].S[1] = - _Xstart[0] - I*_Xstart[1];
  _multidata[k0].S[2] = _Xstart[2];

  compute_segment(
    _multidata[k0].S, _multidata[k0].z,
    z0 - _zstart, _initial_integrator_count, thread_id );
}

void
LabBase::
step_v(
  Complex const &z0,
  Complex const &z1,
  uint k0, uint k1,
  uint thread_id )
{
  // set z0, z1, dz
  Complex dz = z1 - z0;

  _multidata[k1].z = _multidata[k0].z;
  _multidata[k1].S = _multidata[k0].S;

  compute_segment(
    _multidata[k1].S, _multidata[k1].z, dz,
    _integrator_count, thread_id );
}

} // namespace kernel
} // namespace minlab

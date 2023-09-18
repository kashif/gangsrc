/* GANG Software
 * GEOM/motion/TransformX.C
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

#include "math/Math.H"
#include "math/Matrix.H"
#include "TransformX.H"

namespace motion {


TransformX::
TransformX()
    :
    _geometry(PARABOLIC),
    _is_translation(false),
    _matrix_dim(0),
    _on(false)
{
}

TransformX::
~TransformX()
{
}


void
TransformX::
get_parameters(
Real &a11,
  Real &a12,
  Real &a21,
  Real &a22,
  Real a,
  GeometryGroup mode )
{
  if ( mode == PARABOLIC )
  {
    a11 = 1.0f;
    a12 = a;
    a21 = 0.0f;
    a22 = 1.0f;
  }
  else if ( mode == ELLIPTIC )
  {
    a11 = math::cos(a);
    a12 = -math::sin(a);
    a21 = -a12;
    a22 = a11;
  }
  else if ( mode == HYPERBOLIC )
  {
    a11 = math::cosh(a);
    a12 = math::sinh(a);
    a21 = a12;
    a22 = a11;
  }
  else
  {
    DIE();
  }
}

//----------------------------------------

TransformXRotation1::
TransformXRotation1(
  uint n0,
  uint n1,
  uint n2,
  Real u,
  Real v,
  Real a,
  GeometryGroup mode,
  bool is_translation,
  uint matrix_dim )
{
  set( n0, n1, n2, u, v, a, mode, is_translation, matrix_dim );
}


void
TransformXRotation1::
set(
  uint n0,
  uint n1,
  uint n2,
  Real u,
  Real v,
  Real a,
  GeometryGroup mode,
  bool is_translation,
  uint matrix_dim )
{
  DIE_IF( n0 >= matrix_dim );
  DIE_IF( n1 >= matrix_dim );
  DIE_IF( n2 >= matrix_dim );
  DIE_IF(n0==n1||n0==n2||n1==n2);

  _n0 = n0;
  _n1 = n1;
  _n2 = n2;

  _u = u;
  _v = v;
  math::normalize( _u, _v );
  _a = a;
  _geometry = mode;
  _is_translation = is_translation;
  _matrix_dim = matrix_dim;
  _on = ! math::effectively_zero(a);
}


TransformXRotation1::
TransformXRotation1(
  uint n0,
  uint n2,
  Real a,
  GeometryGroup mode,
  bool is_translation,
  uint matrix_dim )
{
  // special case of above: rotate or translate in the n0-n1
  // coordinate plane. a=speed.

  uint n1 = 0;
  for ( n1 = 0; n1 < 4; n1++ )
  {
    if ( n1 != n0 && n1 != n2 ) { break; }
  }
  set( n0, n1, n2, 1.0f, 0.0f, a, mode, is_translation, matrix_dim );
}


void
TransformXRotation1::
to_matrix(
  math::Matrix<Real> &t ) const
{
  using math::sqr;
  using math::norm;

  t.allocate(_matrix_dim);
  t.identity();

  if ( !_on ) { return; }

  Real a11, a12, a21, a22;
  get_parameters( a11, a12, a21, a22, _a, _geometry );

  // NOTE: t is transposed
  t[_n0][_n0] = a11 * sqr(_u) + sqr(_v);
  t[_n0][_n1] = (-1.0f + a11) * _u * _v;
  t[_n0][_n2] = a21 * _u;

  t[_n1][_n0] = (-1.0f + a11) * _u * _v;
  t[_n1][_n1] = sqr(_u) + a11 * sqr(_v);
  t[_n1][_n2] = a21 * _v;

  t[_n2][_n0] = a12 * _u;
  t[_n2][_n1] = a12 * _v;
  t[_n2][_n2] = a22;
}


void
TransformXRotation1::
decay( Real decayfactor, Real clip )
{
  if (!_on) {return; }

  _a *= decayfactor;
  if ( math::abs(_a) < clip )
  {
    _on = false;
  }
}

//----------------------------------------

TransformXRotation2::
TransformXRotation2(
  uint n0,
  uint n1,
  uint n2,
  uint n3,
  Real a,
  Real b,
  GeometryGroup mode,
  bool is_translation,
  uint matrix_dim )
{
  // rotate in the n0-n1 coordinate plane by a
  //    and in the n2-n3 coordinate plane by b

  DIE_IF( n0 >= matrix_dim );
  DIE_IF( n1 >= matrix_dim );
  DIE_IF( n2 >= matrix_dim );
  DIE_IF( n3 >= matrix_dim );
  DIE_IF(n0==n1||n0==n2||n1==n2||n0==n3||n0==n2||n0==n3);

  _n0 = n0;
  _n1 = n1;
  _n2 = n2;
  _n3 = n3;
  _a = a;
  _b = b;
  _geometry = mode;
  _is_translation = is_translation;
  _matrix_dim = matrix_dim;
  _on = ! math::effectively_zero(a) && ! math::effectively_zero(b);
}


void
TransformXRotation2::
to_matrix(
  math::Matrix<Real> &t ) const
{
  using math::sqr;
  using math::norm;

  t.allocate(_matrix_dim);
  t.identity();

  if ( ! _on ) { return; }

  Real a11, a12, a21, a22;
  // get the parameters for the first rotation
  get_parameters( a11, a12, a21, a22, _a, _geometry );

  // NOTE: t is transposed
  t[_n0][_n0] = a11;
  t[_n0][_n1] = a21;
  t[_n1][_n0] = a12;
  t[_n1][_n1] = a22;

  // get the parameters for the second rotation
  get_parameters( a11, a12, a21, a22, _b, _geometry );

  t[_n2][_n2] = a11;
  t[_n2][_n3] = a21;
  t[_n3][_n2] = a12;
  t[_n3][_n3] = a22;
}



void
TransformXRotation2::
decay( Real decayfactor, Real clip )
{
  _a *= decayfactor;
  _b *= decayfactor;
  if ( math::abs(_a) < clip && math::abs(_b) < clip )
  {
    _on = false;
  }
}

//----------------------------------------

TransformXMoebiusParabolic2::
TransformXMoebiusParabolic2(
  uint n0,
  uint n1,
  uint n2,
  uint n3,
  Real u,
  Real v,
  Real a,
  bool inverse,
  bool is_translation,
  uint matrix_dim )
{
  DIE_IF( n0 >= matrix_dim );
  DIE_IF( n1 >= matrix_dim );
  DIE_IF( n2 >= matrix_dim );
  DIE_IF( n3 >= matrix_dim );
  DIE_IF(n0==n1||n0==n2||n1==n2);

  _n0 = n0;
  _n1 = n1;
  _n2 = n2;
  _n3 = n3;
  _u = u;
  _v = v;
  math::normalize( _u, _v );
  _a = a;
  _geometry = PARABOLIC;
  _inverse = inverse;
  _is_translation = is_translation;
  _matrix_dim = matrix_dim;
  _on = ! math::effectively_zero(a);
}


void
TransformXMoebiusParabolic2::
to_matrix(
  math::Matrix<Real> &t ) const
{
  using math::sqr;
  using math::norm;

  t.allocate(_matrix_dim);
  t.identity();

  if ( ! _on ) { return; }

  Real u = _a * _u;
  Real v = _a * _v;
  Real b = 0.5f * math::norm(u, v);

  t[_n0][_n2] = u;
  t[_n0][_n3] = u;

  t[_n1][_n2] = v;
  t[_n1][_n3] = v;

  t[_n2][_n0] = -u;
  t[_n2][_n1] = -v;
  t[_n2][_n2] = 1.0f - b;
  t[_n2][_n3] = -b;

  t[_n3][_n0] = u;
  t[_n3][_n1] = v;
  t[_n3][_n2] = b;
  t[_n3][_n3] = 1.0f + b;

  if ( _inverse )
  {
    t.transpose();
  }
}


void
TransformXMoebiusParabolic2::
decay( Real decayfactor, Real clip )
{
  _a *= decayfactor;
  if ( math::abs(_a) < clip )
  {
    _on = false;
  }
}

//----------------------------------------

TransformXMoebiusParabolic1::
TransformXMoebiusParabolic1(
  uint n0,
  uint n1,
  uint n2,
  Real a,
  bool inverse,
  bool is_translation,
  uint matrix_dim )
{
  DIE_IF( n0 >= matrix_dim );
  DIE_IF( n1 >= matrix_dim );
  DIE_IF( n2 >= matrix_dim );
  DIE_IF(n0==n1||n0==n2||n1==n2);

  _n0 = n0;
  _n1 = n1;
  _n2 = n2;
  _a = a;
  _geometry = PARABOLIC;
  _inverse = inverse;
  _is_translation = is_translation;
  _matrix_dim = matrix_dim;
  _on = ! math::effectively_zero(a);
}


void
TransformXMoebiusParabolic1::
decay( Real decayfactor, Real clip )
{
  _a *= decayfactor;
  if ( math::abs(_a) < clip )
  {
    _on = false;
  }
}


void
TransformXMoebiusParabolic1::
to_matrix(
  math::Matrix<Real> &t ) const
{
  using math::sqr;
  using math::norm;

  t.allocate(_matrix_dim);
  t.identity();

  if ( ! _on ) { return; }

  Real b = 0.5f * math::sqr(_a);

  t[_n0][_n1] = _a;
  t[_n0][_n2] = _a;

  t[_n1][_n0] = -_a;
  t[_n1][_n1] = 1.0f - b;
  t[_n1][_n2] = -b;

  t[_n2][_n0] = _a;
  t[_n2][_n1] = b;
  t[_n2][_n2] = 1.0f + b;

  if ( _inverse )
  {
    t.transpose();
  }
}

std::ostream &
operator<<( std::ostream &o, TransformX const &t )
{
  math::Matrix<Real> m;
  t.to_matrix(m);
  o << m;
  return o;
}


} // namespace motion

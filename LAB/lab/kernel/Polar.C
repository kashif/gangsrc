/* GANG Software
 * LAB/lab/kernel/Polar.C
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
#include "base/vector.H"
#include "eval/Eval.H"
#include "math/Math.H"
#include "Evaluator.H"
#include "Polar.H"

namespace lab {
namespace kernel {

char const *const
Polar::Exception::
_message0[] =
{
  "",
  "Syntax error in polar domain",
  "Syntax error in polar domain: center",
  "Syntax error in polar domain: radius 1",
  "Syntax error in polar domain: radius 2",
  "Syntax error in polar domain: radius count",
  "Syntax error in polar domain: angle 1",
  "Syntax error in polar domain: angle 2",
  "Syntax error in polar domain: angle count",
  "Invalid value in polar domain: radius count",
  "Invalid value in polar domain: angle count",
  "Invalid value in polar domain: radius 1",
  "Invalid value in polar domain: radius 2",
};

Polar::
Polar( base::String const &s )
    :
    PlanarDomain(),
    _center(0),
    _radius0(0),
    _radius1(0),
    _d_radius(0),
    _angle0(0),
    _angle1(0),
    _d_angle(0),
    _exp(false)
{
  set(s);
}

Polar::
Polar(
  Complex const &center,
  Real radius0, Real radius1, uint n_radius,
  Real angle0, Real angle1, uint n_angle, bool exp )
    :
    PlanarDomain(),
    _center(0),
    _radius0(0),
    _radius1(0),
    _d_radius(0),
    _angle0(0),
    _angle1(0),
    _d_angle(0),
    _exp(false)
{
  set( center, radius0, radius1, n_radius,
       angle0, angle1, n_angle, exp );
}

Polar::
Polar( Polar const &a )
    :
    PlanarDomain(),
    _center( a._center ),
    _radius0( a._radius0 ),
    _radius1( a._radius1 ),
    _d_radius( a._d_radius ),
    _angle0( a._angle0 ),
    _angle1( a._angle1 ),
    _d_angle( a._d_angle ),
    _exp( a._exp )
{
}

Polar::
~Polar()
{
}

Polar &
Polar::
operator=( Polar const &a )
{
  if ( this == &a ) { return *this; }
  PlanarDomain::operator=(*this);
  _center = a._center;
  _radius0 = a._radius0;
  _radius1 = a._radius1;
  _d_radius = a._d_radius;
  _angle0 = a._angle0;
  _angle1 = a._angle1;
  _d_angle = a._d_angle;
  _exp = a._exp;
  return *this;
}


void
Polar::
set( Complex const &center,
     Real radius0, Real radius1, uint count0,
     Real angle0, Real angle1, uint count1, bool exp )
{
  if ( count0 < COUNT_MIN )
  { throw Exception( Exception::ERR_COUNT0_VAL ); }
  if ( count1 < COUNT_MIN )
  { throw Exception( Exception::ERR_COUNT0_VAL ); }

  if ( radius0 < 0 )
  { throw Exception( Exception::ERR_RADIUS0_VAL ); }
  if ( radius1 < 0 )
  { throw Exception( Exception::ERR_RADIUS1_VAL ); }

  _center = center;
  _radius0 = radius0;
  _radius1 = radius1;
  _angle0 = angle0;
  _angle1 = angle1;
  _count0 = count0;
  _count1 = count1;
  _exp = exp;

  _d_radius = _exp ? log(_radius1/_radius0) : _radius1 - _radius0;
  _d_radius /= Real(_count0-1);
  _d_angle = (_angle1 - _angle0)/Real(_count1-1);
}


void
Polar::
get(
  Complex &center,
  Real &radius0, Real &radius1, uint &count0,
  Real &angle0, Real &angle1, uint &count1, bool &exp ) const
{
  center = _center;
  radius0 = _radius0;
  radius1 = _radius1;
  angle0 = _angle0;
  angle1 = _angle1;
  count0 = _count0;
  count1 = _count1;
  exp = _exp;
}

Complex
Polar::
z( uint i, uint j ) const
{
  Real a = _exp ?
    _radius0 * exp( i * _d_radius ) :
    _radius0 + i * _d_radius;

  Real angle  = _angle0 + j * _d_angle;
  Complex v( math::cos(angle), math::sin(angle) );

  return _center + a * v;
}

void
Polar::
set( base::String const &s )
{
  base::vector<base::String> v;

  if ( ! base::match(
         "^[ \n\r\t]*polar(_exp)?[ \n\r\t]+(.*)$", s, v ) )
  {
    throw Exception(Exception::ERR_PARSE);
  }

  bool exp = v[1].length() > 0;

  base::vector<base::String> w;
  base::split( w, v[2], ';' );
  if ( w.size() != 7 )
  {
    throw Exception( Exception::ERR_PARSE );
  }

  Complex center;
  Real radius0, radius1;
  Real angle0, angle1;
  uint count0, count1;

  try { Evaluator::evaluator()->evaluate( center, w[0] ); }
  catch ( base::Exception const & )
  { throw Exception( Exception::ERR_CENTER ); }

  try { Evaluator::evaluator()->evaluate( radius0, w[1] ); }
  catch ( base::Exception const & )
  { throw Exception( Exception::ERR_RADIUS0 ); }

  try { Evaluator::evaluator()->evaluate( radius1, w[2] ); }
  catch ( base::Exception const & )
  { throw Exception( Exception::ERR_RADIUS1 ); }

  try { Evaluator::evaluator()->evaluate( count0, w[3] ); }
  catch ( base::Exception const & )
  { throw Exception( Exception::ERR_COUNT0 ); }

  try { Evaluator::evaluator()->evaluate( angle0, w[4] ); }
  catch ( base::Exception const & )
  { throw Exception( Exception::ERR_ANGLE0 ); }

  try { Evaluator::evaluator()->evaluate( angle1, w[5] ); }
  catch ( base::Exception const & )
  { throw Exception( Exception::ERR_ANGLE1 ); }

  try { Evaluator::evaluator()->evaluate( count1, w[6] ); }
  catch ( base::Exception const & )
  { throw Exception( Exception::ERR_COUNT1 ); }

  set( center, radius0, radius1, count0, angle0, angle1, count1, exp );

}

} // namespace kernel
} // namespace lab

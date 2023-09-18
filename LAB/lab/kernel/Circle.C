/* GANG Software
 * LAB/lab/kernel/Circle.C
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

#include "base/Regex.H"
#include "eval/Eval.H"
#include "Evaluator.H"
#include "Circle.H"

namespace lab {
namespace kernel {

char const *const
Circle::Exception::
_message0[] =
{
  "",
  "Syntax error in circle domain",
  "Syntax error in circle domain: center",
  "Syntax error in circle domain: radius",
  "Syntax error in circle domain: angle 1",
  "Syntax error in circle domain: angle 2",
  "Syntax error in circle domain: count",
  "Invalid value in circle domain: count",
  "Invalid value in circle domain: radius"
};

Circle::
Circle( base::String const &s )
{
  set(s);
}

Circle::
Circle(
  Complex const &center,
  Real radius, Real angle0, Real angle1,
  uint count )
{
  set( center, radius, angle0, angle1, count );
}

Circle::
Circle( Circle const & )
{
  DIE();
}

Circle::
~Circle()
{
}

Circle &
Circle::
operator=( const Circle & )
{
  DIE();
  return *this;
}


void
Circle::
set( Complex const &center,
     Real radius, Real angle0, Real angle1, uint count )
{
  if ( count < 2 ) { throw Exception(Exception::ERR_COUNT_VAL); }
  if (radius < 0.0) { throw Exception(Exception::ERR_RADIUS_VAL); }
  _center = center;
  _radius = radius;
  _angle0 = angle0;
  _angle1 = angle1;
  _count = count;
  _delta = (_angle1 - _angle0)/Real(_count-1);
}

void
Circle::
get( Complex &center,
     Real &radius, Real &angle0, Real &angle1,
     uint &count ) const
{
  center = _center;
  radius = _radius;
  angle0 = _angle0;
  angle1 = _angle1;
  count = _count;
}


Complex
Circle::
z( uint i ) const
{
  static Complex const I(0.0,1.0);

  // circle coordinates
  Real angle  = _angle0 + Real(i) * _delta;
  return _center + _radius * std::exp( I * angle );
}


void
Circle::
set( base::String const &s )
{
  base::vector<base::String> v;

  if ( ! base::match(
         "^[ \n\r\t]*circle[ \n\r\t]+(.*)$", s, v ) )
  {
    throw Exception(Exception::ERR_PARSE);
  }

  base::vector<base::String> w;
  base::split( w, v[1], ';' );
  if ( w.size() != 5 )
  {
    throw Exception( Exception::ERR_PARSE );
  }

  Complex center;
  Real radius;
  Real angle0, angle1;
  uint count;

  try { Evaluator::evaluator()->evaluate( center, w[0] ); }
  catch ( base::Exception const & )
  { throw Exception( Exception::ERR_CENTER ); }

  try { Evaluator::evaluator()->evaluate( radius, w[1] ); }
  catch ( base::Exception const & )
  { throw Exception( Exception::ERR_RADIUS ); }

  try { Evaluator::evaluator()->evaluate( angle0, w[2] ); }
  catch ( base::Exception const & )
  { throw Exception( Exception::ERR_ANGLE0 ); }

  try { Evaluator::evaluator()->evaluate( angle1, w[3] ); }
  catch ( base::Exception const & )
  { throw Exception( Exception::ERR_ANGLE1 ); }

  try { Evaluator::evaluator()->evaluate( count, w[4] ); }
  catch ( base::Exception const & )
  { throw Exception( Exception::ERR_COUNT ); }

  set( center, radius, angle0, angle1, count );
}

} // namespace kernel
} // namespace lab

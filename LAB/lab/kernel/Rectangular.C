/* GANG Software
 * LAB/lab/kernel/Rectangular.C
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
#include "Evaluator.H"
#include "Rectangular.H"

namespace lab {
namespace kernel {

char const *const
Rectangular::Exception::
_message0[] =
{
  "",
  "Syntax error in rectangular domain",
  "Syntax error in rectangular domain: start",
  "Syntax error in rectangular domain: corner 0",
  "Syntax error in rectangular domain: count 1",
  "Syntax error in rectangular domain: corner 2",
  "Syntax error in rectangular domain: count 2",
  "Invalid value in rectangular domain: count 1",
  "Invalid value in rectangular domain: count 2",
};

Rectangular::
Rectangular( base::String const &s )
    :
    PlanarDomain(),
    _base(0),
    _a0(0),
    _a1(0),
    _delta0(0),
    _delta1(0)
{
  set(s);
}

Rectangular::
Rectangular(
  Complex const &base,
  Complex const &a0, uint count0,
  Complex const &a1, uint count1 )
    :
    PlanarDomain(),
    _base(0),
    _a0(0),
    _a1(0),
    _delta0(0),
    _delta1(0)
{
  set( base, a0, count0, a1, count1 );
}

Rectangular::
Rectangular( Rectangular const &a )
    :
    PlanarDomain(a),
    _base(0),
    _a0(0),
    _a1(0),
    _delta0(0),
    _delta1(0)
{
}

Rectangular::
~Rectangular()
{
}

Rectangular &
Rectangular::
operator=( Rectangular const &a )
{
  if ( this == &a ) { return *this; }
  PlanarDomain::operator=(*this);
  _base = a._base;
  _a0 = a._a0;
  _a1 = a._a1;
  _delta0 = a._delta0;
  _delta1 = a._delta1;
  return *this;
}


void
Rectangular::
set(
  Complex const &base,
  Complex const &a0, uint count0,
  Complex const &a1, uint count1 )
{
  if ( count0 < COUNT_MIN )
  { throw Exception( Exception::ERR_COUNT0_VAL ); }
  if ( count1 < COUNT_MIN )
  { throw Exception( Exception::ERR_COUNT1_VAL ); }

  _base = base;
  _a0 = a0;
  _a1 = a1;
  _count0 = count0;
  _count1 = count1;
  _delta0 = (_a0 - _base)/Real(_count0-1);
  _delta1 = (_a1 - _base)/Real(_count1-1);
}

void
Rectangular::
get(
  Complex &base, Complex &a0,
  uint &count0,
  Complex &a1, uint &count1 ) const
{
  base = _base;
  a0 = _a0;
  a1 = _a1;
  count0 = _count0;
  count1 = _count1;
}


Complex
Rectangular::
z( uint i, uint j ) const
{
  // rectangular coordinates
  return _base + Real(i) * _delta0 + Real(j) * _delta1;
}

void
Rectangular::
set( base::String const &s )
{
  base::vector<base::String> v;

  if ( ! base::match(
         "^[ \n\r\t]*rectangular[ \n\r\t]+(.*)$", s, v ) )
  {
    throw Exception(Exception::ERR_PARSE);
  }

  base::vector<base::String> w;
  base::split( w, v[1], ';' );
  if ( w.size() != 5 )
  {
    throw Exception( Exception::ERR_PARSE );
  }

  Complex base, a0, a1;
  uint count0, count1;

  try { Evaluator::evaluator()->evaluate( base, w[0] ); }
  catch ( base::Exception const & )
  { throw Exception( Exception::ERR_BASE ); }

  try { Evaluator::evaluator()->evaluate( a0, w[1] ); }
  catch ( base::Exception const & )
  { throw Exception( Exception::ERR_A0 ); }

  try { Evaluator::evaluator()->evaluate( count0, w[2] ); }
  catch ( base::Exception const & )
  { throw Exception( Exception::ERR_COUNT0 ); }

  try { Evaluator::evaluator()->evaluate( a1, w[3] ); }
  catch ( base::Exception const & )
  { throw Exception( Exception::ERR_A1 ); }

  try { Evaluator::evaluator()->evaluate( count1, w[4] ); }
  catch ( base::Exception const & )
  { throw Exception( Exception::ERR_COUNT1 ); }

  set( base, a0, count0, a1, count1 );
}

} // namespace kernel
} // namespace lab

/* GANG Software
 * LAB/lab/kernel/Line.C
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
#include "Exception.H"
#include "Evaluator.H"
#include "Line.H"

namespace lab {
namespace kernel {

char const *const
Line::Exception::
_message0[] =
{
  "",
  "Syntax error in line domain",
  "Syntax error in line domain: x0",
  "Syntax error in line domain: x1",
  "Syntax error in line domain: count",
  "Invalid value in line domain: count"
};

Line::
Line( base::String const &s )
{
  set(s);
}

Line::
Line(
  Complex const &x0, Complex const &x1, uint count )
{
  set( x0, x1, count );
}

Line::
Line( Line const & )
{
  DIE();
}

Line::
~Line()
{
}

Line &
Line::
operator=( const Line & )
{
  DIE();
  return *this;
}

void
Line::
set(
  Complex const &x0,
  Complex const &x1,
  uint count )
{
  if ( count < 2 ) { throw Exception(Exception::ERR_COUNT); }
  _x0 = x0;
  _x1 = x1;
  _count = count;
  _delta = (_x1 - _x0)/Real(_count-1);
}


void
Line::
get( Complex &x0, Complex &x1,
     uint &count ) const
{
  x0 = _x0;
  x1 = _x1;
  count = _count;
}

Complex
Line::
z( uint i ) const
{
  // line coordinates
  return _x0 + Real(i) * _delta;
}

void
Line::
set( base::String const &s )
{
  base::vector<base::String> v;

  if ( ! base::match(
         "^[ \n\r\t]*line[ \n\r\t]+(.*)$", s, v ) )
  {
    throw Exception(Exception::ERR_PARSE);
  }

  base::vector<base::String> w;
  base::split( w, v[1], ';' );
  if ( w.size() != 3 )
  {
    throw Exception( Exception::ERR_PARSE );
  }

  Complex x0, x1;
  uint count;

  try { Evaluator::evaluator()->evaluate( x0, w[0] ); }
  catch ( base::Exception const & )
  { throw Exception( Exception::ERR_X0 ); }

  try { Evaluator::evaluator()->evaluate( x1, w[1] ); }
  catch ( base::Exception const & )
  { throw Exception( Exception::ERR_X1 ); }

  try { Evaluator::evaluator()->evaluate( count, w[2] ); }
  catch ( base::Exception const & )
  { throw Exception( Exception::ERR_COUNT ); }

  set( x0, x1, count );
}

} // namespace kernel
} // namespace lab

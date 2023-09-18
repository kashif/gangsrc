/* GANG Software
 * LAB/loop/EvalLoop.C
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
#include "Common.H"
#include "Parser.H"
#include "EvalLoop.H"

namespace loop {

EvalLoop::
EvalLoop()
    :
    _matrix(),
    _range(),
    _evaluator(),
    _varname(),
    _time(0),
    _time_varname()
{
}

EvalLoop::
EvalLoop( EvalLoop const &a )
    :
    _matrix(a._matrix),
    _range( a._range ),
    _evaluator( a._evaluator ),
    _varname(a._varname),
    _time(a._time),
    _time_varname(a._time_varname)
{
}

EvalLoop &
EvalLoop::
operator=( EvalLoop const &a )
{
  if ( this == &a ) { return *this; }

  _matrix = a._matrix;
  _range = a._range;
  _evaluator = a._evaluator;
  _varname = a._varname;
  _time = a._time;
  _time_varname = a._time_varname;

  return *this;
}

EvalLoop::
~EvalLoop()
{
}

void
EvalLoop::
clear_data()
{
  uint i;
  for ( i = 0; i < 2; i++ )
  {
    uint j;
    for ( j = 0; j < 2; j++ )
    {
      _matrix[i][j].deallocate();
    }
  }
}

void
EvalLoop::
set( base::String const &s, bool is_potential )
{
  // sets *this to s

  // NOTE: does not assume trace-free

  int r = 0;

  // parse s_ into stringHash
  Parser parser;

  // stringHash stores the coefficients of t=lambda
  // stringHash[0] = xi11
  // stringHash[1] = xi12
  // stringHash[2] = xi21
  // stringHash[3] = xi22
  base::ArrayX<Hash,4U> stringHash;

  // parse the string s into stringHash
  r = parser.parse(stringHash, s);

  // check for error in parse
  if ( r != 0 )
  { WARN(); throw base::Exception( "syntax error in loop evaluation"); }
  // compute _matrix
  uint i;
  for ( i = 0; i < 2; i++ )
  {
    uint j;
    for ( j = 0; j < 2; j++ )
    {
      Hash &h = stringHash[ 2*i+j ];
      ExpressionEntry &m = _matrix[i][j];

      // compute range
      if ( h.empty() )
      { WARN(); throw base::Exception( "range error in loop evaluation" ); }
      int rmin = (*h.begin()).first;
      _range[i][j].start = rmin;
      _range[i][j].count = (*h.rbegin()).first - rmin + 1;

      // check bounds in the case of a potential
      if (is_potential)
      {
        if ((i==0 && j==1 && rmin < -1) ||
            (!(i==0 && j==1) && rmin < 0))
        { WARN(); throw base::Exception( "range error in loop evaluation" ); }
      }

      // allocate _matrix
      m.deallocate();
      m.allocate(_range[i][j].count);

      // evaluate stringHash into matrix
      uint k;
      for (k = 0; k < _range[i][j].count; k++ )
      {
        _evaluate_string( m[k], h, _range[i][j].start+int(k) );
      }
    }
  }
}

void
EvalLoop::
evaluate(
  Loop4 &X,
  Complex const &z )
{
  // evaluate *this at z; put result into Loop4 xi
  X.clear();

  uint p = X.polylen();

  // compute _matrix
  uint i;
  for ( i = 0; i < 2; i++ )
  {
    uint j;
    for ( j = 0; j < 2; j++ )
    {
      uint k;
      for ( k = 0; k < _range[i][j].count; k++ )
      {
        int n = _range[i][j].start + k;
        if (n >= -int(p) && n <= int(p) )
        {
          // note indices on X are reversed
          _evaluate_expression(
            X[j][i][n], _matrix[i][j][k], z );
        }
      }
    }
  }
}

void
EvalLoop::
_evaluate_string(
 eval::Expression<Complex> &e,
 Hash const &h,
 int j )
{
  // evaluate h[j] into e

  Hash::const_iterator k = h.find(j);

  base::String const zero("0");
  base::String s = ( k == h.end() ? zero : (*k).second );

  // replace "*^" with "e" ("*^" is mathematica notation*)
  for(;;)
  {
    uint n = s.find("*^");
    if (n == (int unsigned)-1) { break; }
    s.replace(n, 2, "e");
  }

  // set e to an expression that evaluates to 0
  e.clear();
  e.create_variable( _varname );
  
  // introduce the time variable
  if ( ! _time_varname.empty() )
  {
    e.create_variable( _time_varname );
  }
  try {
    _evaluator.evaluate(e, s);
  }
  catch ( base::Exception const & )
  { throw base::Exception( "syntax error in loop evaluation"); }
}

void
EvalLoop::
_evaluate_expression(
  Complex &w,
  eval::Expression<Complex> &e,
  Complex const &z )
{
  // evaluate the expression e at z; put result into w

  e.set_variable( _varname, z );

  // set the time variable
  if ( !_time_varname.empty() )
  {
    e.set_variable( _time_varname, _time );
  }

  try {
    _evaluator.evaluate( w, e );
  }
  catch ( base::Exception const & )
  { throw base::Exception( "syntax error in loop evaluation"); }

  if ( math::isnan( w ) )
  { throw base::Exception( "nan in loop evaluation"); }
}

} // namespace loop

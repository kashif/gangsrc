/* GANG Software
 * BASE/eval/Eval.H
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

#ifndef eval_Eval_INCLUDED
#define eval_Eval_INCLUDED

#include <math.h>
#include "base/String.H"
#include "base/Exception.H"
#include "Base.H"
#include "ParseBase.H"
#include "NumberOp.H"

namespace eval {

template <class NUMBER>
void
evaluate( NUMBER &, base::String const & );

template <class NUMBER>
void
evaluate( NUMBER &, char const * );

template <class NUMBER>
void
evaluate( NUMBER &, char const *, uint );

template <class NUMBER>
void
evaluate( NUMBER &, std::istream & );

template <>
inline void
evaluate( int &n, base::String const &expr );

template <>
inline void
evaluate( uint &n, base::String const &expr );



template <class NUMBER>
class Evaluator;

template <class NUMBER>
class Expression
{
public:

  // void constructor
  Expression();

  // copy constructor
  Expression( Expression const & );

  // destructor
  ~Expression();

  // assignment operator
  Expression &operator=( Expression const & );

  //
  void create_variable( char const * );
  //
  void create_variable( base::String const & );
  //
  void set_variable( char const *, NUMBER const & );
  //
  void set_variable( base::String const &, NUMBER const & );
  //
  int get_variable( NUMBER &, char const * ) const;
  //
  void remove_variable( char const * );
  //
  void remove_variables();
  //
  void clear();

protected:
  //
  expr_base<NUMBER> _expr;

private:
  //
  friend class Evaluator<NUMBER>;
};

//
template <class NUMBER>
class Evaluator
{
public:

  // void constructor
  Evaluator();

  // copy constructor
  Evaluator( Evaluator const & );

  // destructor
  ~Evaluator();

  // assignment operator
  Evaluator &operator=( Evaluator const & );

  //
  void evaluate( NUMBER &, char const * );
  //
  void evaluate( NUMBER &, char const *, uint );
  //
  void evaluate( NUMBER &, std::istream & );
  //
  void evaluate( NUMBER &, base::String const & );

  //
  void evaluate( Expression<NUMBER> &, char const * );
  //
  void evaluate( Expression<NUMBER> &, char const *, uint );
  //
  void evaluate( Expression<NUMBER> &, std::istream & );
  //
  void evaluate( Expression<NUMBER> &, base::String const & );

  //
  void evaluate( NUMBER &, Expression<NUMBER> const &);

protected:
  //
  ParseBase<NUMBER, number_op<NUMBER> > _parser;
  //
  eval_base<NUMBER, number_op<NUMBER> > _evaluator;

private:
};


// Expression methods

template <class NUMBER>
Expression<NUMBER>::
Expression()
    :
    _expr()
{
}

template <class NUMBER>
Expression<NUMBER>::
Expression( Expression const &a )
    :
    _expr(a._expr)
{
}

template <class NUMBER>
Expression<NUMBER>::
~Expression()
{
}

template <class NUMBER>
Expression<NUMBER> &
Expression<NUMBER>::
operator=( Expression const &a )
{
  if ( this != &a )
  {
    _expr = a._expr;
  }
  return *this;
}

template <class NUMBER>
void
Expression<NUMBER>::
create_variable( char const *s )
{
  _expr.create_variable( s );
}

template <class NUMBER>
void
Expression<NUMBER>::
create_variable( base::String const &s )
{
  _expr.create_variable( s );
}

template <class NUMBER>
void
Expression<NUMBER>::
set_variable( char const *c, NUMBER const &x )
{
  _expr.set_variable( c, x );
}

template <class NUMBER>
void
Expression<NUMBER>::
set_variable( base::String const &s, NUMBER const &x )
{
  _expr.set_variable( s, x );
}

template <class NUMBER>
int
Expression<NUMBER>::
get_variable( NUMBER &x, char const *c ) const
{
  return _expr.get_variable( x, c );
}

template <class NUMBER>
void
Expression<NUMBER>::
remove_variable( char const *s )
{
  _expr.remove_variable( s );
}

template <class NUMBER>
void
Expression<NUMBER>::
remove_variables()
{
  _expr.remove_variables();
}

template <class NUMBER>
void
Expression<NUMBER>::
clear()
{
  _expr.clear();
}


// evaluate

template <class NUMBER>
void
evaluate( NUMBER &x, base::String const &s )
{
  try
  {
    x = NUMBER(0.0);
    expr_base<NUMBER> e;
    ParseBase<NUMBER, number_op<NUMBER> > P;
    P.parse( e, s );
    eval_base<NUMBER, number_op<NUMBER> > E;
    E.evaluate( x, e );
  }
  catch( ... )
  {
    throw base::Exception( "eval syntax error" );
  }
}

template <class NUMBER>
void
evaluate( NUMBER &x, char const *c )
{
  x = NUMBER(0.0);
  expr_base<NUMBER> e;
  ParseBase<NUMBER, number_op<NUMBER> > P;
  P.parse( e, c );
  eval_base<NUMBER, number_op<NUMBER> > E;
  E.evaluate( x, e );
}

template <class NUMBER>
void
evaluate( NUMBER &x, char const *c, uint n )
{
  x = NUMBER(0.0);
  expr_base<NUMBER> e;
  ParseBase<NUMBER, number_op<NUMBER> > P;
  P.parse( e, c, n );
  eval_base<NUMBER, number_op<NUMBER> > E;
  E.evaluate( x, e );
}

template <class NUMBER>
void
evaluate( NUMBER &x, std::istream &i )
{
  x = NUMBER(0.0);
  expr_base<NUMBER> e;
  ParseBase<NUMBER, number_op<NUMBER> > P;
  P.parse( e, i );
  eval_base<NUMBER, number_op<NUMBER> > E;
  E.evaluate( x, e );
}

template <>
inline void
evaluate( int &n, base::String const &expr )
{
  double x;
  evaluate( x, expr );
  if ( floor(x) != x ) 
  { throw base::Exception("eval error"); }
  n = int(x);
}

template <>
inline void
evaluate( uint &n, base::String const &expr )
{
  double x;
  evaluate( x, expr );
  if ( x < 0.0 || floor(x) != x )
  { throw base::Exception("eval error"); }
  n = int(x);
}


// Evaluator methods

template <class NUMBER>
Evaluator<NUMBER>::
Evaluator()
    :
    _parser(),
    _evaluator()
{
}

template <class NUMBER>
Evaluator<NUMBER>::
Evaluator( Evaluator const &a )
    :
    _parser(a._parser),
    _evaluator(a._evaluator)
{
}

template <class NUMBER>
Evaluator<NUMBER>::
~Evaluator()
{
}

template <class NUMBER>
Evaluator<NUMBER> &
Evaluator<NUMBER>::
operator=( const Evaluator &a )
{
  if ( this != &a )
  {
    _parser = a._parser;
    _evaluator = a._evaluator;
  }
  return *this;
}

template <class NUMBER>
void
Evaluator<NUMBER>::
evaluate( NUMBER &x, char const *c )
{
  x = NUMBER(0.0);
  expr_base<NUMBER> e;
  _parser.parse( e, c );
  _evaluator.evaluate( x, e );
}

template <class NUMBER>
void
Evaluator<NUMBER>::
evaluate( NUMBER &x, char const *c, uint n )
{
  x = NUMBER(0.0);
  expr_base<NUMBER> e;
  _parser.parse( e, c, n );
  _evaluator.evaluate( x, e );
}

template <class NUMBER>
void
Evaluator<NUMBER>::
evaluate( NUMBER &x, std::istream &i )
{
  x = NUMBER(0.0);
  expr_base<NUMBER> e;
  _parser.parse( e, i );
  _evaluator.evaluate( x, e );
}

template <class NUMBER>
void
Evaluator<NUMBER>::
evaluate( NUMBER &x, base::String const &s )
{
  x = NUMBER(0.0);
  expr_base<NUMBER> e;
  _parser.parse( e, s );
  _evaluator.evaluate( x, e );
}

template <class NUMBER>
void
Evaluator<NUMBER>::
evaluate( Expression<NUMBER> &e, char const *c )
{
  _parser.parse( e._expr, c );
}

template <class NUMBER>
void
Evaluator<NUMBER>::
evaluate( Expression<NUMBER> &e, char const *c, uint n )
{
  _parser.parse( e._expr, c, n );
}

template <class NUMBER>
void
Evaluator<NUMBER>::
evaluate( Expression<NUMBER> &e, std::istream &i )
{
  _parser.parse( e._expr, i );
}

template <class NUMBER>
void
Evaluator<NUMBER>::
evaluate( Expression<NUMBER> &e, base::String const &s )
{
  _parser.parse( e._expr, s );
}

template <class NUMBER>
void
Evaluator<NUMBER>::
evaluate( NUMBER &x, Expression<NUMBER> const &e )
{
  x = NUMBER(0.0);
  _evaluator.evaluate( x, e._expr );
}

} // namespace eval

#endif // eval_Eval_INCLUDED

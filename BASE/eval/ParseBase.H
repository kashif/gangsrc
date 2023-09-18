/* GANG Software
 * BASE/eval/ParseBase.H
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

#ifndef eval_ParseBase_INCLUDED
#define eval_ParseBase_INCLUDED

#include <iostream>
#include <strstream>
#include "base/vector.H"
#include "io/IstreamStream.H"
#include "Node.H"
#include "ExprBase.H"
#include "Parser.H"


#if !defined(DISABLE_EVAL_NAMESPACE)
namespace eval {
#endif

/*
  Parses an expression in two passes.
  Pass 1 runs a yacc parser on a base::String, creating a tree.
  Pass 2 vectorizes the tree, creating an rpn-style vector.
*/

template <class TYPE, class TYPE_OP>
class ParseBase
{

public:

  // void constructor
  ParseBase();

  // copy constructor
  ParseBase( ParseBase const & );

  // destructor
  ~ParseBase();

  // assignment operator
  ParseBase &operator=( ParseBase const & );

  void parse( expr_base<TYPE> &, base::String const & );
  void parse( expr_base<TYPE> &, char const * );
  void parse( expr_base<TYPE> &, char const *, uint );
  void parse( expr_base<TYPE> &, std::istream & );

protected:

  void vectorize( expr_base<TYPE> &, EvalNode const * );

private:

  char const *unary_op_name(uint i) const;
  char const *binary_op_name(uint i) const;

  Parser _parser;
};

template <class TYPE, class TYPE_OP>
char const *
ParseBase<TYPE, TYPE_OP>::
unary_op_name(uint i) const
{
  static char const *const v[] = { "pos", "neg" };
  DIE_IF(i < SY_pos || i - SY_pos >= 2 );
  return v[i - SY_pos];
}

template <class TYPE, class TYPE_OP>
char const *
ParseBase<TYPE, TYPE_OP>::
binary_op_name(uint i) const
{
  static char const *const v[] = { "add", "sub", "mul", "div", "pow" };
  DIE_IF(i < SY_add || i - SY_add >= 5 );
  return v[i - SY_add];
}

template <class TYPE, class TYPE_OP>
ParseBase<TYPE, TYPE_OP>::
ParseBase()
{
  _parser._stream = (::io::Istream *)0;
}

template <class TYPE, class TYPE_OP>
ParseBase<TYPE, TYPE_OP>::
ParseBase( ParseBase<TYPE, TYPE_OP> const & )
{
  // ParseBase has no data
}

template <class TYPE, class TYPE_OP>
ParseBase<TYPE, TYPE_OP>::
~ParseBase()
{
}

template <class TYPE, class TYPE_OP>
ParseBase<TYPE, TYPE_OP> &
ParseBase<TYPE, TYPE_OP>::
operator=( const ParseBase<TYPE, TYPE_OP> & )
{
  return *this;
}

template <class TYPE, class TYPE_OP>
void
ParseBase<TYPE, TYPE_OP>::
parse( expr_base<TYPE> &e, std::istream &i )
{ 
  e.clear();

  ::io::IstreamStream stream(i);
  _parser._stream = &stream;

  // parse
  try { _parser.parsex(); }
  catch (base::Exception const &)
  { EvalNode::destruct( _parser.parser_node_p ); throw; }

  EvalNode *n = _parser.parser_node_p;
  DIE_IF( n == (EvalNode *)0 );
  // EvalNode::dump(std::cerr, n);

  // vectorize
  try { vectorize(e, n); }
  catch (base::Exception const &)
  { EvalNode::destruct( n ); throw; }

  // e.dump( std::cerr );
  EvalNode::destruct( n );
}

template <class TYPE, class TYPE_OP>
void
ParseBase<TYPE, TYPE_OP>::
parse( expr_base<TYPE> &e, char const *s )
{
  std::strstream ss;
  ss << s;
  parse( e, ss );
}

template <class TYPE, class TYPE_OP>
void
ParseBase<TYPE, TYPE_OP>::
parse( expr_base<TYPE> &e, char const *s, uint m )
{
  std::strstream ss;
  ss.write(s, m);
  parse( e, ss );
}

template <class TYPE, class TYPE_OP>
void
ParseBase<TYPE, TYPE_OP>::
parse( expr_base<TYPE> &e, base::String const &s )
{
  std::strstream ss;
  ss << s;
  parse( e, ss );
}

template <class TYPE, class TYPE_OP>
void
ParseBase<TYPE, TYPE_OP>::
vectorize( expr_base<TYPE> &e, EvalNode const *n )
{
  if ( n == (EvalNode *)0 ) { return; }

  vectorize( e, n->left );
  vectorize( e, n->right );

  expr_base<TYPE>::element x;

  if ( n->_token_type == TT_number )
  {
    x._type = expr_base<TYPE>::OBJECT;
    TYPE_OP::from_string( x._x, n->_string);
  }
  else if ( n->_token_type == TT_identifier )
  {
    x._type = expr_base<TYPE>::IDENTIFIER;
    x._fn_argcount = 0;
    int k = e.get_variable_key( n->_string.data(), n->_string.length() );
    if ( k < 0 )
    {
      // interpret as a constant (function with 0 arguments)
      x._type = expr_base<TYPE>::FUNCTION;
      k = TYPE_OP::lookup_function(n->_string.data(),
                                   n->_string.length(), 0);
      if ( k < 0 ) { throw base::Exception( "eval: vectorize" ); }
      x._id = k;
    }
    else
    {
      x._id = k;
    }
  }
  else if ( n->_token_type == TT_unary_op )
  {
    x._type = expr_base<TYPE>::FUNCTION;
    x._fn_argcount = 1;
    char const *c = unary_op_name(n->_token);
    int k = TYPE_OP::lookup_function( c, strlen(c), 1);
    if ( k < 0 ) { throw base::Exception( "eval: vectorize" ); }
    x._id = k;
  }
  else if ( n->_token_type == TT_binary_op )
  {
    x._type = expr_base<TYPE>::FUNCTION;
    x._fn_argcount = 2;
    char const *c = binary_op_name(n->_token);
    int k = TYPE_OP::lookup_function( c, strlen(c), 2);
    if ( k < 0 ) { throw base::Exception( "eval: vectorize" ); }
    x._id = k;
  }
  else if ( n->_token_type == TT_unary_fn )
  {
    x._type = expr_base<TYPE>::FUNCTION;
    x._fn_argcount = 1;
    int k =
      TYPE_OP::lookup_function( n->_string.data(), n->_string.length(), 1);
    if ( k < 0 ) { throw base::Exception( "eval: vectorize" ); }
    x._id = k;
  }
  else if ( n->_token_type == TT_binary_fn )
  {
    x._type = expr_base<TYPE>::FUNCTION;
    x._fn_argcount = 2;
    int k =
      TYPE_OP::lookup_function( n->_string.data(), n->_string.length(), 2);
    if ( k < 0 ) { throw base::Exception( "eval: vectorize" ); }
    x._id = k;
  }

  e._data.push_back(x);
}

#if !defined(DISABLE_EVAL_NAMESPACE)
} // namespace eval
#endif

#endif // eval_ParseBase_INCLUDED

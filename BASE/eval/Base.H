/* GANG Software
 * BASE/eval/Base.H
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

#ifndef eval_Base_INCLUDED
#define eval_Base_INCLUDED

#include "base/vector.H"
#include "base/Stl.H"
#include "ExprBase.H"

#if !defined(DISABLE_EVAL_NAMESPACE)
namespace eval {
#endif

//
uint const EVAL_STACK_RESERVE = 4;

//
template <class TYPE, class TYPE_OP>
class eval_base
{

public:

  // void constructor
  eval_base();

  // copy constructor
  eval_base( eval_base const & );

  // destructor
  ~eval_base();

  // assignment operator
  eval_base &operator=( eval_base const & );

  //
  int evaluate( TYPE &, expr_base<TYPE> const & );
//  int set_variable( char const *, TYPE const & );
//  int get_variable( TYPE &, char const * );

protected:
  base::vector<TYPE> _stack;
private:
};



//
template <class TYPE, class TYPE_OP>
eval_base<TYPE, TYPE_OP>::
eval_base()
    :
//    _varlist(),
    _stack()
{
//  _stack.reserve(EVAL_STACK_RESERVE);
}

template <class TYPE, class TYPE_OP>
eval_base<TYPE, TYPE_OP>::
eval_base( eval_base const &a )
    :
//    _varlist(a._varlist),
    _stack(a._stack)
{
  DIE_IF(a._stack.size() != 0 );
}

template <class TYPE, class TYPE_OP>
eval_base<TYPE, TYPE_OP>::
~eval_base()
{
}

template <class TYPE, class TYPE_OP>
eval_base<TYPE, TYPE_OP> &
eval_base<TYPE, TYPE_OP>::
operator=( eval_base<TYPE, TYPE_OP> const &a )
{
  if ( this != &a )
  {
    // _varlist = a._varlist;
    _stack = a._stack;
    DIE_IF(a._stack.size() != 0 );
  }
  return *this;
}


template <class TYPE, class TYPE_OP>
int
eval_base<TYPE, TYPE_OP>::
evaluate( TYPE &x, expr_base<TYPE> const &e )
{
  uint i;
  TYPE t;
  int err = 0;

  size_t size = e._data.size();
  for ( i = 0; i < size; i++ )
  {
    expr_base<TYPE>::element const &v = e._data[i];

    if ( v._type == expr_base<TYPE>::OBJECT )
    {
      _stack.push_back( v._x );
    }
    else if ( v._type == expr_base<TYPE>::IDENTIFIER )
    {
      err = e.get_variable( t, v._id );
      if ( err != 0 ) { break; }
      _stack.push_back( t );
    }
    else if ( v._type == expr_base<TYPE>::FUNCTION )
    {
      if ( v._fn_argcount == 0 )
      {
        TYPE r;
        TYPE_OP::apply_function(
          r,
          v._id,
          (TYPE *)0,
          0 );
        if ( err != 0 ) { break; }
        _stack.push_back(r);
      }
      else
      {
        // note place of result is same as one of args
        TYPE_OP::apply_function(
          _stack[_stack.size()-v._fn_argcount],
          v._id,
          &_stack[_stack.size()-v._fn_argcount],
          v._fn_argcount );
        if ( err != 0 ) { break; }
        uint i;
        for ( i = 0; i < v._fn_argcount - 1; i++ )
        {
          // make this more efficient
          _stack.pop_back();
        }
      }
    }
    else
    {
      DIE();
    }

  }

  if ( err == 0 && _stack.size() == 1 )
  {
    x = _stack.back();
  }
  else
  {
    err = 1;
  }
  _stack.clear();

  return err;
}


#if !defined(DISABLE_EVAL_NAMESPACE)
} // namespace eval
#endif

#endif // eval_Base_INCLUDED

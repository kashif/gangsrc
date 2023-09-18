/* GANG Software
 * BASE/eval/NumberOp.H
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

#ifndef eval_NumberOp_INCLUDED
#define eval_NumberOp_INCLUDED

#include <ctype.h>


#if !defined(DISABLE_EVAL_NAMESPACE)
namespace eval {
#endif

template <class TYPE>
class number_op
{

public:
#if 0
  // void constructor
  number_op() {}

  // destructor
  ~number_op() {}
#endif

  static int evaluate_identifier(TYPE &, base::String const &);
  static int lookup_function( char const *name, size_t len,
                              uint arg_count );
  static int apply_function( TYPE &r, int function_id, TYPE *arg,
                             uint arg_count );

  static void from_string( TYPE &x, base::String const & );
  static void to_string( base::String &, TYPE const & );

  typedef void (*function0_t)( TYPE & );
protected:
  typedef void (*function1_t)( TYPE &, TYPE const & );
  typedef void (*function2_t)( TYPE &, TYPE const &, TYPE const & );

  struct function0x_t { function0_t func; char const *name; };
  struct function1x_t { function1_t func; char const *name; };
  struct function2x_t { function2_t func; char const *name; };

  static function0x_t const function0[];
  static function1x_t const function1[];
  static function2x_t const function2[];

  enum fn_id
  {
    FN_ID_POS=1, FN_ID_NEG,
    FN_ID_ADD, FN_ID_SUB, FN_ID_MUL, FN_ID_DIV, FN_ID_POW, FN_ID_COS
  };

};

template <class A>
int
lookup( char const *name, size_t len, A const *v )
{
  uint i, j;
  for ( i = 0;  (void *)v[i].func != (void *)0;  i++ )
  {
    if ( len == strlen(v[i].name) )
    {
      for ( j = 0; j < len; j++ )
      {
        if ( tolower(name[j]) != tolower(v[i].name[j]) ) { break; }
      }
      if ( j == len ) { break; }
    }
  }
  return ( (void *)v[i].func == (void *)0 ? -1 : int(i) );
}


template <class TYPE>
int
number_op<TYPE>::
evaluate_identifier( TYPE &, base::String const &s )
{
  USE(s);
  DIE();
  return 0;
}


template <class TYPE>
int
number_op<TYPE>::
lookup_function( char const *name, size_t len, uint argcount )
{
  int r = -1;
  if (argcount==0)
  {
    r = lookup( name, len, &function0[0] );
  }
  else if (argcount==1)
  {
    r = lookup( name, len, &function1[0] );
  }
  else if (argcount==2)
  {
    r = lookup( name, len, &function2[0] );
  }
  else
  {
    r = -1;
  }
  return r;
}

template <class TYPE>
int
number_op<TYPE>::
apply_function( TYPE &r, int id, TYPE *arg, uint arg_count )
{
  int err = 0;
  if (arg_count==0)
  {
    (*function0[id].func)( r );
  }
  else if (arg_count==1)
  {
    (*function1[id].func)( r, arg[0] );
  }
  else if (arg_count==2)
  {
    (*function2[id].func)( r, arg[0], arg[1] );
  }
  else
  {
    err = 1;
  }
  return err;
}


#if !defined(DISABLE_EVAL_NAMESPACE)
} // namespace eval
#endif

#endif // eval_NumberOp_INCLUDED

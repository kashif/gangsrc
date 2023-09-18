/* GANG Software
 * BASE/eval/Types.H
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

#ifndef eval_Types_INCLUDED
#define eval_Types_INCLUDED


#if !defined(DISABLE_EVAL_NAMESPACE)
namespace eval {
#endif

enum token_types
{
  TT_nothing,
  TT_number,
  TT_identifier,
  TT_unary_op,
  TT_binary_op,
  TT_unary_fn,
  TT_binary_fn
};

enum tokens
{
  SY_nothing,
  SY_enclose,
  SY_comma,
  SY_pos,
  SY_neg,
  SY_add,
  SY_sub,
  SY_mul,
  SY_div,
  SY_pow,
  SY_mod
};


#if !defined(DISABLE_EVAL_NAMESPACE)
} // namespace eval
#endif

#endif // eval_Types_INCLUDED

/* GANG Software
 * BASE/eval/Node.H
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

#ifndef eval_Node_INCLUDED
#define eval_Node_INCLUDED

#include "base/String.H"
#include "Types.H"


#if !defined(DISABLE_EVAL_NAMESPACE)
namespace eval {
#endif

class EvalNode
{

public:
  //
  EvalNode *left;
  //
  EvalNode *right;

  //
  token_types _token_type;
  //
  tokens _token;
  //
  base::String _string;

  // constructor
  inline EvalNode(token_types, tokens, EvalNode *, EvalNode *);

  // constructor
  inline EvalNode(token_types, tokens, base::String const &);

  // constructor
  inline EvalNode(token_types, tokens, base::String const &, EvalNode *,
                  EvalNode *);

  // destructor
  inline ~EvalNode();

  //
  static void destruct(EvalNode *);
  //
  static void dump(std::ostream &, EvalNode const *);
private:
  //
  static void dump(std::ostream &, EvalNode const *, uint level);
  //
  EvalNode( EvalNode const & ) { DIE(); }
  //
  EvalNode &operator=(EvalNode const &) { DIE(); return *this; }
};


EvalNode::
EvalNode(token_types t, tokens u, EvalNode *a, EvalNode *b):
  left(a),
  right(b),
  _token_type(t),
  _token(u),
  _string()
{
}

EvalNode::
EvalNode(token_types t, tokens u, base::String const &s):
  left( (EvalNode *)0 ),
  right( (EvalNode *)0),
  _token_type(t),
  _token(u),
  _string(s)
{
}

EvalNode::
EvalNode(token_types t, tokens u, base::String const &s, EvalNode *a, EvalNode *b):
  left(a),
  right(b),
  _token_type(t),
  _token(u),
  _string(s)
{
}

EvalNode::
~EvalNode()
{
}


#if !defined(DISABLE_EVAL_NAMESPACE)
} // namespace eval
#endif

#endif // eval_Node_INCLUDED

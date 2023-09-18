/* GANG Software
 * BASE/eval/Node.C
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

#include <iostream>

#include "Node.H"


#if !defined(DISABLE_EVAL_NAMESPACE)
namespace eval {
#endif

void EvalNode::
destruct(EvalNode *n)
{
  if ( n != (EvalNode *)0 )
  {
    destruct(n->left);
    destruct(n->right);
    delete(n);
  }
}

void
EvalNode::
dump(std::ostream &o, EvalNode const *n)
{
  o << "_______________________________________\n";
  dump(o, n, 0);
  o << "_______________________________________\n";
}

void
EvalNode::
dump(std::ostream &o, EvalNode const *n, uint level)
{
  if ( n != (EvalNode *)0 )
  {
    uint i;
    for (i = 0; i < level; i++) { o << "  "; }
    o << "/" << n->_string << "/\n";
    o << (void *)n << std::endl;

    level++;
    dump(o, n->left, level);
    dump(o, n->right, level);
  }
}


#if !defined(DISABLE_EVAL_NAMESPACE)
} // namespace eval
#endif

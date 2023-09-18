/* GANG Software
 * BASE/base/ListX.H
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

#ifndef base_ListX_INCLUDED
#define base_ListX_INCLUDED

#include "System.H"

namespace base {

/*
   Node for ListX container class -- see ListX
 */
template <class A>
class ListXNode
{
public:
  //
  ListXNode( A const & );

  //
  ListXNode<A> *&prev() { return _prev; };
  //
  ListXNode<A> *&next() { return _next; };

  //
  A &data() { return _data; }
  //
  A const &data() const { return _data; }

  //
  static void link( ListXNode<A> *a, ListXNode<A> *b );

private:
  //
  A _data;
  //
  ListXNode<A> *_prev, *_next;
};


/*
   List container class
 */
template <class A>
class ListX
{

public:

  // void constructor
  ListX();

  // shallow copy
  ListX( ListX const & );

  // shallow destruct
  virtual ~ListX();

  // shallow copy
  ListX &operator=( ListX const & );

  //
  void link_to_top( ListXNode<A> * );
  //
  void link_to_bot( ListXNode<A> * );

  //
  void link_to_top( ListX<A> & );
  //
  void link_to_bot( ListX<A> & );

  //
  void unlink( ListXNode<A> * );

  //
  ListXNode<A> *pop_top();
  //
  ListXNode<A> *pop_bot();

  //
  ListXNode<A> *&top() { return _top; };
  //
  ListXNode<A> *const &top() const { return _top; };

  //
  ListXNode<A> *&bot() { return _bot; };

  //
  ListXNode<A> *const &bot() const { return _bot; };

  //
  void link_after( ListXNode<A> *i, ListXNode<A> *marker );

  //
  void link_before( ListXNode<A> *i, ListXNode<A> *marker );

protected:

private:
  //
  ListXNode<A> *_top;

  //
  ListXNode<A> *_bot;
};


template <class A>
ListXNode<A>::
ListXNode( A const &a )
    :
    _data( a ),
    _prev( (ListXNode *)0 ),
    _next( (ListXNode *)0 )
{
}


template <class A>
ListX<A>::
ListX()
    :
    _top( (ListXNode<A> *)0 ),
    _bot( (ListXNode<A> *)0 )
{
}

template <class A>
ListX<A>::
ListX( ListX const &a )
    :
    _top( a._top ),
    _bot( a._bot )
{
}


template <class A>
ListX<A>::
~ListX()
{
}


template <class A>
ListX<A> &ListX<A>::
operator=( const ListX &a )
{
  if ( this != &a )
  {
    _top = a._top;
    _bot = a._bot;
  }
  return *this;
}


template <class A>
void
ListX<A>::
link_to_top( ListXNode<A> *a )
{
  ListXNode<A>::link( a, _top );
  ListXNode<A>::link( (ListXNode<A> *)0, a );
  _top = a;
  if ( _bot == (ListXNode<A> *)0 )
  {
    _bot = a;
  }
}


template <class A>
void
ListX<A>::
link_to_bot( ListXNode<A> *a )
{
  ListXNode<A>::link( _bot, a );
  ListXNode<A>::link( a, (ListXNode<A> *)0 );
  _bot = a;
  if ( _top == (ListXNode<A> *)0 )
  {
    _top = a;
  }
}


template <class A>
void
ListX<A>::
link_to_top( ListX<A> &a )
{

  if ( a._top != (ListXNode<A> *)0 )
  {
    ListXNode<A>::link( a._bot, _top );
    ListXNode<A>::link( (ListXNode<A> *)0, a._top );
    _top = a._top;
    a._top = (ListXNode<A> *)0;
    a._bot = (ListXNode<A> *)0;
  }
}


template <class A>
void
ListX<A>::
link_to_bot( ListX<A> &a )
{
  if ( a._top != (ListXNode<A> *)0 )
  {
    ListXNode<A>::link( _bot, a._top );
    ListXNode<A>::link( a._bot, (ListXNode<A> *)0 );
    _bot = a._bot;
    a._top = (ListXNode<A> *)0;
    a._bot = (ListXNode<A> *)0;
  }
}


template <class A>
ListXNode<A> *
ListX<A>::
pop_top()
{
  DIE_IF( _top == (ListXNode<A> *)0 );
  ListXNode<A> *tmp = _top;
  _top = _top->next();
  tmp->next() = ( ListXNode<A> *)0;
  return tmp;
}


template <class A>
ListXNode<A> *
ListX<A>::
pop_bot()
{
  DIE_IF( _bot == (ListXNode<A> *)0 );
  ListXNode<A> *tmp = _bot;
  _bot = _bot->prev();
  tmp->prev() = ( ListXNode<A> *)0;
  return tmp;
}


template <class A>
void
ListX<A>::
unlink( ListXNode<A> *a )
{
  DIE_IF( !a );
  DIE_IF( _top == (ListXNode<A> *)0 && _bot == (ListXNode<A> *)0 );

  if ( _top == a )
  {
    _top = a->next();
  }
  if ( _bot == a )
  {
    _bot = a->prev();
  }

  ListXNode<A>::link( a->prev(), a->next() );

  a->prev() = (ListXNode<A> *)0;
  a->next() = (ListXNode<A> *)0;
}


template <class A>
void
ListXNode<A>::
link( ListXNode<A> *a, ListXNode<A> *b )
{
  if ( a != (ListXNode<A> *)0 )
  { a->next() = b; }
  if ( b != (ListXNode<A> *)0 )
  { b->prev() = a; }
}


template <class A>
void
ListX<A>::
link_after( ListXNode<A> *i, ListXNode<A> *marker )
{
  // link i after marker
  if ( marker == (ListXNode<A> *)0 )
  {
    link_to_top( i );
  }
  else if ( marker == _bot )
  {
    link_to_bot( i );
  }
  else
  {
    ListXNode<A> *tmp = marker->next();
    ListXNode<A>::link( marker, i );
    ListXNode<A>::link( i, tmp );
  }
}


template <class A>
void
ListX<A>::
link_before( ListXNode<A> *i, ListXNode<A> *marker )
{
  // link i before marker
  if ( marker == (ListXNode<A> *)0 )
  {
    link_to_bot( i );
  }
  else if ( marker == _top )
  {
    link_to_top( i );
  }
  else
  {
    ListXNode<A> *tmp = marker->prev();
    ListXNode<A>::link( i, marker );
    ListXNode<A>::link( tmp, i );
  }
}

} // namespace base

#endif // base_ListX_INCLUDED

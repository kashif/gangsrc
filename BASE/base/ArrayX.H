/* GANG Software
 * BASE/base/ArrayX.H
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

#ifndef base_ArrayX_INCLUDED
#define base_ArrayX_INCLUDED

#include <stdlib.h>
#include <iostream>
#include "System.H"

namespace base {

#if !defined(NO_TMPL_FRIENDS)
#if (defined(__sgi) && _COMPILER_VERSION >= 730) || defined(__GNUG__)
#define NULL_TMPL_ARGS <>
#else
#define NULL_TMPL_ARGS
#endif

template <class A, int unsigned N>
class ArrayX;

template <class A, int unsigned N>
::std::ostream &operator<<( ::std::ostream &, ArrayX<A,N> const & );
#endif

/*
  Fixed-length one-dimensional array template class that optionally
  does bounds checking.

  Space is allocated/deallocated with explicit calls to methods
  allocate()/deallocate()
*/

template <class A, int unsigned N>
class ArrayX
{

public:

  // void constructor
  ArrayX();

  // copy constructor
  ArrayX( ArrayX const &a );

  // copy constructor
  ArrayX( A const *a );

  // destructor
  virtual inline ~ArrayX();

  // assignment operators
  ArrayX &operator=( ArrayX const &a );

  // assignment operators
  ArrayX &operator=( A const *a );

  // return reference to nth entry
  A &operator[]( int unsigned n );

  // return reference to nth entry
  A const &operator[]( int unsigned n ) const;

  // set all entries of *this to 0
  void clear();

  // set all entries of *this to a
  void set( A const &a );

  // write array 'a' to stream 'o'
#if !defined(NO_TMPL_FRIENDS)
  friend std::ostream &operator<< NULL_TMPL_ARGS
  ( std::ostream &o, ArrayX<A,N> const &a );
#endif

#if 0
  int unsigned size() const { return N; }
#endif

  A *data() { return _; }
  A const *data() const { return _; }
protected:
  A _[N];
};


// constructors

template <class A, int unsigned N>
inline
ArrayX<A, N>::
ArrayX()
    :
    _()
{
}

template <class A, int unsigned N>
inline
ArrayX<A, N>::
ArrayX( ArrayX<A, N> const &a )
    :
    _()
{
  int unsigned i;
  for( i = 0; i < N; i++ )
  {
    _[i] = a._[i];
  }
}

template <class A, int unsigned N>
inline
ArrayX<A, N>::
ArrayX( A const *a )
    :
    _()
{
  int unsigned i;
  for( i = 0; i < N; i++ )
  {
    _[i] = a[i];
  }
}

// assignment operator

template <class A, int unsigned N>
ArrayX<A, N> &
ArrayX<A, N>::
operator=( ArrayX<A, N> const &a )
{
  if ( this != &a )
  {
    int unsigned i;
    for( i = 0; i < N; i++ )
    {
      _[i] = a._[i];
    }
  }
  return *this;
}


// assignment operator

template <class A, int unsigned N>
ArrayX<A, N> &
ArrayX<A, N>::
operator=( A const *a )
{
  if ( _ != a )
  {
    int unsigned i;
    for( i = 0; i < N; i++ )
    {
      _[i] = a[i];
    }
  }
  return *this;
}

// destructor

template <class A, int unsigned N>
inline
ArrayX<A, N>::
~ArrayX()
{
}


// returns reference to nth entry

template <class A, int unsigned N>
inline
A &
ArrayX<A, N>::
operator[]( int unsigned n )
{
  DIE_IF( n >= N );
  return _[n];
}


// returns reference to nth entry

template <class A, int unsigned N>
inline
A const &
ArrayX<A, N>::
operator[]( int unsigned n ) const
{
  DIE_IF( n >= N );
  return _[n];
}

template <class A, int unsigned N>
void
ArrayX<A, N>::
clear()
{
  int unsigned i;
  for( i = 0; i < N; i++ )
  {
    _[i] = 0;
  }
}

// set all entries of *this to a

template <class A, int unsigned N>
void
ArrayX<A, N>::
set( A const &a )
{
  int unsigned i;
  for( i = 0; i < N; i++ )
  {
    _[i] = a;
  }
}

#if !defined(NO_TMPL_FRIENDS)
// write a to stream o
template <class A, int unsigned N>
inline
std::ostream &
operator<<( std::ostream &o, ArrayX<A, N> const &a )
{
  int unsigned i;

  o << "{ ";
  for( i = 0; i < N; i++ )
  {
    o << a._[i];
    if( i < N - 1 )
    {
      o << ", ";
    }
  }
  o << "}";
  return o;
}
#endif

} // namespace base

#if defined(__sgi) && !defined(__GNUG__)
#pragma reset woff 1375 // The destructor for class is not virtual.
#endif

#endif // base_ArrayX_INCLUDED

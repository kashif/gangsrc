/* GANG Software
 * BASE/base/Array.H
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

#ifndef base_Array_INCLUDED
#define base_Array_INCLUDED

#include "System.H"

namespace base {

/*
  Variable-size one-dimensional array template class

  Space is allocated/deallocated with explicit calls to methods
  allocate()/deallocate()
*/

template <class A>
class Array
{

public:
  // void constructor
  inline Array();

  inline Array( A const *data, int len );

  // copy constructor
  inline Array(Array<A> const &);

  // destructor
  inline ~Array();

  // assignment operator
  inline Array<A> &operator=( Array<A> const & );
  inline Array<A> &operator=( A const * );

  inline void export_( A * ) const;

  inline void allocate(uint);
  inline void deallocate();

  inline A const &operator[](uint i) const
    { DIE_IF(i >= _len); return _data[i]; }
  inline A &operator[](uint i)
    { DIE_IF(i >= _len); return _data[i]; }

  inline A *data()
    { return _data; }
  inline A const *data() const
    { return _data; }

  inline uint length() const
    { return _len; }
  inline uint size() const
    { return _len; }

  inline void set( A const & );

protected:
  A *_data;
  uint _len;
};


// constructor
template <class A>
Array<A>::
Array()
{
  // construct a length-0 array
  _data = (A *)0;
  _len = 0;
}

// constructor
template <class A>
Array<A>::
Array( A const *data, int len )
{
  if ( len != 0 )
  {
    // copy a
    _data = new A[len];
    _len = len;

    uint i;
    for ( i = 0; i < _len; i++ ) { _data[i] = data[i]; }
  }
  else
  {
    _data = (A *)0;
    _len = 0;
  }
}

// copy constructor
template <class A>
Array<A>::
Array( Array<A> const &a )
{
  if ( a._len != 0 )
  {
    // copy a
    _data = new A[a._len];
    _len = a._len;

    uint i;
    for ( i = 0; i < _len; i++ ) { _data[i] = a[i]; }
  }
  else
  {
    _data = (A *)0;
    _len = 0;
  }
}


// destructor
template <class A>
Array<A>::
~Array()
{
  deallocate();
}


// assignment operator
template <class A>
Array<A> &
Array<A>::
operator=( Array<A> const &a )
{
  if ( a._len != 0 )
  {
    // copy a
    if ( _len != a._len )
    {
      delete [] _data;
      _data = new A[a._len];
      _len = a._len;
    }

    uint i;
    for ( i = 0; i < _len; i++ ) { _data[i] = a[i]; }
  }
  else
  {
    // construct a 0-length array
    if ( _data != (A *)0 )
    {
      delete [] _data;
      _data = (A *)0;
      _len = 0;
    }
  }
  return *this;
}

// assignment operator
template <class A>
Array<A> &
Array<A>::
operator=( A const *a )
{
  uint i;
  for ( i = 0; i < _len; i++ )
  {
    _data[i] = a[i];
  }
  return *this;
}

template <class A>
void
Array<A>::
export_( A *a ) const
{
  uint i;
  for ( i = 0; i < _len; i++ )
  {
    a[i] = _data[i];
  }
}

template <class A>
void
Array<A>::
allocate(uint n)
{
  deallocate();
  if (n > 0)
  {
    _data = new A[n];
    _len = n;
  }
}

template <class A>
void
Array<A>::
deallocate()
{
  if ( _data != (A *)0 )
  {
    delete [] _data;
    _data = (A *)0;
    _len = 0;
  }
}

template <class A>
void
Array<A>::
set( A const & a )
{
  uint i;
  for ( i = 0; i < _len; i++ )
  {
    _data[i] = a;
  }
}

} // namespace base

#endif // base_Array_INCLUDED

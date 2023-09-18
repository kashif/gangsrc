/* GANG Software
 * BASE/base/ArrayP.H
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

#ifndef base_ArrayP_INCLUDED
#define base_ArrayP_INCLUDED

#include "System.H"

namespace base {

/*
  Variable-size one-dimensional ArrayP template class that
  does not store its own length.

  Space is allocated/deallocated with explicit calls to methods
  allocate()/deallocate().
*/

template <class A>
class ArrayP
{

public:

  // void constructor
  inline ArrayP();

  // destructor
  inline ~ArrayP();

  inline void allocate(uint);
  inline void deallocate();

  inline A const &operator[](uint i) const { return _data[i]; }
  inline A &operator[](uint i) { return _data[i]; }

  inline A *data() { return _data; }
  inline A const *data() const { return _data; }

private:

  A *_data;

  // disabled copy constructor and assigment operators
  // these can't be implemented because an ArrayP<> doesn't know how
  // long it is. Use ArrayPv<> if you need these.
  ArrayP(ArrayP<A> const &);
  ArrayP<A> &operator=( ArrayP<A> const & );
};


template <class A>
ArrayP<A>::
ArrayP()
{
  // does not allocate
  _data = (A *)0;
}


template <class A>
ArrayP<A>::
~ArrayP()
{
  deallocate();
}


template <class A>
void
ArrayP<A>::
allocate(uint n)
{
  deallocate();
  if (n > 0)
  {
    _data = new A[n];
  }
}


template <class A>
void
ArrayP<A>::
deallocate()
{
  if ( _data != (A *)0 )
  {
    delete [] _data;
    _data = (A *)0;
  }
}

} // namespace base

#endif // base_ArrayP_INCLUDED

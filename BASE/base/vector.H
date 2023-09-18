/* GANG Software
 * BASE/base/vector.H
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

#ifndef base_vector_INCLUDED
#define base_vector_INCLUDED

#include <vector>
#include "System.H"

namespace base {

#if !defined(__sgi)
template <class T, class Alloc = alloc>
class vector
  :
    public ::std::vector<T, Alloc>
{
public:
  typedef T value_type;
  typedef value_type* pointer;
  typedef const value_type* const_pointer;
  typedef value_type* iterator;
  typedef const value_type* const_iterator;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;

#ifdef __STL_CLASS_PARTIAL_SPECIALIZATION
  typedef reverse_iterator<const_iterator> const_reverse_iterator;
  typedef reverse_iterator<iterator> reverse_iterator;
#else /* __STL_CLASS_PARTIAL_SPECIALIZATION */
  typedef reverse_iterator<const_iterator, value_type, const_reference, 
                           difference_type>  const_reverse_iterator;
  typedef reverse_iterator<iterator, value_type, reference, difference_type>
          reverse_iterator;
#endif /* __STL_CLASS_PARTIAL_SPECIALIZATION */
protected:
  typedef simple_alloc<value_type, Alloc> data_allocator;

public:
  vector() : std::vector<T, Alloc>() {}
  vector(size_type n, const T& value) : std::vector<T, Alloc>(n, value) {}
  vector(int n, const T& value) : std::vector<T, Alloc>(n, value) {}
  vector(long n, const T& value) : std::vector<T, Alloc>(n, value) {}
  explicit vector(size_type n) : std::vector<T, Alloc>(n) {}
  vector(const vector<T, Alloc>& x) : std::vector<T, Alloc>(x) {}
#ifdef __STL_MEMBER_TEMPLATES
  template <class InputIterator>
  vector(InputIterator first, InputIterator last) :
      std::vector<T, Alloc>(first, last) {}
#else /* __STL_MEMBER_TEMPLATES */
  vector(const_iterator first, const_iterator last)
      std::vector<T, Alloc>(first, last) {}
#endif /* __STL_MEMBER_TEMPLATES */
  ~vector() {}
  vector<T, Alloc>& operator=(const vector<T, Alloc>& x)
    { std::vector<T, Alloc>::operator=(x); return *this; }

  reference operator[](size_type n)
    {
#ifdef DEBUG
      DIE_IF( n >= size() );
#endif
      return std::vector<T, Alloc>::operator[](n);
    }

  const_reference operator[](size_type n) const
    {
#ifdef DEBUG
      DIE_IF( n >= size() );
#endif
      return std::vector<T, Alloc>::operator[](n);
    }

  void sort()
    {
      std::sort(begin(), end());
    }
  void fill( T const &elem, size_t count )
    {
      clear();
      reserve(count);
      insert( end(), count, elem );
    }
};
#endif






#if defined(__sgi)
template <class T>
class vector
  :
    public ::std::vector<T>
{
public:
  typedef T value_type;
  typedef value_type* pointer;
  typedef const value_type* const_pointer;
  typedef value_type* iterator;
  typedef const value_type* const_iterator;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;

protected:

public:
  vector() : std::vector<T>() {}
  vector(size_type n, const T& value) : std::vector<T>(n, value) {}
  vector(int n, const T& value) : std::vector<T>(n, value) {}
  vector(long n, const T& value) : std::vector<T>(n, value) {}
  explicit vector(size_type n) : std::vector<T>(n) {}
  vector(const vector<T>& x) : std::vector<T>(x) {}
#ifdef __STL_MEMBER_TEMPLATES
  template <class InputIterator>
  vector(InputIterator first, InputIterator last) :
      std::vector<T>(first, last) {}
#else /* __STL_MEMBER_TEMPLATES */
  vector(const_iterator first, const_iterator last)
      std::vector<T>(first, last) {}
#endif /* __STL_MEMBER_TEMPLATES */
  ~vector() {}
  vector<T>& operator=(const vector<T>& x)
    { std::vector<T>::operator=(x); return *this; }

  reference operator[](size_type n)
    {
#ifdef DEBUG
      DIE_IF( n >= size() );
#endif
      return std::vector<T>::operator[](n);
    }

  const_reference operator[](size_type n) const
    {
#ifdef DEBUG
      DIE_IF( n >= size() );
#endif
      return std::vector<T>::operator[](n);
    }
};
#endif

} // namespace base

#endif // base_vector_INCLUDED

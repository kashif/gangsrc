/* GANG Software
 * BASE/base/Pool.H
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

#ifndef base_Pool_INCLUDED
#define base_Pool_INCLUDED

#include <stdlib.h>
#include <iostream>
#include <slist>
#include "System.H"

namespace base {

/*
  Class Pool - maintains a pool of fixed-sized elements.
  Using Pool is often more efficient than calling new/delete for each
   element, especially if many elements are allocated and deallocated.
  Memory grows but does not shrink until Pool's destructor is called.
  The Pool is not aware of the type of the element, so never calls
    an element's constructor or destructor.
  Pool does not support base::vector allocation (like new[]); this functionality
    can be implemented by the client

  Example:
<blockquote><font face="courier">
    class A {<br>
    public:<br>
      A() {}<br>
      ~A() {}<br>
      static void *operator new( size_t )<br>
        { return _pool.allocate(); }<br>
      static void operator delete( void *p )<br>
        { _pool.deallocate(p); }<br>
      // ...<br>
    protected:<br>
      // ...<br>
      int a1, a2, a3, a4, a5;<br>
    private:<br>
      static Pool _pool;<br>
      // ...<br>
      // disabled - not implemented<br>
      static void *operator new[]( size_t ) {abort(); return (void *)0;}<br>
      static void operator delete[]( void * ) {abort();}<br>
    };<br>
    <br>
    Pool A::_pool(sizeof(A), 1024);<br>
</font></blockquote>
 */

class Pool
{

public:

  /*
     Constructor.
     elements_in_block is the number of elements A in each block.
     A block is a piece of memory allocated by malloc().
  */
  Pool( size_t element_size, size_t elements_in_block );

  /*
     Destructor.
     Calls A's destructor on all allocated space.
  */
  virtual ~Pool();

  /*
     returns pointer to space allocating A.
     Calls A's default (no-argument) destructor.
  */
  void *allocate();

  /*
     Deallocates the space pointed to by a .
     Does not call A's destructor.
  */
  void deallocate(void *a);

  /*
     Returns the total amount of memory to date allocated with new().
     Not all of this memory need have been allocated to the client
     with Pool::allocate().
  */
  size_t memory_in_use() const
    { return _element_size * _elements_in_block * _block_list.size(); }

  /*
     Returns the number of elements allocated (in use)
     This does not include the potential elements for which
     space has been allocated but which have not been doled out
     with allocate().
  */
  size_t elements_in_use() const { return _elements_in_use; }

  // size of block.
  size_t elements_in_block() const
    { return _elements_in_block; }

  // size of element, adjusted up to a multiple of alignment size.
  size_t element_size() const
    { return _element_size; }

  // number of blocks currently in use.
  size_t blocks_in_use() const
    { return _block_list.size(); }

protected:

  // size of element.
  size_t _element_size;

  // size of block.
  size_t _elements_in_block;

  // number of elements currently in use.
  size_t _elements_in_use;

  // pointer to first block.
  std::slist<char *> _block_list;

   // pointer to next free element.
  void *_free_list_top;

  size_t _block_index;

private:

  Pool( Pool const & ) { DIE(); }
  Pool &operator=( Pool const & ) { DIE(); return *this; }
};


/*
   Class defaultPool is an alternate Pool which uses the default new/delete
   allocators. This may be useful for comparison with class Pool, either
   in debugging or time test.
*/
class defaultPool
{

public:

  // constructor
  defaultPool( size_t element_size, size_t )
    { _element_size = element_size; }

  // destructor
  virtual ~defaultPool() {}

  void *allocate()
    { _elements_in_use++; return new char[_element_size]; }

  void deallocate(void *p)
    { DIE_IF(_elements_in_use == 0); _elements_in_use--; delete [] (char *)p; }

  size_t memory_in_use() const
    { return 0; }

  size_t elements_in_use() const
    { return _elements_in_use; }

  size_t elements_in_block() const
    { return 0; }

  size_t element_size() const
    { return _element_size; }

  size_t blocks_in_use() const
    { return 0; }

protected:

  // size of element
  size_t _element_size;

  // number of elements currently in use
  size_t _elements_in_use;

private:

  defaultPool( defaultPool const & ) { DIE(); }
  defaultPool &operator=( defaultPool const & ) { DIE(); return *this; }
};

} // namespace base

#endif // base_Pool_INCLUDED

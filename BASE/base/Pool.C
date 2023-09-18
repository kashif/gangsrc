/* GANG Software
 * BASE/base/Pool.C
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

#include <iomanip>
#include "Pool.H"

namespace base {

int **PPP = 0;

Pool::
Pool(
  size_t element_size,
  size_t elements_in_block )
    :
    _block_list()
{
  // correct elemnt_size so that it is a multiple of align
  size_t align = sizeof(size_t *); // ???
  _element_size = (element_size % align == 0 ? element_size :
                   align*(element_size/align + 1));
  if (_element_size < align) { _element_size = align; }

  DIE_IF(_element_size <= 0);

  // elements_in_block
  _elements_in_block = elements_in_block;
  DIE_IF(_elements_in_block <= 0);

  _block_index = _elements_in_block;
  _free_list_top = (void *)0;

  _elements_in_use = 0;
}

Pool::
~Pool()
{
  DIE_IF(_elements_in_use != 0);

  // delete the blocks
  std::slist<char *>::iterator i;
  for (i = _block_list.begin(); i != _block_list.end(); i++ )
  {
    delete [] (*i);
  }
}

void *
Pool::
allocate()
{
  void *p = (void *)0;
  _elements_in_use++;

  if (_free_list_top != (void *)0)
  {
    // allocate an recycled element in the free std::list
    p = _free_list_top;

    // increment top
    _free_list_top = *(void **)_free_list_top;
  }
  else
  {
    if (_block_index == _elements_in_block)
    {
      // allocate a new block
      char *p = new char[_elements_in_block * _element_size];
      _block_list.push_front(p);
      _block_index = 0;
    }
    // allocate a fresh element from the current block
    p = (void *)(
      _block_list.front() + (_block_index++)*_element_size);
  }
  return p;
}

void
Pool::
deallocate(void *p)
{
  DIE_IF(_elements_in_use == 0);
  _elements_in_use--;
  // put 'a' onto the freelist
  void *v = _free_list_top;
  _free_list_top = p;
  *(void **)_free_list_top = v;
}

} // namespace base

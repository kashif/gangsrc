/* GANG Software
 * BASE/base/memory.C
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

#ifdef DEBUG

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <map>
#include "memory.H"

static size_t _memcount = 0;
static std::map<void *, std::pair<size_t, size_t> > _memmap;

static size_t _memdebug_no = (size_t)(-1);

static bool memdebug()
{
  char const *p = getenv("MEMDEBUG");
  if (p == 0)
  {
    return false;
  }

  errno = 0;
  char *q = (char *)0;
  size_t x = (size_t)strtoul( p, &q, 10);
  if ( q == p || errno != 0 )
  {
    abort();
  }
  _memdebug_no = x;
  return true;
}

static bool _memdebug = memdebug();

static
void *
allocate( size_t size )
{
  if ( _memdebug && _memcount == _memdebug_no )
  {
    fprintf( stderr, "memory: found memory allocation id %u; aborting\n",
             _memdebug_no );
    abort();
  }

  void *p = malloc( size );
  if ( p == (void *)NULL )
  {
    fprintf( stderr, "memory: malloc() returned 0 on attempt to allocate %u bytes\n", size );
    abort();
  }

  if (size == 0) {
    fprintf( stderr, "memory: allocating 0 bytes %p\n", p );
    abort();
  }


  // check if memory is already allocated (should never happen)
  if (_memmap.find(p) != _memmap.end())
  {
    fprintf( stderr, "memory: malloc returned pointer to memory already allocated\n" );
    abort();
  }
  // insert p into map
  _memmap[p] = std::pair<size_t, size_t>(_memcount, size);

#if 0
  fprintf( stderr, "+ %6u %p %6u\n", _memcount, p, size );
#endif

  _memcount++;

  return p;
}

static
void
deallocate( void *p )
{
  if ( p == (void *)0 )
  {
    return;
  }

  // check bad call to delete
  std::map<void *, std::pair<size_t,size_t> >::iterator i = _memmap.find(p);
  if (i == _memmap.end())
  {
    fprintf( stderr, "memory: delete called on an unallocated pointer %p\n",
             p );
    abort();
  }

#if 0
  fprintf( stderr, "- %6u %p %6u\n",
           (*i).second.first, (*i).first, (*i).second.second );
#endif
  _memmap.erase(i);

  free( p );
}

void
check_memory()
{
  if ( _memmap.size() == 0)
  {
    fprintf( stderr, "memory: no memory leaks\n" );
    return;
  }

  // count size
  size_t x = 0;
  std::map<void *, std::pair<size_t,size_t> >::const_iterator i;
  for ( i = _memmap.begin(); i != _memmap.end(); i++ )
  {
    x += (*i).second.second;
  }

  fprintf( stderr, "memory: %u memory leaks, %u bytes\n", _memmap.size(),
           x );

  fprintf( stderr, "id     pointer       size\n" );
  for ( i = _memmap.begin(); i != _memmap.end(); i++ )
  {
    fprintf( stderr, "%6u %p %6u\n",
             (*i).second.first, (*i).first, (*i).second.second );
  }
  
}

void *operator new( size_t size )
 throw (std::bad_alloc)
 { return allocate(size); }

void *operator new[]( size_t size )
 throw (std::bad_alloc)
 { return allocate(size); }

void operator delete( void *p )
  throw()
 { deallocate(p); }

void operator delete[]( void *p )
  throw()
 { deallocate(p); }
#endif

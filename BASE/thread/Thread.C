/* GANG Software
 * BASE/thread/Thread.C
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

#include <stdlib.h>
#include <iostream>
#include "base/Exception.H"
#include "Thread.H"

namespace thread {

#ifdef THREAD_PTHREAD

Thread::
Thread( uint thread_count )
    :
    _count(thread_count),
    _data( new Data[thread_count] ),
    _thread( new pthread_t[thread_count] )
{
  // initialize _data
  uint i;
  for ( i = 0; i < _count; i++ )
  {
    _data[i].me = this;
    _data[i].thread_id = i;
  }

  // initialize attributes
  pthread_attr_init( &_thread_attr );
  pthread_attr_setdetachstate( &_thread_attr, PTHREAD_CREATE_JOINABLE );
}

Thread::
~Thread()
{
  delete _data;
  delete _thread;
}


void
Thread::
run()
  throw(int)
{
#if 1
  uint i;
  for ( i = 0; i < _count; i++ )
  {
    int r = pthread_create(
      _thread + i, &_thread_attr,
      _function, (void *)(_data + i) );
    if ( r != 0 ) { throw (int)-1; }
  }

  // wait for all threads to finish
  pthread_attr_destroy( &_thread_attr );

  for ( i = 0; i < _count; i++ )
  {
    int r = pthread_join( _thread[i], (void **)0 );
    if ( r != 0 ) { throw (int)-1; }
  }
#endif

#if 0
  uint i;
  for ( i = 1; i < _count; i++ )
  {
    int r = pthread_create(
      _thread + i, &_thread_attr,
      _function, (void *)(_data + i) );
    if ( r != 0 ) { throw (int)-1; }
  }
  _function(_data);

  // wait for all threads to finish
  pthread_attr_destroy( &_thread_attr );

  for ( i = 1; i < _count; i++ )
  {
    int r = pthread_join( _thread[i], (void **)0 );
    if ( r != 0 ) { throw (int)-1; }
  }
#endif
}

void *
Thread::
_function( void *p )
{
  ((Data *)p)->me->function( ((Data *)p)->thread_id );
  return p;
}

#endif

#ifdef THREAD_MFORK

Thread::
Thread( uint thread_count )
    :
    _count(thread_count)
{
  // NOTE: this loses info about number of processors
  m_set_procs(_count);
}

Thread::
~Thread()
{
}


void
Thread::
run()
  throw(int)
{
  int r = m_fork( (void (*)())_function, (void *)this );
  if ( r == -1 )
  { WARN(); throw base::Exception("m_fork() failed" ); }
  m_kill_procs();
}

void
Thread::
_function( void *p )
{
  ((Thread *)p)->function( m_get_myid() );
}

#endif

} // namespace thread

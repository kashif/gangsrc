/* GANG Software
 * BASE/thread/Thread.H
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

#ifndef thread_Thread_INCLUDED
#define thread_Thread_INCLUDED

// NOTE: m_fork() and friends cannot be used in a program which links
// to libpthread. Thus m_fork() can't be used with libMagick.

#if defined(__sgi)
//#define THREAD_MFORK
#define THREAD_PTHREAD
#else
#define THREAD_PTHREAD
#endif

#ifdef THREAD_PTHREAD
#include <pthread.h>
#endif

#ifdef THREAD_MFORK
#include <ulocks.h>
#include <task.h>
#endif

#include "base/System.H"

namespace thread {

class Thread
{

public:

  // Constructor: initialize for 'thread_count' threads.
  Thread( uint thread_count );

  // destructor
  virtual ~Thread();

  // start 'thread_count' threads, running function() on each.
  // wait for all threads to finish
  void run() throw(int);

protected:
  virtual void function( uint thread_id ) = 0;

private:
  struct Data { Thread *me; uint thread_id; };

  uint _count;

#ifdef THREAD_PTHREAD
  Data *_data;
  pthread_t *_thread;
  pthread_attr_t _thread_attr;
  static void *_function(void *);
#endif

#ifdef THREAD_MFORK
  static void _function(void *);
#endif

  // disabled
  Thread( Thread const & );
  // disabled
  Thread & operator=( Thread const & );
};

} // namespace thread

#endif // thread_Thread_INCLUDED

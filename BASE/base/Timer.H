/* GANG Software
 * BASE/base/Timer.H
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

#ifndef base_Timer_INCLUDED
#define base_Timer_INCLUDED

#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/times.h>
#ifdef __GNUG__
#include <time.h>
#endif

namespace base {

class Timer
{

public:
  // constructor -- starts the timer
  Timer()
    { start(); }

  // destructor
  virtual ~Timer() {}

  void start()
    { _time = times( &_time_struct ); }

  // starts the timer and return the time in seconds
  float time();

protected:

  static float to_seconds(uint x)
    { return float(x)/float(sysconf(_SC_CLK_TCK)); }

  clock_t _time;
  tms _time_struct;

private:

  // disabled copy constructor
  Timer( Timer const & );
  // disabled assignment operator
  Timer &operator=( Timer const & );
};

} // namespace base

#endif // base_Timer_INCLUDED

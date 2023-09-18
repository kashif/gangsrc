/* GANG Software
 * BASE/base/ProcTimer.H
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

#ifndef base_ProcTimer_INCLUDED
#define base_ProcTimer_INCLUDED

#include "String.H"
#include "Timer.H"

namespace base {

class ProcTimer
  :
    public Timer
{
public:

  // constructor (initializes timer)
  ProcTimer() : Timer() {}

  // return user/system/elapsed time in clock ticks
  void read( long &, long &, long & ) const;

  // return user/system/elapsed time in seconds
  void read( float &, float &, float & ) const;

  /*
     return user/system/elapsed time in seconds as strings
     (two-digit precision)
  */
  void read( base::String &, base::String &, base::String & ) const;

private:

  // disabled copy constructor
  ProcTimer( Timer const & );
  // disabled assignment operator
  ProcTimer &operator=( Timer const & );
};

} // namespace base

#endif // base_ProcTimer_INCLUDED

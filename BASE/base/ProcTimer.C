/* GANG Software
 * BASE/base/ProcTimer.C
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

#include <stdio.h>
#include "ProcTimer.H"

namespace base {

void
ProcTimer::
read(
  float &user_time,
  float &system_time,
  float &elapsed_time ) const
{
  long user_time_, system_time_, elapsed_time_;
  read( user_time_, system_time_, elapsed_time_ );

  user_time = to_seconds(user_time_);
  system_time = to_seconds(system_time_);
  elapsed_time = to_seconds(elapsed_time_);
}

void
ProcTimer::
read(
  base::String &user_time,
  base::String &system_time,
  base::String &elapsed_time ) const
{
  float user_time_, system_time_, elapsed_time_;
  read( user_time_, system_time_, elapsed_time_ );

  char t[100];
  sprintf( t, "%.2f", user_time_ );
  user_time = t;
  sprintf( t, "%.2f", system_time_ );
  system_time = t;
  sprintf( t, "%.2f", elapsed_time_ );
  elapsed_time = t;
}

void
ProcTimer::
read(
  long &user_time,
  long &system_time,
  long &elapsed_time ) const
{
  tms system_time1;
  clock_t elapsed_time1 = times( &system_time1 );

  user_time = (system_time1.tms_utime - _time_struct.tms_utime) +
    (system_time1.tms_cutime - _time_struct.tms_cutime);
  system_time = (system_time1.tms_stime - _time_struct.tms_stime) +
    (system_time1.tms_cstime - _time_struct.tms_cstime);
  elapsed_time = elapsed_time1 - _time;
}


} // namespace base

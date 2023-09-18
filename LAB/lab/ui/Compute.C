/* GANG Software
 * LAB/lab/ui/Compute.C
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

#include "base/String.H"
#include "Compute.H"

namespace lab {
namespace ui {

Compute::
Compute()
{
}

Compute::
~Compute()
{
}

void
Compute::
compute()
{
  // grab focus so that widgets can update their numbers
  grab_focus();

  clear_status();

  // show compute dialog box when computation starts
  raise_d(true);
  show_d(true);

  _compute_and_export();
}

void
Compute::
stop_computation()
{
  progressbar_w()->set(0.0f);
  _stop_computation();
}

void
Compute::
reset()
{
  name_w()->set( "" );
  clear_status();
}

void
Compute::
clear_status()
{
  set_time( "", "" );
  progressbar_w()->set(0.0f);
}

void
Compute::
set( parser::KeyParser const &data )
{
  name_w()->set( data.get("name").c_str() );
}

void
Compute::
set_time(
  char const *t0,
  char const *t1 )
{
  time0_w()->set(t0);
  time1_w()->set(t1);
}


void
Compute::
set_status(
  uint count,
  uint total )
{
  // update the ui every 20'th call (hueristic choice)

  if ( count % 20 == 0 )
  {
    if (total != 0)
    {
      // called by the Ui driver for each data point X[i,j]
      progressbar_w()->set( float(count)/float(total) );
    }
    sync();
  }
}

void
Compute::
set_status(
  base::String user_time,
  base::String system_time,
  base::String elapsed_time )
{
  // fill progress bar
  progressbar_w()->set(1.0f);

  // report time
  Compute::set_time( user_time.c_str(), elapsed_time.c_str() );
}

void
Compute::
get( parser::KeyParser &data ) const
{
  data.set("name", name_w()->get() );
}

bool
Compute::
command(
  base::String const &command,
  base::String const &argument,
  base::String &response )
{
  bool r = false;
  if ( command == "labCompute" )
  {
    compute();
    r = true;
  }
  if ( command == "labStop" )
  {
    stop_computation();
    r = true;
  }
  if ( command == "labName" )
  {
    name_w()->set(argument.c_str());
    r = true;
  }
  return r;
}


} // namespace ui
} // namespace lab

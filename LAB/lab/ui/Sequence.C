/* GANG Software
 * LAB/lab/ui/Sequence.C
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
#include "Sequence.H"

namespace lab {
namespace ui {

// The sequencer creates a sequence of image files suitable for making
// a video

Sequence::
Sequence()
{
}

Sequence::
~Sequence()
{
}


void
Sequence::
reset_cb()
{
  int const a[2] = { 0, 4 };
  counter_w()->set( a );
  now_w()->set( "" );
  counter_varname_w()->set("n");
  time_varname_w()->set( "s" );
  function_w()->set( "n" );
  filename_w()->set( "image###.sgi" );
}

void
Sequence::
go_cb()
{
  int a[2];
  counter_w()->get( a );
  uint start = (uint)trunc(a[0]);
  uint count = (uint)trunc(a[1]);

  compute_sequence(
    (char *)0,
    counter_varname_w()->get(),
    time_varname_w()->get(),
    function_w()->get(),
    start, count
    );
}

void
Sequence::
go_write_cb()
{
  int a[2];
  counter_w()->get( a );
  if ( a[0] < 0 || a[1] < 1) { WARN(); return; }
  uint start = a[0];
  uint count = a[1];

  compute_sequence(
    filename_w()->get(),
    counter_varname_w()->get(),
    time_varname_w()->get(),
    function_w()->get(),
    start, count
    );
}

void
Sequence::
update_sequencer(
  uint n )
{
  base::String now;
  now.to_string( n );
  now_w()->set( now.c_str() );
}

bool
Sequence::
command(
  base::String const &command,
  base::String const &argument,
  base::String &response ){
  bool r = false;
  return r;
}

} // namespace ui
} // namespace lab

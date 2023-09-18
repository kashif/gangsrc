/* GANG Software
 * LAB/lab/kernel/Lab.C
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

#include "io/IstreamStream.H"
#include "io/OstreamStream.H"
#include "Lab.H"

namespace lab {
namespace kernel {

Lab::
Lab()
    :
    LabBase2(),
    ::lab::ui::Ui()
{
}

Lab::
~Lab()
{
}

void
Lab::
_read( io::Istream &stream )
{
  message( base::String() );

  try
  {
    data().parse(stream);
    set_state_from_data(); 
    set_ui_from_data_v();
  }
  catch ( base::Exception &e )
  {
    message( e.message() );
  }
}

void
Lab::
_read( base::String const &filename )
{
  try
  {
    io::IstreamStream stream(filename);
    _read(stream);
  }
  catch ( base::Exception &e )
  {
    message( e.message() );
  }
}

void
Lab::
_write( io::Ostream &stream )
{
  message( base::String() );
  set_data_from_ui_v();
  data().write( stream );
}

void
Lab::
_write( base::String const &filename )
{
  io::OstreamStream stream(filename);
  _write(stream);
}

void
Lab::
_compute_and_export()
{
  try
  {
    set_data_from_ui_v();
    set_state_from_data();
  }
  catch (base::Exception const &e)
  {
    message(e.message());
    return;
  }

  // baseclass version
  LabBase2::_compute_and_export();
}

} // namespace kernel
} // namespace lab

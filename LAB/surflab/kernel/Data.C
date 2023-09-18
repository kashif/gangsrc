/* GANG Software
 * LAB/surflab/kernel/Data.C
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

#include "Data.H"

namespace surflab {
namespace kernel {

char const *
Data::_version_string = "SurfLab 1.0";

Data::KeyValPair Data::_data_default[] =
{
  { "geometry", "parabolic" },
  { "dim", "3" },
  { "name", "" },
  { "var1", "u" },
  { "var2", "v" },
  { "x1", "" },
  { "x2", "" },
  { "x3", "" },
  { "x4", "" },
  { "x5", "" },
  { "domain", "" },
};

Data::
Data()
    :
    parser::KeyParser(
      _version_string,
      _data_default,
      sizeof(_data_default)/sizeof(KeyValPair) )
{
}

Data::
~Data()
{
}

} // namespace kernel
} // namespace surflab

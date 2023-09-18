/* GANG Software
 * LAB/klab/kernel/Data.C
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

namespace klab {
namespace kernel {

char const *
Data::_version_string = "KLab 1.0";

Data::KeyValPair
Data::_data_default[] =
{
  { "name",                  ""   },
  { "potential_x",           ""   },
  { "potential_y",           ""   },
  { "domain",                ""   },
  { "zstart",                ""   },
  { "lambda",                "1"  },
  { "polynomial_length",     "20"  },
  { "initial_x",             "{{1,0},{0,1}}" },
  { "initial_y",             "{{1,0},{0,1}}" },
  { "initial_integrator_count", "100" },
  { "integrator_count",         "1"  }
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
} // namespace klab

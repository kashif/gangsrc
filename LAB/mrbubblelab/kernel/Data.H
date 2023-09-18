/* GANG Software
 * LAB/mrbubblelab/kernel/Data.H
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

#ifndef mrbubblelab_kernel_Data_INCLUDED
#define mrbubblelab_kernel_Data_INCLUDED

#include "parser/KeyParser.H"

namespace mrbubblelab {
namespace kernel {

class Data
  :
    public parser::KeyParser
{

public:
  Data();
  virtual ~Data();

protected:

private:

  static char const *_version_string;
  static KeyValPair _data_default[];

  // disabled copy constructor
  Data( Data const & );
  // disabled assignment operator
  Data &operator=( Data const & );

};

} // namespace kernel
} // namespace mrbubblelab

#endif // mrbubblelab_kernel_Data_INCLUDED

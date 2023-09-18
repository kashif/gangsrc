/* GANG Software
 * LAB/minlab/kernel/Exception.C
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

#include "Exception.H"

namespace minlab {
namespace kernel {

char const *const
Exception::
_message0[] =
{
  "",
  "Computation stopped.",
  "error reading data",
  "invalid file",
  "error in variable name",
  "error in mode (spinor/weierstrass)",
  "error in zstart",
  "error in spinor 1",
  "error in spinor 2",
  "error in Weierstrass g",
  "error in Weierstrass f",
  "error in integrator count",
  "error in initial integrator count",
  "error in Xstart1",
  "error in Xstart2",
  "error in Xstart3",
  "error evaluating integrand",
  "associate family parameter"
};

} // namespace kernel
} // namespace minlab

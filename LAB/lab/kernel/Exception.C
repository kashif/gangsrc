/* GANG Software
 * LAB/lab/kernel/Exception.C
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

namespace lab {
namespace kernel {

char const *const
Exception::
_message0[] =
{
  "",
  "Domain is unconfigured.",
  "Unknown domain keyword.",
  "Error reading indexed domain file.",
  "Error finding indexed domain start index.",
  "Error computing indexed domain edge tree.",
  "Error in indexed domain: n-gon detected with n>3",
  "Error in refine",
  "Error in max_area2",
  "Error in curvature_exp",
  "Error in curvature_cut",
  "Error in sequencer",
  "Computation stopped",
  "Sequence computation stopped",
  "Internal error in Domain"
};

} // namespace kernel
} // namespace lab

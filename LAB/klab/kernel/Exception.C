/* GANG Software
 * LAB/klab/kernel/Exception.C
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

namespace klab {
namespace kernel {

char const *const
Exception::
_message0[] =
{
  "",
  "Computation stopped.",
  "Input error.",
  "There is an error of some kind in the specification of the domain.",
  "An error occurred computing the domain.",

  "There is a syntax error in the x potential.",
  "There is a syntax error in the y potential.",
  "The x potential blew up.",
  "The y potential blew up.",
  "Birkhoff decomposition failed.",

  "There is a syntax error in the x potential.",
  "There is a syntax error in the y potential.",
  "The x potential blew up in the initial segment.",
  "The y potential blew up in the initial segment.",
  "The Birkhoff decomposition failed in the initial segment.",

  "The x potential contains an invalid loop parameter exponent.",
  "The y potential contains an invalid loop parameter exponent.",
  "There is a syntax error in the x initial matrix.",
  "An error occurred while evaluating the x initial matrix.",
  "There is a syntax error in the y initial matrix.",
  "An error occurred while evaluating the y initial matrix.",

  "The value for polynomial length is invalid.",
  "The value for polynomial length must be even.",

  "Error reading file.",
  "The file you attempted to load is not a valid Lab file. The first line of a Lab file should be \"KLab 1.0\"",

  "There is a syntax error in indexed domain.",
  "There is a syntax error in grid domain.",
  "There is a syntax error in zstart.",
  "There is a syntax error in the lambda parameter.",
  "There is a syntax error in the initial x matrix.",
  "There is a syntax error in the initial y matrix.",
  "There is a syntax error in the x potential.",
  "There is a syntax error in the y potential.",
  "There is a syntax error in integrator count.",
  "There is an invalid value for integrator count.",
  "There is a syntax error in initial integrator count.",
  "There is an invalid value for initial integrator count.",
  "There is a syntax error in polynomial length.",
  "There is an invalid value for polynomial length."
  "There was a computational error in the Sym formula."
};

} // namespace kernel
} // namespace klab

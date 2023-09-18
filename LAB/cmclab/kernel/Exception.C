/* GANG Software
 * LAB/cmclab/kernel/Exception.C
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

namespace cmclab {
namespace kernel {

char const * const
Exception::_message0[] =
{
  "",
  "Stopped.",
  "Input error.",
  "There is an error of some kind in the specification of the domain.",
  "An error occurred computing the domain.",

  "There is a syntax error in the potential.",
  "The potential blew up.",
  "Iwasawa factorization failed.",
  "Spaceform mismatch.",

  "There is a syntax error in potential.",
  "The potential blew up in initial segment.",
  "The Iwasawa decomposition failed in the initial segment.",

  "The potential contains an invalid loop parameter exponent.",
  "There is a syntax error in the dressing matrix.",
  "An error occurred while evaluating the dressing matrix.",

  "The value for polynomial length is invalid.",
  "The value for polynomial length must be even.",
  "The value for basis length is invalid.",
  "The value for basis length must be even.",
  "The values for polynomial length and basis length are relatively invalid.",

  "Error reading file.",
  "The file you attempted to load is not a valid Lab file. The first line of a Lab file should be \"CMCLab 1.0\"",

  "There is a syntax error in indexed domain.",
  "There is a syntax error in grid domain.",
  "There is a syntax error in zstart.",
  "There is a syntax error in the mean curvature.",
  "There is a syntax error in the lambda parameter.",
  "There is a syntax error in the normal shift parameter.",
  "There is a syntax error in xstart.",
  "There is a syntax error in the potential.",
  "There is a syntax error in integrator count.",
  "There is an invalid value for integrator count.",
  "There is a syntax error in initial integrator count.",
  "There is an invalid value for initial integrator count.",
  "There is a syntax error in polynomial length.",
  "There is an invalid value for polynomial length.",
  "There is a syntax error in basis length.",
  "There is an invalid value for basis length.",
  "The basis length is too high relative to the polynomial length.",
  "There is a syntax error in Iwasawa method (fast/far).",
  "There is a syntax error in Birkhoff (true/false).",
  "There is a syntax error in the one_column option (true/false)."
};


} // namespace kernel
} // namespace cmclab

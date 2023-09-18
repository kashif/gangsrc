/* GANG Software
 * LAB/loop/Common.H
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

#ifndef loop_Common_INCLUDED
#define loop_Common_INCLUDED

#include <complex>
#include "base/Array.H"
#include "base/ArrayX.H"
#include "math/Complex4.H"

namespace loop {

typedef double Real;
typedef std::complex<Real> Complex;

struct Range { int start; uint count; };
typedef base::ArrayX<base::ArrayX<Range,2U>,2U> RangeMatrix;

//#define LOOP_DIE() // nothing
//#define LOOP_DIE_IF(__x__) // nothing

#define LOOP_DIE() DIE()
#define LOOP_DIE_IF(__x__) DIE_IF(__x__)

} // namespace loop

#endif // loop_Common_INCLUDED

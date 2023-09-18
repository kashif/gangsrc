/* GANG Software
 * LAB/loop/RIwasawa.H
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

#ifndef loop_RIwasawa_INCLUDED
#define loop_RIwasawa_INCLUDED

#include "Birkhoff.H"
#include "Iwasawa.H"

namespace loop {

class RIwasawa
  :
    public Iwasawa
{

public:
  // constructor
  RIwasawa( uint polylen, uint basislen,
            bool birkhoff, bool onecolumn );

  // destructor
  virtual ~RIwasawa();

  void factor( Loop4 &F, Loop4 const &X );

protected:

private:

  Birkhoff *_birkhoff;
  Loop4 *_X1;

  // disabled copy constructor
  RIwasawa( RIwasawa const & );

  // disabled assignment operator
  RIwasawa &operator=( RIwasawa const & );

};

} // namespace loop

#endif // loop_RIwasawa_INCLUDED

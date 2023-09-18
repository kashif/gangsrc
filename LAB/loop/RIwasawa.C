/* GANG Software
 * LAB/loop/RIwasawa.C
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

#include "RIwasawa.H"

namespace loop {

RIwasawa::
RIwasawa( uint polylen, uint basislen,
          bool birkhoff, bool onecolumn )
    :
    Iwasawa( polylen, basislen, onecolumn ),
    _birkhoff( (Birkhoff *)0 )
{
  if (birkhoff)
  {
    _birkhoff = new Birkhoff(_polylen, true);
    _X1 = new Loop4(_polylen);
  }
}

RIwasawa::
~RIwasawa()
{
  if (_birkhoff != (Birkhoff *)0)
  {
    delete _birkhoff;
    delete _X1;
  }
}

void
RIwasawa::
factor( Loop4 &F, Loop4 const &X )
{
  if (_birkhoff != (Birkhoff *)0)
  {
    _birkhoff->factor_minus_plus( *_X1, X );
    Iwasawa::factor( F, *_X1 );
  }
  else
  {
    Iwasawa::factor( F, X );
  }
}


} // namespace loop

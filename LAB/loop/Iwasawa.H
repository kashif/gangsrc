/* GANG Software
 * LAB/loop/Iwasawa.H
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

#ifndef loop_Iwasawa_INCLUDED
#define loop_Iwasawa_INCLUDED

#include "base/System.H"
#include "Common.H"
#include "loop/Loop4.H"

#define IWASAWA_LAPACK
#ifdef IWASAWA_LAPACK
#include "QRLapack.H"
#else
#include "QR.H"
#endif

namespace loop {

class Iwasawa
{

public:
  // constructor
  Iwasawa( uint polylen, uint basislen,
           bool onecolumn );

  // destructor
  virtual ~Iwasawa();

  void factor( Loop4 &F, Loop4 const &X );

protected:

  uint _polylen;

  /*
    _basislen:

    With W = {t X1, ... t^b X1, t X2, ..., t^b X2},
    _basislen is b.
    Thus W has length 2b.
  */
  uint _basislen;

  // _len is the number of rows in half of A
  uint _len;
  bool _onecolumn;

private:

  base::ArrayP<Complex> _Ax;
  base::ArrayP<Complex> _Bx;

#ifdef IWASAWA_LAPACK
  QRLapack *_QR;
#else
  QR *_QR;
#endif

  void setup_A( Loop4 const &X );
  void setup_B( Loop4 const &X );
  void setup_F( Loop4 &F ) const;
  void normalize( Loop4 &F ) const;

  // disabled copy constructor
  Iwasawa( Iwasawa const & );

  // disabled assignment operator
  Iwasawa &operator=( Iwasawa const & );

};

} // namespace loop

#endif // loop_Iwasawa_INCLUDED

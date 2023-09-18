/* GANG Software
 * LAB/loop/Iwasawa.C
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

#include "QRLapack.H"
#include "Iwasawa.H"

namespace loop {

Iwasawa::
Iwasawa(
  uint polylen,
  uint basislen,
  bool onecolumn )
    :
    _polylen(polylen),
    _basislen(basislen),
    _len(2*_polylen + 1 + _basislen),
//    _len(2*_polylen + 1),
    _onecolumn(onecolumn),
#ifdef IWASAWA_LAPACK
    _QR(new QRLapack( 2*_len, 2*_basislen ))
#else
    _QR(new QR( 2*_len, 2*_basislen ))
#endif
{
  // Ax is a (2*_len) x (2*_basislen) matrix
  _Ax.allocate( (2*_len) * (2*_basislen) );
  // Bx is a (2*_len)x(2) matrix
  _Bx.allocate( (2*_len) * (2) );
}

Iwasawa::
~Iwasawa()
{
  delete _QR;
}

void
Iwasawa::
factor(
  Loop4 &F,
  Loop4 const &X )
{
  // sanity checks
  DIE_IF( &X == &F );
  DIE_IF( X.polylen() != _polylen );
  DIE_IF( F.polylen() != _polylen );

  // setup A
  setup_A( X );

  // perform QR factorizaton
  _QR->factor( _Ax );

  // setup B
  setup_B( X );

  // compute projection
  uint b = ( _onecolumn ? 1 : 2 );
  _QR->projection( _Ax, _Bx, b );

  // setup F
  setup_F( F );

  // orthogonal complement
  if (!_onecolumn)
  {
    F.sub(X);
    F.neg();
  }
  else
  {
    F.col1().sub(X.col1());
    F.col1().neg();
  }

  // normalize
  normalize( F );

//  F.chop();
}

void
Iwasawa::
setup_A( Loop4 const &X )
{
  // copy X into A in the appropriate format

  uint u = _len;
  uint v = _basislen * 2*u;
  uint p = 2*_polylen + 1;

  // set up A
  uint i;
  for ( i = 0; i < 2; i++ )
  {
    uint j;
    for ( j = 0; j < 2; j++ )
    {
      // pointer to input vector
      Complex const *X1 = X[j][i].data().data();

      // for each column of A
      uint s;
      for (s = 0; s < _basislen; s++ )
      {
        uint q = i*u + j*v + 2*u*s;

        // pointer to start of output vector
        Complex *A1 = _Ax.data() + q;

        // initial zeros
        math::zero( A1, s+1 );

        // copy X into A
        math::blas<Real>::zcopy(
          std::min(_len-(s+1), p), X1, 1, A1 + (s+1), 1 );

        // final zeros
        if( _len > p + (s+1) )
        {
          math::zero( A1 + p + s+1, _len - p - (s+1) );
        }
      }
    }
  
  }

#if 0
  uint j;
  for (j = 0; j < 2*_basislen; j++) {
    for (i = 0; i < 2*_len; i++) {
      std::cerr << _Ax[i+j*2*_len] << " ";
    }
    std::cerr << "\n";
  }
#endif
}

void
Iwasawa::
setup_B( Loop4 const &X )
{
  uint u = _len;
  uint p = 2*_polylen + 1;

  uint b = ( _onecolumn ? 1 : 2 );

  // set up B
  uint i;
  for ( i = 0; i < 2; i++ )
  {
    uint j;
    for ( j = 0; j < b; j++ )
    {
      uint q = (i+2*j)*u;
      // copy X to B
      math::blas<Real>::zcopy(
        p, X[j][i].data().data(), 1, _Bx.data() + q, 1 );

      // final zeros
      if (_len > p )
      {
        math::zero( _Bx.data() + q + p, _len - p );
      }
    }
  }

#if 0
  uint j;
  for (j = 0; j < 2; j++) {
    for (i = 0; i < 2*_len; i++) {
      std::cerr << _Bx[i+j*2*_len] << " ";
    }
    std::cerr << "\n";
  }
#endif
}

void
Iwasawa::
setup_F( Loop4 &F ) const
{
  uint u = _len;
  uint p = 2*_polylen + 1;

  uint b = ( _onecolumn ? 1 : 2 );

  // copy B into F
  uint i;
  for ( i = 0; i < 2; i++ )
  {
    uint j;
    for ( j = 0; j < b; j++ )
    {
      uint q = (i+2*j)*u;
      math::blas<Real>::zcopy(
        p, _Bx.data() + q, 1, F[j][i].data().data(), 1 );
    }
  }
}

void
Iwasawa::
normalize( Loop4 &F ) const
{
  if (!_onecolumn)
  {
    // normalize first column of F
    int r = F.col1().normalize();
    if ( r!= 0 )
    { throw base::Exception(
      "Error in Iwasawa factorization: the first column of the unitary loop is 0"); }

    // normalize second column of F
    Complex y;
    inner_product( y, F.col2(), F.col1() );

    Loop2 T(F.col1());
    T.mul( y );
    F.col2().sub( T );
    F.col2().normalize();
  }
  else
  {
    // normalize first column of F
    int r = F.col1().normalize();
    if ( r != 0 )
    { throw base::Exception(
      "Error in Iwasawa factorization: the first column of the unitary loop is 0"); }
    F.col2().row2().conj( F.col1().row1() );
    F.col2().row1().conj( F.col1().row2() );
    F.col2().row1().neg();
  }
}

} // namespace loop

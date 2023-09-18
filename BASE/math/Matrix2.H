/* GANG Software
 * BASE/math/Matrix2.H
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

#ifndef math_Matrix2_INCLUDED
#define math_Matrix2_INCLUDED

#include <iostream>
#include "MatrixX.H"
#include "mathx.H"

namespace math {

template <class A>
class Vector2;

/*
  2-by-2 matrices with R^2 functionality.
*/

template <class A>
class Matrix2 : public matrixX<A, 2U>
{
  //
public :

  // void constructor
  Matrix2();

  // copy constructor
  Matrix2( Matrix2 const &a );

  // constructor
  Matrix2( A const *a );

  // destructor
  ~Matrix2();

  // assignment operators
  Matrix2 &
  operator=( Matrix2<A> const & );

  //
  Matrix2 &
  operator=( A const *a );

  /*
     sets *this to a rotation matrix with axis "axis",
     and rotation angle "angle"
  */
  int
  rotation( Vector2<A> const &axis, A angle );
  //
  int
  reflection( Vector2<A> const &normal );
  //
  void
  inversion();

  //
  friend class Vector2<A>;
};


// constructors and destructors
template <class A>
inline
Matrix2<A>::Matrix2() : matrixX<A, 2U>()
{
}


template <class A>
inline
Matrix2<A>::Matrix2( Matrix2 const &a ) : matrixX<A, 2U>( a )
{
}


template <class A>
inline
Matrix2<A>::Matrix2( A const *a ) : matrixX<A, 2U>( a )
{
}


template <class A>
inline
Matrix2<A>::~Matrix2()
{
}


// assigenment operators
template <class A>
Matrix2<A> &
Matrix2<A>::operator=( Matrix2 const &a )
{
  ( ( matrixX<A, 2U> * )this )->operator=( a );
  return *this;
}


template <class A>
Matrix2<A> &
Matrix2<A>::operator=( A const *a )
{
  ( ( matrixX<A, 2U> * )this )->operator=( a );
  return *this;
}


template <class A>
int
Matrix2<A>::rotation( Vector2<A> const &axis, A angle )
{
  unsigned i, j;
  A x(  math::cos( angle )  ), y(  math::sin( angle )  );

  Vector2<A> a( axis );

  if ( a.normalize() )
    return 1;

  Matrix2<A> mat1, mat2;

  identity();

  for ( i = 0;  i < 2;  i++ )
  {
    for ( j = 0;  j < 2;  j++ )
    {
      mat1[i][j] = a[i] * a[j];
    }
  }

  mat2[0][1] = -a[2];
  mat2[0][2] =  a[1];
  mat2[1][0] =  a[2];
  mat2[1][2] = -a[0];
  mat2[2][0] = -a[1];
  mat2[2][1] =  a[0];

  *this *= x;

  mat1 *= ( 1 - x );
  mat2 *= y;

  *this += mat1;
  *this += mat2;

  return 0;
}


template <class A>
int
Matrix2<A>::reflection( Vector2<A> const &axis )
{
  unsigned i, j;
  Matrix2<A> mat;

  identity();

  for ( i = 0;  i < 2;  i++ )
  {
    for ( j = 0;  j < 2;  j++ )
    {
      mat[i][j] = axis[i] * axis[j];
    }
  }

  mat *= ( 2 / axis.norm2() );

  operator -=( mat );
  return 0;
}


template <class A>
void
Matrix2<A>::inversion()
{
  unsigned i, j;
  for ( i = 0;  i < 2;  i++ )
  {
    for ( j = 0;  j < 2;  i++ )
    {
      x[i][j] = ( i == j ? A(-1) : A(0) );
    }
  }
}

} // namespace math

#endif // math_Matrix2_INCLUDED

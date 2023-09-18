/* GANG Software
 * BASE/math/Matrix3.H
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

#ifndef math_Matrix3_INCLUDED
#define math_Matrix3_INCLUDED

#include <iostream>
#include "VectorX.H"
#include "Vector3.H"
#include "MatrixX.H"

#if defined(__sgi) && !defined(__GNUG__)
#pragma set woff 1375 // The destructor for class is not virtual.
#endif

namespace math {

/*
   3-by-3 matrices with R^3 functionality.
 */
template <class A>
class Matrix3 : public MatrixX<A, 3>
{
public :

  // void constructor
  Matrix3 ();

  // constructor
  Matrix3 (Matrix3 const &a);

  // constructor
  Matrix3 (A const *a);

  // destructor
  ~Matrix3 ();

  // assignment operators
  Matrix3 &
  operator= (Matrix3<A> const &);

  //
  Matrix3 &
  operator= (A const *a);

  /*
     sets *this to a rotation matrix with axis "axis",
     and rotation angle "angle"
  */
  int
  rotation(Vector3<A> const &axis, A angle);
  //
  int
  reflection(Vector3<A> const &normal);
  //
  void
  inversion();

  A det() const;

  //
  friend class Vector3<A>;
};


// constructors and destructors
template <class A>
inline
Matrix3<A>::
Matrix3() : MatrixX<A, 3>()
{
}


template <class A>
inline
Matrix3<A>::
Matrix3(Matrix3 const &a) : MatrixX<A, 3>(a)
{
}


template <class A>
inline
Matrix3<A>::
Matrix3(A const *a) : MatrixX<A, 3>(a)
{
}


template <class A>
inline
Matrix3<A>::
~Matrix3()
{
}


// assigenment operators
template <class A>
Matrix3<A> &
Matrix3<A>::
operator= (Matrix3 const &a)
{
  ((MatrixX<A, 3> *)this)->operator=(a);
  return *this;
}


template <class A>
Matrix3<A> &
Matrix3<A>::
operator= (A const *a)
{
  ((MatrixX<A, 3> *)this)->operator=(a);
  return *this;
}


template <class A>
int
Matrix3<A>::
rotation(Vector3<A> const &axis, A angle)
{
  unsigned i, j;
  A x( math::cos(angle) ), y( math::sin(angle) );

  Vector3<A> a(axis);

  if (a.normalize())
    return 1;

  Matrix3<A> mat1, mat2;

  this->identity();

  for (i = 0;  i < 3;  i++)
  {
    for (j = 0;  j < 3;  j++)
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

  mat1 *= (1 - x);
  mat2 *= y;

  *this += mat1;
  *this += mat2;

  return 0;
}


template <class A>
int
Matrix3<A>::
reflection(Vector3<A> const &axis)
{
  unsigned i, j;
  Matrix3<A> mat;

  this->identity();

  for (i = 0;  i < 3;  i++)
  {
    for (j = 0;  j < 3;  j++)
    {
      mat[i][j] = axis[i] * axis[j];
    }
  }

  mat *= (2 / axis.norm2());

  operator -=(mat);
  return 0;
}


template <class A>
void
Matrix3<A>::
inversion()
{
  unsigned i, j;
  for (i = 0;  i < 3;  i++)
  {
    for (j = 0;  j < 3;  i++)
    {
      x[i][j] = (i == j ? (A)-1.0 : (A)0.0);
    }
  }
}


template <class A>
A
Matrix3<A>::
det() const
{
  return
      x[0][0] * ( x[1][1]*x[2][2] - x[1][2]*x[2][1] )
    - x[0][1] * ( x[1][0]*x[2][2] - x[1][2]*x[2][0] )
    + x[0][2] * ( x[1][0]*x[2][1] - x[1][1]*x[2][0] );
}


} // namespace math

#if defined(__sgi) && !defined(__GNUG__)
#pragma reset woff 1375 // The destructor for class is not virtual.
#endif

#endif // math_Matrix3_INCLUDED

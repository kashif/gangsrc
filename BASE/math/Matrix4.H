/* GANG Software
 * BASE/math/Matrix4.H
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

#ifndef math_Matrix4_INCLUDED
#define math_Matrix4_INCLUDED

#include <iostream>
#include "MatrixX.H"
#include "Matrix3.H"

#if defined(__sgi) && !defined(__GNUG__)
#pragma set woff 1375 // The destructor for class is not virtual.
#endif

namespace math {

template <class A>
class vector4;

template <class A>
class Matrix4 : public MatrixX<A,4U>
{
public :

  // constructor
  Matrix4();
  // constructor
  Matrix4(Matrix4 const &a);
  // constructor
  Matrix4(A const *a);
  // destructor
  ~Matrix4();
  // assignment operator
  Matrix4 &operator=(Matrix4<A> const &);
  // assignment operator
  Matrix4 &operator=(A const *a);

  void reflection(vector4<A> const &normal);
  void scale_matrix( A x, A y, A z );
  void translation_matrix( A x, A y, A z );
  void rotation_matrix( A angle, A a0, A a1, A a2 );
  void rotation_matrix( A angle, A a0, A a1, A a2, A o0, A o1, A o2 );
};


// constructors and destructors
template <class A>
inline
Matrix4<A>::
Matrix4()
    :
    MatrixX<A,4U>()
{
}


template <class A>
inline
Matrix4<A>::
Matrix4(Matrix4 const &a) : MatrixX<A,4U>(a)
{
}


template <class A>
inline
Matrix4<A>::
Matrix4(A const *a) : MatrixX<A,4U>(a)
{
}


template <class A>
inline
Matrix4<A>::
~Matrix4()
{
}


// assigenment operators
template <class A>
Matrix4<A> &
Matrix4<A>::
operator=(Matrix4 const &a)
{
  MatrixX<A,4U>::operator=(a);
  return *this;
}


template <class A>
Matrix4<A> &
Matrix4<A>::
operator=(A const *a)
{
  ((MatrixX<A,4U> *)this)->operator=(a);
  return *this;
}

template <class A>
void
Matrix4<A>::
reflection(vector4<A> const &axis)
{
  unsigned i, j;
  Matrix4<A> mat;

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
Matrix4<A>::
scale_matrix( A x_, A y, A z )
{
  zero();
  _data[0][0] = x_;
  _data[1][1] = y;
  _data[2][2] = z;
  _data[3][3] = A(1);
}


template <class A>
void
Matrix4<A>::
translation_matrix( A x_, A y, A z )
{
  // NOTE: uses OpenGL convention, which is the transpose of the usual
  // convention

  this->identity();
  _data[3][0] = x_;
  _data[3][1] = y;
  _data[3][2] = z;
}


template <class A>
void
Matrix4<A>::
rotation_matrix( A angle, A a0, A a1, A a2 )
{
  // Set *this to the matrix which rotates by 'angle' around axis (a0, a1, a2)
  // and center (0, 0, 0)

  // NOTE: uses OpenGL convention, which is the transpose of the usual
  // convention

  normalize(a0, a1, a2);

  A x = math::cos(angle);
  A x1 = A(1) - x;
  A y = math::sin(angle);

  _data[0][0] = x1*sqr(a0) + x;
  _data[0][1] = x1*a0*a1 + y*a2;
  _data[0][2] = x1*a0*a2 - y*a1;
  _data[0][3] = A(0);

  _data[1][0] = x1*a0*a1 - y*a2;
  _data[1][1] = x1*sqr(a1) + x;
  _data[1][2] = x1*a1*a2 + y*a0;
  _data[1][3] = A(0);

  _data[2][0] = x1*a0*a2 + y*a1;
  _data[2][1] = x1*a1*a2 - y*a0;
  _data[2][2] = x1*sqr(a2) + x;
  _data[2][3] = A(0);

  _data[3][0] = A(0);
  _data[3][1] = A(0);
  _data[3][2] = A(0);
  _data[3][3] = A(1);
}


template <class A>
void
Matrix4<A>::
rotation_matrix( A angle, A a0, A a1, A a2, A o0, A o1, A o2 )
{
  // Set *this to the matrix which rotates by 'angle' around axis (a0, a1, a2)
  // and center (o0, o1, o2)

  // NOTE: uses OpenGL convention, which is the transpose of the usual
  // convention

  rotation_matrix( angle, a0, a1, a2 );
  Matrix4<A> t1, t2;
  t1.translation_matrix(o0, o1, o2);
  t2.translation_matrix(-o0, -o1, -o2);
  mul(t1);
  mulleft(t2);
}


} // namespace math

#if defined(__sgi) && !defined(__GNUG__)
#pragma reset woff 1375 // The destructor for class is not virtual.
#endif

#endif // math_Matrix4_INCLUDED

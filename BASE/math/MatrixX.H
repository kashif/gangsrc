/* GANG Software
 * BASE/math/MatrixX.H
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

#ifndef math_MatrixX_INCLUDED
#define math_MatrixX_INCLUDED

#include <iostream>

#include "Math.H"
#include "VectorX.H"

namespace math {

#if !defined(NO_TMPL_FRIENDS)
#if (defined(__sgi) && _COMPILER_VERSION >= 730) || defined(__GNUG__)
#define NULL_TMPL_ARGS <>
#else
#define NULL_TMPL_ARGS
#endif

template<class A, uint N>
class MatrixX;

template<class A, uint N>
std::ostream &operator<<( std::ostream &o, MatrixX<A,N> const & );
#endif

/*
  Template matrix container class.
*/

template <class A, uint N>
class MatrixX
{
public:

  // void constructor
  MatrixX();

  // copy constructor
  MatrixX( MatrixX<A,N> const & );

  // constructor
  MatrixX( A const *a );

  // destructor
  ~MatrixX();

  // assignment operators
  MatrixX<A,N> &
  operator=( MatrixX<A,N> const & );

  //
  MatrixX<A,N> &
  operator=( A const *a );

  // reference to entry
  A * operator[]( uint );

  // reference to entry
  A const * operator[]( uint ) const;

  // set all entries of *this to 0
  void zero() { clear(); }
  // set all entries of *this to 0
  void clear();

  // set all entries of *this to a
  void set( A const & );

  // *this := identity MatrixX<A,N>
  void identity();

  // copy nth row of *this into a
  void getrow( VectorX<A, N> &, uint ) const;

  // copy nth column of *this into a
  void getcol( VectorX<A, N> &, uint ) const;

  // copy a into nth row of *this
  void putrow( VectorX<A, N> const &, uint  );

  // copy a into nth column of *this
  void putcol( VectorX<A, N> const &, uint );

  // negation: *this := - *this
  void neg();

  // negation *this := -a
  void neg( MatrixX<A,N> const & );

  // *this := a + b
  void add( MatrixX<A,N> const &, MatrixX<A,N> const &b );

  // *this += a
  void add( MatrixX<A,N> const &a );

  // *this += a
  void operator+=( MatrixX<A,N> const &a ) { add(a); }

  // *this := a - b
  void sub( MatrixX<A,N> const &, MatrixX<A,N> const & );

  // *this -= a
  void sub( MatrixX<A,N> const &a );

  // *this -= a
  void operator-=( MatrixX<A,N> const &a ) { sub(a); }

  // *this *= a
  void operator*=( A const & );

  // *this *= a
  void operator*=( MatrixX<A,N> const & );

  // scalar multiplication:
  // *this := a * b
  void mul( A const &, MatrixX<A,N> const &b );

  // scalar multiplication:
  // *this := a * b
  void mul( MatrixX<A,N> const &, A const &b );

  // scalar multiplication:
  // *this *= a
  void mul( A const &b );

  // vector multiplication
  // v := (*this) * v
  void mul( VectorX<A,N> &v ) const;

  // vector multiplication
  // v := v * (*this)
  void mulleft( VectorX<A,N> &v ) const;

  // matrix multiplication:
  // *this := a * b
  void mul( MatrixX<A,N> const &, MatrixX<A,N> const &b );

  // matrix multiplication:
  // *this *= a
  void mul( MatrixX<A,N> const &a );

  // matrix multiplication:
  // *this *= a
  void mulleft( MatrixX<A,N> const &a );

  // *this /= a
  void operator/=( A const & );

  // *this := a / b
  void div( MatrixX<A,N> const &, A const &b );

  // return trace( *this )
  A trace() const;

  // *this := transpose( *this )
  void transpose();

  // *this := transpose( a )
  void transpose( MatrixX<A,N> const & );

#if !defined(NO_TMPL_FRIENDS)
  // write a to stream o
  friend std::ostream & operator<< NULL_TMPL_ARGS
  ( std::ostream &o, MatrixX<A,N> const & );
#endif

  /* solves the linear system A.X=B.

     A:    n-by-n matrix of A's (already allocated) (input and output)
     n:    size of a (input)
     B:   right-hand-side and and solution (input and output)

     A is replaced by its LU-decomposition
  */
  int linear_solve( VectorX<A,N> &B );


  /* computes the inverse of a matrix.

      A_inv:  inverse of A (already allocated) (output)
      A:    n-by-n matrix of A's (already allocated) (input)
      n:    size of a (input)
  */
  int inv();
  int inv( MatrixX<A,N> const & );


  A det() const;


  /* replaces a by LU-decomposition. With pivoting.

      a:    n-by-n matrix of A's (already allocated) (input and output)
      n:    size of a (input)
      indx: row permutation index (already allocated) (output)
      d:    +1 or -1 according as permuation is even/odd (output)

      a and a_inv must be distinct
  */
  int LU_decomposition(VectorX<uint,N> &indx, int &d);


  /* LU_back_substitution.

      a:    n-by-n matrix of A's in LU form (input)
      n:    size of a (input)
      indx: row permutation index (already allocated) (input)
      b:    right-hand-side (array of n A's) (input and output)
  */
  int LU_back_substitution(
    VectorX<uint,N> const &indx,
    VectorX<A,N> &b );


  A *data() { return &_data[0][0]; }

protected:
  /* The elements x[][] sit in memory in the order
     x[0][0],..., x[0][N-1], x[1][0],....
   */
  A _data[N][N];
};


template <class A, uint N>
inline
MatrixX<A, N>::
MatrixX()
{
  clear();
}


template <class A, uint N>
inline
MatrixX<A, N>::
MatrixX( MatrixX<A,N> const &a )
{
  *this = a;
}


template <class A, uint N>
inline
MatrixX<A, N>::
MatrixX( A const *a )
{
  *this = a;
}


template <class A, uint N>
inline
MatrixX<A, N>::
~MatrixX()
{
}


template <class A, uint N>
inline
A *
MatrixX<A, N>::
operator[]( uint n )
{
  return _data[n];
}


template <class A, uint N>
inline
A const *
MatrixX<A, N>::
operator[]( uint n ) const
{
  return _data[n];
}


template <class A, uint N>
MatrixX<A, N> &
MatrixX<A, N>::
operator=(MatrixX<A,N> const &a)
{
  uint i, j;

  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N; j++)
    {
      _data[i][j] = a._data[i][j];
    }
  }

  return *this;
}

template <class A, uint N>
MatrixX<A, N> &
MatrixX<A, N>::
operator=(A const *a)
{
  uint i, j;

  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N; j++)
    {
      _data[i][j] = a[i * N + j];
    }
  }

  return *this;
}


template <class A, uint N>
void
MatrixX<A, N>::
clear()
{
  uint i, j;

  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N; j++)
    {
      _data[i][j] = A(0);
    }
  }
}


template <class A, uint N>
void
MatrixX<A, N>::
set(A const &a)
{
  uint i, j;

  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N; j++)
    {
      _data[i][j] = a;
    }
  }
}


template <class A, uint N>
void
MatrixX<A, N>::
getrow(VectorX<A, N> &a, uint n) const
{
  uint i;

  for (i = 0; i < N; i++)
  {
    a._data[i] = _data[n][i];
  }
}


template <class A, uint N>
void
MatrixX<A, N>::
getcol(VectorX<A, N> &a, uint n) const
{
  uint i;

  for (i = 0; i < N; i++)
  {
    a._data[i] = _data[i][n];
  }
}


template <class A, uint N>
void
MatrixX<A, N>::
putrow(VectorX<A, N> const &a, uint n)
{
  uint i;

  for (i = 0; i < N; i++)
  {
    _data[n][i] = a._data[i];
  }
}


template <class A, uint N>
void
MatrixX<A, N>::
putcol(VectorX<A, N> const &a, uint n)
{
  uint i;

  for (i = 0; i < N; i++)
  {
    _data[i][n] = a._data[i];
  }
}


template <class A, uint N>
void
MatrixX<A, N>::
identity()
{
  clear();
  uint i;

  for (i = 0; i < N; i++)
  {
    _data[i][i] = 1;
  }
}


template <class A, uint N>
void
MatrixX<A, N>::
transpose()
{
  A t;
  uint i, j;

  for (i = 0; i < N - 1; i++)
  {
    for (j = i + 1; j < N; j++)
    {
      t = _data[i][j];
      _data[i][j] = _data[j][i];
      _data[j][i] = t;
    }
  }
}


template <class A, uint N>
void
MatrixX<A, N>::
transpose(MatrixX<A,N> const &a)
{
  uint i, j;

  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N; j++)
    {
      _data[i][j] = a._data[j][i];
    }
  }
}


template <class A, uint N>
void
MatrixX<A, N>::
neg()
{
  uint i, j;

  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N; j++)
    {
      _data[i][j] = -_data[i][j];
    }
  }
}


template <class A, uint N>
void
MatrixX<A, N>::
neg(MatrixX<A,N> const &a)
{
  uint i, j;
  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N; j++)
    {
      _data[i][j] = -a._data[i][j];
    }
  }
}


template <class A, uint N>
void
MatrixX<A, N>::
add(MatrixX<A,N> const &a)
{
  uint i, j;

  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N; j++)
    {
      _data[i][j] += a._data[i][j];
    }
  }
}


template <class A, uint N>
void
MatrixX<A, N>::
add(MatrixX<A,N> const &a, MatrixX<A,N> const &b)
{
  uint i, j;

  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N; j++)
    {
      _data[i][j] = a._data[i][j] + b._data[i][j];
    }
  }
}


template <class A, uint N>
void
MatrixX<A, N>::
sub(MatrixX<A,N> const &a)
{
  uint i, j;
  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N; j++)
    {
      _data[i][j] -= a._data[i][j];
    }
  }
}


template <class A, uint N>
void
MatrixX<A, N>::
sub(MatrixX<A,N> const &a, MatrixX<A,N> const &b)
{
  uint i, j;

  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N; j++)
    {
      _data[i][j] = a._data[i][j] - b._data[i][j];
    }
  }
}


template <class A, uint N>
void
MatrixX<A, N>::
operator*=(A const &a)
{
  uint i, j;

  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N; j++)
    {
      _data[i][j] *= a;
    }
  }
}


template <class A, uint N>
void
MatrixX<A, N>::
operator*=(MatrixX<A,N> const &a)
{
  MatrixX<A,N> r;
  A s;
  uint i, j, k;

  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N; j++)
    {
      s = 0;
      for (k = 0; k < N; k++)
	s += _data[i][k] * a._data[k][j];
      r._data[i][j] = s;
    }
  }

  *this = r;
}


template <class A, uint N>
void
MatrixX<A, N>::
mul(A const &a, MatrixX<A,N> const &b)
{
  uint i, j;

  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N; j++)
    {
      _data[i][j] = a * b._data[i][j];
    }
  }
}


template <class A, uint N>
void
MatrixX<A, N>::
mul(MatrixX<A,N> const &a, A const &b)
{
  uint i, j;

  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N; j++)
    {
      _data[i][j] = a._data[i][j] * b;
    }
  }
}


template <class A, uint N>
void
MatrixX<A, N>::
mul( A const &a )
{
  uint i, j;

  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N; j++)
    {
      _data[i][j] *= a;
    }
  }
}

template <class A, uint N>
void
MatrixX<A, N>::
mul(MatrixX<A,N> const &a, MatrixX<A,N> const &b)
{
  MatrixX<A,N> r;
  A s;
  uint i, j, k;

  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N; j++)
    {
      s = A(0);
      for (k = 0; k < N; k++)
      {
	s += a._data[i][k] * b._data[k][j];
      }
      r._data[i][j] = s;
    }
  }

  *this = r;
}

template <class A, uint N>
void
MatrixX<A, N>::
mul(MatrixX<A,N> const &a)
{
  mul( *this, a );
}

template <class A, uint N>
void
MatrixX<A, N>::
mulleft(MatrixX<A,N> const &a)
{
  MatrixX<A,N> tmp;
  tmp.mul( a, *this );
  *this = tmp;
}

template <class A, uint N>
void
MatrixX<A, N>::
mul( VectorX<A,N> &v ) const
{
  // v := (*this).v

  VectorX<A,N> tmp;

  uint i, j;

  A s;
  for (i = 0; i < N; i++)
  {
    s = A(0);
    for (j = 0; j < N; j++)
    {
      s += _data[i][j] * v[j];
    }
    tmp[i] = s;
  }
  v = tmp;
}

template <class A, uint N>
void
MatrixX<A, N>::
mulleft( VectorX<A,N> &v ) const
{
  // v := v . (*this)

  VectorX<A,N> tmp;

  uint i, j;

  A s;
  for (i = 0; i < N; i++)
  {
    s = A(0);
    for (j = 0; j < N; j++)
    {
      s += _data[j][i] * v[j];
    }
    tmp[i] = s;
  }
  v = tmp;
}

template <class A, uint N>
void
MatrixX<A, N>::
operator/=(A const &a)
{
  uint i, j;

  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N; j++)
    {
      _data[i][j] /= a;
    }
  }
}

template <class A, uint N>
void
MatrixX<A, N>::
div(MatrixX<A,N> const &a, A const &b)
{
  uint i, j;

  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N; j++)
    {
      _data[i][j] = a._data[i][j] / b;
    }
  }
}

template <class A, uint N>
A
MatrixX<A, N>::
trace() const
{
  A a(0);
  uint i;

  for (i = 0; i < N; i++)
  {
    a += _data[i][i];
  }

  return a;
}


#if !defined(NO_TMPL_FRIENDS)
template <class A, uint N>
std::
ostream &
operator<<(
 std::ostream &o, MatrixX<A, N> const &a)
{
  uint i, j;

  o << "{";
  for (i = 0; i < N; i++)
  {
    o << "{";
    for (j = 0; j < N; j++)
    {
      o << a._data[i][j];
      if (j < N - 1)
	o << ", ";
    }
    o << "}";
    if (i < N - 1)
      o << ",\n";
  }
  o << "}\n";

  return o;
}
#endif

template<class A, uint N>
int
MatrixX<A,N>::
LU_decomposition(VectorX<uint,N> &indx, int &d)
{
  double const TINY = 1.0e-20;
  uint imax = 0U;
  A big, dum, sum, temp;
  int err = 0;

  VectorX<A,N> vv;
  d = 1;
  uint i;
  for (i = 0; i < N; i++)
  {
    uint j;
    big = A(0);
    for (j = 0; j < N; j++)
    {
      if ((temp = math::abs(_data[i][j])) > big)
      {
        big = temp;
      }
    }
    if (big == A(0))
    {
      err = 1;
      // singular
      goto end;
    }
    vv[i] = A(1) / big;
  }
  uint j;
  for (j = 0; j < N; j++)
  {
    for (i = 0; i < j; i++)
    {
      sum = _data[i][j];
      uint k;
      for (k = 0; k < i; k++)
      {
        sum -= _data[i][k] * _data[k][j];
      }
      _data[i][j] = sum;
    }
    big = A(0);
    for (i = j; i < N; i++)
    {
      sum = _data[i][j];
      uint k;
      for (k = 0; k < j; k++)
      {
        sum -= _data[i][k] * _data[k][j];
      }
      _data[i][j] = sum;
      if ((dum = vv[i] * math::abs(sum)) >= big)
      {
        big = dum;
        imax = i;
      }
    }
    if (j != imax)
    {
      uint k;
      for (k = 0; k < N; k++)
      {
        dum = _data[imax][k];
        _data[imax][k] = _data[j][k];
        _data[j][k] = dum;
      }
      d = -d;
      vv[imax] = vv[j];
    }
    indx[j] = imax;
    if (_data[j][j] == A(0))
    {
      _data[j][j] = TINY;
    }
    if (j != N)
    {
      if ( math::abs(_data[j][j]) < 1.0e-10 ) { abort(); }
      dum = A(1) / (_data[j][j]);
      for (i = j + 1; i < N; i++)
      {
        _data[i][j] *= dum;
      }
    }
  }
  end:
  return err;
}

template<class A, uint N>
int
MatrixX<A,N>::
LU_back_substitution(
  VectorX<uint,N> const &indx,
  VectorX<A,N> &b )
{
  uint i;
  uint ii = N;
  uint ip, j;
  A sum;

  for (i = 0; i < N; i++)
  {
    ip = indx[i];
    sum = b[ip];
    b[ip] = b[i];

    if (ii != N)
    {
      for (j = ii; j <= i - 1; j++)
      {
        sum -= _data[i][j] * b[j];
      }
    }
    else if (sum != A(0))
    {
      ii = i;
    }
    b[i] = sum;
  }

  int ix;
  for (ix = N-1; ix >= 0; ix--)
  {
    sum = b[ix];
    for (j = ix + 1; j < N; j++)
    {
      sum -= _data[ix][j] * b[j];
    }
    if ( math::effectively_zero(_data[ix][ix]) ) { abort(); }
    b[ix] = sum / _data[ix][ix];
  }
  return 0;
}


template<class A, uint N>
int
MatrixX<A,N>::
linear_solve( VectorX<A,N> &B )
{
  int *indx = new int[n];
  A d;
  int err = LU_decomposition( a, n, indx, &d );
  if ( err != 0 ) { return 1; }
  LU_back_substitution( a, n, indx, b );
  return 0;
}

template<class A, uint N>
int
MatrixX<A,N>::
inv()
{
  return inv(*this);
}

template<class A, uint N>
int
MatrixX<A,N>::
inv( MatrixX<A,N> const &a_ )
{
  MatrixX<A,N> a = a_;
  identity();

  VectorX<uint,N> indx;
  int d;
  int err = a.LU_decomposition(indx, d);
  if ( err != 0 ) { return 1; }

  VectorX<A,N> b;

  uint j;
  for (j = 0; j < N; j++)
  {
    b.set(A(0));
    b[j] = A(1);
    a.LU_back_substitution( indx, b );
    uint i;
    for ( i = 0; i < N; i++ )
    {
      _data[i][j] = b[i];
    }
  }
  return 0;
}

template<class A, uint N>
A
MatrixX<A,N>::
det() const
{
  MatrixX<A,N> a = *this;

  VectorX<uint,N> indx;
  int s;
  int err = a.LU_decomposition(indx, s);
  if (err) { return 0.0f; }

  A d(1);
  uint i;
  for ( i = 0; i < N; i++ )
  {
    d *= a[i][i];
  }

  return d;
}

} // namespace math

#endif // math_MatrixX_INCLUDED

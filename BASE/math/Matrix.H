/* GANG Software
 * BASE/math/Matrix.H
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

#ifndef math_Matrix_INCLUDED
#define math_Matrix_INCLUDED

#include <limits.h>
#include <iostream>
#include "base/Exception.H"
#include "Math.H"
#include "Vector.H"

namespace math {

#if !defined(NO_TMPL_FRIENDS)
#if (defined(__sgi) && _COMPILER_VERSION >= 730) || defined(__GNUG__)
#define NULL_TMPL_ARGS <>
#else
#define NULL_TMPL_ARGS
#endif

template<class A>
class Matrix;

template<class A>
std::ostream &operator<<( std::ostream &o, Matrix<A> const & );
#endif

/*
   Template matrix container class.
 */
template <class A>
class Matrix
{
public:

  // void constructor
  Matrix();

  // copy constructor
  Matrix( Matrix<A> const & );

  // destructor
  ~Matrix();

  // assignment operator
  Matrix<A> &operator=( Matrix<A> const & );

  // Reference to entry.
  A *operator[]( uint );

  // Reference to entry.
  A const *operator[]( uint ) const;

  bool isnan() const;

  // Set all entries of *this to A(0).
  void clear() { set( A(0) ); }

  // allocate to n-by-n; Set all entries of *this to A(0).
  void clear(uint n) { set( A(0), n ); }

  // Set all entries of *this to A(0).
  void zero() { clear(); }

  // Set all entries of *this to A(0).
  void zero(uint n) { clear(n); }


  // Set all entries of *this to a.
  void set( A const & );

  // allocate to n-by-n; Set all entries of *this to a.
  void set( A const &, uint n );

  // *this := identity matrix
  void identity();
  // allocate to n-by-n; *this := identity matrix
  void identity(uint n);

#if 0
  // copy nth row of *this into a
  void getrow( Vector<A> &, uint ) const;

  // copy nth column of *this into a
  void getcol( Vector<A> &, uint ) const;

  // copy a into nth row of *this
  void putrow( Vector<A> const &, uint  );

  // copy a into nth column of *this
  void putcol( Vector<A> const &, uint );
#endif
  // negation: *this := - *this
  void neg();

  // negation *this := -a
  void neg( Matrix<A> const & );

  // *this := a + b
  void add( Matrix<A> const &, Matrix<A> const &b );

  // *this += a
  void add( Matrix<A> const &a );

  // *this += a
  void operator+=( Matrix<A> const &a ) { add(a); }

  // *this := a - b
  void sub( Matrix<A> const &, Matrix<A> const & );

  // *this -= a
  void sub( Matrix<A> const &a );

  // *this -= a
  void operator-=( Matrix<A> const &a ) { sub(a); }

  // *this *= a
  void operator*=( A const & );

  // *this *= a
  void operator*=( Matrix<A> const & );

  // scalar multiplication:
  // *this := a * b
  void mul( A const &, Matrix<A> const &b );

  // scalar multiplication:
  // *this := a * b
  void mul( Matrix<A> const &, A const &b );

  // scalar multiplication:
  // *this *= a
  void mul( A const &b );

  // vector multiplication
  // v := (*this) * v
  void mul( Vector<A> &v ) const;

  // vector multiplication
  // v := (*this) * v
  void mulleft( Vector<A> &v ) const;

  // matrix multiplication:
  // *this := a * b
  void mul( Matrix<A> const &, Matrix<A> const &b );

  // matrix multiplication:
  // *this *= a
  void mul( Matrix<A> const &a );

  // matrix multiplication:
  // *this *= a
  void mulleft( Matrix<A> const &a );

  // *this /= a
  void operator/=( A const & );

  // *this := a / b
  void div( Matrix<A> const &, A const &b );

  // return trace( *this )
  A trace() const;

  // *this := transpose( *this )
  void transpose();

  // *this := transpose( a )
  void transpose( Matrix<A> const & );

#if !defined(NO_TMPL_FRIENDS)
  // write a to stream o
  friend std::ostream & operator<< NULL_TMPL_ARGS
  ( std::ostream &o, Matrix<A> const & );
#endif

  /* solves the linear system A.X=B.

     A:    n-by-n matrix of A's (already allocated) (input and output)
     n:    size of a (input)
     B:   right-hand-side and and solution (input and output)

     A is replaced by its LU-decomposition
  */
  void linear_solve( Vector<A> &b )
    throw( base::Exception );


  /* computes the inverse of a matrix.

      A_inv:  inverse of A (already allocated) (output)
      A:    n-by-n matrix of A's (already allocated) (input)
      n:    size of a (input)
  */
  void inv()
    throw( base::Exception );
  void inv( Matrix<A> const & )
    throw( base::Exception );


  A det() const
    throw( base::Exception );


  /* replaces a by LU-decomposition. With pivoting.

      a:    n-by-n matrix of A's (already allocated) (input and output)
      n:    size of a (input)
      indx: row permutation index (already allocated) (output)
      d:    +1 or -1 according as permuation is even/odd (output)

      a and a_inv must be distinct
  */
  void LU_decomposition(Vector<uint> &indx, int &d)
    throw( base::Exception );

  /* LU_back_substitution.

      a:    n-by-n matrix of A's in LU form (input)
      n:    size of a (input)
      indx: row permutation index (already allocated) (input)
      b:    right-hand-side (array of n A's) (input and output)
  */
  void LU_back_substitution(
    Vector<uint> const &indx,
    Vector<A> &b )
    throw( base::Exception );


  A *data() { return _data; }
  A const *data() const { return _data; }
  uint dim() const { return _len; }

  void allocate( uint len );

protected:

  uint _len;
  A *_data;

  A &el(uint i, uint j)
    { return _data[ind(i,j)]; }
  A const &el(uint i, uint j) const
    { return _data[ind(i,j)]; }

  uint ind( uint i, uint j) const
    { return i*_len + j; }
};

template <class A>
inline
Matrix<A>::
Matrix()
    :
    _len(0U),
    _data( (A *)0 )
{
  _data = (A *)0;
}


template <class A>
inline
Matrix<A>::
Matrix( Matrix<A> const &a )
    :
    _len(a._len),
    _data( (A *)0 )
{
  if (a._len == 0U) { return; }

  _data = new A[math::sqr(a._len)];

  uint i, j;
  for (i = 0; i < _len; i++)
  {
    for (j = 0; j < _len; j++)
    {
      el(i,j) = a.el(i,j);
    }
  }
}

template <class A>
inline
Matrix<A>::
~Matrix()
{
  allocate(0);
}


template <class A>
inline
A *
Matrix<A>::
operator[]( uint i )
{
  DIE_IF( i >= sqr(_len) );

  return _data + ind(i,0U);
}


template <class A>
inline
A const *
Matrix<A>::
operator[]( uint i ) const
{
  DIE_IF( i >= sqr(_len) );

  return _data + ind(i,0U);
}


template <class A>
void
Matrix<A>::
allocate( uint len )
{
  if ( _len != len )
  {
    if ( _data != (A *)0 )
    {
      delete [] _data;
    }
    if ( len > 0 )
    {
      _data = new A[sqr(len)];
    }
    else
    {
      _data = (A *)0;
    }
    _len = len;
  }
}

template <class A>
Matrix<A> &
Matrix<A>::
operator=(Matrix<A> const &a)
{
  if ( this == &a ) { return *this; }

  allocate(a._len);

  uint i, j;
  for (i = 0; i < _len; i++)
  {
    for (j = 0; j < _len; j++)
    {
      el(i,j) = a.el(i,j);
    }
  }

  return *this;
}

template <class A>
void
Matrix<A>::
set(A const &a)
{
  uint i, j;

  for (i = 0; i < _len; i++)
  {
    for (j = 0; j < _len; j++)
    {
      el(i,j) = a;
    }
  }
}

template <class A>
void
Matrix<A>::
set(A const &a, uint n)
{
  allocate(n);
  set(a);
}

#if 0
template <class A>
void
Matrix<A>::
getrow(Vector<A> &a, uint n) const
{
  uint i;

  for (i = 0; i < _len; i++)
  {
    a._data[i] = el(n,i);
  }
}


template <class A>
void
Matrix<A>::
getcol(Vector<A> &a, uint n) const
{
  uint i;

  for (i = 0; i < _len; i++)
  {
    a._data[i] = el(i,n);
  }
}


template <class A>
void
Matrix<A>::
putrow(Vector<A> const &a, uint n)
{
  uint i;

  for (i = 0; i < _len; i++)
  {
    el(n,i) = a._data[i];
  }
}


template <class A>
void
Matrix<A>::
putcol(Vector<A> const &a, uint n)
{
  uint i;

  for (i = 0; i < _len; i++)
  {
    el(i,n) = a._data[i];
  }
}
#endif


template <class A>
void
Matrix<A>::
identity()
{
  clear();
  uint i;

  for (i = 0; i < _len; i++)
  {
    el(i,i) = 1;
  }
}

template <class A>
void
Matrix<A>::
identity(uint n)
{
  clear(n);
  identity();
}

template <class A>
void
Matrix<A>::
transpose()
{
  WARN_IF( _len == 0U );

  A t;
  uint i, j;

  for (i = 0; i < _len - 1; i++)
  {
    for (j = i + 1; j < _len; j++)
    {
      t = el(i,j);
      el(i,j) = el(j,i);
      el(j,i) = t;
    }
  }
}


template <class A>
void
Matrix<A>::
transpose(Matrix<A> const &a)
{
  DIE_IF( a._len == 0 );
  allocate(a._len);

  uint i, j;

  for (i = 0; i < _len; i++)
  {
    for (j = 0; j < _len; j++)
    {
      el(i,j) = a.el(j,i);
    }
  }
}


template <class A>
void
Matrix<A>::
neg()
{
  DIE_IF( _len == 0U );

  uint i, j;

  for (i = 0; i < _len; i++)
  {
    for (j = 0; j < _len; j++)
    {
      el(i,j) = -el(i,j);
    }
  }
}


template <class A>
void
Matrix<A>::
neg(Matrix<A> const &a)
{
  DIE_IF( a._len == 0 );
  allocate( a._len );

  uint i, j;
  for (i = 0; i < _len; i++)
  {
    for (j = 0; j < _len; j++)
    {
      el(i,j) = -a.el(i,j);
    }
  }
}


template <class A>
void
Matrix<A>::
add(Matrix<A> const &a)
{
  DIE_IF( _len == 0U );
  DIE_IF( _len != a._len);

  uint i, j;

  for (i = 0; i < _len; i++)
  {
    for (j = 0; j < _len; j++)
    {
      el(i,j) += a.el(i,j);
    }
  }
}


template <class A>
void
Matrix<A>::
add(Matrix<A> const &a, Matrix<A> const &b)
{
  DIE_IF( a._len == 0 );
  DIE_IF( a._len != b._len);

  allocate( a._len );

  uint i, j;

  for (i = 0; i < _len; i++)
  {
    for (j = 0; j < _len; j++)
    {
      el(i,j) = a.el(i,j) + b.el(i,j);
    }
  }
}


template <class A>
void
Matrix<A>::
sub(Matrix<A> const &a)
{
  DIE_IF( _len == 0U );
  DIE_IF( _len != a._len);

  uint i, j;
  for (i = 0; i < _len; i++)
  {
    for (j = 0; j < _len; j++)
    {
      el(i,j) -= a.el(i,j);
    }
  }
}


template <class A>
void
Matrix<A>::
sub(Matrix<A> const &a, Matrix<A> const &b)
{
  DIE_IF( a._len == 0 );
  DIE_IF( a._len != b._len);

  allocate( a._len );

  uint i, j;

  for (i = 0; i < _len; i++)
  {
    for (j = 0; j < _len; j++)
    {
      el(i,j) = a.el(i,j) - b.el(i,j);
    }
  }
}


template <class A>
void
Matrix<A>::
operator*=(A const &a)
{
  DIE_IF( _len == 0U );

  uint i, j;

  for (i = 0; i < _len; i++)
  {
    for (j = 0; j < _len; j++)
    {
      el(i,j) *= a;
    }
  }
}


template <class A>
void
Matrix<A>::
operator*=(Matrix<A> const &a)
{
  DIE_IF( _len == 0U );
  DIE_IF( _len != a._len);

  Matrix<A> r;
  A s;
  uint i, j, k;

  for (i = 0; i < _len; i++)
  {
    for (j = 0; j < _len; j++)
    {
      s = 0;
      for (k = 0; k < _len; k++)
	s += el(i,k) * a.el(k,j);
      r.el(i,j) = s;
    }
  }

  *this = r;
}


template <class A>
void
Matrix<A>::
mul(A const &a, Matrix<A> const &b)
{
  DIE_IF( a._len == 0 );
  DIE_IF( a._len != b._len);

  allocate( a._len );

  uint i, j;

  for (i = 0; i < _len; i++)
  {
    for (j = 0; j < _len; j++)
    {
      el(i,j) = a * b.el(i,j);
    }
  }
}


template <class A>
void
Matrix<A>::
mul(Matrix<A> const &a, A const &b)
{
  DIE_IF( _len == 0U );
  DIE_IF( _len != a._len);
  DIE_IF( _len != b._len);

  uint i, j;

  for (i = 0; i < _len; i++)
  {
    for (j = 0; j < _len; j++)
    {
      el(i,j) = a.el(i,j) * b;
    }
  }
}


template <class A>
void
Matrix<A>::
mul( A const &a )
{
  DIE_IF( _len == 0U );
  DIE_IF( _len != a._len);

  uint i, j;

  for (i = 0; i < _len; i++)
  {
    for (j = 0; j < _len; j++)
    {
      el(i,j) *= a;
    }
  }
}

template <class A>
void
Matrix<A>::
mul(Matrix<A> const &a, Matrix<A> const &b)
{
  DIE_IF( a._len == 0U );
  DIE_IF( a._len != b._len );

  allocate(a._len);

  Matrix<A> r;
  r.allocate(a._len);

  A s;
  uint i, j, k;

  for (i = 0; i < _len; i++)
  {
    for (j = 0; j < _len; j++)
    {
      s = A(0);
      for (k = 0; k < _len; k++)
      {
	s += a.el(i,k) * b.el(k,j);
      }
      r.el(i,j) = s;
    }
  }

  *this = r;
}

template <class A>
void
Matrix<A>::
mul(Matrix<A> const &a)
{
  DIE_IF( _len == 0U );
  DIE_IF( a._len == 0U );
  DIE_IF( _len != a._len);

  mul( *this, a );
}

template <class A>
void
Matrix<A>::
mulleft(Matrix<A> const &a)
{
  DIE_IF( _len == 0U );
  DIE_IF( _len != a._len);

  Matrix<A> tmp;
  tmp.mul( a, *this );
  *this = tmp;
}

template <class A>
void
Matrix<A>::
mul( Vector<A> &v ) const
{
  DIE_IF( _len == 0U );
  DIE_IF( _len != v.length() );

  // v := (*this).v

  Vector<A> tmp;
  tmp.allocate( _len );

  uint i, j;

  A s;
  for (i = 0; i < _len; i++)
  {
    s = A(0);
    for (j = 0; j < _len; j++)
    {
      s += el(i,j) * v[j];
    }
    tmp[i] = s;
  }
  v = tmp;
}

template <class A>
void
Matrix<A>::
mulleft( Vector<A> &v ) const
{
  DIE_IF( _len == 0U );
  DIE_IF( _len != v.length() );

  // v := v . (*this)

  Vector<A> tmp;
  tmp.allocate( _len );

  uint i, j;

  A s;
  for (i = 0; i < _len; i++)
  {
    s = A(0);
    for (j = 0; j < _len; j++)
    {
      s += el(j,i) * v[j];
    }
    tmp[i] = s;
  }
  v = tmp;
}

template <class A>
void
Matrix<A>::
operator/=(A const &a)
{
  DIE_IF( _len == 0U );

  uint i, j;

  for (i = 0; i < _len; i++)
  {
    for (j = 0; j < _len; j++)
    {
      el(i,j) /= a;
    }
  }
}

template <class A>
void
Matrix<A>::
div(Matrix<A> const &a, A const &b)
{
  DIE_IF( a._len == 0U );

  allocate( a._len );

  uint i, j;

  for (i = 0; i < _len; i++)
  {
    for (j = 0; j < _len; j++)
    {
      el(i,j) = a.el(i,j) / b;
    }
  }
}

template <class A>
A
Matrix<A>::
trace() const
{
  DIE_IF( _len == 0U );

  A a(0);
  uint i;

  for (i = 0; i < _len; i++)
  {
    a += el(i,i);
  }

  return a;
}


#if !defined(NO_TMPL_FRIENDS)
template <class A>
std::
ostream &
operator<<(std::
ostream &o, Matrix<A> const &a)
{
  DIE_IF( a._len == 0U );

  uint i, j;

  o << "{";
  for (i = 0; i < a._len; i++)
  {
    o << "{";
    for (j = 0; j < a._len; j++)
    {
      o << a.el(i,j);
      if (j < a._len - 1)
	o << ", ";
    }
    o << "}";
    if (i < a._len - 1)
      o << ",\n";
  }
  o << "}\n";

  return o;
}
#endif

template<class A>
void
Matrix<A>::
LU_decomposition(Vector<uint> &indx, int &d)
  throw (base::Exception)
{
  double const TINY = 1.0e-20;
  uint imax = 0;
  A big, dum, sum, temp;

  Vector<A> vv;
  vv.allocate( _len );

  d = 1;
  uint i;
  for (i = 0; i < _len; i++)
  {
    uint j;
    big = A(0);
    for (j = 0; j < _len; j++)
    {
      if ((temp = math::abs(el(i,j))) > big)
      {
        big = temp;
      }
    }
    if (big == A(0))
    {
      throw base::Exception( "LU_decomposition failed: singular" );
    }
    vv[i] = A(1) / big;
  }
  uint j;
  for (j = 0; j < _len; j++)
  {
    for (i = 0; i < j; i++)
    {
      sum = el(i,j);
      uint k;
      for (k = 0; k < i; k++)
      {
        sum -= el(i,k) * el(k,j);
      }
      el(i,j) = sum;
    }
    big = A(0);
    for (i = j; i < _len; i++)
    {
      sum = el(i,j);
      uint k;
      for (k = 0; k < j; k++)
      {
        sum -= el(i,k) * el(k,j);
      }
      el(i,j) = sum;
      if ((dum = vv[i] * math::abs(sum)) >= big)
      {
        big = dum;
        imax = i;
      }
    }
    if (j != imax)
    {
      uint k;
      for (k = 0; k < _len; k++)
      {
        dum = el(imax,k);
        el(imax,k) = el(j,k);
        el(j,k) = dum;
      }
      d = -d;
      vv[imax] = vv[j];
    }
    indx[j] = imax;
    if (el(j,j) == A(0))
    {
      el(j,j) = TINY;
    }
    if (j != _len)
    {
      if ( math::effectively_zero( el(j,j) ) )
      {
        throw base::Exception( "LU_decomposition failed" );
      }
      dum = A(1) / (el(j,j));
      for (i = j + 1; i < _len; i++)
      {
        el(i,j) *= dum;
      }
    }
  }
}

template<class A>
void
Matrix<A>::
LU_back_substitution(
  Vector<uint> const &indx,
  Vector<A> &b )
  throw (base::Exception)
{
  DIE_IF( _len == 0U );

  uint i;
  uint ii = UINT_MAX;
  uint ip, j;
  A sum;

  for (i = 0; i < _len; i++)
  {
    ip = indx[i];
    sum = b[ip];
    b[ip] = b[i];

    if (ii != UINT_MAX)
    {
      for (j = ii; j <= i - 1; j++)
      {
        sum -= el(i,j) * b[j];
      }
    }
    else if (sum != A(0))
    {
      ii = i;
    }
    b[i] = sum;
  }

  int ix;
  for (ix = _len-1; ix >= 0; ix--)
  {
    sum = b[ix];
    for (j = ix + 1; j < _len; j++)
    {
      sum -= el(ix,j) * b[j];
    }
    if ( math::effectively_zero( el(ix,ix) ) )
    {
      throw base::Exception( "LU_back_substitution failed" );
    }
    b[ix] = sum / el(ix,ix);
  }
}

template<class A>
void
Matrix<A>::
linear_solve( Vector<A> &b )
  throw (base::Exception)
{
  DIE_IF( _len == 0U );

  Vector<uint> indx;
  indx.allocate(_len);
  int d;
  LU_decomposition( indx, d );
  LU_back_substitution( indx, b );
}

template<class A>
void
Matrix<A>::
inv()
  throw (base::Exception)
{
  DIE_IF( _len == 0U );
  return inv(*this);
}

template<class A>
void
Matrix<A>::
inv( Matrix<A> const &a_ )
  throw (base::Exception)
{
  DIE_IF( a_._len == 0U );

  allocate( a_._len );

  Matrix<A> a = a_;
  identity();

  Vector<uint> indx;
  indx.allocate(_len);

  int d;
  a.LU_decomposition(indx, d);

  Vector<A> b;
  b.allocate(_len);

  uint j;
  for (j = 0; j < _len; j++)
  {
    b.set(A(0));
    b[j] = A(1);
    a.LU_back_substitution( indx, b );

    uint i;
    for ( i = 0; i < _len; i++ )
    {
      el(i,j) = b[i];
    }
  }
}

template<class A>
A
Matrix<A>::
det() const
  throw (base::Exception)
{
  DIE_IF( _len == 0U );

  Matrix<A> a = *this;

  Vector<uint> indx;
  indx.allocate(_len);

  int s;
  a.LU_decomposition(indx, s);

  A d(1);
  uint i;
  for ( i = 0; i < _len; i++ )
  {
    d *= a[i][i];
  }

  return d;
}

template<class A>
bool
Matrix<A>::
isnan() const
{
  // NOTE: this prevents Matrix<int>
  uint i;
  for ( i = 0; i < math::sqr(_len); i++ )
  {
    if (math::isnan(_data[i])) { return true; }
  }
  return false;
}

} // namespace math

#endif // math_Matrix_INCLUDED

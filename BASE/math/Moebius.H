/* GANG Software
 * BASE/math/Moebius.H
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

#ifndef math_Moebius_INCLUDED
#define math_Moebius_INCLUDED

#include <iostream>

namespace math {

#if !defined(NO_TMPL_FRIENDS)
#if (defined(__sgi) && _COMPILER_VERSION >= 730) || defined(__GNUG__)
#define NULL_TMPL_ARGS <>
#else
#define NULL_TMPL_ARGS
#endif

template <class A>
class Moebius;

template <class A>
std::ostream &operator<<( std::ostream &, Moebius<A> const &);
#endif

/*
  Moebius (fractional linear) transforms (a x + b)(c x + d)^(-1)
  Modified from code by J. Lawrence.
*/

template <class A>
class Moebius
{
public:
  typedef typename A::Real Real;

  Moebius();
  Moebius( Moebius const &f );
  Moebius &operator=( Moebius const &f );

  // coefficeients (a x + b)(c x + d)^(-1)
  const A &a() const { return _a; }
  const A &b() const { return _b; }
  const A &c() const { return _c; }
  const A &d() const { return _d; }

  // *this := 1
  void identity();

  // *this := (*this) * a
  void mul( Moebius const &a );

  // *this := a * b
  void mul( Moebius const &a, Moebius const &b );

  // *this := a * (*this)
  void mulleft( Moebius const &a );

  // *this := a^(-1)
  void invert( Moebius const &a );

  // *this := (*this)^(-1)
  void invert();

  /* Sets *this to a rotation FLT
     This FLT is the element of SO(4) which
     rotates the (1,v) plane by the angle a
     and rotates the (1,v)-perp plane by the angle b
     The orientation of the FLT is positive with 1 rotating toward v
     NOTE: v = quat(0,x,y,z) must have length one
  */
  void rotation( Real a, Real b, Real x, Real y, Real z );

  /* Sets *this to a rotation FLT
     This FLT is the element of SO(4) which
     rotates the (s,t) plane by angle a
     and rotates the (s,t)-perp plane by angleb
     Tthe orientation of the FLT is positive with s rotating toward v
     NOTE: s, t must be orthonormal
  */
  void rotation( Real a, Real b, A const &s, A const &t );

  /* sets *this to a translation FLT
     {{1, q},{0, 1}}, where q = quat(r,x,y,z)
  */
  void translation( Real r, Real x, Real y, Real z );

  /* sets *this to an inversion FLT
     {{1, 0},{q, 1}}, where q = quat(r,x,y,z)
  */
  void inversion( Real r, Real x, Real y, Real z );

  /* sets *this to an scale FLT
     (a,b,c,d) = (s,0,0,1)
  */
  void scale( Real s );

  // apply *this to x
  void apply( A &x );

#if !defined(NO_TMPL_FRIENDS)
  friend std::ostream &operator<< NULL_TMPL_ARGS
  ( std::ostream &, Moebius<A> const &);
#endif

  A _a, _b, _c, _d;
};

template< class A >
Moebius<A>::
Moebius()
    :
    _a(1), _b(0), _c(0), _d(1)
{
}

template< class A >
Moebius<A>::
Moebius( Moebius const &f )
    :
    _a(f._a), _b(f._b), _c(f._c), _d(f._d)
{
}

template< class A >
Moebius<A> &Moebius<A>::
operator=( Moebius const &f )
{
  if( &f != this )
  {
    _a = f._a;
    _b = f._b;
    _c = f._c;
    _d = f._d;
  }
  return *this;
}

template< class A >
void
Moebius<A>::
identity()
{
  _a = 1.0;
  _b = 0.0;
  _c = 0.0;
  _d = 1.0;
}

template< class A >
void
Moebius<A>::
mul( Moebius const &u, Moebius const &v )
{
  Moebius w;
  w._a = u._a*v._a + u._b*v._c;
  w._b = u._a*v._b + u._b*v._d;
  w._c = u._c*v._a + u._d*v._c;
  w._d = u._c*v._b + u._d*v._d;
  *this = w;
}

template< class A >
void
Moebius<A>::
mul( Moebius const &t )
{
  Moebius u = *this;
  _a = u._a*t._a + u._b*t._c;
  _b = u._a*t._b + u._b*t._d;
  _c = u._c*t._a + u._d*t._c;
  _d = u._c*t._b + u._d*t._d;
}

template< class A >
void
Moebius<A>::
mulleft( Moebius const &u )
{
  Moebius t = *this;
  _a = u._a*t._a + u._b*t._c;
  _b = u._a*t._b + u._b*t._d;
  _c = u._c*t._a + u._d*t._c;
  _d = u._c*t._b + u._d*t._d;
}


template< class A >
void
Moebius<A>::
invert()
{
  A a = _a;
  A b = _b;
  A c = _c;
  A d = _d;

  Real norm_a = norm(a);
  Real norm_b = norm(b);
  Real norm_c = norm(c);
  Real norm_d = norm(d);

  Real det = norm_a*norm_d + norm_b*norm_c - 2*real(a*conj(c)*d*conj(b));

  _a = conj(a*norm_d-b*conj(d)*c) / det;
  _b = conj(c*norm_b-d*conj(b)*a) / det;
  _c = conj(b*norm_c-a*conj(c)*d) / det;
  _d = conj(d*norm_a-c*conj(a)*b) / det;
}


template< class A >
void
Moebius<A>::
rotation(
  Real a, Real b,
  Real x, Real y, Real z )
{
  Real c1 = 0.5 * (a+b);
  Real cos_c1 = math::cos(c1);
  Real sin_c1 = math::sin(c1);

  Real c2 = 0.5 * (a-b);
  Real cos_c2 = math::cos(c2);
  Real sin_c2 = math::sin(c2);

  _a = A(cos_c1, x*sin_c1, y*sin_c1, z*sin_c1 );
  _b = A(0);
  _c = A(0);
  _d = A(cos_c2, -x*sin_c2, -y*sin_c2, -z*sin_c2 );
}


template< class A >
void
Moebius<A>::
rotation(
  Real a, Real b,
  A const &s, A const &t )
{
  Real c1 = 0.5 * (a+b);
  Real cos_c1 = math::cos(c);
  Real sin_c1 = math::sin(c);

  Real c2 = 0.5 * (a-b);
  Real cos_c2 = math::cos(c2);
  Real sin_c2 = math::sin(c2);

  A u = t*conj(s);
  A v = conj(s)*t;

  _a = A( cos_c1, u.x()*sin_c1, u.y()*sin_c1,  u.z()*sin_c1 );
  _b = A(0);
  _c = A(0);
  _d = A( cos_c2, -v.x()*sin_c2, -v.y()*sin_c2, -v.z()*sin_c2 );
}


template< class A >
void
Moebius<A>::
translation(
  Real r, Real x, Real y, Real z )
{
  _a = A(1);
  _b = A(r, x, y, z);
  _c = A(0);
  _d = A(1);
}


template< class A >
void
Moebius<A>::
inversion(
  Real r, Real x, Real y, Real z )
{
  _a = A(1);
  _b = A(0);
  _c = A(r, x, y, z);
  _d = A(1);
}


template< class A >
void
Moebius<A>::
scale( Real s )
{
  _a = A( s );
  _b = A(0);
  _c = A(0);
  _d = A(1);
}

template< class A >
void
Moebius<A>::
apply( A &x )
{
  x = (_a*x + _b) * inv(_c*x + _d);
}


#if !defined(NO_TMPL_FRIENDS)
template<class A>
inline
std::ostream &
operator<<( std::ostream &o, Moebius<A> const &t )
{
  o << "{{" << t._a << ",\n" << t._b << "},\n{"
    << t._c << ",\n" << t._d << "}}";
  return o;
}
#endif

} // namespace math

#endif // math_Moebius_INCLUDED

/* GANG Software
 * LAB/mrbubblelab/kernel/MrBubble.C
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

#include <math.h>
#if defined(__sgi)
#include <nan.h>
#endif
#include <iostream>
#include <iomanip>
#include <getopt.h>
#include "base/System.H"
#include "math/Math.H"
#include "math/VectorX.H"
#include <complex>
#include "base/Timer.H"
#include "base/String.H"
#include "base/Stl.H"
#include "base/ArrayP.H"
#include "geom/interface/Surface.H"
#include "MrBubble.H"

namespace mrbubblelab {
namespace kernel {

Complex const MrBubble::I(0.0,1.0);


MrBubble::
MrBubble(
  Complex const &coefficient, Real exponent,
  Real u0, Real uprime0 )
    :
    _coefficient(coefficient),
    _exponent(exponent),
    _u0(u0),
    _uprime0(uprime0),
    H(1.0)
{
  e1.col1().row1() = 0.0;
  e1.col2().row1() = 1.0;
  e1.col1().row2() = -1.0;
  e1.col2().row2() = 0.0;

  e2.col1().row1() = 0.0;
  e2.col2().row1() = I;
  e2.col1().row2() = I;
  e2.col2().row2() = 0.0;

  e3.col1().row1() = I;
  e3.col2().row1() = 0.0;
  e3.col1().row2() = 0.0;
  e3.col2().row2() = -I;

#ifdef DEBUG_MRBUBBLE
  std::cerr
    << "----------------------------------\n"
    << "coefficient=" << _coefficient
    << ";  exponent=" << _exponent << "\n"
    << "u=" << _u0
    << ";   u'=" << _uprime0 << "\n";
#endif
}

MrBubble::
~MrBubble()
{
}

void
MrBubble::
start( 
  Data &X,
  Complex const &z,
  uint count )
{
  DIE_IF(count==0);

  // initialize X
  // integration starts from 0
  X.z = 0.0;
  X.u = _u0;
  X.uprime = _uprime0;
  X.F.identity();
  X.f.zero();
  X.X.set(0.0);

  X.fx[0] = 1.0;
  X.fx[1] = 0.0;
  X.fx[2] = 0.0;

  X.fy[0] = 0.0;
  X.fy[1] = 1.0;
  X.fy[2] = 0.0;

  X.N[0] = 0.0;
  X.N[1] = 0.0;
  X.N[2] = 1.0;

  step( X, z, count );
}

void
MrBubble::
step( 
  Data &X,
  Complex const &z1,
  uint count )
{
  DIE_IF(count==0);

  // integrate from X.z to z2 in count steps
  Complex z = X.z;
  Complex dz = z1 - X.z;

  uint i;
  for ( i = 1; i <= count; i++ )
  {
    step( X, z + Real(i)/Real(count)*dz );
  }
}

void
MrBubble::
step(
  Data &X,
  Complex const &z1 )
{
  // integrate from X.z to z2 in 1 step

#if 0
  // don't integrate from X.z to X.z
  if ( math::effectively_zero(z1-X.z) ) { return; }
#endif

  integrate_surface( X, z1 - X.z );

  X.z = z1;

  su2_to_r3( X.X, X.f );

  Complex4 Finv;
  Finv.inv(X.F);
  Complex4 G;
  Real v = math::exp(0.5*X.u);

  // compute fx = exp(u/2) F.e1.Finv
  G.mul(X.F, e1);
  G.mul(G, Finv);
  G.mul(v);
  su2_to_r3( X.fx, G );

  // compute fy = exp(u/2) F.e2.Finv
  G.mul(X.F, e2);
  G.mul(G, Finv);
  G.mul(v);
  su2_to_r3( X.fy, G );

  // compute normal = F.e3.Finv (normalized)
  G.mul(X.F, e3);
  G.mul(G, Finv);
  su2_to_r3( X.N, G );
  Real q = X.N.norm();
  DIE_IF(math::effectively_zero(q));
  X.N /= q;
}

void
MrBubble::
integrate_metric(
  Data &X,
  Complex const &dz )
{
  Real r0 = std::abs(X.z);
  Real dr = std::abs(X.z + dz) - r0;

  if(! ::finite(X.u) )
  { throw base::Exception("overflow 0"); }
  if(! ::finite(X.uprime) )
  { throw base::Exception("overflow 1"); }

  // step 0
  Real dY0_u = 0.0;
  Real dY0_v = 0.0;
  metric_integration_function( dY0_u, dY0_v, X.u, X.uprime, r0 );

  // step 1
  if(! ::finite(X.u))
  { throw base::Exception("overflow 2"); }
  if(! ::finite(dY0_u))
  { throw base::Exception("overflow 3"); }

  X.z += 0.5*dz;

  Real tmp_u = X.u + 0.5*dr * dY0_u;
  Real tmp_v = X.uprime + 0.5*dr * dY0_v;

  Real dY1_u = 0.0;
  Real dY1_v = 0.0;
  metric_integration_function( dY1_u, dY1_v, tmp_u, tmp_v, r0+0.5*dr );

  // step 2
  tmp_u = X.u + 0.5*dr * dY1_u;
  tmp_v = X.uprime + 0.5*dr * dY1_v;

  Real dY2_u = 0.0;
  Real dY2_v = 0.0;
  metric_integration_function( dY2_u, dY2_v, tmp_u, tmp_v, r0+0.5*dr );

  X.z += 0.5*dz;


  // step 3
  tmp_u = X.u + dr * dY2_u;
  tmp_v = X.uprime + dr * dY2_v;

  Real dY3_u = 0.0;
  Real dY3_v = 0.0;
  metric_integration_function( dY3_u, dY3_v, tmp_u, tmp_v, r0+dr );

  // final
  X.u += (1.0/6.0) * dr * ( dY0_u + 2.0 *( dY1_u + dY2_u ) + dY3_u );
  X.uprime += (1.0/6.0) * dr * ( dY0_v + 2.0 *( dY1_v + dY2_v ) + dY3_v );

  if(! ::finite(X.u))
  { throw base::Exception("overflow 4"); }
  if(! ::finite(X.uprime))
  { throw base::Exception("overflow 5"); }
}


void
MrBubble::
metric_integration_function(
  Real &du,
  Real &dv,
  Real u,
  Real v,
  Real r )
{
  /*
  computes u''

  u'' + u'/r = f = -2 exp(u) H^2 + 8 exp(-u) |Q|^2

  it's divided into two cases:

    case r != 0:  u'' = -u'/r + f
    case r == 0:  u'' = f/2

  Rationale for the case r==0:
  When r=0, you can't evaluate u'/r directly.
  Instead, take the limit lim(u'/r) as r->0,
  which is u''.
  */

  if (! ::finite(du))
  { throw base::Exception("overflow 6"); }
  if (! ::finite(dv))
  { throw base::Exception("overflow 7"); }
  if (! ::finite(u))
  { throw base::Exception("overflow 8"); }
  if (! ::finite(v))
  { throw base::Exception("overflow 9"); }
  if (! ::finite(r))
  { throw base::Exception("overflow 10"); }

  du = v;

  Real e = math::exp(u);

  if (! ::finite(e))
  { throw base::Exception("overflow 11"); }

  Real f = -2.0 * math::sqr(H) * e + 8.0 * std::norm(Q(r)) / e;

  if (! ::finite(f))
  { throw base::Exception("overflow 12"); }

  if ( ! math::effectively_zero( r ) )
  {
    dv = -du/r + f;
  }
  else
  {
    // r is near 0
    dv = 0.5 * f;
  }

  if (! ::finite(dv))
  { throw base::Exception("overflow 13"); }
}

void
MrBubble::
integrate_frame(
  Data &X,
  Complex const &dz )
{
  Complex4 T;

  // step 0
  Complex4 dF0;
  frame_integration_function( dF0, X.F, X, 0.5*dz );

  // step 1
  integrate_metric( X, 0.5*dz );
  T.mul_add( X.F, 0.5, dF0 );
  Complex4 dF1;
  frame_integration_function( dF1, T, X, 0.5*dz );

  // step 2
  T.mul_add( X.F, 0.5, dF1 );
  Complex4 dF2;
  frame_integration_function( dF2, T, X, 0.5*dz );

  // step 3
  integrate_metric( X, 0.5*dz );
  T.add( X.F, dF2 );
  Complex4 dF3;
  frame_integration_function( dF3, T, X, 0.5*dz );

  // final
  Complex4 G = dF0;
  G.mul_add(2.0, dF1);
  G.mul_add(2.0, dF2);
  G.add(dF3);
  G.mul(2.0*(1.0/6.0));  // the 2 balances the 0.5dz
  X.F.add(G);

  // NOTE: why should this be so necessary?
  make_unitary(X.F);
}

void
MrBubble::
frame_integration_function(
  Complex4 &dF,
  Complex4 const &F,
  Data const &X,
  Complex const &dz )
{
  /*
    compute the Maurer-Cartan form

    Theta = {{(dz*uz)/4 - (dzb*uzb)/4, (-I*dzb*Qb)/t - I/2*dz*H*t},
             {(-I*dz*Q)/t - I/2*dzb*H*t, -(dz*uz)/4 + (dzb*uzb)/4}}
    t = exp(u/2)
    uz = zb u'/(2r)
  */

  if(! ::finite(X.u))
  { throw base::Exception("overflow 14"); }

  // compute u_z
  Complex u_z = 0.0;
  if ( ! math::effectively_zero( std::abs(X.z) ) )
  {
    u_z = 0.5 * std::conj(X.z) * X.uprime / std::abs(X.z);
  }

  Complex e = math::exp(0.5 * X.u);

  Complex4 T; // the Maurer-Cartan form
  T.col1().row1() = 0.5 * I * std::imag(u_z * dz);
  T.col1().row2() = -I * Q(X.z) * dz / e - 0.5 * I * H * e * std::conj(dz);
  T.col2().row1() = -std::conj(T.col1().row2());
  T.col2().row2() = -T.col1().row1();

  // Y = F.T
  dF.mul( F, T );
}

void
MrBubble::
integrate_surface( Data &X, Complex const &dz )
{
  // integrate df = f_z dz + f_zb dzb

  // step 0
  Complex4 df0;
  compute_df( df0, X, 0.5*dz );

  // step 1
  integrate_frame( X, 0.5*dz );
  Complex4 df1;
  compute_df( df1, X, 0.5*dz );

  // step 2
  integrate_frame( X, 0.5*dz );
  Complex4 df2;
  compute_df( df2, X, 0.5*dz );

  // final
  Complex4 g = df0;
  g.mul_add( g, 4.0, df1 );
  g.add( g, df2 );
  g.mul(2.0*(1.0/6.0)); // the 2 balances the 0.5dz
  X.f.add(g);
}

void
MrBubble::
compute_df(
  Complex4 &df,
  Data const &X,
  Complex const &dz )
{
  Complex dz_ = math::exp( 0.5 * X.u ) * dz;
  Complex fz11 = dz_ * X.F.col1().row1() * (-X.F.col1().row2());
  Complex fz12 = dz_ * X.F.col1().row1() * X.F.col1().row1();
  Complex fz21 = dz_ * X.F.col1().row2() * (-X.F.col1().row2());
  Complex fz22 = dz_ * X.F.col1().row2() * X.F.col1().row1();

  df.col1().row1() = fz11 - std::conj(fz11);
  df.col2().row1() = fz12 - std::conj(fz21);
  df.col1().row2() = fz21 - std::conj(fz12);
  df.col2().row2() = fz22 - std::conj(fz22);
}


Complex
MrBubble::
Q( Complex const &z )
{
  Complex v;
  if ( math::effectively_zero(_exponent) )
  {
    v = _coefficient;
  }
  else
  {
    v = _coefficient * std::pow( z, _exponent );
  }
  return v;
}

void
MrBubble::
make_unitary(
  Complex4 &F )
{
  // normalize F
  // F approximates an element of SU(2), so
  // replace F by a close element of SU(2)

  Complex a11, a12, a21, a22;

  a11 = 0.5 * ( F.col1().row1() + std::conj(F.col2().row2()) );
  a22 = std::conj(a11);
  a12 = 0.5 * (F.col2().row1() - std::conj(F.col1().row2()));
  a21 = -std::conj(a12);

  F.col1().row1() = a11;
  F.col2().row1() = a12;
  F.col1().row2() = a21;
  F.col2().row2() = a22;

  // make det(F)==1
  Complex det =
    std::sqrt(F.col1().row1() * F.col2().row2() -
         F.col1().row2() * F.col2().row1());
  DIE_IF( math::effectively_zero( std::norm(det) ) );
  F.mul( 1.0/std::sqrt(det), F );
}

void
MrBubble::
su2_to_r3(
  base::ArrayX<Real,3U> &X,
  Complex4 const &f )
{
  X[0] = f.col2().row1().real();
  X[1] = f.col2().row1().imag();
  X[2] = f.col1().row1().imag();
}

MrBubble::
Data::
Data()
{
  z = 0.0;
  u = 0.0;
  uprime = 0.0;

  F.col1().row1() = 1.0;
  F.col1().row2() = 0.0;
  F.col2().row1() = 0.0;
  F.col2().row2() = 1.0;

  f.col1().row1() = 0.0;
  f.col1().row2() = 0.0;
  f.col2().row1() = 0.0;
  f.col2().row2() = 0.0;

  X.set(0.0);
}

MrBubble::
Data::
Data( Data const &a )
{
  z = a.z;
  u = a.u;
  uprime = a.uprime;
  F = a.F;
  f = a.f;
  X = a.X;
}

MrBubble::
Data::
~Data()
{
}

MrBubble::Data &
MrBubble::
Data::
operator=( Data const &a )
{
  if ( this != &a )
  {
    z = a.z;
    u = a.u;
    uprime = a.uprime;
    F = a.F;
    f = a.f;
    X = a.X;
  }
  return *this;
}

#ifdef DEBUG_MRBUBBLE
std::ostream &
operator<<( std::ostream &o, MrBubble::Data const &X )
{
  o << "-------------------------\n";
  o << "z=" << X.z << "\n";
  o << "u=" << X.u << ";  uprime=" << X.uprime << "\n";
//  o << "H=" << X.H << ";  Q=" << X.Q << "\n";
  o << "F = " << X.F;
//  o << "X = " << X.X;
  o << "f = " << X.f;
  return o;
}
#endif


} // namespace kernel
} // namespace mrbubblelab

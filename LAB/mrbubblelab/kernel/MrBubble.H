/* GANG Software
 * LAB/mrbubblelab/kernel/MrBubble.H
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

#ifndef mrbubblelab_kernel_MrBubble_INCLUDED
#define mrbubblelab_kernel_MrBubble_INCLUDED

/*
  This CMC software package creates graphics of constant mean curvature
  surfaces by solving the Maurer-Cartan equation for the surface, under
  the assumption that that the first fundamental form is radially symmetric
  about a point.

  The Maurer-Cartan equation is the integrability condition for
  a conformal immersion M->R^3, a second-order partial differential
  equation involving the conformal factor u and its derivatives,
  the mean curvature H, and the Hopf form Q.

  If you make the strong assumption that u, H and Q are is rotationally
  symmetric about a point, the Maurer-Cartan equation reduces to a second-
  order ordinary differential equation in u.

  This software computes such a surface by three integrations:
    (1) Given H and Q, integrate the rotationally-symmetric Maurer-Cartan
        equation. This give the conformal factor u. This is done by
        writing the second-order ODE as a system of 2 first-order ODE's
        and integrating by fourth-order Runge-Kutta methods.
    (2) From u, H and Q, compute the frame F for the surface. (F is in
        SU(2).) This is done by first computing the Maurer-Cartan form T,
        and then integrating the equation dF = F T. Euler's method is used.
    (3) Compute the surface by integrating the frame F.


=========================================================
COMPUTING CMC SURFACES WITH ROTATIONALLY INVARIANT METRIC
=========================================================

This CMC software package creates graphics of constant mean curvature
surfaces by solving the Maurer-Cartan equation for the surface, under
the assumption that that the first fundamental form is radially symmetric
about a point.

The Maurer-Cartan equation is the integrability condition for
a conformal immersion M->R^3, a second-order partial differential
equation involving the conformal factor u and its derivatives,
the mean curvature H, and the Hopf form Q.

If you make the strong assumption that u, H and Q are rotationally
symmetric about a point, the Maurer-Cartan equation reduces to a second-
order ordinary differential equation in u.

This software computes such a surface by three integrations:
  (1) Given H and Q, integrate the rotationally-symmetric Maurer-Cartan
      equation. This give the conformal factor u. This is done by
      writing the second-order ODE as a system of 2 first-order ODE's
      and integrating by fourth-order Runge-Kutta methods.
  (2) From u, H and Q, compute the frame F for the surface. (F is in
      SU(2).) This is done by first computing the Maurer-Cartan form T,
      and then integrating the equation dF = F T. Euler's method is used.
  (3) Compute the surface by integrating the frame F.



FIRST INTEGRATION: COMPUTING THE METRIC

Integrate the Maurer-Cartan equation to get the metric (conformal factor) u.

The Maurer-Cartan integrability condition for a CMC surface f:M-->R^3 is

  (1)  u_z_zb + (1/2) exp(u) H^2 - 2 |Q|^2 exp(-u) = 0,

where

  exp(u) = |fx|^2 = |fy|^2

is the square of the conformal factor of f,

  H = 2 exp(-u) < f_z_zb, N>

is the mean curvature of f, and

  Q = <f_z_z, N>

is the Hopf form of f. N denotes a normal to F.


Make the strong assumption that u(z) is invariant
under rotations about z=0, so that u is a function of r=|z|.
Then (1) becomes

  (2)  u'' + (1/r) u' + 2 H^2 exp(u) - 8 |Q|^2 exp(-u) = 0.

where u' denotes du/dr, and using u_z_zb = (1/4) u'' + (1/(4r)) u'.

The routines below solve equation (2).



In order to use Runge-Kutta, this second order equation is rewritten as
a  system of first-order
equations

  u' = v
  v' = F(u, v, r)

where

  F(u, v, r) = -(1/r)v - 2 H^2 exp(u) + 8 |Q|^2 exp(-u).


SECOND INTEGRATION: COMPUTING THE FRAME

Integrate the frame differentials to get the frame for the surface.
Integrate the differential equation

    dF = F T

  where F is the frame for the surface in SU(2), and T is the
  Maurer-Cartan form

    T = {{(dz*uz)/4 - (dzb*uzb)/4, (-I*dzb*Qb)/t - I/2*dz*H*t},
             {(-I*dz*Q)/t - I/2*dzb*H*t, -(dz*uz)/4 + (dzb*uzb)/4}}
    t = exp(u/2)
    uz = zb u'/(2r)


  The corresponding difference equation is

    F_new = F_old + F_old T

  or equivalently,

    F_new = F_old ( I + T )



THIRD INTEGRATION: COMPUTING THE SURFACE

Integrate the frame to get the surface.


  Compute

     f_z  = exp(u/2) dz F.g1.Finv
     f_zb = exp(u/2) dzb F.g2.Finv = -conj(trans(f_z))

  where f is the surface in R^3 and

    g1 = {{0,1},{0,0}}
    g2 = {{0,0},{-1,0}}

The reason for this:
F satisfies

  F.e1.Finv = fx/|fx|
  F.e2.Finv = fy/|fy|

where

  e1 = {{0,1},{-1,0}}
  e2 = {{0,i},{i,0}}
  e3 = {{i,0},{0,-i}}

Add the two equations.

  g1 = 1/2(e1-i e2)
  g2 = 1/2(e1+i e2)

  |fx|=|fy|=exp(u/2)

  */

#include "base/vector.H"
#include "base/System.H"
#include "base/Array.H"
#include "base/ArrayP.H"
#include "base/ArrayX.H"
#include "math/VectorX.H"
#include "math/Complex4.H"
#include "math/Math.H"

namespace mrbubblelab {
namespace kernel {

typedef double Real;
typedef std::complex<Real> Complex;
typedef math::VectorX<Real, 3U> Real3;
typedef math::complex4<Real> Complex4;

#undef DEBUB_MRBUBBLE

class MrBubble
{

public:

  /*
    constructor
    typical values:
      coefficient = 1
      exponent = 1 (three-legged; legs=exponent+2)
      u0 = 1
      uprime0 = 0
  */
  MrBubble(
    Complex const &coefficient, Real exponent,
    Real u0, Real uprime0 );

  // destructor
  virtual ~MrBubble();

  struct Data
  {
    // constructor
    Data();
    
    // copy constructor
    Data( Data const &a );
    
    // destructor
    ~Data();

    // assignemt operator
    Data &operator=( Data const & );

    // conformal coordinate
    Complex z;

    // metric
    Real u;

    // r derivative of the metric
    Real uprime;

    // frame in SU(2)
    Complex4 F;

    // point in su(2)
    Complex4 f;

    // fx, fy
    Real3 fx, fy;

    // normal in R^3
    Real3 N;

    // point in R^3
    Real3 X;


#ifdef DEBUG_MRBUBBLE
    // output
    friend std::ostream &operator<<( std::ostream &o, Data const &p );
#endif
  };



  void start(
    Data &X,
    Complex const &z,
    uint count );

  void step(
    Data &X,
    Complex const &z1,
    uint count );

  void step( Data &X, Complex const &z2 );

private:

  /*
    INTEGRATION STEP 1
    compute the metric
  */
  void integrate_metric(
    Data &X, Complex const &dz );

  void
  metric_integration_function(
    Real &du,
    Real &dv,
    Real u,
    Real v,
    Real r );

  /*
    INTEGRATION STEP 2:  computing the frame from the maurer-cartan form

    Integrate the frame differentials to get the frame for the surface.
    Integrate the differential equation

      dF = F T

    where F is the frame for the surface in SU(2), and T is the
    Maurer-Cartan form.
    The corresponding difference equation is

      F_new = F_old + F_old T

    or equivalently,

      F_new = F_old ( I + T )
  */

  void integrate_frame( Data &X, Complex const &dz );

  void frame_integration_function(
    Complex4 &dF, Complex4 const &F, Data const &X, Complex const &dz );

  /*
    INTEGRATION STEP 3: computing the surface from the frame

    Integrate the frame to get the surface.

    Compute

      f_z  = exp(u/2) dz F.e1.Finv
      f_zb = exp(u/2) dzb F.e2.Finv = -conj(trans(f_z))

    where f is the surface in R^3 and

      e1 = {{0,1},{0,0}}
      e2 = {{0,0},{-1,0}}
  */

  void integrate_surface( Data &X, Complex const &dz );

  void compute_df( Complex4 &df, Data const &X, Complex const &dz );


  // utility routines
  static void su2_to_r3(
    base::ArrayX<Real, 3U> &f,
    Complex4 const &X );

  static void make_unitary( Complex4 &F );

  Complex _coefficient;
  Real _exponent;
  Real _u0;
  Real _uprime0;

  Real H;
  Complex Q( Complex const & );

  struct Real2 { Real u, uprime; };
  base::vector<Real2> _metric;

  static Complex const I;

  Complex4 e1, e2, e3;

  // disabled copy constructor
  inline MrBubble( MrBubble const & );

  // disabled assigment operator
  inline MrBubble &operator=( MrBubble const & );
};

} // namespace kernel
} // namespace mrbubblelab

#endif // mrbubblelab_kernel_MrBubble_INCLUDED

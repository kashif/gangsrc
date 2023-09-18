/* GANG Software
 * LAB/bubbletonlab/kernel/Bubbleton.H
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

#ifndef bubbletonlab_kernel_Bubbleton_INCLUDED
#define bubbletonlab_kernel_Bubbleton_INCLUDED

#include <complex>
#include "base/vector.H"
#include "math/Vector3.H"
#include "math/Matrix3.H"

namespace bubbletonlab {
namespace kernel {

/*
  Computes multibubbletons -- arbitrary number of bubbletons on a round
  cylinder (H=1) or on a line (K=1)

  To use: constuct a Bubbleton object, specifying
    bubbletonlab count, centers and sizes.
  Call compute(X, z) to compute each point X in R^3 at z in the rectangular
  domain.

  Implementation of Sterling-Wente algorithm for Multibubbletons with
  constant mean curvature (CMC) or constant positive Gaussian curvature.

  This algorithm is pointwise: it does not integrate. It only requires trig,
  hyperbolic trig, exp and log.

  The algorithm is described in:
  Sterling, I.; Wente, H.C.
  Existence and classification of constant mean curvature multibubbletons of
    finite and infinite type. 
  Indiana Univ. Math. J. 42 (1993), no. 4, 1239-1266. 
*/

#undef DEBUG_BUBBLETON

class Bubbleton
{

public:

  typedef double Real;
  typedef std::complex<Real> Complex;
  typedef math::VectorX<Complex,3U> Vector3;
  typedef math::MatrixX<Complex,3U> Matrix3;

  /* constructor
     center = vector of centers of the bubbletons
     size = vector of sizes of the bubbletons
       (size=number of lobes in one wrap; can be fractional)
  */
  Bubbleton(
    base::vector<Complex> const &center,
    base::vector<Complex> const &size
    );

  // destructor
  virtual ~Bubbleton();

  // compute a single point
  void
  compute(
    math::VectorX<Real,3U> &X,
    math::VectorX<Real,3U> &N,
    Complex const &z );

protected:

private:

  // compute one bubbletonlab
  void _compute(uint i, Complex const &z);

  // utility method to compute the frame
  void _frame(
    Matrix3 &A,
    Complex const &theta0,
    Complex const &theta1,
    Complex const &beta);

  static Complex tanh(Complex const &z)
    { return std::sinh(z) / std::cosh(z); }

  static Complex coth(Complex const &z)
    { return std::cosh(z) / std::sinh(z); }

  static Complex acosh(Complex const &z)
    { return std::log( z + std::sqrt( z*z-1.0 ) ); }

  static Complex atanh(Complex const &z)
    { return 0.5 * std::log( (1.0+z) / (1.0-z) ); }

  uint _count;

  struct Data
  {
    Complex center; // center
    Complex beta; // ArcCosh[size]
    Complex beta_; // beta^* = Pi I - Conjugate[beta]
    base::vector<Complex> theta;
    base::vector<Complex> theta_; // theta^* = \pm theta
    Matrix3 frame; // frame of bubbletonlab
    Vector3 surface; // bubbletonlab
  };

  base::vector<Data> _;

  static Complex const I;

  // disabled copy constructor
  Bubbleton( Bubbleton const & );

  // disabled assignment operator
  Bubbleton &operator=( Bubbleton const & );

#ifdef DEBUG_BUBBLETON
  void _dump_initial(
    std::ostream &o,
    base::vector<Complex> const &center,
    base::vector<Complex> const &size );

  void _dump(
    std::ostream &o,
    Complex const &z,
    math::VectorX<Real,3U> const &X );
#endif

};

} // namespace kernel
} // namespace bubbletonlab

#endif // bubbletonlab_kernel_Bubbleton_INCLUDED

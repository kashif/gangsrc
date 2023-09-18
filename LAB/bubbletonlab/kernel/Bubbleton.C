/* GANG Software
 * LAB/bubbletonlab/kernel/Bubbleton.C
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

#include "base/Exception.H"
#include "base/Stl.H"
#include "Bubbleton.H"

namespace bubbletonlab {
namespace kernel {

#define MAKE_REAL 1

Bubbleton::Complex const Bubbleton::I(0.0, 1.0);

Bubbleton::
Bubbleton(
  base::vector<Complex> const &center,
  base::vector<Complex> const &size
  )
    :
    _count(center.size())
{
  DIE_IF( center.size() != size.size() );

  // check whether two bubbletonlab sizes are the same
  uint i;
  for (i = 0; i < _count-1; i++)
  {
    uint j;
    for (j = i+1; j < _count; j++)
    {
      if ( math::effectively_zero( std::abs(size[i]-size[j]) ) )
      {
        throw base::Exception( "Two bubbletonlab have the same size" );
      }
    }
  }

  // allocate _
  Data d;
  _.fill(d, _count+1);

  // allocate _[i].theta and _[i].theta_
  for (i = 0; i <= _count; i++)
  {
    Complex t(0.0);
    _[i].theta.fill(t, 2*i+1);
    _[i].theta_.fill(t, 2*i+1);
  }

  for (i = 1; i <= _count; i++) // starts at 1
  {
    _[i].center = center[i-1];
    _[i].beta = acosh(size[i-1]);
    _[i].beta_ = math::pi * I - std::conj(_[i].beta);
    _[i].theta[2*i] = 0.0;
  }

#ifdef DEBUG_BUBBLETON
  _dump_initial( std::cerr, center, size );
#endif
}

Bubbleton::
~Bubbleton()
{
}

void
Bubbleton::
compute(
  math::VectorX<Real,3U> &X,
  math::VectorX<Real,3U> &N,
  Complex const &z_ )
{
  Complex z = z_;

  // _[0].theta
  _[0].theta[0] = 0.0;

  // _[0].frame
  Real x = math::cos(z.imag());
  Real y = math::sin(z.imag());

  _[0].frame[0][0] = 1.0;
  _[0].frame[0][1] = 0.0;
  _[0].frame[0][2] = 0.0;

  _[0].frame[1][0] = 0.0;
  _[0].frame[1][1] = x;
  _[0].frame[1][2] = -y;

  _[0].frame[2][0] = 0.0;
  _[0].frame[2][1] = y;
  _[0].frame[2][2] = x;

  // _[0].surface
  _[0].surface[0] = z.real();
  _[0].surface[1] = 0.0;
  _[0].surface[2] = 0.0;


  // if z+n pi i is too close to a bubbletonlab center for some integer n,
  // then perturb z
  uint i;
  for (i = 1; i <= _count; i++) // starts at 1
  {
    Complex p = (z-_[i].center)/(math::pi * I);
    p -= ::floor(p.real());
    if (math::effectively_zero(p) )
    {
      break;
    }
  }
  if (i != _count+1)
  {
    // perturb z
    WARN();
#ifdef DEBUG_BUBBLETON
    std::cerr << "perturbing z=" << z << "\n";
#endif
    z += Complex(1.23e-5, 1.67e-5); // arbitrary perturbation
  }

  // compute the bubbletons
  for (i = 1; i <= _count; i++) // starts at 1
  {
    _compute(i, z);
  }

  // set X and N
  for ( i = 0; i < 3; i++ )
  {
    X[i] = _[_count].surface[i].real();
    N[i] = _[_count].frame[2][i].real();

#if 0
    std::cerr << math::chop(_[_count].surface[i].imag()) << " "
              << math::chop((_[_count].frame[2][i]).imag()) << "\n";
#endif
  }

  for ( i = 0; i < 3; i++ )
  {
    if (math::isnan(X[i]))
    {
      WARN("surface coordinate is a NaN");
#ifdef DEBUG_BUBBLETON
      std::cerr << "  z=" << z << "\n";
#endif
      X[i] = 0.0;
    }
    if (math::abs(X[i])>1.0e+06)
    {
      WARN();
#ifdef DEBUG_BUBBLETON
      std::cerr << "surface coordinate " << i  << " is infinite; z="
                << z << "\n";
#endif
      X[i]=0.0;
    }
    X[i] = math::chop(X[i]);

    if (math::isnan(N[i]))
    {
      WARN("surface coordinate is a NaN");
#ifdef DEBUG_BUBBLETON
      std::cerr << "  z=" << z << "\n";
#endif
      N[i] = 0.0;
    }
    if (math::abs(N[i])>1.0e+06)
    {
      WARN();
#ifdef DEBUG_BUBBLETON
      std::cerr << "surface coordinate " << i  << " is infinite; z="
                << z << "\n";
#endif
      N[i]=0.0;
    }
    N[i] = math::chop(N[i]);
  }

#if 0
  _dump( std::cerr, z, X );
#endif
}

void
Bubbleton::
_compute(uint i, Complex const &z)
{
  // _[i].theta[2i-1]
  Complex z0 = z - _[i].center;

  if (math::effectively_zero(z0)) {
    WARN();
#ifdef DEBUG_BUBBLETON
    std::cerr << "domain point coincides with the center "
              << z << " of bubbletonlab " << i << "\n";
#endif
  }

  Complex b = _[i].beta;

  Complex r =
    std::exp( z0.real() * std::sinh(b) + I * z0.imag() * std::cosh(b) );

  DIE_IF(math::effectively_zero(r-1.0));

  Complex s = 2.0 * atanh(r);
  _[i].theta[2*i-1] = s;
  _[i].theta_[2*i-1] = -std::conj(s);

  // _[i].theta[j]
  int j;
  for ( j = 2*i-2; j >= 0; j-- )
  {
    Complex t1 = _[i].theta[j+1]; // upper
    Complex t0 =
      ( j > (int)0 ? _[i-1].theta[j-1] : _[i].theta_[1] ); // lower

    Complex b1 = _[i].beta; // upper
    Complex b0 =
      ( j >= (int)i ? _[j-i+1].beta : _[i-j].beta_ ); // lower

    Complex r = 0.5*(b1-b0);
    Complex s(0.0);

    if (math::effectively_zero(r))
    {
      // this happens when two bubbletons are the same size
      WARN("something is zero");
      s = 0.0;
    }
    else
    {
      s = _[i-1].theta[j] + 2.0 * atanh( coth(r) * tanh(0.5*(t1-t0)) );
    }

    _[i].theta[j] = s;

    if (j % 2 == 1)
    { _[i].theta_[j] = -std::conj(s); }
    else
    { _[i].theta_[j] = std::conj(s); }

  }

#if MAKE_REAL
  // make _[i].theta[0] real
  _[i].theta[0] = _[i].theta[0].real();
  _[i].theta_[0] = _[i].theta_[0].real();
#endif

  // intermediate frame
  Matrix3 tmpframe;
  _frame( tmpframe, _[i].theta[1], _[i-1].theta[0], _[i].beta );
  tmpframe.mul(_[i-1].frame);

  // bubbletonlab frame
  _frame( _[i].frame, _[i].theta[0], _[i].theta[1], _[i].beta_ );
  _[i].frame.mul(tmpframe);

#if MAKE_REAL
  // make frame real
  uint p;
  for (p = 0; p < 3; p++)
  {
    uint q;
    for (q = 0; q < 3; q++)
    {
      _[i].frame[p][q] = _[i].frame[p][q].real();
    }
  }
#endif

  // surface
  {
    Complex t0 = _[i].theta[1];
    Complex t1 = _[i].theta_[1];
    Complex b0 = _[i].beta;
    Complex b1 = _[i].beta_;

    Complex Lambda = std::sinh(b0 - b1) /
      ( std::sinh(b0) * std::sinh(b1) *
        (std::cosh(b0 - b1) - std::cosh(t0 - t1)));

    Vector3 alpha;
    alpha[0] = std::cosh(b0) * std::cosh(t1) - std::cosh(b1) * std::cosh(t0);
    alpha[1] = 
      I*(std::cosh(b0) * std::sinh(t1) - std::cosh(b1) * std::sinh(t0));
    alpha[2] = std::sinh(t0 - t1);

    // alpha = alpha * _[i-1].frame
    _[i-1].frame.mulleft( alpha );
    _[i].surface.mul_add( _[i-1].surface, Lambda, alpha );

#if MAKE_REAL
    // make surface real
    uint p;
    for (p = 0; p < 3; p++)
    {
      _[i].surface[p] = _[i].surface[p].real();
    }
#endif
  }
}

void
Bubbleton::
_frame(
    Matrix3 &A,
    Complex const &theta0,
    Complex const &theta1,
    Complex const &beta)
{
  Complex c0 = std::cosh(theta0);
  Complex s0 = std::sinh(theta0);
  Complex c1 = std::cosh(theta1);
  Complex s1 = std::sinh(theta1);
  Complex cb = std::cosh(beta);
  Complex sb = std::sinh(beta);

  A[0][0] = c0 * c1 * sb + s0 * s1 * cb;
  A[0][1] = I * (s0 * c1 * sb + c0 * s1 * cb);
  A[0][2] = -s1;
  A[1][0] = I * (c0 * s1 * sb + s0 * c1 * cb);
  A[1][1] = -(s0 * s1 * sb + c0 * c1 * cb);
  A[1][2] = -I * c1;
  A[2][0] = s0;
  A[2][1] = I * c0;
  A[2][2] = -cb;

  A /= sb;
}

#ifdef DEBUG_BUBBLETON
void
Bubbleton::
_dump_initial(
  std::ostream &o,
  base::vector<Complex> const &center,
  base::vector<Complex> const &size )
{
  o << "---------------------------\n";
  o << "count=" << center.size() << "\n";
  
  uint i;
  for ( i = 0; i < center.size(); i++ )
  {
    o << "center[" << i << "]=" << center[i]
              << "  size[" << i << "]=" << size[i] << "\n";
  }
  o << "---------------------------\n";
}

void
Bubbleton::
_dump(
  std::ostream &o,
  Complex const &z,
  math::VectorX<Real,3U> const &X )
{
  o << "==================================\n";
  o << "z= " << z << "\n";
  o << "X= " << X << "\n";
  uint i;
  for ( i = 0; i <= _count; i++ )
  {
    o << "[" << i << "]--------------------------\n";
    o << "center= " << _[i].center << "\n";
    o << "beta=   " << _[i].beta << "\n";
    o << "beta_=  " << _[i].beta_ << "\n";

    int j;

    o << "theta.size()= " << _[i].theta.size() << "\n";
    if (_[i].theta.size() > 0)
    {
      for (j = _[i].theta.size() - 1; j>=0; j--)
      {
        o << "theta[" << j << "]= " << _[i].theta[j] << "\n";
      }
    }

    o << "theta_.size()= " << _[i].theta_.size() << "\n";
    if (_[i].theta_.size() > 0)
    {
      for (j = _[i].theta_.size() - 1; j>=0; j--)
      {
        o << "theta_[" << j << "]= " << _[i].theta_[j] << "\n";
      }
    }
    o << "frame= " << _[i].frame << "\n";
    o << "surface= " << _[i].surface << "\n";
  }
}
#endif

} // namespace kernel
} // namespace bubbletonlab

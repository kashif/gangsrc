/* GANG Software
 * LAB/loop/Fourier.C
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

#include "Fourier.H"

namespace loop {

Fourier::
Fourier( uint count )
    :
    _integrator1(this, count),
    _integrator2(this, count),
    _count(count)
{
}

Fourier::
~Fourier()
{
}

void
Fourier::
Integrator1::
compute_(
  Loop1 &r,
  Loop1 const &x,
  void (*f)( Complex &, Complex const & ) )
{
  DIE_IF(&r == &x);

  _f = f;
  _loop = &x;

  int n = static_cast<Loop1 const *>(_loop)->polylen();
  DIE_IF(n == 0);

  int i;
  for (i = -n; i <= n; i+=2 )
  {
    compute_coefficient( r[i], i );
  }
}

#if REDUNDANT
void
Fourier::
Integrator1::
compute_(
  Loop1 &r,
  Loop1 const &x,
  void (*f)( Complex &, Complex const & ) )
{
  DIE_IF(&r == &x);

  _f = f;
  int n = static_cast<Loop1 const *>(_loop)->polylen();
  DIE_IF(n == 0);

  int i;
  for (i = -(n-1); i <= n-1; i+=2 )
  {
    compute_coefficient( r[i], i );
  }
}
#endif

void
Fourier::
Integrator1::
compute_coefficient(
  Complex &x, int n )
{
  _n = n;
  x = 0.0;
  compute( x, 0, 2.0*math::pi, _count );
  x = math::chop(x);
}

void
Fourier::
Integrator1::
function(
  Complex &w,
  Complex const &t_,
  Complex const & )
{
  Complex it = Complex(0.0, t_.real());
  Complex x;
  _loop->eval( x, std::exp(it)  );
  Complex r;
  (*_f)(r, x);
  w = r * std::exp( -Real(_n) * it ) / (2.0 * math::pi);
}

void
Fourier::
Integrator2::
compute_(
  Loop1 &r,
  Loop1 const &x,
  Loop1 const &y,
  void (*f)( Complex &, Complex const &, Complex const & ) )
{
  DIE_IF(&r == &x);
  DIE_IF(&r == &y);

  _f = f;
  _loop1 = &x;
  _loop2 = &y;
  int n = static_cast<Loop1 const *>(_loop1)->polylen();
  DIE_IF(n == 0);

  int i;
  for (i = -n; i <= n; i+=2 )
  {
    compute_coefficient( r[i], i );
  }
}
#if REDUNDANT
void
Fourier::
Integrator2::
compute_(
  Loop1 &r,
  Loop1 const &x,
  Loop1 const &y,
  void (*f)( Complex &, Complex const &, Complex const & ) )
{
  _f = f;
  _loop1 = &x;
  _loop2 = &y;
  int n = static_cast<Loop1 const *>(_loop1)->polylen();
  DIE_IF(n == 0);

  int i;
  for (i = -n; i <= n; i+=2 )
  {
    compute_coefficient( r[i], i );
  }
}
#endif

#if REDUNDANT
void
Fourier::
Integrator2::
compute_(
  Loop1 &r,
  Loop1 const &x,
  Loop1 const &y,
  void (*f)( Complex &, Complex const &, Complex const & ) )
{
  DIE_IF(&r == &x);

  _f = f;
  _loop1 = &x;
  _loop2 = &y;
  int n = static_cast<Loop1 const *>(_loop1)->polylen();
  DIE_IF(n == 0);

  int i;
  for (i = -(n-1); i <= n-1; i+=2 )
  {
    compute_coefficient( r[i], i );
  }
}
#endif

void
Fourier::
Integrator2::
compute_coefficient( Complex &x, int n )
{
  _n = n;
  x = 0.0;
  compute( x, 0, 2.0*math::pi, _count );
  x = math::chop(x);
}

void
Fourier::
Integrator2::
function(
  Complex &w,
  Complex const &t_,
  Complex const & )
{
  Complex it = Complex(0.0, t_.real());
  Complex x;
  _loop1->eval( x, std::exp(it)  );
  Complex y;
  _loop2->eval( y, std::exp(it)  );
  Complex r;
  (*_f)(r, x, y);
  w =  r * std::exp( -Real(_n) * it ) / (2.0 * math::pi);
}


} // namespace loop

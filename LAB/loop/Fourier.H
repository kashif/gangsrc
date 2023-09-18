/* GANG Software
 * LAB/loop/Fourier.H
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

#ifndef loop_Fourier_INCLUDED
#define loop_Fourier_INCLUDED

#include "math/RungeKutta.H"
#include "loop/Loop1.H"

namespace loop {

class Fourier
{

public:
  Fourier(uint count);

  virtual ~Fourier();

  void count( uint c ) { _count = c; };

  // compute r := 1/x via Fourier integrals
  void inv( Loop1 &r, Loop1 const &x )
    { _integrator1.compute_( r, x, _inv ); }

  // compute r := x/y via Fourier integrals
  void div( Loop1 &r, Loop1 const &x, Loop1 const &y )
    { _integrator2.compute_( r, x, y, _div ); }

  // compute r := Sqrt[x] via Fourier integrals
  void sqrt( Loop1 &r, Loop1 const &x )
    { _integrator1.compute_( r, x, _sqrt ); }

  // compute r := 1/Sqrt[x] via Fourier integrals
  void inv_sqrt( Loop1 &r, Loop1 const &x )
    { _integrator1.compute_( r, x, _inv_sqrt ); }

  // compute r := x^(1/4) via Fourier integrals
  void root4( Loop1 &r, Loop1 const &x )
    { _integrator1.compute_( r, x, _root4 ); }

protected:

private:


  class Integrator1
    : public math::RungeKutta<std::complex<double>, std::complex<double> >
  {
  public:
    Integrator1(Fourier *parent, uint count ) :
        _count(count), _n(0), _loop((Loop1 *)0),
        _parent(parent) {}
    void compute_( Loop1 &r, Loop1 const &x,
                  void (*f)( Complex &, Complex const & ) );
    void compute_coefficient( Complex &x, int n );
    void function( Complex &w,
                   Complex const &t,
                   Complex const & );
    void (*_f)( Complex &, Complex const & );
    uint _count;
    int _n;
    Loop1 const *_loop;
    Fourier *_parent;

  };
  friend class Integrator1;
  Integrator1 _integrator1;


  class Integrator2
    : public math::RungeKutta<std::complex<double>, std::complex<double> >
  {
  public:
    Integrator2(Fourier *parent, uint count ) :
        _count(count), _n(0), _loop1((Loop1 *)0), _loop2((Loop1 *)0),
        _parent(parent) {}
    void compute_( Loop1 &r, Loop1 const &y, Loop1 const &x,
                  void (*f)( Complex &, Complex const &, Complex const & ) );
    void compute_coefficient( Complex &x, int n );
    void function( Complex &w,
                   Complex const &t,
                   Complex const & );
    void (*_f)( Complex &, Complex const &, Complex const &);
    uint _count;
    int _n;
    Loop1 const *_loop1, *_loop2;
    Fourier *_parent;
  };
  friend class Integrator2;
  Integrator2 _integrator2;

  static void _inv( Complex &r, Complex const &x )
    { r = 1.0/x; }
  static void _div( Complex &r, Complex const &x, Complex const &y )
    { r = x/y; }
  static void _sqrt( Complex &r, Complex const &x )
    { r = std::sqrt(x); }
  static void _inv_sqrt( Complex &r, Complex const &x )
    { r = 1.0/std::sqrt(x); }
  static void _root4( Complex &r, Complex const &x )
    { r = std::pow(x, 0.25); }

  uint _count;

  // disabled copy constructor
  Fourier( Fourier const & );

  // disabled assignment operator
  Fourier &operator=( Fourier const & );

};

} // namespace loop

#endif // loop_Fourier_INCLUDED

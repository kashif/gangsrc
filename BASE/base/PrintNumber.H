/* GANG Software
 * BASE/base/PrintNumber.H
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

#ifndef base_PrintNumber_INCLUDED
#define base_PrintNumber_INCLUDED

#include <complex>
#include <iostream>
#include "System.H"

namespace base {

#ifdef __linux__
  typedef unsigned long FlagType;
#else
  typedef long FlagType;
#endif

// print a real in c format
template<class A>
inline void
_print( std::ostream &o, A const &x, uint precision_ )
{
  // save current state
  FlagType flags = o.flags();
  int long precision = o.precision();
  o.precision(precision_);
  o.setf(std::ios::scientific, std::ios::floatfield);
  o.width(precision_+7);

  // print
  o << x;

  // restore original state
  o.precision( (int)precision );
  o.flags( flags );
}

// print a real in mathematica format
template<class A>
inline void
_printM( std::ostream &o, A const &x, uint precision_ )
{
  // print in form "d.ddddddd*10^+dd

  // save current state
  FlagType flags = o.flags();
  int long precision = o.precision();
  o.precision(precision_);
  o.setf(std::ios::fixed, std::ios::floatfield);
  o.setf(std::ios::showpos);
  o.width(precision_+3);

  int exponent = 0;
  double mantissa = 0;

  if ( x != 0.0 )
  {
    exponent = (int)floor(log10(fabs(x)));
    mantissa = x/pow(double(10.0), double(exponent));
  }
  o << mantissa << "*10^" << exponent;

  // restore original state
  o.precision( (int)precision );
  o.flags( flags );
}

// print a complex in c format
template<class A>
inline void
print( std::ostream &o, std::complex<A> const &x )
{
  o << "(";
  print( o, x.real() );
  o << ", ";
  print( o, x.imag() );
  o << ")";
}

// print a complex in mathematica format
template <class A>
inline void
printM( std::ostream &o, std::complex<A> const &z )
{
  // prints in the format +x+y*I
  double u = z.real();
  double v = z.imag();

  if ( v == double(0.0) )
  {
    printM(o, u);
  }
  else
  {
    if ( u == double(0.0) )
    {
      printM(o, v);
      o << "*I";
    }
    else
    {
      printM(o, u);
      printM(o, v);
      o << "*I";
    }
  }
}

// print in c format with newlline
template <class A>
inline void
println( std::ostream &o, A const &x )
{
  print(o, x);
  o << '\n';
}

// print in Mathematica format with newlline
template <class A>
inline void
printMln( std::ostream &o, A const &x )
{
  printM(o, x);
  o << '\n';
}

// SPECIALIZED VERSIONS

// c versions
inline void print( std::ostream &o, float x )
{ _print( o, x, 8U ); }

inline void print( std::ostream &o, double x )
{ _print( o, x, 15U ); }

inline void print( std::ostream &o, double long x )
{ _print( o, x, 30U ); }

// mathematica versions
inline void printM( std::ostream &o, float x )
{ _printM( o, x, 8U ); }

inline void printM( std::ostream &o, double x )
{ _printM( o, x, 15U ); }

inline void printM( std::ostream &o, double long x )
{ _printM( o, x, 30U ); }

} // namespace base

#endif // base_PrintNumber_INCLUDED

/* GANG Software
 * BASE/base/String.H
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

#ifndef base_String_INCLUDED
#define base_String_INCLUDED

#include <stdio.h>
#include <errno.h>
#include <complex>
#include <string>
#include "System.H"
#include "vector.H"
#include "Exception.H"

namespace base {

class String
  :
  public std::string
{

public:

  // constructor
  explicit String()
      : std::string() {}

  String (const base::String& str)
      : std::string(str) {}
  String (const std::string& str)
      : std::string(str) {}

  String (const std::string& str, size_type pos, size_type n = npos)
      : std::string( str, pos, n ) {}

  String (char const *s, size_type n)
#if defined(DEBUG)
      : std::string()
    {
      DIE_IF( s == (char *)0 );
      *this = std::string(s, n);
    }
#else
      : std::string( s, n ) {}
#endif

  String (char const *s)
#if defined(DEBUG)
      : std::string()
    {
      DIE_IF( s == (char *)0 );
      *this = std::string(s);
    }
#else
      : std::string( s ) {}
#endif

  String (size_type n, char c)
      : std::string( n, c ) {}
#ifdef __STL_MEMBER_TEMPLATES
  template<class InputIterator>
  String(InputIterator __begin, InputIterator __end)
      : std::string(__begin, __end) {}
#else
  String(const_iterator __begin, const_iterator __end)
      : std::string(__begin, __end) {}
#endif

  // destructor
  virtual ~String() {}

  // assignment operator
  String &operator=( base::String const &a )
    { std::string::operator=(a); return *this; }
  String &operator=( char const *s )
    {
      DIE_IF(s == (char *)0);
      std::string::operator=(s);
      return *this;
    }
  String &operator=( char a )
    { std::string::operator=(a); return *this; }

  void strip( std::string const & );
  void strip()
    { strip(*this); }

  void uppercase( std::string const &s );
  void uppercase()
    { uppercase(*this); }
  void lowercase( std::string const &s );
  void lowercase()
    { lowercase(*this); }

  static int compare_nocase( std::string const &, std::string const & );
  int find_nocase(base::vector<String> const &,
                  std::string const &pattern);

  // splits s into whitespace-separated words
  int split( base::vector<String> &w ) const;

  void to_number( int &x ) const
    { _to_long( x ); }
  void to_number( int unsigned &x ) const
    { _to_ulong( x ); }
  void to_number( int short &x ) const
    { _to_long( x ); }
  void to_number( int unsigned short &x ) const
    { _to_ulong( x ); }
  void to_number( int long &x ) const
    { _to_long( x ); }
  void to_number( int unsigned long &x ) const
    { _to_ulong( x ); }
  void to_number( float &x ) const
    { _to_double( x ); }
  void to_number( double &x ) const
    { _to_double( x ); }
  void to_number( double long &x ) const
    { _to_double( x ); }


  void to_string( int const &x )
    { _to_string( x ); }
  void to_string( int unsigned const &x )
    { _to_string( x ); }
  void to_string( int short const &x )
    { _to_string( x ); }
  void to_string( int unsigned short const &x )
    { _to_string( x ); }
  void to_string( int long const &x )
    { _to_string( x ); }
  void to_string( int unsigned long const &x )
    { _to_string( x ); }
  void to_string( float const &x )
    { _to_string( x ); }
  void to_string( double const &x )
    { _to_string( x ); }
  void to_string( double long const &x )
    { _to_string( x ); }

  void to_string( std::complex<float> const &x )
    { _to_string(x); }
  void to_string( std::complex<double> const &x )
    { _to_string(x); }
  void to_string( std::complex<double long> const &x )
    { _to_string(x); }

protected:

private:

  template <class A>
  static char const *_format_string()
    { DIE(); return (char *)0; }

  template <class A>
  static int sign( A a )
    { return ( a > 0 ? 1 : ( a < 0 ? -1 : 0 ) ); }


  template <class A>
  void _to_long( A & ) const;
  template <class A>
  void _to_ulong( A & ) const;
  template <class A>
  void _to_double( A & ) const;

  template <class A>
  void _to_string( A const &x );
  template <class A>
  void _to_string( std::complex<A> const & );

};

template <>
inline char const * String::_format_string<int>() { return "%d"; }
template <>
inline char const * String::_format_string<int long>() { return "%ld"; }
template <>
inline char const * String::_format_string<int unsigned>() { return "%u"; }
template <>
inline char const * String::_format_string<int unsigned long>() { return "%lu"; }
template <>
inline char const * String::_format_string<float>() { return "%g"; }
template <>
inline char const * String::_format_string<double>() { return "%g"; }
template <>
inline char const * String::_format_string<double long>() { return "%Lg"; }

template <class A>
void
String::
_to_long( A &x ) const
{
  errno = 0;
  char *p = (char *)0;
  long int w = strtol( c_str(), &p, 10);
  x = static_cast<A>(w);
  if ( p == c_str() || errno != 0 )
  { throw Exception("error converting to number"); }
}

template <class A>
void
String::
_to_ulong( A &x ) const
{
  errno = 0;
  char *p = (char *)0;
  long int unsigned w = strtoul( c_str(), &p, 10);
  x = static_cast<A>( w );
  if ( p == c_str() || errno != 0 )
  { throw Exception("error converting to number"); }
}

template <class A>
void
String::
_to_double( A &x ) const
{
  errno = 0;
  char *p = (char *)0;
  double w = strtod( c_str(), &p);
  x = static_cast<A>( w );
  if ( p == c_str() || errno != 0 )
  { throw Exception("error converting to number"); }
}

template <class A>
void
String::
_to_string( A const &x )
{
  char c[128]; // NOTE: can this overflow
  char const *format = _format_string<A>();
  sprintf( c, format, x );
  (*this) = c;
}

template <class A>
void
String::
_to_string( std::complex<A> const &z )
{
  erase();

  A re = std::real(z);
  A im = std::imag(z);
  bool flag= false;

  if ( z == std::complex<A>(0.0) )
  {
    (*this) = "0";
    goto end;
  }

  if ( re != 0 )
  {
    to_string( re );
    flag = true;
  }

  if ( im == 1.0 )
  {
    (*this) += ( flag ? "+i" : "i" );
  }
  else if ( im == -1 )
  {
    (*this) += ( flag ? "+i" : "-i" );
  }
  else if ( im != 0.0 )
  {
    base::String t;
    t.to_string( im );
    if ( im > 0.0 && flag ) { (*this) += "+"; }
    (*this) += t;
    (*this) += "i";
  }
  end:
  ;
}

} // namespace base

#endif // base_String_INCLUDED

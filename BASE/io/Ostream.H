/* GANG Software
 * BASE/io/Ostream.H
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

#ifndef io_Ostream_INCLUDED
#define io_Ostream_INCLUDED

#include <complex>
#include "base/System.H"
#include "base/PrintNumber.H"
#include "Type.H"
#include "WriteException.H"

namespace io {


/*
  Write to a variety of streams.
  NOTE: should be implemented as separate classes.
*/

class Ostream
{

public:
  
  virtual ~Ostream() {}

  virtual std::ostream &stream() = 0;

  virtual Ostream &operator<<( char const *x )
    { stream() << x; return *this; }

  virtual Ostream &operator<<( int x )
    { stream() << x; return *this; }

  virtual Ostream &operator<<( uint x )
    { stream() << x; return *this; }

  virtual Ostream &operator<<( float x )
    { print(x) ; return *this; }

  virtual Ostream &operator<<( double x )
    { print(x); return *this; }

  virtual Ostream &operator<<( std::complex<float> const &x )
    { print(x); return *this; }

  virtual Ostream &operator<<( std::complex<double> const &x )
    { print(x); return *this; }

  virtual Ostream &operator<<( base::String const &x )
    { stream() << x; return *this; }

  virtual void write( char const *buffer, uint buffer_len )
    { stream().write( buffer, buffer_len ); }
  virtual void write( char unsigned const *buffer, uint buffer_len )
    { stream().write( (char const *)buffer, buffer_len ); }

  virtual void flush()
    { stream().flush(); }

  template <class A>
  void print( A x );

  virtual base::String const &filename() const
    { return _filename; }

  virtual StreamType type() const = 0;

  void mode( WriteMode m )
    { _mode = m; }
  WriteMode mode() const
    { return _mode; }

protected:

  Ostream( base::String const &filename) : _filename(), _mode(CMODE)
    {
      if ( filename.empty() )
      { throw WriteException(WriteException::OPEN_ERROR, base::String()); }
      _filename = filename;
    }
  Ostream() : _filename(), _mode(CMODE) {}

private:

  base::String _filename;

  WriteMode _mode;

  // disabled copy constructor
  Ostream( Ostream const & );
  // disabled assignment operator
  Ostream &operator=( Ostream const & );
};

template <class A>
void
Ostream::
print( A x )
{
  if ( _mode == CMODE )
  {
    stream() << x;
  }
  else if ( _mode == CMODE_SCIENTIFIC )
  {
    base::print(stream(), x);
  }
  else if ( _mode == MATHEMATICA )
  {
    base::printM(stream(), x);
  }
  else
  {
    DIE();
  }
}

} // namespace io

#endif // io_Ostream_INCLUDED

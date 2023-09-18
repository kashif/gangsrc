/* GANG Software
 * BASE/io/BinaryOstream.H
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

#ifndef io_BinaryOstream_INCLUDED
#define io_BinaryOstream_INCLUDED

#include <iostream>

namespace io {

class BinaryOstream
{

public:
  // constructor
  BinaryOstream( std::ostream &stream )
    { _ostream = &stream; }

  // destructor
  virtual ~BinaryOstream() {};

  std::ostream &stream() { return *_ostream; }

#if 0
  void write( bool x )
    { _ostream->write( (char *)&x, sizeof(x) ); }
#endif
  void write( char x )
    { _ostream->write( (char *)&x, sizeof(x) ); }
  void write( char unsigned x )
    { _ostream->write( (char *)&x, sizeof(x) ); }
  void write( int short x )
    { _ostream->write( (char *)&x, sizeof(x) ); }
  void write( int unsigned short x )
    { _ostream->write( (char *)&x, sizeof(x) ); }
  void write( int x )
    { _ostream->write( (char *)&x, sizeof(x) ); }
  void write( uint x )
    { _ostream->write( (char *)&x, sizeof(x) ); }
  void write( int long x )
    { _ostream->write( (char *)&x, sizeof(x) ); }
  void write( int unsigned long x )
    { _ostream->write( (char *)&x, sizeof(x) ); }
#if 0
  void write( int long long x )
    { _ostream->write( (char *)&x, sizeof(x) ); }
  void write( int unsigned long long x )
    { _ostream->write( (char *)&x, sizeof(x) ); }
#endif
  void write( float x )
    { _ostream->write( (char *)&x, sizeof(x) ); }
  void write( double x )
    { _ostream->write( (char *)&x, sizeof(x) ); }
  void write( long double x )
    { _ostream->write( (char *)&x, sizeof(x) ); }
#if 0
  void write( char * x )
    { _ostream->write( (char *)&x, sizeof(x) ); }
  void write( char const * x )
    { _ostream->write( (char *)&x, sizeof(x) ); }
  void write( void * x )
    { _ostream->write( (char *)&x, sizeof(x) ); }
  void write( void const * x )
    { _ostream->write( (char *)&x, sizeof(x) ); }
#endif
#if 0
  BinaryOstream &operator<<( bool x )
    { write(x); return *this; }
#endif
  BinaryOstream &operator<<( char x )
    { write(x); return *this; }
  BinaryOstream &operator<<( char unsigned x )
    { write(x);  return *this; }
  BinaryOstream &operator<<( int short x )
    { write(x);  return *this; }
  BinaryOstream &operator<<( int unsigned short x )
    { write(x);  return *this; }
  BinaryOstream &operator<<( int x )
    { write(x);  return *this; }
  BinaryOstream &operator<<( uint x )
    { write(x);  return *this; }
  BinaryOstream &operator<<( int long x )
    { write(x);  return *this; }
  BinaryOstream &operator<<( int unsigned long x )
    { write(x);  return *this; }
#if 0
  BinaryOstream &operator<<( int long long x )
    { write(x); return *this; }
  BinaryOstream &operator<<( int unsigned long long x )
    { write(x); return *this; }
#endif
  BinaryOstream &operator<<( float x )
    { write(x); return *this; }
  BinaryOstream &operator<<( double x )
    { write(x);  return *this; }
  BinaryOstream &operator<<( long double x )
    { write(x);  return *this; }
#if 0
  BinaryOstream &operator<<( char * x )
    { write(x);  return *this; }
  BinaryOstream &operator<<( char const * x )
    { write(x);  return *this; }
  BinaryOstream &operator<<( void * x )
    { write(x);  return *this; }
  BinaryOstream &operator<<( void const * x )
    { write(x);  return *this; }
#endif
  void flush()
    { _ostream->flush(); }

protected:

private:

  //
  std::ostream *_ostream;

  // disabled copy constructor
  BinaryOstream( BinaryOstream const & );

  // disabled assignment operator
  BinaryOstream &operator=( BinaryOstream const & );

};

} // namespace io

#endif // io_BinaryOstream_INCLUDED

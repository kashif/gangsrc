/* GANG Software
 * BASE/io/BinaryIstream.H
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

#ifndef io_BinaryIstream_INCLUDED
#define io_BinaryIstream_INCLUDED

#include <iostream>

namespace io {

class BinaryIstream
{

public:
  // constructor
  BinaryIstream( std::istream &stream )
    { _istream = &stream; }

  // destructor
  virtual ~BinaryIstream() {};

  std::istream &stream() { return *_istream; }

#if 0
  void read( bool &x )
    { _istream->read( (char *)&x, sizeof(x) ); }
#endif
  void read( char &x )
    { _istream->read( (char *)&x, sizeof(x) ); }
  void read( char unsigned &x )
    { _istream->read( (char *)&x, sizeof(x) ); }
  void read( int short &x )
    { _istream->read( (char *)&x, sizeof(x) ); }
  void read( int unsigned short &x )
    { _istream->read( (char *)&x, sizeof(x) ); }
  void read( int &x )
    { _istream->read( (char *)&x, sizeof(x) ); }
  void read( uint &x )
    { _istream->read( (char *)&x, sizeof(x) ); }
  void read( int long &x )
    { _istream->read( (char *)&x, sizeof(x) ); }
  void read( int unsigned long &x )
    { _istream->read( (char *)&x, sizeof(x) ); }
#if 0
  void read( int long long &x )
    { _istream->read( (char *)&x, sizeof(x) ); }
  void read( int unsigned long long &x )
    { _istream->read( (char *)&x, sizeof(x) ); }
#endif
  void read( float &x )
    { _istream->read( (char *)&x, sizeof(x) ); }
  void read( double &x )
    { _istream->read( (char *)&x, sizeof(x) ); }
  void read( long double &x )
    { _istream->read( (char *)&x, sizeof(x) ); }
#if 0
  void read( char * x )
    { _istream->read( (char *)&x, sizeof(x) ); }
  void read( char const * x )
    { _istream->read( (char *)&x, sizeof(x) ); }
  void read( void * x )
    { _istream->read( (char *)&x, sizeof(x) ); }
  void read( void const * x )
    { _istream->read( (char *)&x, sizeof(x) ); }
#endif
#if 0
  BinaryIstream &operator>>( bool &x )
    { read(x); return *this; }
#endif
  BinaryIstream &operator>>( char &x )
    { read(x); return *this; }
  BinaryIstream &operator>>( char unsigned &x )
    { read(x);  return *this; }
  BinaryIstream &operator>>( int short &x )
    { read(x);  return *this; }
  BinaryIstream &operator>>( int unsigned short &x )
    { read(x);  return *this; }
  BinaryIstream &operator>>( int &x )
    { read(x);  return *this; }
  BinaryIstream &operator>>( uint &x )
    { read(x);  return *this; }
  BinaryIstream &operator>>( int long &x )
    { read(x);  return *this; }
  BinaryIstream &operator>>( int unsigned long &x )
    { read(x);  return *this; }
#if 0
  BinaryIstream &operator>>( int long long &x )
    { read(x); return *this; }
  BinaryIstream &operator>>( int unsigned long long &x )
    { read(x); return *this; }
#endif
  BinaryIstream &operator>>( float &x )
    { read(x); return *this; }
  BinaryIstream &operator>>( double &x )
    { read(x);  return *this; }
  BinaryIstream &operator>>( long double &x )
    { read(x);  return *this; }
#if 0
  BinaryIstream &operator>>( char * x )
    { read(x);  return *this; }
  BinaryIstream &operator>>( char const * x )
    { read(x);  return *this; }
  BinaryIstream &operator>>( void * x )
    { read(x);  return *this; }
  BinaryIstream &operator>>( void const * x )
    { read(x);  return *this; }
#endif
protected:

private:

  //
  std::istream *_istream;

  // disabled copy constructor
  BinaryIstream( BinaryIstream const & );

  // disabled assignment operator
  BinaryIstream &operator=( BinaryIstream const & );

};

} // namespace io

#endif // io_BinaryIstream_INCLUDED

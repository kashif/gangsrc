/* GANG Software
 * BASE/base/LineStream.C
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

#include <stdio.h>
#include "System.H"
#include "LineStream.H"

namespace base {

char const LineStream::SPACE = ' ';
char const LineStream::NEWLINE = '\n';
size_t const LineStream::NPOS = (size_t)(-1);

LineStream::
LineStream( std::ostream &o, int linewidth )
{
  DIE_IF(linewidth == 1);

  _buf_len = linewidth + 1;
  _buffer = new char[_buf_len];
  _buf_start = 0;
  _buf_end = 0;
  _ostream = &o;
  _linebreak = NPOS;
}


LineStream::
~LineStream()
{
  _flush();
  delete [] _buffer;
}


inline
void
LineStream::
_inc( size_t &x )
{
  x = ( x == _buf_len - 1 ? 0 : x + 1 );
}


void
LineStream::
_dec( size_t &x )
{
  x = ( x == 0 ? _buf_len - 1 : x - 1 );
}

void
LineStream::
_flush()
{
  while ( _buf_start != _buf_end )
  {
    *_ostream << _buffer[_buf_start];
    _inc( _buf_start );
  }
}


LineStream &
LineStream::
put( char c )
{
  // insert a single char to the stream
  if (_buf_len == 1 )
  {
    // line splitting disabled
    _ostream->put(c);
    return *this;
  }


  // write a newline
  if ( c == NEWLINE )
  {
    _flush();
    *_ostream << NEWLINE;
  }
  else
  {

    // put char into buffer
    _buffer[_buf_end] = c;
    _inc( _buf_end );

    if ( _buf_end == _buf_start )
    {
      // buffer is full (fully wrapped)

      if ( _linebreak != NPOS )
      {
        // linebreak found: write chars up to (but not including) _linebreak
        do
        {
          _ostream->put(_buffer[_buf_start]);
          _inc( _buf_start );
        }
        while ( _buf_start != _linebreak );

        // skip over space
        if ( _buffer[_linebreak] == SPACE )
        {
          _inc( _buf_start );
        }

        // reset _linebreak
        _linebreak = NPOS;
      }
      else
      {
        // no linebreak: write the whole buffer (except one char)
        // and append a "\"
        size_t i;
        for ( i = 0; i < _buf_len - 2; i++ )
        {
          *_ostream << _buffer[_buf_start];
          _inc( _buf_start );
        }
        *_ostream << "\\";
      }
      *_ostream << "\n";
    }
  }

  return *this;
}


LineStream &
LineStream::
put( char unsigned c )
{
  put( (char)c );
  return *this;
}


LineStream &
LineStream::
write( char const *s, int n )
{
  char const *s1 = s + n;
  for ( ; s < s1; s++ )
  {
    put( *s );
  }
  return *this;
}


LineStream &
LineStream::
write( char unsigned const *s, int n )
{
  char unsigned const *s1 = s + n;
  for ( ; s < s1; s++ )
  {
    put( *s );
  }
  return *this;
}


LineStream &
LineStream::
operator<<( char c )
{
  put( c );
  return *this;
}


LineStream &
LineStream::
operator<<( char unsigned c )
{
  put( c );
  return *this;
}


LineStream &
LineStream::
operator<<( signed short x )
{
  char s[40];
  sprintf( s, "%hd", x );
  operator<<(s);
  return *this;
}


LineStream &
LineStream::
operator<<( unsigned short x )
{
  char s[40];
  sprintf( s, "%hu", x );
  operator<<(s);
  return *this;
}


LineStream &
LineStream::
operator<<( signed int x )
{
  char s[40];
  sprintf( s, "%d", x );
  operator<<(s);
  return *this;
}


LineStream &
LineStream::
operator<<( unsigned int x )
{
  char s[40];
  sprintf( s, "%u", x );
  operator<<(s);
  return *this;
}


LineStream &
LineStream::
operator<<( signed long x )
{
  char s[40];
  sprintf( s, "%ld", x );
  operator<<(s);
  return *this;
}


LineStream &
LineStream::
operator<<( unsigned long x )
{
  char s[40];
  sprintf( s, "%lu", x );
  operator<<(s);
  return *this;
}


LineStream &
LineStream::
operator<<( float x )
{
  char s[40];
  sprintf( s, "%f", x );
  operator<<(s);
  return *this;
}


LineStream &
LineStream::
operator<<( double x )
{
  char s[40];
  sprintf( s, "%f", x );
  operator<<(s);
  return *this;
}


LineStream &
LineStream::
operator<<( long double x )
{
  char s[40];
  sprintf( s, "%Lf", x );
  operator<<(s);
  return *this;
}


LineStream &
LineStream::
operator<<( void * x )
{
  char s[40];
  sprintf( s, "%p", x );
  operator<<(s);
  return *this;
}


LineStream &
LineStream::
operator<<( char const *s )
{
  char const *t;
  for ( t = s; *t != 0; t++ )
  {
    put( *t );
  }
  return *this;
}


LineStream &
LineStream::
operator<<( char unsigned const *s )
{
  char unsigned const *t;
  for ( t = s; *t != 0; t++ )
  {
    put( *t );
  }
  return *this;
}


LineStream &
LineStream::
operator<<( base::String const &s )
{
  size_t i;
  for ( i = 0; i < s.length(); i++ )
  {
    put( s[i] );
  }
  return *this;
}

} // namespace base

/* GANG Software
 * BASE/base/LineStream.H
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

#ifndef base_LineStream_INCLUDED
#define base_LineStream_INCLUDED

#include <stddef.h>
#include <iostream>
#include "String.H"

namespace base {

/*
   Writes to a stream with linebreaking.

   Example:
<blockquote><font face="courier">
     LineStream out( std::cout );<br>
     out << "Hello ";<br>
     out.mark_linebreak();<br>
     out << "12345 ";<br>
     out.mark_linebreak();<br>
     ...<br>
</font></blockquote>
 */
class LineStream
{

public:
  /*
     Constructor.
     'o' is the stream to write to.
     'linewidth' is the maximum line length (>=2).
     'linewidth'==0 means don't split lines.
  */
  LineStream( std::ostream &o, int linewidth = 79 );

  // destructor
  ~LineStream();

  /*
     As you are writing to the LineStream, call this whenever a legal
     place to break the line occurs
  */
  void mark_linebreak()
    { _linebreak = _buf_end; }

  //
  LineStream &put( char c );
  //
  LineStream &put( char unsigned c );
  //
  LineStream &write( char const *s, int n );
  //
  LineStream &write( char unsigned const *s, int n );
  //
  LineStream &operator<<( char );

  LineStream &operator<<( char unsigned );
  //
  LineStream &operator<<( signed short );
  //
  LineStream &operator<<( unsigned short );
  //
  LineStream &operator<<( signed int );
  //
  LineStream &operator<<( unsigned int );
  //
  LineStream &operator<<( signed long );
  //
  LineStream &operator<<( unsigned long );
  //
  LineStream &operator<<( float );
  //
  LineStream &operator<<( double );
  //
  LineStream &operator<<( long double );
  //
  LineStream &operator<<( void * );
  //
  LineStream &operator<<( char const * );
  //
  LineStream &operator<<( char unsigned const * );
  //
  LineStream &operator<<( base::String const & );

private:
  // Rotating buffer.
  char *_buffer;

  // Buffer positions.
  size_t _buf_start, _buf_end;

  // Buffer length.
  size_t _buf_len;

  //
  size_t _linebreak;

  //
  std::ostream *_ostream;

  //
  inline void _inc( size_t & );
  //
  inline void _dec( size_t & );
  //
  void _flush();

  static char const SPACE;
  static char const NEWLINE;
  static size_t const NPOS;
};

} // namespace base

#endif // base_LineStream_INCLUDED

/* GANG Software
 * BASE/base/ReadUtil.H
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

#ifndef base_ReadUtil_INCLUDED
#define base_ReadUtil_INCLUDED

#include "String.H"
#include "Exception.H"
#include "Color3.H"
#include "Color4.H"

namespace base {

/*
  Read and parse space-separated entries.
*/

class ReadUtil
{

public:
  typedef double Real;

  // constructor
  ReadUtil();

  // destructor
  virtual ~ReadUtil();

  Real read_real( base::String const &s );
  uint read_uint( base::String const &s );
  bool read_bool( base::String const &s );
  void read_list( base::vector<uint> &v, uint n,
                         base::String const &s );
  void read_list( base::vector<float> &v, uint n,
                          base::String const &s );
  void read_list( base::vector<Real> &v, uint n,
                         base::String const &s );
  void read_color( base::Color4 &c, base::String const &s );
  void read_color( base::Color3 &c, base::String const &s );

  static bool equal( char const *a, char const *b )
    { return ! ::strcmp( a, b ); }

  virtual void error( char const *message )
    { throw base::Exception(message); }

protected:

  static void split1( base::String &a, base::String &b,
                      base::String const &s );

private:

  // disabled copy constructor
  ReadUtil( ReadUtil const & );
  // disabled assignment operator
  ReadUtil &operator=( ReadUtil const & );

};

} // namespace base

#endif // base_ReadUtil_INCLUDED

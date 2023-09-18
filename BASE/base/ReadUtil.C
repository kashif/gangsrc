/* GANG Software
 * BASE/base/ReadUtil.C
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

#include "Regex.H"
#include "ReadUtil.H"

namespace base {

ReadUtil::
ReadUtil()
{
}

ReadUtil::
~ReadUtil()
{
}



ReadUtil::Real
ReadUtil::
read_real( base::String const &s )
{
  Real x;
  try {
    s.to_number( x );
  }
  catch (base::Exception const &) {
    error( "syntax error reading real number" );
    return 0.0;
  }
  return x;
}

uint
ReadUtil::
read_uint( base::String const &s )
{
  uint x;
  try {
    s.to_number( x );
  }
  catch (base::Exception const &) {
    error( "syntax error reading integer" );
    return 0;
  }
  return x;
}

bool
ReadUtil::
read_bool( base::String const &s )
{
  uint x = read_uint( s );
  if (x != 0 && x != 1) {
    error( "unknown text" );
    return 0;
  }
  return x;
}

void
ReadUtil::
read_list( base::vector<Real> &v, uint size, base::String const &s )
{
  base::vector<base::String> w;
  s.split( w );

  if ( w.size() != size )
  {
    error( "wrong number of entries" );
    return;
  }
  v.clear();
  v.reserve(size);
  uint i;
  for ( i = 0; i < size; i++ )
  {
    v.push_back( read_real(w[i]) );
  }
  DIE_IF(v.size() != size);
}

void
ReadUtil::
read_list( base::vector<float> &v, uint size, base::String const &s )
{
  base::vector<base::String> w;
  s.split( w );

  if ( w.size() != size )
  {
    error( "wrong number of entries" );
    return;
  }
  v.clear();
  v.reserve(size);
  uint i;
  for ( i = 0; i < size; i++ )
  {
    v.push_back( read_real(w[i]) );
  }
  DIE_IF(v.size() != size);
}

void
ReadUtil::
read_list( base::vector<uint> &v, uint size, base::String const &s )
{
  base::vector<base::String> w;
  s.split( w );

  if ( w.size() != size )
  {
    error( "wrong number of entries" );
    return;
  }
  v.clear();
  v.reserve(size);
  uint i;
  for ( i = 0; i < size; i++ )
  {
    v.push_back( read_uint(w[i]) );
  }
  DIE_IF(v.size() != size);
}

void
ReadUtil::
read_color( base::Color3 &c, base::String const &s )
{
  base::vector<float> v;
  read_list( v, 3, s );
  uint i;
  for ( i = 0; i < 3; i++ )
  {
    if ( v[i] < 0.0 || v[i] > 1.0 )
    {
      error( "color specification out of range" );
    }
    c[i] = v[i];
  }
}

void
ReadUtil::
read_color( base::Color4 &c, base::String const &s )
{
  base::vector<float> v;
  read_list( v, 4, s );
  uint i;
  for ( i = 0; i < 4; i++ )
  {
    if ( v[i] < 0.0 || v[i] > 1.0 )
    {
      error( "color specification out of range" );
    }
    c[i] = v[i];
  }
}

void
ReadUtil::
split1(
  base::String &a, base::String &b,
  base::String const &s )
{
  base::vector<base::String> v;
  base::match( "^([^ ]+) +(.*)$", s, v );
  if ( v.size() == 3 )
  {
    a = v[1];
    b = v[2];
  }
  else
  {
    a = s;
    b.erase();
  }
}

} // namespace base

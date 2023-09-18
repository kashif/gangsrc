/* GANG Software
 * GEOM/geom/surface/MaterialSetBase.C
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

#include "io/OstreamStream.H"
#include "MaterialSetBase.H"

namespace geom {
namespace surface {

MaterialSetBase::
MaterialSetBase()
{
}

MaterialSetBase::
MaterialSetBase( MaterialSetBase const &a )
{
}

MaterialSetBase::
~MaterialSetBase()
{
}

MaterialSetBase &
MaterialSetBase::
operator=( MaterialSetBase const &a )
{
  if ( this == &a ) { return *this; }
  uint i;
  for ( i = 0; i < count(); i++ )
  {
    operator[](i) = a[i];
  }
  return *this;
}

void
MaterialSetBase::
reset_materials()
{
  uint i;
  for ( i = 0; i < count(); i++ )
  {
    reset_materials(i);
  }
}

void
MaterialSetBase::
reset_materials( uint n )
{
  operator[](n).reset();
  _reset(n);
}

void
MaterialSetBase::
_reset()
{
  uint i;
  for ( i = 0; i < count(); i++ )
  {
    _reset(i);
  }
}

void
MaterialSetBase::
_reset(uint n)
{
  if ( n == 0 || n == 3 )
  {
    // faces, faces2
    operator[](n).enable( n==0 );
    operator[](n).diffuse( base::Color4( 0.5f, 0.5f, 0.5f, 1.0f ) );
    operator[](n).specular( base::Color3(1.0f, 1.0f, 1.0f) );
    operator[](n).shininess(1.0f);
    uint const side[2] = { 3U, 3U };
    operator[](n).side(side);

#ifdef __linux__
    float const nudge[2] = { 0.0f, 0.0f };
#else
    float const nudge[2] = { 0.0f, 0.0f };
#endif
    operator[](n).nudge(nudge);
  }
  else if (n == 1)
  {
    // edges
    operator[](n).enable(true);
    operator[](n).color( base::Color4( 0.2f, 0.2f, 0.2f, 1.0f ) );
    operator[](n).diffuse( base::Color4( 0.2f, 0.2f, 0.2f, 1.0f ) );
    uint const side[2] = { 2U, 2U };
    operator[](n).side(side);
#ifdef __linux__
    float const nudge[2] = { 0.0f, -1.0f };
#else
    float const nudge[2] = { -1.0f, 0.0f };
#endif
    operator[](n).nudge(nudge);
  }
  else if (n == 2)
  {
    // vertices
    uint const side[2] = { 1U, 1U };
    operator[](n).side(side);
#ifdef __linux__
    float const nudge[2] = { 0.0f, -2.0f };
#else
    float const nudge[2] = { -2.0f, 0.0f };
#endif
    operator[](n).nudge(nudge);
  }
  else if (n >= LINE)
  {
    operator[](n).color( base::Color4( 0.7f, 0.7f, 0.7f, 1.0f ) );
    operator[](n).diffuse( base::Color4( 0.7f, 0.7f, 0.7f, 1.0f ) );
    uint const side[2] = { 2U, 2U };
    operator[](n).side(side);
    operator[](n).lit(false);
  }

#if 0
  std::cerr << "DUMP " << &operator[](0) << "\n";
  io::OstreamStream s(std::cerr);
  operator[](0).dump(s);
#endif
}

void
MaterialSetBase::
dump_materials( io::Ostream &o ) const
{
  char const *tab = "\t";
  o << tab << "<materialset>\n";
  uint i;
  for ( i = 0; i < count(); i++ )
  {
    dump_materials( i, o );
  }
  o << tab << "</materialset>\n";
}

void
MaterialSetBase::
dump_materials( uint i, io::Ostream &o ) const
{
  operator[](i).dump(o);
}

} // namespace surface
} // namespace geom

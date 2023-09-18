/* GANG Software
 * GEOM/milieu/kernel/Background.C
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

#include "Background.H"

namespace milieu {
namespace kernel {

Background::
Background()
{
}

Background::
Background( Background const &a )
{
  copy(a);
}

Background::
~Background()
{
}

Background &
Background::
operator=( Background const &a )
{
  copy(a);
  return *this;
}

void
Background::
reset()
{
  _color = base::Color3(0.0f, 0.0f, 0.0f );
}

void
Background::
copy( Background const &a )
{
  _color = a._color;
}

void
Background::
dump( io::Ostream &o ) const
{
  char const *tab = "\t\t";
  o << tab << "<background>\n";
  o << tab << "\t<color>"
    << _color[0] << " "
    << _color[1] << " "
    << _color[2] << "</color>\n";
  o << tab << "</background>\n";
}

} // namespace kernel
} // namespace milieu

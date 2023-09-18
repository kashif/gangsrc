/* GANG Software
 * GEOM/milieu/kernel/GlobalLight.C
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

#include "GlobalLight.H"

namespace milieu {
namespace kernel {

GlobalLight::
GlobalLight()
{
  reset();
}

GlobalLight::
GlobalLight( GlobalLight const &a )
{
  copy(a);
}

GlobalLight::
~GlobalLight()
{
}

GlobalLight &
GlobalLight::
operator=( GlobalLight const &a )
{
  copy(a);
  return *this;
}

void
GlobalLight::
reset()
{
  _enable = true;

  _ambient[0] = 0.2;
  _ambient[1] = 0.2;
  _ambient[2] = 0.2;

  _viewpoint = false;
  _sidedness = true;
}

void
GlobalLight::
copy( GlobalLight const &a )
{
  _enable = a._enable;
  _ambient = a._ambient;
  _viewpoint = a._viewpoint;
  _sidedness = a._sidedness;
}

void
GlobalLight::
dump( io::Ostream &o ) const
{
  char const *tab = "\t\t";
  o << tab << "<lightmodel>\n";
  o << tab << "\t<enable>" << _enable << "</enable>\n";
  o << tab << "\t<ambient>"
    << _ambient[0] << " "
    << _ambient[1] << " "
    << _ambient[2] << "</ambient>\n";
  o << tab << "\t<viewpoint>" << _viewpoint << "</viewpoint>\n";
  o << tab << "\t<sidedness>" << _sidedness << "</sidedness>\n";
  o << tab << "</lightmodel>\n";
}

} // namespace kernel
} // namespace milieu

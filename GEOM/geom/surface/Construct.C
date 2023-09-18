/* GANG Software
 * GEOM/geom/surface/Construct.C
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

#include "geom/surface0/Reflector.H"
#include "geom/surface0/Surface.H"
#include "geom/surface0/Translator.H"
#include "geom/surface0/Reflector.H"
#include "geom/surface0/TransformerMatrix.H"
#include "Construct.H"

namespace geom {
namespace surface {

Construct::
Construct()
{
}

Construct::
~Construct()
{
}
Construct::
Construct( Construct const &a )
    :
    SurfaceBase(a)
{
}

Construct &
Construct::
operator=( Construct const &a )
{
  if ( this == &a ) { return *this; }
  SurfaceBase::operator=(a);
  return *this;
}

geom::Real
Construct::
glue(
  uint g0,
  uint g1,
  std::list<uint> const &boundary )
{
  // Glue g1 to g0. Remove g1

  DIE_IF(g0 == g1);
  DIE_IF( g0 >= list().size() );
  DIE_IF( g1 >= list().size() );

  // find g0 and g1 in list()
  std::list<surface0::GeomObject *>::iterator i;
  std::list<surface0::GeomObject *>::iterator geom1_iter;
  surface0::GeomObject *geom = (surface0::GeomObject *)0;
  surface0::GeomObject *geom1 = (surface0::GeomObject *)0;
  uint n = 0;
  for ( i = list().begin(); i != list().end(); i++ )
  {
    if (n == g0) { geom = *i; }
    if (n == g1) { geom1 = *i; geom1_iter = i; }
    n++;
  }

  DIE_IF(geom == (surface0::GeomObject *)0);
  DIE_IF(geom1 == (surface0::GeomObject *)0);

  Real gluesep = 0.0;

  if ( geom->dimension() == 2U && geom1->dimension() == 2U )
  {
    surface0::Surface *h0 = surface(geom);
    surface0::Surface *h1 = surface(geom1);
    if ( h0->type() == h0->INDEXED && h1->type() == h1->INDEXED )
    {
      Real x = h0->glue( h1, boundary );
      if ( x > gluesep ) { gluesep = x; }
    }
  }

  // remove glued geometry
  delete geom1;
  list().erase(geom1_iter);
  changed();

  return gluesep;
}

geom::Real
Construct::
glue_self(
  uint part,
  std::list<uint> const &boundaryset1,
  std::list<uint> const &boundaryset2 )
{
  // Glue part of g to self

  DIE_IF( part >= list().size() );

  // find part in list()
  std::list<surface0::GeomObject *>::iterator i;
  surface0::GeomObject *geom = (surface0::GeomObject *)0;
  uint n = 0;
  for ( i = list().begin(); i != list().end(); i++ )
  {
    if (n == part) { geom = *i; break; }
    n++;
  }

  DIE_IF(geom == (surface0::GeomObject *)0);

  Real gluesep = 0.0;

  if ( geom->dimension() == 2U )
  {
    surface0::Surface *h = surface(geom);
    if ( h->type() == h->INDEXED )
    {
      Real x = h->glue_self( boundaryset1, boundaryset2 );
      if ( x > gluesep ) { gluesep = x; }
    }
  }

  changed();

  return gluesep;
}

void
Construct::
reverse_orientation()
{
  std::list<surface0::GeomObject *>::iterator i;
  for ( i = list().begin(); i != list().end(); i++ )
  {
    if ( (*i)->dimension() == 2U )
    {
      surface0::Surface *s = surface(*i);
      if ( s->type() == s->INDEXED )
      {
        s->reverse_orientation();
      }
    }
  }
}

#if 0
void
Construct::
reverse_orientation( surface0::GeomObject *g )
{
  // Reversed the orientation of each face by reversing the order of its
  // indices. Does not affect meshes

}
#endif

void
Construct::
apply(
  ::geom::surface0::Transformer const &T )
{
  std::list<surface0::GeomObject *>::iterator i;
  for ( i = list().begin(); i != list().end(); i++ )
  {
    surface0::Surface *g2 = surface(*i);
    g2->apply( T );
  }
}

void
Construct::
transform(
  geom::Transform const &a )
{
  std::list<surface0::GeomObject *>::iterator i;
  for ( i = list().begin(); i != list().end(); i++ )
  {
    surface0::Surface *g2 = surface(*i);
    g2->transform(a);
  }
}

void
Construct::
translate(
  math::VectorX<Real,3U> const &a )
{
  std::list<surface0::GeomObject *>::iterator i;
  for ( i = list().begin(); i != list().end(); i++ )
  {
    surface0::Surface *g2 = surface(*i);
    g2->translate(a);
  }
}

void
Construct::
reflect(
  math::VectorX<Real,4U> const &a )
{
  std::list<surface0::GeomObject *>::iterator i;
  for ( i = list().begin(); i != list().end(); i++ )
  {
    surface0::Surface *g2 = surface(*i);
    g2->reflect(a);
  }
}

void
Construct::
build_reflect(
  math::VectorX<Real,4U> const &a )
{
  if ( list().empty() ) { return; }

  surface0::Reflector T(a);

  // create a temporary list 'tmp'
  std::list<surface0::GeomObject *> tmp;

  // reflect the existing surface into 'tmp'
  std::list<surface0::GeomObject *>::iterator i;
  for ( i = list().begin(); i != list().end(); i++ )
  {
//    surface0::GeomObject *g = (*i)->clone();
    surface0::Surface *g2 =
      new surface0::Surface( *surface(*i) );

    g2->apply(T);

    g2->reverse_orientation();

    tmp.push_back(g2);
  }

  // splice the temporary list onto the end of the existing surface
  list().splice( list().end(), tmp);

  changed();
}

void
Construct::
remove_to_one()
{
  // restores the surface to unreflected state
  // clear all parts of surface but the first
  // NOTE: this assumes the base surface is 1 part, and the added parts
  //   are from a previous reflection

  std::list<surface0::GeomObject *>::iterator i;
  for ( i = list().begin(), i++; i != list().end(); i++ )
  {
    delete (*i);
  }
  if ( size() >= 1 )
  {
    i = list().begin();
    i++;
    list().erase( i, list().end());
    DIE_IF( list().size() != 1 );
  }
  changed();
}

} // namespace surface
} // namespace geom

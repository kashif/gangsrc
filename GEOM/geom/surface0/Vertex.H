/* GANG Software
 * GEOM/geom/surface0/Vertex.H
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

#ifndef geom_surface0_Vertex_INCLUDED
#define geom_surface0_Vertex_INCLUDED

#include "base/vector.H"
#include <iostream.h>
#include "Common.H"

namespace geom {
namespace surface0 {

/*
  Vertex data structure
*/
/*
A Vertex represents a point on a surface.

There are two projection modes: central and stereographic.
A Vertex is exported according to the projection mode.

Let N = the dimension of the ambient space of the surface.
A Vertex stores N+2 real numbers (v[0]...v[N+1]). In the following
comments, these are called (y[1]...y[N], y[0], y[inf]).

In central projection mode, only the first N+1 real numbers
(y[1]...y[N], y[0]) are used. The last real number y[inf] is not
used. The first N+1 coordinates are interpreted as homogeneous
coordinates in RP^N. The Vertex is exported in either of two ways:

  point in RP^N:
    [ y[1] ... y[N] ]
  point in R^N via central projection:
    ( y[1] ... y[N-1] ) / y[N]

In stereographic projection mode, all N+2 real numbers are used.
First, comments in a different coordinate system x[1]...x[N],x[0],x[inf].
The last real number x[inf] is precomputed so that
(x[1]...x[N],x[0],x[inf]) lies in the projective quadric
  Q:  x[1]^2 + ... + x[N]^2 + x[0]^2 - x[inf]^2 = 0.
The Vertex is exported as

  point in RP^(N+1):
    [ x[0] ... x[N], x[inf] - x[0] ]
  point in R^N via stereographic projection:
    ( x[1] ... x[N] ) / (x[inf] - x[0])

The numbers x[1]...x[N],x[0],x[inf] are stored in a memory-efficient
way, namely as
  y[1]...y[n],y[0],y[inf]
where
  y[1] = x[1]
  ...
  y[N] = x[N]
  y[0] = x[inf]-x[0]
  y[inf] = x[inf] + x[0]
so
  x[1] = y[1]
  ...
  x[N] = y[N]
  x[0] = (y[inf]-y[0])/2
  x[inf] = (y[inf] + y[0])/2
Under this change of coordinates, the quadric
  Q:  x[1]^2 + ... + x[N]^2 + x[0]^2 - x[inf]^2 = 0.
becomes
  Q':  y[1]^2 + ... + y[N]^2 - y[0] y[inf] = 0.
Thus y[inf] is computed as
  y[inf] = (y[1]^2 + ... + y[N]^2)/y[0].
  */

class Vertex
{

public:

  // constructor
  inline Vertex( SpaceForm const & );

  // copy constructor
  inline Vertex( Vertex const & );

  // destructor
  inline virtual ~Vertex() {}

  // assignment operator
  inline Vertex &operator=( Vertex const & );

  void import( Vertex2 const &v )
    { import_inhomogeneous(v, 2U); }
  void import( Vertex3 const &v )
    { import_inhomogeneous(v, 3U); }
  void import( Vertex4 const &v )
    { import_inhomogeneous(v, 4U); }
  void import( math::Vector<Real> const &v )
    { import_inhomogeneous(v, v.size()); }
  template <class T>
  inline void import( base::vector<T> const &v );

  void export_( Vertex2 &v ) const
    { export_inhomogeneous(v, 2U); }
  void export_( Vertex3 &v ) const
    { export_inhomogeneous(v, 3U); }
  void export_( Vertex4 &v ) const
    { export_homogeneous(v, 3U); }
  void export_( math::Vector<Real> &v ) const
    { export_inhomogeneous(v, v.size()); }
  void export_( Vertex4 &v, Transform const &t, ProjectionMode p ) const
    { export_homogeneous(v, 3U, t, p); }

#if 0
  void import( base::vector<float> const &v, SpaceForm spaceform );
  void import( base::vector<double> const &v, SpaceForm spaceform );
#endif

  friend std::ostream &operator<<( std::ostream &o, Vertex const & );

protected:

private:
  
#if 0
  template <class T>
  void import_homogeneous( T const &, uint N );
#endif
  template <class T>
  void import_inhomogeneous( T const &, uint N );

  template <class T>
  void export_homogeneous( T &, uint N ) const;

  template <class T>
  void export_inhomogeneous( T &, uint N ) const;

  template <class T>
  void export_homogeneous( T &, uint N, Transform const &t,
                           ProjectionMode p) const;

  static void mulleft( Real const *, Real *, uint );

  template <class T>
  void import_S( base::vector<T> const &v );

  template <class T>
  void import_H( base::vector<T> const &v );

  SpaceForm _spaceform;
  math::Vector<Real> _x;
  Real _xp;
  Real _x0;
  Real _xi;
};

Vertex::
Vertex( SpaceForm const &spaceform )
    :
    _spaceform(spaceform)
{
  _x.allocate(_spaceform.dim);
  _x.set(0.0f);
  _xp = 1.0f;
  _x0 = 1.0f;
  _xi = 0.0f;
}

Vertex::
Vertex( Vertex const &a )
    :
    _spaceform(a._spaceform),
    _x(a._x),
    _xp(a._xp),
    _x0(a._x0),
    _xi(a._xi)
{
}

Vertex &
Vertex::
operator=( Vertex const &a )
{
  if ( this != &a )
  {
    _spaceform = a._spaceform;
    _x = a._x;
    _xp = a._xp;
    _x0 = a._x0;
    _xi = a._xi;
  }
  return *this;
}

template <class T>
void
Vertex::
import(
  base::vector<T> const &v )
{
  if (_spaceform.space == SpaceForm::SPACEFORM_R)
  { import_inhomogeneous(v, v.size()); }
  else if (_spaceform.space == SpaceForm::SPACEFORM_S)
  { import_S( v ); }
  else if (_spaceform.space == SpaceForm::SPACEFORM_H)
  { import_H( v ); }
  else
  { DIE(); }
}

template <class T>
void
Vertex::
import_S( base::vector<T> const &v )
{
  DIE_IF( _spaceform.space != SpaceForm::SPACEFORM_S );
  DIE_IF( v.size() != _spaceform.dim + 1U );

  if ( _spaceform.dim == 3U )
  {
    _x[0] = v[0];
    _x[1] = v[1];
    _x[2] = v[2];

    // NOTE: is this negative?
    _xp = 1.0f - v[3];
    _x0 = v[3];
    _xi = math::sqrt( math::sqr(v[0]) + math::sqr(v[1]) +
                      math::sqr(v[2]) + math::sqr(v[3]) );
  }
  else
  {
    uint n = _spaceform.dim;
    uint i;
    for ( i = 0; i < n; i++ )
    {
      _x[i] = v[i];
    }

    _xp = 1.0f - v[n];
    _x0 = v[n];

    T s = 0;
    for ( i = 0; i < n; i++ ) { s += math::sqr(v[i]); }
    _xi = math::sqrt( s );
  }
}

template <class T>
void
Vertex::
import_H( base::vector<T> const &v )
{
  DIE_IF( _spaceform.space != SpaceForm::SPACEFORM_H );
  DIE_IF( v.size() != _spaceform.dim + 1U );

  if ( _spaceform.dim == 3U )
  {
    _x[0] = v[0];
    _x[1] = v[1];
    _x[2] = v[2];

    // NOTE: is this negative?
    _xp = 1.0f - v[3];
    _xi = v[3];
    _x0 = math::sqrt( -math::sqr(v[0]) - math::sqr(v[1]) - math::sqr(v[2]) +
                      math::sqr(v[3]) );
  }
  else
  {
    uint n = _spaceform.dim;
    uint i;
    for ( i = 0; i < n; i++ )
    {
      _x[i] = v[i];
    }

    _xp = 1.0f - v[n];
    _x0 = v[n];

    T s = 0;
    for ( i = 0; i < n-1; i++ ) { s += math::sqr(v[i]); }
    _xi = math::sqrt( -s + math::sqr(v[n]) );
  }
}

template <class T>
void
Vertex::
import_inhomogeneous( T const &v, uint N )
{
  uint n = std::min( _spaceform.dim, N );
  uint i;
  for ( i = 0; i < n; i++ ) { _x[i] = v[i]; }
  for ( i = n; i < _spaceform.dim; i++ ) { _x[i] = 0.0f; }
  _xp = 1.0f;

  Real x = 0.0f;
  for ( i = 0; i < n; i++ ) { x += math::sqr(_x[i]); }
  _x0 = 0.5f * ( x - 1.0f );
  _xi = 0.5f * ( x + 1.0f );
}

template <class T>
void
Vertex::
export_homogeneous( T &v, uint N ) const
{
  // central projection

  uint n = std::min( _spaceform.dim, N );
  uint i;
  for ( i = 0; i < n; i++ ) { v[i] = _x[i]; }
  for ( i = n; i < N; i++ ) { v[i] = 0.0f; }
  v[N] = _xp;
}


template <class T>
void
Vertex::
export_inhomogeneous( T &v, uint N ) const
{
  // central projection

  uint n = std::min( _spaceform.dim, N );
  uint i;
  for ( i = 0; i < n; i++ ) { v[i] = _x[i]/_xp; }
  for ( i = n; i < N; i++ ) { v[i] = 0.0f; }
}


template <class T>
void
Vertex::
export_homogeneous(
  T &v,
  uint N,
  Transform const &t,
  ProjectionMode p ) const
{
  uint i;

  uint dimm = t.dim();

  // allocate a temporary, set it to 0
  math::Vector<Real> x;
  x.allocate(dimm);

  if ( p == CENTRAL )
  {
    DIE_IF(dimm < 1U);

    // copy the first _d coordinates to x
    uint n = std::min(_spaceform.dim, dimm-1);
    for ( i = 0; i < n; i++ ) { x[i] = _x[i]; }
    for ( i = n; i < dimm - 1; i++ ) { x[i] = 0.0f; }

    // copy the last coordinate
    x[dimm-1] = _xp;

    mulleft( t.data(), x.data(), dimm);

    // central projection to RP^3
    n = std::min(_spaceform.dim, 3U);
    for ( i = 0; i < n; i++ ) { v[i] = x[i]; }
    for ( i = n; i < 3U; i++ ) { v[i] = 0.0f; }
    v[3] = x[dimm-1];
  }
  else if ( p == STEREOGRAPHIC )
  {
    DIE_IF(dimm < 2U);

    if ( _spaceform.dim == 3 && dimm == 5 )
    {
      x[0] = _x[0];
      x[1] = _x[1];
      x[2] = _x[2];
      x[3] = _x0;
      x[4] = _xi;

      t.mulleft(x);

      v[0] = x[0];
      v[1] = x[1];
      v[2] = x[2];
      v[3] = x[4] - x[3];
      if ( v[3] < 0.0f )
      {
        v.neg();
      }
    }
    else
    {
      // copy the first d coordinates to x
      uint n = std::min(_spaceform.dim, dimm-2);
      for ( i = 0; i < n; i++ ) { x[i] = _x[i]; }
      for ( i = n; i < dimm - 2; i++ ) { x[i] = 0.0f; }

      // copy the last two homogeneous coordinates
      x[dimm-2] = _x0;
      x[dimm-1] = _xi;

      mulleft( t.data(), x.data(), dimm);

      // stereographic projection to RP^3
      n = std::min(_spaceform.dim, 3U);
      for ( i = 0; i < n; i++ ) { v[i] = x[i]; }
      for ( i = n; i < 3U; i++ ) { v[i] = 0.0f; }
      v[3] = x[dimm-1] - x[dimm-2];
      if (v[3] < 0.0)
      {
        v.neg();
      }
    }

  }
  else
  {
    DIE();
  }
}

#if 0
template <class T>
void
Vertex::
import_homogeneous( T const &v, uint N )
{
  uint n = std::min( _spaceform.dim, N );
  uint i;
  for ( i = 0; i < n; i++ ) { _x[i] = v[i]; }
  for ( i = n; i < _spaceform.dim; i++ ) { _x[i] = 0.0f; }
  _xp = v[N];

  // normalize so the fourth coordinate is positive
  // OpenGL requires this
  if (_xp < 0.0f)
  {
    _x.neg();
    _xp = -_xp;
  }

  Real x = 0.0f;
  for ( i = 0; i < n; i++ ) { x += math::sqr(_x[i]); }
  x /= _xp;
  _x0 = 0.5f * ( x - _xp );
  _xi = 0.5f * ( x + _xp );
}
#endif


} // namespace surface0
} // namespace geom

#endif // geom_surface0_Vertex_INCLUDED

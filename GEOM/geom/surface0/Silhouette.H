/* GANG Software
 * GEOM/geom/surface0/Silhouette.H
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

#ifndef geom_surface0_Silhouette_INCLUDED
#define geom_surface0_Silhouette_INCLUDED

#include "Normal.H"

namespace geom {
namespace surface0 {

class Silhouette
  :
    public Normal
{

public:
  // constructor
  Silhouette();

  // copy constructor
  Silhouette( Silhouette const & );

  // destructor
  virtual ~Silhouette();

  // assignment operator
  Silhouette &operator=( Silhouette const & );

  bool first_silhouette_segment( EdgeMap::const_iterator &i,
    math::Matrix4<Real> const &transform ) const;

  bool next_silhouette_segment( EdgeMap::const_iterator &i ) const;

protected:

  void clear();
  void clear_silhouette();

private:

  /*
     computes the "visual boundary" of the surface
     this is the set of edges with two adjacent faces whose normals
     N1, N2 satisfy the following condition:
       V.N1 and V.N2 (dot products) have opposite signs
       where V is the direction the camera is pointing

     returns true if i points to a visual boundary segment
     returns false when there are no more visual boundary segements

     do not modify '_edge' while using this (will crash)
  */
  //
  bool next_silhouette_segment_( EdgeMap::const_iterator &i ) const;

  /*
     indices into _vertex making up the visual boundary
     each std::pair of unsigned ints is a line segment
      base::vector< std::pair<uint, uint> > _silhouette;
  */
  //
  mutable Vertex4 _silhouette_vector;

};

} // namespace surface0
} // namespace geom

#endif // geom_surface0_Silhouette_INCLUDED

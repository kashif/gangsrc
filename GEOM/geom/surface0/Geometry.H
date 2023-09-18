/* GANG Software
 * GEOM/geom/surface0/Geometry.H
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

#ifndef geom_surface0_Geometry_INCLUDED
#define geom_surface0_Geometry_INCLUDED

#include "base/vector.H"
#include "Common.H"
#include "Silhouette.H"

namespace geom {
namespace surface0 {

class Geometry
  :
    public Silhouette
{

public:
  // constructor
  Geometry();

  // copy constructor
  Geometry( Geometry const & );

  // destructor
  virtual ~Geometry();

  // assignment operator
  Geometry &operator=( Geometry const & );

  void clear();
  void clear_geometry();

  void compute_face_area() const;
  void compute_gaussian_curvature() const
    { compute_face_gaussian_curvature(); }
  void compute_mean_curvature() const
    { compute_face_mean_curvature(); }

  Real face_area(uint i) const
    { return _face_area[i]; }
  Real face_gaussian_curvature(uint i) const
    { return _face_gaussian_curvature[i]; }
  Real vertex_gaussian_curvature(uint i) const
    { return _vertex_gaussian_curvature[i]; }
  Real face_mean_curvature(uint i) const
    { return _face_mean_curvature[i]; }

protected:

private:

  void compute_vertex_gaussian_curvature() const;
  void compute_face_gaussian_curvature() const;
  void compute_face_mean_curvature() const;

  struct CurvatureData
  { Real angle; Real area; uint count; bool boundary; };

  Real mean_curvature(
    uint a,
    uint b,
    uint c,
    uint d ) const;

  mutable base::vector<Real> _vertex_gaussian_curvature;
  mutable base::vector<Real> _face_gaussian_curvature;
  mutable base::vector<Real> _face_mean_curvature;
  mutable base::vector<Real> _face_area;

};

} // namespace surface0
} // namespace geom

#endif // geom_surface0_Geometry_INCLUDED

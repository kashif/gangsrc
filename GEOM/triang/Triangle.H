/* GANG Software
 * GEOM/triang/Triangle.H
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

#ifndef triang_Triangle_INCLUDED
#define triang_Triangle_INCLUDED

#include "base/vector.H"
#include "TriangleBase.H"

namespace triang {

using base::vector;
using std::pair;

/*
  C++ Wrapper for TrianglBase
*/
class Triangle
{

public:

  Triangle();
  virtual ~Triangle();

  typedef pair<Real,Real> Point;
  typedef vector<Point> PointList;
  typedef vector<uint> IntList;
  typedef vector<uint> Face;

  /* compute triangulation - with holes (calls 'triangle')
     input: vertex_in, edge_in, hole_in
     output: vertex_out, face_out
  */
  void triangulate(
    PointList &vertex_out,
    vector<Face> &face_out,
    vector<Curve> const &vertex_in,
    PointList &hole_in );

  /* refine a triangulation - with area constraints (calls 'triangle')
     uses a previous triangulation
  */
  void triangulate(
    PointList &vertex_out,
    vector<Face> &face_out,
    vector<Real> const &area_in );

  // set the maximum area (set to 0.0 to disable)
  void max_area( Real max_area );

  Real max_area() const { return _max_area; }

  // set the minimum angle in degrees (set to 0.0 to disable)
  void min_angle( Real min_angle );

  Real min_angle() const { return _min_angle; }

protected:

  Real _max_area;
  Real _min_angle;

private:

  class TriangleData
  {
  public:
    TriangleData();
    TriangleData( TriangleData const &a )
      { copy(a); }
    TriangleData &operator=( TriangleData const &a )
      { copy(a); return *this; }
    ~TriangleData();
    void initialize();
    void clear();
    void copy( TriangleData const &a );
    triangulateio *data() { return &_; }
    triangulateio const *data() const { return &_; }

    void import_vertex(
      vector<Curve> const &vertex );
    void import_edge(
      vector<pair<uint, uint> > const &edge );
    void import_hole(
      PointList const &hole );
    void import_face(
      vector<Face> const &face );
    void import_area(
      vector<Real> const &area );

    void export_(
      PointList &vertex,
      vector<Face> &face ) const;

#ifdef DEBUG
    static void
    DEBUG_COMPARE(
      TriangleData const *t1,
      TriangleData const *t2
      );
#endif

  private:
    triangulateio _;

  };

  void triangulate(
    TriangleData &data_out,
    TriangleData const &data_in,
    bool refine = false );

  TriangleData *_current_data;

  static uint const OFFSET = 0;

  static void *_malloc( size_t n );

  // disabled copy constructor
  Triangle( Triangle const & );

  // disabled assignment operator
  Triangle &operator=( Triangle const & );
};

} // namespace triang

#endif // triang_Triangle_INCLUDED

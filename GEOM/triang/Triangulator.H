/* GANG Software
 * GEOM/triang/Triangulator.H
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

#ifndef triang_Triangulator_INCLUDED
#define triang_Triangulator_INCLUDED

#include <iomanip>
#if defined(__sgi) && !defined(__GNUG__)
#pragma set woff 1174
#endif
#include <list>
#if defined(__sgi) && !defined(__GNUG__)
#pragma reset woff 1174
#endif
#include "base/vector.H"
#include "base/String.H"
#include "base/Exception.H"
#include "base/Regex.H"
#include "eval/Eval.H"
#include "geom/interface/Surface.H"
#include "Triangle.H"
#include "Data.H"
#include "Parser.H"
#include "Common.H"

namespace triang {

class Triangulator
  :
    public Parser,
    public Triangle
{
public:
  typedef geom::Real Real;

  // void constructor
  Triangulator();

  // destructor
  virtual ~Triangulator();

  // read configuration from file
  void read( char const *filename );
  // read configuration from stream
  void read( io::Istream & );
  // read configuration from char *
  void read_string( char const *s );
  // read configuration from base::Stringg
  void read_string( base::String const &s );

  // get the smoothing iteration number
  uint smooth() const
    { return _smooth; }
  Real max_area() const
    { return _max_area; }
  Real min_angle() const
    { return _min_angle; }
  uint refine() const
    { return _refine; }
  Real max_area2() const
    { return _max_area2; }
  Real curvature_exp() const
    { return _curvature_exp; }
  Real curvature_cut() const
    { return _curvature_cut; }


  inline void get_boundary( base::vector<base::String> &v )
    { v = _boundary_str; }

  // triangulate without area constraint
  void triangulate(
    geom::Surface *surface )
    throw ( base::Exception );

  // triangulate with area constraint
  void triangulate(
    geom::Surface *surface,
    base::vector< Real> const &area )
    throw ( base::Exception );

protected:

private:

  void initialize();

  static void
  copy(
    base::vector<geom::Vertex2> &b,
    base::vector< std::pair<Real,Real> > const &a );

  void set_data();

  typedef std::pair<uint,uint> uint_pair;

  void
  corners(
    std::list<std::list<uint> > &corner,
    base::vector<Curve> const &boundary );

  // triangulation input data
  Data _data;

  uint _smooth;
  uint _refine;
  Real _max_area2;
  Real _curvature_cut;
  Real _curvature_exp;

  // vector of strings describing boundary
  base::vector<base::String> _boundary_str;

  // points
  base::vector<std::pair< Real,Real> >
  _vertex_v;

  // points
  base::vector<Curve> _vertex_v_v;

  // holes
  base::vector<std::pair< Real,Real> > _hole_v;

  // faces
  base::vector<base::vector<uint> > _face_v;


  // disabled copy constructor
  Triangulator( Triangulator const & );
  // disabled assignment operator
  Triangulator &operator=( Triangulator const & );
};

} // namespace triang

#endif // triang_Triangulator_INCLUDED

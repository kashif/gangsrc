/* GANG Software
 * GEOM/geom/interface/Surface.H
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

#ifndef geom_Surface_INCLUDED
#define geom_Surface_INCLUDED

#include <list>
#include "base/Color3.H"
#include "base/Color4.H"
#include "base/vector.H"
#include "io/IstreamStream.H"
#include "io/OstreamStream.H"
#include "milieu/kernel/MilieuBase.H"
#include "Common.H"

namespace geom {

namespace surface { class Construct; }

class Surface
{

public:
  // constructor
  Surface();

  // copy constructor
  Surface( Surface const & );

  // destructor
  virtual ~Surface();

  // assignment operator
  Surface &operator=( Surface const & );

  enum Type { EMPTY, INDEXED, GRID };
  Type type() const;

  void vertex( Vertex3 &x, uint i ) const;
  void vertex( Vertex4 &x, uint i ) const;

  uint vertex_count() const;
  uint edge_count() const;

  uint face_count() const;
  uint face_count(uint i) const;
  uint face_vertex(uint i, uint j) const;

  std::list<std::list<uint> > const &line() const;

  void boundary( std::list<std::list<std::pair<uint,uint> > > & ) const;

  Real vertex_gaussian_curvature( uint i ) const;
  Real face_gaussian_curvature(uint i) const;
  Real face_area(uint i) const;
  base::vector<base::vector<uint> > const &face_data() const;

  // import a grid
  void import( base::vector<base::vector<base::vector<Real> > > const &vertex,
               SpaceForm const &spaceform );
  // import an indexed surface
  void import( base::vector<Vertex2> const &vertex,
               base::vector<base::vector<uint> > const &face,
               SpaceForm const &spaceform );
  // import an indexed surface
  void import( base::vector<base::vector<Real> > const &vertex,
               base::vector<base::vector<uint> > const &face,
               SpaceForm const &spaceform );
  // import lines
  void import_lines( std::list<std::list<uint> > const &line );
  void import_boundary_lines( std::list<std::list<uint> > const &corner );

  // get position
  Transform const &position() const;
  void position( std::list<Transform> & ) const;
  // set position
  void position( Transform const &x );

  geom::Box const &box() const;

  // check whether the surface is empty
  bool empty() const;
  // clear
  void clear();

  void insert( Surface const &x );

  void remove_to_one();

  // read from a stream
  void read(
    ::io::Istream &stream,
    FileMode = FILEMODE_DEFAULT )
    throw (::io::ReadException);

  // read from a file
  void read(
    base::String &filename,
    FileMode filemode = FILEMODE_UNSPECIFIED )
    throw (::io::ReadException)
    { ::io::IstreamStream stream(filename); read( stream, filemode ); }

  void read(
    ::io::Istream &in,
    ::milieu::kernel::MilieuBase &M,
    FileMode filemode = FILEMODE_UNSPECIFIED )
    throw (::io::ReadException);

  void read(
    base::String const &filename,
    ::milieu::kernel::MilieuBase &M,
    FileMode filemode = FILEMODE_UNSPECIFIED )
    throw (::io::ReadException)
    { ::io::IstreamStream stream(filename); read( stream, M, filemode ); }

  void write(
    ::io::Ostream &stream,
    FileMode filemode = FILEMODE_DEFAULT ) const
    throw (::io::ReadException);

  // write to a file
  void write(
    base::String &filename,
    FileMode filemode = FILEMODE_UNSPECIFIED ) const
    throw (::io::ReadException)
    { ::io::OstreamStream stream(filename); write( stream, filemode ); }

  void write(
    ::io::Ostream &stream,
    uint normals, uint colors,
    milieu::kernel::MilieuBase const &milieu,
    FileMode filemode = FILEMODE_DEFAULT ) const
    throw (::io::WriteException);

  void write(
    base::String const &filename,
    uint normals, uint colors,
    milieu::kernel::MilieuBase const &milieu,
    FileMode filemode = FILEMODE_UNSPECIFIED ) const
    throw (::io::WriteException)
    { ::io::OstreamStream stream(filename);
    write( stream, normals, colors, milieu, filemode ); }

  void transform( Transform const &a );
  void translate( math::VectorX<Real,3U> const &a );
  void reflect( math::VectorX<Real,4U> const &a );
  void build_reflect( math::VectorX<Real,4U> const &a );
  void reverse_orientation();

  Real glue(
    uint part1, uint part2,
    std::list<uint> const &boundaryset );

  Real glue(
    uint part,
    std::list<uint> const &boundaryset1,
    std::list<uint> const &boundaryset2 );

  void relax( uint iterations );

  virtual void color_original( base::Color4 const &p );
  /*
     Color the surface at each vertex by the normal direction of the
     surface at that vertex
  */
  virtual void color_by_normal( base::Color4 const &p );

  /*
     Color the surface at each vertex by its direction of that vertex
     from the origin
     (r,g,b) = scale * (unit direction vector)
  */
  virtual void color_by_direction( base::Color4 const &p );

  /*
     Color the surface at each vertex by its distance from the origin
     the distance, in the interval [0,inf) is rescaled
     to the interval [0,1) by an arctan function
  */
  virtual void color_by_distance( base::Color4 const &p, float scale );

  /*
     Color the surface at each vertex by the area of an adjacent face
  */
  virtual void color_by_area( base::Color4 const &p, float scale );

  /*
     Color the surface by discrete Gaussian curvature.
  */
  virtual void color_by_gaussian_curvature(
    base::Color4 const &p, float scale );

  /*
     Color the surface by discrete mean curvature.
  */
  virtual void color_by_mean_curvature(
    base::Color4 const &p, float scale );

  /*
     Color the faces of the surface with randomly chosen colors.
  */
  virtual void color_randomly( base::Color4 const &p );

  void color_checked( base::Color4 const &c0, base::Color4 const &c1 );

  /*
    sets alpha as follows:
      alpha is 1 in the interval [0,x0]
      alpha ranges from 1->0 linerarly in the interval [x0,x1]
      alpha is 1 in the interval [x1,inf]
  */
  void alpha_fade( float alpha, float scale );

  void colorData(
    uint &mode,
    base::Color4 &color0,
    base::Color4 &color1,
    float &scale );

  bool has_original_color() const;

  // mesh clip
  uint i_count() const;
  uint j_count() const;
  uint i_begin() const;
  uint i_step() const;
  uint j_begin() const;
  uint j_step() const;

  void reset_clip();
  void set_clip(
    uint i_begin, uint i_step,
    uint j_begin, uint j_step );
  void get_clip(
    uint &i_begin, uint &i_step,
    uint &j_begin, uint &j_step ) const;

  static uint material_count();
  void reset_material();
  void reset_material(uint id);
  void materials( Surface const &x );

  // materials
  bool const &enable(uint id) const;
  void enable( uint id, bool a );

  bool const &shademodel(uint id) const;
  void shademodel( uint id, bool a );

  uint const &model(uint id) const;
  void model( uint id, uint a );

  float const &element_size(uint id) const;
  void element_size(uint id, float a );

  base::ArrayX<float,2U> const &gap(uint id) const;
  void gap( uint id, base::ArrayX<float,2U> const &a );

  base::Color4 const &color(uint id) const;
  void color( uint id, base::Color4 const &a );

  base::Color3 const &ambient(uint id) const;
  void ambient( uint id, base::Color3 const &a );

  base::Color4 const &diffuse(uint id) const;
  void diffuse( uint id, base::Color4 const &a );

  base::Color3 const &specular(uint id) const;
  void specular( uint id, base::Color3 const &a );

  base::Color3 const &emissive(uint id) const;
  void emissive( uint id, base::Color3 const &a );

  float const &shininess(uint id) const;
  void shininess( uint id, float a );

  base::ArrayX<uint,2U> const &side( uint id ) const;
  void side( uint id, base::ArrayX<uint,2U> const &a );

  base::ArrayX<float,2U> const &nudge(uint id ) const;
  void nudge( uint id, base::ArrayX<float,2U> const &a );

  bool const &lit( uint id ) const;
  void lit( uint id, bool a );

  bool const &transparent( uint id ) const;
  void transparent( uint id, bool a );

  bool const &custom_color( uint id ) const;
  void custom_color( uint id, bool a );

  void compute_face_area() const;
  void compute_gaussian_curvature() const;
  void compute_boundary() const;

  base::String const &name() const;
  void name( base::String const & );

protected:
  Surface(bool);
  surface::Construct *_;
private:
};

} // namespace geom

#endif // geom_Surface_INCLUDED

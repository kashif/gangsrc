/* GANG Software
 * GEOM/motion/TransformX.H
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

#ifndef motion_TransformX_INCLUDED
#define motion_TransformX_INCLUDED

#include "math/Matrix.H"
#include "Common.H"

namespace motion {

/*
  KINDS OF TRANSFORMS:<br><br>

  TransformXRotation1:<br>

    Single rotation/translation in the plane spanned by (u n0 + v n1) and n2
    at speed=a<br><br>


  TransformXRotation2:<br>

    Two simultaneous rotations/translations in perpendicular coordinate
    planes:
        in the n0-n1 coordinate plane at speed=a;
        in the n2-n3 coordinate plane at speed=b.<br><br>


  TransformXMoebiusParabolic2:<br>

    Moebius parabolic translation in a plane.

    Computes MatrixExp[u A1 + v A2], where
    A1 = {
    {0, 0, -1, 1},
    {0, 0, 0, 0},
    {1, 0, 0, 0},
    {1, 0, 0, 0}}<br>

    A2 = {
    {0, 0, 0, 0},
    {0, 0, -1, 1},
    {0, 1, 0, 0},
    {0, 1, 0, 0}}<br>


  TransformXMoebiusParabolic1:<br>

    Moebius parabolic translation along a line<br>

    Computes MatrixExp[a A], where
    A = {{0, -1, 1}, {1, 0, 0}, {1, 0, 0}}<br>

  Note: matrices are transposed for OpenGL compatibility<br><br>
*/

class TransformX
{

public:

  // void constructor
  TransformX();

  // destructor
  virtual ~TransformX();

  enum GeometryGroup { HYPERBOLIC, PARABOLIC, ELLIPTIC };

  bool on() const
    { return _on; }

  bool is_translation() const
    { return _on && _is_translation; }

  virtual void to_matrix( math::Matrix<Real> & ) const = 0;

  virtual void decay( Real decayfactor, Real clip ) = 0;

  uint dim() const
    { return _matrix_dim; }

  friend std::ostream &operator<<( std::ostream &o, TransformX const &t );

protected:

  GeometryGroup _geometry;
  bool _is_translation;

  static void
  get_parameters(
    Real &a11, Real &a12, Real &a21, Real &a22,
    Real a, GeometryGroup mode );

  uint _matrix_dim;

  bool _on;

private:

  TransformX( TransformX const & );
  TransformX &operator=( TransformX const & );
};


/*
  Derived classes
*/

class TransformXRotation1
  :
    public TransformX
{
public:

  TransformXRotation1(
    uint n0,
    uint n1,
    uint n2,
    Real u,
    Real v,
    Real a,
    GeometryGroup mode,
    bool is_translation,
    uint matrix_dim );

  TransformXRotation1(
    uint n0,
    uint n2,
    Real a,
    GeometryGroup mode,
    bool is_translation,
    uint matrix_dim );

  void to_matrix( math::Matrix<Real> & ) const;
  void decay( Real decayfactor, Real clip );

private:

  void set(
    uint n0,
    uint n1,
    uint n2,
    Real u,
    Real v,
    Real a,
    GeometryGroup mode,
    bool is_translation,
    uint matrix_dim );

  uint _n0, _n1, _n2;
  Real _u, _v, _a;
};


class TransformXRotation2
  :
    public TransformX
{
public:

  TransformXRotation2(
    uint n0,
    uint n1,
    uint n2,
    uint n3,
    Real a,
    Real b,
    GeometryGroup mode,
    bool is_translation,
    uint matrix_dim );

  void to_matrix( math::Matrix<Real> & ) const;
  void decay( Real decayfactor, Real clip );

private:

  uint _n0, _n1, _n2, _n3;
  Real _a, _b;
};


class TransformXMoebiusParabolic2
  :
    public TransformX
{
public:

  TransformXMoebiusParabolic2(
    uint n0,
    uint n1,
    uint n2,
    uint n3,
    Real u,
    Real v,
    Real a,
    bool inverse,
    bool is_translation,
    uint matrix_dim );

  void to_matrix( math::Matrix<Real> & ) const;
  void decay( Real decayfactor, Real clip );

private:

  uint _n0, _n1, _n2, _n3;
  Real _u, _v, _a;
  bool _inverse;
};


class TransformXMoebiusParabolic1
  :
    public TransformX
{
public:

  TransformXMoebiusParabolic1(
    uint n0,
    uint n1,
    uint n2,
    Real a,
    bool inverse,
    bool is_translation,
    uint matrix_dim );

  void to_matrix( math::Matrix<Real> & ) const;
  void decay( Real decayfactor, Real clip );

private:

  uint _n0, _n1, _n2;
  Real _a;
  bool _inverse;
};

} // namespace motion

#endif // motion_TransformX_INCLUDED

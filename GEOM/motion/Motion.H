/* GANG Software
 * GEOM/motion/Motion.H
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

#ifndef motion_Motion_INCLUDED
#define motion_Motion_INCLUDED

#include "math/Vector3.H"
#include "math/VectorX.H"
#include "Common.H"
#include "TransformX.H"
#include "Inertia.H"

namespace motion {

/*
  Motion engine for geometry viewer.
  Handles motions that arise from mouse action, including inertia
*/

#if 0
using kernel::GeometryMode;
using kernel::PROJECTIVE;
using kernel::CONFORMAL;
using kernel::MOEBIUS;

using kernel::GeometryGroup;
using kernel::PARABOLIC;
using kernel::HYPERBOLIC;
using kernel::ELLIPTIC;

using kernel::MouseMode;
using kernel::MM_NOTHING;
using kernel::ROTATION;
using kernel::TRANSLATION;
using kernel::INVERSION;
using kernel::SCALE;
#endif

class Motion
  :
    public Inertia
{

public:

  // void constructor
  Motion();

  // destructor
  virtual ~Motion();

  float speed() const
    { return _speed; }
  float acceleration() const
    { return _accel - 1.0; }
  int view_mode() const
    { return _view_mode; }
  void mouse_mode( MouseMode );
  MouseMode mouse_mode() const;
  void mouse_rotation()
    { mouse_mode(ROTATION); }
  void mouse_translation()
    { mouse_mode(TRANSLATION); }
  void mouse_inversion()
    { mouse_mode(INVERSION); }
  void mouse_scale()
    { mouse_mode(SCALE); }

  inline void speed(
    float speed, float accel );
  // view mode: 0 = examine mode, 1 = fly mode
  void view_mode( int model );

  bool standard_geometry() const
    { return _standard_geometry; }

  GeometryMode geometry_mode() const
    { return _geometryMode; }
  GeometryGroup geometry_group() const
    { return _geometry; }
  uint geometry_dim() const
    { return _dim; }

  void geometry(
    GeometryMode mode,
    GeometryGroup geom,
    uint dim );

  virtual uint matrix_dim() const
    { return _matrix_dim; }    

  ProjectionMode const &projectionMode() const
    { return _projectionMode; }

protected:

private:

  void _set_geometry(
    GeometryMode mode,
    GeometryGroup geom,
    uint dim );

  virtual void compute_inertia(
    uint button, Point const &p0, Point const &p1 );

  enum Action {
    NOTHING,
    ROTATE4,  // rotate in two planes
    ROTATE3,  // rotate in a skew plane
    ROTATE2,  // rotate in a coordinate plane
    TRANSLATE2,  // translate in a skew direction
    TRANSLATE1,  // translate along a coordinate axis
    ITRANSLATE2,  // inverse translate in a skew direction
    ITRANSLATE1,  // inverse translate along a coordinate axis
    HOMOTHETY // homothety
  };

  struct MouseAction
  {
    Action action;
    int axis0, axis1, axis2, axis3;
  };

  void
  compute_inertia(
    MouseAction const &action,
    float x, float y );

  float accel( float x );

  void move_projective3( Point const &p0, Point const &p1 );
  void move_projective4( Point const &p0, Point const &p1 );
  void move_conformal3( Point const &p0, Point const &p1 );
  void move_moebius4( Point const &p0, Point const &p1 );

  GeometryMode _geometryMode;
  GeometryGroup _geometry;

  uint _matrix_dim;

  uint _dim;

  // dimension chosen by user from menu
  uint _user_dim;

  // direction +1 or -1
  float _direction;

  float _speed;
  float _accel;

  int _view_mode;

  TransformX::GeometryGroup _transform_geometry;

  int _mouse_mode;

  ProjectionMode _projectionMode;
  bool _standard_geometry;


  // non-Moebius mouse action tables for dim=4,3,2
  static MouseAction const action4[2][3];
  static MouseAction const action3[2][4];

  // Moebius mouse action tables for dim=4,3,2
  static MouseAction const action_moebius[3][4][3];

  // copy constructor
  Motion( Motion const & );
  // assignment operator
  Motion &operator=( Motion const & );
};

void
Motion::
speed( float speed, float accel )
{
  _speed = speed;
  _accel = accel + 1.0f;
}

} // namespace motion

#endif // motion_Motion_INCLUDED

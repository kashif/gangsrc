/* GANG Software
 * GEOM/motion/Motion.C
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

#include <math.h>
#include <algorithm>
#include "base/System.H"
#include "math/Math.H"
#include "math/Matrix4.H"
#include "Motion.H"

namespace motion {

enum
{
  AXIS_X = 0,
  AXIS_Y = 1,
  AXIS_Z = 2,
  AXIS_W = 3
};

// GeometryMode==PROJECTIVE/CONFORMAL
// dim==4
Motion::MouseAction const Motion::action4[2][3] =
{
  // [R]otation: // mouse buttons 1, 2, 3
  {{ Motion::ROTATE3,    AXIS_X, AXIS_Y, AXIS_Z, -1 },
   { Motion::ROTATE4,    AXIS_X, AXIS_Y, AXIS_Z, AXIS_W },
   { Motion::ROTATE3,    AXIS_X, AXIS_Y, AXIS_W, -1 }},
  // [T]ranslation: // mouse buttons 1, 2, 3
  {{ Motion::TRANSLATE2, AXIS_X, AXIS_Y, -1 },
   { Motion::TRANSLATE2, AXIS_Z, AXIS_W, -1 },
   { Motion::NOTHING,     -1}}
};

// GeometryMode==PROJECTIVE/CONFORMAL
// dim==3,2
Motion::MouseAction const Motion::action3[2][4] =
{
  // dim == 3
  {
    // mouse buttons 1, 2a, 2b, 3
    { Motion::ROTATE3,    AXIS_X, AXIS_Y, AXIS_Z, -1 },
    { Motion::TRANSLATE1, AXIS_Z, -1 },
    { Motion::ROTATE2,    AXIS_X, AXIS_Y, -1 },
    { Motion::TRANSLATE2, AXIS_X, AXIS_Y, -1 }
  },
  // dim == 2 (same as dim==3 but with z disabled)
  {
    // mouse buttons 1, 2a, 2b, 3
    { Motion::NOTHING,    -1 },
    { Motion::NOTHING,    -1 },
    { Motion::ROTATE2,    AXIS_X, AXIS_Y, -1 },
    { Motion::TRANSLATE2, AXIS_X, AXIS_Y, -1 }
  }
};

// GeometryMode==MOEBIUS
// dim==4,3,2
Motion::MouseAction const Motion::action_moebius[3][4][3] =
{
  // dim == 4
  {
    // [R]otation: mouse buttons 1, 2, 3
    {{ Motion::ROTATE3,     AXIS_X, AXIS_Y, AXIS_Z, -1 },
     { Motion::ROTATE4,     AXIS_X, AXIS_Y, AXIS_Z, AXIS_W },
     { Motion::ROTATE3,     AXIS_X, AXIS_Y, AXIS_W, -1 }},
    // [T]ranslation: mouse buttons 1, 2, 3
    {{ Motion::TRANSLATE2,  AXIS_X, AXIS_Y, -1 },
     { Motion::TRANSLATE2,  AXIS_Z, AXIS_W, -1 },
     { Motion::NOTHING,     -1 }},
    // [I]nverse translation: mouse buttons 1, 2, 3
    {{ Motion::ITRANSLATE2, AXIS_X, AXIS_Y, -1 },
     { Motion::ITRANSLATE2, AXIS_Z, AXIS_W, -1 },
     { Motion::NOTHING,     -1}},
    // [S]cale: mouse buttons 1, 2, 3
    {{ Motion::HOMOTHETY,       -1 },
     { Motion::NOTHING,     -1 },
     { Motion::NOTHING,     -1 }}
  },
  // dim == 3 (same as dim==4 but with w disabled)
  {
    // [R]otation: mouse buttons 1, 2, 3
    {{ Motion::ROTATE3,     AXIS_X, AXIS_Y, AXIS_Z, -1 },
     { Motion::ROTATE2,     AXIS_X, AXIS_Y, -1 },
     { Motion::NOTHING,     -1 }},
    // [T]ranslation: mouse buttons 1, 2, 3
    {{ Motion::TRANSLATE2,  AXIS_X, AXIS_Y, -1 },
     { Motion::TRANSLATE1,  AXIS_Z, -1 },
     { Motion::NOTHING,     -1 }},
    // [I]nverse translation: mouse buttons 1, 2, 3
    {{ Motion::ITRANSLATE2, AXIS_X, AXIS_Y, -1 },
     { Motion::ITRANSLATE1, AXIS_Z, -1 },
     { Motion::NOTHING,     -1}},
    // [S]cale: mouse buttons 1, 2, 3
    {{ Motion::HOMOTHETY,       -1 },
     { Motion::NOTHING,     -1 },
     { Motion::NOTHING,     -1 }}
  },
  // dim == 2 (same as dim==4 but with w and z disabled)
  {
    // [R]otation: mouse buttons 1, 2, 3
    {{ Motion::NOTHING,     -1 },
     { Motion::ROTATE2,     AXIS_X, AXIS_Y, AXIS_Z, -1 },
     { Motion::NOTHING,     -1 }},
    // [T]ranslation: mouse buttons 1, 2, 3
    {{ Motion::TRANSLATE2,  AXIS_X, AXIS_Y, -1 },
     { Motion::NOTHING,     -1 },
     { Motion::NOTHING,     -1 }},
    // [I]nverse translation: mouse buttons 1, 2, 3
    {{ Motion::ITRANSLATE2, AXIS_X, AXIS_Y, -1 },
     { Motion::NOTHING,     -1 },
     { Motion::NOTHING,     -1}},
    // [S]cale: mouse buttons 1, 2, 3
    {{ Motion::HOMOTHETY,       -1 },
     { Motion::NOTHING,     -1 },
     { Motion::NOTHING,     -1 }}
  }
};

Motion::
Motion()
    :
  _geometryMode(PROJECTIVE),
  _geometry(PARABOLIC),
  _matrix_dim(0),
  _dim(0),
  _user_dim(0),
  _direction(1.0f),
  _speed(0.15f),
  _accel(1.0f),
  _view_mode(0),
  _transform_geometry(TransformX::PARABOLIC),
  _mouse_mode(0),
  _projectionMode(CENTRAL),
  _standard_geometry(true)
{
  _set_geometry( PROJECTIVE, PARABOLIC, 3U );
}

Motion::
~Motion()
{
}

void
Motion::
geometry(
 GeometryMode mode,
 GeometryGroup geom,
 uint dim )
{
  stop_motion();
  _set_geometry(mode, geom, dim);
}

void
Motion::
_set_geometry(
 GeometryMode mode,
 GeometryGroup geom,
 uint dim )
{
  _geometryMode = mode;
  _geometry = geom;
  _projectionMode =
    ( mode == PROJECTIVE ? CENTRAL : STEREOGRAPHIC );

  // prevent dim > 4
  DIE_IF( dim > 4 );

  // _dim
  _dim = std::max( 3U, dim );

  // _matrix_dim
  _matrix_dim = ( _geometryMode == PROJECTIVE ? _dim + 1U : _dim + 2U );

  // _user_dim
  _user_dim = dim;

  // _transform_geometry
  if ( _geometry == PARABOLIC )
  { _transform_geometry = TransformX::PARABOLIC; }
  else if ( _geometry == HYPERBOLIC )
  { _transform_geometry = TransformX::HYPERBOLIC; }
  else if ( _geometry == ELLIPTIC )
  { _transform_geometry = TransformX::ELLIPTIC; }
  else
  { DIE(); }

  _standard_geometry =
    ( _dim <= 3 && _geometryMode == PROJECTIVE && _geometry == PARABOLIC );

  // _mouse_mode
  _mouse_mode = 0;
}


void
Motion::
view_mode( int model )
{
  stop_motion();

  if (model != 0 && model != 1) { WARN(); return; }

  if (model == 0 && _view_mode == 1 )
  {
    // examine mode
    _direction = 1.0f;
    _view_mode = 0;
  }
  else if (model == 1 && _view_mode == 0 )
  {
    // fly mode
    _direction = -1.0f;
    _view_mode = 1;
  }
}

void
Motion::
compute_inertia(
  uint button,
  Point const &p0,
  Point const &p1 )
{
  DIE_IF( _user_dim < 2U || _user_dim > 4U );

  float x = float( p1.x - p0.x );
  // use negative here because y is measured downward in the context
  float y = -float( p1.y - p0.y );

  if ( x == 0.0f && y == 0.0f )
  { stop_motion(); return; }

  // chose a mouse action table
  if ( _geometryMode != MOEBIUS )
  {
    DIE_IF(button > 2);
    if (_user_dim == 4)
    {
      DIE_IF(_mouse_mode > 1);
      compute_inertia( action4[_mouse_mode][button], x, y );
    }
    else
    {
      // split mouse button 2 according as x>y or x<y
      uint b = button;
      if (button == 2) { b++;}
      if ( button == 1 &&  math::abs(x) < math::abs(y) )
      {
        b++;
        math::swap(x, y);
      }
      compute_inertia( action3[3-_user_dim][b], x, y );
    }
  }
  else
  {
    DIE_IF(_mouse_mode > 3);
    DIE_IF(button > 2);
    compute_inertia(
      action_moebius[4-_user_dim][_mouse_mode][button], x, y );
  }
}

void
Motion::
compute_inertia(
  Motion::MouseAction const &action,
  float x, float y )
{
  float const ROTATION_SPEED = 0.01f;
  float const TRANSLATION_SPEED = 0.01f;
  float const HOMOTHETY_SPEED = 0.01f;

  bool const IS_NOT_TRANSLATION = false;
  bool const IS_TRANSLATION = true;

  if ( action.action == ROTATE4 )
  {
    float a = ROTATION_SPEED * x;
    float b = ROTATION_SPEED * y;
    if (_inertia != (TransformX *)0) { delete _inertia; }
    _inertia = new TransformXRotation2(
      action.axis0, action.axis1, action.axis2, action.axis3,
      accel(a), accel(b),
      TransformX::ELLIPTIC, IS_NOT_TRANSLATION, _matrix_dim );
  }
  else if ( action.action == ROTATE3 )
  {
    float a = ROTATION_SPEED * math::abs(x, y);
    if (_inertia != (TransformX *)0) { delete _inertia; }
    _inertia = new TransformXRotation1(
      action.axis0, action.axis1, action.axis2,
      x, y, -accel(a),
      TransformX::ELLIPTIC, IS_NOT_TRANSLATION, _matrix_dim );
  }
  else if ( action.action == ROTATE2 )
  {
    float a = _direction * ROTATION_SPEED * x;
    if (_inertia != (TransformX *)0) { delete _inertia; }
    _inertia = new TransformXRotation1(
      action.axis0, action.axis1, accel(a),
      TransformX::ELLIPTIC, IS_NOT_TRANSLATION, _matrix_dim );
  }
  else if ( action.action == TRANSLATE2 ||
            action.action == ITRANSLATE2 )
  {
    float a = _direction * TRANSLATION_SPEED * math::abs(x,y);
    if (_geometryMode == PROJECTIVE)
    {
      if (_inertia != (TransformX *)0) { delete _inertia; }
      _inertia = new TransformXRotation1(
        action.axis0, action.axis1, _matrix_dim-1, x, y, accel(a),
        _transform_geometry, IS_TRANSLATION, _matrix_dim );
    }
    else
    {
      if ( _geometry == PARABOLIC )
      {
        if (_inertia != (TransformX *)0) { delete _inertia; }
        _inertia = new TransformXMoebiusParabolic2(
          action.axis0, action.axis1, _matrix_dim-2, _matrix_dim-1,
          x, y, accel(a),
          action.action == ITRANSLATE2, IS_TRANSLATION, _matrix_dim );
      }
      else
      {
//        uint ax = ( _geometry == ELLIPTIC ? _dim : _dim+1 );
        uint ax = ( _geometry == ELLIPTIC ?
                            _matrix_dim - 2 : _matrix_dim - 1 );
        if (_inertia != (TransformX *)0) { delete _inertia; }
        _inertia = new TransformXRotation1(
          action.axis0, action.axis1, ax, x, y, accel(a),
          _transform_geometry, IS_TRANSLATION, _matrix_dim );
      }
    }
  }
  else if ( action.action == TRANSLATE1 ||
            action.action == ITRANSLATE1 )
  {
    float a = _direction * TRANSLATION_SPEED * x;

    if (_geometryMode == PROJECTIVE)
    {
      if (_inertia != (TransformX *)0) { delete _inertia; }
      _inertia = new TransformXRotation1(
        action.axis0, _matrix_dim-1, accel(a),
        _transform_geometry, IS_TRANSLATION, _matrix_dim );
    }
    else
    {
      if ( _geometry == PARABOLIC )
      {
        if (_inertia != (TransformX *)0) { delete _inertia; }
        _inertia = new TransformXMoebiusParabolic1(
          action.axis0, _matrix_dim-2, _matrix_dim-1, accel(a),
          action.action == ITRANSLATE1, IS_TRANSLATION, _matrix_dim );
      }
      else
      {
//        uint ax = ( _geometry == ELLIPTIC ? _dim : _dim+1 );
        uint ax = ( _geometry == ELLIPTIC ?
                            _matrix_dim - 2 : _matrix_dim - 1 );
        if (_inertia != (TransformX *)0) { delete _inertia; }
        _inertia = new TransformXRotation1(
          action.axis0, ax, accel(a),
          _transform_geometry, IS_TRANSLATION, _matrix_dim );
      }
    }
  }
  else if ( action.action == HOMOTHETY )
  {
    float a = HOMOTHETY_SPEED * x;
    if (_inertia != (TransformX *)0) { delete _inertia; }
    _inertia = new TransformXRotation1(
      _matrix_dim-2, _matrix_dim-1, accel(a),
      TransformX::HYPERBOLIC, IS_NOT_TRANSLATION, _matrix_dim );
  }
}

float
Motion::
accel( float x )
{
  // returns a x^n
  float y = math::sign(x) * _speed *
    math::pow( math::abs(x), _accel );

  if (math::isnan(y)) { y = 0.0f; }
  return y;
}


MouseMode
Motion::
mouse_mode() const
{
  if (_geometryMode == MOEBIUS || _dim == 4)
  { return MouseMode(_mouse_mode+1); }
  else
  { return MM_NOTHING; }
}

void
Motion::
mouse_mode( MouseMode mode )
{
  DIE_IF(mode > 4);

  if ( _geometryMode == MOEBIUS )
  {
    if (mode >= 1 ) { _mouse_mode = mode-1; }
  }
  else if ( _dim == 4 )
  {
    if (mode >= 1 && mode <= 2)
    { _mouse_mode = mode-1; }
  }
  else
  {
    _mouse_mode = 0;
  }
}

} // namespace motion

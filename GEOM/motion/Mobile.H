/* GANG Software
 * GEOM/motion/Mobile.H
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

#ifndef motion_Mobile_INCLUDED
#define motion_Mobile_INCLUDED

#include "Common.H"
#include "TransformX.H"

namespace motion {

class Mobile
{

public:

  // constructor
  Mobile(
    uint dim,
    ProjectionMode mode );

  // constructor
  Mobile(
    Place const &place,
    Center const &center,
    ProjectionMode mode );

  // destructor
  virtual ~Mobile();

  virtual void move( TransformX const &step );
  virtual void draw() const {}
  virtual void view_mode( int mode );

  virtual Place const &get_place() const
    { return _place; }

  virtual void set(
    Place const &place,
    Center const &center,
    ProjectionMode mode );

  virtual void set(
    Place const &position,
    Center const &center );

  virtual void set( Place const &place )
    {
      DIE_IF( _matrix_dim != place.position.dim() );
      _place = place;
    }

  // access _place.position
  Transform const &position() const
    { return _place.position; }

  // set rotation/translation/position from a
  virtual void position( Transform const &a );


  // access _place.rotation
  virtual Transform const &rotation() const
    { return _place.rotation; }

  virtual void rotation( Transform const &a )
    {
      DIE_IF( _matrix_dim != a.dim() );
      _place.rotation = a;
    }

  // access _place.translation
  virtual Transform const &translation() const
    { return _place.translation; }

  virtual void translation( Transform const &a )
    {
      DIE_IF( _matrix_dim != a.dim() );
      _place.translation = a;
    }

  // access _place.translation
  virtual Transform const &center() const
    { return _center; }

  virtual void set_center( Center const &a );

protected:

  Place _place;
  Transform _center;
  Transform _centerinv;

  uint _matrix_dim;

  /*
     RotationMode
     CENTER_AT_ORIGIN:
       fixed: the center for rotations is fixed at the origin
     CENTER_AT_OBJECT:
       moving: the center for rotations is translated by translations
     when you translate and then rotate an object, it rotates
     about the point that used to be at the origin (default)
  */

  enum RotationMode { CENTER_AT_ORIGIN=0, CENTER_AT_OBJECT=1 };
  int _rotation_mode;
  ProjectionMode _projection_mode;

private:

  // disabled copy constructor
  Mobile( Mobile const & );

  // disabled assignment operator
  Mobile &operator=( Mobile const & );
};

} // namespace motion

#endif // motion_Mobile_INCLUDED

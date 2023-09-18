/* GANG Software
 * GEOM/motion/Mobile.C
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

#include "Mobile.H"

namespace motion {

Mobile::
Mobile(uint dim,
       motion::ProjectionMode mode )
    :
    _place(),
    _center(),
    _centerinv(),
    _matrix_dim( mode == CENTRAL ? dim + 1U : dim + 2U ),
    _rotation_mode(CENTER_AT_OBJECT),
    _projection_mode(mode)
{
  Place place;
  place.rotation.allocate(_matrix_dim);
  place.rotation.identity();
  place.translation.allocate(_matrix_dim);
  place.translation.identity();
  place.position.allocate(_matrix_dim);
  place.position.identity();
  Center center;
  center.set(0.0);
  set( place, center, mode );
}

Mobile::
Mobile(
  Place const &place,
  Center const &center,
  ProjectionMode mode )
    :
    _place(),
    _center(),
    _centerinv(),
    _matrix_dim(0U),
    _rotation_mode(CENTER_AT_OBJECT),
    _projection_mode(CENTRAL)
{
  set( place, center, mode );
}

Mobile::
~Mobile()
{
}

void
Mobile::
position( Transform const &a )
{
  // factors a into rotation and translation
  // NOTE: assumes last column is 0,...,0,1
  // NOTE: assumes standard geometry

  DIE_IF( a.dim() == 0U );

  // position
  _place.position = a;

  // translation
  _place.translation.identity(4);
  uint i;
  // copy last row
  for (i = 0; i < a.dim()-1; i++)
  {
    _place.translation[a.dim()-1][i] = a[a.dim()-1][i];
  }

  // rotation
  _place.rotation = a;
  // set last row to 0
  for (i = 0; i < a.dim()-1; i++)
  {
    _place.rotation[a.dim()-1][i] = 0.0;
  }
}

void
Mobile::
set(
  Place const &place,
  Center const &center,
  ProjectionMode mode )
{
  _projection_mode = mode;
  set( place, center );
}

void
Mobile::
set(
  Place const &place,
  Center const &center )
{
  _matrix_dim = place.position.dim();
  _place = place;
  set_center(center);
}

void
Mobile::
set_center( Center const &center )
{
  _center.allocate(_matrix_dim);
  _center.identity();
  _centerinv.allocate(_matrix_dim);
  _centerinv.identity();

  if (_matrix_dim == 4U)
  {
    uint n = _matrix_dim - 1U;

    _center[n][0] = center[0];
    _center[n][1] = center[1];
    _center[n][2] = center[2];
    
    _centerinv[n][0] = -center[0];
    _centerinv[n][1] = -center[1];
    _centerinv[n][2] = -center[2];
  }
}
  
void
Mobile::
move( TransformX const &transform )
{
  DIE_IF (_matrix_dim == 0U);
  DIE_IF( transform.dim() != _matrix_dim,
           "(transform.dim() == %d) != (_matrix_dim == %d)",
           transform.dim(), _matrix_dim );
  DIE_IF( _place.position.dim() != _matrix_dim );
  DIE_IF( _place.rotation.dim() != _matrix_dim );
  DIE_IF( _place.translation.dim() != _matrix_dim );
  DIE_IF( _center.dim() != _matrix_dim );
  DIE_IF( _centerinv.dim() != _matrix_dim );


  // update _place from transform

  Transform m;
  m.allocate(_matrix_dim);
  transform.to_matrix( m );

  // OK

  if ( transform.is_translation() )
  {
    _place.translation.mul( m );
  }
  else
  {
    // rotate about _center
    if (_matrix_dim == 4U)
    {
      _place.rotation.mul( _centerinv );
    }
    _place.rotation.mul( m );
    if (_matrix_dim == 4U)
    {
      _place.rotation.mul( _center );
    }
  }

  // OK

  if ( _rotation_mode == CENTER_AT_OBJECT )
  {
    _place.position.mul( _place.rotation, _place.translation );
  }
  else
  {
    _place.position.mul( _place.translation, _place.rotation );
  }

  // check for overflow
  uint i;
  for ( i = 0; i < _matrix_dim; i++ )
  {
    uint j;
    for ( j = 0; j < _matrix_dim; j++ )
    {
      if (math::abs(_place.position[i][j])>1.0e+4)
      {
        WARN("overflow in position matrix");
        _place.position.identity();
        _place.rotation.identity();
        _place.translation.identity();
        break;
      }
    }
  }
}


void
Mobile::
view_mode( int model )
{
  if (model == 0)
  {
    _rotation_mode = CENTER_AT_OBJECT;
  }
  else
  {
    _rotation_mode = CENTER_AT_ORIGIN;
  }
}

} // namespace motion

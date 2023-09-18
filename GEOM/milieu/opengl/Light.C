/* GANG Software
 * GEOM/milieu/opengl/Light.C
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

#include "base/System.H"
#include "opengl/OpenGL.H"
#include "Light.H"

namespace milieu {
namespace opengl {

// light at the origin
float const Light::standard_light[4] = {0.0f, 0.0f, 0.0f, 1.0f};

Light::
Light( uint id )
    :
    ::milieu::kernel::Light(),
    motion::Mobile(3U, motion::CENTRAL),
    _id(id)
{
}

Light::
~Light()
{
}

void
Light::
reset()
{
  // reset position
  motion::Place place;
  place.position.identity(4U);
  place.rotation.identity(4U);
  place.translation.identity(4U);
  motion::Center center;
  center.set(0.0);
  set( place, center, motion::CENTRAL );

  // baseclass version
  kernel::Light::reset();
}

void
Light::
enable( bool state )
{
  ::milieu::kernel::Light::enable(state);
  ::opengl::glenable( (GLenum)(GL_LIGHT0 + _id), state );
#if 0
  light_enable( _id, state );
#endif
  refresh();
}

void
Light::
moving( bool state )
{
  ::milieu::kernel::Light::moving(state);
#if 0
  light_moving( _id, state );
#endif
  refresh();
}

void
Light::
show( bool state )
{
  ::milieu::kernel::Light::show(state);
  refresh();
}

void
Light::
attached( bool state )
{
  ::milieu::kernel::Light::attached(state);
#if 0
  light_attached( _id, state );
#endif
  refresh();
}

void
Light::
ambient( base::Color3 const &a )
{
  ::milieu::kernel::Light::ambient(a);
  float x[4U];
  x[0] = a.data()[0];
  x[1] = a.data()[1];
  x[2] = a.data()[2];
  x[3] = 0.0f;
  glLightfv( GL_LIGHT0 + _id, GL_AMBIENT, x );
  refresh();
}

void
Light::
diffuse( base::Color3 const &a )
{
  ::milieu::kernel::Light::diffuse(a);
  float x[4U];
  x[0] = a.data()[0];
  x[1] = a.data()[1];
  x[2] = a.data()[2];
  x[3] = 0.0f;
  glLightfv( GL_LIGHT0 + _id, GL_DIFFUSE, x );
  refresh();
}

void
Light::
specular( base::Color3 const &a )
{
  ::milieu::kernel::Light::specular(a);
  float x[4U];
  x[0] = a.data()[0];
  x[1] = a.data()[1];
  x[2] = a.data()[2];
  x[3] = 0.0f;
  glLightfv( GL_LIGHT0 + _id, GL_SPECULAR, x );
  refresh();
}

void
Light::
spot( base::ArrayX<float,5U> const &a )
{
  /*
    GL_SPOT_DIRECTION: (spot[0], spot[1], spot[2])
    GL_SPOT_EXPONENT: spot[3] in range [0, 1] (not [0,128])
    GL_SPOT_CUTOFF:   spot[4] in range [0, 1] (not [0,180])
  */
  base::ArrayX<float,5U> b = a;
  float angle = b[4];
  if (angle > 0.5) { angle = 1.0; }
  ::milieu::kernel::Light::spot(b);

  // direction
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  glLightfv( GL_LIGHT0 + _id, GL_SPOT_DIRECTION, a.data() );
  glPopMatrix();

  // exponent
  glLightf( GL_LIGHT0 + _id, GL_SPOT_EXPONENT, 128.0f*a[3] );

  // cutoff
  // GL_SPOT_CUTOFF accepts values [0, 90] and 180
  glLightf( GL_LIGHT0 + _id, GL_SPOT_CUTOFF, 180.0f * angle );

  refresh();
}

void
Light::
attenuation( base::ArrayX<float,3U> const &a )
{
  ::milieu::kernel::Light::attenuation(a);

  glLightf( GL_LIGHT0 + _id, GL_CONSTANT_ATTENUATION, a[0] );
  glLightf( GL_LIGHT0 + _id, GL_LINEAR_ATTENUATION, a[1] );
  glLightf( GL_LIGHT0 + _id, GL_QUADRATIC_ATTENUATION, a[2] );
  refresh();
}

void
Light::
draw() const
{
  GLenum id = (GLenum)(GL_LIGHT0 + _id);

  ::opengl::glenable( id, enable() );

  float x[4U];
  x[0] = ambient().data()[0];
  x[1] = ambient().data()[1];
  x[2] = ambient().data()[2];
  x[3] = 0.0f;
  glLightfv( id, GL_AMBIENT, x );
  x[0] = diffuse().data()[0];
  x[1] = diffuse().data()[1];
  x[2] = diffuse().data()[2];
  x[3] = 0.0f;
  glLightfv( id, GL_DIFFUSE, x );
  x[0] = specular().data()[0];
  x[1] = specular().data()[1];
  x[2] = specular().data()[2];
  x[3] = 0.0f;
  glLightfv( id, GL_SPECULAR, x );

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  glLightfv( id, GL_SPOT_DIRECTION, spot().data() );
  glPopMatrix();
  
  glLightf( id, GL_SPOT_EXPONENT, 128.0f * spot()[3] );
  glLightf( id, GL_SPOT_CUTOFF, 180.0f * spot()[4] );
  
  glLightf( id, GL_CONSTANT_ATTENUATION, attenuation()[0] );
  glLightf( id, GL_LINEAR_ATTENUATION, attenuation()[1] );
  glLightf( id, GL_QUADRATIC_ATTENUATION, attenuation()[2] );

  draw_position();
}

void
Light::
draw_position() const
{
#if 0
  if ( id() == 0) {
    std::cerr << _place.position;
  }
#endif

  // position the light
  if ( enable() )
  {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    ::opengl::glLoadMatrix( _place.position );
    glLightfv( GL_LIGHT0 + _id, GL_POSITION, standard_light );
    glPopMatrix();
  }

  // show the light
  // draw a dot for the light
  if ( show() )
  {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glDisable(GL_LIGHTING);
    glEnable( GL_POINT_SMOOTH );

    glPointSize(4.0f);
    glBegin(GL_POINTS);
    glColor3f( 1.0f, 1.0f, 0.0f ); //yellow

    uint const n = 3U;
    glVertex3f( _place.translation[n][0], _place.translation[n][1],
                _place.translation[n][2] );

    glEnd();

    glPopAttrib();

    glPopMatrix();
  }
}

} // namespace opengl
} // namespace milieu

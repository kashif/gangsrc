/* GANG Software
 * VIEWER/isight/context/Sphere.C
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

#include <GL/gl.h>
#include "math/Math.H"
#include "Sphere.H"

namespace isight {
namespace context {


Sphere::
Sphere()
    :
    _mode(DISABLED)
{
}

Sphere::
~Sphere()
{
}

void
Sphere::
draw() const
{
  if ( _mode == DISABLED ) { return; }

  glMatrixMode(GL_MODELVIEW);

  glPushAttrib(GL_ALL_ATTRIB_BITS);
  glDisable(GL_LIGHTING);
  glEnable( GL_POINT_SMOOTH );
//  glEnable( GL_LINE_SMOOTH );

  glColor3f( 0.51, 0.51, 0.51 );

  // draw lines
  glLineWidth( 1.0f );

  if (_mode == CIRCLE)
  { draw_circle(); }
  else { draw_sphere(); }

  glPopAttrib();
}

void
Sphere::
draw_circle() const
{
  glBegin(GL_LINE_STRIP);
  uint i;
  for ( i = 0; i <= circle_count; i++ )
  {
    float u = 2.0*math::pi*float(i)/float(circle_count);
    float r = math::cos(u);
    float s = math::sin(u);
    glVertex3f( r, s, 0.0 );
  }
  glEnd();
}

void
Sphere::
draw_sphere() const
{
  uint s = (_mode == BACK_HEMISPHERE ? latitude_count/2 : latitude_count - 1);

  // latitude lines
  uint j;
  for ( j = 1; j <= s; j++ )
  {
    glBegin(GL_LINE_STRIP);

    float v = math::pi*( float(j)/float(latitude_count) - 0.5 );
    float r2 = math::cos(v);
    float s2 = math::sin(v);
    uint i;
    for ( i = 0; i <= longitude_count; i++ )
    {
      float u = 2.0*math::pi*float(i)/float(longitude_count);
      float r1 = math::cos(u);
      float s1 = math::sin(u);
      glVertex3f( r2*r1, r2*s1, s2 );
    }

    glEnd();
  }

  // longitude lines
  uint i;
  for ( i = 0; i < longitude_count; i++ )
  {
    glBegin(GL_LINE_STRIP);

    float u = 2.0*math::pi*float(i)/float(longitude_count);
    float r1 = math::cos(u);
    float s1 = math::sin(u);
    for ( j = 1; j <= s; j++ )
    {
      float v = math::pi*( float(j)/float(latitude_count) - 0.5 );
      float r2 = math::cos(v);
      float s2 = math::sin(v);
      glVertex3f( r2*r1, r2*s1, s2 );
    }

    glEnd();
  }

#if 0
  // draw points
  glPointSize( 4.0f );

  glBegin(GL_POINTS);

  for ( j = 0; j < n; j++ )
  {
    float v = 2*math::pi*j/n;
    float r2 = math::cos(v);
    float s2 = math::sin(v);
    for ( i = 0; i < s*n; i++ )
    {
      float u = 2*math::pi*i/(s*n);
      float r1 = math::cos(u);
      float s1 = math::sin(u);
      glVertex3f( r2*r1, r2*s1, s2 );
    }
  }

  glEnd();
#endif
}

} // namespace context
} // namespace isight

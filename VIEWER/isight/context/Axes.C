/* GANG Software
 * VIEWER/isight/context/Axes.C
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
#include "base/System.H"
#include "Axes.H"

namespace isight {
namespace context {

float const Axes::axes_plus[3][3] =
{
  { 1.0f, 0.0f, 0.0f }, // x
  { 0.0f, 1.0f, 0.0f }, // y
  { 0.0f, 0.0f, 1.0f }  // z
};

float const Axes::axes_minus[3][3] =
{
  { -1.0f, 0.0f, 0.0f }, // x
  { 0.0f, -1.0f, 0.0f }, // y
  { 0.0f, 0.0f, -1.0f }  // z
};

float const Axes::axes_color_plus[3][3] =
{
  { 0.8f, 0.2f, 0.2f }, // red
  { 0.2f, 0.8f, 0.2f }, // green
  { 0.2f, 0.2f, 0.8f }  // blue
};

float const Axes::axes_color_minus[3][3] =
{
  { 0.5f, 0.1f, 0.1f }, // red
  { 0.1f, 0.5f, 0.1f }, // green
  { 0.1f, 0.1f, 0.5f }  // blue
};

Axes::
Axes()
    :
    _enable(false)
{
}

Axes::
~Axes()
{
}

void
Axes::
draw() const
{
  if ( ! _enable ) { return; }

  glMatrixMode(GL_MODELVIEW);

  glPushAttrib(GL_ALL_ATTRIB_BITS);
  glDisable(GL_LIGHTING);
  glEnable( GL_POINT_SMOOTH );
//  glEnable( GL_LINE_SMOOTH );

  uint i;
  // draw lines
  glLineWidth( 1.0f );

  glBegin(GL_LINES);

  for ( i = 0; i < 3; i++ )
  {
    // positive axis
    glColor3fv( axes_color_plus[i] );
    glVertex3f( 0.0f, 0.0f, 0.0f );
    glVertex3fv( axes_plus[i] );

    // negative axis
    glColor3fv( axes_color_minus[i] );
    glVertex3f( 0.0f, 0.0f, 0.0f );
    glVertex3fv( axes_minus[i] );
  }

  glEnd();

#if 0
  // draw points
  glPointSize( 4.0f );

  glBegin(GL_POINTS);

  for ( i = 0; i < 3; i++ )
  {
    // positive axis
    glColor3fv( axes_color_plus[i] );
    glVertex3fv( axes_plus[i] );

    // negative axis
    glColor3fv(axes_color_minus[i]);
    glVertex3fv( axes_minus[i] );
  }
  glEnd();
#endif
  glPopAttrib();
}

} // namespace context
} // namespace isight

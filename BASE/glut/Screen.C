/* GANG Software
 * BASE/glut/Screen.C
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

#include <stdlib.h>
#include <math.h>
#include <iostream.h>
#include <GL/glut.h>
#include "base/System.H"
#include "base/String.H"
#include "Screen.H"

namespace glut {

Screen *Screen::_this = (Screen *)0;

Screen::
Screen(
  char const *title,
  int width, int height,
  int argc, char *argv[] )
{
  _this = this;

  _width = width;
  _height = height;

  // initialize GLUT system
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(width, height);

  // create window
  _window = glutCreateWindow(title);

  // set background to black
  glClearColor(0.0,0.0,0.0,0.0);

  // handlers
  glutDisplayFunc(display_cb_);
  glutKeyboardFunc(key_cb_);
  glutMouseFunc(mouse_cb_);
  glutReshapeFunc(reshape_cb_);
  glutMotionFunc(motion_cb_);
}

Screen::
~Screen()
{
}

void
Screen::
loop()
{
  // There is no way to return from glutMainLoop() directly; the
  // C++ exception mechanism is used instead.
  try
  {
    glutMainLoop();
  }
  catch (int)
  {
  }
}

void
Screen::
reshape_cb0(uint width, uint height)
{
  glViewport( 0, 0, width, height );
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // note backwards y
  gluOrtho2D( 0, width, 0, height );

  // Call the subclass version.
  reshape_cb( width, height );

  // cache the new width/height
  // do this after the call to reshape_cb so that function has access
  // to the old sizes
  _width = width;
  _height = height;
}

void
Screen::
clear_window()
{
  // clear the display
  glClear(GL_COLOR_BUFFER_BIT);
}

void
Screen::
set_point_size( float x )
{
  glPointSize(x);
}

void
Screen::
set_line_size( float x )
{
  glLineWidth(x);
}

void
Screen::
set_color( Color const &color )
{
  glColor3fv( color.x );
}

void
Screen::
write_number( int n, Point const &p )
{
  base::String s;
  s.to_string( n );
  glRasterPos2i( (int)rint(p.x), (int)rint(p.y) );
  size_t i;
  for ( i = 0; i != s.length(); i++)
  {
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, s[i]);
  }
}

void
Screen::
draw_point( Point const &p )
{
  glBegin(GL_POINTS);
  glVertex2f( p.x, p.y );
  glEnd();
}

void
Screen::
draw_points( base::vector<Point> const &v )
{
  glBegin(GL_POINTS);

  base::vector<Point>::const_iterator i;
  for ( i = v.begin(); i != v.end(); i++ )
  {
    glVertex2f( (*i).x, (*i).y );
  }

  glEnd();
}

void
Screen::
draw_line( Point const &a, Point const &b )
{
  glBegin(GL_LINES);
  glVertex2i( (int)rint(a.x), (int)rint(a.y) );
  glVertex2i( (int)rint(b.x), (int)rint(b.y) );
  glEnd();
}

void
Screen::
draw_lines( base::vector<Point> const &v, bool loop )
{
  if ( v.size() < 2 ) { return; }

  glBegin(GL_LINES);

  base::vector<Point>::const_iterator i;
  for ( i = v.begin(); i != v.end() - 1; i++ )
  {
    glVertex2i( (int)rint((*i).x), (int)rint((*i).y) );
    glVertex2i( (int)rint((*(i+1)).x), (int)rint((*(i+1)).y) );
  }

  if ( loop )
  {
    // draw the final line making a loop
    i = v.end() - 1;
    glVertex2i( (int)rint((*i).x), (int)rint((*i).y) );
    i = v.begin();
    glVertex2i( (int)rint((*i).x), (int)rint((*i).y) );
  }

  glEnd();
}

void
Screen::
flush()
{
  glFlush();
}

void
Screen::
set_background_color( Color const &x )
{
  // set background to black
  glClearColor( x.x[0], x.x[1], x.x[2], 1.0 );
  clear_window();
  display_cb();
  flush();
}

} // namespace glut

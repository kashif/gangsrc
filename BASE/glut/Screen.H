/* GANG Software
 * BASE/glut/Screen.H
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

#ifndef glut_Screen_INCLUDED
#define glut_Screen_INCLUDED

#include "base/vector.H"
#include "math/Vector2.H"

namespace glut {

using namespace math;

/*
  glut-based screen.
*/
class Screen
{
public:

  Screen(
    char const *title,
    int width, int height,
    int argc, char *argv[] );

  virtual ~Screen();

  void clear_window();

  void set_point_size( float );
  void set_line_size( float );

  struct Color {
    Color( float r, float g, float b )
      { x[0] = r; x[1] = g; x[2] = b; }
    float x[3];
  };

  typedef double Real;
  typedef math::Vector2<Real> Point;

  void set_color( Color const & );
  void flush();
  void write_number( int n, Point const & );

  void draw_point( Point const & );
  void draw_points( base::vector<Point> const & );
  void draw_line( Point const &, Point const & );
  void draw_lines( base::vector<Point> const &, bool loop );

  void loop();

  void set_background_color( Color const & );

  uint width() const
    { return _width; }
  uint height() const
    { return _height; }

protected:
  virtual void display_cb() = 0;
  virtual void reshape_cb( uint width, uint height ) {}
  virtual void key_cb(unsigned char key, uint x, uint y) {}
  virtual void mouse_cb( int button, int state, uint x, uint y) {}
  virtual void motion_cb( uint x, uint y ) {}

private:

  virtual void reshape_cb0( uint width, uint height );

  static void reshape_cb_(int width, int height)
    { _this->reshape_cb0(width, height); }
  static void key_cb_(unsigned char key, int x, int y)
    { _this->key_cb(key, x, _this->height()-y); }
  static void mouse_cb_( int button, int state, int x, int y)
    { _this->mouse_cb(button, state, x, _this->height()-y); }
  static void display_cb_()
    { _this->display_cb(); }
  static void motion_cb_( int x, int y )
    { _this->motion_cb(x, _this->height()-y); }

  uint _width;
  uint _height;
  int _window;

  // for glut callbacks
  static Screen *_this;

  Screen( Screen const & );
  Screen &operator=( Screen const & );
};

} // namespace glut

#endif // glut_Screen_INCLUDED

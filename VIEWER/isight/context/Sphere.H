/* GANG Software
 * VIEWER/isight/context/Sphere.H
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

#ifndef isight_context_Sphere_INCLUDED
#define isight_context_Sphere_INCLUDED

#include "base/System.H"

namespace isight {
namespace context {

class Sphere
{

public:
  // constructor
  Sphere();

  // destructor
  virtual ~Sphere();

  enum Mode { DISABLED, SPHERE, BACK_HEMISPHERE, CIRCLE };
  Mode mode() const
    { return _mode; }
  void enable( Mode mode )
    { _mode = mode; }
  void draw() const;

  void mode( Mode m )
    { _mode = m; }
protected:

private:

  void draw_sphere() const;
  void draw_circle() const;

  Mode _mode;

  // number of longitude lines
  static uint const longitude_count = 30U;
  // number of latitude lines
  static uint const latitude_count = 20U;

  static uint const circle_count = 360U;

  // disabled copy constructor
  Sphere( Sphere const & );

  // disabled assignment operator
  Sphere &operator=( Sphere const & );

};

} // namespace context
} // namespace isight

#endif // isight_context_Sphere_INCLUDED

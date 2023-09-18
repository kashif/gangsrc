/* GANG Software
 * GEOM/milieu/opengl/ClipPlane.H
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

#ifndef milieu_opengl_ClipPlane_INCLUDED
#define milieu_opengl_ClipPlane_INCLUDED

#include "motion/Mobile.H"
#include "milieu/kernel/ClipPlane.H"

namespace milieu {
namespace opengl {

class ClipPlane
  :
    public ::milieu::kernel::ClipPlane,
    public ::motion::Mobile
{

public:
  // constructor
  ClipPlane( uint id );

  // destructor
  virtual ~ClipPlane();

  uint id() const { return _id; }
  void draw() const;
  void reset();

  // access functions
  virtual bool const &enable() const
    { return ::milieu::kernel::ClipPlane::enable(); }
  virtual bool const &moving() const
    { return ::milieu::kernel::ClipPlane::moving(); }
  virtual bool const &show() const
    { return ::milieu::kernel::ClipPlane::show(); }
  virtual bool const &attached() const
    { return ::milieu::kernel::ClipPlane::attached(); }
  virtual motion::Transform const &position() const
    { return Mobile::position(); }

  virtual void enable( bool a );
  virtual void moving( bool a );
  virtual void show( bool a );
  virtual void attached( bool a );
  virtual void position( motion::Transform const &x )
    { Mobile::position(x); }

protected:

  virtual void refresh() = 0;

private:

  void draw_position() const;

  // the xy coordinate plane
  static double const standard_clipplane[4];

  uint _id;

  // disabled copy constructor
  ClipPlane( ClipPlane const & );
  // disabled assignment operator
  ClipPlane &operator=( ClipPlane const & );
};

} // namespace opengl
} // namespace milieu

#endif // milieu_opengl_ClipPlane_INCLUDED

/* GANG Software
 * GEOM/milieu/opengl/Background.H
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

#ifndef milieu_opengl_Background_INCLUDED
#define milieu_opengl_Background_INCLUDED

#include "milieu/kernel/Background.H"

namespace milieu {
namespace opengl {

class Background
  :
    virtual public milieu::kernel::Background
{

public:
  // constructor
  Background();

  // copy constructor
  Background( Background const & );

  // destructor
  virtual ~Background();

  // assignment operator
  Background &operator=( Background const & );

  // access functions
  virtual base::Color3 const &color() const
    { return ::milieu::kernel::Background::color(); }

  virtual void color( base::Color3 const &a );

  virtual void enable_draw(bool) = 0;

  virtual void refresh() = 0;

  virtual void background_image( base::String const &filename ) = 0;
  virtual void background_clear_image() = 0;
  virtual void stars(bool state) = 0;

//  virtual void background_next();
//  virtual void background_prev();
//  virtual void background_synchronize();
protected:

  void draw() const;

private:

  static float const DEFAULT_ALPHA;

};

} // namespace opengl
} // namespace milieu

#endif // milieu_opengl_Background_INCLUDED

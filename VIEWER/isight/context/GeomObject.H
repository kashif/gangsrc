/* GANG Software
 * VIEWER/isight/context/GeomObject.H
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

#ifndef isight_context_GeomObject_INCLUDED
#define isight_context_GeomObject_INCLUDED

#include "geom/interface/SurfaceGL.H"
#include "motion/Mobile.H"

namespace isight {
namespace context {

class GeomObject
  :
    public motion::Mobile
{

public:
  // constructor
  GeomObject(
    geom::SurfaceGL const *g,
    motion::Place const &position,
    motion::Center const &center,
    motion::ProjectionMode mode );

  // destructor
  virtual ~GeomObject();

  virtual void draw() const;

  void set_movemode( bool fast );

  geom::SurfaceGL const *geomobject() const
    { return _geomobject; }

  bool showing() const { return _showing; }
  bool moving() const { return _moving; }

  void showing(bool state) { _showing = state; }
  void moving(bool state) { _moving = state; }

protected:
private:

  bool _showing;
  bool _moving;

  bool _fast;

  geom::SurfaceGL const *_geomobject;

  // disabled copy constructor
  GeomObject( GeomObject const & );

  // disabled assignment operator
  GeomObject &operator=( GeomObject const & );
};

} // namespace context
} // namespace isight

#endif // isight_context_GeomObject_INCLUDED

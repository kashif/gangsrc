/* GANG Software
 * GEOM/geom/surface0/GeomObject.H
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

#ifndef geom_surface0_GeomObject_INCLUDED
#define geom_surface0_GeomObject_INCLUDED

#include "io/Ostream.H"
#include "Common.H"
#include "Vertex.H"
#include "BoundingBox.H"

namespace geom {
namespace surface0 {

class GeomObject
{

public:

  // constructor
  GeomObject();

  // copy constructor
  GeomObject( GeomObject const & );

  // destructor
  virtual ~GeomObject();

  // assignment operator
  GeomObject &operator=( GeomObject const & );

  virtual uint dimension() const = 0;

  virtual void changed( bool state ) const
    { _changed = state; }
  virtual bool is_changed() const
    { return _changed; }
  virtual uint id() const
    { return _id; }

  virtual base::String name() const
    { return _name; }
  void name( base::String const &s )
    { _name = s; }

  virtual void dump( ::io::Ostream & ) const = 0;

  Transform const &position() const
    { return _position; }
  void position( Transform const &t )
    { _position = t; }
  ProjectionMode projection_mode() const
    { return _projection_mode; }
  void projection_mode( ProjectionMode mode )
    { _projection_mode = mode; }

protected:

private:

  mutable bool _changed;

  base::String _name;

  Transform _position;
  mutable ProjectionMode _projection_mode;

  uint _id;
  static uint _static_id;
};

} // namespace surface0
} // namespace geom

#endif // geom_surface0_GeomObject_INCLUDED

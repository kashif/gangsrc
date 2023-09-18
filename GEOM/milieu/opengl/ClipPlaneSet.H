/* GANG Software
 * GEOM/milieu/opengl/ClipPlaneSet.H
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

#ifndef milieu_opengl_ClipPlaneSet_INCLUDED
#define milieu_opengl_ClipPlaneSet_INCLUDED

#include "base/ArrayX.H"
#include "milieu/kernel/ClipPlaneSetBase.H"
#include "ClipPlane.H"

namespace milieu {
namespace opengl {

class ClipPlaneSet
  :
    public milieu::kernel::ClipPlaneSetBase
{

public:
  // constructor
  ClipPlaneSet();

  // destructor
  virtual ~ClipPlaneSet();

  void reset();
  void reset( uint n );

//  virtual void geomobject_move_enable(bool state) = 0;
//  virtual void light_moving_off() = 0;

  bool moving( uint id ) const
    { return ClipPlaneSetBase::moving(id); }
  void moving( uint id, bool state );

protected:

  void move( motion::TransformX const & );
  void draw() const;
  virtual void refresh() = 0;
  virtual void _milieu_moving_notify(bool) = 0;

private:

  virtual ClipPlane &elem(uint id) { return *_[id]; }
  virtual ClipPlane const &elem(uint id) const { return *_[id]; }

  ClipPlane &operator[](uint id)
    { return *static_cast< ClipPlane *>(_[id]); }
  ClipPlane const &operator[](uint id) const
    { return *static_cast< ClipPlane const *>(_[id]); }

  class ClipPlane1 : public ClipPlane
  {
  public:
    ClipPlane1( uint id, ClipPlaneSet *parent )
        : ClipPlane(id), _parent(parent) {}
  protected:
    virtual void refresh()
      { _parent->refresh(); }
  private:
    ClipPlaneSet *_parent;
  };

  base::ArrayX<ClipPlane1 *, CLIPPLANE_COUNT> _;

  // disabled copy constructor
  ClipPlaneSet( ClipPlaneSet const & );
  // disabled assignment operator
  ClipPlaneSet &operator=( ClipPlaneSet const & );

};

} // namespace opengl
} // namespace milieu

#endif // milieu_opengl_ClipPlaneSet_INCLUDED

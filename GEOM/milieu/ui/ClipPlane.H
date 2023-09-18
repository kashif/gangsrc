/* GANG Software
 * GEOM/milieu/ui/ClipPlane.H
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

#ifndef milieu_ui_ClipPlane_INCLUDED
#define milieu_ui_ClipPlane_INCLUDED

#include "math/ReadUtil.H"
#include "widget/ui/Dialog.H"
#include "widget/ui/Choice.H"
#include "widget/ui/Boolean.H"
#include "milieu/opengl/ClipPlaneSet.H"

namespace milieu {

namespace opengl { class ClipPlaneSet; }

namespace ui {

class ClipPlane
  :
    public widget::ui::Dialog,
    public math::ReadUtil
{

public:
  typedef double Real;
  typedef math::Matrix<Real> Transform;

  // constructor
  ClipPlane();

  // destructor
  virtual ~ClipPlane();

  // interface
  virtual void clipplane_reset();
  virtual void clipplane_reset( uint id );
  virtual void clipplane_select( uint id )
    { id_w()->set(id); }
  virtual void clipplane_enable( uint id, bool a );
  virtual void clipplane_moving( uint id, bool a );
  virtual void clipplane_show( uint id, bool a );
  virtual void clipplane_attached( uint id, bool a );
  virtual void clipplane_position( bool id, Transform const &a );
  virtual void clipplane_synchronize()
    { set_ui_from_data( clipplaneset() ); }

  bool command(
    base::String const &command,
    base::String const &argument,
    base::String &response );

protected:

  // callbacks
  // callbacks
  virtual void id_cb()
    { clipplane_synchronize(); }
  virtual void enable_cb()
    { _enable( id_w()->get(), enable_w()->get() ); }
  virtual void moving_cb()
    { clipplaneset()->moving( id_w()->get(), moving_w()->get() ); }
  virtual void show_cb()
    { _show( id_w()->get(), show_w()->get() ); }
  virtual void attached_cb()
    { _attached( id_w()->get(), attached_w()->get() ); }
  virtual void reset_cb()
    { clipplane_reset( id_w()->get() ); }

  char const *label()
    { return "Clip Plane"; }

private:

  // pure virtuals
  virtual ::milieu::opengl::ClipPlaneSet *clipplaneset() = 0;
  virtual ::milieu::opengl::ClipPlaneSet const *clipplaneset() const = 0;
//  virtual void geomobject_move_enable(bool state) = 0;
//  virtual void light_moving_off() = 0;

  // widgets
  virtual widget::ui::Choice *id_w() = 0;
  virtual widget::ui::Boolean *enable_w() = 0;
  virtual widget::ui::Boolean *moving_w() = 0;
  virtual widget::ui::Boolean *show_w() = 0;
  virtual widget::ui::Boolean *attached_w() = 0;

  // implementation
  void _select( uint id );
  void _reset( uint id );
  void _enable( uint id, bool a )
    { clipplaneset()->enable( id, a ); }
//  void _moving( uint id, bool a );
  void _show( uint id, bool a )
    { clipplaneset()->show( id, a ); }
  void _attached( uint id, bool a )
    { clipplaneset()->attached( id, a ); }

  // utility
  void set_ui_from_data( opengl::ClipPlaneSet *clipplaneset );

  // disabled copy constructor
  ClipPlane( ClipPlane const & );
  // disabled assignment operator
  ClipPlane &operator=( ClipPlane const & );

};

} // namespace ui
} // namespace milieu

#endif // milieu_ui_ClipPlane_INCLUDED

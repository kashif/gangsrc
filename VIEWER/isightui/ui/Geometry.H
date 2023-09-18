/* GANG Software
 * VIEWER/isightui/ui/Geometry.H
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

#ifndef isightui_ui_Geometry_INCLUDED
#define isightui_ui_Geometry_INCLUDED

#include "base/ReadUtil.H"
#include "widget/ui/Dialog.H"
#include "widget/ui/Choice.H"
#include "motion/Common.H"

namespace isight { namespace kernel { class ViewerBase; } }

namespace isightui {
namespace ui {

class Viewer;

class Geometry
  :
    public widget::ui::Dialog,
    public base::ReadUtil
{

public:

  // constructor
  Geometry();

  // destructor
  virtual ~Geometry();

  virtual void get_geometry( motion::GeometryMode &mode,
                             motion::GeometryGroup &group,
                             uint &dim ) const;
  virtual void set_geometry( motion::GeometryMode mode,
                             motion::GeometryGroup group,
                             uint dim );
  virtual void reset_geometry();

  virtual void geometry_mousemode( motion::MouseMode x )
    { mousemode_w()->set( uint(x) ); }
  void mouse_rotation()
    { geometry_mousemode( motion::ROTATION ); }
  void mouse_translation()
    { geometry_mousemode( motion::TRANSLATION ); }
  void mouse_inversion()
    { geometry_mousemode( motion::INVERSION ); }
  void mouse_scale()
    { geometry_mousemode( motion::SCALE ); }

  //
  void synchronize();

  char const *label() const
    { return "Geometry"; }

  bool command(
    base::String const &command,
    base::String const &argument,
    base::String &response );

protected:

  // callbacks
  virtual void reset_position_cb();
  virtual void geometry_reset_cb()
    { reset_geometry(); }
  virtual void geometry_mode_cb()
    { _set_geometry(); }
  virtual void geometry_group_cb()
    { _set_geometry(); }
  virtual void geometry_dim_cb()
    { _set_geometry(); }
  virtual void mousemode_cb();

private:

  virtual isight::kernel::ViewerBase *viewer() = 0;
  virtual isight::kernel::ViewerBase const *viewer() const = 0;

  void _set_geometry();

  // widgets
  virtual widget::ui::Choice *geometry_mode_w() = 0;
  virtual widget::ui::Choice const *geometry_mode_w() const = 0;
  virtual widget::ui::Choice *geometry_group_w() = 0;
  virtual widget::ui::Choice const *geometry_group_w() const = 0;
  virtual widget::ui::Choice *geometry_dim_w() = 0;
  virtual widget::ui::Choice const *geometry_dim_w() const = 0;
  virtual widget::ui::Choice *mousemode_w() = 0;
  virtual widget::ui::Choice const *mousemode_w() const = 0;

  static uint const DIM_OFFSET = 2U;

  Geometry( Geometry const & );
  Geometry &operator=( Geometry const & );

};

} // namespace ui
} // namespace isightui

#endif // isightui_ui_Geometry_INCLUDED

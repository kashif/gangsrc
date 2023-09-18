/* GANG Software
 * VIEWER/isightui/ui/GeomObject.H
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

#ifndef isightui_ui_GeomObject_INCLUDED
#define isightui_ui_GeomObject_INCLUDED

#include "base/String.H"
#include "math/ReadUtil.H"
#include "math/Matrix.H"
#include "widget/ui/Dialog.H"
#include "widget/ui/Boolean.H"
#include "widget/ui/List.H"
#include "isight/kernel/ViewerBase.H"

namespace isightui { namespace kernel { class ViewerBase; } }

namespace isightui {
namespace ui {

class GeomObject
  :
    public widget::ui::Dialog,
    public math::ReadUtil
{

public:
  typedef double Real;
  typedef math::Matrix<Real> Transform;

  // constructor
  GeomObject();

  // destructor
  virtual ~GeomObject();

  // interface
  virtual void insert_geomobject_notify( base::String const &label );
  virtual void delete_geomobject_notify( uint id );
  virtual void select_geomobject( uint id )
    { select_geomobject_w()->set(id); }
  virtual void show_geomobject( uint id, bool state )
    { select_geomobject_w()->set(id); show_geomobject_w()->set(state); }
  virtual void move_geomobject( uint id, bool state )
    { select_geomobject_w()->set(id); move_geomobject_w()->set(state); }
  virtual void move_all_geomobjects( bool state );
  virtual void delete_geomobject( uint id )
    { select_geomobject_w()->set(id); delete_geomobject_cb(); }
  virtual void delete_all_geomobjects();
  virtual bool replace_geomobject() const
    { return replace_geomobject_w()->get(); }
  virtual void replace_geomobject(bool state)
    { replace_geomobject_w()->set(state); }
  virtual uint selected_geomobject() const
    { return select_geomobject_w()->get(); }
  void geomobject_position( uint id, Transform const &position )
    { viewer()->context()->geomobject_position( id, position ); }
  virtual void geomobject_inherit_materials(bool a)
    { _inherit_materials = a; }
  virtual bool geomobject_inherit_materials() const
    { return _inherit_materials; }
  virtual uint position_by_box() const
    { return _position_by_box; }
  virtual void position_by_box(uint state)
    { _position_by_box = state; }

  // no row is selected
  static uint const NONE = (uint)(-1);

  bool command(
    base::String const &command,
    base::String const &argument,
    base::String &response );

protected:

  // callbacks
  virtual void select_geomobject_cb();
  virtual void show_geomobject_cb();
  virtual void move_geomobject_cb();
  virtual void delete_geomobject_cb();

  char const *label() const
    { return "GeomObject Object"; }

private:

  virtual isight::kernel::ViewerBase *viewer() = 0;
  virtual isight::kernel::ViewerBase const *viewer() const = 0;

  void synchronize();
  void set_sensitive();
  uint item_count() const
    { return select_geomobject_w()->item_count(); }

  bool _inherit_materials;
  uint _position_by_box;

  // widgets
  virtual widget::ui::List *select_geomobject_w() = 0;
  virtual widget::ui::List const *select_geomobject_w() const = 0;
  virtual widget::ui::Boolean *show_geomobject_w() = 0;
  virtual widget::ui::Boolean *move_geomobject_w() = 0;
  virtual widget::ui::Boolean *replace_geomobject_w() = 0;
  virtual widget::ui::Boolean const *replace_geomobject_w() const = 0;
  virtual widget::ui::Widget *delete_geomobject_w() = 0;

  GeomObject( GeomObject const & );
  GeomObject &operator=( GeomObject const & );

};

} // namespace ui
} // namespace isightui

#endif // isightui_ui_GeomObject_INCLUDED

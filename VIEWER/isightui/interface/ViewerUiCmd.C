/* GANG Software
 * VIEWER/isightui/interface/ViewerUiCmd.C
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

#include "isightui/cmd/Ui.H"
#include "ViewerUiCmd.H"

namespace isightui {

class _ViewerUiCmd
  :
    public isightui::cmd::Ui
{
public:
  _ViewerUiCmd( ViewerUiCmd *parent) : _parent(parent) {}
  virtual ~_ViewerUiCmd() {}
protected:
  virtual isight::kernel::ViewerBase *viewer()
    { return _parent->viewer(); }
  virtual isight::kernel::ViewerBase const *viewer() const
    { return _parent->viewer(); }
  virtual geom::Surface const *geomlist() const
    { return _parent->surface(); }
  virtual geom::Surface *geomlist()
    { return _parent->surface(); }
  virtual ::geomui::GeomUi *geom_ui()
    { return _parent->geom_ui(); }
  virtual ::geomui::GeomUi const *geom_ui() const
    { return _parent->geom_ui(); }
  virtual ::milieu::MilieuUi *milieu_ui()
    { return _parent->milieu_ui(); }
  virtual ::milieu::MilieuUi const *milieu_ui() const
    { return _parent->milieu_ui(); }
private:
  ViewerUiCmd *_parent;
  friend class ViewerUiCmd;
};

ViewerUiCmd::
ViewerUiCmd()
    :
    _(new _ViewerUiCmd(this) )
{
}

ViewerUiCmd::
~ViewerUiCmd()
{
  delete _;
}

void
ViewerUiCmd::
read(
  io::Istream &stream,
  geom::FileMode filemode = geom::FILEMODE_DEFAULT )
  throw (io::ReadException)
{
  viewer()->read(stream, filemode);
}

void
ViewerUiCmd::
read(
    base::String const &filename,
    geom::FileMode filemode = geom::FILEMODE_UNSPECIFIED )
    throw (io::ReadException)
{
  viewer()->read(filename, filemode);
}

void
ViewerUiCmd::
read(
    base::vector<base::String> const &filename,
    geom::FileMode filemode = geom::FILEMODE_UNSPECIFIED )
    throw (io::ReadException)
{
  viewer()->read(filename, filemode);
}

void
ViewerUiCmd::
write(
    io::Ostream &stream,
    geom::FileMode filemode = geom::FILEMODE_DEFAULT) const
    throw (io::WriteException)
{
  viewer()->write(stream, filemode);
}

void
ViewerUiCmd::
write(
    base::String const &filename,
    geom::FileMode filemode = geom::FILEMODE_UNSPECIFIED) const
    throw (io::WriteException)
{
  viewer()->write(filename, filemode);
}


void
ViewerUiCmd::
insert_geomobject( geom::Surface const &x )
{
  viewer()->insert_geomobject(x);
}

void
ViewerUiCmd::
insert_geomobject( geom::SurfaceGL const &x )
{
  viewer()->insert_geomobject(x);
}


void
ViewerUiCmd::
background_image( base::String const &filename )
{
  viewer()->context()->background_image(filename);
}

void
ViewerUiCmd::
_hide_all()
{
  _->show_all(false);
}

void
ViewerUiCmd::
_enable_tooltips(bool state)
{
  _->enable_tooltips(state);
}

bool
ViewerUiCmd::
_command( base::String const &command, base::String const &argment, base::String &response )
{
  return _->command( command, argment, response );
}

void
ViewerUiCmd::
synchronize()
{
  _->synchronize();
}

void
ViewerUiCmd::
move_all_geomobjects(bool state)
{
  _->move_all_geomobjects(state);
}


void
ViewerUiCmd::
geometry_toggle_raise_show()
{
  static_cast< ::isightui::ui::Geometry *>(_)->toggle_raise_show_d();
}

void
ViewerUiCmd::
mouse_toggle_raise_show()
{
  static_cast< ::isightui::ui::Mouse *>(_)->toggle_raise_show_d();
}

void
ViewerUiCmd::
read_toggle_raise_show()
{
  static_cast< ::isightui::ui::Read *>(_)->toggle_raise_show_d();
}

void
ViewerUiCmd::
geomobject_toggle_raise_show()
{
  static_cast< ::isightui::ui::GeomObject *>(_)->toggle_raise_show_d();
}

void
ViewerUiCmd::
window_toggle_raise_show()
{
  static_cast< ::isightui::ui::Window *>(_)->toggle_raise_show_d();
}

void
ViewerUiCmd::
style_toggle_raise_show()
{
  static_cast< ::isightui::ui::Style *>(_)->toggle_raise_show_d();
}

void
ViewerUiCmd::
windowsize_toggle_raise_show()
{
  static_cast< ::isightui::ui::WindowSize *>(_)->toggle_raise_show_d();
}

void
ViewerUiCmd::
write_toggle_raise_show()
{
  static_cast< ::isightui::ui::Write *>(_)->toggle_raise_show_d();
}

void
ViewerUiCmd::
writeconfig_toggle_raise_show()
{
  static_cast< ::isightui::ui::WriteConfig *>(_)->toggle_raise_show_d();
}

void
ViewerUiCmd::
windowsize_reset()
{
  _->windowsize_reset();
}

void
ViewerUiCmd::
windowsize_set( base::ArrayX<uint,2U> const &x )
{
  _->windowsize_set( x );
}

void
ViewerUiCmd::
windowsize_fullscreen( bool state )
{
  _->windowsize_fullscreen( state );
}

void
ViewerUiCmd::
windowsize_toggle_fullscreen()
{
  _->windowsize_toggle_fullscreen();
}

void
ViewerUiCmd::
windowsize_synchronize_notify()
{
  _->windowsize_synchronize_notify();
}

void
ViewerUiCmd::
style( uint n )
{
  _->style( n );
}

void
ViewerUiCmd::
axes(bool a)
{
  _->axes( a );
}

void
ViewerUiCmd::
toggle_axes()
{
  _->toggle_axes();
}

void
ViewerUiCmd::
sphere(bool a)
{
  _->sphere( a );
}

void
ViewerUiCmd::
toggle_sphere()
{
  _->toggle_sphere();
}

void
ViewerUiCmd::
stars(bool a)
{
  _->stars( a );
}

void
ViewerUiCmd::
toggle_stars()
{
  _->toggle_stars();
}

void
ViewerUiCmd::
style_prev()
{
  _->style_prev();
}

void
ViewerUiCmd::
style_next()
{
  _->style_next();
}

void
ViewerUiCmd::
reset_position()
{
  _->reset_position();
}

void
ViewerUiCmd::
stop_motion()
{
  _->stop_motion();
}

void
ViewerUiCmd::
mouse_rotation()
{
  _->mouse_rotation();
}

void
ViewerUiCmd::
mouse_translation()
{
  _->mouse_translation();
}

void
ViewerUiCmd::
mouse_inversion()
{
  _->mouse_inversion();
}

void
ViewerUiCmd::
mouse_scale()
{
  _->mouse_scale();
}

void
ViewerUiCmd::
geomobject_position( uint id, motion::Transform const &position )
{
  _->geomobject_position( id, position );
}

void
ViewerUiCmd::
get_geometry(
  motion::GeometryMode &mode,
  motion::GeometryGroup &group,
  uint &dim ) const
{
  _->get_geometry( mode, group, dim );
}

void
ViewerUiCmd::
set_geometry(
  motion::GeometryMode mode,
  motion::GeometryGroup group,
  uint dim )
{
  _->set_geometry( mode, group, dim );
}

void
ViewerUiCmd::
reset_geometry()
{
  _->reset_geometry();
}

void
ViewerUiCmd::
geometry_mousemode( motion::MouseMode x )
{
  _->geometry_mousemode( x );
}

void
ViewerUiCmd::
mouse_reset()
{
  _->mouse_reset();
}

void
ViewerUiCmd::
mouse_inertia_enable( bool x )
{
  _->mouse_inertia_enable( x );
}

void
ViewerUiCmd::
mouse_inertia_decay_enable( bool x )
{
  _->mouse_inertia_decay_enable( x );
}

void
ViewerUiCmd::
mouse_inertia_decay_rate( float x )
{
  _->mouse_inertia_decay_rate( x );
}

void
ViewerUiCmd::
mouse_speed( base::ArrayX<float,2U> const &x )
{
  _->mouse_speed( x );
}

void
ViewerUiCmd::
mouse_viewmode( uint x )
{
  _->mouse_viewmode( x );
}

void
ViewerUiCmd::
select_geomobject( uint id )
{
  _->select_geomobject( id );
}

void
ViewerUiCmd::
show_geomobject( uint id, bool state )
{
  _->show_geomobject( id, state );
}

void
ViewerUiCmd::
move_geomobject( uint id, bool state )
{
  _->move_geomobject( id, state );
}

void
ViewerUiCmd::
delete_geomobject( uint id )
{
  _->delete_geomobject( id );
}

void
ViewerUiCmd::
delete_all_geomobjects()
{
  _->delete_all_geomobjects();
}

bool
ViewerUiCmd::
replace_geomobject() const
{
  return _->replace_geomobject();
}

void
ViewerUiCmd::
replace_geomobject(bool a)
{
  return _->replace_geomobject( a );
}

uint
ViewerUiCmd::
selected_geomobject() const
{
  return _->selected_geomobject();
}

void
ViewerUiCmd::
geomobject_inherit_materials(bool a)
{
  _->geomobject_inherit_materials(a);
}
 
bool
ViewerUiCmd::
geomobject_inherit_materials() const
{
  return _->geomobject_inherit_materials();
}

void
ViewerUiCmd::
position_by_box(uint a)
{
  _->position_by_box(a);
}
 
uint
ViewerUiCmd::
position_by_box() const
{
  return _->position_by_box();
}

void
ViewerUiCmd::
insert_geomobject_notify( base::String const &name )
{
  _->::isightui::ui::GeomObject::insert_geomobject_notify( name );
}

void
ViewerUiCmd::
delete_geomobject_notify( uint id )
{
  _->::isightui::ui::GeomObject::delete_geomobject_notify( id );
}

void
ViewerUiCmd::
new_window()
{
  _->new_window();
}

void
ViewerUiCmd::
select_window( uint id )
{
  _->select_window( id );
}

void
ViewerUiCmd::
show_window( uint id, bool state )
{
  _->show_window( id, state );
}

void
ViewerUiCmd::
delete_window( uint id )
{
  _->delete_window( id );
}

uint
ViewerUiCmd::
selected_window() const
{
  return _->selected_window();
}

bool
ViewerUiCmd::
image_size_use_window() const
{
  return _->image_size_use_window();
}

void
ViewerUiCmd::
image_size_use_window( bool state )
{
  _->image_size_use_window( state );
}

void
ViewerUiCmd::
get_image_size( uint &width, uint &height ) const
{
  _->get_image_size( width, height );
}

void
ViewerUiCmd::
set_image_size( uint width, uint height )
{
  _->set_image_size( width, height );
}

float
ViewerUiCmd::
image_compression() const
{
  return _->image_compression();
}

void
ViewerUiCmd::
image_compression( float a )
{
  return _->image_compression( a );
}

uint
ViewerUiCmd::
write_normals() const
{
  return _->write_normals();
}

void
ViewerUiCmd::
write_normals( uint state )
{
  _->write_normals( state );
}

uint
ViewerUiCmd::
write_colors() const
{
  return _->write_colors();
}

void
ViewerUiCmd::
write_colors( uint state )
{
  _->write_colors( state );
}

bool
ViewerUiCmd::
transparent() const
{
  return _->transparent();
}

void
ViewerUiCmd::
controls( widget::ui::KeyBase &x )
{
  _->controls(x);
}

void
ViewerUiCmd::
controls_file( widget::ui::KeyBase &x )
{
  _->controls_file(x);
}

void
ViewerUiCmd::
controls_win( widget::ui::KeyBase &x )
{
  _->controls_win(x);
}

} // namespace isightui

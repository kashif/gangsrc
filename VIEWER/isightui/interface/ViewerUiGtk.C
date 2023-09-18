/* GANG Software
 * VIEWER/isightui/interface/ViewerUiGtk.C
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

#include "isightui/gtk/Ui.H"
#include "ViewerUiGtk.H"

namespace isightui {

class _ViewerUiGtk
  :
    public isightui::gtk::Ui
{
public:
  _ViewerUiGtk( char const *label, ViewerUiGtk *parent) :
      isightui::gtk::Ui(label), _parent(parent) {}
protected:
  virtual int key_press_event_d( uint key, uint state )
    { return _parent->key_press_event_d( key, state ); }
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
  ViewerUiGtk *_parent;
  friend class ViewerUiGtk;
};

ViewerUiGtk::
ViewerUiGtk( char const *label )
    :
    _(new _ViewerUiGtk(label, this) )
{
}

ViewerUiGtk::
~ViewerUiGtk()
{
  delete _;
}

void
ViewerUiGtk::
read(
  io::Istream &stream,
  geom::FileMode filemode = geom::FILEMODE_DEFAULT )
  throw (io::ReadException)
{
  viewer()->read(stream, filemode);
}

void
ViewerUiGtk::
read(
    base::String const &filename,
    geom::FileMode filemode = geom::FILEMODE_UNSPECIFIED )
    throw (io::ReadException)
{
  viewer()->read(filename, filemode);
}

void
ViewerUiGtk::
read(
    base::vector<base::String> const &filename,
    geom::FileMode filemode = geom::FILEMODE_UNSPECIFIED )
    throw (io::ReadException)
{
  viewer()->read(filename, filemode);
}

void
ViewerUiGtk::
write(
    io::Ostream &stream,
    geom::FileMode filemode = geom::FILEMODE_DEFAULT) const
    throw (io::WriteException)
{
  viewer()->write(stream, filemode);
}

void
ViewerUiGtk::
write(
    base::String const &filename,
    geom::FileMode filemode = geom::FILEMODE_UNSPECIFIED) const
    throw (io::WriteException)
{
  viewer()->write(filename, filemode);
}


void
ViewerUiGtk::
insert_geomobject( geom::Surface const &x )
{
  viewer()->insert_geomobject(x);
}

void
ViewerUiGtk::
insert_geomobject( geom::SurfaceGL const &x )
{
  viewer()->insert_geomobject(x);
}


void
ViewerUiGtk::
background_image( base::String const &filename )
{
  viewer()->context()->background_image(filename);
}


void
ViewerUiGtk::
_hide_all()
{
  _->show_all(false);
}

void
ViewerUiGtk::
_enable_tooltips(bool state)
{
  _->isightui::ui::Ui::enable_tooltips(state);
}

bool
ViewerUiGtk::
_command( base::String const &command, base::String const &argment, base::String &response )
{
  return _->command( command, argment, response );
}

void
ViewerUiGtk::
synchronize()
{
  _->synchronize();
}

void
ViewerUiGtk::
move_all_geomobjects(bool state)
{
  _->move_all_geomobjects(state);
}

void
ViewerUiGtk::
geometry_toggle_raise_show()
{
  static_cast< ::isightui::ui::Geometry *>(_)->toggle_raise_show_d();
}

void
ViewerUiGtk::
mouse_toggle_raise_show()
{
  static_cast< ::isightui::ui::Mouse *>(_)->toggle_raise_show_d();
}

void
ViewerUiGtk::
read_toggle_raise_show()
{
  static_cast< ::isightui::ui::Read *>(_)->toggle_raise_show_d();
}

void
ViewerUiGtk::
geomobject_toggle_raise_show()
{
  static_cast< ::isightui::ui::GeomObject *>(_)->toggle_raise_show_d();
}

void
ViewerUiGtk::
window_toggle_raise_show()
{
  static_cast< ::isightui::ui::Window *>(_)->toggle_raise_show_d();
}

void
ViewerUiGtk::
style_toggle_raise_show()
{
  static_cast< ::isightui::ui::Style *>(_)->toggle_raise_show_d();
}

void
ViewerUiGtk::
windowsize_toggle_raise_show()
{
  static_cast< ::isightui::ui::WindowSize *>(_)->toggle_raise_show_d();
}

void
ViewerUiGtk::
write_toggle_raise_show()
{
  static_cast< ::isightui::ui::Write *>(_)->toggle_raise_show_d();
}

void
ViewerUiGtk::
writeconfig_toggle_raise_show()
{
  static_cast< ::isightui::ui::WriteConfig *>(_)->toggle_raise_show_d();
}

void
ViewerUiGtk::
windowsize_reset()
{
  _->windowsize_reset();
}

void
ViewerUiGtk::
windowsize_set( base::ArrayX<uint,2U> const &x )
{
  _->windowsize_set( x );
}

void
ViewerUiGtk::
windowsize_fullscreen( bool state )
{
  _->windowsize_fullscreen( state );
}

void
ViewerUiGtk::
windowsize_toggle_fullscreen()
{
  _->windowsize_toggle_fullscreen();
}

void
ViewerUiGtk::
windowsize_synchronize_notify()
{
  _->windowsize_synchronize_notify();
}

void
ViewerUiGtk::
style( uint n )
{
  _->style( n );
}

void
ViewerUiGtk::
axes(bool a)
{
  _->axes( a );
}

void
ViewerUiGtk::
toggle_axes()
{
  _->toggle_axes();
}

void
ViewerUiGtk::
sphere(bool a)
{
  _->sphere( a );
}

void
ViewerUiGtk::
toggle_sphere()
{
  _->toggle_sphere();
}

void
ViewerUiGtk::
stars(bool a)
{
  _->stars( a );
}

void
ViewerUiGtk::
toggle_stars()
{
  _->toggle_stars();
}

void
ViewerUiGtk::
style_prev()
{
  _->style_prev();
}

void
ViewerUiGtk::
style_next()
{
  _->style_next();
}

void
ViewerUiGtk::
reset_position()
{
  _->reset_position();
}

void
ViewerUiGtk::
stop_motion()
{
  _->stop_motion();
}

void
ViewerUiGtk::
mouse_rotation()
{
  _->mouse_rotation();
}

void
ViewerUiGtk::
mouse_translation()
{
  _->mouse_translation();
}

void
ViewerUiGtk::
mouse_inversion()
{
  _->mouse_inversion();
}

void
ViewerUiGtk::
mouse_scale()
{
  _->mouse_scale();
}

void
ViewerUiGtk::
geomobject_position( uint id, motion::Transform const &position )
{
  _->geomobject_position( id, position );
}

void
ViewerUiGtk::
get_geometry(
  motion::GeometryMode &mode,
  motion::GeometryGroup &group,
  uint &dim ) const
{
  _->get_geometry( mode, group, dim );
}

void
ViewerUiGtk::
set_geometry(
  motion::GeometryMode mode,
  motion::GeometryGroup group,
  uint dim )
{
  _->set_geometry( mode, group, dim );
}

void
ViewerUiGtk::
reset_geometry()
{
  _->reset_geometry();
}

void
ViewerUiGtk::
geometry_mousemode( motion::MouseMode x )
{
  _->geometry_mousemode( x );
}

void
ViewerUiGtk::
mouse_reset()
{
  _->mouse_reset();
}

void
ViewerUiGtk::
mouse_inertia_enable( bool x )
{
  _->mouse_inertia_enable( x );
}

void
ViewerUiGtk::
mouse_inertia_decay_enable( bool x )
{
  _->mouse_inertia_decay_enable( x );
}

void
ViewerUiGtk::
mouse_inertia_decay_rate( float x )
{
  _->mouse_inertia_decay_rate( x );
}

void
ViewerUiGtk::
mouse_speed( base::ArrayX<float,2U> const &x )
{
  _->mouse_speed( x );
}

void
ViewerUiGtk::
mouse_viewmode( uint x )
{
  _->mouse_viewmode( x );
}

void
ViewerUiGtk::
select_geomobject( uint id )
{
  _->select_geomobject( id );
}

void
ViewerUiGtk::
show_geomobject( uint id, bool state )
{
  _->show_geomobject( id, state );
}

void
ViewerUiGtk::
move_geomobject( uint id, bool state )
{
  _->move_geomobject( id, state );
}

void
ViewerUiGtk::
delete_geomobject( uint id )
{
  _->delete_geomobject( id );
}

void
ViewerUiGtk::
delete_all_geomobjects()
{
  _->delete_all_geomobjects();
}

bool
ViewerUiGtk::
replace_geomobject() const
{
  return _->replace_geomobject();
}

void
ViewerUiGtk::
replace_geomobject(bool a)
{
  return _->replace_geomobject( a );
}

uint
ViewerUiGtk::
selected_geomobject() const
{
  return _->selected_geomobject();
}

void
ViewerUiGtk::
geomobject_inherit_materials(bool a)
{
  _->geomobject_inherit_materials(a);
}
 
bool
ViewerUiGtk::
geomobject_inherit_materials() const
{
  return _->geomobject_inherit_materials();
}

void
ViewerUiGtk::
position_by_box(uint a)
{
  _->position_by_box(a);
}
 
uint
ViewerUiGtk::
position_by_box() const
{
  return _->position_by_box();
}

void
ViewerUiGtk::
insert_geomobject_notify( base::String const &name )
{
  _->::isightui::ui::GeomObject::insert_geomobject_notify( name );
}

void
ViewerUiGtk::
delete_geomobject_notify( uint id )
{
  _->::isightui::ui::GeomObject::delete_geomobject_notify( id );
}

void
ViewerUiGtk::
new_window()
{
  _->new_window();
}

void
ViewerUiGtk::
select_window( uint id )
{
  _->select_window( id );
}

void
ViewerUiGtk::
show_window( uint id, bool state )
{
  _->show_window( id, state );
}

void
ViewerUiGtk::
delete_window( uint id )
{
  _->delete_window( id );
}

uint
ViewerUiGtk::
selected_window() const
{
  return _->selected_window();
}

bool
ViewerUiGtk::
image_size_use_window() const
{
  return _->image_size_use_window();
}

void
ViewerUiGtk::
image_size_use_window( bool state )
{
  _->image_size_use_window( state );
}

void
ViewerUiGtk::
get_image_size( uint &width, uint &height ) const
{
  _->get_image_size( width, height );
}

void
ViewerUiGtk::
set_image_size( uint width, uint height )
{
  _->set_image_size( width, height );
}

float
ViewerUiGtk::
image_compression() const
{
  return _->image_compression();
}

void
ViewerUiGtk::
image_compression( float a )
{
  return _->image_compression( a );
}

uint
ViewerUiGtk::
write_normals() const
{
  return _->write_normals();
}

void
ViewerUiGtk::
write_normals( uint state )
{
  _->write_normals( state );
}

uint
ViewerUiGtk::
write_colors() const
{
  return _->write_colors();
}

void
ViewerUiGtk::
write_colors( uint state )
{
  _->write_colors( state );
}

bool
ViewerUiGtk::
transparent() const
{
  return _->transparent();
}

void
ViewerUiGtk::
controls( widget::ui::KeyBase &x )
{
  _->controls(x);
}

void
ViewerUiGtk::
controls_file( widget::ui::KeyBase &x )
{
  _->controls_file(x);
}

void
ViewerUiGtk::
controls_win( widget::ui::KeyBase &x )
{
  _->controls_win(x);
}

} // namespace isightui

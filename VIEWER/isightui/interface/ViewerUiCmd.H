/* GANG Software
 * VIEWER/isightui/interface/ViewerUiCmd.H
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

#ifndef isightui_ViewerUiCmd_INCLUDED
#define isightui_ViewerUiCmd_INCLUDED

#include "ViewerUi.H"

namespace isightui {

class _ViewerUiCmd;

class ViewerUiCmd
  :
    virtual public ViewerUi
{

public:
  // constructor
  ViewerUiCmd();

  // destructor
  virtual ~ViewerUiCmd();

  virtual void read(
    io::Istream &stream,
    geom::FileMode filemode = geom::FILEMODE_DEFAULT )
    throw (io::ReadException);
  virtual void read(
    base::String const &filename,
    geom::FileMode filemode = geom::FILEMODE_UNSPECIFIED )
    throw (io::ReadException);
  virtual void read(
    base::vector<base::String> const &filename,
    geom::FileMode filemode = geom::FILEMODE_UNSPECIFIED )
    throw (io::ReadException);
  virtual void write(
    io::Ostream &stream,
    geom::FileMode filemode = geom::FILEMODE_DEFAULT) const
    throw (io::WriteException);
  virtual void write(
    base::String const &filename,
    geom::FileMode filemode = geom::FILEMODE_UNSPECIFIED) const
    throw (io::WriteException);

  virtual void insert_geomobject( geom::Surface const & );
  virtual void insert_geomobject( geom::SurfaceGL const & );

  virtual void background_image( base::String const &filename );

  virtual void _hide_all();
  virtual void _enable_tooltips(bool state);

  virtual bool _command(
    base::String const &command, base::String const &argment,
    base::String &response );

  virtual int key_press_event_d( uint key, uint state ) = 0;

  virtual void move_all_geomobjects(bool state);

  virtual void geometry_toggle_raise_show();
  virtual void mouse_toggle_raise_show();
  virtual void read_toggle_raise_show();
  virtual void geomobject_toggle_raise_show();
  virtual void window_toggle_raise_show();
  virtual void style_toggle_raise_show();
  virtual void windowsize_toggle_raise_show();
  virtual void write_toggle_raise_show();
  virtual void writeconfig_toggle_raise_show();

  // windowsize
  virtual void windowsize_reset();
  virtual void windowsize_set( base::ArrayX<uint,2U> const &x );
  virtual void windowsize_fullscreen( bool state );
  virtual void windowsize_toggle_fullscreen();
  virtual void windowsize_synchronize_notify();

  // style
  virtual void style( uint n );
  virtual void axes(bool a);
  virtual void toggle_axes();
  virtual void sphere(bool a);
  virtual void toggle_sphere();
  virtual void stars(bool a);
  virtual void toggle_stars();
  virtual void style_prev();
  virtual void style_next();


  virtual void reset_position();
  virtual void stop_motion();
  virtual void mouse_rotation();
  virtual void mouse_translation();
  virtual void mouse_inversion();
  virtual void mouse_scale();
  virtual void geomobject_position(
    uint id, motion::Transform const &position );

  // geometry
  virtual void get_geometry( motion::GeometryMode &mode,
                             motion::GeometryGroup &group,
                             uint &dim ) const;
  virtual void set_geometry( motion::GeometryMode mode,
                             motion::GeometryGroup group,
                             uint dim );
  virtual void reset_geometry();
  virtual void geometry_mousemode( motion::MouseMode );

  // mouse
  virtual void mouse_reset();
  virtual void mouse_inertia_enable( bool x );
  virtual void mouse_inertia_decay_enable( bool x );
  virtual void mouse_inertia_decay_rate( float x );
  virtual void mouse_speed( base::ArrayX<float,2U> const &x );
  virtual void mouse_viewmode( uint x );

  // geomobject select operations
  virtual void select_geomobject( uint id );
  virtual void show_geomobject( uint id, bool state );
  virtual void move_geomobject( uint id, bool state );
  virtual void delete_geomobject( uint id );
  virtual void delete_all_geomobjects();
  virtual bool replace_geomobject() const;
  virtual void replace_geomobject(bool);
  virtual uint selected_geomobject() const;
  virtual void geomobject_inherit_materials(bool);
  virtual bool geomobject_inherit_materials() const;
  virtual void position_by_box(uint);
  virtual uint position_by_box() const;
  virtual void insert_geomobject_notify( base::String const &name );
  virtual void delete_geomobject_notify( uint id );

  // window select operations
  virtual void new_window();
  virtual void select_window( uint id );
  virtual void show_window( uint id, bool state );
  virtual void delete_window( uint id );
  virtual uint selected_window() const;

  // write config
  virtual bool image_size_use_window() const;
  virtual void image_size_use_window( bool state );
  virtual void get_image_size( uint &width, uint &height ) const;
  virtual void set_image_size( uint width, uint height );
  virtual float image_compression() const;
  virtual void image_compression( float a );
  virtual uint write_normals() const;
  virtual void write_normals( uint state );
  virtual uint write_colors() const;
  virtual void write_colors( uint state );
  virtual bool transparent() const;

  // synchronize the widgets with the current Surface
  virtual void synchronize();

protected:

  virtual void controls( widget::ui::KeyBase &);
  virtual void controls_file( widget::ui::KeyBase &);
  virtual void controls_win( widget::ui::KeyBase &);

private:
#if 0
  virtual ::geomui::GeomUi *geom_ui() = 0;
  virtual ::geomui::GeomUi const *geom_ui() const = 0;
  virtual ::milieuui::MilieuUi *milieu_ui() = 0;
  virtual ::milieuui::MilieuUi const *milieu_ui() const = 0;
  virtual isight::kernel::ViewerBase *viewer() = 0;
  virtual isight::kernel::ViewerBase const *viewer() const = 0;
  virtual geom::Surface const *surface() const = 0;
  virtual geom::Surface *surface() = 0;
#endif

  _ViewerUiCmd *_;

  // disabled copy constructor
  ViewerUiCmd( ViewerUiCmd const & );
  // disabled assignment operator
  ViewerUiCmd &operator=( ViewerUiCmd const & );

  friend class _ViewerUiCmd;
};

} // namespace isightui

#endif // isightui_ViewerUiCmd_INCLUDED

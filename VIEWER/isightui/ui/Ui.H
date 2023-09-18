/* GANG Software
 * VIEWER/isightui/ui/Ui.H
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

#ifndef isightui_ui_Ui_INCLUDED
#define isightui_ui_Ui_INCLUDED

#include "widget/ui/KeyBase.H"
#include "Geometry.H"
#include "Mouse.H"
#include "WindowSize.H"
#include "Read.H"
#include "Write.H"
#include "GeomObject.H"
#include "Window.H"
#include "Style.H"
#include "WriteConfig.H"

namespace isightui { namespace kernel { class ViewerBase; } }

namespace isightui {
namespace ui {

class Ui
  :
  virtual protected Geometry,
  virtual protected Mouse,
  virtual protected WindowSize,
  virtual protected Read,
  virtual protected Write,
  virtual protected GeomObject,
  virtual protected Window,
  virtual protected Style,
  virtual protected WriteConfig
{

public:
  // constructor
  Ui();

  // destructor
  virtual ~Ui();

  virtual ::isight::kernel::ViewerBase *viewer() = 0;
  virtual ::isight::kernel::ViewerBase const *viewer() const = 0;

  void reset();

  virtual void show_all(bool state);
  virtual void enable_tooltips( bool state );
  virtual void synchronize();

  bool command(
    base::String const &command,
    base::String const &argument,
    base::String &response );

  virtual int key_press_event( uint key, uint state )
    { WARN(); return 0; }

  void controls( ::widget::ui::KeyBase &p );
  void controls_file( ::widget::ui::KeyBase &p );
  void controls_win( ::widget::ui::KeyBase &p );

protected:

private:

  void read_toggle_raise_show()
    { _read()->toggle_raise_show_d(); }
  void write_toggle_raise_show()
    { _write()->toggle_raise_show_d(); }
  void windowsize_toggle_raise_show()
    { _windowsize()->toggle_raise_show_d(); }
  void mouse_toggle_raise_show()
    { _mouse()->toggle_raise_show_d(); }
  void geometry_toggle_raise_show()
    { _geometry()->toggle_raise_show_d(); }
  void geomobject_toggle_raise_show()
    { _geomobject()->toggle_raise_show_d(); }
  void window_toggle_raise_show()
    { _window()->toggle_raise_show_d(); }
  void writeconfig_toggle_raise_show()
    { _writeconfig()->toggle_raise_show_d(); }
  void style_toggle_raise_show()
    { _style()->toggle_raise_show_d(); }

#if 0
  virtual motion::GeometryMode geometry_mode() const
    { return context()->geometry_mode(); }
  virtual motion::GeometryGroup geometry_group() const
    { return context()->geometry_group(); }
  virtual uint geometry_dim() const
    { return context()->geometry_dim(); }
  virtual motion::MouseMode mouse_mode() const
    { return context()->mouse_mode(); }
  virtual void mouse_mode( motion::MouseMode x )
    { context()->mouse_mode(x); }
  virtual bool standard_geometry() const
    { return context()->standard_geometry(); }
  virtual void geomobject_reset_position()
    { context()->geomobject_reset_position(); }

  virtual bool inertia() const
    { return context()->inertia(); }
  virtual bool inertia_decay() const
    { return context()->inertia_decay(); }
  virtual float inertia_decay_rate() const
    { return context()->inertia_decay_rate(); }
  virtual void inertia( bool a )
    { context()->inertia(a); }
  virtual void inertia_decay( bool a )
    { context()->inertia_decay(a); }
  virtual void inertia_decay_rate( float a )
    { context()->inertia_decay_rate(a); }
  virtual float speed() const
    { return context()->speed(); }
  virtual float acceleration() const
    { return context()->acceleration(); }
  virtual int view_mode() const
    { return context()->view_mode(); }
  virtual void speed( float s, float a )
    { context()->speed(s, a); }
  virtual void view_mode( int model )
    { context()->view_mode(model); }

  virtual void save_window_size_and_position()
    { context()->save_window_size_and_position(); }
  virtual void restore_window_size_and_position()
    { context()->restore_window_size_and_position(); }
  virtual uint width()
    { return context()->width(); }
  virtual uint height()
    { return context()->height(); }
  virtual void resize( uint x, uint y )
    { context()->resize(x, y); }
  virtual void reposition( uint x, uint y )
    { context()->reposition(x, y); }
  virtual void raise()
    { context()->raise(); }
  virtual bool showing()
    { return context()->showing(); }
#endif

  Geometry *_geometry() { return this; }
  Mouse *_mouse() { return this; }
  WindowSize *_windowsize() { return this; }
  Read *_read() { return this; }
  Write *_write() { return this; }
  GeomObject *_geomobject() { return this; }
  GeomObject const *_geomobject() const { return this; }
  Window *_window() { return this; }
  Window const *_window() const { return this; }
  Style *_style() { return this; }
  WriteConfig *_writeconfig() { return this; }

  // disabled copy constructor
  Ui( Ui const & );

  // disabled assignment operator
  Ui &operator=( Ui const & );

};

} // namespace ui
} // namespace isightui

#endif // isightui_ui_Ui_INCLUDED

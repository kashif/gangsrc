/* GANG Software
 * VIEWER/isight/gtk/ContextGtk.H
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

#ifndef isight_gtk_ContextGtk_INCLUDED
#define isight_gtk_ContextGtk_INCLUDED

#include "gtk/widget1/GLWindow.H"
#include "gtk/widget1/Idler.H"
#include "isight/context/Context.H"

namespace isight {
namespace gtk {

class ContextGtk
  :
    protected ::gtk::widget1::GLWindow,
    public ::isight::context::Context
{

public:
  // constructor
  ContextGtk( isight::context::ContextSetBase *base );

  // destructor
  virtual ~ContextGtk();

  virtual uint area_width() const
    { return ::gtk::widget1::GLWindow::area_width(); }
  virtual uint area_height() const
    { return ::gtk::widget1::GLWindow::area_height(); }
  virtual void make_current()
    { ::gtk::widget1::GLWindow::make_current(); }
  virtual void refresh()
    { ::gtk::widget1::GLWindow::refresh(); }
  virtual void enable_draw(bool a)
    { ::gtk::widget1::GLWindow::enable_draw(a); }

  virtual void set_title( char const *a )
    { ::gtk::widget1::GLWindow::set_title(a); }
  virtual uint width() const
    { return ::gtk::widget1::GLWindow::width(); }
  virtual uint height() const
    { return ::gtk::widget1::GLWindow::height(); }
  virtual uint x_position() const
    { return ::gtk::widget1::GLWindow::x_position(); }
  virtual uint y_position() const
    { return ::gtk::widget1::GLWindow::y_position(); }
  virtual void resize( uint width, uint height )
    { ::gtk::widget1::GLWindow::resize(width, height); }
  virtual void reposition( uint x, uint y )
    { ::gtk::widget1::GLWindow::reposition(x, y); }
  virtual void raise( bool state = true )
    { ::gtk::widget1::GLWindow::raise(state); }
  virtual void raise_show( bool state = true )
    { ::gtk::widget1::GLWindow::raise_show(state); }
  virtual void toggle_raise_show()
    { ::gtk::widget1::GLWindow::toggle_raise_show(); }

  virtual void show( bool state = true )
    { ::gtk::widget1::GLWindow::show(state); }
  virtual bool showing() const
    { return ::gtk::widget1::GLWindow::showing(); }
  virtual void set_sensitive( bool state = true )
    { ::gtk::widget1::GLWindow::set_sensitive(state); }

  virtual void draw()
    { ::isight::context::Context::draw(); }

  virtual void swap_buffers()
    { ::gtk::widget1::GLWindow::swap_buffers(); }

protected:

private:
  virtual int key_press_event_d( uint key, uint state )
    { DIE(); return 0; }


  // Called by gtk when the user presses a mouse button.
  virtual int button_press_event_cb( GdkEventButton * );

  // Called by gtk when the user presses a mouse button.
  virtual int button_release_event_cb( GdkEventButton * );

  // Called by gtk when user moves or drags the mouse over the window
  virtual int motion_notify_event_cb( GdkEventMotion * );

  // Called by gtk when a keyboard key is pressed (and the window has focus)
  virtual int key_press_event_cb( GdkEventKey *event );

  // Called by gtk when a keyboard key is released
  virtual int key_release_event_cb( GdkEventKey * )
    { return 0; }

  virtual int focus_in_event_cb( GdkEventFocus * )
    { return focus_in_event(this); }
  virtual int focus_out_event_cb( GdkEventFocus * )
    { return 0; }

  virtual int configure_event_cb( GdkEventConfigure *event );

  virtual widget::ui::Idler *idler()
    { return &_idler; }

  mutable ::gtk::widget1::GtkIdler< ::isight::context::Context> _idler;

  // disabled copy constructor
  ContextGtk( ContextGtk const & );
  // disabled assignment operator
  ContextGtk &operator=( ContextGtk const & );

};

} // namespace gtk
} // namespace isight

#endif // isight_gtk_ContextGtk_INCLUDED

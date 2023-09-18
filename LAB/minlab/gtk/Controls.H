/* GANG Software
 * LAB/minlab/gtk/Controls.H
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

#ifndef minlab_gtk_Controls_INCLUDED
#define minlab_gtk_Controls_INCLUDED

#include "app/app/Dialog.H"
#include "minlab/ui/Controls.H"
#include "Controls_.H"

namespace minlab {
namespace gtk {

class Controls
  :
    virtual public ui::Controls,
    protected Controls_,
    public ::app::app::Dialog
{

public:
  // constructor
  Controls(char const *title);

  // destructor
  virtual ~Controls();

protected:

private:

  // connector functions
  virtual void raise_d( bool state = true )
    { ::app::app::Dialog::raise(state); }
  virtual void show_d( bool state = true )
    { ::app::app::Dialog::show(state); }
  virtual void toggle_raise_show_d()
    { ::app::app::Dialog::toggle_raise_show(); }
  virtual void enable_tooltips_d( bool state = true )
    { Controls_::enable_tooltips(state); }
  virtual int key_press_event( uint key, uint state )
    { return key_press_event_d( key, state ); }

  // widgets
  virtual widget::ui::Choice *main_widget_w()
    { return _main_widget_w; }
  virtual widget::ui::Choice *notebook_surf_data_w()
    { return _notebook_surf_data_w; }
  virtual widget::ui::String *zstart_spinor_w()
    { return _zstart_spinor_w; }
  virtual widget::ui::String *spinor1_w()
    { return _spinor1_w; }
  virtual widget::ui::String *spinor2_w()
    { return _spinor2_w; }
  virtual widget::ui::String *spinor0_init_w()
    { return _spinor0_init_w; }
  virtual widget::ui::String *spinor1_init_w()
    { return _spinor1_init_w; }
  virtual widget::ui::String *spinor2_init_w()
    { return _spinor2_init_w; }
  virtual widget::ui::String *zstart_weierstrass_w()
    { return _zstart_weierstrass_w; }
  virtual widget::ui::String *weierstrass1_w()
    { return _weierstrass1_w; }
  virtual widget::ui::String *weierstrass2_w()
    { return _weierstrass2_w; }
  virtual widget::ui::String *weierstrass0_init_w()
    { return _weierstrass0_init_w; }
  virtual widget::ui::String *weierstrass1_init_w()
    { return _weierstrass1_init_w; }
  virtual widget::ui::String *weierstrass2_init_w()
    { return _weierstrass2_init_w; }
  virtual widget::ui::Widget *parameter_reset_w()
    { return _parameter_reset_w; }
  virtual widget::ui::Float *associate_slider_w()
    { return _associate_slider_w; }
  virtual widget::ui::Widget *associate_button0_w()
    { return _associate_button0_w; }
  virtual widget::ui::Widget *associate_button1_w()
    { return _associate_button1_w; }
  virtual widget::ui::Widget *associate_button2_w()
    { return _associate_button2_w; }
  virtual widget::ui::Widget *associate_button3_w()
    { return _associate_button3_w; }
  virtual widget::ui::Float *integrator_count_w()
    { return _integrator_count_w; }
  virtual widget::ui::Float *initial_integrator_count_w()
    { return _initial_integrator_count_w; }
  virtual widget::ui::Choice const *main_widget_w() const
    { return _main_widget_w; }
  virtual widget::ui::Choice const *notebook_surf_data_w() const
    { return _notebook_surf_data_w; }
  virtual widget::ui::String const *zstart_spinor_w() const
    { return _zstart_spinor_w; }
  virtual widget::ui::String const *spinor1_w() const
    { return _spinor1_w; }
  virtual widget::ui::String const *spinor2_w() const
    { return _spinor2_w; }
  virtual widget::ui::String const *spinor0_init_w() const
    { return _spinor0_init_w; }
  virtual widget::ui::String const *spinor1_init_w() const
    { return _spinor1_init_w; }
  virtual widget::ui::String const *spinor2_init_w() const
    { return _spinor2_init_w; }
  virtual widget::ui::String const *zstart_weierstrass_w() const
    { return _zstart_weierstrass_w; }
  virtual widget::ui::String const *weierstrass1_w() const
    { return _weierstrass1_w; }
  virtual widget::ui::String const *weierstrass2_w() const
    { return _weierstrass2_w; }
  virtual widget::ui::String const *weierstrass0_init_w() const
    { return _weierstrass0_init_w; }
  virtual widget::ui::String const *weierstrass1_init_w() const
    { return _weierstrass1_init_w; }
  virtual widget::ui::String const *weierstrass2_init_w() const
    { return _weierstrass2_init_w; }
  virtual widget::ui::Widget const *parameter_reset_w() const
    { return _parameter_reset_w; }
  virtual widget::ui::Float const *associate_slider_w() const
    { return _associate_slider_w; }
  virtual widget::ui::Widget const *associate_button0_w() const
    { return _associate_button0_w; }
  virtual widget::ui::Widget const *associate_button1_w() const
    { return _associate_button1_w; }
  virtual widget::ui::Widget const *associate_button2_w() const
    { return _associate_button2_w; }
  virtual widget::ui::Widget const *associate_button3_w() const
    { return _associate_button3_w; }
  virtual widget::ui::Float const *integrator_count_w() const
    { return _integrator_count_w; }
  virtual widget::ui::Float const *initial_integrator_count_w() const
    { return _initial_integrator_count_w; }

  // callbacks
  virtual void parameter_reset_cb()
    { ui::Controls::parameter_reset_cb(); }
  virtual void associate_slider_cb()
    { ui::Controls::associate_slider_cb(); }
  virtual void associate_button0_cb()
    { ui::Controls::associate_button0_cb(); }
  virtual void associate_button1_cb()
    { ui::Controls::associate_button1_cb(); }
  virtual void associate_button2_cb()
    { ui::Controls::associate_button2_cb(); }
  virtual void associate_button3_cb()
    { ui::Controls::associate_button3_cb(); }

  // disabled copy constructor
  Controls( Controls const & );

  // disabled assignment operator
  Controls &operator=( Controls const & );

};

} // namespace gtk
} // namespace minlab

#endif // minlab_gtk_Controls_INCLUDED

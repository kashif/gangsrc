/* GANG Software
 * GEOM/milieu/gtk/GlobalLight_.H
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
// Generated by glade++

#ifndef milieu_gtk_GlobalLight__INCLUDED
#define milieu_gtk_GlobalLight__INCLUDED

#include "gtk/widget0/Tooltips.H"
#include "gtk/widget0/ButtonCb.H"
#include "gtk/widget1/ColorCb.H"
#include "gtk/widget0/Frame.H"
#include "gtk/widget1/MenuButtonCb.H"
#include "gtk/widget0/Table.H"
#include "gtk/widget0/ToggleButtonCb.H"

namespace milieu {
namespace gtk {


class GlobalLight_
{

public:

  GlobalLight_();
  virtual ~GlobalLight_();

  void enable_tooltips( bool state )
    { _tooltips->enable(state); }

protected:

  ::gtk::widget0::Widget *main_widget() { return _main_widget_w; }

  // widgets
  ::gtk::widget0::Frame *_main_widget_w;
  ::gtk::widget0::Table *_table45_w;
  ::gtk::widget0::Table *_table72_w;
  ::gtk::widget0::ButtonCb<GlobalLight_> *_reset_w;
  ::gtk::widget0::ToggleButtonCb<GlobalLight_> *_enable_w;
  ::gtk::widget1::ColorCb<GlobalLight_> *_ambient_w;
  ::gtk::widget0::Frame *_frame3_w;
  ::gtk::widget1::MenuButtonCb<GlobalLight_> *_sidedness_w;
  ::gtk::widget0::Frame *_frame2_w;
  ::gtk::widget1::MenuButtonCb<GlobalLight_> *_viewpoint_w;

  // callbacks
  virtual void reset_cb() = 0;
  virtual void enable_cb() = 0;
  virtual void ambient_cb() = 0;
  virtual void sidedness_cb() = 0;
  virtual void viewpoint_cb() = 0;

private:

  void set_tooltip( ::gtk::widget0::Widget *w, char const *text )
    { _tooltips->set_tip( w, text, 0 ); }

  ::gtk::widget0::Tooltips *_tooltips;

  // disabled copy constructor
  GlobalLight_( GlobalLight_ const & );
  // disabled assignment operator
  GlobalLight_ &operator=( GlobalLight_ const & );

};

} // namespace gtk
} // namespace milieu


#endif // milieu_gtk_GlobalLight__INCLUDED

/* GANG Software
 * VIEWER/isightui/gtk/WriteConfig_.H
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

#ifndef isightui_gtk_WriteConfig__INCLUDED
#define isightui_gtk_WriteConfig__INCLUDED

#include "gtk/widget0/Tooltips.H"
#include "gtk/widget0/ButtonCb.H"
#include "gtk/widget0/Frame.H"
#include "gtk/widget0/Label.H"
#include "gtk/widget1/MenuButton.H"
#include "gtk/widget1/NumberWidget2Int.H"
#include "gtk/widget1/NumberWidgetFloat.H"
#include "gtk/widget1/PopNotebook.H"
#include "gtk/widget0/ToggleButton.H"
#include "gtk/widget0/ToggleButtonCb.H"
#include "gtk/widget0/VBox.H"

namespace isightui {
namespace gtk {


class WriteConfig_
{

public:

  WriteConfig_();
  virtual ~WriteConfig_();

  void enable_tooltips( bool state )
    { _tooltips->enable(state); }

protected:

  ::gtk::widget0::Widget *main_widget() { return _main_widget_w; }

  // widgets
  ::gtk::widget1::PopNotebook *_main_widget_w;
  ::gtk::widget0::VBox *_vbox3_w;
  ::gtk::widget0::ButtonCb<WriteConfig_> *_reset_geometry_w;
  ::gtk::widget0::Frame *_frame4_w;
  ::gtk::widget1::MenuButton *_write_colors_w;
  ::gtk::widget0::Frame *_frame5_w;
  ::gtk::widget1::MenuButton *_write_normals_w;
  ::gtk::widget0::ToggleButton *_transparent_w;
  ::gtk::widget0::Label *_label3_w;
  ::gtk::widget0::VBox *_vbox1_w;
  ::gtk::widget0::ButtonCb<WriteConfig_> *_reset_image_w;
  ::gtk::widget0::Frame *_frame3_w;
  ::gtk::widget0::VBox *_vbox2_w;
  ::gtk::widget0::ToggleButtonCb<WriteConfig_> *_size_use_window_w;
  ::gtk::widget1::NumberWidget2Int *_size_w;
  ::gtk::widget0::Frame *_frame1_w;
  ::gtk::widget1::NumberWidgetFloat *_compression_w;
  ::gtk::widget0::Label *_label2_w;

  // callbacks
  virtual void reset_geometry_cb() = 0;
  virtual void reset_image_cb() = 0;
  virtual void size_use_window_cb() = 0;

private:

  void set_tooltip( ::gtk::widget0::Widget *w, char const *text )
    { _tooltips->set_tip( w, text, 0 ); }

  ::gtk::widget0::Tooltips *_tooltips;

  // disabled copy constructor
  WriteConfig_( WriteConfig_ const & );
  // disabled assignment operator
  WriteConfig_ &operator=( WriteConfig_ const & );

};

} // namespace gtk
} // namespace isightui


#endif // isightui_gtk_WriteConfig__INCLUDED

/* GANG Software
 * WIDGET/gtk/widget1/FileSelection.H
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
// created by gtk2c++

#ifndef gtk_widget1_FileSelection_INCLUDED
#define gtk_widget1_FileSelection_INCLUDED

#include "gtk/widgetc/gtk_filesel2.h"
#include "gtk/widget0/VBox.H"

namespace gtk {
namespace widget1 {

class FileSelection
  :
    public gtk::widget0::VBox
{
public:
  FileSelection();
  virtual ~FileSelection() {}

#if 0
  void show(bool = true);
#endif
  void set(char const *filename)
    { gtk_file_selection2_set_filename( GTK_FILE_SELECTION2(w()), filename ); }
  char const *get() const
    { return gtk_file_selection2_get_filename( GTK_FILE_SELECTION2(w()) ); }

  void set_filename( char const *filename )
    { gtk_file_selection2_set_filename( GTK_FILE_SELECTION2(w()), filename ); }
  char* get_filename()
    { return gtk_file_selection2_get_filename( GTK_FILE_SELECTION2(w())); }
  void complete( char const *pattern )
    { gtk_file_selection2_complete( GTK_FILE_SELECTION2(w()), pattern ); }
  void show_fileop_buttons()
    { gtk_file_selection2_show_fileop_buttons( GTK_FILE_SELECTION2(w())); }
  void hide_fileop_buttons()
    { gtk_file_selection2_hide_fileop_buttons( GTK_FILE_SELECTION2(w())); }

  uint button() const
    { return _button; } // cancel=0, ok=1

protected:

private:
  virtual void callback() = 0;
  void ok_cb();
  void cancel_cb();

  static void ok_cb_(GtkWidget *, gpointer p)
    { static_cast<FileSelection *>(p)->ok_cb(); }
  static void cancel_cb_(GtkWidget *, gpointer p)
    { static_cast<FileSelection *>(p)->cancel_cb(); }

  FileSelection( GtkWidget *x ) : ::gtk::widget0::VBox(x) {}
private:

  uint _button;

};

} // namespace widget1
} // namespace gtk

#endif // gtk_widget1_FileSelection_INCLUDED

/* GANG Software
 * WIDGET/gtk/widget1/FileRead.C
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

#include <unistd.h>
#include "base/Regex.H"
#include "FileRead.H"

namespace gtk {
namespace widget1 {

FileRead::
FileRead()
    :
    FileSelection(),
    _current_dir(),
    _library_dir()
{
  GtkFileSelection2 *x = GTK_FILE_SELECTION2( w() );

  // put a library button on the file selector

  // hbox for buttons
  GtkHBox *hbox = GTK_HBOX( gtk_hbox_new( false, 0 ) );
  gtk_box_pack_end(GTK_BOX(x->main_vbox), GTK_WIDGET(hbox), false, false, 0);
  gtk_widget_show(GTK_WIDGET(hbox));

  // library button
  GtkButton *button1 = GTK_BUTTON(gtk_button_new_with_label("Library"));
  gtk_widget_show(GTK_WIDGET(button1));
  gtk_signal_connect( GTK_OBJECT(button1), "clicked",
                      GTK_SIGNAL_FUNC(library_dir_cb_),
                        (void *)this);
  gtk_box_pack_end(GTK_BOX(hbox), GTK_WIDGET(button1), false, false, 0);

  // current dir button
  GtkButton *button2 = GTK_BUTTON(gtk_button_new_with_label("Current"));
  gtk_widget_show(GTK_WIDGET(button2));
  gtk_signal_connect( GTK_OBJECT(button2), "clicked",
                      GTK_SIGNAL_FUNC(current_dir_cb_),
                        (void *)this);
  gtk_box_pack_end(GTK_BOX(hbox), GTK_WIDGET(button2), false, false, 0);

  // current directory
#ifdef __linux__
  char *cwd = getcwd( (char *)0, (size_t)0 );
#else
  char *cwd = getcwd( (char *)0, (size_t)(-1) );
#endif
  if ( cwd != (char *)0 )
  {
    // NOTE: check for "/"
    _current_dir = cwd;
    _current_dir += "/";
    free(cwd);
  }

  //  set(_current_dir);
}

void
FileRead::
set_lib_env_path(
  char const *env_path )
{
  if ( env_path == (char *)0) { return; }

  // library directory
  char const *p = getenv( env_path );
  if (p == (char *)0)
  {
    _library_dir = ".";
  }
  else
  {
    _library_dir = p;
  }

  // add '/' if missing
  if ( ! base::match( "/$", _library_dir ) )
  {
    _library_dir += "/";
  }

  FileSelection::set(_library_dir.c_str());
}

} // namespace widget1
} // namespace gtk

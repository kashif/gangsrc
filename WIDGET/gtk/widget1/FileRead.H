/* GANG Software
 * WIDGET/gtk/widget1/FileRead.H
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

#ifndef gtk_widget1_FileRead_INCLUDED
#define gtk_widget1_FileRead_INCLUDED

#include "widget/ui/ReadFile.H"
#include "base/String.H"
#include "FileSelection.H"

namespace gtk {
namespace widget1 {

class FileRead
  :
    public widget::ui::ReadFile,
    public FileSelection
{
public:
  FileRead();

  void set_lib_env_path( char const *env_path );

  virtual void set( char const *a )
    { FileSelection::set(a); }
  virtual char const *get() const
    { return FileSelection::get(); }
  virtual uint button() const
    { return FileSelection::button(); }

private:

  void current_dir_cb()
    { FileSelection::set(_current_dir.c_str()); }
  void library_dir_cb()
    { FileSelection::set(_library_dir.c_str()); }
  static void current_dir_cb_(GtkWidget *, gpointer p)
    { static_cast<FileRead *>(p)->current_dir_cb(); }
  static void library_dir_cb_(GtkWidget *, gpointer p)
    { static_cast<FileRead *>(p)->library_dir_cb(); }
  base::String _current_dir;
  base::String _library_dir;

};

} // namespace widget1
} // namespace gtk

#endif // gtk_widget1_FileRead_INCLUDED

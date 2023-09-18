/* GANG Software
 * LAB/lab/ui/Read.H
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

#ifndef lab_ui_Read_INCLUDED
#define lab_ui_Read_INCLUDED

#include "io/Istream.H"
#include "parser/KeyParser.H"
#include "widget/ui/Dialog.H"
#include "widget/ui/ReadFile.H"

namespace lab {
namespace ui {

class Read
  :
    public widget::ui::Dialog
{

public:
  // constructor
  Read() {}

  // destructor
  virtual ~Read() {}

  virtual void read_labfile( base::String const &filename )
    { _read(filename); }
  virtual void read_labfile( io::Istream &stream )
    { _read(stream); }

  bool command(
    base::String const &command,
    base::String const &argument,
    base::String &response );

  void set_lab_lib_env_path( char const *lib_env_path )
    { read_w()->set_lib_env_path( lib_env_path ); }

protected:

  // callbacks
  virtual void read_cb();

  char const *label()
    { return "Open Lab File"; }

  void set( parser::KeyParser const & ) {}
  void get( parser::KeyParser & ) const {}

private:

  virtual void _read( base::String const &filename ) = 0;
  virtual void _read( io::Istream &stream ) = 0;

  // widgets
  virtual widget::ui::ReadFile *read_w() = 0;

  void read_( char const *filename );

  // disabled copy constructor
  Read( Read const & );
  // disabled assignment operator
  Read &operator=( Read const & );

};

} // namespace ui
} // namespace lab

#endif // lab_ui_Read_INCLUDED

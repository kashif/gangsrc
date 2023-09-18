/* GANG Software
 * LAB/lab/ui/Write.H
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

#ifndef lab_ui_Write_INCLUDED
#define lab_ui_Write_INCLUDED

#include "io/Ostream.H"
#include "parser/KeyParser.H"
#include "widget/ui/Dialog.H"
#include "widget/ui/File.H"

namespace lab {
namespace ui {

class Write
  :
    public widget::ui::Dialog
{

public:
  // constructor
  Write();

  // destructor
  virtual ~Write();

  virtual void write_labfile( base::String const &filename )
    { _write(filename); }
  virtual void write_labfile( io::Ostream &stream )
    { _write(stream); }

  bool command(
    base::String const &command,
    base::String const &argument,
    base::String &response );

protected:

  // callbacks
  virtual void write_cb();

  char const *label()
    { return "Save Lab File"; }

  void set( parser::KeyParser const & ) {}
  void get( parser::KeyParser & ) const {}

private:

  virtual void _write( base::String const &filename ) = 0;
  virtual void _write( io::Ostream &stream ) = 0;

  // widgets
  virtual widget::ui::File *write_w() = 0;

  void write_( char const *filename );

  // disabled copy constructor
  Write( Write const & );
  // disabled assignment operator
  Write &operator=( Write const & );

};

} // namespace ui
} // namespace lab

#endif // lab_ui_Write_INCLUDED

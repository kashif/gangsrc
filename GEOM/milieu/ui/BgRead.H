/* GANG Software
 * GEOM/milieu/ui/BgRead.H
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

#ifndef milieu_ui_BgRead_INCLUDED
#define milieu_ui_BgRead_INCLUDED

#include "base/String.H"
#include "widget/ui/Dialog.H"
#include "widget/ui/File.H"
#include "milieu/opengl/Background.H"

namespace milieu {
namespace ui {

class BgRead
  :
    public widget::ui::Dialog
{

public:
  // constructor
  BgRead() {}

  // destructor
  virtual ~BgRead() {}

  bool command(
    base::String const &command,
    base::String const &argument,
    base::String &response );

protected:

  // callbacks
  virtual void read_cb();

  char const *label() const
    { return "Save iSight File"; }

private:

  // pure virtuals
  // pure virtuals
  virtual ::milieu::opengl::Background *background() = 0;
  virtual ::milieu::opengl::Background const *background() const = 0;

  // widgets
  virtual widget::ui::File *read_w() = 0;

  void _read( char const *filename );

  // disabled copy constructor
  BgRead( BgRead const & );
  // disabled assignment operator
  BgRead &operator=( BgRead const & );

};

} // namespace ui
} // namespace milieu

#endif // milieu_ui_BgRead_INCLUDED

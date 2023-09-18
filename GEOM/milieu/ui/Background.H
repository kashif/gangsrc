/* GANG Software
 * GEOM/milieu/ui/Background.H
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

#ifndef milieu_ui_Background_INCLUDED
#define milieu_ui_Background_INCLUDED

#include "base/String.H"
#include "base/Color3.H"
#include "base/ReadUtil.H"
#include "widget/ui/Dialog.H"
#include "widget/ui/FloatSet.H"

namespace milieu {

namespace opengl { class Background; }

namespace ui {

class Background
  :
    public widget::ui::Dialog,
    public base::ReadUtil
{

public:

  // constructor
  Background();

  // destructor
  virtual ~Background();

  // interface
  virtual void background_reset();
  virtual void background_color( base::Color3 const & );
  virtual void background_color( uint i )
    { background_color( _color[i] ); }
//  virtual void background_image( base::String const &filename ) = 0;
//  virtual void background_clear_image() = 0;
  virtual void background_next();
  virtual void background_prev();
  virtual void background_synchronize();

  bool command(
    base::String const &command,
    base::String const &argument,
    base::String &response );

protected:

  // callbacks
  virtual void reset_cb();
  virtual void bgcolor0_cb()
    { background_color(_color[0U]); }
  virtual void bgcolor1_cb()
    { background_color(_color[1U]); }
  virtual void bgcolor2_cb()
    { background_color(_color[2U]); }
  virtual void bgcolor3_cb()
    { background_color(_color[3U]); }
  virtual void color_cb();
  virtual void image_cb()
    { background_file_selection_show(); }

  char const *label()
    { return "Background"; }

private:

  // pure virtuals
  virtual ::milieu::opengl::Background *background() = 0;
  virtual ::milieu::opengl::Background const *background() const = 0;
  virtual void background_file_selection_show() = 0;
//  virtual void stars(bool) = 0;

  // widgets
  virtual widget::ui::FloatSet *color_w() = 0;
//  virtual widget::ui::Widget *image_w() = 0;

  base::Color3 _color[4U];

  uint _background_counter;

  Background( Background const & );
  Background &operator=( Background const & );

};

} // namespace ui
} // namespace milieu

#endif // milieu_ui_Background_INCLUDED

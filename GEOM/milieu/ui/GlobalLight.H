/* GANG Software
 * GEOM/milieu/ui/GlobalLight.H
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

#ifndef milieu_ui_GlobalLight_INCLUDED
#define milieu_ui_GlobalLight_INCLUDED

#include "base/String.H"
#include "base/Color3.H"
#include "base/ReadUtil.H"
#include "widget/ui/Dialog.H"
#include "widget/ui/Choice.H"
#include "widget/ui/Boolean.H"
#include "widget/ui/FloatSet.H"

namespace milieu {

namespace opengl { class GlobalLight; }

namespace ui {

class GlobalLight
  :
    public widget::ui::Dialog,
    public base::ReadUtil
{

public:
  // constructor
  GlobalLight();

  // destructor
  virtual ~GlobalLight();

  // interface
  virtual void globallight_reset();
  virtual void globallight_enable( bool a )
    { enable_w()->set(a); }
  virtual void globallight_ambient( base::Color3 const &a )
    { ambient_w()->set(a.data()); }
  virtual void globallight_viewpoint( bool a )
    { viewpoint_w()->set(a); }
  virtual void globallight_sidedness( bool a )
    { sidedness_w()->set(a); }
  virtual void globallight_toggle()
    { enable_w()->set( ! enable_w()->get() ); }
  virtual void globallight_synchronize();

  bool command(
    base::String const &command,
    base::String const &argument,
    base::String &response );

protected:

  // callbacks
  virtual void enable_cb();
  virtual void reset_cb();
  virtual void ambient_cb();
  virtual void sidedness_cb();
  virtual void viewpoint_cb();

  char const *label()
    { return "Global Light"; }

private:

  // pure virtuals
  virtual ::milieu::opengl::GlobalLight *globallight() = 0;
  virtual ::milieu::opengl::GlobalLight const *globallight() const = 0;

  // widgets
  virtual widget::ui::Boolean *enable_w() = 0;
  virtual widget::ui::FloatSet *ambient_w() = 0;
  virtual widget::ui::Choice *viewpoint_w() = 0;
  virtual widget::ui::Choice *sidedness_w() = 0;

  static float const _default_lightmodel_ambient[3U];

  // disabled copy constructor
  GlobalLight( GlobalLight const & );
  // disabled assignment operator
  GlobalLight &operator=( GlobalLight const & );

};

} // namespace ui
} // namespace milieu

#endif // milieu_ui_GlobalLight_INCLUDED

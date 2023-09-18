/* GANG Software
 * VIEWER/isightui/ui/Mouse.H
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

#ifndef isightui_ui_Mouse_INCLUDED
#define isightui_ui_Mouse_INCLUDED

#include "base/ArrayX.H"
#include "base/String.H"
#include "base/ReadUtil.H"
#include "widget/ui/Dialog.H"
#include "widget/ui/Choice.H"
#include "widget/ui/Boolean.H"
#include "widget/ui/Float.H"
#include "widget/ui/FloatSet.H"

namespace isight { namespace kernel { class ViewerBase; } }

namespace isightui {
namespace ui {

class Mouse
  :
    public widget::ui::Dialog,
    public base::ReadUtil
{

public:

  // constructor
  Mouse();

  // destructor
  virtual ~Mouse();

  char const *label() const
    { return "Mouse"; }

  virtual void mouse_reset();
  virtual void mouse_inertia_enable( bool x )
  { inertia_enable_w()->set(x); }
  virtual void mouse_inertia_decay_enable( bool x )
  { inertia_decay_enable_w()->set(x); }
  virtual void mouse_inertia_decay_rate( float x )
  { inertia_decay_rate_w()->set(x); }
  virtual void mouse_speed( base::ArrayX<float,2U> const &x )
  { mouse_speed_w()->set(x.data()); }
  virtual void mouse_viewmode( uint x )
  { viewmode_w()->set(x); }

  //
  void synchronize();

  bool command(
    base::String const &command,
    base::String const &argument,
    base::String &response );

protected:

  // callbacks
  virtual void reset0_cb();
  virtual void reset1_cb();
  virtual void inertia_enable_cb();
  virtual void inertia_decay_enable_cb();
  virtual void inertia_decay_rate_cb();
  virtual void viewmode_cb();
  virtual void mouse_speed_cb();

private:

  virtual isight::kernel::ViewerBase *viewer() = 0;
  virtual isight::kernel::ViewerBase const *viewer() const = 0;

  // widgets
  virtual ::widget::ui::Choice   *viewmode_w() = 0;
  virtual ::widget::ui::Boolean  *inertia_enable_w() = 0;
  virtual ::widget::ui::Boolean  *inertia_decay_enable_w() = 0;
  virtual ::widget::ui::Float    *inertia_decay_rate_w() = 0;
  virtual ::widget::ui::FloatSet *mouse_speed_w() = 0;

  Mouse( Mouse const & );
  Mouse &operator=( Mouse const & );

};

} // namespace ui
} // namespace isightui

#endif // isightui_ui_Mouse_INCLUDED

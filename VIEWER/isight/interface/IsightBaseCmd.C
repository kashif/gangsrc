/* GANG Software
 * VIEWER/isight/interface/IsightBaseCmd.C
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

#include "isight/kernel/Viewer.H"
#include "isight/cmd/ContextCmd.H"
#include "IsightBaseCmd.H"

namespace isight {

class IsightBaseCmd1
  :
    public isight::kernel::Viewer
{
public:
  IsightBaseCmd1( IsightBaseCmd *parent ) :
      isight::kernel::Viewer(),
      _parent(parent) {}
  virtual ~IsightBaseCmd1() {}

protected:
  virtual void message( base::String const &text ) const
    { _parent->message(text); }
  virtual int window_key_press_event( uint key, uint state )
    { return _parent->window_key_press_event(key, state); }
  virtual context::ContextBase *context_construct( ContextSetBase *base )
    { return new isight::cmd::ContextCmd( base ); }

  virtual ::geomui::GeomUi *geom_ui()
    { return _parent; }
  virtual ::geomui::GeomUi const *geom_ui() const
    { return _parent; }
  virtual ::milieu::MilieuUi *milieu_ui()
    { return _parent; }
  virtual ::milieu::MilieuUi const *milieu_ui() const
    { return _parent; }
  virtual ::isightui::ViewerUi *viewer_ui()
    { return _parent; }
  virtual ::isightui::ViewerUi const *viewer_ui() const
    { return _parent; }

  virtual isight::kernel::ViewerBase *viewer()
    { return this; }
  virtual isight::kernel::ViewerBase const *viewer() const
    { return this; }

  virtual uint global_screen_width()
    { return 100; }
  virtual uint global_screen_height()
    { return 100; }

private:
  IsightBaseCmd *_parent;
};

IsightBaseCmd::
IsightBaseCmd()
    :
    IsightBase(),
    ::geomui::GeomUiCmd(),
    ::milieu::MilieuUiCmd(),
    ::isightui::ViewerUiCmd(),
    _(new IsightBaseCmd1(this) )
{
}

IsightBaseCmd::
~IsightBaseCmd()
{
  delete _;
}

geom::Surface *
IsightBaseCmd::
surface()
{
  return _->geomlist();
}

geom::Surface const *
IsightBaseCmd::
surface() const
{
  return _->geomlist();
}

void
IsightBaseCmd::
refresh()
{
  _->context()->refresh();
}

isight::kernel::ViewerBase *
IsightBaseCmd::
viewer()
{
  return _;
}

isight::kernel::ViewerBase const *
IsightBaseCmd::
viewer() const
{
  return _;
}

milieu::opengl::Milieu *
IsightBaseCmd::
milieu()
{
  return _->context()->milieu();
}

milieu::opengl::Milieu const *
IsightBaseCmd::
milieu() const
{
  return _->context()->milieu();
}

} // namespace isight

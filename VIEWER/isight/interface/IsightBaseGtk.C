/* GANG Software
 * VIEWER/isight/interface/IsightBaseGtk.C
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
#include "isight/gtk/ContextGtk.H"
#include "IsightBaseGtk.H"

namespace isight {

class IsightBaseGtk1
  :
    public isight::kernel::Viewer
{
public:
  IsightBaseGtk1( IsightBaseGtk *parent ) :
      isight::kernel::Viewer(),
      _parent(parent) {}
  virtual ~IsightBaseGtk1() {}
protected:
  virtual void message( base::String const &text ) const
    { _parent->message(text); }
  virtual int window_key_press_event( uint key, uint state )
    { return _parent->window_key_press_event(key, state); }
  virtual context::ContextBase *context_construct( ContextSetBase *base )
    { return new isight::gtk::ContextGtk( base ); }

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

  uint global_screen_width()
    { return gdk_screen_width(); }
  uint global_screen_height()
    { return gdk_screen_height(); }

private:
  IsightBaseGtk *_parent;
};

IsightBaseGtk::
IsightBaseGtk()
    :
    IsightBase(),
    ::geomui::GeomUiGtk(viewer_name()),
    ::milieu::MilieuUiGtk(viewer_name()),
    ::isightui::ViewerUiGtk(viewer_name()),
    _(new IsightBaseGtk1(this) )
{
}

IsightBaseGtk::
~IsightBaseGtk()
{
  delete _;
}

geom::Surface *
IsightBaseGtk::
surface()
{
  return _->geomlist();
}

geom::Surface const *
IsightBaseGtk::
surface() const
{
  return _->geomlist();
}

void
IsightBaseGtk::
refresh()
{
  _->context()->refresh();
}

isight::kernel::ViewerBase *
IsightBaseGtk::
viewer()
{
  return _;
}

isight::kernel::ViewerBase const *
IsightBaseGtk::
viewer() const
{
  return _;
}

milieu::opengl::Milieu *
IsightBaseGtk::
milieu()
{
  return _->context()->milieu();
}

milieu::opengl::Milieu const *
IsightBaseGtk::
milieu() const
{
  return _->context()->milieu();
}

char const *
IsightBaseGtk::
viewer_name()
{
  return "iSight";
}

void
IsightBaseGtk::
milieu_moving_notify( bool state )
{
  _->context()->milieu_moving_notify(state);
}

} // namespace isight

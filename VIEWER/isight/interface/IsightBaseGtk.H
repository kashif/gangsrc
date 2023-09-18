/* GANG Software
 * VIEWER/isight/interface/IsightBaseGtk.H
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

#ifndef isight_IsightBaseGtk_INCLUDED
#define isight_IsightBaseGtk_INCLUDED

#include "geomui/interface/GeomUiGtk.H"
#include "milieu/interface/MilieuUiGtk.H"
#include "isightui/interface/ViewerUiGtk.H"
#include "IsightBase.H"

namespace isight {

namespace kernel { class ViewerBase; }

class IsightBaseGtk1;

class IsightBaseGtk
  :
    public IsightBase,
    public ::geomui::GeomUiGtk,
    public ::milieu::MilieuUiGtk,
    public ::isightui::ViewerUiGtk
{

public:
  // constructor
  IsightBaseGtk();

  // destructor
  virtual ~IsightBaseGtk();

protected:

#if 0
  virtual void geom_controls( widget::ui::KeyBase &x)
    { geomui::GeomUiGtk::controls(x); }
  virtual void geom_controls_win( widget::ui::KeyBase &x)
    { geomui::GeomUiGtk::controls(x); }
#endif

private:

  // GeomUi
  virtual geom::Surface *surface();
  virtual geom::Surface const * surface() const;
  virtual void refresh();

  // MilieuUi
  virtual milieu::opengl::Milieu *milieu();
  virtual milieu::opengl::Milieu const *milieu() const;

  // ViewerUi
  virtual isight::kernel::ViewerBase *viewer();
  virtual isight::kernel::ViewerBase const *viewer() const;

  virtual void message( base::String const &text ) const = 0;
  virtual int window_key_press_event( uint key, uint state ) = 0;
  virtual void milieu_moving_notify( bool state );
  char const *viewer_name();

  IsightBaseGtk1 *_;

  // disabled copy constructor
  IsightBaseGtk( IsightBaseGtk const & );
  // disabled assignment operator
  IsightBaseGtk &operator=( IsightBaseGtk const & );

  friend class IsightBaseGtk1;
};

} // namespace isight

#endif // isight_IsightBaseGtk_INCLUDED

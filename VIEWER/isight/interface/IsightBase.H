/* GANG Software
 * VIEWER/isight/interface/IsightBase.H
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

#ifndef isight_IsightBase_INCLUDED
#define isight_IsightBase_INCLUDED

#include "geomui/interface/GeomUi.H"
#include "milieu/interface/MilieuUi.H"
#include "isightui/interface/ViewerUi.H"

namespace isight {

namespace kernel { class ViewerBase; }

class IsightBase
  :
    virtual public geomui::GeomUi,
    virtual public milieu::MilieuUi,
    virtual public isightui::ViewerUi
{

public:
  // constructor
  IsightBase();

  // destructor
  virtual ~IsightBase();

  virtual bool command( base::String const &command,
                        base::String const &argment,
                        base::String &response );

protected:

  virtual void hide_all();
  virtual void enable_tooltips( bool state );

private:

  virtual ::geomui::GeomUi *geom_ui()
    { return this; }
  virtual ::geomui::GeomUi const *geom_ui() const
    { return this; }
  virtual ::milieu::MilieuUi *milieu_ui()
    { return this; }
  virtual ::milieu::MilieuUi const *milieu_ui() const
    { return this; }
  virtual ::isightui::ViewerUi *viewer_ui()
    { return this; }
  virtual ::isightui::ViewerUi const *viewer_ui() const
    { return this; }

  ::geomui::GeomUi *_geom_ui()
    { return this; }
  ::geomui::GeomUi const *_geom_ui() const
    { return this; }
  ::milieu::MilieuUi *_milieu_ui()
    { return this; }
  ::milieu::MilieuUi const *_milieu_ui() const
    { return this; }
  ::isightui::ViewerUi *_viewer_ui()
    { return this; }
  ::isightui::ViewerUi const *_viewer_ui() const
    { return this; }

  // MilieuUi
  virtual milieu::opengl::Milieu *milieu() = 0;
  virtual milieu::opengl::Milieu const *milieu() const = 0;

  // GeomUi
  virtual geom::Surface *surface() = 0;
  virtual geom::Surface const *surface() const = 0;
  virtual void refresh() = 0;

  // ViewerUi
  virtual isight::kernel::ViewerBase *viewer() = 0;
  virtual isight::kernel::ViewerBase const *viewer() const = 0;

  // disabled copy constructor
  IsightBase( IsightBase const & );
  // disabled assignment operator
  IsightBase &operator=( IsightBase const & );

};

} // namespace isight

#endif // isight_IsightBase_INCLUDED

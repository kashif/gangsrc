/* GANG Software
 * VIEWER/isight/interface/IsightBaseCmd.H
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

#ifndef isight_IsightBaseCmd_INCLUDED
#define isight_IsightBaseCmd_INCLUDED

#include "milieu/interface/MilieuUiCmd.H"
#include "geomui/interface/GeomUiCmd.H"
#include "isightui/interface/ViewerUiCmd.H"
#include "IsightBase.H"

namespace isight {

namespace kernel { class ViewerBase; }

class IsightBaseCmd1;

class IsightBaseCmd
  :
    public IsightBase,
    public ::geomui::GeomUiCmd,
    public ::milieu::MilieuUiCmd,
    public ::isightui::ViewerUiCmd
{

public:
  // constructor
  IsightBaseCmd();

  // destructor
  virtual ~IsightBaseCmd();

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
  char const *viewer_name();

  IsightBaseCmd1 *_;

  // disabled copy constructor
  IsightBaseCmd( IsightBaseCmd const & );
  // disabled assignment operator
  IsightBaseCmd &operator=( IsightBaseCmd const & );

  friend class IsightBaseCmd1;
};

} // namespace isight

#endif // isight_IsightBaseCmd_INCLUDED

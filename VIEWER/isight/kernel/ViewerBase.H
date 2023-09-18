/* GANG Software
 * VIEWER/isight/kernel/ViewerBase.H
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

#ifndef isight_kernel_ViewerBase_INCLUDED
#define isight_kernel_ViewerBase_INCLUDED

#include "motion/Common.H"
#include "geom/interface/Surface.H"
#include "geom/interface/SurfaceGL.H"
#include "geomui/interface/GeomUi.H"
#include "milieu/interface/MilieuUi.H"
#include "isight/context/ContextBase.H"
#include "isightui/interface/ViewerUi.H"

namespace isight {
namespace kernel {

class ViewerBase
{

public:
  // constructor
  ViewerBase();

  // destructor
  virtual ~ViewerBase();

  // access to the current context
  virtual context::ContextBase *context() = 0;
  // access to the current context
  virtual context::ContextBase const *context() const = 0;

  // read from a stream
  virtual void read(
    io::Istream &stream,
    geom::FileMode filemode = geom::FILEMODE_DEFAULT )
    throw (io::ReadException) = 0;

  // read a file
  virtual void read(
    base::String const &filename,
    geom::FileMode filemode = geom::FILEMODE_UNSPECIFIED )
    throw (io::ReadException) = 0;

  // read a list of files
  virtual void read(
    base::vector<base::String> const &filename,
    geom::FileMode filemode = geom::FILEMODE_UNSPECIFIED )
    throw (io::ReadException) = 0;

  // write to a stream
  virtual void write(
    io::Ostream &stream,
    geom::FileMode filemode = geom::FILEMODE_DEFAULT) const
    throw (io::WriteException) = 0;

  // write a file
  virtual void write(
    base::String const &filename,
    geom::FileMode filemode = geom::FILEMODE_UNSPECIFIED) const
    throw (io::WriteException) = 0;

  // insert a surface into the viewer
  virtual void insert_geomobject( geom::Surface const & ) = 0;

  // insert a surface into the viewer
  virtual void insert_geomobject( geom::SurfaceGL const & ) = 0;

  virtual void
  geometry_(
    motion::GeometryMode mode,
    motion::GeometryGroup group,
    uint dim ) = 0;

  // select object
  virtual void select_geomobject_( uint id ) = 0;
  virtual void show_geomobject_( uint id, bool state ) = 0;
  virtual void move_geomobject_( uint id, bool state ) = 0;
  virtual void delete_geomobject_( uint id ) = 0;
  virtual bool geomobject_showing_( uint id ) = 0;
  virtual bool geomobject_moving_( uint id ) = 0;

  // select window
  virtual void new_window_() = 0;
  virtual void delete_window_( uint id ) = 0;
  virtual bool window_showing_(uint id) = 0;
  virtual void show_window_( uint id, bool state ) = 0;
  virtual void select_window_( uint id ) = 0;
  virtual base::String const &window_title() = 0;

  virtual uint global_screen_width() = 0;
  virtual uint global_screen_height() = 0;

  virtual ::geomui::GeomUi *geom_ui() = 0;
  virtual ::geomui::GeomUi const *geom_ui() const = 0;
  virtual ::milieu::MilieuUi *milieu_ui() = 0;
  virtual ::milieu::MilieuUi const *milieu_ui() const = 0;
  virtual ::isightui::ViewerUi *viewer_ui() = 0;
  virtual ::isightui::ViewerUi const *viewer_ui() const = 0;

protected:

private:

  // copy constructor
  ViewerBase( ViewerBase const & );
  // assignment operator
  ViewerBase &operator=( ViewerBase const & );
};

} // namespace kernel
} // namespace isight

#endif // isight_kernel_ViewerBase_INCLUDED

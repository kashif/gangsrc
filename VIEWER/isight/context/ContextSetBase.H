/* GANG Software
 * VIEWER/isight/context/ContextSetBase.H
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

#ifndef isight_context_ContextSetBase_INCLUDED
#define isight_context_ContextSetBase_INCLUDED

#include "base/System.H"
#include "base/String.H"
#include "motion/Common.H"
#include "isightui/interface/ViewerUi.H"

namespace isight {
namespace context {

class ContextBase;

class ContextSetBase
{

public:
#if 0
  virtual void windowsize_synchronize_notify() = 0;
  virtual void mouse_mode( motion::MouseMode ) = 0;
  virtual void image_size( uint &x, uint &y ) const = 0;
  virtual float image_compression() const = 0;
  virtual bool image_size_use_window() const = 0;
  virtual bool transparent() const = 0;
#endif
  virtual int window_key_press_event( uint key, uint state ) = 0;
  virtual int focus_in_event( ContextBase const * ) = 0;
  virtual void message( base::String const &text ) const = 0;
  virtual ::isightui::ViewerUi *viewer_ui() = 0;
  virtual ::isightui::ViewerUi const *viewer_ui() const = 0;

};

} // namespace context
} // namespace isight

#endif // isight_context_ContextSetBase_INCLUDED

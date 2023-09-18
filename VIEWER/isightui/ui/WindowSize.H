/* GANG Software
 * VIEWER/isightui/ui/WindowSize.H
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

#ifndef isightui_ui_WindowSize_INCLUDED
#define isightui_ui_WindowSize_INCLUDED

#include "base/ArrayX.H"
#include "base/String.H"
#include "base/ReadUtil.H"
#include "widget/ui/Dialog.H"
#include "widget/ui/IntSet.H"

namespace isight { namespace kernel { class ViewerBase; } }

namespace isightui {
namespace ui {

class WindowSize
  :
    public widget::ui::Dialog,
    public base::ReadUtil
{

public:

  // constructor
  WindowSize();

  // destructor
  virtual ~WindowSize();

  // interface
  virtual void windowsize_reset();
  virtual void windowsize_set( base::ArrayX<uint,2U> const &x )
    { restore( x[0], x[1] ); }

  virtual void windowsize_fullscreen( bool state );
  virtual void windowsize_toggle_fullscreen()
    { windowsize_fullscreen( ! _fullscreen ); }

  //
  void windowsize_synchronize();
  void windowsize_synchronize_notify()
    { windowsize_synchronize(); }

  char const *label() const
    { return "Window Size"; }

  bool command(
    base::String const &command,
    base::String const &argument,
    base::String &response );

protected:

  // callbacks
  virtual void window_size_cb();
  virtual void windowsize0_cb() { resize(0); }
  virtual void windowsize1_cb() { resize(1); }
  virtual void windowsize2_cb() { resize(2); }
  virtual void windowsize3_cb() { resize(3); }
  virtual void windowsize4_cb() { resize(4); }
  virtual void windowsize5_cb() { resize(5); }
  virtual void fullscreen_cb()
    { windowsize_fullscreen( true ); }

private:

  virtual isight::kernel::ViewerBase *viewer() = 0;
  virtual isight::kernel::ViewerBase const *viewer() const = 0;

  // widgets
  virtual ::widget::ui::IntSet *window_size_w() = 0;

  void resize( uint id );
  void restore( uint x, uint y );
  void update( uint x, uint y);

  bool _fullscreen;
  struct uint2 { uint x, y; };
//  static uint2 _screen_size;
  static uint2 _size[6];

  WindowSize( WindowSize const & );
  WindowSize &operator=( WindowSize const & );

};

} // namespace ui
} // namespace isightui

#endif // isightui_ui_WindowSize_INCLUDED

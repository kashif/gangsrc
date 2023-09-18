/* GANG Software
 * VIEWER/isight/context/Context.H
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

#ifndef isight_context_Context_INCLUDED
#define isight_context_Context_INCLUDED

#include <stdlib.h>
#include <math.h>
#include "base/System.H"
#include "geom/interface/SurfaceGL.H"
#include "opengl/Fade.H"
#include "isight/context/ContextSetBase.H"
#include "isight/context/ContextBase.H"
#include "Write.H"
#include "Background.H"

namespace isight {
namespace context {

class Context
  :
    public Background,
    protected opengl::Fade
{

public:

  // constructor
  Context( ContextSetBase *base );

  // destructor
  virtual ~Context();

  // set geometry
  virtual void geometry( motion::GeometryMode mode,
                         motion::GeometryGroup group,
                         uint dim );
protected:

  // draw the context
  virtual void draw();

  // callback for when the mouse focuses into the context
  virtual int focus_in_event( Context *w )
    { return base()->focus_in_event(w); }

  // callback for when context changes size
  virtual void context_size_event_cb( uint x, uint y );

  // callback for when a key is pressed in the context
  int window_key_press_event( uint key, uint state )
    { return base()->window_key_press_event( key, state ); }

private:

  virtual void fade()
    { Fade::fade(); }
  virtual void fade_enable(bool state)
    { Fade::fade_enable(state); }

  virtual void save_window_size_and_position()
    { _size_x = width(); _size_y = height();
    _position_x = x_position(); _position_y = y_position(); }

  virtual void restore_window_size_and_position()
    {
      resize( _size_x, _size_y );
      reposition( _position_x, _position_y );
    }

  virtual milieu::opengl::Milieu *milieu()
    { return this; }
  virtual milieu::opengl::Milieu const *milieu() const
    { return this; }

  //
  virtual void destroy_cb();

  // key shortcuts in the window
  uint _key_press_event( uint key, uint state );

  uint _size_x, _size_y;
  uint _position_x, _position_y;

  // disabled copy constructor
  Context( Context const & );
  // disabled assignment operator
  Context &operator=( Context const & );
};

} // namespace context
} // namespace isight

#endif // isight_context_Context_INCLUDED

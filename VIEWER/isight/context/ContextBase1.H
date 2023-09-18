/* GANG Software
 * VIEWER/isight/context/ContextBase1.H
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

#ifndef isight_context_ContextBase1_INCLUDED
#define isight_context_ContextBase1_INCLUDED

#include "milieu/opengl/Milieu.H"
#include "motion/Motion.H"
#include "widget/ui/Idler.H"
#include "ContextSetBase.H"
#include "ContextBase.H"

namespace isight {
namespace context {

class ContextBase1
  :
    public ContextBase,
    public milieu::opengl::Milieu
{

public:
  // constructor
  ContextBase1(ContextSetBase *base);

  // destructor
  virtual ~ContextBase1();

protected:

  virtual motion::GeometryMode geometry_mode() const
    { return geom_motion()->geometry_mode(); }
  virtual motion::GeometryGroup geometry_group() const
    { return geom_motion()->geometry_group(); }
  virtual uint geometry_dim() const
    { return geom_motion()->geometry_dim(); }
  virtual motion::MouseMode mouse_mode() const
    { return geom_motion()->mouse_mode(); }
  virtual void mouse_mode( motion::MouseMode x)
    { geom_motion()->mouse_mode(x); }
  virtual bool standard_geometry() const
    { return geom_motion()->standard_geometry(); }
  virtual void mouse_rotation() { WARN(); }
  virtual void mouse_translation() { WARN(); }
  virtual void mouse_inversion() { WARN(); }
  virtual void mouse_scale() { WARN(); }


  // mouse
  virtual bool inertia_enable() const
    { return geom_motion()->inertia_enable(); }
  virtual void inertia_enable( bool a )
    { geom_motion()->inertia_enable(a); }
  virtual bool inertia_decay() const
    { return geom_motion()->inertia_decay(); }
  virtual void inertia_decay( bool a )
    { geom_motion()->inertia_decay(a); }
  virtual float inertia_decay_rate() const
    { return geom_motion()->inertia_decay_rate(); }
  virtual void inertia_decay_rate( float a )
    { geom_motion()->inertia_decay_rate(a); }
  virtual float speed() const
    { return geom_motion()->speed(); }
  virtual void speed( float s, float a )
    { geom_motion()->speed(s, a); }
  virtual float acceleration() const
    { return geom_motion()->acceleration(); }
  virtual int view_mode() const
    { return geom_motion()->view_mode(); }
  virtual void view_mode( int m )
    { geom_motion()->view_mode(m); }
  virtual void stop_motion()
    { geom_motion()->stop_motion(); }

  virtual uint area_width() const = 0;
  virtual uint area_height() const = 0;

  virtual void refresh() = 0;

  ContextSetBase *base()
    { return _base; }
  ContextSetBase const *base() const
    { return _base; }

  motion::Motion *geom_motion()
    { return &_geom_motion; }
  motion::Motion const *geom_motion() const
    { return &_geom_motion; }
  motion::Motion *milieu_motion()
    { return &_milieu_motion; }
  motion::Motion const *milieu_motion() const
    { return &_milieu_motion; }

  bool mouse_press_event( uint button, uint x, uint y )
    { return current_motion()->mouse_press_event( button, x, y ); }

  bool mouse_release_event( uint button, uint x, uint y )
    { return current_motion()->mouse_release_event(button, x, y); }

  bool mouse_drag_event( uint x, uint y )
    { return current_motion()->mouse_drag_event(x, y); }

  int idle_cb()
    { return current_motion()->idle_cb(); }

  enum MotionMode { GEOMOBJECT, MILIEU };
  MotionMode motion_mode() const
    { return _motion_mode; }
  void motion_mode(MotionMode m)
    { _motion_mode = m; }

  virtual void enable_idle( bool state )
    { idler()->enable(state); }

private:
  virtual void milieu_moving_notify( bool state );

  virtual widget::ui::Idler *idler() = 0;

  class Motion1 : public motion::Motion
  {
  public:
    Motion1( ContextBase1 *parent ) : motion::Motion(), _parent(parent) {}
  private:
    void refresh() { _parent->refresh(); }
    void enable_idle( bool state ) { _parent->enable_idle(state); }
    ContextBase1 *_parent;
  };

  motion::Motion *current_motion()
    { return _current_motion; }
  motion::Motion const *current_motion() const
    { return _current_motion; }

  MotionMode _motion_mode;

  Motion1 _geom_motion;
  Motion1 _milieu_motion;
  Motion1 *_current_motion;

  ContextSetBase *_base;

  // disabled copy constructor
  ContextBase1( ContextBase1 const & );
  // disabled assignment operator
  ContextBase1 &operator=( ContextBase1 const & );

};

} // namespace context
} // namespace isight

#endif // isight_context_ContextBase1_INCLUDED

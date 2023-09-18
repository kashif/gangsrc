/* GANG Software
 * GEOM/motion/Inertia.H
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

#ifndef motion_Inertia_INCLUDED
#define motion_Inertia_INCLUDED

#include "TransformX.H"
#include "Mouse.H"

namespace motion {

class Inertia
  :
    public Mouse
{

public:
  // constructor
  Inertia();

  // destructor
  virtual ~Inertia();

  bool inertia_enable() const
    { return _inertia_enabled; } 
  void inertia_enable( bool a )
    { _inertia_enabled = a; if (!a) { stop_motion(); } }
  bool inertia_decay() const
    { return _inertia_decay_enabled; }
  void inertia_decay( bool a )
    { _inertia_decay_enabled = a; }
  float inertia_decay_rate() const
    { return _inertia_decay_rate; }
  void inertia_decay_rate( float a )
    { _inertia_decay_rate = a; }

  virtual motion::TransformX const *inertia() const
    { DIE_IF(_inertia == (TransformX *)0); return _inertia; }
  virtual void stop_motion();

  int idle_cb();

  bool moving() const
    {  return _inertia != (motion::TransformX *)0 && _inertia->on(); }

protected:

  TransformX *_inertia;

private:

  void enable_inertia(bool state);

  void decay_inertia();

  virtual void enable_idle( bool state ) = 0;

  // true means that the inertia is turned on
  bool _inertia_enabled;

  // true means that the inertia decay is turned on
  bool _inertia_decay_enabled;

  float _inertia_decay_rate;

  static float const INERTIA_DECAY_RATE_DEFAULT;
  static float const INERTIA_CLIP;

  // disabled copy constructor
  Inertia( Inertia const & );

  // disabled assignment operator
  Inertia &operator=( Inertia const & );

};

} // namespace motion

#endif // motion_Inertia_INCLUDED

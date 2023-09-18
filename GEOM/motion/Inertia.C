/* GANG Software
 * GEOM/motion/Inertia.C
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

#include "Inertia.H"

namespace motion {

float const Inertia::INERTIA_DECAY_RATE_DEFAULT = 0.975f;
float const Inertia::INERTIA_CLIP = 1.0e-4f;

Inertia::
Inertia()
    :
  _inertia((TransformX *)0),
  _inertia_enabled(true),
  _inertia_decay_enabled(false),
  _inertia_decay_rate(INERTIA_DECAY_RATE_DEFAULT)
{
}

Inertia::
~Inertia()
{
  if (_inertia != (TransformX *)0)
  {
    delete _inertia;
  }
}

void
Inertia::
enable_inertia( bool state )
{
  if (state && _inertia_enabled)
  {
    enable_idle(true);
  }
  else
  {
    stop_motion();
  }
}

void
Inertia::
stop_motion()
{
  enable_idle(false);

  if (_inertia != (TransformX *)0)
  {
    delete _inertia;
    _inertia = (TransformX *)0;
  }
}

void
Inertia::
decay_inertia()
{
  if ( _inertia == (TransformX *)0 ) { return; }

  // ignore inertia decay if inertia is not enabled
  if ( ! _inertia_enabled ) { return; }
  if ( ! _inertia_decay_enabled ) { return; }

  // decay the inertia
  _inertia->decay(_inertia_decay_rate, INERTIA_CLIP);

  if ( ! _inertia->on() )
  {
    stop_motion();
  }
}

int
Inertia::
idle_cb()
{
  // decay the inertia
  decay_inertia();

  if ( _inertia == (TransformX *)0 || ! _inertia->on() )
  {
    stop_motion();
  }

  refresh();

  return 1;
}

} // namespace motion

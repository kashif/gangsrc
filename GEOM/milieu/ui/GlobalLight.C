/* GANG Software
 * GEOM/milieu/ui/GlobalLight.C
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

#include "milieu/opengl/GlobalLight.H"
#include "GlobalLight.H"

namespace milieu {
namespace ui {

GlobalLight::
GlobalLight()
{
}

GlobalLight::
~GlobalLight()
{
}

void
GlobalLight::
globallight_reset()
{
  ambient_w()->set( base::Color3(0.2f, 0.2f, 0.2f).data() );

  viewpoint_w()->set(0);
  globallight()->viewpoint(0);

  sidedness_w()->set(1);
  globallight()->sidedness(1);

  enable_w()->set(true);
}

void
GlobalLight::
globallight_synchronize()
{
  // global lights
  enable_w()->set_blocked( globallight()->enable() );
  ambient_w()->set_blocked( globallight()->ambient().data() );
  viewpoint_w()->set_blocked(globallight()->viewpoint() );
  sidedness_w()->set_blocked(globallight()->sidedness() );
}

void
GlobalLight::
enable_cb()
{
  bool state = enable_w()->get();
  globallight()->enable( state );
}

void
GlobalLight::
reset_cb()
{
  globallight_reset();
}

void
GlobalLight::
ambient_cb()
{
  base::Color3 a;
  ambient_w()->get( a.data() );
  globallight()->ambient( a );
}

void
GlobalLight::
viewpoint_cb()
{
  int n =  viewpoint_w()->get();
  globallight()->viewpoint(n);
}

void
GlobalLight::
sidedness_cb()
{
  int n = sidedness_w()->get();
  globallight()->sidedness(n);
}

bool
GlobalLight::
command(
  base::String const &command,
  base::String const &argument,
  base::String &response )
{
  bool r = false;

  if ( command == "globalLightEnable" )
  {
    globallight_enable( read_bool(argument) );
    r = true;
  }
  else if ( command == "globalLightAmbient" )
  {
    base::Color3 x;
    read_color( x, argument );
    globallight_ambient( x );
    r = true;
  }
  else if ( command == "globalLightViewpoint" )
  {
    globallight_viewpoint( read_bool(argument) );
    r = true;
  }
  else if ( command == "globalLightSidedness" )
  {
    globallight_sidedness( read_bool(argument) );
    r = true;
  }

  return r;
}

} // namespace ui
} // namespace milieu

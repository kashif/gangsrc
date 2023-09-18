/* GANG Software
 * GEOM/milieu/ui/Light.C
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

#include "milieu/opengl/Light.H"
#include "Light.H"

namespace milieu {
namespace ui {

Light::
Light()
    :
    _showflag(false),
    _light_counter(0)
{
}

Light::
~Light()
{
}

// interface


void
Light::
light_reset()
{
  lightset()->reset();
  light_synchronize();
//  geomobject_move_enable(true);
}

void
Light::
light_reset( uint id )
{
  lightset()->reset( id );
  light_synchronize();
//  geomobject_move_enable(true);
}

void
Light::
light_enable( uint id, bool a )
{
  _enable(id, a);
  if ( id == id_w()->get() ) { enable_w()->set_blocked(a); }
}

void
Light::
light_moving( uint id, bool a )
{
  lightset()->moving(id, a);
  if ( id == id_w()->get() ) { moving_w()->set_blocked(a); }
}

void
Light::
light_show( uint id, bool a )
{
  _show(id, a);
  if ( id == id_w()->get() ) { show_w()->set_blocked(a); }
}

void
Light::
light_attached( uint id, bool a )
{
  _attached(id, a);
  if ( id == id_w()->get() ) { attached_w()->set_blocked(a); }
}

void
Light::
light_position( bool id, Transform const &a )
{
  lightset()->position(id, a);
}

void
Light::
light_ambient( uint id, base::Color3 const &a )
{
  _ambient(id, a);
  if ( id == id_w()->get() ) { ambient_w()->set_blocked(a.data()); }
}

void
Light::
light_diffuse( uint id, base::Color3 const &a )
{
  _diffuse(id, a);
  if ( id == id_w()->get() ) { diffuse_w()->set_blocked(a.data()); }
}

void
Light::
light_specular( uint id, base::Color3 const &a )
{
  _specular(id, a);
  if ( id == id_w()->get() ) { specular_w()->set_blocked(a.data()); }
}

void
Light::
light_spot( uint id, base::ArrayX<float,5U> const &a )
{
  _spot(id, a);
  if ( id == id_w()->get() ) { spot_w()->set_blocked(a.data()); }
}

void
Light::
light_attenuation( uint id, base::ArrayX<float,3U> const &a )
{
  _attenuation(id, a);
  if ( id == id_w()->get() ) { attenuation_w()->set_blocked(a.data()); }
}


void
Light::
light_next()
{
  _light_counter = (_light_counter == 6 ? 0 : _light_counter+1);

  uint i;
  for ( i = 0; i < 8; i++ )
  {
    lightset()->enable( i, i<_light_counter );
  }
  uint n = id_w()->get();
  enable_w()->set( n<_light_counter);
}

void
Light::
light_prev()
{
  _light_counter = (_light_counter == 0 ? 6 : _light_counter-1);

  uint i;
  for ( i = 0; i < 8; i++ )
  {
    lightset()->enable( i, i<_light_counter );
  }
  uint n = id_w()->get();
  enable_w()->set( n<_light_counter);
}

// utility

void
Light::
set_ui_from_data( opengl::LightSet *lightset )
{
  uint id = id_w()->get();
  enable_w()->set_blocked( lightset->enable(id) );
  moving_w()->set_blocked( lightset->moving(id) );
  show_w()->set_blocked( lightset->show(id) );
  attached_w()->set_blocked( lightset->attached(id) );
  ambient_w()->set_blocked( lightset->ambient(id).data() );
  diffuse_w()->set_blocked( lightset->diffuse(id).data() );
  specular_w()->set_blocked( lightset->specular(id).data() );
  spot_w()->set_blocked( lightset->spot(id).data() );
  attenuation_w()->set_blocked( lightset->attenuation(id).data() );
}

// implementation
#if 0
void
Light::
_moving( uint id, bool state )
{
  if (state)
  {
    // turn off clipplane motion
    clipplane_moving_off();

    // turn off light motion
    uint i;
    for ( i= 0; i < 8; i++ )
    {
      if ( i != id) { lightset()->moving( i, false ); }
    }
  }

  // reset off geomobject motion
  geomobject_move_enable(!state);

  lightset()->moving( id, state );
}
#endif
// callbacks

void
Light::
ambient_cb()
{
  base::Color3 a;
  ambient_w()->get( a.data() );
  _ambient( id_w()->get(), a );
}

void
Light::
diffuse_cb()
{
  base::Color3 a;
  diffuse_w()->get( a.data() );
  _diffuse( id_w()->get(), a );
}

void
Light::
specular_cb()
{
  base::Color3 a;
  specular_w()->get( a.data() );
  _specular( id_w()->get(), a );
}


void
Light::
spot_cb()
{
  base::ArrayX<float,5U> a;
  spot_w()->get( a.data() );
  _spot( id_w()->get(), a );
}

void
Light::
attenuation_cb()
{
  base::ArrayX<float,3U> a;
  attenuation_w()->get( a.data() );
  _attenuation( id_w()->get(), a );
}

void
Light::
hidebutton_cb()
{
  _showflag = ! _showflag;
  hidebox_w()->show(_showflag);
}

bool
Light::
command(
  base::String const &command,
  base::String const &argument,
  base::String &response )
{
  bool r = false;

  if ( command == "lightReset" )
  {
    if ( argument.empty() )
    {
      light_reset();
    }
    else
    {
      light_reset( read_uint(argument) );
    }
    r = true;
  }
  else if ( command == "lightEnable" )
  {
    base::String id, x;
    split1( id, x, argument );
    light_enable( read_uint(id), read_uint(x) );
    r = true;
  }
  else if ( command == "lightMoving" )
  {
    base::String id, x;
    split1( id, x, argument );
    light_moving( read_uint(id), read_uint(x) );
    r = true;
  }
  else if ( command == "lightAttached" )
  {
    base::String id, x;
    split1( id, x, argument );
    light_attached( read_uint(id), read_uint(x) );
    r = true;
  }
  else if ( command == "lightPosition" )
  {
    base::String id, x;
    split1( id, x, argument );
    Transform t;
    read_transform( t, x );
    light_position( read_bool(id), t );
    r = true;
  }
  else if ( command == "lightAmbient" )
  {
    base::String id, x;
    split1( id, x, argument );
    base::Color3 y;
    read_color( y, x );
    light_ambient( read_uint(id), y );
    r = true;
  }
  else if ( command == "lightDiffuse" )
  {
    base::String id, x;
    split1( id, x, argument );
    base::Color3 y;
    read_color( y, x );
    light_diffuse( read_uint(id), y );
    r = true;
  }
  else if ( command == "lightSpecular" )
  {
    base::String id, x;
    split1( id, x, argument );
    base::Color3 y;
    read_color( y, x );
    light_specular( read_uint(id), y );
    r = true;
  }
  else if ( command == "lightSpot" )
  {
    base::String id, x;
    split1( id, x, argument );
    base::vector<float> y;
    read_list( y, 5U, x );
    base::ArrayX<float,5U> z(&y[0]);
    light_spot( read_uint(id), z );
    r = true;
  }
  else if ( command == "lightAttenuation" )
  {
    base::String id, x;
    split1( id, x, argument );
    base::vector<float> y;
    read_list( y, 3U, x );
    base::ArrayX<float,3U> z(&y[0]);
    light_attenuation( read_uint(id), z );
    r = true;
  }

  return r;
}

} // namespace ui
} // namespace milieu

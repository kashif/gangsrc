/* GANG Software
 * GEOM/milieu/ui/Background.C
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

#include "base/System.H"
#include "milieu/opengl/Background.H"
#include "Background.H"

namespace milieu {
namespace ui {

Background::
Background()
    :
    _background_counter(0)
{
  _color[0] = base::Color3(0.0f, 0.0f, 0.0f);
  _color[1] = base::Color3(0.35f, 0.35f, 0.35f);
  _color[2] = base::Color3(0.7f, 0.7f, 0.7f);
  _color[3] = base::Color3(1.0f, 1.0f, 1.0f);
}

Background::
~Background()
{
}

void
Background::
background_reset()
{
  base::Color3 const black( 0.0f, 0.0f, 0.0f );
  color_w()->set_blocked( black.data() );
  background()->color( black );
}

void
Background::
background_synchronize()
{
  color_w()->set_blocked( background()->color().data() );
}

void
Background::
reset_cb()
{
  background_reset();
}

void
Background::
background_color( base::Color3 const &color )
{
  color_w()->set( color.data() );
  base::Color3 a;
  color_w()->get( a.data() ); // a is RGB
  background()->color( a );
  background()->background_clear_image();
}

void
Background::
color_cb()
{
  base::Color3 a;
  color_w()->get( a.data() ); // a is RGB
  background()->color( a );
  background()->background_clear_image();
}

void
Background::
background_next()
{
  _background_counter =
    (_background_counter == 4 ? 0 : _background_counter+1 );
  if (_background_counter == 4)
  {
    background()->stars(true);
  }
  else
  {
    background()->enable_draw(false);
    background()->stars(false);
    background_color(_background_counter);
    background()->enable_draw(true);
    background()->refresh();
  }
}

void
Background::
background_prev()
{
  _background_counter =
    ( _background_counter == 0 ? 4 : _background_counter-1 );
  if (_background_counter == 4)
  {
    background()->stars(true);
  }
  else
  {
    background()->enable_draw(false);
    background()->stars(false);
    background_color(_background_counter);
    background()->enable_draw(true);
    background()->refresh();
  }
}

bool
Background::
command(
  base::String const &command,
  base::String const &argument,
  base::String &response )
{
  bool r = false;

  // background
  if ( command == "backgroundColor" )
  {
    base::Color3 c;
    read_color( c, argument );
    background_color(c);
    r = true;
  }
  else if ( command == "backgroundReset" )
  {
    background_reset();
    r = true;
  }
  else if ( command == "backgroundImage" )
  {
    background()->background_image(argument.c_str());
    r = true;
  }
  else if ( command == "backgroundClearImage" )
  {
    background()->background_clear_image();
    r = true;
  }
  else if ( command == "backgroundPrev" )
  {
    background_prev();
    r = true;
  }
  else if ( command == "backgroundNext" )
  {
    background_prev();
    r = true;
  }
  return r;
}

} // namespace ui
} // namespace milieu

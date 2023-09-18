/* GANG Software
 * VIEWER/isightui/ui/Style.C
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

#include "isight/kernel/ViewerBase.H"
#include "Style.H"

namespace isightui {
namespace ui {

static float const ALPHA = 0.5;

Style::StyleData const Style::_style_data[Style::STYLE_COUNT] =
{
  { // style 0: color by normal
    {
      { // materials0
        true,                       // enable
        { 0.5f, 0.5f, 0.5f, ALPHA }, // color
        { 0.0f, 0.0f, 0.0f },       // ambient
        { 0.5f, 0.5f, 0.5f, ALPHA }, // diffuse
        { 1.0f, 1.0f, 1.0f },       // specular
        1.0f,                       // shininess
        false,                      // shademodel
        false,                      // transparent
        true,                       // lit
        true,                       // custom_color_flag
        1                           // custom_color
      },
      { // materials1
        false,                      // enable
        { 0.7f, 0.7f, 0.7f, ALPHA }, // color
        { 0.0f, 0.0f, 0.0f },       // ambient
        { 0.7f, 0.7f, 0.7f, ALPHA }, // diffuse
        { 0.0f, 0.0f, 0.0f },       // specular
        0.0f,                       // shininess
        false,                      // shademodel
        false,                      // transparent
        false,                      // lit
        false,                      // custom_color_flag
        0                           // custom_color
      }
    },
    { // milieu
      true,                       // lit
      { true, true, true },       // lights
      { 0.0f, 0.0f, 0.0f }        // background color
    }
  },

  { // style 1: color by gaussian curvature
    {
      { // material0
        true,                       // enable
        { 0.7f, 0.7f, 0.7f, ALPHA }, // color
        { 0.0f, 0.0f, 0.0f },       // ambient
        { 0.0f, 0.0f, 0.0f, ALPHA }, // diffuse
        { 1.0f, 1.0f, 1.0f },       // specular
        1.0f,                       // shininess
        false,                      // shademodel
        false,                      // transparent
        true,                       // lit
        true,                       // custom_color_flag
        2                           // custom_color
      },
      { // material1
        false,                      // enable
        { 0.7f, 0.7f, 0.7f, ALPHA }, // color
        { 0.0f, 0.0f, 0.0f },       // ambient
        { 0.0f, 0.0f, 0.0f, ALPHA }, // diffuse
        { 0.0f, 0.0f, 0.0f },       // specular
        0.0f,                       // shininess
        false,                      // shademodel
        false,                      // transparent
        false,                      // lit
        false,                      // custom_color_flag
        0                           // custom_color
      }
    },
    { // milieu
      true,                       // lit
      { true, true, true },       // lights
      { 0.0f, 0.0f, 0.0f }        // background color
    }
  },

  { // style 2: flat
    {
      { // material0
        true,                       // enable
        { 0.7f, 0.7f, 0.7f, ALPHA }, // color
        { 0.0f, 0.0f, 0.0f },       // ambient
        { 0.6f, 0.6f, 0.6f, ALPHA }, // diffuse
        { 0.1f, 0.1f, 0.1f },       // specular
        0.2f,                       // shininess
        true,                       // shademodel
        false,                      // transparent
        true,                       // lit
        false,                      // custom_color_flag
        0                           // custom_color
      },
      { // material1
        false,                      // enable
        { 0.7f, 0.7f, 0.7f, ALPHA }, // color
        { 0.0f, 0.0f, 0.0f },       // ambient
        { 0.0f, 0.0f, 0.0f, ALPHA }, // diffuse
        { 0.0f, 0.0f, 0.0f },       // specular
        0.0f,                       // shininess
        false,                      // shademodel
        false,                      // transparent
        false,                      // lit
        false,                      // custom_color_flag
        0                           // custom_color
      }
    },
    { // milieu
      true,                       // lit
      { true, true, true },       // lights
      { 0.0f, 0.0f, 0.0f }        // background color
    }
  },

  { // style 3: shiny
    {
      { // material0
        true,                       // enable
        { 0.7f, 0.7f, 0.7f, ALPHA }, // color
        { 0.0f, 0.0f, 0.0f },       // ambient
        { 0.6f, 0.6f, 0.6f, ALPHA }, // diffuse
        { 1.0f, 1.0f, 1.0f },       // specular
        1.0f,                       // shininess
        false,                       // shademodel
        false,                      // transparent
        true,                       // lit
        false,                      // custom_color_flag
        0                           // custom_color
      },
      { // material1
        false,                      // enable
        { 0.7f, 0.7f, 0.7f, ALPHA }, // color
        { 0.0f, 0.0f, 0.0f },       // ambient
        { 0.0f, 0.0f, 0.0f, ALPHA }, // diffuse
        { 0.0f, 0.0f, 0.0f },       // specular
        0.0f,                       // shininess
        false,                      // shademodel
        false,                      // transparent
        false,                      // lit
        false,                      // custom_color_flag
        0                           // custom_color
      }
    },
    { // milieu
      true,                       // lit
      { true, true, true },       // lights
      { 0.0f, 0.0f, 0.0f }        // background color
    }
  },

  { // style 4: transparent
    {
      { // materials0
        true,                       // enable
        { 0.7f, 0.7f, 0.7f, ALPHA }, // color
        { 0.0f, 0.0f, 0.0f },       // ambient
        { 0.5f, 0.5f, 0.5f, ALPHA }, // diffuse
        { 1.0f, 1.0f, 1.0f },       // specular
        1.0f,                       // shininess
        false,                      // shademodel
        true,                       // transparent
        true,                       // lit
        false,                      // custom_color_flag
        0                           // custom_color
      },
      { // materials1
        true,                       // enable
        { 0.2f, 0.2f, 0.2f, ALPHA }, // color
        { 0.0f, 0.0f, 0.0f },       // ambient
        { 0.2f, 0.2f, 0.2f, ALPHA }, // diffuse
        { 0.0f, 0.0f, 0.0f },       // specular
        0.0f,                       // shininess
        false,                      // shademodel
        true,                       // transparent
        true,                       // lit
        false,                      // custom_color_flag
        0                           // custom_color
      }
    },
    { // milieu
      true,                       // lit
      { true, true, true },       // lights
      { 0.0f, 0.0f, 0.0f }        // background color
    }
  },

  { // style 5: plain lit
    {
      { // material0
        true,                       // enable
        { 0.7f, 0.7f, 0.7f, ALPHA }, // color
        { 0.0f, 0.0f, 0.0f },       // ambient
        { 0.5f, 0.5f, 0.5f, ALPHA }, // diffuse
        { 0.2f, 0.2f, 0.2f },       // specular
        0.07f,                      // shininess
        false,                      // shademodel
        false,                      // transparent
        true,                       // lit
        false,                      // custom_color_flag
        0                           // custom_color
      },
      { // material1
        true,                       // enable
        { 0.0f, 0.0f, 0.0f, ALPHA }, // color
        { 0.0f, 0.0f, 0.0f },       // ambient
        { 0.0f, 0.0f, 0.0f, ALPHA }, // diffuse
        { 0.0f, 0.0f, 0.0f },       // specular
        0.0f,                       // shininess
        false,                      // shademodel
        false,                      // transparent
        false,                      // lit
        false,                      // custom_color_flag
        0                           // custom_color
      }
    },
    { // milieu
      true,                       // lit
      { true, true, true },       // lights
      { 0.0f, 0.0f, 0.0f }        // background color
    }
  },

  { // style 6: plain unlit
    {
      { // material0
        true,                       // enable
        { 0.0f, 0.0f, 0.0f, ALPHA }, // color
        { 0.0f, 0.0f, 0.0f },       // ambient
        { 0.0f, 0.0f, 0.0f, ALPHA }, // diffuse
        { 0.0f, 0.0f, 0.0f },       // specular
        0.0f,                       // shininess
        false,                      // shademodel
        false,                      // transparent
        false,                      // lit
        false,                      // custom_color_flag
        0                           // custom_color
      },
      { // material1
        true,                       // enable
        { 0.7f, 0.7f, 0.7f, ALPHA }, // color
        { 0.0f, 0.0f, 0.0f },       // ambient
        { 0.7f, 0.7f, 0.7f, ALPHA }, // diffuse
        { 0.0f, 0.0f, 0.0f },       // specular
        0.0f,                       // shininess
        false,                      // shademodel
        false,                      // transparent
        false,                      // lit
        false,                      // custom_color_flag
        0                           // custom_color
      }
    },
    { // milieu
      false,                       // lit
      { false, false, false },     // lights
      { 0.0f, 0.0f, 0.0f }         // background color
    },
  },

  { // style 7: wireframe
    {
      { // material0
        false,                      // enable
        { 0.7f, 0.7f, 0.7f, ALPHA }, // color
        { 0.0f, 0.0f, 0.0f },       // ambient
        { 0.0f, 0.0f, 0.0f, ALPHA }, // diffuse
        { 0.0f, 0.0f, 0.0f },       // specular
        0.0f,                       // shininess
        false,                      // shademodel
        false,                      // transparent
        true,                       // lit
        false,                      // custom_color_flag
        0                           // custom_color
      },
      { // material1
        true,                       // enable
        { 0.7f, 0.7f, 0.7f, ALPHA }, // color
        { 0.0f, 0.0f, 0.0f },       // ambient
        { 0.7f, 0.7f, 0.7f, ALPHA }, // diffuse
        { 0.0f, 0.0f, 0.0f },       // specular
        0.0f,                       // shininess
        false,                      // shademodel
        false,                      // transparent
        false,                      // lit
        false,                      // custom_color_flag
        0                           // custom_color
      }
    },
    { // milieu
      false,                      // lit
      { false, false, false },    // lights
      { 0.0f, 0.0f, 0.0f }        // background color
    }
  }

};


Style::
Style()
    :
    widget::ui::Dialog(),
    _style( uint(-1) )
{
}


Style::
~Style()
{
}

void
Style::
style_synchronize()
{
  axes_w()->set_blocked( viewer()->context()->axes() );
  sphere_w()->set_blocked( viewer()->context()->sphere() );
  stars_w()->set_blocked( viewer()->context()->stars() );
}

void
Style::
style( uint n )
{
  DIE_IF( n >= STYLE_COUNT );
  _style = n;

  viewer()->context()->enable_draw(false);

  geomlist()->reset_material();

  uint i;
  for ( i = 0; i < 2; i++ )
  {
    geomlist()->enable(i, _style_data[n].material[i].enablex );
    geomlist()->color(i, _style_data[n].material[i].color );
    geomlist()->ambient(i, _style_data[n].material[i].ambient );
    geomlist()->diffuse(i, _style_data[n].material[i].diffuse );
    geomlist()->specular(i, _style_data[n].material[i].specular );
    geomlist()->shininess(i, _style_data[n].material[i].shininess );
    geomlist()->shademodel(i, _style_data[n].material[i].shademodel );
    geomlist()->transparent(i, _style_data[n].material[i].transparent );
    geomlist()->lit(i, _style_data[n].material[i].lit );
  }
  geomlist()->custom_color(1, _style_data[n].material[1].custom_color_flag );
  geomlist()->custom_color(0, _style_data[n].material[0].custom_color_flag);

  if ( ! geomlist()->empty() )
  {
    base::Color4 c(0.0f, 0.5f, 0.5f, 0.5f);
    uint cc = _style_data[n].material[0].custom_color;
    if (cc == 0)
    {
      geomlist()->color_original(c);
    }
    else if (cc == 1)
    {
      geomlist()->color_by_normal(c);
    }
    else if (cc == 2)
    {
      geomlist()->color_by_gaussian_curvature(c, 0.5);
    }
  }

  // milieu
  milieu_ui()->globallight_enable( _style_data[n].milieu.lit );

  for ( i = 0; i < 3; i++ )
  {
    milieu_ui()->light_enable(
      i, _style_data[n].milieu.light[i] );
  }
  for ( i = 3; i < 8; i++ )
  { 
    milieu_ui()->light_enable( i, false );
  }

#if 0
  background_color( _style_data[n].milieu.background );
#endif

  geom_ui()->synchronize();

  viewer()->context()->enable_draw(true);
  viewer()->context()->refresh();
}

void
Style::
axes_cb()
{
  viewer()->context()->axes( axes_w()->get() );
}

void
Style::
sphere_cb()
{
  viewer()->context()->sphere( sphere_w()->get() );
}

void
Style::
stars_cb()
{
  viewer()->context()->stars( stars_w()->get() );
}

void
Style::
style_prev()
{
  uint n;
  if (_style >= STYLE_COUNT) { n = 0U; }
  else { n = ( _style == 0U ? STYLE_COUNT - 1U : _style - 1U ); }
  style(n);
}

void
Style::
style_next()
{
  uint n;
  if (_style >= STYLE_COUNT) { n = 0U; }
  else { n = ( _style == STYLE_COUNT - 1U ? 0U : _style + 1U ); }
  style(n);
}

bool
Style::
command(
  base::String const &command,
  base::String const &argument,
  base::String &response )
{
  bool r = false;

  if ( command == "style" )
  {
    style( read_uint(argument) );
    r = true;
  }

  if ( command == "axes" )
  {
    axes( read_bool(argument) );
    r = true;
  }

  if ( command == "toggleAxes" )
  {
    toggle_axes();
    r = true;
  }

  if ( command == "sphere" )
  {
    sphere( read_bool(argument) );
    r = true;
  }

  if ( command == "toggleSphere" )
  {
    toggle_sphere();
    r = true;
  }

  if ( command == "stars" )
  {
    stars( read_bool(argument) );
    r = true;
  }

  if ( command == "toggleStars" )
  {
    toggle_stars();
    r = true;
  }

  if ( command == "stylePrev" )
  {
    style_prev();
    r = true;
  }

  if ( command == "styleNext" )
  {
    style_next();
    r = true;
  }
  return r;
}

} // namespace ui
} // namespace isightui

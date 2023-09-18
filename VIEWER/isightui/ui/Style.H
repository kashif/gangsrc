/* GANG Software
 * VIEWER/isightui/ui/Style.H
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

#ifndef isightui_ui_Style_INCLUDED
#define isightui_ui_Style_INCLUDED

#include "base/ReadUtil.H"
#include "widget/ui/Dialog.H"
#include "widget/ui/Boolean.H"
#include "geomui/interface/GeomUi.H"
#include "milieu/interface/MilieuUi.H"
#include "geom/interface/Surface.H"

namespace isight { namespace kernel { class ViewerBase; } }

namespace isightui {
namespace ui {

class Style
  :
    public widget::ui::Dialog,
    public base::ReadUtil
{

public:

  // constructor
  Style();

  // destructor
  virtual ~Style();

  // interface
  virtual void style( uint n );
  virtual void axes(bool a)
    { axes_w()->set( a ); }
  virtual void toggle_axes()
    { axes_w()->set( ! axes_w()->get() ); }

  virtual void sphere(bool a)
    { sphere_w()->set( a ); }
  virtual void toggle_sphere()
    { sphere_w()->set( ! sphere_w()->get() ); }

  virtual void stars(bool a)
    { stars_w()->set( a ); }
  virtual void toggle_stars()
    { stars_w()->set( ! stars_w()->get() ); }
  virtual void style_prev();
  virtual void style_next();

  void style_synchronize();

  bool command(
    base::String const &command,
    base::String const &argument,
    base::String &response );

protected:

  // callbacks
  virtual void style0_cb()
    { style(0); }
  virtual void style1_cb()
    { style(1); }
  virtual void style2_cb()
    { style(2); }
  virtual void style3_cb()
    { style(3); }
  virtual void style4_cb()
    { style(4); }
  virtual void style5_cb()
    { style(5); }
  virtual void style6_cb()
    { style(6); }
  virtual void style7_cb()
    { style(7); }
  virtual void axes_cb();
  virtual void sphere_cb();
  virtual void stars_cb();

  char const *label() const
    { return "Style"; }

private:
  // pure virtuals
  virtual isight::kernel::ViewerBase *viewer() = 0;
  virtual isight::kernel::ViewerBase const *viewer() const = 0;
  virtual geom::Surface const *geomlist() const = 0;
  virtual geom::Surface *geomlist() = 0;
  virtual ::geomui::GeomUi *geom_ui() = 0;
  virtual ::geomui::GeomUi const *geom_ui() const = 0;
  virtual ::milieu::MilieuUi *milieu_ui() = 0;
  virtual ::milieu::MilieuUi const *milieu_ui() const = 0;

  static uint const STYLE_COUNT = 8;

  struct MaterialData
  {
    bool enablex;
    float color[4];
    float ambient[3];
    float diffuse[4];
    float specular[3];
    float shininess;
    bool shademodel;
    bool transparent;
    bool lit;
    bool custom_color_flag;
    uint custom_color;
  };

  struct MilieuData
  {
    bool lit;
    bool light[3];
    float background[3];
  };

  uint _style;

  struct StyleData
  {
    MaterialData material[2];
    MilieuData milieu;
  };
  static StyleData const _style_data[STYLE_COUNT];

  // widgets
  virtual widget::ui::Boolean *axes_w() = 0;
  virtual widget::ui::Boolean *sphere_w() = 0;
  virtual widget::ui::Boolean *stars_w() = 0;

  Style( Style const & );
  Style &operator=( Style const & );

};

} // namespace ui
} // namespace isightui

#endif // isightui_ui_Style_INCLUDED

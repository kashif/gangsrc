/* GANG Software
 * GEOM/milieu/cmd/Ui.H
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

#ifndef milieu_cmd_Ui_INCLUDED
#define milieu_cmd_Ui_INCLUDED

#include "milieu/opengl/Milieu.H"
#include "milieu/ui/Ui.H"
#include "BgRead.H"
#include "Background.H"
#include "Blend.H"
#include "Camera.H"
#include "ClipPlane.H"
#include "GlobalLight.H"
#include "Light.H"

namespace milieu {
namespace cmd {

class Ui
  :
    public ui::Ui,
    public BgRead,
    public Background,
    public Blend,
    public Camera,
    public ClipPlane,
    public GlobalLight,
    public Light
{

public:
  // constructor
  Ui();

  // destructor
  virtual ~Ui();


protected:
  virtual milieu::opengl::Milieu *milieu() = 0;
  virtual milieu::opengl::Milieu const *milieu() const = 0;

  virtual ::milieu::opengl::Background *background()
    { return milieu(); }
  virtual ::milieu::opengl::Background const *background() const
    { return milieu(); }
  virtual ::milieu::opengl::Blend *blend()
    { return milieu(); }
  virtual ::milieu::opengl::Blend const *blend() const
    { return milieu(); }
  virtual ::milieu::opengl::Camera *camera()
    { return milieu(); }
  virtual ::milieu::opengl::ClipPlaneSet *clipplaneset()
    { return milieu(); }
  virtual ::milieu::opengl::ClipPlaneSet const *clipplaneset() const
    { return milieu(); }
  virtual ::milieu::opengl::GlobalLight *globallight()
    { return milieu(); }
  virtual ::milieu::opengl::GlobalLight const *globallight() const
    { return milieu(); }
  virtual ::milieu::opengl::LightSet *lightset()
    { return milieu(); }
  virtual ::milieu::opengl::LightSet const *lightset() const
    { return milieu(); }

  virtual void background_file_selection_show()
    { BgRead::show_d(true); }

private:

  // disabled copy constructor
  Ui( Ui const & );
  // disabled assignment operator
  Ui &operator=( Ui const & );

};

} // namespace cmd
} // namespace milieu

#endif // milieu_cmd_Ui_INCLUDED

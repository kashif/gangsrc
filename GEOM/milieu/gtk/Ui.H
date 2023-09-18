/* GANG Software
 * GEOM/milieu/gtk/Ui.H
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

#ifndef milieu_gtk_Ui_INCLUDED
#define milieu_gtk_Ui_INCLUDED

#include "milieu/ui/Ui.H"
#include "BgRead.H"
#include "Background.H"
#include "Blend.H"
#include "Camera.H"
#include "ClipPlane.H"
#include "GlobalLight.H"
#include "Light.H"

namespace milieu {
namespace gtk {

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
  Ui(char const *title);

  // destructor
  virtual ~Ui();

protected:

  virtual void background_file_selection_show()
    { BgRead::show_d(true); }

private:

  // disabled copy constructor
  Ui( Ui const & );
  // disabled assignment operator
  Ui &operator=( Ui const & );

};

} // namespace gtk
} // namespace milieu

#endif // milieu_gtk_Ui_INCLUDED

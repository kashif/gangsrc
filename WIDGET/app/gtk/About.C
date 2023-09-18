/* GANG Software
 * WIDGET/app/gtk/About.C
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

#include "base/String.H"
#include "About.H"

namespace app {
namespace gtk {

About::
About( char const *title,
       char const *app_name,
       char const *about_info,
       char const * const *xpm )
    :
    About_(),
    ::app::app::Dialog( title, label(), main_widget() ),
    _pixmap( (::gtk::widget1::Pixmap *)0 )
{
  // insert the xpm
  if ( xpm != (char **)0 )
  {
    _pixmap = new ::gtk::widget1::Pixmap( xpm, window() );
    _pixmap->show();
    _image_w->add( _pixmap, true, true, 0 );
  }

  DIE_IF(app_name == (char *)0);
  DIE_IF(about_info == (char *)0);

  // insert the label
  base::String s = app_name;
  s += "-";
  s += base::system->version();
  s += "\n";
  s += about_info;
  _label_w->set_text(s.c_str());

}

About::
~About()
{
  if (_pixmap != (::gtk::widget1::Pixmap *)0)
  {
    delete _pixmap;
  }
}

} // namespace gtk
} // namespace app

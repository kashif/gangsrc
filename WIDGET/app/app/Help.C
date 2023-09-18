/* GANG Software
 * WIDGET/app/app/Help.C
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

#include <stdlib.h>
#include "gtk/widget1/Netscape.H"
#include "Help.H"

namespace app {
namespace app {

Help::
Help( char const *help_url_env )
    :
    _help_url((char const *)0)
{
  _help_url = getenv( help_url_env );
  if (_help_url == (char *)0)
  {
    _help_url = "http://www.math.umass.edu/software/";
  }
}

Help::
~Help()
{
}

void
Help::
help()
{
  ::gtk::widget1::Netscape::open_url_new_window(_help_url);
}

} // namespace app
} // namespace app

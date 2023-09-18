/* GANG Software
 * VIEWER/isight/context/Write.C
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

#include <gdk/gdkx.h>

#include "image/Io.H"
#include "Write.H"

namespace isight {
namespace context {

Write::
Write( ContextSetBase *base )
    :
    GeomObjectSet( base ),
    ::imagegl::ScreenLoad(),
    ::imagegl::ScreenDump( GDK_DISPLAY() ),
    ::imagegl::PostScript()
{
}

Write::
~Write()
{
}

void
Write::
write_image( base::String const &filename ) const
{
  ((Write *)this)->stop_motion();
  ((Write *)this)->enable_draw(false);
  uint x, y;
  size_for_image(x, y);
  image::Writer *writer = image::writer( filename );
  ScreenDump *p = (ScreenDump *)
    static_cast< ::imagegl::ScreenDump const *>(this);
  p->transparent( base()->viewer_ui()->transparent() );
  p->write( filename, x, y, *writer );
  delete writer;
  ((Write *)this)->enable_draw(true);
}

void
Write::
background_image(
  base::String const &filename, bool on_top )
{
  try
  {
    image::Reader *reader = ::image::reader( filename );
    ::imagegl::ScreenLoad::read( filename, *reader );
    delete reader;
    refresh();
  }
  catch ( base::Exception &e )
  {
    base()->message( base::String(e.message()) );
  }
}

void
Write::
background_clear_image()
{
  ::imagegl::ScreenLoad::clear();
  refresh();
}

void
Write::
size_for_image( uint &x, uint &y ) const
{
  if ( base()->viewer_ui()->image_size_use_window() )
  {
    x = area_width();
    y = area_height();
  }
  else
  {
    base()->viewer_ui()->get_image_size( x, y );
  }
}

} // namespace context
} // namespace isight

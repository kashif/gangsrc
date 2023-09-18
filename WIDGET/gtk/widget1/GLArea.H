/* GANG Software
 * WIDGET/gtk/widget1/GLArea.H
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

#ifndef gtk_widget1_GLArea_INCLUDED
#define gtk_widget1_GLArea_INCLUDED

#include <gtkgl/gtkglarea.h>
#include "gtk/widget0/DrawingArea.H"

namespace gtk {
namespace widget1 {

class GLArea
  :
  public ::gtk::widget0::DrawingArea
{

public:
  GLArea( int attributes[] ) :
      ::gtk::widget0::DrawingArea( gtk_gl_area_new( attributes ) ) {}
  void size( uint x, uint y )
    { gtk_gl_area_size( GTK_GL_AREA(w()), x, y ); }
  int make_current()
    { return gtk_gl_area_make_current( GTK_GL_AREA(w()) ); }
  void swap_buffers()
    { gtk_gl_area_swap_buffers( GTK_GL_AREA(w()) ); }

protected:

private:

  GLArea( GLArea const & );
  GLArea &operator=( GLArea const & );
};

} // namespace widget1
} // namespace gtk

#endif // gtk_widget1_GLArea_INCLUDED

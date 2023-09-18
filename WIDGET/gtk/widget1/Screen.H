/* GANG Software
 * WIDGET/gtk/widget1/Screen.H
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

#ifndef gtk_widget1_Screen_INCLUDED
#define gtk_widget1_Screen_INCLUDED

#include "gtk/widget0/DrawingArea.H"

namespace gtk {
namespace widget1 {

/*
  Screen for drawing points
*/

class Screen
  :
    public ::gtk::widget0::DrawingArea
{

public:

  struct PointInt { int unsigned x, y; };
  struct Color256 { char unsigned red, green, blue; };

  // constructor
  Screen();

  // destructor
  virtual ~Screen();

  void draw_point( PointInt const &p, Color256 const &c);

protected:

private:

  GdkGC *_gc;

  // disabled copy constructor
  Screen( Screen const & );

  // disabled assignment operator
  Screen &operator=( Screen const & );

};

} // namespace widget1
} // namespace gtk

#endif // gtk_widget1_Screen_INCLUDED

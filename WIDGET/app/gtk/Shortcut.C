/* GANG Software
 * WIDGET/app/gtk/Shortcut.C
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

#include "Shortcut.H"

namespace app {
namespace gtk {

Shortcut::
Shortcut(char const *title)
    :
    Shortcut_(),
    ::app::app::Dialog( title, label(), main_widget() )
{
  _label1_w->set_padding( 6, 0 );
  _label1_w->set_justify( GTK_JUSTIFY_LEFT );
  _label1_w->set_line_wrap( true );

  _label2_w->set_padding( 6, 0 );
  _label2_w->set_justify( GTK_JUSTIFY_LEFT );
  _label2_w->set_line_wrap( true );

  _label1_w->set_text(
"CTRL-h - Netscape Help\n"
"CTRL-q - Quit\n"
"CTRL-o - Open iSight File\n"
"CTRL-s - Save iSight File\n"
"CTRL-; - Main Menu Widget\n"
"\n"
"CTRL-M - Messages Widget\n"
"CTRL-A - About Widget\n"
"CTRL-p - WriteConfig Widget\n"
"CTRL-d - Command Widget\n"
"CTRL-k - Key Shortcuts Widget\n"
"CTRL-W - Close Windows\n"
"CTRL-T - Toggle Help Balloons\n"
"\n"
"CTRL-w - WindowSize Widget\n"
"CTRL-m - Mouse Widget\n"
"CTRL-g - Ambient Space Widget\n"
"CTRL-u - Select Object Widget\n"
"CTRL-i - Select Window Widget\n"
"CTRL-b - Build Widget\n"
"CTRL-t - Statistics Widget\n"
"CTRL-c - Camera Widget\n"
"\n"
"ALT-y - Styles Widget\n"
"ALT-m - Materials Widget\n"
"ALT-k - Custom Colors Widget\n"
"ALT-g - Global Light Widget\n"
"ALT-l - Lights Widget\n"
"ALT-b - Background Widget\n"
"ALT-d - Blend Widget\n"
"ALT-p - Clip Planes Widget\n"
"ALT-h - Mesh Clip Widget\n"
    );

  _label2_w->set_text(
"w - Toggle FullScreen\n"
"a - Toggle Axes\n"
"p - Toggle Sphere\n"
"f - Toggle Faces\n"
"e - Toggle Edges\n"
"v - Toggle Vertices\n"
"u - Toggle Boundary\n"
"x - Toggle Bounding Box\n"
"o - Toggle Silhouette\n"
"j - Toggle Smooth\n"
"t - Toggle Transparency\n"
"m - Cycle Two-way Mirror\n"
"y,Y - Cycle Styles\n"
"k,K - Cycle Custom Colors\n"
"b,B - Cycle Backgrounds\n"
"g - Toggle Global Light\n"
"l,L - Cycle Lights\n"
"h,H - Cycle Shininess\n"
"c - Reset Position\n"
"s - Stop Motion\n"
"CTRL-ALT-r - Mouse Rotation\n"
"CTRL-ALT-t - Mouse Translation\n"
"CTRL-ALT-i - Mouse Inversion\n"
"CTRL-ALT-S - Mouse Scale\n"
"\n"
"CTRL-O - Read Lab File\n"
"CTRL-S - Write Lab File\n"
"CTRL-X - Compute Surface\n"
"CTRL-C - Compute Widget\n"
"CTRL-L - Lab Widget\n"
"CTRL-D - Domain Widget\n"
"CTRL-U - Sequence Widget\n"
    );
}

Shortcut::
~Shortcut()
{
}

} // namespace gtk
} // namespace app

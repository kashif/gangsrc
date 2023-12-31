/* GANG Software
 * WIDGET/gtk/widget0/Label.H
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
// generated by gtk2c++

#ifndef gtk_widget0_Label_INCLUDED
#define gtk_widget0_Label_INCLUDED

#include "Misc.H"

namespace gtk {
namespace widget0 {

class Label : public Misc
{
public:
  Label( char const *str ) :
      Misc( gtk_label_new( str ) ) {}
  void set( char const *str )
    { set_text(str); }
  void set_text( char const *str )
    { gtk_label_set_text( GTK_LABEL(w()), str ); }
  void set_justify( GtkJustification jtype )
    { gtk_label_set_justify( GTK_LABEL(w()), jtype ); }
  void set_pattern( char const *pattern )
    { gtk_label_set_pattern( GTK_LABEL(w()), pattern ); }
  void set_line_wrap( bool wrap )
    { gtk_label_set_line_wrap( GTK_LABEL(w()), wrap ); }
  void get( char **str )
    { gtk_label_get( GTK_LABEL(w()), str ); }

protected:
  Label( GtkWidget *x ) : Misc(x) {}
};

} // namespace widget0
} // namespace gtk

#endif // gtk_widget0_Label_INCLUDED

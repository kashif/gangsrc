/* GANG Software
 * WIDGET/gtk/widget0/ProgressBar.H
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

#ifndef gtk_widget0_ProgressBar_INCLUDED
#define gtk_widget0_ProgressBar_INCLUDED

#include "widget/ui/Float.H"
#include "Progress.H"

namespace gtk {
namespace widget0 {

class ProgressBar
  :
    virtual public widget::ui::Float,
    public Progress
{
public:
  ProgressBar() :
      Progress( gtk_progress_bar_new() ) {}
  ProgressBar( GtkAdjustment *adjustment ) :
      Progress( gtk_progress_bar_new_with_adjustment( adjustment ) ) {}
  void set(float a) { update(a); }
  float get() const { WARN(); return 0.0f; }

  void format_string( char const *format )
    { gtk_progress_set_format_string( GTK_PROGRESS(w()), format ); }
  void show_text( bool state )
    { gtk_progress_set_show_text( GTK_PROGRESS(w()), state ); }


  void set_bar_style( GtkProgressBarStyle style )
    { gtk_progress_bar_set_bar_style( GTK_PROGRESS_BAR(w()), style ); }
  void set_discrete_blocks( uint blocks )
    { gtk_progress_bar_set_discrete_blocks( GTK_PROGRESS_BAR(w()), blocks ); }
  void set_activity_step( uint step )
    { gtk_progress_bar_set_activity_step( GTK_PROGRESS_BAR(w()), step ); }
  void set_activity_blocks( uint blocks )
    { gtk_progress_bar_set_activity_blocks( GTK_PROGRESS_BAR(w()), blocks ); }
  void set_orientation( GtkProgressBarOrientation orientation )
    { gtk_progress_bar_set_orientation( GTK_PROGRESS_BAR(w()), orientation ); }
  void update( float percentage )
    { gtk_progress_bar_update( GTK_PROGRESS_BAR(w()), percentage ); }

protected:
  ProgressBar( GtkWidget *x ) : Progress(x) {}
};

} // namespace widget0
} // namespace gtk

#endif // gtk_widget0_ProgressBar_INCLUDED

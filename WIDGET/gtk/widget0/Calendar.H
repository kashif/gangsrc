/* GANG Software
 * WIDGET/gtk/widget0/Calendar.H
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

#ifndef gtk_widget0_Calendar_INCLUDED
#define gtk_widget0_Calendar_INCLUDED

#include "Widget.H"

namespace gtk {
namespace widget0 {

class Calendar : public Widget
{
public:
  Calendar() :
      Widget( gtk_calendar_new() ) {}
  int select_month( uint month, uint year )
    { return gtk_calendar_select_month( GTK_CALENDAR(w()), month, year ); }
  void select_day( uint day )
    { gtk_calendar_select_day( GTK_CALENDAR(w()), day ); }
  int mark_day( uint day )
    { return gtk_calendar_mark_day( GTK_CALENDAR(w()), day ); }
  int unmark_day( uint day )
    { return gtk_calendar_unmark_day( GTK_CALENDAR(w()), day ); }
  void clear_marks()
    { gtk_calendar_clear_marks( GTK_CALENDAR(w())); }
  void display_options( GtkCalendarDisplayOptions flags )
    { gtk_calendar_display_options( GTK_CALENDAR(w()), flags ); }
  void get_date( uint *year, uint *month, uint *day )
    { gtk_calendar_get_date( GTK_CALENDAR(w()), year, month, day ); }
  void freeze()
    { gtk_calendar_freeze( GTK_CALENDAR(w())); }
  void thaw()
    { gtk_calendar_thaw( GTK_CALENDAR(w())); }

protected:
  Calendar( GtkWidget *x ) : Widget(x) {}
};

} // namespace widget0
} // namespace gtk

#endif // gtk_widget0_Calendar_INCLUDED

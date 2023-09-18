/* GANG Software
 * WIDGET/gtk/widgetc/gtk_numberwidget.c
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
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#if defined(__sgi) && !defined(__GNUC__)
#pragma set woff 1174,3201
#endif
#include <gtk/gtksignal.h>

#include "gtk_numberpatch.h"
#include "gtk_numberwidget.h"

/*#define TRACE fprintf( stderr, "trace: %s(%d)\n", __FILE__, __LINE__ );*/

static void gtk_numberwidget_class_init(GtkNumberWidgetClass *);
static void gtk_numberwidget_init(GtkNumberWidget *);

#if 0
static void gtk_numberwidget_finalize(GtkObject *object);
#endif

guint
gtk_numberwidget_get_type()
{
  static guint w_type = 0;

  if(!w_type)
  {
    GtkTypeInfo w_info =
    {
      "GtkNumberWidget",
      sizeof(GtkNumberWidget),
      sizeof(GtkNumberWidgetClass),
      (GtkClassInitFunc) gtk_numberwidget_class_init,
      (GtkObjectInitFunc) gtk_numberwidget_init,
      0,
      0
    };

    /*ooo*/
    w_type = gtk_type_unique(gtk_hbox_get_type(), &w_info);
  }

  return w_type;
}

static void
gtk_numberwidget_class_init(GtkNumberWidgetClass *c)
{
}

static void
gtk_numberwidget_init(GtkNumberWidget *w)
{
}

GtkWidget*
gtk_numberwidget_new()
{
  GtkNumberWidget *me;
  GtkAdjustment *adjustment;

  me = gtk_type_new( TYPE_GTK_NUMBERWIDGET );

  /* create a new adjustment */
  adjustment = GTK_ADJUSTMENT(gtk_adjustment_new(
    0.0, -FLT_MAX, FLT_MAX, 0.01, 0.1, 1.0 ));

  /* create a new numberpatch */
  me->numberpatch =
    GTK_NUMBERPATCH(gtk_numberpatch_new_with_adjustment( adjustment ) );

  /* show the gtk_numberpatch */
  gtk_widget_show( GTK_WIDGET(me->numberpatch) );
  /* put the gtk_numberpatch in the first column of the table */
  gtk_box_pack_start( GTK_BOX(GTK_HBOX(&me->hbox)),
                      GTK_WIDGET(me->numberpatch),
                      TRUE, TRUE, 0 );
  /* create a new gtk_numberinput */
  me->numberinput =
    GTK_NUMBERINPUT(gtk_numberinput_new_with_adjustment( adjustment ) );

  /* show the gtk_numberinput */
  gtk_widget_show( GTK_WIDGET(me->numberinput) );

  /* put the gtk_numberinput in the second column of the table */
  gtk_box_pack_start( GTK_BOX(GTK_HBOX(&me->hbox)),
                      GTK_WIDGET(me->numberinput),
                      TRUE, TRUE, 0 );
  return GTK_WIDGET(me);
}

/* access function */
GtkNumberPatch *gtk_numberwidget_get_gtk_numberpatch( GtkNumberWidget *w )
{
  return w->numberpatch;
}

/* access function */
GtkNumberInput *gtk_numberwidget_get_gtk_numberinput( GtkNumberWidget *w )
{
  return w->numberinput;
}

/* wrapper for the corresponding gtk_numberinput functions */
void gtk_numberwidget_set_label( GtkNumberWidget *w, char const *text )
{
  gtk_numberpatch_set_label( w->numberpatch, text );
}

/* wrapper for the corresponding gtk_numberinput functions */
GtkAdjustment *gtk_numberwidget_get_adjustment( GtkNumberWidget *w )
{
  return gtk_numberinput_get_adjustment(w->numberinput);
}

/* wrapper for the corresponding gtk_numberinput functions */
GtkAdjustment const *gtk_numberwidget_get_adjustment_const( GtkNumberWidget const *w )
{
  return gtk_numberinput_get_adjustment(w->numberinput);
}

/* wrapper for the corresponding gtk_numberinput functions */
void gtk_numberwidget_set_adjustment( GtkNumberWidget *w, GtkAdjustment *adj )
{
  gtk_numberinput_set_adjustment(w->numberinput, adj);
}

/* wrapper for the corresponding gtk_numberinput functions */
void gtk_numberwidget_set_value( GtkNumberWidget *w, gfloat value )
{
  gtk_adjustment_set_value(w->numberinput->adj, value);
}

void gtk_numberwidget_set_value_blocked(
  GtkNumberWidget *w, float const value, gpointer user_pointer )
{
  GtkAdjustment *adj = w->numberinput->adj;
  gtk_signal_handler_block_by_data( GTK_OBJECT(adj), user_pointer );
  gtk_adjustment_set_value(w->numberinput->adj, value);
  gtk_signal_handler_unblock_by_data( GTK_OBJECT(adj), user_pointer );
}

/* wrapper for the corresponding gtk_numberinput functions */
gfloat gtk_numberwidget_get_value( GtkNumberWidget *w )
{
  return gtk_numberinput_get_value( w->numberinput );
}

/* wrapper for the corresponding gtk_numberinput functions */
gint gtk_numberwidget_get_value_as_int( GtkNumberWidget *w )
{
  return gtk_numberinput_get_value_as_int( w->numberinput );
}

/* wrapper for the corresponding gtk_numberinput functions */
void gtk_numberwidget_set_speeds( GtkNumberWidget *w, float s0, float s1, float  s2)
{
  gtk_numberinput_set_speeds( w->numberinput, s0, s1, s2 );
  gtk_numberpatch_set_speeds( w->numberpatch, s0, s1, s2 );
}

/* wrapper for the corresponding gtk_numberinput functions */
void gtk_numberwidget_set_digits( GtkNumberWidget *w, guint n )
{
  gtk_numberinput_set_digits( w->numberinput, n );
}

void gtk_numberwidget_configure(
  GtkNumberWidget *w,
  numberwidget_config const *p )
{
  GtkAdjustment *adj = gtk_numberinput_get_adjustment( w->numberinput );

  /* set lower and upper bound on gtk_numberinput */
  adj->lower = p->min_value;
  adj->upper = p->max_value;

  gtk_numberinput_set_speeds(
    w->numberinput, p->speed0, p->speed1, p->speed2 );

  gtk_numberpatch_set_speeds(
    w->numberpatch, p->speed0, p->speed1, p->speed2 );

  gtk_numberinput_set_digits( w->numberinput, p->digits );

  /* set the default value for the gtk_numberinput
     NOTE HACK: sets wrong value first so that for value 0.000 the
     the gtk_numberwidget gets the right number of digits */
  gtk_numberinput_set_value(
    w->numberinput, p->value + 0.1 );

  gtk_numberinput_set_value(
    w->numberinput, p->value );

  /* label text */
  gtk_numberpatch_set_label( w->numberpatch, p->label );
  /* NOTE label size -- HACK */
  gtk_widget_set_usize( GTK_WIDGET(w->numberpatch->label), 40,20 );
  /* label alignment */
  gtk_misc_set_alignment(
    GTK_MISC(w->numberpatch->label), 0.95, 0.5);
}

/* NOTE should be a finalize */
#if defined(__sgi) && !defined(__GNUC__)
#pragma reset woff 3201
#endif

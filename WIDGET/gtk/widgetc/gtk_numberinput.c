/* GANG Software
 * WIDGET/gtk/widgetc/gtk_numberinput.c
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
#include <math.h>
#include <stdio.h>

#if defined(__sgi) && !defined(__GNUC__)
#include <nan.h>
#endif

#if defined(__sgi) && !defined(__GNUC__)
#pragma set woff 1174,1209,3201
#endif
#include <gdk/gdkkeysyms.h>
#include <gtk/gtksignal.h>

#include "gtk_numberinput.h"

/*#define TRACE fprintf( stderr, "trace: %s(%d)\n", __FILE__, __LINE__ )*/

/*#define NOTIFY(x) fprintf(stderr, "%s\n", (x))*/
#define NOTIFY(x)

#define MAX_TEXT_LENGTH 256

#define MIN_GTK_NUMBERINPUT_WIDTH 40

static void gtk_numberinput_class_init(GtkNumberInputClass *);
static void gtk_numberinput_init(GtkNumberInput *);

static gfloat gtk_numberinput_get_entry( GtkNumberInput *me );
static void gtk_numberinput_set_entry( GtkNumberInput *, gfloat );
void gtk_numberinput_update_from_entry( GtkNumberInput * );

void
gtk_numberinput_adjustment_value_changed( GtkAdjustment *, gpointer );

static void gtk_numberinput_size_request( GtkWidget *, GtkRequisition *);
static void gtk_numberinput_size_allocate( GtkWidget *, GtkAllocation *);
static gint gtk_numberinput_key_press( GtkWidget *, GdkEventKey * );
static gint gtk_numberinput_focus_out( GtkWidget *, GdkEventFocus *);
static gint gtk_numberinput_leave_notify( GtkWidget *, GdkEventCrossing * );

static GtkEntryClass *parent_class = 0;


guint
gtk_numberinput_get_type(void)
{
  static guint w_type = 0;

  if(!w_type)
  {
    GtkTypeInfo w_info =
    {
      "GtkNumberInput",
      sizeof(GtkNumberInput),
      sizeof(GtkNumberInputClass),
      (GtkClassInitFunc) gtk_numberinput_class_init,
      (GtkObjectInitFunc) gtk_numberinput_init,
      0,
      0
    };

    /* ooo */
    w_type = gtk_type_unique(gtk_entry_get_type(), &w_info);
  }

  return w_type;
}

static void
gtk_numberinput_class_init(GtkNumberInputClass *c)
{
  GtkWidgetClass   *widget_class;

  widget_class = (GtkWidgetClass*)c;

  /*ooo*/
  parent_class = gtk_type_class(GTK_TYPE_ENTRY);

  widget_class->size_request = gtk_numberinput_size_request;
  widget_class->size_allocate = gtk_numberinput_size_allocate;
  widget_class->key_press_event = gtk_numberinput_key_press;
  widget_class->focus_out_event = gtk_numberinput_focus_out;
  widget_class->leave_notify_event = gtk_numberinput_leave_notify;
}

static void
gtk_numberinput_init(GtkNumberInput *me)
{
  me->digits = 3;
  me->speed[0] = 0.001;
  me->speed[0] = 0.01;
  me->speed[0] = 0.1;
}

GtkWidget*
gtk_numberinput_new(void)
{
  return gtk_numberinput_new_with_adjustment(0);
}

GtkWidget*
gtk_numberinput_new_with_adjustment( GtkAdjustment *adjustment )
{
  GtkNumberInput *me;

  me = gtk_type_new( TYPE_GTK_NUMBERINPUT );

  g_return_val_if_fail(me != 0, 0);
  g_return_val_if_fail(IS_GTK_NUMBERINPUT(me), 0);

  if ( adjustment == 0 )
  {
    adjustment =
      (GtkAdjustment*) gtk_adjustment_new(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
  }

  gtk_numberinput_set_adjustment( me, adjustment );

  return GTK_WIDGET(me);
}

GtkAdjustment* gtk_numberinput_get_adjustment(GtkNumberInput *me )
{
  return me->adj;
}

void gtk_numberinput_set_adjustment(GtkNumberInput *me, GtkAdjustment *adjustment)
{
  g_return_if_fail(me != 0);
  g_return_if_fail(IS_GTK_NUMBERINPUT(me));

  if (me->adj)
  {
    gtk_signal_disconnect_by_data(
      GTK_OBJECT(me->adj),(gpointer) me);
    gtk_object_unref(GTK_OBJECT(me->adj));
  }

  me->adj = adjustment;
  gtk_object_ref(GTK_OBJECT(me->adj));

  gtk_signal_connect(
    GTK_OBJECT(adjustment), "value_changed",
    GTK_SIGNAL_FUNC( gtk_numberinput_adjustment_value_changed ),
    (gpointer) me);

  gtk_numberinput_set_entry( me, adjustment->value );
}

void
gtk_numberinput_size_request( GtkWidget *w, GtkRequisition *requisition )
{
  g_return_if_fail (w != 0);
  g_return_if_fail (requisition != 0);
  g_return_if_fail (IS_GTK_NUMBERINPUT(w));
#if 0
  GTK_WIDGET_CLASS(parent_class)->size_request(w, requisition);
  requisition->width = MIN_GTK_NUMBERINPUT_WIDTH +
    2 * w->style->klass->xthickness;
#endif
  GTK_WIDGET_CLASS(parent_class)->size_request(w, requisition);
  requisition->width = MIN_GTK_NUMBERINPUT_WIDTH;

}

void
gtk_numberinput_size_allocate( GtkWidget *w, GtkAllocation *allocation )
{
  g_return_if_fail (w != 0);
  g_return_if_fail (IS_GTK_NUMBERINPUT(w));
  g_return_if_fail (allocation != 0);

  GTK_WIDGET_CLASS(parent_class)->size_allocate(w, allocation);

  w->allocation = *allocation;

  if (GTK_WIDGET_REALIZED(w))
  {
    gdk_window_move_resize(
      w->window,
      allocation->x, allocation->y, allocation->width, allocation->height);
  }
}

gint
gtk_numberinput_key_press( GtkWidget *w, GdkEventKey *event )
{
  GtkNumberInput *me;
  gint key;
/*  gboolean key_repeat = FALSE; */
  gfloat x;

  NOTIFY( "key press" );

  g_return_val_if_fail(w != 0, FALSE);
  g_return_val_if_fail(IS_GTK_NUMBERINPUT(w), FALSE);
  g_return_val_if_fail(event != 0, FALSE);

  me = GTK_NUMBERINPUT(w);

  if ( !GTK_WIDGET_HAS_FOCUS(&me->entry) ) { return FALSE; }


  key = event->keyval;

  if (key == GDK_Up )
  {
    gtk_signal_emit_stop_by_name (GTK_OBJECT (&me->entry),
                                  "key_press_event");
    x = gtk_numberinput_get_entry( me );
    x += me->speed[0];
    gtk_numberinput_set_entry( me, x );
    gtk_adjustment_set_value( me->adj, x );
    return TRUE;
  }
  else if ( key == GDK_Down )
  {
    gtk_signal_emit_stop_by_name (GTK_OBJECT (&me->entry),
                                  "key_press_event");
    x = gtk_numberinput_get_entry( me );
    x -= me->speed[0];
    gtk_numberinput_set_entry( me, x );
    gtk_adjustment_set_value( me->adj, x );
    return TRUE;
  }
  else if ( key ==  GDK_Page_Up )
  {
    gtk_signal_emit_stop_by_name (GTK_OBJECT (&me->entry),
                                  "key_press_event");
    x = gtk_numberinput_get_entry( me );
    x += me->speed[1];
    gtk_numberinput_set_entry( me, x );
    gtk_adjustment_set_value( me->adj, x );
    return TRUE;
  }
  else if ( key == GDK_Page_Down )
  {
    gtk_signal_emit_stop_by_name (GTK_OBJECT (&me->entry),
                                  "key_press_event");
    x = gtk_numberinput_get_entry( me );
    x -= me->speed[1];
    gtk_numberinput_set_entry( me, x );
    gtk_adjustment_set_value( me->adj, x );
    return TRUE;
  }
  else if ( key == GDK_Return )
  {
    gtk_signal_emit_stop_by_name (GTK_OBJECT (&me->entry),
                                  "key_press_event");
    gtk_numberinput_update_from_entry( me );
    return TRUE;
  }

  return GTK_WIDGET_CLASS(parent_class)->key_press_event(w, event);
}

gint
gtk_numberinput_focus_out( GtkWidget *w, GdkEventFocus *event )
{
  GtkNumberInput *me;
/*  gint key; */
/*  gboolean key_repeat = FALSE; */
/*  gfloat x; */

  NOTIFY( "focus out" );

  g_return_val_if_fail(w != 0, FALSE);
  g_return_val_if_fail(IS_GTK_NUMBERINPUT(w), FALSE);
  g_return_val_if_fail(event != 0, FALSE);

  me = GTK_NUMBERINPUT(w);

  if ( !GTK_WIDGET_HAS_FOCUS (&me->entry) ) { return FALSE; }

  gtk_numberinput_update_from_entry( me );

  return GTK_WIDGET_CLASS(parent_class)->focus_out_event(w, event);
}

gint
gtk_numberinput_leave_notify( GtkWidget *w, GdkEventCrossing *event )
{
  GtkNumberInput *me;
/*  gint key; */
/*  gboolean key_repeat = FALSE; */
/*  gfloat x; */

  NOTIFY( "focus out" );

  g_return_val_if_fail(w != 0, FALSE);
  g_return_val_if_fail(IS_GTK_NUMBERINPUT(w), FALSE);
  g_return_val_if_fail(event != 0, FALSE);

  me = GTK_NUMBERINPUT(w);

  if ( !GTK_WIDGET_HAS_FOCUS (&me->entry) ) { return FALSE; }

  gtk_numberinput_update_from_entry( me );

  return FALSE;
}

void
gtk_numberinput_adjustment_value_changed( GtkAdjustment *adjustment, gpointer data)
{
  /*
    gtk_numberinput_adjustment_changed
    called whenever the value of the adjustment associated to the gtk_numberinput
    changes
  */
  GtkNumberInput *me;

  g_return_if_fail(adjustment != 0);
  g_return_if_fail(data != 0);

  me = GTK_NUMBERINPUT(data);

  gtk_numberinput_set_entry( me, adjustment->value );
}

void
gtk_numberinput_set_entry( GtkNumberInput *me, gfloat x )
{
  /* set the entry widget to x */

  char buffer[MAX_TEXT_LENGTH];

  if ( isnan(x) ) { abort(); }

  sprintf( buffer, "%0.*f", (int)me->digits, x );
  gtk_entry_set_text(GTK_ENTRY(&me->entry), buffer);
}


gfloat
gtk_numberinput_get_entry( GtkNumberInput *me )
{
  gchar *error = 0;
/*  gfloat x; */

  return strtod(gtk_entry_get_text(GTK_ENTRY(&me->entry)), &error);
}

void
gtk_numberinput_update_from_entry( GtkNumberInput *me )
{
  gfloat x;

  x = gtk_numberinput_get_entry( me );
  gtk_adjustment_set_value( me->adj, x );
}

void
gtk_numberinput_set_value( GtkNumberInput *me, gfloat value )
{
  g_return_if_fail(me != 0);
  g_return_if_fail(IS_GTK_NUMBERINPUT(me));

  gtk_adjustment_set_value(me->adj, value);
}

gfloat
gtk_numberinput_get_value( GtkNumberInput *me )
{
  g_return_val_if_fail(me != 0, 0.0);
  g_return_val_if_fail(IS_GTK_NUMBERINPUT(me), 0.0);

  return me->adj->value;
}

gint
gtk_numberinput_get_value_as_int( GtkNumberInput *me )
{
  gfloat val;

  g_return_val_if_fail(me != 0, 0);
  g_return_val_if_fail(IS_GTK_NUMBERINPUT(me), 0);

  val = me->adj->value;

  if (val - floor(val) < ceil(val) - val)
  {
    return floor(val);
  }
  else
  {
    return ceil(val);
  }
}

void
gtk_numberinput_set_digits( GtkNumberInput *me, guint d )
{
  g_return_if_fail(me != 0);
  g_return_if_fail(IS_GTK_NUMBERINPUT(me));
  me->digits = d;
}

void
gtk_numberinput_set_speeds(
  GtkNumberInput *me,
  float speed0, float speed1, float speed2 )
{
  g_return_if_fail(me != 0);
  g_return_if_fail(IS_GTK_NUMBERINPUT(me));
  me->speed[0] = speed0;
  me->speed[1] = speed1;
  me->speed[2] = speed2;
}

#if defined(__sgi) && !defined(__GNUC__)
#pragma reset woff 1174,1209,3201
#endif

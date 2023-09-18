/* GANG Software
 * WIDGET/gtk/widgetc/gtk_numberpatch.c
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
#if defined(__sgi) && !defined(__GNUC__)
#pragma set woff 1174,1209,3201
#endif
#include <gtk/gtkmain.h>
#include <gtk/gtksignal.h>
#include "gtk_numberpatch.h"


#define SCROLL_DELAY_LENGTH  300
#define GTK_NUMBERPATCH_DEFAULT_WIDTH 20
/*#define GTK_NUMBERPATCH_DEFAULT_HEIGHT 14 */

/*#define NOTIFY(x) fprintf(stderr, "%s\n", (x))*/
#define NOTIFY(x)
/*#define TRACE fprintf( stderr, "%s(%d)\n", __FILE__, __LINE__ )*/

static gint button_mask[3] =
{ GDK_BUTTON1_MASK, GDK_BUTTON2_MASK,GDK_BUTTON3_MASK };


/*
  --------------------------------------------------------------------------
  CONSTRUCTORS
*/

static void gtk_numberpatch_class_init(
  GtkNumberPatchClass *klass);
static void gtk_numberpatch_init(
  GtkNumberPatch *me);
#if 0
static void gtk_numberpatch_destroy(
  GtkObject *object);
#endif
static void gtk_numberpatch_realize(
  GtkWidget *widget);
#if 0
static void gtk_numberpatch_size_request(
  GtkWidget *widget,
  GtkRequisition *requisition);
static void gtk_numberpatch_size_allocate(
  GtkWidget *widget,
  GtkAllocation *allocation);
#endif
#if 0
static gint gtk_numberpatch_expose(
  GtkWidget *widget,
  GdkEventExpose *event);
#endif
static gint gtk_numberpatch_button_press(
  GtkWidget *widget,
  GdkEventButton *event);
static gint gtk_numberpatch_button_release(
  GtkWidget *widget,
  GdkEventButton *event);
static gint gtk_numberpatch_motion_notify(
  GtkWidget *widget,
  GdkEventMotion *event);
static void gtk_numberpatch_update_mouse(
  GtkNumberPatch *me, gint x, gint y);

#if 0
static void gtk_numberpatch_adjustment_value_changed(
  GtkAdjustment *adjustment,
  gpointer data);
#endif

guint gtk_numberpatch_get_type(void);



static GtkWidgetClass *parent_class = 0;

guint
gtk_numberpatch_get_type(void)
{
  static guint me_type = 0;

  if (!me_type)
  {
    GtkTypeInfo me_info =
    {
      "GtkNumberPatch",
      sizeof(GtkNumberPatch),
      sizeof(GtkNumberPatchClass),
      (GtkClassInitFunc) gtk_numberpatch_class_init,
      (GtkObjectInitFunc) gtk_numberpatch_init,
      0,
      0,
    };

    /* ooo */
    me_type = gtk_type_unique(gtk_event_box_get_type(), &me_info);
  }

  return me_type;
}

static void
gtk_numberpatch_class_init(
  GtkNumberPatchClass *class)
{
/*  GtkObjectClass *object_class; */
  GtkWidgetClass *widget_class;

/*  object_class = (GtkObjectClass*)class; */
  widget_class = (GtkWidgetClass*)class;

  /* ooo */
  parent_class = gtk_type_class(gtk_event_box_get_type());


#if 0
  widget_class->size_request = gtk_numberpatch_size_request;
  widget_class->size_allocate = gtk_numberpatch_size_allocate;

  object_class->destroy = gtk_numberpatch_destroy;


  widget_class->expose_event = gtk_numberpatch_expose;

#endif
  widget_class->realize = gtk_numberpatch_realize;

  widget_class->button_press_event = gtk_numberpatch_button_press;
  widget_class->button_release_event = gtk_numberpatch_button_release;
  widget_class->motion_notify_event = gtk_numberpatch_motion_notify;
}

static void
gtk_numberpatch_init( GtkNumberPatch *me)
{
  g_return_if_fail(me != 0);
  g_return_if_fail(IS_GTK_NUMBERPATCH(me));

  /* set event mask on event box */
  gtk_widget_set_events(
    GTK_WIDGET(&me->box),
    GDK_EXPOSURE_MASK
    | GDK_BUTTON_PRESS_MASK
    | GDK_BUTTON_RELEASE_MASK
    | GDK_POINTER_MOTION_MASK
    | GDK_POINTER_MOTION_HINT_MASK);

  /* create a new label */

  me->label = GTK_LABEL( gtk_label_new( "" ));

  gtk_widget_show( GTK_WIDGET(me->label) );

  /* put the label into the eventbox */
  gtk_container_add( GTK_CONTAINER(&me->box), GTK_WIDGET(me->label) );

  me->button = 0;
  me->speed[0] = 0.001;
  me->speed[1] = 0.01;
  me->speed[2] = 0.1;
  me->current_speed = 0.0;

  me->adjustment = 0;
}


/*
  --------------------------------------------------------------------------
  EVENT HANDLERS
*/

#if 0
static void
gtk_numberpatch_destroy(
  GtkObject *object)
{
  GtkNumberPatch *me;

  g_return_if_fail(object != 0);
  g_return_if_fail(IS_GTK_NUMBERPATCH(object));

  me = GTK_NUMBERPATCH(object);

  if (me->adjustment)
    gtk_object_unref(GTK_OBJECT(me->adjustment));

  if (GTK_OBJECT_CLASS(parent_class)->destroy)
  {
    (* GTK_OBJECT_CLASS(parent_class)->destroy)(object);
  }
}
#endif

#if 0
void
gtk_numberpatch_realize(
  GtkWidget *widget)
{
  GdkWindowAttr attributes;
  gint attributes_mask;

  NOTIFY( "==> realize" );

  g_return_if_fail(widget != 0);
  g_return_if_fail(IS_GTK_NUMBERPATCH(widget));

#if 0
  GTK_WIDGET_CLASS (parent_class)->realize (widget);

  GTK_WIDGET_UNSET_FLAGS (widget, GTK_NO_WINDOW);
#endif
  attributes.x = widget->allocation.x;
  attributes.y = widget->allocation.y;
  attributes.width = widget->allocation.width;
  attributes.height = widget->allocation.height;

  attributes.wclass = GDK_INPUT_OUTPUT;
  attributes.window_type = GDK_WINDOW_CHILD;

  attributes.event_mask =
    gtk_widget_get_events(widget)
    | GDK_EXPOSURE_MASK
    | GDK_BUTTON_PRESS_MASK
    | GDK_BUTTON_RELEASE_MASK
    | GDK_POINTER_MOTION_MASK
    | GDK_POINTER_MOTION_HINT_MASK;

  attributes.visual = gtk_widget_get_visual(widget);
  attributes.colormap = gtk_widget_get_colormap(widget);
  attributes.cursor = gdk_cursor_new( GDK_SB_H_DOUBLE_ARROW );

  attributes_mask =
    GDK_WA_X
    | GDK_WA_Y
    | GDK_WA_VISUAL
    | GDK_WA_COLORMAP
    | GDK_WA_CURSOR;

  widget->window =
    gdk_window_new(
      gtk_widget_get_parent_window(widget),
      &attributes, attributes_mask);
  widget->style = gtk_style_attach(widget->style, widget->window);
  gdk_window_set_user_data(widget->window, widget);

  gtk_style_set_background(widget->style, widget->window, GTK_STATE_NORMAL);

  GTK_WIDGET_SET_FLAGS(widget, GTK_REALIZED);
}
#endif


void
gtk_numberpatch_realize( GtkWidget *widget)
{
  GtkNumberPatch *me;
  GdkCursor *cursor;

  g_return_if_fail(widget != 0 );
  g_return_if_fail(IS_GTK_NUMBERPATCH(widget) );

  me = GTK_NUMBERPATCH(widget);

 GTK_WIDGET_CLASS (parent_class)->realize (widget);

  /* set cursor on event box */
  cursor = gdk_cursor_new( GDK_SB_H_DOUBLE_ARROW );
  gdk_window_set_cursor( GTK_WIDGET(&me->box)->window, cursor);
  gdk_cursor_destroy(cursor);
}

#if 0
static void
gtk_numberpatch_size_request(
  GtkWidget *widget,
  GtkRequisition *requisition)
{
  NOTIFY( "==> size request" );

  requisition->width = GTK_NUMBERPATCH_DEFAULT_WIDTH;
/*  requisition->height = GTK_NUMBERPATCH_DEFAULT_HEIGHT; */
}

static void
gtk_numberpatch_size_allocate(
  GtkWidget *widget,
  GtkAllocation *allocation)
{

  NOTIFY( "==> size allocate" );

  g_return_if_fail(widget != 0);
  g_return_if_fail(IS_GTK_NUMBERPATCH(widget));
  g_return_if_fail(allocation != 0);

  widget->allocation = *allocation;

  if (GTK_WIDGET_REALIZED(widget))
  {
    gdk_window_move_resize(
      widget->window,
      allocation->x, allocation->y,
      allocation->width, allocation->height);
  }
}
#endif

#if 0
static gint
gtk_numberpatch_expose(
  GtkWidget *widget,
  GdkEventExpose *event)
{
  GtkNumberPatch *me;

  g_return_val_if_fail(widget != 0, FALSE);
  g_return_val_if_fail(IS_GTK_NUMBERPATCH(widget), FALSE);
  g_return_val_if_fail(event != 0, FALSE);

  me = GTK_NUMBERPATCH(widget);

  NOTIFY( "==> expose" );

  if (event->count > 0)
  {
    return FALSE;
  }
  gtk_label_set_text( GTK_LABEL(me->label), "whatever, dude!" );
#if 0
  if ( me->text != (char *)0 )
  {
    /* FIX THIS */
    gtk_paint_string(
      widget->style, widget->window, (GtkStateType)widget->state,
      &event->area, widget, (gchar *)"label",
/* widget->allocation.x, widget->allocation.y,*/
     (gint)2, (gint)14, me->text );
  }
#endif
  return FALSE;
}
#endif

#if 0
void
gtk_numberpatch_adjustment_value_changed(
  GtkAdjustment *adjustment,
  gpointer data)
{
  /*
    gtk_numberpatch_adjustment_changed
    called whenever the value of the adjustment associated to the gtk_numberpatch
    changes
  */
  GtkNumberPatch *me;

  g_return_if_fail(adjustment != 0);
  g_return_if_fail(data != 0);

  me = GTK_NUMBERPATCH(data);

  me->value = adjustment->value;
}
#endif
/*
  --------------------------------------------------------------------------
  MOUSE EVENT HANDLERS
*/

static gint
gtk_numberpatch_button_press(
  GtkWidget *widget,
  GdkEventButton *event)
{
  /*
    gtk_numberpatch_button_press()
      this function is called whenever the user presses a mouse button over
      the gtk_numberpatch
  */
  GtkNumberPatch *me;
/*
  gint dx, dy;
  double s, c;
  double d_parallel;
  double d_perpendicular;
  */

  NOTIFY( "==> button press" );

  g_return_val_if_fail(widget != 0, FALSE);
  g_return_val_if_fail(IS_GTK_NUMBERPATCH(widget), FALSE);
  g_return_val_if_fail(event != 0, FALSE);

  me = GTK_NUMBERPATCH(widget);

  if ( me->button == 0 )
  {
    me->x_old = event->x;
    me->button = event->button;

    me->current_speed = me->speed[me->button-1];

    gtk_grab_add(widget);

    gtk_numberpatch_update_mouse(me, event->x, event->y);
  }
  return FALSE;
}

static gint
gtk_numberpatch_button_release(
  GtkWidget *widget,
  GdkEventButton *event)
{
  /*
    gtk_numberpatch_button_press()
      this function is called whenever the user releases the mouse button
  */
  GtkNumberPatch *me;

  NOTIFY( "==> button release" );

  g_return_val_if_fail(widget != 0, FALSE);
  g_return_val_if_fail(IS_GTK_NUMBERPATCH(widget), FALSE);
  g_return_val_if_fail(event != 0, FALSE);

  me = GTK_NUMBERPATCH(widget);

  if ( me->button == event->button )
  {
    gtk_grab_remove(widget);

    me->button = 0;
  }
  return FALSE;
}

static gint
gtk_numberpatch_motion_notify(
  GtkWidget *widget,
  GdkEventMotion *event)
{
  /*
    gtk_numberpatch_button_press()
      this function is called whenever the user moves the mouse

      typedef enum
      {
      GDK_SHIFT_MASK    = 1 << 0,
      GDK_LOCK_MASK     = 1 << 1,
      GDK_CONTROL_MASK  = 1 << 2,
      GDK_MOD1_MASK     = 1 << 3,
      GDK_MOD2_MASK     = 1 << 4,
      GDK_MOD3_MASK     = 1 << 5,
      GDK_MOD4_MASK     = 1 << 6,
      GDK_MOD5_MASK     = 1 << 7,
      GDK_BUTTON1_MASK  = 1 << 8,
      GDK_BUTTON2_MASK  = 1 << 9,
      GDK_BUTTON3_MASK  = 1 << 10,
      GDK_BUTTON4_MASK  = 1 << 11,
      GDK_BUTTON5_MASK  = 1 << 12,
      GDK_RELEASE_MASK  = 1 << 13,
      GDK_MODIFIER_MASK = 0x3fff
      } GdkModifierType;

  */
  GtkNumberPatch *me;
  GdkModifierType state;
  gint x, y;

  NOTIFY( "==> mouse motion" );

  g_return_val_if_fail(widget != 0, FALSE);
  g_return_val_if_fail(IS_GTK_NUMBERPATCH(widget), FALSE);
  g_return_val_if_fail(event != 0, FALSE);

  me = GTK_NUMBERPATCH(widget);

  if ( me->button != 0 )
  {
    if ( event->is_hint || (event->window != widget->window) )
    {
      gdk_window_get_pointer( widget->window, &x, &y, &state );
    }
    else
    {
      x = event->x;
      y = event->y;
      state = (GdkModifierType)event->state;
    }

    if ( state & button_mask[me->button-1] )
    {
      gtk_numberpatch_update_mouse( me, x, y );
    }
  }
  return FALSE;
}

static void
gtk_numberpatch_update_mouse(
  GtkNumberPatch *me, gint x, gint y)
{
  /*
    gtk_numberpatch_update_mouse()
      this function updates the gtk_numberpatch state
      (x, y) = mouse position
      this function is called by gtk_numberpatch_button_pressed()
      and gtk_numberpatch_motion_notify()
  */

  gfloat value;

/*  fprintf( stderr, "(x, y) = ( %d, %d )\n", x, y ); */

  g_return_if_fail(me != 0);
  g_return_if_fail(IS_GTK_NUMBERPATCH(me));

  /* increment current value */
  value = me->adjustment->value + (me->current_speed)*(x - me->x_old);

  /* clamp value */
  if (value < me->adjustment->lower) { value = me->adjustment->lower; }
  if (value > me->adjustment->upper) { value = me->adjustment->upper; }

  /* save mouse x position */
  me->x_old = x;

  /* emit "value_changed" signal */
  if (value != me->adjustment->value)
  {
    me->adjustment->value = value;
    gtk_signal_emit_by_name(GTK_OBJECT(me->adjustment), "value_changed");
  }
}

#if 0
void
gtk_numberpatch_adjustment_value_changed(
  GtkAdjustment *adjustment,
  gpointer data)
{
  GtkNumberPatch *me;

  g_return_if_fail(adjustment != 0);
  g_return_if_fail(data != 0);

  me = GTK_NUMBERPATCH(data);
}
#endif
/*
  --------------------------------------------------------------------------
  PUBLIC FUNCTIONS
*/


GtkWidget*
gtk_numberpatch_new(void)
{
  return gtk_numberpatch_new_with_adjustment(0);
}

GtkWidget*
gtk_numberpatch_new_with_adjustment(
  GtkAdjustment *adjustment)
{

  GtkNumberPatch *me;

  me = gtk_type_new( TYPE_GTK_NUMBERPATCH );

  g_return_val_if_fail(me != 0, 0);
  g_return_val_if_fail(IS_GTK_NUMBERPATCH(me), 0);

  if ( adjustment == 0 )
  {
    adjustment =
      (GtkAdjustment*) gtk_adjustment_new(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
  }

  gtk_numberpatch_set_adjustment(me, adjustment);

  return GTK_WIDGET(me);
}

GtkAdjustment*
gtk_numberpatch_get_adjustment(
  GtkNumberPatch *me)
{
  g_return_val_if_fail(me != 0, 0);
  g_return_val_if_fail(IS_GTK_NUMBERPATCH(me), 0);

  return me->adjustment;
}

void
gtk_numberpatch_set_adjustment(
  GtkNumberPatch *me,
  GtkAdjustment *adjustment)
{
  g_return_if_fail(me != 0);
  g_return_if_fail(IS_GTK_NUMBERPATCH(me));

  if (me->adjustment)
  {
    gtk_signal_disconnect_by_data(
      GTK_OBJECT(me->adjustment),(gpointer) me);
    gtk_object_unref(GTK_OBJECT(me->adjustment));
  }

  me->adjustment = adjustment;
  gtk_object_ref(GTK_OBJECT(me->adjustment));

#if 0
  gtk_signal_connect(
    GTK_OBJECT(adjustment), "value_changed",
    (GtkSignalFunc) gtk_numberpatch_adjustment_value_changed,
    (gpointer) me);
#endif
}


void
gtk_numberpatch_set_label(
  GtkNumberPatch *me, char const *s )
{
  g_return_if_fail(me != 0);
  g_return_if_fail(IS_GTK_NUMBERPATCH(me));

  gtk_label_set_text( me->label, s );
}


void
gtk_numberpatch_set_speeds(
  GtkNumberPatch *me, float speed0, float speed1, float speed2 )
{
  g_return_if_fail(me != 0);
  g_return_if_fail(IS_GTK_NUMBERPATCH(me));

  me->speed[0] = speed0;
  me->speed[1] = speed1;
  me->speed[2] = speed2;
}

#if defined(__sgi) && !defined(__GNUC__)
#pragma reset woff 1174,1209,3201
#endif

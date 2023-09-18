/* GANG Software
 * WIDGET/gtk/widgetc/gtk_numberwidget.h
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
#ifndef gtk_numberwidget_INCLUDED
#define gtk_numberwidget_INCLUDED

/*
  GtkNumberWidget is a GtkWidget made up of a GtkNumberPatch and a GtkNumberInput.
  A GtkNumberWidget is used to input real or integer values like a GtkSpinButton,
  with mouse drags (three speeds for three buttons) to increase/decrease
  values.
*/

#if defined(__sgi) && !defined(__GNUC__)
#pragma set woff 1174
#endif
#if 0
#include <gdk/gdk.h>
#endif

#include <gtk/gtkhbox.h>
#include <gtk/gtkframe.h>

#include "gtk_numberpatch.h"
#include "gtk_numberinput.h"
#if defined(__sgi) && !defined(__GNUC__)
#pragma reset woff 1174
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define TYPE_GTK_NUMBERWIDGET \
  (gtk_numberwidget_get_type ())
#define GTK_NUMBERWIDGET(obj) \
  GTK_CHECK_CAST(obj, gtk_numberwidget_get_type(), GtkNumberWidget)
#define GTK_NUMBERWIDGET_CLASS(klass) \
  GTK_CHECK_CLASS_CAST(klass, gtk_numberwidget_get_type(), GtkNumberWidgetClass)
#define IS_GTK_NUMBERWIDGET(obj) \
  GTK_CHECK_TYPE(obj, gtk_numberwidget_get_type())
#define IS_GTK_NUMBERWIDGET_CLASS(klass) \
  (GTK_CHECK_CLASS_TYPE ((klass), TYPE_GTK_NUMBERWIDGET))


typedef struct _GtkNumberWidget       GtkNumberWidget;
typedef struct _GtkNumberWidgetClass  GtkNumberWidgetClass;

struct _GtkNumberWidget
{
  /*ooo*/
  GtkHBox hbox;
  GtkNumberPatch *numberpatch;
  GtkNumberInput *numberinput;
};

struct _GtkNumberWidgetClass
{
  /*ooo*/
  GtkHBoxClass parent_class;
};

/* constructors, etc */
guint gtk_numberwidget_get_type(void);
GtkWidget *gtk_numberwidget_new(void);

/* access functions */
GtkNumberPatch *gtk_numberwidget_get_numberpatch( GtkNumberWidget * );
GtkNumberInput *gtk_numberwidget_get_numberinput( GtkNumberWidget * );

/* wrappers for the corresponding numberinput functions */
void gtk_numberwidget_set_label( GtkNumberWidget *, char const * );
GtkAdjustment *gtk_numberwidget_get_adjustment( GtkNumberWidget * );
GtkAdjustment const *gtk_numberwidget_get_adjustment_const( GtkNumberWidget const * );
void gtk_numberwidget_set_adjustment( GtkNumberWidget *, GtkAdjustment * );
void gtk_numberwidget_set_value( GtkNumberWidget *, gfloat );
void gtk_numberwidget_set_value_blocked(
  GtkNumberWidget *w, float const a, gpointer user_pointer );
gfloat gtk_numberwidget_get_value( GtkNumberWidget * );
gint gtk_numberwidget_get_value_as_int( GtkNumberWidget * );
void gtk_numberwidget_set_speeds( GtkNumberWidget *, float, float, float );
void gtk_numberwidget_set_digits( GtkNumberWidget *, guint );

struct numberwidget_config_
{
  char *label;
  float min_value;
  float max_value;
  float speed0, speed1, speed2;
  guint digits;
  float value;
};
typedef struct numberwidget_config_ numberwidget_config;

void gtk_numberwidget_configure(
  GtkNumberWidget *,
  numberwidget_config const * );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* gtk_numberwidget_INCLUDED */

/* GANG Software
 * WIDGET/gtk/widgetc/gtk_numberinput.h
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
#ifndef gtk_numberinput_INCLUDED
#define gtk_numberinput_INCLUDED

/*
  GtkNumberInput is a GtkWidget derived from GtkEntry which shows a number.
  GtkNumberPatch, together with GtkNumberInput, make up GtkNumberWidget.
*/

#if defined(__sgi) && !defined(__GNUC__)
#pragma set woff 1174
#endif
#include <gtk/gtkentry.h>
#if defined(__sgi) && !defined(__GNUC__)
#pragma reset woff 1174
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define TYPE_GTK_NUMBERINPUT \
  (gtk_numberinput_get_type ())
#define GTK_NUMBERINPUT(obj) \
  (GTK_CHECK_CAST ((obj), TYPE_GTK_NUMBERINPUT, GtkNumberInput))
#define GTK_NUMBERINPUT_CLASS(klass) \
  (GTK_CHECK_CLASS_CAST ((klass), TYPE_GTK_NUMBERINPUT, GtkNumberInputClass))
#define IS_GTK_NUMBERINPUT(obj) \
  (GTK_CHECK_TYPE ((obj), TYPE_GTK_NUMBERINPUT))
#define IS_GTK_NUMBERINPUT_CLASS(klass) \
  (GTK_CHECK_CLASS_TYPE ((klass), TYPE_GTK_NUMBERINPUT))


typedef struct _GtkNumberInput GtkNumberInput;
typedef struct _GtkNumberInputClass GtkNumberInputClass;

struct _GtkNumberInput
{
  /* ooo */
  GtkEntry entry;
  GtkAdjustment *adj;
  guint digits;
  float speed[3];
};

struct _GtkNumberInputClass
{
  /* ooo */
  GtkEntryClass parent_class;
};

guint gtk_numberinput_get_type(void);

GtkWidget *gtk_numberinput_new(void);
GtkWidget *gtk_numberinput_new_with_adjustment( GtkAdjustment *adj );

GtkAdjustment* gtk_numberinput_get_adjustment(GtkNumberInput *);
void gtk_numberinput_set_adjustment(GtkNumberInput *, GtkAdjustment *);

void gtk_numberinput_set_value( GtkNumberInput *, gfloat );
gfloat gtk_numberinput_get_value( GtkNumberInput * );
gint gtk_numberinput_get_value_as_int( GtkNumberInput * );

void gtk_numberinput_set_speeds( GtkNumberInput *, float, float, float );
void gtk_numberinput_set_digits( GtkNumberInput *, guint );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* gtk_numberinput_INCLUDED */

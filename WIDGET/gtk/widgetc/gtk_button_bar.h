/* GANG Software
 * WIDGET/gtk/widgetc/gtk_button_bar.h
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
/* Copyright (C) 2002 Nicholas Schmitt nick@math.umass.edu */

#ifndef gtk_button_bar_INCLUDED
#define gtk_button_bar_INCLUDED

/* Row or column of radio buttons */

#if defined(__sgi) && !defined(__GNUC__)
#pragma set woff 1174
#endif

#include <gtk/gtktable.h>
#include <gtk/gtkradiobutton.h>

#if defined(__sgi) && !defined(__GNUC__)
#pragma reset woff 1174
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define TYPE_GTK_BUTTON_BAR             (gtk_button_bar_get_type ())
#define GTK_BUTTON_BAR(obj)             (GTK_CHECK_CAST ((obj), TYPE_GTK_BUTTON_BAR, GtkButtonBar))
#define GTK_BUTTON_BAR_CLASS(klass)     (GTK_CHECK_CLASS_CAST ((klass), TYPE_GTK_BUTTON_BAR, GtkButtonBarClass))
#define IS_GTK_BUTTON_BAR(obj)          (GTK_CHECK_TYPE ((obj), TYPE_GTK_BUTTON_BAR))
#define IS_GTK_BUTTON_BAR_CLASS(klass)  (GTK_CHECK_CLASS_TYPE ((klass), TYPE_GTK_BUTTON_BAR))


typedef struct _GtkButtonBar       GtkButtonBar;
typedef struct _GtkButtonBarClass  GtkButtonBarClass;

struct _GtkButtonBar
{
  GtkTable table;
  GtkRadioButton **button;
  guint count;
};

struct _GtkButtonBarClass
{
  GtkTableClass parent_class;
  void (*f)(GtkButtonBar *);
};

GtkType gtk_button_bar_get_type(void);
GtkWidget *gtk_button_bar_new( guint rows, guint cols );
void gtk_button_bar_set( GtkButtonBar *self, guint n );
guint gtk_button_bar_get_value( GtkButtonBar *self );
void gtk_button_bar_set_labels( GtkButtonBar *self, char const *label[] );
void gtk_button_bar_set_sensitive( GtkButtonBar *self, guint id,
                                   gboolean state );
void gtk_button_bar_show( GtkButtonBar *self, guint id, gboolean state );

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* gtk_button_bar_INCLUDED */

/* GANG Software
 * WIDGET/gtk/widgetc/gtk_numberpatch.h
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
#ifndef gtk_numberpatch_INCLUDED
#define gtk_numberpatch_INCLUDED

/*
  GtkNumberPatch is a GtkWidget that changes values when you drag
  the mouse on it, three speeds for three mouse buttons.
  GtkNumberPatch, together with GtkNumberInput, make up GtkNumberWidget.
*/

#include <gtk/gtkeventbox.h>
#include <gtk/gtklabel.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define TYPE_GTK_NUMBERPATCH \
  (gtk_numberpatch_get_type ())
#define GTK_NUMBERPATCH(obj) \
  (GTK_CHECK_CAST ((obj), TYPE_GTK_NUMBERPATCH, GtkNumberPatch))
#define GTK_NUMBERPATCH_CLASS(klass) \
  (GTK_CHECK_CLASS_CAST ((klass), TYPE_GTK_NUMBERPATCH, GtkNumberPatchClass))
#define IS_GTK_NUMBERPATCH(obj) \
  (GTK_CHECK_TYPE ((obj), TYPE_GTK_NUMBERPATCH))
#define IS_GTK_NUMBERPATCH_CLASS(klass) \
  (GTK_CHECK_CLASS_TYPE ((klass), TYPE_GTK_NUMBERPATCH))


typedef struct _GtkNumberPatch        GtkNumberPatch;
typedef struct _GtkNumberPatchClass   GtkNumberPatchClass;

struct _GtkNumberPatch
{
/*  GtkWidget widget; */

  /* ooo */
  GtkEventBox box;
  GtkLabel *label;

  /* Button currently pressed or 0 if none */
  guint8 button;
  gint x_old;
  gfloat speed[3], current_speed;

  /* ID of update timer, or 0 if none */
  guint32 timer;

  /* The adjustment object that stores the data for this gtk_numberpatch */
  GtkAdjustment *adjustment;
};

struct _GtkNumberPatchClass
{
  /* ooo */
  GtkEventBoxClass parent_class;
};

guint gtk_numberpatch_get_type(void);
GtkWidget* gtk_numberpatch_new(void);
GtkWidget* gtk_numberpatch_new_with_adjustment( GtkAdjustment *adjustment );

GtkAdjustment* gtk_numberpatch_get_adjustment( GtkNumberPatch * );
void gtk_numberpatch_set_adjustment( GtkNumberPatch *, GtkAdjustment *adjustment );
void gtk_numberpatch_set_speeds( GtkNumberPatch *, float, float, float );
void gtk_numberpatch_set_label( GtkNumberPatch *, char const * );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* gtk_numberpatch_INCLUDED */

/* GANG Software
 * WIDGET/gtk/widgetc/gtk_popnotebook.h
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
#ifndef gtk_popnotebook_INCLUDED
#define gtk_popnotebook_INCLUDED

/* GTK Notebook with detachable pages */

#if defined(__sgi) && !defined(__GNUC__)
#pragma set woff 1174
#endif

#include <gtk/gtknotebook.h>
#include <gtk/gtklabel.h>
#include <gtk/gtkvbox.h>
#include <gtk/gtkhbox.h>
#include <gtk/gtkframe.h>
#include <gtk/gtkbutton.h>
#include <gtk/gtkwindow.h>

#if defined(__sgi) && !defined(__GNUC__)
#pragma reset woff 1174
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define TYPE_GTK_POPNOTEBOOK             (gtk_popnotebook_get_type ())
#define GTK_POPNOTEBOOK(obj)             (GTK_CHECK_CAST ((obj), TYPE_GTK_POPNOTEBOOK, GtkPopNotebook))
#define GTK_POPNOTEBOOK_CLASS(klass)     (GTK_CHECK_CLASS_CAST ((klass), TYPE_GTK_POPNOTEBOOK, GtkPopNotebookClass))
#define IS_GTK_POPNOTEBOOK(obj)          (GTK_CHECK_TYPE ((obj), TYPE_GTK_POPNOTEBOOK))
#define IS_GTK_POPNOTEBOOK_CLASS(klass)  (GTK_CHECK_CLASS_TYPE ((klass), TYPE_GTK_POPNOTEBOOK))


typedef struct _GtkPopNotebook       GtkPopNotebook;
typedef struct _GtkPopNotebookClass  GtkPopNotebookClass;
typedef struct _GtkPopNotebookPage GtkPopNotebookPage;

#define GTK_POPNOTEBOOK_MAX_PAGES 20
struct _GtkPopNotebookCounter
{
  GtkPopNotebook *me;
  guint id;
};
typedef struct _GtkPopNotebookCounter GtkPopNotebookCounter;


struct _GtkPopNotebook
{
  GtkNotebook notebook;
  GtkPopNotebookPage *page;
  guint page_count;
  /* Note: counter[] cannot be reallocated without breaking
     the button callback. Hence is fixed size */
  GtkPopNotebookCounter counter[GTK_POPNOTEBOOK_MAX_PAGES];
  char const *title;
};

struct _GtkPopNotebookPage {
  GtkLabel *tab_label;
  char const *tab_label_text;
  GtkWidget *child;
  GtkVBox *vbox0;
  GtkFrame *frame;
  GtkVBox *vbox;
  GtkHBox *hbox;
  GtkLabel *label;
  char const *label_text;
  GtkButton *button;
  int attached;
  GtkWindow *window;
};

struct _GtkPopNotebookClass
{
  GtkNotebookClass  parent_class;
};

GtkType gtk_popnotebook_get_type(void);
GtkWidget *gtk_popnotebook_new(void);

void gtk_popnotebook_append_page (
  GtkPopNotebook *popnotebook,
  GtkWidget *child,
  char const *tab_label_text,
  char const *label_text,
  GtkWindow *main_window );

void gtk_popnotebook_add (
  GtkPopNotebook *popnotebook,
  GtkWidget *child );

void gtk_popnotebook_set_tab_label(
  GtkPopNotebook *popnotebook,
  GtkWidget *child,
  GtkWidget *tab_label);

void gtk_popnotebook_add_with_label(
  GtkPopNotebook *popnotebook,
  GtkWidget *child,
  GtkWidget *tab_label);

void gtk_popnotebook_set_title(
  GtkPopNotebook *popnotebook, char const *title );

void gtk_popnotebook_set_packing(
  GtkPopNotebook *popnotebook, guint page,
  gboolean expand, gboolean fill, guint padding, GtkPackType pack_type );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* gkt_popnotebook_INCLUDED */

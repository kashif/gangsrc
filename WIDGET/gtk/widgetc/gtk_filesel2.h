/* GANG Software
 * WIDGET/gtk/widgetc/gtk_filesel2.h
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
/* GTK - The GIMP Toolkit
 * Copyright (C) 1995-1997 Peter Mattis, Spencer Kimball and Josh MacDonald
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

/*
 * Modified by the GTK+ Team and others 1997-1999.  See the AUTHORS
 * file for a list of people on the GTK+ Team.  See the ChangeLog
 * files for a list of changes.  These files are distributed with
 * GTK+ at ftp://ftp.gtk.org/pub/gtk/. 
 */

#ifndef __GTK_FILESEL2_H__
#define __GTK_FILESEL2_H__


#include <gdk/gdk.h>
#include <gtk/gtkvbox.h>


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#define GTK_TYPE_FILE_SELECTION2            (gtk_file_selection2_get_type ())
#define GTK_FILE_SELECTION2(obj)            (GTK_CHECK_CAST ((obj), GTK_TYPE_FILE_SELECTION2, GtkFileSelection2))
#define GTK_FILE_SELECTION2_CLASS(klass)    (GTK_CHECK_CLASS_CAST ((klass), GTK_TYPE_FILE_SELECTION2, GtkFileSelection2Class))
#define GTK_IS_FILE_SELECTION2(obj)         (GTK_CHECK_TYPE ((obj), GTK_TYPE_FILE_SELECTION2))
#define GTK_IS_FILE_SELECTION2_CLASS(klass) (GTK_CHECK_CLASS_TYPE ((klass), GTK_TYPE_FILE_SELECTION2))


typedef struct _GtkFileSelection2       GtkFileSelection2;
typedef struct _GtkFileSelection2Class  GtkFileSelection2Class;

struct _GtkFileSelection2
{
  GtkVBox containing_vbox;

  GtkWidget *dir_list;
  GtkWidget *file_list;
  GtkWidget *selection_entry;
  GtkWidget *selection_text;
  GtkWidget *main_vbox;
  GtkWidget *ok_button;
  GtkWidget *cancel_button;
  GtkWidget *help_button;
  GtkWidget *history_pulldown;
  GtkWidget *history_menu;
  GList     *history_list;
  GtkWidget *fileop_dialog;
  GtkWidget *fileop_entry;
  gchar     *fileop_file;
  gpointer   cmpl_state;
  
  GtkWidget *fileop_c_dir;
  GtkWidget *fileop_del_file;
  GtkWidget *fileop_ren_file;
  
  GtkWidget *button_area;
  GtkWidget *action_area;
  
};

struct _GtkFileSelection2Class
{
  GtkVBoxClass parent_class;
};


GtkType    gtk_file_selection2_get_type            (void);
GtkWidget* gtk_file_selection2_new                 ();
void       gtk_file_selection2_set_filename        (GtkFileSelection2 *filesel,
						   const gchar      *filename);
gchar*     gtk_file_selection2_get_filename        (GtkFileSelection2 *filesel);
void	   gtk_file_selection2_complete		  (GtkFileSelection2 *filesel,
						   const gchar	    *pattern);
void       gtk_file_selection2_show_fileop_buttons (GtkFileSelection2 *filesel);
void       gtk_file_selection2_hide_fileop_buttons (GtkFileSelection2 *filesel);


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* __GTK_FILESEL2_H__ */

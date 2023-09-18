/* GANG Software
 * WIDGET/gtk/widgetc/gtk_popnotebook.c
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
#include <stdio.h>
#include <memory.h>
#include <string.h>

#if defined(__sgi) && !defined(__GNUC__)
#pragma set woff 1174
#endif
#include <gtk/gtksignal.h>
#include <gtk/gtkpixmap.h>
#if defined(__sgi) && !defined(__GNUC__)
#pragma reset woff 1174
#endif


#include "gtk_popnotebook.h"

#if defined(__sgi) && !defined(__GNUC__)
#pragma set woff 3201
#endif

static void popnotebook_class_init( GtkPopNotebookClass   *klass );
static void popnotebook_init( GtkPopNotebook        *notebook );
static void reparent(
  GtkWidget *child, GtkWidget *new_parent, GtkWidget *old_parent );


GtkType
gtk_popnotebook_get_type(void)
{
  static GtkType notebook_type = 0;

  if (!notebook_type)
    {
      static const GtkTypeInfo notebook_info =
      {
        "GtkPopNotebook",
        sizeof(GtkPopNotebook),
        sizeof(GtkPopNotebookClass),
        (GtkClassInitFunc) popnotebook_class_init,
        (GtkObjectInitFunc) popnotebook_init,
        /* reserved_1 */ 0,
        /* reserved_2 */ 0,
        (GtkClassInitFunc) 0,
      };

      notebook_type = gtk_type_unique(GTK_TYPE_NOTEBOOK, &notebook_info);
      gtk_type_set_chunk_alloc(notebook_type, 16);
    }

  return notebook_type;
}

static void
popnotebook_class_init(GtkPopNotebookClass *class)
{
}

static void
popnotebook_init(GtkPopNotebook *this)
{
  /* info used by detach_attach_cb() */
  guint i;
  for ( i = 0; i < GTK_POPNOTEBOOK_MAX_PAGES; i++ )
  {
    this->counter[i].me = this;
    this->counter[i].id = i;
  }
  this->page = (GtkPopNotebookPage *)0;
  this->page_count = 0;
  this->title = (char *)0;
}

static
void
popnotebook_detach_attach_cb( GtkWidget *w, void *v )
{
  GtkPopNotebook *this = ((GtkPopNotebookCounter *)v)->me;
  guint n = ((GtkPopNotebookCounter *)v)->id;

  GtkPopNotebookPage *p = this->page + n;
  guint i;
  guint s = 0;

  if ( n >= this->page_count ) { abort(); }

  /* find position of page n in the notebook */
  for ( i = 0; i < n; i++ )
  { s += this->page[i].attached; }

  if ( p->attached )
  {
    /* is attached, so detach */
    /* NOTE: after a page is detached, another page is selected
       this can be counterintuitive
       also, when all pages are removed, what page is selected?
    */

    /* make window the new parent of frame */
    reparent( GTK_WIDGET(p->frame), GTK_WIDGET(p->window),
              GTK_WIDGET(p->vbox0));

    gtk_window_set_title( p->window, this->title );

    /* show the separate window */
    gtk_widget_show(GTK_WIDGET(p->window));

    /* remove_page() deletes the page contents (frame) and label */
    gtk_notebook_remove_page( &this->notebook, s );
  }
  else
  {
    /* is detached, so attach */

    GtkWidget *w;

    /* hide the separate window_w */
    gtk_widget_hide( GTK_WIDGET(p->window) );

    /* create and show frame
       NOTE: this should not be a memory leak, since removing
       a notebook page deletes the contents */
    w = gtk_vbox_new( 0, 0 );
    p->vbox0 = GTK_VBOX(w);
    gtk_widget_show( GTK_WIDGET(p->vbox0) );

    /* create and show tab label; */
    w = gtk_label_new( p->tab_label_text );
    /* w = gtk_label_new( "label" ); */

    p->tab_label = GTK_LABEL(w);
    gtk_widget_show( GTK_WIDGET(p->tab_label ) );

    /* insert the page contents and label */
    gtk_notebook_insert_page(
      &this->notebook, GTK_WIDGET(p->vbox0), GTK_WIDGET(p->tab_label), s );

    /* make vbox the new parent of frame */
    reparent( GTK_WIDGET(p->frame), GTK_WIDGET(p->vbox0),
              GTK_WIDGET(p->window) );

    /* go to the notebook page which was just attached */
    gtk_notebook_set_page( &this->notebook, s );

#if 0
    gtk_widget_draw( GTK_WIDGET(&this->notebook), (GdkRectangle *)0 );
#endif
  }
  p->attached = ! p->attached;
}

static
void
reparent( GtkWidget *child, GtkWidget *new_parent, GtkWidget *old_parent )
{
  /* bug in gtk_widget_reparent() caused by GtkScrolledWindow */
  gtk_widget_ref(child);
  gtk_container_remove(GTK_CONTAINER(old_parent), child);
  gtk_container_add(GTK_CONTAINER(new_parent), child);
  gtk_widget_unref(child);
}

static
gint
popnotebook_delete_event_cb(GtkWidget *w, GdkEvent *e, gpointer p )
{
  popnotebook_detach_attach_cb( w, p );
  return TRUE; /* don't destroy */
}


#if 0
static
void
popnotebook_add_pixmap(
  GtkPopNotebook *this,
  char const * const *xpm,
  GtkContainer *container,
  GtkWindow *window )
{
  GdkBitmap *mask;
  GtkStyle *style = gtk_widget_get_style( GTK_WIDGET(window) );

  GdkPixmap *pixmap = gdk_pixmap_create_from_xpm_d(
    GTK_WIDGET(window)->window, &mask,
    &style->bg[GTK_STATE_NORMAL],
    (gchar **)xpm
    );

  GtkWidget *pixmapw = gtk_pixmap_new( pixmap, mask );
  gtk_widget_show( pixmapw );

  gtk_container_add(container, pixmapw);
}
#endif

GtkWidget*
gtk_popnotebook_new()
{
  return GTK_WIDGET(gtk_type_new(gtk_popnotebook_get_type()));
}

void gtk_popnotebook_add(
  GtkPopNotebook *this,
  GtkWidget *child )
{
  /* TO DO: MEMORY LEAK - memory not freed when the popnotebook is destroyed */
  /* TO DO: Tooltip for button */
  /* TO DO: methods other than popnotebook_append_page */
  /* TO DO: ability to remove a page, etc */

    /*
    this->notebook
      p->vbox0
        p->frame
          p->vbox
            p->hbox
              p->button
            child
  */

  GtkWidget *w;
  GtkPopNotebookPage *p;
  int n = this->page_count;

  /* GtkPopNotebookPage *t; */

  if ( this->page_count >= GTK_POPNOTEBOOK_MAX_PAGES ) { abort(); }

  /* re-allocate page, adding one GtkPopNotebookPage */
  /* NOTE: memory leak (this memory never gets freed */
  if ( n == 0 )
  {
    this->page = (GtkPopNotebookPage *)malloc( sizeof(GtkPopNotebookPage) );
  }
  else
  {
    this->page = (GtkPopNotebookPage *)realloc(
      this->page, (n+1) * sizeof(GtkPopNotebookPage) );
  }
  
  p = this->page + n;

  p->tab_label_text = (char *)0;
  p->label_text = (char *)0;

#if 0
  p->tab_label_text = strdup( tab_label_text );
  p->label_text = strdup( label_text );
#endif
  /* create and show vbox; */
  w = gtk_vbox_new(0, 0);
  p->vbox0 = GTK_VBOX(w);
  gtk_widget_show( GTK_WIDGET(p->vbox0) );
#if 0
  /* create and show tab label */
  w = gtk_label_new( p->tab_label_text );
  p->tab_label = GTK_LABEL(w);
  gtk_widget_show( GTK_WIDGET(p->tab_label ) );

  /* put vbox into notebook */
  gtk_notebook_append_page( &this->notebook, GTK_WIDGET(p->vbox0),
                            GTK_WIDGET(p->tab_label) );
#endif
  gtk_container_add( GTK_CONTAINER(&this->notebook), GTK_WIDGET(p->vbox0) );

  /* create and show frame; put frame into vbox0 */
  w = gtk_frame_new( (gchar *)0 );
  p->frame = GTK_FRAME(w);
  gtk_widget_show( GTK_WIDGET(p->frame ) );
  gtk_box_pack_start( GTK_BOX(p->vbox0), GTK_WIDGET(p->frame),
                      1, 1, 0);

  /* create and show vbox; put vbox into frame */
  w = gtk_vbox_new( 0, 0 );
  p->vbox = GTK_VBOX(w);
  gtk_widget_show( GTK_WIDGET(p->vbox) );
  gtk_container_add( GTK_CONTAINER(p->frame), GTK_WIDGET(p->vbox) );

  /* create and show hbox; put hbox into vbox */
  w = gtk_hbox_new( 0, 0 );
  p->hbox = GTK_HBOX(w);
  gtk_widget_show( GTK_WIDGET(p->hbox) );
  gtk_box_pack_start( GTK_BOX(p->vbox), GTK_WIDGET(p->hbox),
                      0, 0, 0 );
  gtk_widget_set_usize( w, 10, 10);

  /* create and show label; align label; put label into hbox */
  /*  w = gtk_label_new( p->label_text ); */
  w = gtk_label_new( "" );
  p->label = GTK_LABEL(w);
  gtk_widget_show( GTK_WIDGET(p->label) );
  gtk_misc_set_alignment( GTK_MISC(p->label), 0.0, 0.5 );
  gtk_box_pack_start( GTK_BOX(p->hbox), GTK_WIDGET(p->label),
                      1, 1, 0);
  gtk_widget_set_usize( w, 10, 10);

  /* create and show button; put button into hbox */
  w = gtk_button_new_with_label("");
  gtk_widget_set_usize( w, 10, 10);

  p->button = GTK_BUTTON(w);
  gtk_widget_show( GTK_WIDGET(p->button) );
  gtk_box_pack_start( GTK_BOX(p->hbox), GTK_WIDGET(p->button),
                      0, 0, 0 );

  /* connect a callback to the button */
  gtk_signal_connect(GTK_OBJECT(p->button), "clicked",
                     GTK_SIGNAL_FUNC(popnotebook_detach_attach_cb),
                     this->counter + n);

  p->attached = 1;

  /* put the child into vbox */
  /* NOTE:
     the child is packed into vbox with expand==false, fill==false.
     To set otherwise, use set_child_packing()
  */
  p->child = child;
  gtk_box_pack_start( GTK_BOX(p->vbox), child, 0, 0, 0 );

#if 0
  /* pixmaps on buttons */
  popnotebook_add_pixmap( this, button_xpm, GTK_CONTAINER(p->button), main_window );
#endif
  /* create a new window */
  w = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  p->window = GTK_WINDOW(w);

  /* window signal_connects */
  gtk_signal_connect(
    GTK_OBJECT(p->window), "delete_event",
    GTK_SIGNAL_FUNC(popnotebook_delete_event_cb), this->counter + n);

#if 0
  gtk_signal_connect(
    GTK_OBJECT(p->window), "destroy",
    GTK_SIGNAL_FUNC(popnotebook_detach_destroy_cb), 0);
#endif

#if 0
    /* tooltip for button */
     ( "Detach/attach this notebook page", (char *)0 );
#endif

  this->page_count++;
}

void gtk_popnotebook_set_tab_label(
  GtkPopNotebook *this,
  GtkWidget *child,
  GtkWidget *tab_label)
{
  char *s = (char *)0;

  /* find child */
  guint i;
  for ( i = 0; i < this->page_count; i++ ) {
    if ( gtk_notebook_get_nth_page(&this->notebook, i) == child ) {
      break;
    }
  }

  /* get label */
  gtk_label_get( GTK_LABEL(tab_label), &s );

  /* TO DO: memory leak */
  this->page[i].tab_label_text = strdup(s);

  /* set notebook label */
  gtk_notebook_set_tab_label(&this->notebook, child, tab_label);


  /* the label on the page */
  this->page[i].label_text = this->page[i].tab_label_text;
  gtk_label_set_text( this->page[i].label, this->page[i].label_text );
}

void gtk_popnotebook_add_with_label(
  GtkPopNotebook *this,
  GtkWidget *child,
  GtkWidget *tab_label )
{
  GtkWidget *w;

  gtk_popnotebook_add( this, child );
  w = gtk_notebook_get_nth_page( GTK_NOTEBOOK(this), this->page_count - 1 );
  gtk_popnotebook_set_tab_label( this, w, tab_label );
}

void gtk_popnotebook_set_title(GtkPopNotebook *popnotebook, char const *title )
{
  popnotebook->title = title;
}

void gtk_popnotebook_set_packing(
  GtkPopNotebook *this, guint pageno,
  gboolean expand, gboolean fill, guint padding, GtkPackType pack_type )
{
  GtkPopNotebookPage p = this->page[pageno];
  gtk_box_set_child_packing( GTK_BOX(p.vbox), p.child,
                             expand, fill, padding, pack_type );

}

#if defined(__sgi) && !defined(__GNUC__)
#pragma reset woff 3201
#endif

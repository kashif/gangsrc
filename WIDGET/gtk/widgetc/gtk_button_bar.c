/* GANG Software
 * WIDGET/gtk/widgetc/gtk_button_bar.c
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

#include <stdlib.h>

#if defined(__sgi) && !defined(__GNUC__)
#pragma set woff 1174
#endif
#include <gtk/gtksignal.h>
#include <gtk/gtklabel.h>
#if defined(__sgi) && !defined(__GNUC__)
#pragma reset woff 1174
#endif

#include "gtk_button_bar.h"

#if defined(__sgi) && !defined(__GNUC__)
#pragma set woff 3187,3201
#endif

static void buttonbar_class_init(GtkButtonBarClass *klass);
static void buttonbar_init(GtkButtonBar *table);

GtkType
gtk_button_bar_get_type (void)
{
  static GtkType table_type = 0;

  if (!table_type)
    {
      static const GtkTypeInfo table_info =
      {
        "GtkButtonBar",
        sizeof (GtkButtonBar),
        sizeof (GtkButtonBarClass),
        (GtkClassInitFunc) buttonbar_class_init,
        (GtkObjectInitFunc) buttonbar_init,
        /* reserved_1 */ 0,
        /* reserved_2 */ 0,
        (GtkClassInitFunc) 0,
      };

      table_type = gtk_type_unique (GTK_TYPE_TABLE, &table_info);
      gtk_type_set_chunk_alloc (table_type, 16);
    }

  return table_type;
}
enum {
  BUTTON_BAR_SIGNAL,
  LAST_SIGNAL
};

static guint buttonbar_signals[LAST_SIGNAL] = { 0 };

static void
buttonbar_class_init (GtkButtonBarClass *class)
{
  GtkObjectClass *object_class;

  object_class = (GtkObjectClass*) class;

  buttonbar_signals[BUTTON_BAR_SIGNAL] =
    gtk_signal_new("toggled0",
                   GTK_RUN_FIRST,
                   GTK_TYPE_OBJECT,
                   GTK_SIGNAL_OFFSET(GtkButtonBarClass, f),
                   gtk_signal_default_marshaller, GTK_TYPE_NONE, 0);

  gtk_object_class_add_signals(object_class, buttonbar_signals, LAST_SIGNAL);

  class->f = 0;
}

static void
buttonbar_init (GtkButtonBar *this)
{
  this->button = (GtkRadioButton **)0;
  this->count = 0;
}

static
void
gtk_button_bar_cb( GtkWidget *w, void *v )
{
  GtkButtonBar *this = GTK_BUTTON_BAR(v);

  /* emit "toggled" signal */
  gtk_signal_emit( GTK_OBJECT(this), buttonbar_signals[BUTTON_BAR_SIGNAL] );
}

GtkWidget*
gtk_button_bar_new(
  guint rows,
  guint cols )
{
  GtkRadioButton *group = (GtkRadioButton *)0;

  GtkWidget *w = gtk_type_new(gtk_button_bar_get_type());
  GtkButtonBar *this = GTK_BUTTON_BAR(w);

  guint i;
  guint x, y;

  this->count = rows*cols;

  gtk_table_set_homogeneous( &this->table, 1 );

  /* NOTE: memory leak */
  this->button = (GtkRadioButton **)
    malloc( this->count * sizeof( GtkRadioButton *) );
 
  for ( i = 0; i < this->count; i++ )
  {
    
    /* set the group */
    if ( i == 1 ) { group = this->button[0]; }

    /* create a new button */
    this->button[i] = GTK_RADIO_BUTTON(
      gtk_radio_button_new_from_widget(group) );

    /* connect a callback to the button */
    gtk_signal_connect(GTK_OBJECT(this->button[i]), "released",
                       GTK_SIGNAL_FUNC(gtk_button_bar_cb),
                       this);

    /* make the button look like a togglebutton, not a check button */
    gtk_toggle_button_set_mode( GTK_TOGGLE_BUTTON(this->button[i]), FALSE );
    gtk_widget_show(GTK_WIDGET(this->button[i]));

    x = i % cols;
    y = i / cols;
    gtk_table_attach( &this->table, GTK_WIDGET(this->button[i]),
                      x, x+1, y, y+1,
                      (GtkAttachOptions)(GTK_EXPAND|GTK_FILL),
                      (GtkAttachOptions)(GTK_EXPAND|GTK_FILL),
                      0, 0 );
  }
  if ( this->count > 0 )
  {
    gtk_toggle_button_set_active(
      GTK_TOGGLE_BUTTON(this->button[0]), TRUE );
  }
  return w;
}

void gtk_button_bar_set( GtkButtonBar *this, guint id )
{
  gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( this->button[id] ), TRUE );
}

guint gtk_button_bar_get_value( GtkButtonBar *this )
{
  /* Can't just look through buttons to see which is pressed,
     because the button just pressed doesn't know it's active yet */

  guint i;
  for ( i = 0; i < this->count; i++ )
  {
    if ( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON( this->button[i]) ))
    { return i; }
  }
  /* error: no buttons are pressed */
  return i;
}

void
gtk_button_bar_set_labels(
  GtkButtonBar *this, char const *text[] )
{
  GtkWidget *label;

  guint i;
  for ( i = 0; i < this->count; i++ )
  {
    /* NOTE memory leak */
    label = gtk_label_new( text[i] );
    gtk_widget_show(label);

    gtk_container_add( GTK_CONTAINER(this->button[i]), label );
  }
}

void
gtk_button_bar_set_sensitive(
  GtkButtonBar *this, guint id, gboolean state )
{
  gtk_widget_set_sensitive( GTK_WIDGET(this->button[id]), state );
}

void
gtk_button_bar_show(
  GtkButtonBar *this, guint id, gboolean state )
{
  if (state)
  {
    gtk_widget_show( GTK_WIDGET(this->button[id]) );
  }
  else
  {
    gtk_widget_hide( GTK_WIDGET(this->button[id]) );
  }
}

#if defined(__sgi) && !defined(__GNUC__)
#pragma reset woff 3201
#endif

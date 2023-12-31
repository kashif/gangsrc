/* GANG Software
 * WIDGET/gtk/widget0/Container.H
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
// generated by gtk2c++

#ifndef gtk_widget0_Container_INCLUDED
#define gtk_widget0_Container_INCLUDED

#include "Widget.H"

namespace gtk {
namespace widget0 {

class Container : public Widget
{
public:
  virtual void add( Widget *x )
    { gtk_container_add( GTK_CONTAINER(w()), x->w() ); }
  void remove( Widget *x )
    { remove( x->w() ); }

  void set_border_width( uint border_width )
    { gtk_container_set_border_width( GTK_CONTAINER(w()), border_width ); }
  void add( GtkWidget *widget )
    { gtk_container_add( GTK_CONTAINER(w()), widget ); }
  void remove( GtkWidget *widget )
    { gtk_container_remove( GTK_CONTAINER(w()), widget ); }
  void set_resize_mode( GtkResizeMode resize_mode )
    { gtk_container_set_resize_mode( GTK_CONTAINER(w()), resize_mode ); }
  void check_resize()
    { gtk_container_check_resize( GTK_CONTAINER(w())); }
  void foreach( GtkCallback callback, gpointer callback_data )
    { gtk_container_foreach( GTK_CONTAINER(w()), callback, callback_data ); }
  void foreach_full( GtkCallback callback, GtkCallbackMarshal marshal, gpointer callback_data, GtkDestroyNotify notify )
    { gtk_container_foreach_full( GTK_CONTAINER(w()), callback, marshal, callback_data, notify ); }
  GList* children()
    { return gtk_container_children( GTK_CONTAINER(w())); }
  int focus( GtkDirectionType direction )
    { return gtk_container_focus( GTK_CONTAINER(w()), direction ); }
  void set_reallocate_redraws( bool needs_redraws )
    { gtk_container_set_reallocate_redraws( GTK_CONTAINER(w()), needs_redraws ); }
  void set_focus_child( GtkWidget *child )
    { gtk_container_set_focus_child( GTK_CONTAINER(w()), child ); }
  void set_focus_vadjustment( GtkAdjustment *adjustment )
    { gtk_container_set_focus_vadjustment( GTK_CONTAINER(w()), adjustment ); }
  void set_focus_hadjustment( GtkAdjustment *adjustment )
    { gtk_container_set_focus_hadjustment( GTK_CONTAINER(w()), adjustment ); }
#if 0
  void register_toplevel()
    { gtk_container_register_toplevel( GTK_CONTAINER(w())); }
  void unregister_toplevel()
    { gtk_container_unregister_toplevel( GTK_CONTAINER(w())); }
#endif
#if 0
  GList* get_toplevels()
    { return gtk_container_get_toplevels( GTK_CONTAINER(w())); }
#endif
  void resize_children()
    { gtk_container_resize_children( GTK_CONTAINER(w())); }
  GtkType child_type()
    { return gtk_container_child_type( GTK_CONTAINER(w())); }
#if 0
  void add_child_arg_type( GtkType arg_type, uint arg_flags, uint arg_id )
    { gtk_container_add_child_arg_type( GTK_CONTAINER(w()), arg_type, arg_flags, arg_id ); }
  GtkArg* query_child_args( guint32 **arg_flags, uint *nargs )
    { return gtk_container_query_child_args( GTK_CONTAINER(w()), arg_flags, nargs ); }
#endif
  void child_getv( GtkWidget *child, uint n_args, GtkArg *args )
    { gtk_container_child_getv( GTK_CONTAINER(w()), child, n_args, args ); }
  void child_setv( GtkWidget *child, uint n_args, GtkArg *args )
    { gtk_container_child_setv( GTK_CONTAINER(w()), child, n_args, args ); }
  void add_with_args( GtkWidget *widget, char const *first_arg_name, ... )
    { gtk_container_add_with_args( GTK_CONTAINER(w()), widget, first_arg_name, first_arg_name ); }
  void addv( GtkWidget *widget, uint n_args, GtkArg *args )
    { gtk_container_addv( GTK_CONTAINER(w()), widget, n_args, args ); }
  void child_set( GtkWidget *child, char const *first_arg_name, ... )
    { gtk_container_child_set( GTK_CONTAINER(w()), child, first_arg_name, first_arg_name ); }
  void queue_resize()
    { gtk_container_queue_resize( GTK_CONTAINER(w())); }
  void clear_resize_widgets()
    { gtk_container_clear_resize_widgets( GTK_CONTAINER(w())); }
  void arg_set( GtkWidget *child, GtkArg *arg, GtkArgInfo *info )
    { gtk_container_arg_set( GTK_CONTAINER(w()), child, arg, info ); }
  void arg_get( GtkWidget *child, GtkArg *arg, GtkArgInfo *info )
    { gtk_container_arg_get( GTK_CONTAINER(w()), child, arg, info ); }
#if 0
  char* child_args_collect( GSList **arg_list_p, GSList **info_list_p, char const *first_arg_name, va_list args )
    { return gtk_container_child_args_collect( GTK_CONTAINER(w()), arg_list_p, info_list_p, first_arg_name, args ); }
  char* child_arg_get_info( char const *arg_name, GtkArgInfo **info_p )
    { return gtk_container_child_arg_get_info( GTK_CONTAINER(w()), arg_name, info_p ); }
#endif
  void forall( GtkCallback callback, gpointer callback_data )
    { gtk_container_forall( GTK_CONTAINER(w()), callback, callback_data ); }
  char* child_composite_name( GtkWidget *child )
    { return gtk_container_child_composite_name( GTK_CONTAINER(w()), child ); }
  void dequeue_resize_handler()
    { gtk_container_dequeue_resize_handler( GTK_CONTAINER(w())); }

protected:
  Container( GtkWidget *x ) : Widget(x) {}
};

} // namespace widget0
} // namespace gtk

#endif // gtk_widget0_Container_INCLUDED

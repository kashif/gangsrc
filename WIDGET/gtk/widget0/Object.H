/* GANG Software
 * WIDGET/gtk/widget0/Object.H
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

#ifndef gtk_widget0_Object_INCLUDED
#define gtk_widget0_Object_INCLUDED

#if defined(__sgi) && !defined(__GNUG__)
#pragma set woff 1174
#endif
#include <gtk/gtk.h>
#if defined(__sgi) && !defined(__GNUG__)
#pragma reset woff 1174
#endif

namespace gtk {
namespace widget0 {

class Object
{
public:
  virtual ~Object()
    {
#if 0
      // NOTE: causes various crashes: what's correct here?
      // NOTE: destroying GtkText writes an error message
      //   "Gtk-WARNING **: horizontal scrolling not implemented"
      if ( ! GTK_IS_TEXT(w()) ) { destroy(); }
//      { destroy(); }
#endif
    }

  void destroy()
    { gtk_object_destroy( w() ); }

#if 0
  void default_construct()
    { default_construct( GTK_OBJECT(w())); }
  void constructed()
    { constructed( GTK_OBJECT(w())); }
  void sink()
    { sink( GTK_OBJECT(w())); }
  void ref()
    { ref( GTK_OBJECT(w())); }
  void unref()
    { unref( GTK_OBJECT(w())); }
  void weakref( GtkDestroyNotify notify, gpointer data )
    { weakref( GTK_OBJECT(w()), notify, data ); }
  void weakunref( GtkDestroyNotify notify, gpointer data )
    { weakunref( GTK_OBJECT(w()), notify, data ); }
  void getv( uint n_args, GtkArg *args )
    { getv( GTK_OBJECT(w()), n_args, args ); }
  void get( char const *first_arg_name, ... )
    { get( GTK_OBJECT(w()), first_arg_name, first_arg_name ); }
  void set( char const *first_arg_name, ... )
    { set( GTK_OBJECT(w()), first_arg_name, first_arg_name ); }
  void setv( uint n_args, GtkArg *args )
    { setv( GTK_OBJECT(w()), n_args, args ); }
  void set_data( char const *key, gpointer data )
    { set_data( GTK_OBJECT(w()), key, data ); }
  void set_data_full( char const *key, gpointer data, GtkDestroyNotify destroy )
    { set_data_full( GTK_OBJECT(w()), key, data, destroy ); }
  void remove_data( char const *key )
    { remove_data( GTK_OBJECT(w()), key ); }
  gpointer get_data( char const *key )
    { return get_data( GTK_OBJECT(w()), key ); }
  void remove_no_notify( char const *key )
    { remove_no_notify( GTK_OBJECT(w()), key ); }
  void set_user_data( gpointer data )
    { set_user_data( GTK_OBJECT(w()), data ); }
  gpointer get_user_data()
    { return get_user_data( GTK_OBJECT(w())); }
  void class_add_signals( uint *signals, uint nsignals )
    { class_add_signals( GTK_OBJECT(w()), signals, nsignals ); }
  void add_arg_type( GtkType arg_type, uint arg_flags, uint arg_id )
    { add_arg_type( GTK_OBJECT(w()), arg_type, arg_flags, arg_id ); }
  void set_data_by_id( GQuark data_id, gpointer data )
    { set_data_by_id( GTK_OBJECT(w()), data_id, data ); }
  void set_data_by_id_full( GQuark data_id, gpointer data, GtkDestroyNotify destroy )
    { set_data_by_id_full( GTK_OBJECT(w()), data_id, data, destroy ); }
  gpointer get_data_by_id( GQuark data_id )
    { return get_data_by_id( GTK_OBJECT(w()), data_id ); }
  void remove_data_by_id( GQuark data_id )
    { remove_data_by_id( GTK_OBJECT(w()), data_id ); }
  void remove_no_notify_by_id( GQuark key_id )
    { remove_no_notify_by_id( GTK_OBJECT(w()), key_id ); }
  void arg_set( GtkArg *arg, GtkArgInfo *info )
    { arg_set( GTK_OBJECT(w()), arg, info ); }
  void arg_get( GtkArg *arg, GtkArgInfo *info )
    { arg_get( GTK_OBJECT(w()), arg, info ); }
  void gtk_trace_referencing( char const *func, uint dummy, uint line, bool do_ref )
    { gtk_trace_referencing( GTK_OBJECT(w()), func, dummy, line, do_ref ); }
#endif
  GtkObject *w() { return _w; }
  GtkObject const *w() const { return _w; }

  GtkObject *_w;
protected:
  Object( GtkObject *x ) { _w = x; }

};

} // namespace widget0
} // namespace gtk

#endif // gtk_widget0_Object_INCLUDED

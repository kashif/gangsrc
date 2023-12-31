/* GANG Software
 * WIDGET/gtk/widget0/CList.H
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

#ifndef gtk_widget0_CList_INCLUDED
#define gtk_widget0_CList_INCLUDED

#include "widget/ui/List.H"
#include "Container.H"

namespace gtk {
namespace widget0 {

class CList
  :
    public widget::ui::List,
    public Container
{
public:
  CList( int columns ) :
      Container( gtk_clist_new( columns ) ) {}
  CList( int columns, char *titles[] ) :
      Container( gtk_clist_new_with_titles( columns, titles ) ) {}

  uint rows() const { return GTK_CLIST(w())->rows; }
  void set_column_widget( int column, Widget *x )
    { set_column_widget( column, x->w() ); }

  // returns true iff an item is selected
  bool selected() const
    {
      GtkCList *c = GTK_CLIST(w());
      GList *L = c->selection;
      return ( L != (GList *)0 );
    }

  uint selected_row() const
    {
      // NOTE: assumes only one item is selected
      GtkCList *c = GTK_CLIST(w());
      GList *L = c->selection;
      if ( L == (GList *)0 ) { return (uint)-1; }
      
      // NOTE
      return (uint)(int unsigned long)L->data;
    }

  virtual bool showing( uint n ) const
    { WARN(); return true; }
  virtual void show( bool state = true )
    { Widget::show(state); }
  virtual void show( uint n, bool state )
    { WARN(); }
  virtual void set_sensitive( uint n, bool state )
    { WARN(); }

  virtual uint item_count() const
    { return rows(); }
  virtual void append(char const *label)
    { append(&label); }
  virtual void set( uint n )
    { select_row(n, 0); }
  virtual uint get() const
    { return selected_row(); }

  void construct( int columns, char *titles[] )
    { gtk_clist_construct( GTK_CLIST(w()), columns, titles ); }
  void set_hadjustment( GtkAdjustment *adjustment )
    { gtk_clist_set_hadjustment( GTK_CLIST(w()), adjustment ); }
  void set_vadjustment( GtkAdjustment *adjustment )
    { gtk_clist_set_vadjustment( GTK_CLIST(w()), adjustment ); }
  GtkAdjustment* get_hadjustment()
    { return gtk_clist_get_hadjustment( GTK_CLIST(w())); }
  GtkAdjustment* get_vadjustment()
    { return gtk_clist_get_vadjustment( GTK_CLIST(w())); }
  void set_shadow_type( GtkShadowType type )
    { gtk_clist_set_shadow_type( GTK_CLIST(w()), type ); }
  void set_selection_mode( GtkSelectionMode mode )
    { gtk_clist_set_selection_mode( GTK_CLIST(w()), mode ); }
  void set_reorderable( bool reorderable )
    { gtk_clist_set_reorderable( GTK_CLIST(w()), reorderable ); }
  void set_use_drag_icons( bool use_icons )
    { gtk_clist_set_use_drag_icons( GTK_CLIST(w()), use_icons ); }
  void set_button_actions( uint button, guint8 button_actions )
    { gtk_clist_set_button_actions( GTK_CLIST(w()), button, button_actions ); }
  void freeze()
    { gtk_clist_freeze( GTK_CLIST(w())); }
  void thaw()
    { gtk_clist_thaw( GTK_CLIST(w())); }
  void column_titles_show()
    { gtk_clist_column_titles_show( GTK_CLIST(w())); }
  void column_titles_hide()
    { gtk_clist_column_titles_hide( GTK_CLIST(w())); }
  void column_title_active( int column )
    { gtk_clist_column_title_active( GTK_CLIST(w()), column ); }
  void column_title_passive( int column )
    { gtk_clist_column_title_passive( GTK_CLIST(w()), column ); }
  void column_titles_active()
    { gtk_clist_column_titles_active( GTK_CLIST(w())); }
  void column_titles_passive()
    { gtk_clist_column_titles_passive( GTK_CLIST(w())); }
  void set_column_title( int column, char const *title )
    { gtk_clist_set_column_title( GTK_CLIST(w()), column, title ); }
  void set_column_widget( int column, GtkWidget *widget )
    { gtk_clist_set_column_widget( GTK_CLIST(w()), column, widget ); }
  void set_column_justification( int column, GtkJustification justification )
    { gtk_clist_set_column_justification( GTK_CLIST(w()), column, justification ); }
  void set_column_visibility( int column, bool visible )
    { gtk_clist_set_column_visibility( GTK_CLIST(w()), column, visible ); }
  void set_column_resizeable( int column, bool resizeable )
    { gtk_clist_set_column_resizeable( GTK_CLIST(w()), column, resizeable ); }
  void set_column_auto_resize( int column, bool auto_resize )
    { gtk_clist_set_column_auto_resize( GTK_CLIST(w()), column, auto_resize ); }
  int columns_autosize()
    { return gtk_clist_columns_autosize( GTK_CLIST(w())); }
  int optimal_column_width( int column )
    { return gtk_clist_optimal_column_width( GTK_CLIST(w()), column ); }
  void set_column_width( int column, int width )
    { gtk_clist_set_column_width( GTK_CLIST(w()), column, width ); }
  void set_column_min_width( int column, int min_width )
    { gtk_clist_set_column_min_width( GTK_CLIST(w()), column, min_width ); }
  void set_column_max_width( int column, int max_width )
    { gtk_clist_set_column_max_width( GTK_CLIST(w()), column, max_width ); }
  void set_row_height( uint height )
    { gtk_clist_set_row_height( GTK_CLIST(w()), height ); }
  void moveto( int row, int column, float row_align, float col_align )
    { gtk_clist_moveto( GTK_CLIST(w()), row, column, row_align, col_align ); }
  GtkVisibility row_is_visible( int row )
    { return gtk_clist_row_is_visible( GTK_CLIST(w()), row ); }
  GtkCellType get_cell_type( int row, int column )
    { return gtk_clist_get_cell_type( GTK_CLIST(w()), row, column ); }
  void set_text( int row, int column, char const *text )
    { gtk_clist_set_text( GTK_CLIST(w()), row, column, text ); }
  int get_text( int row, int column, char **text )
    { return gtk_clist_get_text( GTK_CLIST(w()), row, column, text ); }
  void set_pixmap( int row, int column, GdkPixmap *pixmap, GdkBitmap *mask )
    { gtk_clist_set_pixmap( GTK_CLIST(w()), row, column, pixmap, mask ); }
  int get_pixmap( int row, int column, GdkPixmap **pixmap, GdkBitmap **mask )
    { return gtk_clist_get_pixmap( GTK_CLIST(w()), row, column, pixmap, mask ); }
  void set_pixtext( int row, int column, char const *text, guint8 spacing, GdkPixmap *pixmap, GdkBitmap *mask )
    { gtk_clist_set_pixtext( GTK_CLIST(w()), row, column, text, spacing, pixmap, mask ); }
  int get_pixtext( int row, int column, char **text, guint8 *spacing, GdkPixmap **pixmap, GdkBitmap **mask )
    { return gtk_clist_get_pixtext( GTK_CLIST(w()), row, column, text, spacing, pixmap, mask ); }
  void set_foreground( int row, GdkColor *color )
    { gtk_clist_set_foreground( GTK_CLIST(w()), row, color ); }
  void set_background( int row, GdkColor *color )
    { gtk_clist_set_background( GTK_CLIST(w()), row, color ); }
  void set_cell_style( int row, int column, GtkStyle *style )
    { gtk_clist_set_cell_style( GTK_CLIST(w()), row, column, style ); }
  void set_row_style( int row, GtkStyle *style )
    { gtk_clist_set_row_style( GTK_CLIST(w()), row, style ); }
  void set_shift( int row, int column, int vertical, int horizontal )
    { gtk_clist_set_shift( GTK_CLIST(w()), row, column, vertical, horizontal ); }
  void set_selectable( int row, bool selectable )
    { gtk_clist_set_selectable( GTK_CLIST(w()), row, selectable ); }
  bool get_selectable( int row )
    { return gtk_clist_get_selectable( GTK_CLIST(w()), row ); }
  int prepend( char const *text[] )
    { return gtk_clist_prepend( GTK_CLIST(w()), (char **)text ); }
  int append( char const *text[] )
    { return gtk_clist_append( GTK_CLIST(w()), (char **)text ); }
  int insert( int row, char const *text[] )
    { return gtk_clist_insert( GTK_CLIST(w()), row, (char **)text ); }
  void remove( uint row )
    { gtk_clist_remove( GTK_CLIST(w()), row ); }
  void set_row_data( int row, gpointer data )
    { gtk_clist_set_row_data( GTK_CLIST(w()), row, data ); }
  void set_row_data_full( int row, gpointer data, GtkDestroyNotify destroy )
    { gtk_clist_set_row_data_full( GTK_CLIST(w()), row, data, destroy ); }
  gpointer get_row_data( int row )
    { return gtk_clist_get_row_data( GTK_CLIST(w()), row ); }
  int find_row_from_data( gpointer data )
    { return gtk_clist_find_row_from_data( GTK_CLIST(w()), data ); }
  void select_row( int row, int column )
    { gtk_clist_select_row( GTK_CLIST(w()), row, column ); }
  void unselect_row( int row, int column )
    { gtk_clist_unselect_row( GTK_CLIST(w()), row, column ); }
  void undo_selection()
    { gtk_clist_undo_selection( GTK_CLIST(w())); }
  void clear()
    { gtk_clist_clear( GTK_CLIST(w())); }
  int get_selection_info( int x, int y, int *row, int *column )
    { return gtk_clist_get_selection_info( GTK_CLIST(w()), x, y, row, column ); }
  void select_all()
    { gtk_clist_select_all( GTK_CLIST(w())); }
  void unselect_all()
    { gtk_clist_unselect_all( GTK_CLIST(w())); }
  void swap_rows( int row1, int row2 )
    { gtk_clist_swap_rows( GTK_CLIST(w()), row1, row2 ); }
  void row_move( int source_row, int dest_row )
    { gtk_clist_row_move( GTK_CLIST(w()), source_row, dest_row ); }
  void set_compare_func( GtkCListCompareFunc cmp_func )
    { gtk_clist_set_compare_func( GTK_CLIST(w()), cmp_func ); }
  void set_sort_column( int column )
    { gtk_clist_set_sort_column( GTK_CLIST(w()), column ); }
  void set_sort_type( GtkSortType sort_type )
    { gtk_clist_set_sort_type( GTK_CLIST(w()), sort_type ); }
  void sort()
    { gtk_clist_sort( GTK_CLIST(w())); }
  void set_auto_sort( bool auto_sort )
    { gtk_clist_set_auto_sort( GTK_CLIST(w()), auto_sort ); }

protected:
  CList( GtkWidget *x ) : Container(x) {}
};

} // namespace widget0
} // namespace gtk

#endif // gtk_widget0_CList_INCLUDED

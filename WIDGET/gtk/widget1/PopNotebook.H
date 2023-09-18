/* GANG Software
 * WIDGET/gtk/widget1/PopNotebook.H
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

#ifndef gtk_widget1_PopNotebook_INCLUDED
#define gtk_widget1_PopNotebook_INCLUDED

#include "gtk/widgetc/gtk_popnotebook.h"
#include "gtk/widget0/Notebook.H"
#include "gtk/widget0/Label.H"

namespace gtk {
namespace widget1 {

/*
   GTK Notebook with detachable pages.
*/
class PopNotebook : public gtk::widget0::Notebook
{
public:
  PopNotebook() :
      gtk::widget0::Notebook( gtk_popnotebook_new() ) {}
  void set( uint page )
    { set_page(page); }
  uint get() const
    { return get_current_page(); }

  void add( gtk::widget0::Widget *x )
    { gtk_popnotebook_add( GTK_POPNOTEBOOK(w()), x->w() ); }
  void add( gtk::widget0::Widget *x, gtk::widget0::Label *l );
  void add( gtk::widget0::Widget *x, char const *tab_label );
  virtual void label( uint page, gtk::widget0::Widget *x )
    { gtk_popnotebook_set_tab_label( GTK_POPNOTEBOOK(w()),
                                     get_nth_page(page), x->w()); }
  void set_title( char const *title )
    { gtk_popnotebook_set_title( GTK_POPNOTEBOOK(w()), title ); }

  virtual bool showing( uint n ) const
    { return ::gtk::widget0::Notebook::showing(n); }
  virtual void set_sensitive( uint n, bool state )
    { ::gtk::widget0::Notebook::set_sensitive(n, state); }

  void set_packing( guint page, gboolean expand, gboolean fill, guint padding,
                    GtkPackType pack_type )
    { gtk_popnotebook_set_packing( GTK_POPNOTEBOOK(w()), page, expand, fill,
                                   padding, pack_type ); }

private:
  uint _label_page;
};


} // namespace widget1
} // namespace gtk

#endif // gtk_widget1_PopNotebook_INCLUDED

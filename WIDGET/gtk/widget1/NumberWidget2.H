/* GANG Software
 * WIDGET/gtk/widget1/NumberWidget2.H
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

#ifndef gtk_widget1_NumberWidget2_INCLUDED
#define gtk_widget1_NumberWidget2_INCLUDED

#include "gtk/widget0/Frame.H"
#include "gtk/widget0/VBox.H"
#include "NumberWidget.H"

namespace gtk {
namespace widget1 {

class NumberWidget2
  :
    public gtk::widget0::Frame
{
public:

  // constructor
  NumberWidget2(
    char const *frame_label,
    numberwidget_config const config[],
    uint count );

  // destructor
  virtual ~NumberWidget2();

  virtual void set( float const a[] );
  virtual void set( int const a[] );
  void get( float a[] ) const;
  void get( int a[] ) const;

  GtkAdjustment *adjustment(uint i)
    { return gtk_numberwidget_get_adjustment(
      GTK_NUMBERWIDGET(_numberwidget[i]->w() )); }

  void _connect( gpointer obj, GtkSignalFunc fn );
  void _block( gpointer obj );
  void _unblock( gpointer obj );

  uint count() const
    { return _count; }

  void set_sensitive( bool state )
    { gtk::widget0::Widget::set_sensitive(state); }
  void set_sensitive( uint n, bool state );

protected:

private:

  gtk::widget0::VBox *_vbox;
  unsigned int _count;
  NumberWidget **_numberwidget;

  NumberWidget2( NumberWidget2 const & );
  NumberWidget2 &operator=( NumberWidget2 const & );
};

} // namespace widget1
} // namespace gtk

#endif // gtk_widget1_NumberWidget2_INCLUDED

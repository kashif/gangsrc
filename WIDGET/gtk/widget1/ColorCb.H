/* GANG Software
 * WIDGET/gtk/widget1/ColorCb.H
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

#ifndef gtk_widget1_ColorCb_INCLUDED
#define gtk_widget1_ColorCb_INCLUDED

#include <iostream>
#include "base/System.H"
#include "base/Color3.H"
#include "base/Color4.H"
#include "widget/ui/FloatSet.H"
#include "gtk/widget0/HBox.H"
#include "gtk/widget0/ButtonCb.H"
#include "gtk/widget0/ColorSelectionDialogCb.H"
#include "gtk/widget1/NumberWidget2Cb.H"

namespace gtk {
namespace widget1 {

template <class A>
class ColorCb
  :
    public widget::ui::FloatSet,
    public gtk::widget0::Frame
{

public:

  typedef void (A::*ObjectCallbackFnPtr)() ;

  // constructor
  ColorCb(
    char const *label,
    base::Color3 const &value,
    A *obj,
    ObjectCallbackFnPtr fn );

  // constructor
  ColorCb(
    char const *label,
    base::Color4 const &value,
    A *obj,
    ObjectCallbackFnPtr fn );

  // constructor
  ColorCb(
    char const *label,
    float const *value,
    uint count,
    A *obj,
    ObjectCallbackFnPtr fn );

  // destructor
  virtual ~ColorCb();

  void set( base::Color3 const &a );
  void set_blocked( base::Color3 const &a );
  void get( base::Color3 &a ) const;

  void set( base::Color4 const &a );
  void set_blocked( base::Color4 const &a );
  void get( base::Color4 &a ) const;

  void set( float const a[] );
  void set_blocked( float const a[] );
  void get( float a[] ) const;

  virtual void set_sensitive( bool state = true )
    { ::gtk::widget0::Widget::set_sensitive(state); }
  virtual void set_sensitive( uint n, bool state )
    { WARN(); }
  virtual void set_bounds( uint n, float lower, float upper )
    { DIE(); }

  uint count() const
    { return _numberwidget->count(); }

protected:

private:

  void button_cb();
  void color_selector_cb();

  gtk::widget0::HBox *_vbox;
  gtk::widget0::ButtonCb<ColorCb<A> > *_button;
  gtk::widget0::ColorSelectionDialogCb<ColorCb<A> > *_colorselection;
  NumberWidget2Cb<A> *_numberwidget;

  gint delete_event_cb();

  static gint delete_event_cb_(
    GtkWidget *widget,
    GdkEvent  *event,
    gpointer   data );

  gtk::widget0::Callback<ColorCb<A> > _ok_callback;
  void ok_cb();

  // disabled copy constructor
  ColorCb( ColorCb const & );

  // disabled assignment operator
  ColorCb &operator=( ColorCb const & );
};

extern const numberwidget_config ColorCb_config[4];

template <class A>
ColorCb<A>::
ColorCb(
  char const *label,
  base::Color3 const &value,
  A *obj,
  ObjectCallbackFnPtr fn )
    :
    gtk::widget0::Frame(label),
    _colorselection( (gtk::widget0::ColorSelectionDialogCb<ColorCb<A> > *)0 ),
    _ok_callback( this, &ColorCb<A>::ok_cb )
{
  uint const COUNT = 3U;

  gtk::widget0::Widget::show();

  // create a HBox
  _vbox = new gtk::widget0::HBox(false, 0);
  _vbox->show();

  // add the HBox to the frame
  add(_vbox);
  
  // create a Button
  _button = new gtk::widget0::ButtonCb<ColorCb<A> >(
    (char *)0, this, &ColorCb<A>::button_cb );
  _button->show();

  // put the Button into the HBox
  _vbox->add(_button, false, false, 0);

  base::Color3 c;
  base::rgb2hsv( c, value );

  numberwidget_config config[4] =
    {
      { "H", -FLT_MAX, FLT_MAX, 0.001, 0.01, 0.1, 3, 0.0 },
      { "S", 0.0, 1.0, 0.001, 0.01, 0.1, 3, 0.0 },
      { "V", 0.0, 1.0, 0.001, 0.01, 0.1, 3, 0.0 },
    };
  uint i;
  for ( i = 0; i < COUNT; i++ )
  {
    config[i].value = c[i];
  }

  // create a new Numberwidget
  _numberwidget = new NumberWidget2Cb<A>(
    (char *)0, config, COUNT, obj, fn );
  _numberwidget->show();

  // put the Numberwidget into the HBox
  _vbox->add(_numberwidget, true, true, 0);
}

template <class A>
ColorCb<A>::
ColorCb(
  char const *label,
  base::Color4 const &value,
  A *obj,
  ObjectCallbackFnPtr fn )
    :
    gtk::widget0::Frame(label),
    _colorselection( (gtk::widget0::ColorSelectionDialogCb<ColorCb<A> > *)0 ),
    _ok_callback( this, &ColorCb<A>::ok_cb )
{
  uint const COUNT = 4U;

  gtk::widget0::Widget::show();

  // create a HBox
  _vbox = new gtk::widget0::HBox(false, 0);
  _vbox->show();

  // add the HBox to the frame
  add(_vbox);
  
  // create a Button
  _button = new gtk::widget0::ButtonCb<ColorCb<A> >(
    (char *)0, this, &ColorCb<A>::button_cb );
  _button->show();

  // put the Button into the HBox
  _vbox->add(_button, false, false, 0);

  base::Color4 c;
  base::rgb2hsv( c, value );

  numberwidget_config config[4] =
    {
      { "H", -FLT_MAX, FLT_MAX, 0.001, 0.01, 0.1, 3, 0.0 },
      { "S", 0.0, 1.0, 0.001, 0.01, 0.1, 3, 0.0 },
      { "V", 0.0, 1.0, 0.001, 0.01, 0.1, 3, 0.0 },
      { "A", 0.0, 1.0, 0.001, 0.01, 0.1, 3, 1.0 }
    };
  uint i;
  for ( i = 0; i < COUNT; i++ )
  {
    config[i].value = c[i];
  }

  // create a new Numberwidget
  _numberwidget = new NumberWidget2Cb<A>(
    (char *)0, config, COUNT, obj, fn );
  _numberwidget->show();

  // put the Numberwidget into the HBox
  _vbox->add(_numberwidget, true, true, 0);
}

template <class A>
ColorCb<A>::
~ColorCb()
{
  delete _button;
  delete _numberwidget;
  delete _colorselection;
  delete _vbox;
}

template <class A>
void
ColorCb<A>::
button_cb()
{
  // create a new ColorSelectionDialog

  // return if there already is a ColorSelectionDialog
  if (_colorselection != (gtk::widget0::ColorSelectionDialogCb<ColorCb<A> > *)0)
  {
    return;
  }

  if (count() == 3U)
  {
    base::Color3 a;
    _numberwidget->get(a.data());
    base::hsv2rgb( a );

    // create a new ColorSelectionDialog
    // NOTE: memory leak ?
    // NOTE: connect delete/destroy?
    _colorselection = new gtk::widget0::ColorSelectionDialogCb<ColorCb<A> >(
      (char *)0, a.data(), this, &ColorCb<A>::color_selector_cb );
  }
  else
  {
    base::Color4 a;
    _numberwidget->get(a.data());
    base::hsv2rgb( a );

    // create a new ColorSelectionDialog
    // NOTE: memory leak ?
    // NOTE: connect delete/destroy?
    _colorselection = new gtk::widget0::ColorSelectionDialogCb<ColorCb<A> >(
      (char *)0, a.data(), this, &ColorCb<A>::color_selector_cb );
  }

  GtkColorSelectionDialog *w =
    GTK_COLOR_SELECTION_DIALOG(_colorselection->w());

  // connect delete_event
  gtk_signal_connect(
    GTK_OBJECT(w), "delete_event",
    GTK_SIGNAL_FUNC(delete_event_cb_), this);

  // connect the ok button
  gtk_signal_connect(
    GTK_OBJECT(w->ok_button ),
    "clicked",
    GTK_SIGNAL_FUNC(_ok_callback.static_callback_fn),
    (gpointer)&_ok_callback );
    
  // hide the cancel button
  gtk_widget_hide( w->cancel_button );

  // hide the help button
  gtk_widget_hide( w->help_button );

  _colorselection->show();
}

template <class A>
void
ColorCb<A>::
color_selector_cb()
{

  if (count() == 3U)
  { 
    base::Color3 a;
    _colorselection->get(a.data());
    base::rgb2hsv( a );
    _numberwidget->set(a.data());
  }
  else
  {
    base::Color4 a;
    _colorselection->get(a.data());
    base::Color4 b;
    _numberwidget->get(b.data());
    a.alpha() = b.alpha();
    base::rgb2hsv( a );
    _numberwidget->set(a.data());
  }
}

template <class A>
void
ColorCb<A>::
ok_cb()
{
  _colorselection->hide();
  delete _colorselection;
  _colorselection = (gtk::widget0::ColorSelectionDialogCb<ColorCb<A> > *)0;
}

template <class A>
gint
ColorCb<A>::
delete_event_cb()
{
  std::cerr << "delete\n";
  _colorselection->hide();
  delete _colorselection;
  _colorselection = (gtk::widget0::ColorSelectionDialogCb<ColorCb<A> > *)0;
  return 1;
}

template <class A>
gint
ColorCb<A>::
delete_event_cb_(
  GtkWidget *widget,
  GdkEvent  *event,
  gpointer   data )
{
  return static_cast<ColorCb<A> *>(data)->delete_event_cb();
}

template <class A>
void
ColorCb<A>::
set( base::Color3 const &a )
{
  DIE_IF(count() != 3U);
  base::Color3 b;
  base::rgb2hsv(b, a);
  _numberwidget->set(b.data());
}

template <class A>
void
ColorCb<A>::
set_blocked( base::Color3 const &a )
{
  DIE_IF(count() != 3U);
  base::Color3 b;
  base::rgb2hsv(b, a);
  _numberwidget->set_blocked(b.data());
}

template <class A>
void
ColorCb<A>::
get( base::Color3 &a ) const
{
  DIE_IF(count() != 3U);
  _numberwidget->get(a.data());
  base::hsv2rgb( a );
}

template <class A>
void
ColorCb<A>::
set( base::Color4 const &a )
{
  DIE_IF(count() != 4U);
  base::Color4 b;
  base::rgb2hsv(b, a);
  _numberwidget->set(b.data());
}

template <class A>
void
ColorCb<A>::
set_blocked( base::Color4 const &a )
{
  DIE_IF(count() != 4U);
  base::Color4 b;
  base::rgb2hsv(b, a);
  _numberwidget->set_blocked(b.data());
}

template <class A>
void
ColorCb<A>::
get( base::Color4 &a ) const
{
  DIE_IF(count() != 4U);
  _numberwidget->get(a.data());
  base::hsv2rgb( a );
}

template <class A>
void
ColorCb<A>::
set( float const a[] )
{
  if (count() == 3U)
  {
    base::Color3 b(a);
    base::rgb2hsv(b);
    _numberwidget->set(b.data());
  }
  else if (count() == 4U)
  {
    base::Color4 b(a);
    base::rgb2hsv(b);
    _numberwidget->set(b.data());
  }
  else
  {
    DIE();
  }
}

template <class A>
void
ColorCb<A>::
set_blocked( float const a[] )
{
  if (count() == 3U)
  {
    base::Color3 b(a);
    base::rgb2hsv(b);
    _numberwidget->set_blocked(b.data());
  }
  else if (count() == 4U)
  {
    base::Color4 b(a);
    base::rgb2hsv(b);
    _numberwidget->set_blocked(b.data());
  }
  else
  {
    DIE();
  }
}

template <class A>
void
ColorCb<A>::
get( float a[] ) const
{
  if (count() == 3U)
  {
    base::Color3 b;
    _numberwidget->get(b.data());
    base::hsv2rgb( b );
    uint i;
    for ( i = 0; i < count(); i++ ) { a[i] = b[i]; }
  }
  else if (count() == 4U)
  {
    base::Color4 b;
    _numberwidget->get(b.data());
    base::hsv2rgb( b );
    uint i;
    for ( i = 0; i < count(); i++ ) { a[i] = b[i]; }
  }
  else
  {
    DIE();
  }
}

} // namespace widget1
} // namespace gtk

#endif // gtk_widget1_ColorCb_INCLUDED

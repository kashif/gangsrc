/* GANG Software
 * WIDGET/widget/ui/KeyBase.H
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

#ifndef widget_ui_KeyBase_INCLUDED
#define widget_ui_KeyBase_INCLUDED

#include <list>
#include <gdk/gdktypes.h>
#include <gdk/gdkkeysyms.h>
#include "base/System.H"
#include "base/String.H"

extern GdkModifierType const MOD_NONE;
extern GdkModifierType const MOD_SHIFT;
extern GdkModifierType const MOD_CTRL;
extern GdkModifierType const MOD_ALT;
extern GdkModifierType const MOD_CTRL_SHIFT;
extern GdkModifierType const MOD_CTRL_ALT;

namespace widget {
namespace ui {

struct EntryBase
{
public:
  EntryBase(
    base::String const &label_,
    uint key_,
    GdkModifierType modifier_ )
      :
      label(label_),
      key(key_),
      modifier(modifier_)
    {}

  virtual ~EntryBase() {}

  virtual void call() = 0;

  base::String label;
  uint key;
  GdkModifierType modifier;
};

template <class A>
struct Entry
  :
    public EntryBase
{
public:
  typedef void (A::*BoundFnPtr)();

  Entry( 
    base::String const &label,
    guint key,
    GdkModifierType modifier,
    A *obj,
    BoundFnPtr fn )
      :
      EntryBase(label, key, modifier),
      _obj(obj),
      _fn(fn) {}

protected:
  virtual void call()
    {
      (_obj->*_fn)();
    }
private:
  A *_obj;
  BoundFnPtr _fn;
};



class KeyBase
{

public:

  // constructor
  KeyBase() : _entry() {}

  // copy constructor
  KeyBase( KeyBase const &a )
      :
      _entry(a._entry) {}

  // destructor
  virtual ~KeyBase()
    {
      std::list<EntryBase *>::iterator i;
      for (i = _entry.begin(); i != _entry.end(); i++ )
      { delete (*i); }
    }

  // assignment operator
  KeyBase &operator=( KeyBase const &a )
    { if (this != &a) { _entry = a._entry; } return *this; }

  template <class A>
  void insert(
    base::String const &label,
    guint key, GdkModifierType modifier,
    A *obj, void (A::*fn)() );

  virtual void insert_separator() {}

  std::list<EntryBase *> const &entry() const
    { return _entry; }
protected:

  virtual void insert_v( EntryBase *e ) {}

private:

  std::list<EntryBase *> _entry;

};

template <class A>
void
KeyBase::
insert(
  base::String const &label,
  guint key, GdkModifierType modifier,
  A *obj, void (A::*fn)() )
{
  DIE_IF(key == 0);
  DIE_IF(obj == (A*)0);

  Entry<A> *e = new Entry<A>(label, key, modifier, obj, fn);
  _entry.push_back( e );
  insert_v(e);
}


} // namespace ui
} // namespace widget

#endif // widget_ui_KeyBase_INCLUDED

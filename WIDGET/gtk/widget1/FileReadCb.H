/* GANG Software
 * WIDGET/gtk/widget1/FileReadCb.H
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

#ifndef gtk_widget1_FileReadCb_INCLUDED
#define gtk_widget1_FileReadCb_INCLUDED

#include "FileRead.H"

namespace gtk {
namespace widget1 {

template <class A>
class FileReadCb
  :
    public FileRead
{
public:
  typedef void (A::*CallbackFnPtr)();

  FileReadCb(
    A *obj, CallbackFnPtr fn ) :
      FileRead(),
      _obj(obj),
      _fn(fn)
      {}

private:
  virtual void callback()
    { (_obj->*_fn)(); }
  A *_obj;
  CallbackFnPtr _fn;
};

} // namespace widget1
} // namespace gtk

#endif // gtk_widget1_FileReadCb_INCLUDED

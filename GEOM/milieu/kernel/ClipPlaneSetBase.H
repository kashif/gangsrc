/* GANG Software
 * GEOM/milieu/kernel/ClipPlaneSetBase.H
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

#ifndef milieu_kernel_ClipPlaneSetBase_INCLUDED
#define milieu_kernel_ClipPlaneSetBase_INCLUDED

#include <iostream>
#include "base/System.H"
#include "base/ArrayX.H"
#include "ClipPlane.H"

namespace milieu {
namespace kernel {

class ClipPlaneSetBase
{

public:
  typedef double Real;
  typedef math::Matrix<Real> Transform;

  // constructor
  ClipPlaneSetBase();

  // destructor
  virtual ~ClipPlaneSetBase();

  void dump( io::Ostream &o ) const;

  static uint count()
    { return CLIPPLANE_COUNT; }

  static uint const CLIPPLANE_COUNT = 6U;

  // interface
  virtual void reset() { WARN(); }
  virtual void reset( uint id ) { WARN(); }

  virtual bool enable( uint id ) const
    { return elem(id).enable(); }
  virtual bool moving( uint id ) const
    { return elem(id).moving(); }
  virtual bool show( uint id ) const
    { return elem(id).show(); }
  virtual bool attached( uint id ) const
    { return elem(id).attached(); }
  virtual Transform const &position( uint id ) const
   { return elem(id).position(); }

  virtual void enable( uint id, bool a )
    { elem(id).enable(a); }
  virtual void moving( uint id, bool a )
    { elem(id).moving(a); }
  virtual void show( uint id, bool a )
    { elem(id).show(a); }
  virtual void attached( uint id, bool a )
    { elem(id).attached(a); }
  virtual void position( uint id, Transform const &a )
    { elem(id).position(a); }

protected:

  base::ArrayX<ClipPlane *, CLIPPLANE_COUNT> _;

private:

  virtual ClipPlane &elem(uint) = 0;
  virtual ClipPlane const &elem(uint) const = 0;

  ClipPlaneSetBase( ClipPlaneSetBase const & );
  ClipPlaneSetBase &operator=( ClipPlaneSetBase const & );
};

} // namespace kernel
} // namespace milieu

#endif // milieu_kernel_ClipPlaneSetBase_INCLUDED

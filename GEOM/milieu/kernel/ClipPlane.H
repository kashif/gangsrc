/* GANG Software
 * GEOM/milieu/kernel/ClipPlane.H
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

#ifndef milieu_kernel_ClipPlane_INCLUDED
#define milieu_kernel_ClipPlane_INCLUDED

#include "math/WriteUtil.H"

namespace milieu {
namespace kernel {

class ClipPlane
  :
    public math::WriteUtil
{

public:
  typedef double Real;
  typedef math::Matrix<Real> Transform;

  // constructor
  ClipPlane();

  // copy constructor
  ClipPlane( ClipPlane const & );

  // destructor
  virtual ~ClipPlane();

  // assignment operator
  ClipPlane &operator=( ClipPlane const & );

  void reset();
  void dump( io::Ostream & ) const;

  // access functions
  virtual bool const &enable() const
    { return _enable; }
  virtual bool const &moving() const
    { return _moving; }
  virtual bool const &show() const
    { return _show; }
  virtual bool const &attached() const
    { return _attached; }
  virtual Transform const &position() const
    { return _identity; }

  virtual void enable( bool a )
    { _enable = a; }
  virtual void moving( bool a )
    { _moving = a; }
  virtual void show( bool a )
    { _show = a; }
  virtual void attached( bool a )
    { _attached = a; }
  virtual void position( Transform const & ) const {}

protected:

private:
  void copy( ClipPlane const & );

  bool _enable;
  bool _moving;
  bool _show;
  bool _attached;

  Transform _identity;
};

} // namespace kernel
} // namespace milieu

#endif // milieu_kernel_ClipPlane_INCLUDED

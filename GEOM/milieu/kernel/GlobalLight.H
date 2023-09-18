/* GANG Software
 * GEOM/milieu/kernel/GlobalLight.H
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

#ifndef milieu_kernel_GlobalLight_INCLUDED
#define milieu_kernel_GlobalLight_INCLUDED

#include "io/Ostream.H"
#include "base/Color3.H"

namespace milieu {
namespace kernel {

class GlobalLight
{

public:
  // constructor
  GlobalLight();

  // copy constructor
  GlobalLight( GlobalLight const & );

  // destructor
  virtual ~GlobalLight();

  // assignment operator
  GlobalLight &operator=( GlobalLight const & );

  void reset();
  void dump( io::Ostream &o ) const;

  // access functions
  virtual bool const &enable() const
    { return _enable; }
  virtual base::Color3 const &ambient() const
    { return _ambient; }
  virtual bool const &viewpoint() const
    { return _viewpoint; }
  virtual bool const &sidedness() const
    { return _sidedness; }

  virtual void enable( bool a )
    { _enable = a; }
  virtual void ambient( base::Color3 const &a )
    { _ambient = a; }
  virtual void viewpoint( bool a )
    { _viewpoint = a; }
  virtual void sidedness( bool a )
    { _sidedness = a; }

protected:

private:

  void copy(GlobalLight const &);

  // global light switch
  bool _enable;

  base::Color3 _ambient;
  bool _viewpoint;
  bool _sidedness;

};

} // namespace kernel
} // namespace milieu

#endif // milieu_kernel_GlobalLight_INCLUDED

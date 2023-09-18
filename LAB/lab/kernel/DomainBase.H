/* GANG Software
 * LAB/lab/kernel/DomainBase.H
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

#ifndef lab_kernel_DomainBase_INCLUDED
#define lab_kernel_DomainBase_INCLUDED

#include "base/System.H"
#include "base/vector.H"
#include "Common.H"

namespace lab {
namespace kernel {

class DomainBase
{

public:
  // constructor
  DomainBase() {}

  // destructor
  virtual ~DomainBase() {}

  virtual Complex zstart_v() const = 0;

  virtual void start_all_v(
    uint vertex_count,
    uint edge_count,
    uint thread_count ) = 0;
  virtual void end_all_v(
    uint vertex_count,
    uint edge_count,
    uint thread_count ) = 0;

  virtual void start_v(
    Complex const &z0,
    uint k0,
    uint thread_id ) = 0;

  virtual void step_v(
    Complex const &z0,
    Complex const &z1,
    uint k0,
    uint k1,
    uint thread_id ) = 0;

  virtual void end_v() = 0;

  // this is called by a single thread
  virtual void check_v( uint count, uint total ) = 0;

  virtual void export_fn_v(
    base::vector<Real> &v, uint k ) = 0;

protected:

private:

  // disabled copy constructor
  DomainBase( DomainBase const & );
  // disabled assignment operator
  DomainBase &operator=( DomainBase const & );

};

} // namespace kernel
} // namespace lab

#endif // lab_kernel_DomainBase_INCLUDED

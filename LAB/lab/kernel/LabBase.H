/* GANG Software
 * LAB/lab/kernel/LabBase.H
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

#ifndef lab_kernel_LabBase_INCLUDED
#define lab_kernel_LabBase_INCLUDED

#include "base/ProcTimer.H"
#include "geom/interface/Surface.H"
#include "DomainBase.H"
#include "Domain.H"

namespace lab {
namespace kernel {

/*
  Class LabBase
  Manages surface domains (DomainIndexed, DomainGrid)
*/

class LabBase
  :
    protected DomainBase
{

public:

  // constructor
  LabBase();

  // destructor
  virtual ~LabBase();

protected:

  void multithread_(bool s)
    { _multithread = s; }
  bool multithread_() const
    { return _multithread; }
  void spaceform( geom::SpaceForm const &s );
  uint dim() const
    { return _dim; }
  void compute_x( base::String const & );
  geom::Surface *export_();
  void _stop_computation();

  void computation_time(
    base::String &user_time,
    base::String &system_time,
    base::String &elapsed_time )
    {
      _timer.read( user_time, system_time, elapsed_time );
    }

protected:

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
  virtual void check_v( uint count, uint total ) = 0;
  virtual void export_fn_v(
    base::vector<Real> &v, uint k ) = 0;
  

  Domain *_domain;

private:

  base::ProcTimer _timer;
  bool _multithread;
  geom::SpaceForm _spaceform;
  uint _dim;

  void parse( base::String const & );

  // disabled copy constructor
  LabBase( LabBase const & );
  // disabled assignment operator
  LabBase &operator=( LabBase const & );
};

} // namespace kernel
} // namespace lab

#endif // lab_kernel_LabBase_INCLUDED

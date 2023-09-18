/* GANG Software
 * LAB/lab/kernel/DomainGrid.H
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

#ifndef lab_kernel_DomainGrid_INCLUDED
#define lab_kernel_DomainGrid_INCLUDED

#include <slist>
#include "base/vector.H"
#include "base/System.H"
#include "base/Exception.H"
#include "thread/Thread.H"
#include "geom/interface/Surface.H"
#include "Rectangular.H"
#include "Polar.H"
#include "Domain2D.H"

namespace lab {
namespace kernel {

class DomainGrid
  :
  public Domain2D
{

public:

  // void constructor
  DomainGrid( bool multithread, DomainBase *base );

  // destructor
  virtual ~DomainGrid();

  virtual void
  edge( uint n, uint &k0, uint &k1, uint thread ) const;

  virtual uint vertex_count() const;

  virtual uint edge_count() const;

  virtual uint edge_count( uint thread ) const;

  virtual uint face_count() const;

  virtual void clear();

  virtual Complex z( uint ) const
    throw();

  virtual void
  initialize( Complex const &zstart, uint proc_count );

  uint count0() const
    { DIE_IF( _planar_domain == (PlanarDomain *)0);
    return _planar_domain->count0(); }
  uint count1() const
    { DIE_IF( _planar_domain == (PlanarDomain *)0);
    return _planar_domain->count1(); }

  geom::Surface *export_() const;

protected:

  virtual int type() const
    { return 2; }  

private:

  virtual void compute();
  void compute_loop( uint thread );

  class Thread1 : public thread::Thread
  {
  public:
    Thread1( DomainGrid *parent, uint thread_id ) :
        thread::Thread( thread_id ), _parent(parent) {}
  protected:
    virtual void function( uint thread_id );
  private:
    DomainGrid *_parent;
  };
  friend class Thread1;

  bool _multithread;

  uint _thread_count;
  static uint const INITIAL_THREAD = uint(-1);

  uint MAX_PROC_COUNT;

  // check data
  uint _check_count;
  base::vector<uint> _check_count_vect;
  uint _check_total;

  PlanarDomain *_planar_domain;

  // disabled private copy constructor
  DomainGrid( DomainGrid const & );
  // disabled private assignement operator
  DomainGrid &operator=( DomainGrid const & );

};

} // namespace kernel
} // namespace lab

#endif // lab_kernel_DomainGrid_INCLUDED

/* GANG Software
 * LAB/lab/kernel/DomainIndexed.H
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

#ifndef lab_kernel_DomainIndexed_INCLUDED
#define lab_kernel_DomainIndexed_INCLUDED

#include <slist>
#include "base/vector.H"
#include "base/System.H"
#include "base/Exception.H"
#include "geom/interface/Surface.H"
#include "triang/Triangulator.H"
#include "Domain2D.H"

namespace lab {
namespace kernel {

class DomainIndexed
  :
  public Domain2D
{

public:

  // void constructor
  DomainIndexed( DomainBase *base );

  // destructor
  virtual ~DomainIndexed();

  virtual uint vertex_count() const
    { return _surface->vertex_count(); }

  virtual uint edge_count() const
    { return (uint)_edge.size(); }

  virtual uint face_count() const
    { return _surface->face_count(); }

  virtual void clear();

  virtual Complex z(uint) const throw();

  geom::Surface const *surface() const
    {
      return _surface;
    }
  /*
     set the surface to 'surface'
     DomainIndexed does not modify or delete 'surface'
  */
  virtual void
  initialize( Complex const &zstart );

  virtual void
  initialize_pass2(
    Complex const &zstart,
    base::vector<Real> const &area );

  virtual void compute();
  virtual void compute_refine();
  virtual void compute_sub();

  virtual geom::Surface *export_() const;

protected:

  virtual int type() const
    { return 1; }  

private:

  void parse( base::String const &s );
  void compute2();

  void initialize_file( base::String const &filename );
  void initialize_triangulated( base::String const &s );

  /*
     Compute the base::vector '_adjacency' containing edge adjacency
     information.
     _adjacency[i] is a list of the vertices connected to i
  */
  void compute_adjacency()
    throw( base::Exception );

  /*
     Compute edge information
     Fills _edge with pairs of edges each connected to
     a previous one
  */
  void compute_edge()
    throw( base::Exception );

#ifdef DEBUG
  void dump_adjacency( std::ostream &o ) const;
  void dump_edge( std::ostream &o ) const;
#endif

  static uint const THREAD_ID = 0;
  static uint const THREAD_COUNT = 1;

  uint _check_total;
  uint _check_count;

  /*
     _adjacency[i] is a vector of points connected to point i
  */
  base::vector<std::slist<uint> > _adjacency;

  /*
     _edge is a vector of edges making a web connecting back
     to starting point
  */
  base::vector<std::pair<uint, uint> > _edge;


  uint _start_index;

  geom::Surface *_surface;

  uint find_closest( Complex const &z )
    throw( base::Exception );

  uint _grid;
  uint _random;
  uint _refine;
  uint _smooth;

  triang::Triangulator *_triangulator;

  // disabled private copy constructor
  DomainIndexed( DomainIndexed const & );
  // disabled private assignement operator
  DomainIndexed &operator=( DomainIndexed const & );

};

} // namespace kernel
} // namespace lab

#endif // lab_kernel_DomainIndexed_INCLUDED

/* GANG Software
 * LAB/lab/kernel/DomainGrid.C
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

#if defined(__sgi)
#include <task.h>
#endif
#include "base/System.H"
#include "base/Stl.H"
#include "base/Regex.H"
#include "DomainGrid.H"

namespace lab {
namespace kernel {

DomainGrid::
DomainGrid(
  bool multithread,
  DomainBase *base )
    :
    Domain2D( base ),
    _multithread(multithread),
    _thread_count(0U),
#if defined(__sgi)
    MAX_PROC_COUNT(m_get_numprocs()),
#else
    // NOTE: default thread count is 1
    MAX_PROC_COUNT(1U),
#endif
    _planar_domain( (PlanarDomain *)0 )
{
#if defined(__sgi)
  // force multithread 0
  _multithread = 0;
#endif
  clear();
}

DomainGrid::
~DomainGrid()
{
  if (_planar_domain != (PlanarDomain *)0 )
  {
    delete _planar_domain;
  }
}

void
DomainGrid::
clear()
{
}

uint
DomainGrid::
vertex_count() const
{
  return count0() * count1();
}

uint
DomainGrid::
face_count() const
{
  DIE_IF( count0() == 0 );
  DIE_IF( count1() == 0 );
  return (count0()-1) * (count1()-1);
}

uint
DomainGrid::
edge_count() const
{
  /*
    total number of edges:

    _count0-1 edges along the 0-direction plus
    _count0 * (count1()-1) edges along the 1-direction
  */
  return count0() - 1 + count0() * ( count1() - 1 );
}

uint
DomainGrid::
edge_count( uint thread ) const
{
  if ( count0() == 0 || count1() == 0 )
  { WARN(); throw Exception( Exception::ERR_INTERNAL ); }

  if (thread == INITIAL_THREAD)
  {
    return count0() - 1;
  }

  uint t = thread;
  uint T = _thread_count;

  return
    (count1()-1) * ( count0()/T + (t < (count0() % T) ? 1 : 0) );

  /* mathematica version:

  edgecount[c0_, c1_][T_][t_] :=
    If[t == -1,
      c0 - 1,
      (c1 - 1)*(Floor[c0/T] + If[t < Mod[c0, T], 1, 0])];

  edge[c0_, c1_][T_][t_][n_] :=
    If[t == -1,
      {n*c1, (n + 1)*c1},
      Block[{a}, a = c1*Floor[n/(c1 - 1)] + Mod[n, c1 - 1] +
          c1(t Floor[c0/T] + Min[t, Mod[c0, T]]); {a, a + 1}]]
  */
}

void
DomainGrid::
edge(
  uint n,
  uint &k0,
  uint &k1,
  uint thread ) const
{
  /*
    thread = 0 is the initial thread which must be completed before
       starting subsequent threads (thread = 0, 1, ...)
       thread = -1 runs along j=0 line.
    thread = 1, 2, ... take adjacent i=const lines.
       these threads may take unequal numbers of edges, depending on
       how the total number of threads (_thread_count) divides count0().
  */

  if ( count1() ==  0 || count1() == 0 )
  { WARN(); throw Exception( Exception::ERR_INTERNAL ); }

  if ( n >= edge_count(thread) )
  { WARN(); throw Exception( Exception::ERR_INTERNAL ); }

  if ( thread == INITIAL_THREAD )
  {
    // initial thread
    k0 = n*count1();
    k1 = k0 + count1();
  }
  else
  {
    // subsequent threads
    uint t = thread;
    uint T = _thread_count;

    k0 = count1()*(n/(count1() - 1)) + (n %(count1() - 1)) +
      count1() * ( t * (count0()/T) + std::min(t, count0() % T) );
    k1 = k0 + 1;
  }
}

Complex
DomainGrid::
z( uint n ) const
  throw ()
{
  DIE_IF( n >= vertex_count() );

  uint i = n / count1();
  uint j = n % count1();

  return _planar_domain->z( i, j );
}

void
DomainGrid::
initialize(
  Complex const &zstart,
  uint proc_count )
{
  DIE_IF( proc_count == 0 );
  USE(zstart);

  if ( configuration().empty() )
  {
    throw Exception( Exception::ERR_UNCONFIGURED );
  }

  // clear data
  clear();

  if ( base::match( "^[ \n\r\t]*rectangular", configuration() ) )
  {
    delete _planar_domain;
    _planar_domain = new Rectangular( configuration() );
  }
  else if ( base::match( "^[ \n\r\t]*polar", configuration() ) )
  {
    delete _planar_domain;
    _planar_domain = new Polar( configuration() );
  }
  else
  {
    throw Exception( Exception::ERR_UNKNOWN_DOMAIN );
  }

  // thread_count cannot exceed count0() because
  // count0() runs n lines off, one for each thread
  DIE_IF( count0() == 0 );
  DIE_IF( proc_count == 0 );
  if (_multithread)
  {
    _thread_count = std::min(proc_count, count0());
  }
  else
  {
    _thread_count = 1;
  }

  DIE_IF( _thread_count == 0 );
}

void
DomainGrid::
compute()
{
  uint const proc_count = ( _multithread ? MAX_PROC_COUNT : 1 );
  DIE_IF( proc_count == 0 );

  initialize( base()->zstart_v(), proc_count);

  DIE_IF( _thread_count == 0 );

  _check_count = 0;
  _check_count_vect.fill( 0U, _thread_count );
  _check_total = edge_count();

  base()->start_all_v( vertex_count(), edge_count(), _thread_count );

  // run start_v()
  uint k0, k1;
  // get indices (k0,k1)=(begin,end) for the 0'th segment for 'thread'
  edge(0, k0, k1, 0 );
  base()->start_v( z(k0), k0, 0 );

  compute_loop(INITIAL_THREAD);

  if ( _thread_count > 1 )
  {
    // multithread version
    Thread1 thread(this, _thread_count);
    thread.run();
  }
  else
  {
    // singlethread version
    compute_loop(0);
  }

  base()->end_all_v( vertex_count(), edge_count(), _thread_count );
}

void
DomainGrid::
compute_loop( uint thread )
{
  DIE_IF( thread != INITIAL_THREAD && thread >= _thread_count );

  check_stopped();
  base()->check_v( 0, _check_total );

  // run step_v() loop
  uint i;
  uint edge_count_;
  edge_count_ = edge_count(thread);
  if (edge_count_ == 0)
  { WARN("edge count == 0"); }
    
  for ( i = 0; i < edge_count_; i++ )
  {
    check_stopped();

    uint k0, k1;
    // get indices (k0,k1)=(begin,end) for the i'th segment for 'thread'
    edge( i, k0, k1, thread );
    uint t = (thread == INITIAL_THREAD ? 0 : thread );
    base()->step_v( z(k0), z(k1), k0, k1, t );

    // increment check count
    if ( thread == INITIAL_THREAD )
    {
      _check_count++;
      DIE_IF( _check_count > _check_total );
      base()->check_v( _check_count, _check_total );
    }
    else
    {
      _check_count_vect[thread]++;
      // call check on first thread
      if ( thread == 0 )
      {
        uint i;
        uint c = _check_count;
        for ( i = 0; i < _thread_count; i++ )
        {
          c += _check_count_vect[i];
        }
        DIE_IF( c > _check_total );
        base()->check_v( c, _check_total );
      }
    }
  }

  // run end_v()
  base()->end_v();
}


geom::Surface *
DomainGrid::
export_() const
{
  // NOTE: inefficient

  uint c0 = count0();
  uint c1 = count1();

  base::vector<base::vector<base::vector<Real> > > v;
  v.reserve(c0);

  uint i;
  for ( i = 0; i < c0; i++ )
  {
    base::vector<base::vector<Real> > w;
    w.reserve(c1);
    uint j;
    for ( j = 0; j < c1; j++ )
    {
      base::vector<Real> v0;
      v0.fill( 0.0, dim() );
      base()->export_fn_v( v0, i * c1 + j );
      w.push_back( v0 );
    }
    v.push_back(w);
  }

  // copy v into surface
  geom::Surface *x = new geom::Surface;

  x->import( v, spaceform() );

  return x;
}

void
DomainGrid::
Thread1::
function( uint thread )
{
  _parent->compute_loop( thread );
}

} // namespace kernel
} // namespace lab

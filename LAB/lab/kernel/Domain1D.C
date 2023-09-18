/* GANG Software
 * LAB/lab/kernel/Domain1D.C
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

#include "base/Regex.H"
#include "base/Stl.H"
#include "geom/interface/Surface.H"
#include "Line.H"
#include "Circle.H"
#include "Exception.H"
#include "Domain1D.H"

namespace lab {
namespace kernel {

Domain1D::
Domain1D( DomainBase *base )
    :
    Domain(base),
    triang::Parser(),
    _check_count(0U),
    _check_total(0U)
{
}

Domain1D::
~Domain1D()
{
}

void
Domain1D::
initialize()
{
  _vertex.clear();

  base::vector<base::String> v;
  if ( ! base::match( "^[ \n\r\t]*curve[ \n\r\t]+(.*)$",
                      configuration(), v ) )
  {
    DIE();
  }
  base::String s = "Line\n" + v[1];

  parse( _boundary_str, _vertex_v_v, s );

  // copy points in _vertex_v_v to _vertex
  base::vector<triang::Curve>::const_iterator i;
  for (i = _vertex_v_v.begin(); i != _vertex_v_v.end(); i++ )
  {
    base::vector<base::vector<std::pair<Real,Real> > >::const_iterator j;
    for (j = (*i).v.begin(); j != (*i).v.end(); j++ )
    {
      base::vector<std::pair<Real,Real> >::const_iterator k;
      for (k = (*j).begin(); k != (*j).end(); k++ )
      {
        _vertex.push_back( Complex((*k).first, (*k).second) );
      }
    }
  }
  _vertex_v_v.clear();

#if 0
  if (_curve != (Curve *)0) { delete _curve; _curve = (Curve *)0; }
  if ( base::match( "^[ \n\r\t]*line", configuration() ) )
  {
    _curve = new Line( configuration() );
  }
  else if ( base::match( "^[ \n\r\t]*circle", configuration() ) )
  {
    _curve = new Circle( configuration() );
  }
  else
  {
    throw Exception( Exception::ERR_UNKNOWN_DOMAIN );
  }
#endif
}

void
Domain1D::
compute()
{
  uint const THREAD_COUNT = 1;
  uint const THREAD_ID = 0;

  initialize();

  DIE_IF(count() <= 1 );

  _check_count = 0U;
  _check_total = count()-1;

  base()->start_all_v( count(), count()-1, THREAD_COUNT );

  base()->start_v( z(0), 0, THREAD_ID );

  uint i;
  for ( i = 0; i < count()-1; i++ )
  {
    check_stopped();
    base()->step_v( z(i), z(i+1), i, i+1, THREAD_ID );
    _check_count++;
    base()->check_v( _check_count, _check_total );
  }

  base()->end_all_v( count(), count()-1, THREAD_COUNT );
}

Complex
Domain1D::
z( uint n ) const
  throw ()
{
  DIE_IF( n >= count() );
  return _vertex[n];
}

geom::Surface *
Domain1D::
export_() const
{
  base::vector<base::vector<Real> > w;
  w.reserve(count());

  std::list<uint> line;

  uint i;
  for ( i = 0; i < count(); i++ )
  {
    base::vector<Real> v;
    v.fill( 0.0, dim() );
    base()->export_fn_v( v, i );
    w.push_back(v);
    line.push_back(i);
  }

  base::vector<base::vector<uint> > face;
  std::list<std::list<uint> > lines;
  lines.push_back(line);

  geom::Surface *X = new geom::Surface;
  X->import( w, face, spaceform() );

  X->import_lines( lines );
  return X;
}

} // namespace kernel
} // namespace lab

/* GANG Software
 * GEOM/geom/surface0/LineSet.H
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

#ifndef geom_surface0_LineSet_INCLUDED
#define geom_surface0_LineSet_INCLUDED

#include <list>

namespace geom {
namespace surface0 {

class LineSet
{

public:
  // constructor
  LineSet();

  // copy constructor
  LineSet( LineSet const & );

  // destructor
  virtual ~LineSet();

  // assignment operator
  LineSet &operator=( LineSet const & );
#if 0
  // Returns the  total number of lines in the surface.
  virtual uint line_count() const
    { return (uint)_line.size(); }

  // Returns the number of vertices of the n'th line.
  virtual uint line_count(uint i) const
    { return (uint)_line[i].size(); }

  // Returns the index of v'th vertex of the f'th line.
  virtual uint line_vertex(
    uint i, uint j) const
    { return _line[i][j]; }

  std::list<uint> const &line(uint i) const
    { return _line[i]; }
#endif

  std::list<std::list<uint> > const &line() const
    { return _line; }
  void line( std::list<std::list<uint> > &line ) const
    { line = _line; }

  void import_lines( std::list<std::list<uint> > const &line )
    { _line = line; }

protected:

  void clear()
    { _line.clear(); }

private:

  // std::list of face indices
  std::list<std::list<uint> > _line;

};

} // namespace surface0
} // namespace geom

#endif // geom_surface0_LineSet_INCLUDED

/* GANG Software
 * GEOM/geom/io/VrmlRead.H
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

#ifndef geom_io_VrmlRead_INCLUDED
#define geom_io_VrmlRead_INCLUDED

#include <list>
#include "base/System.H"
#include "io/Istream.H"
#include "vrml/Parser.H"
#include "geom/surface0/Common.H"
#include "geom/surface0/GeomObject.H"
#include "Reader.H"

namespace geom {
namespace io {

class VrmlRead
  :
    public Reader,
    public vrml::Parser
{
public:
  VrmlRead();

  void read(
    ::io::Istream &,
    ::geom::surface::SurfaceBase &G,
    ::milieu::kernel::MilieuBase &M )
    throw (::io::ReadException);

protected:

private:

  virtual void indexedFaceSet( IndexedFaceSet const & );
  virtual void material( Material const & ) {};
  virtual void light( Light const & ) {};
  virtual void background( Background const & ) {};

  virtual void cleanup();
  virtual void _throw( char const *message );

  std::list<surface0::GeomObject *> _list;
  ::io::Istream *_istream;

  // disabled copy constructor
  VrmlRead( VrmlRead const & );
  // disabled assignement operator
  VrmlRead &operator=(VrmlRead const &);
};

} // namespace io
} // namespace geom

#endif // geom_io_VrmlRead_INCLUDED

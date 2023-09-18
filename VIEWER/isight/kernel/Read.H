/* GANG Software
 * VIEWER/isight/kernel/Read.H
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

#ifndef isight_kernel_Read_INCLUDED
#define isight_kernel_Read_INCLUDED

#include "io/Istream.H"
#include "milieu/kernel/MilieuBase.H"
#include "geom/interface/SurfaceGL.H"
#include "ContextSet.H"

namespace isight {
namespace kernel {

class Read
  :
    public ContextSet
{

public:
  // constructor
  Read();

  // destructor
  virtual ~Read();

  // read from a stream
  virtual void read(
    io::Istream &stream,
    geom::FileMode filemode = geom::FILEMODE_DEFAULT )
    throw (io::ReadException);

  // read a file
  virtual void read(
    base::String const &filename,
    geom::FileMode filemode = geom::FILEMODE_UNSPECIFIED )
    throw (io::ReadException);

  // read a set of files
  virtual void read(
    base::vector<base::String> const &filename,
    geom::FileMode filemode = geom::FILEMODE_DEFAULT )
    throw (io::ReadException);

protected:

private:

  // pure virtuals
  virtual void insert_geomobject( geom::SurfaceGL * ) = 0;

  // disabled copy constructor
  Read( Read const & );
  // disabled assignment operator
  Read &operator=( Read const & );

};

} // namespace kernel
} // namespace isight

#endif // isight_kernel_Read_INCLUDED

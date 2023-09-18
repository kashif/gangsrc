/* GANG Software
 * VIEWER/isight/kernel/Write.H
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

#ifndef isight_kernel_Write_INCLUDED
#define isight_kernel_Write_INCLUDED

#include "io/Ostream.H"
#include "Read.H"

namespace isight {
namespace kernel {

class Write
  :
    public Read
{

public:
  // constructor
  Write();

  // destructor
  virtual ~Write();

  // write to a stream
  virtual void write(
    io::Ostream &,
    geom::FileMode filemode = geom::FILEMODE_DEFAULT) const
    throw (io::WriteException);

  // write a file
  virtual void write(
    base::String const &filename,
    geom::FileMode filemode = geom::FILEMODE_UNSPECIFIED) const
    throw (io::WriteException);

protected:

private:

  // returns true iff a surface is loaded and selected
  bool surface_exists() const;

  void _write_geometry( base::String const &filename ) const;
  void _write_postscript( base::String const &filename, bool EPS ) const;
  void _write_image( base::String const &filename ) const;
  void _write_geometry(
    io::Ostream &stream,
    geom::FileMode mode ) const;

  // disabled copy constructor
  Write( Write const & );
  // disabled assignment operator
  Write &operator=( Write const & );

};

} // namespace kernel
} // namespace isight

#endif // isight_kernel_Write_INCLUDED

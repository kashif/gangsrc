/* GANG Software
 * LAB/lab/kernel/Domain2D.H
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

#ifndef lab_kernel_Domain2D_INCLUDED
#define lab_kernel_Domain2D_INCLUDED

#include <complex>
#include "base/String.H"
#include "Common.H"
#include "Exception.H"
#include "Domain.H"
#include "DomainBase.H"

namespace lab {
namespace kernel {

/*
   Abstract base class for surface domains.
*/

class Domain2D
  :
    public Domain
{

public:

  // void constructor
  Domain2D( DomainBase *base );

  // destructor
  virtual ~Domain2D();

  virtual Complex z(uint) const throw() = 0;

  //
  virtual void clear() = 0;

  // number of vertices
  virtual uint vertex_count() const = 0;

  // total number of edges to be processed
  virtual uint edge_count() const = 0;

  // number of faces
  virtual uint face_count() const = 0;
 
protected:

  virtual void compute() = 0;

  virtual int type() const = 0;

private:

  // disabled copy constructor
  Domain2D( Domain2D const & );
  // disabled assignment operator
  Domain2D &operator=( Domain2D const & );

};

} // namespace kernel
} // namespace lab

#endif // lab_kernel_Domain2D_INCLUDED

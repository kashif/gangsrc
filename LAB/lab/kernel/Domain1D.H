/* GANG Software
 * LAB/lab/kernel/Domain1D.H
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

#ifndef lab_kernel_Domain1D_INCLUDED
#define lab_kernel_Domain1D_INCLUDED

#include "base/String.H"
#include "base/vector.H"
#include "triang/Common.H"
#include "triang/Parser.H"
#include "DomainBase.H"
#include "Domain.H"
//#include "Curve.H"

namespace lab {
namespace kernel {

class Domain1D
  :
    public Domain,
    public triang::Parser
{

public:
  // constructor
  Domain1D( DomainBase *base );

  // destructor
  virtual ~Domain1D();

protected:

  uint count() const
    { return _vertex.size(); }

  Complex z( uint n ) const
    throw ();

  virtual void compute();

  virtual geom::Surface *export_() const;

private:

  void initialize();

  base::vector<Complex> _vertex;

  base::vector<base::String> _boundary_str;
  base::vector<triang::Curve> _vertex_v_v;

  uint _check_count, _check_total;

  // disabled copy constructor
  Domain1D( Domain1D const & );
  // disabled assignment operator
  Domain1D &operator=( Domain1D const & );

};

} // namespace kernel
} // namespace lab

#endif // lab_kernel_Domain1D_INCLUDED

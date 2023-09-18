/* GANG Software
 * LAB/lab/kernel/Domain.H
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

#ifndef lab_kernel_Domain_INCLUDED
#define lab_kernel_Domain_INCLUDED

#include "base/String.H"
#include "geom/interface/Surface.H"
#include "DomainBase.H"

namespace lab {
namespace kernel {

class Domain
{

public:
  // constructor
  Domain( DomainBase *base );

  // destructor
  virtual ~Domain();

  // configuration
  void configuration( base::String const &v )
    { _configuration = v; }
  base::String const &configuration() const
    { return _configuration; }

  // dim
  uint const &dim() const
    { return _dim; }
  void dim(uint s)
    { _dim = s; }

  // spaceform
  geom::SpaceForm const &spaceform() const
    { return _spaceform; }
  void spaceform( geom::SpaceForm s)
    { _spaceform = s; }

  // base
  DomainBase *base() const
    { return _base; }

  void stop_computation()
    { _stop = true; }


  // pure virtuals
  virtual void compute() = 0;

  virtual geom::Surface *export_() const = 0;

protected:

  void check_stopped();


private:

  // flag to stop computation on next iteration
  bool _stop;

  base::String _configuration;
  uint _dim;
  geom::SpaceForm _spaceform;
  DomainBase *_base;

  // disabled copy constructor
  Domain( Domain const & );
  // disabled assignment operator
  Domain &operator=( Domain const & );

};

} // namespace kernel
} // namespace lab

#endif // lab_kernel_Domain_INCLUDED

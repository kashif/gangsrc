/* GANG Software
 * LAB/lab/kernel/LabBase.C
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

#include "base/System.H"
#include "Domain1D.H"
#include "DomainIndexed.H"
#include "DomainGrid.H"
#include "LabBase.H"

namespace lab {
namespace kernel {

LabBase::
LabBase()
    :
    _domain( (Domain *)0 ),
    _multithread(true),
    _spaceform(),
    _dim()
{
  // set _spaceform and _dim to default
  geom::SpaceForm s;
  spaceform(s);
}

LabBase::
~LabBase()
{
  if (_domain != (Domain *)0) { delete _domain; }
}

void
LabBase::
spaceform( geom::SpaceForm const &s )
{
  _spaceform = s;
  _dim = ( _spaceform.space == geom::SpaceForm::SPACEFORM_R ?
           _spaceform.dim : _spaceform.dim + 1U );
}

void
LabBase::
compute_x( base::String const &s )
{
  if (_domain != (Domain *)0) { delete _domain; }

  base::vector<base::String> v;
  if ( base::match(
         "^[ \n\r\t]*triangulated[ \n\r\t]+(.*)$", s, v )  ||
       base::match( "^[ \n\r\t]*file",  s ) )
  {
    _domain = new DomainIndexed(this);
    _domain->configuration(s);
  }
  else if ( base::match( "^[ \n\r\t]*rectangular", s ) ||
            base::match( "^[ \n\r\t]*polar", s ) ||
            base::match( "^[ \n\r\t]*polar_exp", s ) )
  {
    _domain = new DomainGrid(_multithread, this);
    _domain->configuration(s);
  }
  else if ( base::match( "^[ \n\r\t]*curve", s ) )
  {
    _domain = new Domain1D(this);
    _domain->configuration(s);
  }
  else
  {
    DIE();
  }

  DIE_IF(_dim == 0);
  _domain->dim(_dim);
  _domain->spaceform(_spaceform);

  _timer.start();
  _domain->compute();
}

geom::Surface *
LabBase::
export_()
{
  DIE_IF( _domain == (Domain *)0 );
  return _domain->export_();
}

void
LabBase::
_stop_computation()
{
  if ( _domain == (Domain *)0 ) { return; }
  _domain->stop_computation();
}

} // namespace kernel
} // namespace lab

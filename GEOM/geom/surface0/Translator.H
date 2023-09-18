/* GANG Software
 * GEOM/geom/surface0/Translator.H
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

#ifndef geom_surface0_Translator_INCLUDED
#define geom_surface0_Translator_INCLUDED

#include "math/VectorX.H"
#include "Transformer.H"

namespace geom {
namespace surface0 {

class Translator
  :
    public Transformer
{

public:
  // constructor
  Translator( math::VectorX<Real,3U> const &a )
      : _a(a) {}

  // destructor
  virtual ~Translator() {}

  virtual void function( math::VectorX<Real,4U> &x ) const;
  
private:

  math::VectorX<Real,3U> _a;

  // disabled copy constructor
  Translator( Translator const & );
  // disabled assignment operator
  Translator &operator=( Translator const & );
};

} // namespace surface0
} // namespace geom

#endif // geom_surface0_Translator_INCLUDED

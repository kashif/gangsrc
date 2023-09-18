/* GANG Software
 * GEOM/geom/surface0/TransformerMatrix.H
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

#ifndef geom_surface0_TransformerMatrix_INCLUDED
#define geom_surface0_TransformerMatrix_INCLUDED

#include "math/VectorX.H"
#include "math/MatrixX.H"
#include "math/Matrix.H"
#include "Transformer.H"

namespace geom {
namespace surface0 {

class TransformerMatrix
  :
    public Transformer
{

public:
  // constructor
  TransformerMatrix( math::Matrix<Real> const &a );

  // destructor
  virtual ~TransformerMatrix() {}

  virtual void function( math::VectorX<Real,4U> &x ) const;
  
private:

  math::MatrixX<Real,4U> _a;

  // disabled copy constructor
  TransformerMatrix( TransformerMatrix const & );
  // disabled assignment operator
  TransformerMatrix &operator=( TransformerMatrix const & );
};

} // namespace surface0
} // namespace geom

#endif // geom_surface0_TransformerMatrix_INCLUDED

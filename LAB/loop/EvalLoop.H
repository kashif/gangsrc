/* GANG Software
 * LAB/loop/EvalLoop.H
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

#ifndef loop_EvalLoop_INCLUDED
#define loop_EvalLoop_INCLUDED

#include <map>
#include "base/ArrayX.H"
#include "base/Array.H"
#include "eval/Eval.H"
#include "math/Complex2.H"
#include "Common.H"
#include "Loop4.H"


namespace loop {

class EvalLoop
{

public:

  // constructor
  EvalLoop();

  // copy constructor
  EvalLoop( EvalLoop const & );

  // assignment operator
  EvalLoop &operator=( EvalLoop const & );

  // destructor
  virtual ~EvalLoop();

  // set *this from a string
  void set( base::String const &, bool is_potential=false );

  // evaluate *this at z; put result into X
  void evaluate( Loop4 &X, Complex const &z);

  // clear the loop
  void clear_data();

  // set the variable name (coordinate on the Riemann surface "z")
  void set_variable_name( base::String const &varname )
    { _varname = varname; }

  // set time parameter
  void set_time( Real time, base::String const &varname )
    { _time = time; _time_varname = varname; }

  typedef std::map<int,base::String, std::less<int> > Hash;

  RangeMatrix range()
    { return _range; }

protected:

private:

  void
  _evaluate_string(
    eval::Expression<Complex> &e,
    Hash const &h,
    int j );

  void
  _evaluate_expression(
    Complex &w,
    eval::Expression<Complex> &,
    Complex const &z );

  typedef base::Array<eval::Expression<Complex> > ExpressionEntry;
  typedef base::ArrayX<base::ArrayX<ExpressionEntry,2U>,2U> ExpressionMatrix;
  ExpressionMatrix _matrix;

  RangeMatrix _range;

  // an evaluator
  eval::Evaluator<Complex> _evaluator;

  // variable name
  base::String _varname;

  // time parameter
  Real _time;

  // time parameter name
  base::String _time_varname;
};

} // namespace loop

#endif // loop_EvalLoop_INCLUDED

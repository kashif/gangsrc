/* GANG Software
 * LAB/lab/kernel/Evaluator.H
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

#ifndef lab_kernel_Evaluator_INCLUDED
#define lab_kernel_Evaluator_INCLUDED

#include "base/String.H"
#include "eval/Eval.H"

namespace lab {
namespace kernel {

// NOTE: templates don't work here (g++ crashes on exceptions)
#undef LAB_EVAL_USE_TEMPLATES

class Evaluator
{

public:
  // constructor
  Evaluator();

  // destructor
  virtual ~Evaluator();

#if defined(LAB_EVAL_USE_TEMPLATES)
  template <class A>
  void evaluate( A &x, base::String const &s ) const;
#else
  void evaluate( float &x, base::String const &s ) const;
  void evaluate( double &x, base::String const &s ) const;
  void evaluate( std::complex<float> &x, base::String const &s ) const;
  void evaluate( std::complex<double> &x, base::String const &s ) const;
  void evaluate( uint &x, base::String const &s ) const;
  void evaluate( int &x, base::String const &s ) const;
#endif

  base::String const &time_varname() const
    { return _time_varname; }
  double time() const
    { return _time; }

  static Evaluator *evaluator()
    { DIE_IF(_evaluator == (Evaluator *)0); return _evaluator; }
protected:

private:

  void set_time( double t, base::String name )
    { _time = t; _time_varname = name; }


  double _time;
  base::String _time_varname;

  // NOTE: hack to make evaluator available to everybody
  static Evaluator *_evaluator;

  // disabled copy constructor
  Evaluator( Evaluator const & );
  // disabled assignment operator
  Evaluator &operator=( Evaluator const & );

  friend class LabBase2;
};

#if 0
template <class A>
void
Evaluator::
evaluate( A &x, base::String const &s ) const
{
  if ( _time_varname.empty() )
  {
    eval::evaluate( x, s );
  }
  else
  {
    eval::Expression<A> e;

    // introduce the time variable
    e.set_variable( _time_varname, static_cast<A>(_time) );

    eval::Evaluator<A> E;

    // evaluate the string s into the expression e
    E.evaluate(e, s);

    // evaluate the expression e into x
    E.evaluate(x, e);
  }
}
#endif

} // namespace kernel
} // namespace lab

#endif // lab_kernel_Evaluator_INCLUDED

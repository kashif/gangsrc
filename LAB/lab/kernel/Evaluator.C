/* GANG Software
 * LAB/lab/kernel/Evaluator.C
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

#include "base/String.H"
#include "base/Exception.H"
#include "base/Regex.H"
#include "math/Math.H"
#include "Evaluator.H"

namespace lab {
namespace kernel {

Evaluator *Evaluator::_evaluator = (Evaluator *)0;

Evaluator::
Evaluator()
    :
    _time(0.0),
    _time_varname()
{
}

Evaluator::
~Evaluator()
{
}

#if defined(LAB_EVAL_USE_TEMPLATES)


#if 0
void
Evaluator::
evaluate( uint &x_, base::String const &s ) const
{
  float x;
  evaluate( x, s );
  if (x < 0) { throw base::Exception("eval: uint is negative"); }
  x_ = math::round(x);
}

void
Evaluator::
evaluate( int &x_, base::String const &s ) const
{
  float x;
  evaluate( x, s );
  x_ = math::round(x);
}
#endif

#else
void
Evaluator::
evaluate( float &x, base::String const &s ) const
{
  if ( _time_varname.empty() )
  {
    eval::evaluate( x, s );
  }
  else
  {
    eval::Expression<float> e;

    // introduce the time variable
    e.set_variable( _time_varname, static_cast<float>(_time) );

    eval::Evaluator<float> E;

    // evaluate the string s into the expression e
    E.evaluate(e, s);

    // evaluate the expression e into x
    E.evaluate(x, e);
  }
}

void
Evaluator::
evaluate( double &x, base::String const &s ) const
{
  if ( _time_varname.empty() )
  {
    eval::evaluate( x, s );
  }
  else
  {
    eval::Expression<double> e;

    // introduce the time variable
    e.set_variable( _time_varname, static_cast<double>(_time) );

    eval::Evaluator<double> E;

    // evaluate the string s into the expression e
    E.evaluate(e, s);

    // evaluate the expression e into x
    E.evaluate(x, e);
  }
}

void
Evaluator::
evaluate( std::complex<float> &x, base::String const &s ) const
{
  if ( _time_varname.empty() )
  {
    eval::evaluate( x, s );
  }
  else
  {
    eval::Expression<std::complex<float> > e;

    // introduce the time variable
    e.set_variable( _time_varname, static_cast<std::complex<float> >(_time) );

    eval::Evaluator<std::complex<float> > E;

    // evaluate the string s into the expression e
    E.evaluate(e, s);

    // evaluate the expression e into x
    E.evaluate(x, e);
  }
}

void
Evaluator::
evaluate( std::complex<double> &x, base::String const &s ) const
{
  if ( _time_varname.empty() )
  {
    eval::evaluate( x, s );
  }
  else
  {
    eval::Expression<std::complex<double> > e;

    // introduce the time variable
    e.set_variable( _time_varname, static_cast<std::complex<double> >(_time) );

    eval::Evaluator<std::complex<double> > E;

    // evaluate the string s into the expression e
    E.evaluate(e, s);

    // evaluate the expression e into x
    E.evaluate(x, e);
  }
}

void
Evaluator::
evaluate( uint &x_, base::String const &s ) const
{
  float x;
  if ( _time_varname.empty() )
  {
    eval::evaluate( x, s );
  }
  else
  {
    eval::Expression<float> e;

    // introduce the time variable
    e.set_variable( _time_varname, static_cast<float>(_time) );

    eval::Evaluator<float> E;

    // evaluate the string s into the expression e
    E.evaluate(e, s);

    // evaluate the expression e into x
    E.evaluate(x, e);
  }
  if (x < 0) { throw base::Exception("eval: uint is negative"); }
  x_ = math::round(x);
}

void
Evaluator::
evaluate( int &x_, base::String const &s ) const
{
  float x;
  if ( _time_varname.empty() )
  {
    eval::evaluate( x, s );
  }
  else
  {
    eval::Expression<float> e;

    // introduce the time variable
    e.set_variable( _time_varname, static_cast<float>(_time) );

    eval::Evaluator<float> E;

    // evaluate the string s into the expression e
    E.evaluate(e, s);

    // evaluate the expression e into x
    E.evaluate(x, e);
  }
  x_ = math::round(x);
}
#endif

} // namespace kernel
} // namespace lab

/* GANG Software
 * LAB/lab/kernel/LabBase2.C
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
#include "base/Regex.H"
#include "io/IstreamStream.H"
#include "io/OstreamStream.H"
#include "LabBase2.H"

namespace lab {
namespace kernel {

LabBase2::
LabBase2()
    :
    LabBase(),
    Evaluator(),
    _surface_exists(false),
    _computing(false),
    _exporting(false),
    _computing_sequence(false),
    _verbosity(0)
{
  Evaluator::_evaluator = this;
}

LabBase2::
~LabBase2()
{
}

void
LabBase2::
_compute_and_export()
{
  if (_computing) { return; }
  _computing = true;

  try
  {
    _compute_and_export_no_exception();
  }
  catch (Exception const &e)
  {
    _computing = false;
    _surface_exists = false;
    clear_status();
    cleanup_on_stop();
    if ( e.code() != Exception::STOP &&
         e.code() != Exception::STOP_SEQUENCE )
    {
      message( e.message() );
    }
  }
  catch (base::Exception const &e)
  {
    _computing = false;
    _surface_exists = false;
    clear_status();
    cleanup_on_stop();
    message( e.message() );
  }

  _computing = false;

}

void
LabBase2::
export_()
{
  if (_computing) { return; }
  _computing = true;

  try
  {
    _export();
  }
  catch (base::Exception const &e)
  {
    _computing = false;
    _surface_exists = false;
    clear_status();
    message( e.message() );
  }

  _computing = false;

}

void
LabBase2::
_compute_and_export_no_exception()
{
  message(base::String());

  compute_x( domain() );

  _surface_exists = true;

  base::String user_time, system_time, elapsed_time;
  computation_time( user_time, system_time, elapsed_time );
  set_status( user_time, system_time, elapsed_time );

  _export();
}

void
LabBase2::
_export()
{
  if ( ! _surface_exists ) { return; }

  // export the object
  geom::Surface *X = LabBase::export_();

  if ( X == (geom::Surface *)0 )
  { WARN(); throw kernel::Exception(kernel::Exception::ERR_INTERNAL); }

  if ( ! _write_filename.empty() )
  {
    X->write( _write_filename );
  }

  // send it to output
  export_object_v( *X );

  delete X;
}

#if 0
void
LabBase2::
write_surface(
  geom::Surface *X,
  io::Ostream &out )
{
  X->write( out );
}

void
LabBase2::
write_surface(
  geom::Surface *X,
  base::String const &filename )
{
  io::OstreamStream stream(filename);
  write_surface(X, name, stream);
}
#endif

void
LabBase2::
export_object_v(
  geom::Surface const &X )
{
  // default export:
  // write surface to cout
  io::OstreamStream stream(std::cout);
  X.write( stream );
}

void
LabBase2::
compute_sequence(
  base::String const &filename,
  base::String const &counter_var,
  base::String const &time_varname,
  base::String const &function,
  uint start,
  uint count )
{
  if ( _computing) { return; }
  if ( _computing_sequence) { return; }

  _computing_sequence = true;

  try
  {
  base::String format;

  _write_filename.erase();

  if ( ! filename.empty() )
  {
    base::vector<base::String> v;

    if ( base::match( "^([^#]*)(#+)(.*)$", filename, v ) )
    {
      format = v[1];
      size_t n = v[2].size();
      base::String q;
      q.to_string(n);
      format += "%0";
      format += q;
      format += "d";
      format += v[3];
    }
    else
    {
      format = filename;
    }
  }
  DIE_IF(format.size() > 1000);

  eval::Evaluator<double> E;
  eval::Expression<double> time_expr;
  time_expr.create_variable( counter_var );

  // evaluate the function into time_expr
  try{ E.evaluate( time_expr, function ); }
    catch ( base::Exception const & )
  { throw kernel::Exception(kernel::Exception::ERR_SEQUENCER); }

  uint n;

  for ( n = start; n < start + count; n++ )
  {
    if (_stop_sequence)
    {
      _stop_sequence = false;
      throw kernel::Exception(kernel::Exception::STOP_SEQUENCE);
    }
    update_sequencer( n );
    // compute the time as a function of the counter
    // set the counter to n
    time_expr.set_variable( counter_var, n );

    // evaluate time_expr into time
    double time;
    try { E.evaluate(time, time_expr); }
    catch ( base::Exception const & )
    { throw kernel::Exception(kernel::Exception::ERR_SEQUENCER); }

    Evaluator::set_time( time, time_varname );

    if ( ! format.empty() )
    {
      static char filename[1024];
      sprintf( filename, format.c_str(), n );
      _write_filename = filename;
    }
    
    _compute_and_export();
  }
  // reset the time
  Evaluator::set_time( 0.0, "" );
  }
  catch (base::Exception const &e)
  {
    _computing = false;
    _computing_sequence = false;
    _surface_exists = false;

    clear_status();
    if (_stop_sequence)
    {
      message( kernel::Exception(kernel::Exception::STOP_SEQUENCE).message() );
    }
    else
    {
      message( e.message() );
    }
  }

  _computing = false;
  _computing_sequence = false;
  _stop_sequence = false;
  _write_filename.erase();
}

void
LabBase2::
_stop_computation()
{
  if (_computing_sequence)
  {
    _stop_sequence = true;
    LabBase::_stop_computation();
  }
  else if (_computing)
  {
    LabBase::_stop_computation();
  }
}

void
LabBase2::
set_status(
  base::String const &user_time,
  base::String const &system_time,
  base::String const &elapsed_time )
{
  if (_verbosity == 0) { return; }

  std::cout <<
    "  user time:    " << user_time << "\n"
    "  system time:  " << system_time << "\n"
    "  elapsed time: " << elapsed_time << "\n";
}

void
LabBase2::
check_v(uint count, uint total)
{
  if (_verbosity == 0) { return; }

  if (count != total)
  {
    static char s[20];
    double p = double(count) / double(total);
    p *= 100;
    sprintf( s, "CMC[%3.0f%%]", p );
    std::cout << '\r' << s;
  }
}

void
LabBase2::
message( base::String const &text ) const
{
  if (! text.empty()) {
    std::cerr << base::system->name() << ": " << text << "\n";
  }
}

} // namespace kernel
} // namespace lab

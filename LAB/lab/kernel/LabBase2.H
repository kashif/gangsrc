/* GANG Software
 * LAB/lab/kernel/LabBase2.H
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

#ifndef lab_kernel_LabBase2_INCLUDED
#define lab_kernel_LabBase2_INCLUDED

#include "base/vector.H"
#include "geom/interface/Surface.H"
#include "Evaluator.H"
#include "LabBase.H"
#include "Exception.H"

namespace lab {
namespace kernel {

class LabBase2
  :
    protected LabBase,
    protected Evaluator
{

public:

  // void constructor
  LabBase2();

  // destructor
  virtual ~LabBase2();

  // compute and export the surface (catches exceptions)
  void _compute_and_export();
  // export the surface (catches exceptions)
  void export_();

protected:

  void multithread_(bool state)
    { LabBase::multithread_(state); }
  bool multithread_() const
    { return LabBase::multithread_(); }
  void verbosity_(uint v)
    { _verbosity = v; }
  uint verbosity_() const
    { return _verbosity; }

  virtual void message( base::String const &text ) const;

  void compute_sequence(
    base::String const &filename,
    base::String const &counter_var,
    base::String const &time_varname,
    base::String const &function,
    uint start,
    uint count );

#if 0
  virtual void write_surface(
    geom::Surface *X, 
    io::Ostream &stream );

  virtual void write_surface(
    geom::Surface *X,
    base::String const &filename );
#endif

  virtual void _stop_computation();

protected:

  /*
    Export the object
    The default behavior is to write the object
    to std::cout
  */
  virtual void export_object_v( geom::Surface const &X );

  virtual void update_sequencer( uint n )
    { update_sequencer( n ); }

  // compute and export the surface (this function does not catch exceptions)
  virtual void _compute_and_export_no_exception();

  virtual base::String const &name() const = 0;
  virtual base::String const &domain() const = 0;

  virtual void cleanup_on_stop() {}
private:

  virtual void set_status(
    base::String const &user_time,
    base::String const &system_time,
    base::String const &elapsed_time );
  virtual void clear_status() {}
  virtual void check_v(uint count, uint total);

  void _export();

  // data

  bool _surface_exists;
  bool _computing;
  bool _exporting;
  bool _computing_sequence;

  bool _stop_sequence;

  base::String _write_filename;

  uint _verbosity;

  // disabled copy constructor
  LabBase2( LabBase2 const & );
  // disabled assignment operator
  LabBase2 &operator=( LabBase2 const & );
};

} // namespace kernel
} // namespace lab

#endif // lab_kernel_LabBase2_INCLUDED

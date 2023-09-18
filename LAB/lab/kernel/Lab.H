/* GANG Software
 * LAB/lab/kernel/Lab.H
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

#ifndef lab_kernel_Lab_INCLUDED
#define lab_kernel_Lab_INCLUDED

#include "base/String.H"
#include "io/Istream.H"
#include "io/Ostream.H"
#include "parser/KeyParser.H"
#include "lab/ui/Ui.H"
#include "LabBase2.H"

namespace lab {
namespace kernel {

/*
  Lab class. Implements data, file read/write
*/

class Lab
  :
    virtual public LabBase2,
    virtual public ::lab::ui::Ui
{

public:
  // constructor
  Lab();

  // destructor
  virtual ~Lab();

protected:

  virtual char const *lab_name() const = 0;
  virtual char const *about_info() const = 0;
  virtual char const *env_lib_path() const = 0;
  virtual char const *env_help_url() const = 0;

private:

  // read the lab data from a filename
  virtual void _read( base::String const &filename );
  // read the lab data from a streamx
  virtual void _read( io::Istream &stream );
  // write the lab data to a filename
  virtual void _write( base::String const &filename );
  // write the lab data to a stream
  virtual void _write( io::Ostream &stream );

  // Compute -> LabBase2 connector functions
  virtual void _compute_and_export();
  virtual void _stop_computation()
    { LabBase2::_stop_computation(); }

  // LabBase2 -> ui::Compute connection functions
  virtual void set_status(
    base::String const &user_time,
    base::String const &system_time,
    base::String const &elapsed_time )
    { Compute::set_status( user_time, system_time, elapsed_time ); }
  virtual void clear_status()
    { Compute::clear_status(); }
  virtual void check_v(uint count, uint total)
    { Compute::set_status(count, total); }

  // Compute -> LabBase2 connector functions
  virtual void compute_sequence(
    base::String const &filename,
    base::String const &counter_var,
    base::String const &time_varname,
    base::String const &function,
    uint start,
    uint count )
    { LabBase2::compute_sequence( filename, counter_var, time_varname,
                                  function, start, count ); }

  // ui::Ui -> LabBase2 connnector functions
  void multithread_(bool state)
    { LabBase::multithread_(state); }
  bool multithread_() const
    { return LabBase::multithread_(); }

  virtual base::String const &name() const
    { return data().get("name"); }
  virtual base::String const &domain() const
    { return data().get("domain"); }

  // set the internal state of the Lab from the data
  virtual void set_state_from_data() = 0;

  // data access
  virtual parser::KeyParser const &data() const = 0;
  virtual parser::KeyParser &data() = 0;

  // disabled copy constructor
  Lab( Lab const & );
  // disabled assignment operator
  Lab &operator=( Lab const & );

};

} // namespace kernel
} // namespace lab

#endif // lab_kernel_Lab_INCLUDED

/* GANG Software
 * LAB/lab/ui/Ui.H
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

#ifndef lab_ui_Ui_INCLUDED
#define lab_ui_Ui_INCLUDED

#include "base/vector.H"
#include "base/String.H"
#include "base/Exception.H"
#include "base/Timer.H"
#include "widget/ui/KeyBase.H"
#include "widget/ui/KeyHandler.H"
#include "Compute.H"
#include "Domain.H"
#include "Sequence.H"
#include "Read.H"
#include "Write.H"

namespace lab {
namespace ui {

/*
  Interface to Lab.
*/

class Ui
  :
    virtual public Compute,
    virtual public Domain,
    virtual public Sequence,
    virtual public Read,
    virtual public Write
{
public:

  // constructor
  Ui();

  // destructor
  virtual ~Ui();

  void multithread( bool state )
    { multithread_(state); }
  bool multithread() const
    { return multithread_(); }
  void verbosity( uint v )
    { _verbosity = v; }
  uint verbosity() const
    { return _verbosity; }

  virtual char const *lab_name() const = 0;
  virtual char const *about_info() const = 0;
  virtual char const *env_lib_path() const = 0;
  virtual char const *env_help_url() const = 0;

  virtual void toggle_raise_show_read()
    { read_p()->toggle_raise_show_d(); }
  virtual void toggle_raise_show_write()
    { write_p()->toggle_raise_show_d(); }
  virtual void toggle_raise_show_compute()
    { compute_p()->toggle_raise_show_d(); }
  virtual void toggle_raise_show_sequence()
    { sequence_p()->toggle_raise_show_d(); }
  virtual void toggle_raise_show_domain()
    { domain_p()->toggle_raise_show_d(); }
  virtual void toggle_raise_show_controls() = 0;

  void compute()
    { Compute::compute(); }

  void show_all(bool state);
  void enable_tooltips(bool state);

  virtual bool command(
    base::String const &command,
    base::String const &argument,
    base::String &response );

protected:

  void controls( ::widget::ui::KeyBase &p );
  void controls_file( ::widget::ui::KeyBase &p );

  virtual void multithread_( bool state ) = 0;
  virtual bool multithread_() const = 0;
  
  virtual void set_ui_from_data() = 0;
  virtual void set_data_from_ui() = 0;

  virtual void set_ui_from_data_v();
  virtual void set_data_from_ui_v();
  virtual void update_sequencer( uint n )
    { Sequence::update_sequencer(n); }

private:

  // data access
  virtual parser::KeyParser const &data() const = 0;
  virtual parser::KeyParser &data() = 0;

  Compute *compute_p() { return this; }
  Domain *domain_p() { return this; }
  Sequence *sequence_p() { return this; }
  Read *read_p() { return this; }
  Write *write_p() { return this; }

  virtual void clear_ui();

#if 0
  virtual void read_v( char const *filename )
    { _lab->read(filename); }

  virtual void write_v( char const *filename )
    { _lab->write(filename); }

  void compute_sequence(
    char const *filename,
    char const *counter_var,
    char const *time_varname,
    char const *function,
    uint start,
    uint count )
    { _lab->compute_sequence(
      filename,
      counter_var,
      time_varname,
      function,
      start,
      count ); }

  void stop()
    { _lab->stop(); }

  // Compute virtuals
  virtual base::String const &surface_name_v() const
    { return _lab->data().get("name"); }
  virtual void compute_v()
    { _lab->compute_and_export(); }
  virtual void stop_v()
    { _lab->stop(); }

  // Domain virtuals
  virtual base::String const &domain_v()
    { return _lab->data().get("domain"); }
#endif

  uint _verbosity;

  // disabled copy constructor
  Ui( Ui const & );
  // disabled assignment operator
  Ui &operator=( Ui const & );
};

} // namespace ui
} // namespace lab

#endif // lab_ui_Ui_INCLUDED

/* GANG Software
 * LAB/klab/kernel/Lab.H
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

#ifndef klab_kernel_Lab_INCLUDED
#define klab_kernel_Lab_INCLUDED

#include "parser/KeyParser.H"
#include "lab/kernel/Lab.H"
#include "loop/Common.H"
#include "loop/EvalLoop.H"
#include "loop/Birkhoff.H"
#include "klab/ui/Ui.H"
#include "Integrator.H"
#include "Sym.H"
#include "Data.H"
#include "Exception.H"

namespace klab {
namespace kernel {

using namespace ::loop;
typedef Loop4 Potential;

class Lab
  :
    protected lab::kernel::Lab,
    public ::klab::ui::Ui
{

public:

  // constructor
  Lab();

  // destructor
  virtual ~Lab();

  virtual parser::KeyParser const &data() const
    { return _data; }
  virtual parser::KeyParser &data()
    { return _data; }

  void set_state_from_data();

  void lambda( Real lambda ) { _lambda = lambda; }
  Real lambda() { return _lambda; }

  virtual char const *lab_name() const
    { return "KLab"; }
  virtual char const *about_info() const
    { return _about_info; }
  virtual char const *env_lib_path() const
    { return "KLAB_LIB"; }
  virtual char const *env_help_url() const
    { return "KLAB_DOC"; }

protected:

private:

  virtual void cleanup_on_stop()
    { cleanup(); }
  void cleanup();

  virtual void set_ui_from_data()
    { Controls::set( data() ); }
  virtual void set_data_from_ui()
    { Controls::get( data() ); }
  virtual void load_surface()
    { export_(); }
  virtual base::String const &domain()
    { return data().get("domain"); }

  /*
     Set the initial condition for the CMC initial value problem.
     'z0' is the basepoint in the domain, the whence integration starts.
     'Phi0' is the initial value of Phi at 'z0'.
  */
  void initial_condition(
    Complex const &z,
    base::String const &x,
    base::String const &y );

  /*
     Get the initial condition for the CMC initial value problem.
     'z0' is the basepoint in the domain, the whence integration starts.
     'Phi0' is the initial value of Phi at 'z0'.
  */
  void initial_condition(
    Complex &z,
    base::String &x,
    base::String &y );

  //
  void integrator_count( uint x )
    { _integrator_count = x; }

  //
  uint integrator_count() const
    { return _integrator_count; }

  //
  void initial_integrator_count( uint x )
    { _initial_integrator_count = x; }

  //
  uint initial_integrator_count() const
    { return _initial_integrator_count; }

  //
  void polynomial_length( uint x )
    { _polylen = x; }

  //
  uint polynomial_length() const
    { return _polylen; }

  // reset internal parameters
  void initialize_data();

  //
  void initialize();

  /*
     Set initial condition
     this is delayed (not performed when the user sets the initial condition)
     so that the user can change polylen, and the stored Xstart will still
     be ok
  */
  void initial_condition( Loop4 &gx0, Loop4 &gy0 );

  virtual Complex zstart_v() const
    { return _zstart; }

  virtual void start_all_v(
    uint vertex_count,
    uint edge_count,
    uint thread_count );

  virtual void end_all_v(
    uint vertex_count,
    uint edge_count,
    uint thread_count);

  // initial integration step (called by Domain1::start() )
  virtual void start_v(
    Complex const &z0,
    uint k0,
    uint thread_id );

  // single intermediate integration step (called by Domain1::step() )
  virtual void step_v(
    Complex const &z0,
    Complex const &z1,
    uint k0,
    uint k1,
    uint thread_id );

  virtual void end_v() {}

  // subroutine to compute one integration/Iwasawa step
  void
  compute_segment(
    Complex &z,
    Complex const &dz,
    Potential &potential_x,
    Potential &potential_y,
    Loop4 &gx,
    Loop4 &gy,
    Loop4 &F,
    uint steps,
    uint thread_count );

  // single Sym step
  void export_fn_v(
    base::vector<Real> &v,
    uint k );

  Data _data;

  // potentials
  EvalLoop _potential_x;
  EvalLoop _potential_y;


  // initial point in domain
  Complex _zstart;

  // initial matrix values
  base::String _initial_x;
  base::String _initial_y;

  // number of fourth-order Runge-Kutta steps to take for each
  // edge of the domain mesh
  uint _integrator_count;

  // number of fourth-order Runge-Kutta steps to take for the initial step
  uint _initial_integrator_count;

  // length of loop fourier series
  uint _polylen;

  // '_lambda_family' is a real number in [0,1];
  // the actual lambda family parameter is
  //   exp(2 pi i _lambda_family)
  Real _lambda;

  Birkhoff *_factorizer;

  Sym _sym;


  struct MultiData
  {
    MultiData() :
        z(0.0),
      gx(0U),
      gy(0U),
      potential_x(0U),
      potential_y(0U),
      F(0U) {}

    // CMC loopgroup data: the point z in the domain
    Complex z;

    // CMC loopgroup data
    Loop4 gx;
    Loop4 gy;

    // CMC loopgroup data: the potential
    Potential potential_x;
    Potential potential_y;

    // CMC loopgroup data: the extended frame
    Loop4 F;
  };
  base::vector<MultiData> _multidata;

  // multithread computational tool data type
  struct MultiOp
  {
    EvalLoop *_potential_x;
    EvalLoop *_potential_y;
    Integrator *_integrator_x;
    Integrator *_integrator_y;
    Birkhoff *_factorizer;
  };

  // multithread computational tool
  base::vector<MultiOp> _multiop;

  static char const *_about_info;

  // disabled copy constructor
  Lab( Lab const & );
  // disabled assignment operator
  Lab &operator=( Lab const & );
};

} // namespace kernel
} // namespace klab

#endif // klab_kernel_Lab_INCLUDED

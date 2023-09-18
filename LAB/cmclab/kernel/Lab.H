/* GANG Software
 * LAB/cmclab/kernel/Lab.H
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

#ifndef cmclab_kernel_Lab_INCLUDED
#define cmclab_kernel_Lab_INCLUDED

#include "parser/KeyParser.H"
#include "lab/kernel/Lab.H"
#include "loop/Common.H"
#include "loop/EvalLoop.H"
#include "loop/RIwasawa.H"
#include "cmclab/ui/Ui.H"
#include "Data.H"
#include "Integrator.H"
#include "Sym.H"
#include "Exception.H"

namespace cmclab {
namespace kernel {

using namespace ::loop;
typedef Loop4 Potential;

/*
  Lab base class for computing constant mean curvature surfaces.
  Class 'cmclab_base' together with class 'cmclab' constitute the
  Lab computer. Class 'cmclab_base' manages the computational
  routines. Class 'cmclab', which derives from class 'cmclab_base'
  provides user interface.
*/

class Lab
  :
    protected lab::kernel::Lab,
    public ::cmclab::ui::Ui
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

  /*
     Read and internalize 'mdata'
     Return error status
  */
  void set_state_from_data();

  enum GeometryType { ELLIPTIC, PARABOLIC, HYPERBOLIC };

  virtual void set_lambda_R3( Real lambda );
  virtual void set_lambda_S3( Real lambda0, Real lambda1 );
  virtual void set_lambda_H3( Complex const &lambda );
  void set_normalshift( Real x )
    { _normalshift = x; }
  void set_mean_curvature( Real x )
    { _mean_curvature = x; }

  virtual char const *lab_name() const
    { return "CMCLab"; }
  virtual char const *about_info() const
    { return _about_info; }
  virtual char const *env_lib_path() const
    { return "CMCLAB_LIB"; }
  virtual char const *env_help_url() const
    { return "CMCLAB_DOC"; }

protected:

  /*
     Set the initial condition for the CMC initial value problem.
     'z' is the basepoint in the domain, the whence integration starts.
     'x' is the initial value for the ODE at 'z'.
  */
  void initial_condition(
    Complex const &z,
    base::String const &x );

  void integrator_count( uint x )
    { _integrator_count = x; }
  uint integrator_count() const
    { return _integrator_count; }

  void initial_integrator_count( uint x )
    { _initial_integrator_count = x; }
  uint initial_integrator_count() const
    { return _initial_integrator_count; }

  void polynomial_length( uint x )
    { _polylen = x; }
  uint polynomial_length() const
    { return _polylen; }

  void basis_length( uint x )
    { _basislen = x; }
  uint basis_length() const
    { return _basislen; }

  // Iwasawa decomposition method
  // 0 = cholesky
  // 1 = QR
  void iwasawa_method( int x )
    { _iwasawa_method = x; }
  uint iwasawa_method() const
    { return _iwasawa_method; }

  void one_column( bool x )
    { _one_column = x; }
  bool one_column() const
    { return _one_column; }

  void birkhoff( bool x )
    { _birkhoff = x; }
  uint birkhoff() const
    { return _birkhoff; }

  static Complex exp2pii( Real r );


  // object for computing the potential
  EvalLoop _potential;

  // initial point in domain
  Complex _zstart;

  // initial value for Phi
  EvalLoop _xstart;

private:

  virtual void cleanup_on_stop()
    { cleanup(); }
  void cleanup();

  virtual void set_ui_from_data()
    { Controls::set( data() ); }
  virtual void set_data_from_ui()
    { Controls::get( data() ); }
  virtual base::String const &domain()
    { return data().get("domain"); }
  virtual void load_surface()
    { export_(); }

  //
  void initialize();

  //
  Data _data;

  /*
     typedef used by set_initial_condition() and initial_condition().
  */
  typedef std::pair<Complex,Complex > complexPair;

  // reset internal parameters
  void initialize_data();

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
    Potential &xi,
    Loop4 &X,
    Loop4 &F,
    Real &metric,
    uint steps,
    uint thread_id );

  // single Sym step
  virtual void export_fn_v(
    base::vector<Real> &v,
    uint k );

  // number of fourth-order Runge-Kutta steps to take for each
  // edge of the domain mesh
  uint _integrator_count;

  // number of fourth-order Runge-Kutta steps to take for the initial step
  uint _initial_integrator_count;

  // length of loop fourier series
  uint _polylen;

  // basis size for Iwasawa decomposition
  uint _basislen;

  // whether to spew extra data (currently has no effect)
  uint _verbosity;

  // multithread computational tool data type
  struct MultiOp
  {
    EvalLoop *_potential;
    Integrator *_integrator;
    RIwasawa *_iwasawa;
  };

  // multithread computational tool
  base::vector<MultiOp> _multiop;

  struct MultiData
  {
    MultiData()
        :
      z(0.0),
      X(0),
      xi(0),
      F(0),
      metric(0.0){}

    // CMC loopgroup data: the point z in the domain
    Complex z;

    // CMC loopgroup data: Phi
    Loop4 X;

    // CMC loopgroup data: the potential
    Potential xi;

    // CMC loopgroup data: the extended frame
    Loop4 F;

    // CMC loopgroup data: the metric
    Real metric;

    void dump( std::ostream & ) const;
  };

  base::vector<MultiData> _multidata;

  // '_lambda_family' is a real number in [0,1];
  // the actual lambda family parameter is
  //   exp(2 pi i _lambda_family)
  Real _lambda_R3;
  Real _lambda0_S3;
  Real _lambda1_S3;
  Complex _lambda_H3;

  // used internally in compute()
  Complex _lambda0;
  // used internally in compute()
  Complex _lambda1;

  GeometryType _geometry;
  Real _normalshift;
  Real _mean_curvature;

  int _iwasawa_method;
  bool _one_column;
  bool _birkhoff;

  Sym _sym;

  static char const *_about_info;

  // disabled copy constructor
  Lab( Lab const & );
  // disabled assignment operator
  Lab &operator=( Lab const & );
};

} // namespace kernel
} // namespace cmclab

#endif // cmclab_kernel_Lab_INCLUDED

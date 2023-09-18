/* GANG Software
 * LAB/surflab/kernel/Lab.H
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

#ifndef surflab_kernel_Lab_INCLUDED
#define surflab_kernel_Lab_INCLUDED

#include "lab/kernel/Lab.H"
#include "eval/Eval.H"
#include "surflab/ui/Ui.H"
#include "Data.H"
#include "Exception.H"

namespace surflab {
namespace kernel {

/*
  Computes parametrized surfaces in R^2, R^3 or R^4.
*/
class Lab
  :
    public lab::kernel::Lab,
    public ::surflab::ui::Ui
{

public:

  typedef ::lab::kernel::Real Real;
  typedef ::lab::kernel::Complex Complex;

  // constructor
  Lab();

  // destructor
  virtual ~Lab();

protected:

  virtual parser::KeyParser const &data() const
    { return _data; }
  virtual parser::KeyParser &data()
    { return _data; }

  virtual char const *lab_name() const
    { return "SurfLab"; }
  virtual char const *about_info() const
    { return _about_info; }
  virtual char const *env_lib_path() const
    { return "SURFLAB_LIB"; }
  virtual char const *env_help_url() const
    { return "SURFLAB_DOC"; }

protected:

  virtual void set_ui_from_data()
    { Controls::set( data() ); }
  virtual void set_data_from_ui()
    { Controls::get( data() ); }

  virtual void set_state_from_data();

private:

  void function(
    base::vector<Real> &y,
    std::complex<double> const &z,
    uint thread_id )
    throw ( base::Exception );

  virtual std::complex<double> zstart_v() const
    { return 0.0; }

  virtual void start_all_v(
    uint vertex_count,
    uint edge_count,
    uint thread_count );

  virtual void end_all_v(
    uint vertex_count,
    uint edge_count,
    uint thread_count);

  virtual void start_v(
    std::complex<Real> const &z0,
    uint k0,
    uint thread_id );

  virtual void step_v(
    std::complex<Real> const &z0,
    std::complex<Real> const &z1,
    uint k0, uint k1,
    uint thread_id );

  virtual void end_v() {};

  virtual void export_fn_v(
    base::vector<Real> &v,
    uint k );

  Data _data;

  // one for each point on the surface
  struct MultiData
  {
    MultiData()
        :
        _domain(),
        _surface()
      { _domain.set(0.0); }
    math::VectorX<Real,2U> _domain;
    // one for each dimension
    base::vector<Real> _surface;
  };
  base::vector<MultiData> _multidata;

  // one for each thread
  struct MultiOp
  {
    base::vector<eval::Expression< std::complex<double> > > _surf_expr;
    eval::Evaluator< std::complex<double> > _evaluator;
  };
  base::vector<MultiOp> _multiop;

  base::vector<eval::Expression< std::complex<double> > > _surf_expr0;

  base::String _varname1, _varname2;

  static char const *_about_info;

  // disabled copy constructor
  Lab( Lab const & );

  // disabled assignment operator
  Lab & operator=( Lab const & );
};

} // namespace kernel
} // namespace surflab

#endif // surflab_kernel_Lab_INCLUDED

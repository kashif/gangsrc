/* GANG Software
 * LAB/bubbletonlab/kernel/Lab.H
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

#ifndef bubbletonlab_kernel_Lab_INCLUDED
#define bubbletonlab_kernel_Lab_INCLUDED

#include "parser/KeyParser.H"
#include "eval/Eval.H"
#include "lab/kernel/Lab.H"
#include "bubbletonlab/ui/Ui.H"
#include "Bubbleton.H"
#include "Data.H"
#include "Exception.H"

namespace bubbletonlab {
namespace kernel {

/*
  Computes H=1 and K=1 bubbletons
*/
class Lab
  :
    public lab::kernel::Lab,
    public bubbletonlab::ui::Ui
{

public:

  typedef double Real;
  typedef std::complex<Real> Complex;

  // constructor
  Lab();

  // destructor
  virtual ~Lab();

  virtual parser::KeyParser const &data() const
    { return _data; }
  virtual parser::KeyParser &data()
    { return _data; }

  virtual void set_state_from_data();

  virtual char const *lab_name() const
    { return "BubbletonLab"; }
  virtual char const *about_info() const
    { return _about_info; }
  virtual char const *env_lib_path() const
    { return "BUBBLETONLAB_LIB"; }
  virtual char const *env_help_url() const
    { return "BUBBLETONLAB_DOC"; }

  void normalshift( Real x )
    { _normalshift = x; }

protected:
  Real _normalshift;

private:
  virtual void set_ui_from_data()
    { Controls::set( data() ); }
  virtual void set_data_from_ui()
    { Controls::get( data() ); }
  virtual void load_surface()
    { export_(); }
  virtual base::String const &domain()
    { return data().get("domain"); }

  Data _data;

  base::vector<Bubbleton *> _bubbletonlab;
  base::vector<Complex> _center;
  base::vector<Complex> _size;

  struct MultiData
  {
    math::VectorX<Real,3U> X;
    math::VectorX<Real,3U> N;
  };

  virtual void function(
    MultiData &y,
    Complex const &z,
    uint thread_id ) throw ( base::Exception );


  base::String _varname1, _varname2;

  void initialize_data();

  base::vector<math::VectorX<Real,2U> > _domain_vect;

  base::vector<MultiData> _surface;

  virtual Complex zstart_v() const
    { return 0.0; }

  virtual void start_all_v(
    uint vertex_count,
    uint edge_count,
    uint thread_count );

  virtual void end_all_v(
    uint vertex_count,
    uint edge_count,
    uint thread_count );

  virtual void start_v(
    Complex const &z0,
    uint k0,
    uint thread_id );

  virtual void step_v(
    Complex const &z0,
    Complex const &z1,
    uint k0, uint k1,
    uint thread_id );

  virtual void end_v() {}

  virtual void export_fn_v(
    base::vector<Real> &v,
    uint k );

  static char const *_about_info;

  // disabled copy constructor
  Lab( Lab const & );
  // disabled assignment operator
  Lab & operator=( Lab const & );
};

} // namespace kernel
} // namespace bubbletonlab

#endif // bubbletonlab_kernel_Lab_INCLUDED

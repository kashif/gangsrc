/* GANG Software
 * LAB/minlab/kernel/LabBase.H
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

#ifndef minlab_kernel_LabBase_INCLUDED
#define minlab_kernel_LabBase_INCLUDED

#include "parser/KeyParser.H"
#include "math/VectorX.H"
#include "math/RungeKutta.H"
#include "eval/Eval.H"
#include "lab/kernel/LabBase2.H"
#include "Type.H"
#include "Data.H"
#include "Exception.H"

namespace minlab {
namespace kernel {

class LabBase
  :
    virtual public lab::kernel::LabBase2
{

public:
  // constructor
  LabBase();

  // destructor
  virtual ~LabBase();

  void set_associate( double theta );

protected:

  void initialize_data();

  virtual void start_all_v(
    uint vertex_count,
    uint edge_count,
    uint thread_count );

  virtual void end_all_v(
    uint vertex_count,
    uint edge_count,
    uint thread_count) {}

  enum IntegrationMode { NONE, SPINOR, WEIERSTRASS };

  //
  IntegrationMode _mode;

  //
  uint _integrator_count;

  //
  uint _initial_integrator_count;

  //
  Complex _zstart;

  //
  math::VectorX<Complex,3U> _Xstart;

  static Complex const I;

private:

  //
  class Integrator :
    public math::RungeKutta<Complex,
    math::VectorX<Complex,3U> >
  {
  public:
    Integrator(LabBase *parent, uint thread_id) :
        math::RungeKutta< Complex,
        math::VectorX<Complex,3U> >()
      { _parent = parent; _mode = NONE; _thread_id = thread_id; }
  public:
    void function(
      math::VectorX<Complex,3U> &y,
      Complex const &z,
      math::VectorX<Complex,3U> const & )
      { _parent->integration_function( y, z, _thread_id ); }

    IntegrationMode _mode;
  private:
    LabBase *_parent;
    uint _thread_id;
  };
  friend class Integrator;

  struct MultiData
  {
    Complex z;
    math::VectorX<Complex,3U> S; // (s1^2,s1*s2,s2^2)

  };
  base::vector<MultiData> _multidata;

  //
  void
  compute_segment(
    math::VectorX<Complex,3U> &S,
    Complex &z,
    Complex const &dz,
    uint steps,
    uint thread_id );

  static void spinor(
    Complex &s1,
    Complex &s2,
    Complex const &z );

  virtual Complex zstart_v() const
    { return _zstart; }

  virtual void start_v(
    Complex const &z0,
    uint k0,
    uint thread_id );

  virtual void end_v() {}

  virtual void step_v(
    Complex const &z0,
    Complex const &z1,
    uint k0, uint k1,
    uint thread_id );

  virtual void export_fn_v(
    base::vector<Real> &v,
    uint k );

  Complex _lambda;

  //
  virtual void
  integration_function(
    math::VectorX<Complex,3U> &y,
    Complex const &z,
    uint thread_id ) = 0;

  int
  to_real(
    base::vector<Real> &v,
    math::VectorX<Complex,3U> const &S ) const;

  // disabled copy constructor
  LabBase( LabBase const & );
  // disabled assignment operator
  LabBase &operator=( LabBase const & );

};

} // namespace kernel
} // namespace minlab

#endif // minlab_kernel_LabBase_INCLUDED

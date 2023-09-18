/* GANG Software
 * LAB/minlab/kernel/Lab.H
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

#ifndef minlab_kernel_Lab_INCLUDED
#define minlab_kernel_Lab_INCLUDED

#include "lab/kernel/Lab.H"
#include "minlab/ui/Ui.H"
#include "LabBase.H"

namespace minlab {
namespace kernel {

/*
  Computes minimal surface
*/
class Lab
  :
    
    protected lab::kernel::Lab,
    protected LabBase,
    public ui::Ui
{
public:

  // void constructor
  Lab();

  // destructor
  virtual ~Lab();

  virtual parser::KeyParser const &data() const
    { return _data; }
  virtual parser::KeyParser &data()
    { return _data; }

protected:

  virtual char const *lab_name() const
    { return "MinLab"; }
  virtual char const *about_info() const
    { return _about_info; }
  virtual char const *env_lib_path() const
    { return "MINLAB_LIB"; }
  virtual char const *env_help_url() const
    { return "MINLAB_DOC"; }

  void set_state_from_data();

private:
  // ui->LabBase connection functions
  virtual void set_associate( double theta )
    { LabBase::set_associate(theta); }

  virtual void
  integration_function(
    math::VectorX<Complex,3U> &y,
    Complex const &z,
    uint thread_id );

  virtual void set_ui_from_data()
    { Controls::set( data() ); }
  virtual void set_data_from_ui()
    { Controls::get( data() ); }
  virtual base::String const &name()
    { return data().get("name"); }
  virtual base::String const &domain()
    { return data().get("domain"); }
  virtual void load_surface()
    { export_(); }

  virtual void start_all_v(
    uint vertex_count,
    uint edge_count,
    uint thread_count );

  virtual void end_all_v(
    uint vertex_count,
    uint edge_count,
    uint thread_count) {}

  static char const *_about_info;

  Data _data;

  //
  typedef std::pair<eval::Expression<Complex>,eval::Expression<Complex> >
  SurfExpr2;
  SurfExpr2 _surf_expr0;
  base::vector<SurfExpr2> _surf_expr;

  //
  base::vector<eval::Evaluator<Complex> > _evaluator;

  base::String _varname;

  // disabled copy constructor
  Lab( Lab const & );
  // disabled assignment operator
  Lab &operator=( Lab const & );

};

} // namespace kernel
} // namespace minlab

#endif // minlab_kernel_Lab_INCLUDED

/* GANG Software
 * LAB/lab/gtk/Domain.H
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

#ifndef lab_gtk_Domain_INCLUDED
#define lab_gtk_Domain_INCLUDED

#include "app/app/Dialog.H"
#include "lab/ui/Domain.H"
#include "Domain_.H"

namespace lab {
namespace gtk {

class Domain
  :
    virtual public ui::Domain,
    protected gtk::Domain_,
    public ::app::app::Dialog
{

public:
  // constructor
  Domain(char const *title);

  // destructor
  virtual ~Domain();

protected:

private:

  // connector functions
  virtual void raise_d( bool state = true )
    { ::app::app::Dialog::raise(state); }
  virtual void show_d( bool state = true )
    { ::app::app::Dialog::show(state); }
  virtual void toggle_raise_show_d()
    { ::app::app::Dialog::toggle_raise_show(); }
  virtual void enable_tooltips_d( bool state = true )
    { Domain_::enable_tooltips(state); }
  virtual int key_press_event( uint key, uint state )
    { return key_press_event_d( key, state ); }

  // widgets
  virtual widget::ui::Choice *domain_choice_w()
    { return _domain_choice_w; }
  virtual widget::ui::Choice const *domain_choice_w() const
    { return _domain_choice_w; }
  virtual widget::ui::String *rect_base_w()
    { return _rect_base_w; }
  virtual widget::ui::String const *rect_base_w() const
    { return _rect_base_w; }
  virtual widget::ui::String *rect_a0_w()
    { return _rect_a0_w; }
  virtual widget::ui::String const *rect_a0_w() const
    { return _rect_a0_w; }
  virtual widget::ui::String *rect_count0_w()
    { return _rect_count0_w; }
  virtual widget::ui::String const *rect_count0_w() const
    { return _rect_count0_w; }
  virtual widget::ui::String *rect_a1_w()
    { return _rect_a1_w; }
  virtual widget::ui::String const *rect_a1_w() const
    { return _rect_a1_w; }
  virtual widget::ui::String *rect_count1_w()
    { return _rect_count1_w; }
  virtual widget::ui::String const *rect_count1_w() const
    { return _rect_count1_w; }
  virtual widget::ui::String *polar_center_w()
    { return _polar_center_w; }
  virtual widget::ui::String const *polar_center_w() const
    { return _polar_center_w; }
  virtual widget::ui::String *polar_radius0_w()
    { return _polar_radius0_w; }
  virtual widget::ui::String const *polar_radius0_w() const
    { return _polar_radius0_w; }
  virtual widget::ui::String *polar_radius1_w()
    { return _polar_radius1_w; }
  virtual widget::ui::String const *polar_radius1_w() const
    { return _polar_radius1_w; }
  virtual widget::ui::String *polar_n_radius_w()
    { return _polar_n_radius_w; }
  virtual widget::ui::String const *polar_n_radius_w() const
    { return _polar_n_radius_w; }
  virtual widget::ui::String *polar_angle0_w()
    { return _polar_angle0_w; }
  virtual widget::ui::String const *polar_angle0_w() const
    { return _polar_angle0_w; }
  virtual widget::ui::String *polar_angle1_w()
    { return _polar_angle1_w; }
  virtual widget::ui::String const *polar_angle1_w() const
    { return _polar_angle1_w; }
  virtual widget::ui::String *polar_n_angle_w()
    { return _polar_n_angle_w; }
  virtual widget::ui::String const *polar_n_angle_w() const
    { return _polar_n_angle_w; }
  virtual widget::ui::Choice *polar_mode_w()
    { return _polar_mode_w; }
  virtual widget::ui::Choice const *polar_mode_w() const
    { return _polar_mode_w; }
#if 0
  virtual widget::ui::String *line_x0_w()
    { return _line_x0_w; }
  virtual widget::ui::String const *line_x0_w() const
    { return _line_x0_w; }
  virtual widget::ui::String *line_x1_w()
    { return _line_x1_w; }
  virtual widget::ui::String const *line_x1_w() const
    { return _line_x1_w; }
  virtual widget::ui::String *line_count_w()
    { return _line_count_w; }
  virtual widget::ui::String const *line_count_w() const
    { return _line_count_w; }
  virtual widget::ui::String *circle_center_w()
    { return _circle_center_w; }
  virtual widget::ui::String const *circle_center_w() const
    { return _circle_center_w; }
  virtual widget::ui::String *circle_radius_w()
    { return _circle_radius_w; }
  virtual widget::ui::String const *circle_radius_w() const
    { return _circle_radius_w; }
  virtual widget::ui::String *circle_angle0_w()
    { return _circle_angle0_w; }
  virtual widget::ui::String const *circle_angle0_w() const
    { return _circle_angle0_w; }
  virtual widget::ui::String *circle_angle1_w()
    { return _circle_angle1_w; }
  virtual widget::ui::String const *circle_angle1_w() const
    { return _circle_angle1_w; }
  virtual widget::ui::String *circle_count_w()
    { return _circle_count_w; }
  virtual widget::ui::String const *circle_count_w() const
    { return _circle_count_w; }
#endif
  virtual widget::ui::String *curve_list_w()
    { return _curve_list_w; }
  virtual widget::ui::String const *curve_list_w() const
    { return _curve_list_w; }
  virtual widget::ui::String *boundary_list_w()
    { return _boundary_list_w; }
  virtual widget::ui::String const *boundary_list_w() const
    { return _boundary_list_w; }
  virtual widget::ui::Int *refine_w()
    { return _refine_w; }
  virtual widget::ui::Int const *refine_w() const
    { return _refine_w; }
  virtual widget::ui::Float *min_angle_w()
    { return _min_angle_w; }
  virtual widget::ui::Float const *min_angle_w() const
    { return _min_angle_w; }
  virtual widget::ui::Float *max_area_w()
    { return _max_area_w; }
  virtual widget::ui::Float const *max_area_w() const
    { return _max_area_w; }
  virtual widget::ui::Float *max_area2_w()
    { return _max_area2_w; }
  virtual widget::ui::Float const *max_area2_w() const
    { return _max_area2_w; }
  virtual widget::ui::Float *curvature_exp_w()
    { return _curvature_exp_w; }
  virtual widget::ui::Float const *curvature_exp_w() const
    { return _curvature_exp_w; }
  virtual widget::ui::Float *curvature_cut_w()
    { return _curvature_cut_w; }
  virtual widget::ui::Float const *curvature_cut_w() const
    { return _curvature_cut_w; }
  virtual widget::ui::Float *smooth_w()
    { return _smooth_w; }
  virtual widget::ui::Float const *smooth_w() const
    { return _smooth_w; }
  virtual widget::ui::String *domainfile_w()
    { return _domainfile_w; }
  virtual widget::ui::String const *domainfile_w() const
    { return _domainfile_w; }

  // disabled copy constructor
  Domain( Domain const & );
  // disabled assignment operator
  Domain &operator=( Domain const & );
};

} // namespace gtk
} // namespace lab

#endif // lab_gtk_Domain_INCLUDED

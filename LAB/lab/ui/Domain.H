/* GANG Software
 * LAB/lab/ui/Domain.H
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

#ifndef lab_ui_Domain_INCLUDED
#define lab_ui_Domain_INCLUDED

#include "base/String.H"
#include "base/Exception.H"
#include "parser/KeyParser.H"
#include "widget/ui/Dialog.H"
#include "widget/ui/Choice.H"
#include "widget/ui/String.H"
#include "widget/ui/Int.H"
#include "widget/ui/Float.H"

namespace lab {
namespace ui {

  class Exception : public base::Exception
  {

  public:
    /*
       Error codes arising from bad input. In the case of a GUI, these
       correspond roughly to the widgets.
    */
    enum ErrorCode
    {
      ERR_OK,
      ERR_TRIANGULATED,
      ERR_MAX_AREA,
      ERR_MIN_ANGLE,
      ERR_SMOOTH,
      ERR_REFINE,
      ERR_MAX_AREA2,
      ERR_CURVATURE_EXP,
      ERR_CURVATURE_CUT,
      ERR_DOMAIN_RECT,
      ERR_DOMAIN_POLAR,
      ERR_DOMAIN_POLAR_EXP,
      ERR_DOMAIN_CURVE,
      ERR_DOMAIN_FILE,
      ERR_DOMAIN
    };

    Exception( ErrorCode code ) throw() :
        base::Exception(_message0[code]) {}

  private:
    static char const *const _message0[];
  };


class Lab;

class Domain
  :
    public widget::ui::Dialog
{

public:

  // constructor
  Domain();

  // destructor
  virtual ~Domain();

  bool command(
    base::String const &command,
    base::String const &argument,
    base::String &response );

protected:

  void reset();

  enum DomainTypes
  {
    RECTANGULAR,
    POLAR,
    TRIANGULATED,
    CURVE,
    FILE };


protected:

  char const *label()
    { return "Domain"; }

  void set( parser::KeyParser const & );
  void get( parser::KeyParser & ) const;

private:

  void set( base::String const &domain );
  void _read_rectangular( base::String const &domain );
  void _read_polar( base::String const &domain );
  void _read_polar_exp( base::String const &domain );
  void _read_curve( base::String const &domain );
  void _read_triangulated( base::String const &domain );
  void _read_file( base::String const &domain );

  // pure virtuals
  virtual base::String const &domain() const = 0;

  // widgets
  virtual widget::ui::Choice *domain_choice_w() = 0;
  virtual widget::ui::Choice const *domain_choice_w() const = 0;
  virtual widget::ui::String *rect_base_w() = 0;
  virtual widget::ui::String const *rect_base_w() const = 0;
  virtual widget::ui::String *rect_a0_w() = 0;
  virtual widget::ui::String const *rect_a0_w() const = 0;
  virtual widget::ui::String *rect_count0_w() = 0;
  virtual widget::ui::String const *rect_count0_w() const = 0;
  virtual widget::ui::String *rect_a1_w() = 0;
  virtual widget::ui::String const *rect_a1_w() const = 0;
  virtual widget::ui::String *rect_count1_w() = 0;
  virtual widget::ui::String const *rect_count1_w() const = 0;
  virtual widget::ui::String *polar_center_w() = 0;
  virtual widget::ui::String const *polar_center_w() const = 0;
  virtual widget::ui::String *polar_radius0_w() = 0;
  virtual widget::ui::String const *polar_radius0_w() const = 0;
  virtual widget::ui::String *polar_radius1_w() = 0;
  virtual widget::ui::String const *polar_radius1_w() const = 0;
  virtual widget::ui::String *polar_n_radius_w() = 0;
  virtual widget::ui::String const *polar_n_radius_w() const = 0;
  virtual widget::ui::String *polar_angle0_w() = 0;
  virtual widget::ui::String const *polar_angle0_w() const = 0;
  virtual widget::ui::String *polar_angle1_w() = 0;
  virtual widget::ui::String const *polar_angle1_w() const = 0;
  virtual widget::ui::String *polar_n_angle_w() = 0;
  virtual widget::ui::String const *polar_n_angle_w() const = 0;
  virtual widget::ui::Choice *polar_mode_w() = 0;
  virtual widget::ui::Choice const *polar_mode_w() const = 0;
#if 0
  virtual widget::ui::String *line_x0_w() = 0;
  virtual widget::ui::String const *line_x0_w() const = 0;
  virtual widget::ui::String *line_x1_w() = 0;
  virtual widget::ui::String const *line_x1_w() const = 0;
  virtual widget::ui::String *line_count_w() = 0;
  virtual widget::ui::String const *line_count_w() const = 0;
  virtual widget::ui::String *circle_center_w() = 0;
  virtual widget::ui::String const *circle_center_w() const = 0;
  virtual widget::ui::String *circle_radius_w() = 0;
  virtual widget::ui::String const *circle_radius_w() const = 0;
  virtual widget::ui::String *circle_angle0_w() = 0;
  virtual widget::ui::String const *circle_angle0_w() const = 0;
  virtual widget::ui::String *circle_angle1_w() = 0;
  virtual widget::ui::String const *circle_angle1_w() const = 0;
  virtual widget::ui::String *circle_count_w() = 0;
  virtual widget::ui::String const *circle_count_w() const = 0;
#endif
  virtual widget::ui::String *curve_list_w() = 0;
  virtual widget::ui::String const *curve_list_w() const = 0;
  virtual widget::ui::String *boundary_list_w() = 0;
  virtual widget::ui::String const *boundary_list_w() const = 0;
  virtual widget::ui::Int *refine_w() = 0;
  virtual widget::ui::Int const *refine_w() const = 0;
  virtual widget::ui::Float *min_angle_w() = 0;
  virtual widget::ui::Float const *min_angle_w() const = 0;
  virtual widget::ui::Float *max_area_w() = 0;
  virtual widget::ui::Float const *max_area_w() const = 0;
  virtual widget::ui::Float *max_area2_w() = 0;
  virtual widget::ui::Float const *max_area2_w() const = 0;
  virtual widget::ui::Float *curvature_exp_w() = 0;
  virtual widget::ui::Float const *curvature_exp_w() const = 0;
  virtual widget::ui::Float *curvature_cut_w() = 0;
  virtual widget::ui::Float const *curvature_cut_w() const = 0;
  virtual widget::ui::Float *smooth_w() = 0;
  virtual widget::ui::Float const *smooth_w() const = 0;
  virtual widget::ui::String *domainfile_w() = 0;
  virtual widget::ui::String const *domainfile_w() const = 0;

  // disabled copy constructor
  Domain( Domain const & );
  // disabled assignment operator
  Domain &operator=( Domain const & );

};

} // namespace ui
} // namespace lab

#endif // lab_ui_Domain_INCLUDED

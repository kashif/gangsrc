/* GANG Software
 * LAB/surflab/cmdlab/SurfLab.H
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

#ifndef surflab_cmdlab_SurfLab_INCLUDED
#define surflab_cmdlab_SurfLab_INCLUDED

#include "lab/cmdlab/Lab.H"
#include "surflab/kernel/Lab.H"
#include "surflab/cmd/Ui.H"

namespace surflab {
namespace cmdlab {

class SurfLab
  :
    public kernel::Lab,
    public cmd::Ui
{

public:
  // constructor
  SurfLab();

  // destructor
  virtual ~SurfLab();

  static char const *app_name()
    { return "surflab"; }

protected:

  virtual bool
  command(
    base::String const &command,
    base::String const &argument,
    base::String &response );

private:

  virtual void toggle_raise_show_controls()
    { static_cast< ::surflab::ui::Controls *>(this)->toggle_raise_show_d(); }

  // disabled copy constructor
  SurfLab( SurfLab const & );
  // disabled assignment operator
  SurfLab &operator=( SurfLab const & );
};

} // namespace cmdlab
} // namespace surflab

#endif // surflab_cmdlab_SurfLab_INCLUDED

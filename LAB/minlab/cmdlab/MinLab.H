/* GANG Software
 * LAB/minlab/cmdlab/MinLab.H
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

#ifndef minlab_cmdlab_MinLab_INCLUDED
#define minlab_cmdlab_MinLab_INCLUDED

#include "lab/cmdlab/Lab.H"
#include "minlab/kernel/Lab.H"
#include "minlab/cmd/Ui.H"

namespace minlab {
namespace cmdlab {

class MinLab
  :
    public kernel::Lab,
    public cmd::Ui
{

public:
  // constructor
  MinLab();

  // destructor
  virtual ~MinLab();

  static char const *app_name()
    { return "minlab"; }

protected:

  virtual bool
  command(
    base::String const &command,
    base::String const &argument,
    base::String &response );

private:

  virtual void toggle_raise_show_controls()
    { static_cast< ::minlab::ui::Controls *>(this)->toggle_raise_show_d(); }

  // disabled copy constructor
  MinLab( MinLab const & );
  // disabled assignment operator
  MinLab &operator=( MinLab const & );
};

} // namespace cmdlab
} // namespace minlab

#endif // minlab_cmdlab_MinLab_INCLUDED

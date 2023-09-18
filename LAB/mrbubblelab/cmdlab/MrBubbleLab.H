/* GANG Software
 * LAB/mrbubblelab/cmdlab/MrBubbleLab.H
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

#ifndef mrbubblelab_cmdlab_MrBubbleLab_INCLUDED
#define mrbubblelab_cmdlab_MrBubbleLab_INCLUDED

#include "lab/cmdlab/Lab.H"
#include "mrbubblelab/kernel/Lab.H"
#include "mrbubblelab/cmd/Ui.H"

namespace mrbubblelab {
namespace cmdlab {

class MrBubbleLab
  :
    public kernel::Lab,
    public cmd::Ui
{

public:
  // constructor
  MrBubbleLab();

  // destructor
  virtual ~MrBubbleLab();

  static char const *app_name()
    { return "mrbubblelab"; }

protected:

  virtual bool
  command(
    base::String const &command,
    base::String const &argument,
    base::String &response );

private:

  virtual void toggle_raise_show_controls()
    { static_cast< ::mrbubblelab::ui::Controls *>(this)->toggle_raise_show_d(); }

  // disabled copy constructor
  MrBubbleLab( MrBubbleLab const & );
  // disabled assignment operator
  MrBubbleLab &operator=( MrBubbleLab const & );
};

} // namespace cmdlab
} // namespace mrbubblelab

#endif // mrbubblelab_cmdlab_MrBubbleLab_INCLUDED

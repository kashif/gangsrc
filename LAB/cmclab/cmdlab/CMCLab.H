/* GANG Software
 * LAB/cmclab/cmdlab/CMCLab.H
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

#ifndef cmclab_cmdlab_CMCLab_INCLUDED
#define cmclab_cmdlab_CMCLab_INCLUDED

#include "lab/cmdlab/Lab.H"
#include "cmclab/kernel/Lab.H"
#include "cmclab/cmd/Ui.H"

namespace cmclab {
namespace cmdlab {

class CMCLab
  :
    public kernel::Lab,
    public cmd::Ui
{

public:
  // constructor
  CMCLab();

  // destructor
  virtual ~CMCLab();

  static char const *app_name()
    { return "cmclab"; }

protected:

  virtual bool
  command(
    base::String const &command,
    base::String const &argument,
    base::String &response );

private:

  virtual void toggle_raise_show_controls()
    { static_cast< ::cmclab::ui::Controls *>(this)->toggle_raise_show_d(); }

  // disabled copy constructor
  CMCLab( CMCLab const & );
  // disabled assignment operator
  CMCLab &operator=( CMCLab const & );
};

} // namespace cmdlab
} // namespace cmclab

#endif // cmclab_cmdlab_CMCLab_INCLUDED

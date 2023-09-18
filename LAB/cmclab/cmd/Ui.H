/* GANG Software
 * LAB/cmclab/cmd/Ui.H
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

#ifndef cmclab_cmd_Ui_INCLUDED
#define cmclab_cmd_Ui_INCLUDED

#include "lab/cmd/Ui.H"
#include "Controls.H"

namespace cmclab {
namespace cmd {

class Ui
  :
    public ::lab::cmd::Ui,
    virtual public Controls
{

public:
  // constructor
  Ui();

  // destructor
  virtual ~Ui();

protected:

private:

  // disabled copy constructor
  Ui( Ui const & );

  // disabled assignment operator
  Ui &operator=( Ui const & );

};

} // namespace cmd
} // namespace cmclab

#endif // cmclab_cmd_Ui_INCLUDED

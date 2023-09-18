/* GANG Software
 * LAB/klab/cmdlab/KLab.H
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

#ifndef klab_cmdlab_KLab_INCLUDED
#define klab_cmdlab_KLab_INCLUDED

#include "lab/cmdlab/Lab.H"
#include "klab/kernel/Lab.H"
#include "klab/cmd/Ui.H"

namespace klab {
namespace cmdlab {

class KLab
  :
    public kernel::Lab,
    public cmd::Ui
{

public:
  // constructor
  KLab();

  // destructor
  virtual ~KLab();

  static char const *app_name()
    { return "klab"; }

protected:

  virtual bool
  command(
    base::String const &command,
    base::String const &argument,
    base::String &response );

private:

  virtual void toggle_raise_show_controls()
    { static_cast< ::klab::ui::Controls *>(this)->toggle_raise_show_d(); }

  // disabled copy constructor
  KLab( KLab const & );
  // disabled assignment operator
  KLab &operator=( KLab const & );
};

} // namespace cmdlab
} // namespace klab

#endif // klab_cmdlab_KLab_INCLUDED

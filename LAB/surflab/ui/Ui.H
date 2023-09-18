/* GANG Software
 * LAB/surflab/ui/Ui.H
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

#ifndef surflab_ui_Ui_INCLUDED
#define surflab_ui_Ui_INCLUDED

#include "lab/ui/Ui.H"
#include "Controls.H"

namespace surflab {
namespace ui {

class Ui
  :
    virtual public ::lab::ui::Ui,
    virtual public Controls
{
public:

  // constructor
  Ui();

  // destructor
  virtual ~Ui();

  virtual bool command(
    base::String const &command,
    base::String const &argument,
    base::String &response );

protected:

  void show_all(bool state);
  void enable_tooltips(bool state);

private:

  Controls *controls_p() { return this; }

  // disabled copy constructor
  Ui( Ui const & );

  // disabled assignment operator
  Ui &operator=( Ui const & );
};

} // namespace ui
} // namespace surflab

#endif // surflab_ui_Ui_INCLUDED

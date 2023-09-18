/* GANG Software
 * LAB/bubbletonlab/ui/Ui.H
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

#ifndef bubbletonlab_ui_Ui_INCLUDED
#define bubbletonlab_ui_Ui_INCLUDED

#include "lab/ui/Ui.H"
#include "Controls.H"

namespace bubbletonlab {
namespace ui {

class Ui
  :
    virtual public lab::ui::Ui,
    virtual public Controls
{
public:

  // constructor
  Ui();
    
  // destructor
  virtual ~Ui();

  void toggle_raise_show_controls()
    { static_cast< ::bubbletonlab::ui::Controls *>(this)->toggle_raise_show_d(); }

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
} // namespace bubbletonlab

#endif // bubbletonlab_ui_Ui_INCLUDED

/* GANG Software
 * LAB/lab/cmd/Ui.C
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

#include "Ui.H"

namespace lab {
namespace cmd {

Ui::
Ui()
  :
    Compute(),
    Domain(),
    Sequence(),
    Read(),
    Write()
#if FIX
    _read_b(
      (base::String("Open ") +
       base::String(lab->app_name()) +
       base::String(" File")).c_str(),
       lab->env_lib_path(), base ),
    _write_b(
      (base::String("Save ") +
       base::String(lab->app_name()) +
       base::String(" File")).c_str(), base )
#endif
{
}

Ui::
~Ui()
{
}

} // namespace cmd
} // namespace lab

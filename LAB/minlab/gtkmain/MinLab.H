/* GANG Software
 * LAB/minlab/gtkmain/MinLab.H
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

#ifndef minlab_gtkmain_MinLab_INCLUDED
#define minlab_gtkmain_MinLab_INCLUDED

#include "minlab/gtklab/MinLab.H"
#include "lab/gtklab/Lab.H"

namespace minlab {
namespace gtkmain {

class MinLab
  :
    public ::lab::gtklab::Lab< ::minlab::gtklab::MinLab>
{

public:
  // constructor
  MinLab();

  // destructor
  virtual ~MinLab();

protected:

private:

  // disabled copy constructor
  MinLab( MinLab const & );
  // disabled assignment operator
  MinLab &operator=( MinLab const & );

};

} // namespace gtkmain
} // namespace minlab

#endif // minlab_gtkmain_MinLab_INCLUDED

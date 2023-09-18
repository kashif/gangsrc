/* GANG Software
 * LAB/mrbubblelab/cmdmain/MrBubbleLab.H
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

#ifndef mrbubblelab_cmdmain_MrBubbleLab_INCLUDED
#define mrbubblelab_cmdmain_MrBubbleLab_INCLUDED

#include "lab/cmdlab/Lab.H"
#include "mrbubblelab/cmdlab/MrBubbleLab.H"

namespace mrbubblelab {
namespace cmdmain {

class MrBubbleLab
  :
    public ::lab::cmdlab::Lab< ::mrbubblelab::cmdlab::MrBubbleLab>
{

public:
  // constructor
  MrBubbleLab();

  // destructor
  virtual ~MrBubbleLab();

protected:

private:

  // disabled copy constructor
  MrBubbleLab( MrBubbleLab const & );
  // disabled assignment operator
  MrBubbleLab &operator=( MrBubbleLab const & );

};

} // namespace cmdmain
} // namespace mrbubblelab

#endif // mrbubblelab_cmdmain_MrBubbleLab_INCLUDED

/* GANG Software
 * LAB/bubbletonlab/cmdmain/BubbletonLab.H
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

#ifndef bubbletonlab_cmdmain_BubbletonLab_INCLUDED
#define bubbletonlab_cmdmain_BubbletonLab_INCLUDED

#include "lab/cmdlab/Lab.H"
#include "bubbletonlab/cmdlab/BubbletonLab.H"

namespace bubbletonlab {
namespace cmdmain {

class BubbletonLab
  :
    public ::lab::cmdlab::Lab< ::bubbletonlab::cmdlab::BubbletonLab>
{

public:
  // constructor
  BubbletonLab();

  // destructor
  virtual ~BubbletonLab();

protected:

private:

  // disabled copy constructor
  BubbletonLab( BubbletonLab const & );
  // disabled assignment operator
  BubbletonLab &operator=( BubbletonLab const & );

};

} // namespace cmdmain
} // namespace bubbletonlab

#endif // bubbletonlab_cmdmain_BubbletonLab_INCLUDED

/* GANG Software
 * VIEWER/isight/context/Axes.H
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

#ifndef isight_context_Axes_INCLUDED
#define isight_context_Axes_INCLUDED

namespace isight {
namespace context {

class Axes
{

public:
  // constructor
  Axes();

  // destructor
  virtual ~Axes();

  bool enable() const
    { return _enable; }
  void enable( bool state )
    { _enable = state; }
  void draw() const;

protected:

private:

  bool _enable;

  static float const axes_plus[3][3];
  static float const axes_minus[3][3];
  static float const axes_color_plus[3][3];
  static float const axes_color_minus[3][3];

  // disabled copy constructor
  Axes( Axes const & );

  // disabled assignment operator
  Axes &operator=( Axes const & );

};

} // namespace context
} // namespace isight

#endif // isight_context_Axes_INCLUDED

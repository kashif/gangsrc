/* GANG Software
 * VIEWER/isight/context/Background.H
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

#ifndef isight_context_Background_INCLUDED
#define isight_context_Background_INCLUDED

#include "Axes.H"
#include "Sphere.H"
#include "Stars.H"
#include "Write.H"

namespace isight {
namespace context {

class Background
  :
    public Write
{

public:
  // constructor
  Background( ContextSetBase *base );

  // destructor
  virtual ~Background();

  virtual bool axes() const
    { return _axes.enable(); }
  virtual void axes(bool state)
    { _axes.enable(state); refresh(); }
  virtual void sphere(bool state)
    { _sphere.mode(state ? Sphere::CIRCLE : Sphere::DISABLED); refresh(); }
  virtual bool sphere() const
    { return _sphere.mode(); }
  virtual void stars(bool state)
    { _stars.enable(state); refresh(); }
  virtual bool stars() const
    { return _stars.enable(); }

protected:

  void draw_background() const
    {
      _axes.draw();
      _sphere.draw();
      _stars.draw();
    }
private:

  Axes _axes;
  Sphere _sphere;
  Stars _stars;

  // disabled copy constructor
  Background( Background const & );
  // disabled assignment operator
  Background &operator=( Background const & );

};

} // namespace context
} // namespace isight

#endif // isight_context_Background_INCLUDED

/* GANG Software
 * GEOM/geom/io/IsxRead.H
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

#ifndef geom_io_IsxRead_INCLUDED
#define geom_io_IsxRead_INCLUDED

#include <list>
#include "geom/surface/MaterialSet.H"
#include "JvxRead.H"

namespace geom {
namespace io {

class IsxRead
  :
    public JvxRead
{

public:
  typedef double Real;
  typedef math::Matrix<Real> Transform;

  // constructor
  IsxRead();

  // destructor
  virtual ~IsxRead();

protected:

private:

  virtual void initialize();
  virtual void finalize();
  virtual void start_tag_cb(
    char const *tag,
    AttributeList const &attributes );
  virtual void end_tag_cb( char const *tag );

  void custom_color();
  virtual void _finalize();

  virtual void end_geometry( surface0::Surface & );

  enum Mode
  { NOTHING_MODE, MILIEU, MATERIALSET, CUSTOMCOLOR };

  Mode _mode;

  enum MilieuMode 
  { NOTHING_MILIEUMODE,
    BACKGROUND,
    DEPTH,
    BLEND,
    FOG,
#if 0
    HINTS,
#endif
    CLIPPLANESET,
    CAMERA,
    GLOBALLIGHT,
    LIGHTSET };

  MilieuMode _milieumode;
  uint _material_id;
  uint _clipplane_id;
  uint _light_id;

  geom::surface::MaterialSet _materials;

  Transform _position;

  struct CustomColor
  {
    bool enable;
    uint mode;
    base::Color4 color0;
    base::Color4 color1;
    float scale;
  };
  CustomColor _custom_color;

  // disabled copy constructor
  IsxRead( IsxRead const & );
  // disabled assignment operator
  IsxRead &operator=( IsxRead const & );

};

} // namespace io
} // namespace geom

#endif // geom_io_IsxRead_INCLUDED

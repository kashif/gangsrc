/* GANG Software
 * VIEWER/isight/context/Write.H
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

#ifndef isight_context_Write_INCLUDED
#define isight_context_Write_INCLUDED

#include "imagegl/Postscript.H"
#include "imagegl/ScreenDump.H"
#include "imagegl/ScreenLoad.H"
#include "GeomObjectSet.H"

namespace isight {
namespace context {

class Write
  :
    public GeomObjectSet,
    public imagegl::ScreenLoad,
    public imagegl::ScreenDump,
    public imagegl::PostScript
{

public:
  // constructor
  Write( ContextSetBase *base );

  // destructor
  virtual ~Write();

protected:

  // write image according to file extension
  virtual void write_image( base::String const &filename ) const;

  // write image in postscript format
  void write_postscript( io::Ostream &stream, bool EPS ) const
    { ((Write *)this)->stop_motion();
    ((Write *)this)->PostScript::write( stream, EPS ); }

  // set the background image
  virtual void background_image(
    base::String const &filename, bool on_top );

  // set the background image
  virtual void background_image(
    base::String const &filename )
    { background_image(filename, false ); }

  // clear the background image
  virtual void background_clear_image();

private:
  virtual void enable_draw(bool) = 0;
  virtual uint area_width() const = 0;
  virtual uint area_height() const = 0;

  // for geom::opengl::ScreenDump
  virtual base::Color3 const &background_color() const
    { return milieu()->Background::color(); }

  // for geom::opengl::ScreenDump
  virtual void set_window_size( uint x, uint y )
    { milieu::opengl::Milieu::set_window_size(x, y); }

  // get the size for an image to be written
  void size_for_image( uint &x, uint &y ) const;

  // disabled copy constructor
  Write( Write const & );
  // disabled assignment operator
  Write &operator=( Write const & );

};

} // namespace context
} // namespace isight

#endif // isight_context_Write_INCLUDED

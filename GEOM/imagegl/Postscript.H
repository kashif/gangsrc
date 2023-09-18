/* GANG Software
 * GEOM/imagegl/Postscript.H
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

#ifndef imagegl_Postscript_INCLUDED
#define imagegl_Postscript_INCLUDED

#include "io/Ostream.H"
#include "PostscriptBase.H"

namespace imagegl {

/*
  This library prints OpenGL images in PostScript format.
  It produces high-quality rescalable vector/polygon graphics,
    not geom/bitmap graphics.
  It works using the OpenGL feedback mechanism.<br><br>

  This library is divided into three classes:<br><br>

  class PostScript - PostScript part of the implementation<br>
  class PostscriptBase - OpenGL part of the implementation<br><br>

  Use the library like this:<br>
    (1) create a PostScript instance X<br>
    (2) call X->set_ostream(o)<br>
    (2) in your imagegl draw handler method, render
        the object with OpenGL commands between calls X->begin() and
        X->end()<br><br>

  The library works by sorting the polygons by depth. It does not
  cull hidden polygons.<br><br>

  See also<br>
    (1) http://www.easysw.com/~mike/imagegl/index.html<br>
    (2) http://reality.sgi.com/mjk_asd/tips/Feedback.html<br>
    (3) geomview<br><br>


  Class PostscriptBase is
    the OpenGL part of the OpenGL-to-PostScript library.
  Class PostScript is
    the PostScript part of the OpenGL-to-PostScript library.

  <br><br>
  Acknowledgements:
  This code is modified from GLP, an OpenGL to Postscript class library by
  Michael Sweet. http://www.easysw.com/~mike/imagegl/ .
*/


class PostScript
  :
  public PostscriptBase
{
public:

  // void constructor
  PostScript() throw();

  // destructor
  ~PostScript() throw();

  void write( ::io::Ostream &o, bool EPS );

protected:

  virtual void draw() = 0;

  // begin_(), end_() performs the PostScript side of the conversion
  virtual void begin_() throw( ::io::WriteException );

  /*
    write list of elements in PostScript form
    write postscript trailer
  */
  virtual void end_() throw( ::io::WriteException );

private:

  int _page_count;     // Page count
  ::io::Ostream *_ostream;      // Output file
  int _status;

  void write_postscript_header( ::io::Ostream &o )
    throw( ::io::WriteException );

  bool _EPS;

  // disabled copy constructor
  PostScript( PostScript const & ) throw();

  // disabled assignment operator
  PostScript &operator=( PostScript const & ) throw();
};

} // namespace imagegl

#endif // imagegl_Postscript_INCLUDED

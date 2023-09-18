/* GANG Software
 * GEOM/imagegl/PostscriptBase.H
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

#ifndef imagegl_PostscriptBase_INCLUDED
#define imagegl_PostscriptBase_INCLUDED

#include <list>
#include "opengl/OpenGL.H"
#include "io/WriteException.H"

namespace imagegl {

class PostscriptBase
{
public:

  // void constructor
  PostscriptBase() throw();

  // destructor
  virtual ~PostscriptBase() throw();

  // wrap your OpenGL drawing routines in begin() and end()


  /*
     puts OpenGL into feedback mode, calls begin_
  */
  virtual void begin() throw ( ::io::WriteException );

  /*
    parse the OpenGL feedback buffer, sort the geometric elements
  */
  virtual int end() throw ( ::io::WriteException );

  // Color type
  typedef GLfloat Color[4];

  // flags
  void set_fit_to_page(bool f) throw() { _fit_to_page = f; }
  void set_greyscale(bool f) throw() { _greyscale = f; }
  void set_draw_background(bool f) throw() { _draw_background = f; }
  void set_colormap( Color const *colormap, uint colormapsize )
    throw();

  void set_autocrop(bool f) throw() { _autocrop = f; } // not implemented
  void set_reverse(bool f) throw() { _reverse = f; } // not implemented

protected:
  typedef GLfloat Vertex4[3];

  // CVertex holds position and color information
  struct CVertex
  {
    Vertex4 xyz; // position
    Color rgba; // color
  };

  // Element struct holds point/line/polygon
  struct Element
  {
    base::vector<CVertex> vertex;       // base::vector of vertexs
    GLfloat       zmin, zmax;     // min and max depth values
    GLboolean     shade;          // true if this element should be shaded
  };

  // depth sort compare function
  static int ElementCompare( Element const *a, Element const *b )
    throw()
  {
    return a->zmin > b->zmin;
  };

  // std::list of polygons
  std::list<Element *> _element_list;

  // in feedback mode, OpenGL dumps its output into this buffer
  int _gl_feedback_buffer_size;    // Feedback buffer size
  GLfloat *_gl_feedback_buffer;   // Feedback data

  // color std::map used in color index mode
  Color *_colormap;

  // flags
  bool _fit_to_page;
  bool _autocrop;
  bool _greyscale;
  bool _reverse;
  bool _draw_background;


  /*
     parse the OpenGL feedback buffer
  */
  void parse_gl_feedback_buffer(uint token_count) throw();

  /*
     add an element to the std::list of elements
     an element is a point/line/polygon
  */
  void insert_element( base::vector<CVertex> const &,  bool depth, bool shade )
    throw();

  /*
     get a vertex from the feedback buffer
  */
  int get_vertex(CVertex &, GLfloat *p) throw();

  /*
    delete all bounding boxes and elements from the current context.
  */
  void delete_all() throw();

  virtual void begin_() throw( ::io::WriteException ) = 0;

  virtual void end_() throw( ::io::WriteException ) =0;

private:
  // disabled copy constructor
  PostscriptBase( PostscriptBase const & ) throw();
  // disabled assignment operator
  PostscriptBase &operator=(PostscriptBase const &) throw();

};


} // namespace imagegl

#endif // imagegl_PostscriptBase_INCLUDED

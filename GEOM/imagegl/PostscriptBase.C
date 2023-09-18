/* GANG Software
 * GEOM/imagegl/PostscriptBase.C
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

#include "PostscriptBase.H"

namespace imagegl {

PostscriptBase::
PostscriptBase()
    throw()
    :
    _element_list()
{
  _gl_feedback_buffer_size = 0;
  _gl_feedback_buffer = (GLfloat *)0;
  _colormap = (Color *)0;

  _fit_to_page = true;
  _autocrop = false;
  _greyscale = false;
  _reverse = false;
  _draw_background = true;
}

PostscriptBase::
~PostscriptBase()
    throw()
{

  delete_all();

  if (_gl_feedback_buffer != (GLfloat *)0)
  {
    delete _gl_feedback_buffer;
  }

  if (_colormap != (Color *)0)
  {
    delete _colormap;
  }
}

void
PostscriptBase::
begin()
    throw( ::io::WriteException )
{
  // Initialize OpenGL feedback mode
  _gl_feedback_buffer_size = 1024*1024;

  _gl_feedback_buffer = new GLfloat[_gl_feedback_buffer_size];
  DIE_IF( _gl_feedback_buffer == 0 );

  // call glFeedbackBuffer() to specify the array to hold the feedback
  //   information
  glFeedbackBuffer(_gl_feedback_buffer_size, GL_3D_COLOR, _gl_feedback_buffer);

  // put OpenGL into feedback mode
  glRenderMode( GL_FEEDBACK );

  begin_();
}


int
PostscriptBase::
end()
    throw( ::io::WriteException )
{
  // return:
  //  0: done
  //  1: not done

  // put OpenGL into render mode
  // save the buffer length
  uint n = glRenderMode( GL_RENDER );

  if ( n == 0 )
  {
    // no values were transferred to the feedback buffer
    return 1;
  }

  parse_gl_feedback_buffer(n);

#ifdef __STL_MEMBER_TEMPLATES
  _element_list.sort(&ElementCompare);
#endif

  end_();

  // Delete everything from the bounding box and element lists

  delete_all();
  return 0;
}

// set the colormap
void
PostscriptBase::
set_colormap(Color const *colormap, uint colormap_size)
  throw()
{
  // Copy the colormap, removing the old one if necessary

  if ( _colormap != (Color *)0)
  {
    delete colormap;
    colormap = (Color *)0;
  }

  if ( colormap_size > 0 )
  {
    // NOTE: memory leak?
    colormap  = new Color[colormap_size];
    memcpy(_colormap, colormap, colormap_size * sizeof(Color));
  }
}

void
PostscriptBase::
parse_gl_feedback_buffer(uint n)
  throw()
{
//  int           i, used, count, v;
  GLboolean     depth;
  GLboolean     shade;
  GLint         shademodel;

  // Get the current depth test state and shade model

  depth = glIsEnabled(GL_DEPTH_TEST);
  glGetIntegerv(GL_SHADE_MODEL, &shademodel);
  shade = shademodel == GL_SMOOTH;

  // Parse the feedback buffer
  GLfloat *p = _gl_feedback_buffer;

  CVertex v;
  base::vector<CVertex> vertex1;
  vertex1.reserve(1);
  vertex1.push_back(v);

  base::vector<CVertex> vertex2;
  vertex2.reserve(2);
  vertex2.push_back(v);
  vertex2.push_back(v);

  base::vector<CVertex> vertex3;
  vertex3.reserve(3);
  vertex3.push_back(v);
  vertex3.push_back(v);
  vertex3.push_back(v);

  base::vector<CVertex> vertexN;
  vertexN.reserve(4);

  uint j = 0;
  while ( j < n )
  {
    GLenum tok = (GLenum)(int)p[j];
    j++;
    if ( tok == GL_POINT_TOKEN )
    {
      // point token
      j += get_vertex(vertex1[0], p+j);
//      Element e;
      insert_element(vertex1, depth, shade);
    }
    else if ( tok == GL_LINE_RESET_TOKEN ||
              tok == GL_LINE_TOKEN )
    {
      // line token
      j += get_vertex(vertex2[0], p+j);
      j += get_vertex(vertex2[1], p+j);
      insert_element(vertex2, depth, shade);
    }
    else if ( tok == GL_POLYGON_TOKEN )
    {
      // polgon token
      // Get the number of vertex
      uint count = (int)p[j];
      j++;

      if ( count == 3 )
      {
        // triangle
        j += get_vertex(vertex3[0], p+j);
        j += get_vertex(vertex3[1], p+j);
        j += get_vertex(vertex3[2], p+j);
        insert_element( vertex3, depth, shade );
      }
      else
      {
        // N-polygon
        CVertex v;
        vertexN.clear();

        uint i;
        for ( i = 0; i < count; i++ )
        {
          j += get_vertex(v, p+j);
          vertexN.push_back(v);
        }
        insert_element( vertexN, depth, shade );
      }
    }
    else if ( tok == GL_BITMAP_TOKEN ||
              tok == GL_DRAW_PIXEL_TOKEN ||
              tok == GL_COPY_PIXEL_TOKEN )
    {
      CVertex v;
      j += get_vertex(v, p+j);
    }
    else if ( tok == GL_PASS_THROUGH_TOKEN )
    {
      // pass-through token
      j++;
    }
    else if ( tok == GL_LINE_RESET_TOKEN )
    {
      // line reset token
      j++;
    }
    else
    {
      // unknown token
      std::cout << "glpostscript: ignoring unknown token "
                << (int)p[j] << "\n" << std::flush;
    }
  }
}

void
PostscriptBase::
insert_element(
  base::vector<CVertex> const &v,
  bool depth,    // Depth testing enabled?
  bool shade)    // Smooth shading?
  throw()
{
  USE(depth);

  DIE_IF(v.size() == 0 );
  // create a new element and compute the bounding box for it

  Element *newelement = new Element;

  newelement->shade = shade;
  newelement->vertex = v;  // inefficient copy

  //----------------------------------------------------
  // compute min and max
  GLfloat zmin = FLT_MAX;

#if 0
  // NOTE: is this right or should it be -FLT_MAX?
  GLfloat zmax = FLT_MIN;
#endif
  GLfloat zmax = -FLT_MAX;


  uint i;
  size_t n = v.size();
#if 0
  std::cerr << "polygon\n";
  for (i = 0; i < n; i++)
  {
    std::cerr << "  vertex: "
              << v[i].xyz[0] << " "
              << v[i].xyz[1] << " "
              << v[i].xyz[2] << std::endl;
  }
#endif
  for (i = 0; i < n; i++)
  {
    if (v[i].xyz[2] < zmin) { zmin = v[i].xyz[2]; }
    if (v[i].xyz[2] > zmax) { zmax = v[i].xyz[2]; }
  }

  newelement->zmin = zmin;
  newelement->zmax = zmax;

  //----------------------------------------------------
  _element_list.push_back(newelement);
}

int
PostscriptBase::
get_vertex(
  CVertex &v,  // Vertex4 pointer
  GLfloat *p)  // Data pointer
  throw()
{
  int i;   // Color index

  v.xyz[0] = p[0];
  v.xyz[1] = p[1];
  v.xyz[2] = p[2];

  if ( _colormap == 0 )
  {
    // RGBA value

    v.rgba[0] = p[3];
    v.rgba[1] = p[4];
    v.rgba[2] = p[5];
    v.rgba[3] = p[6];

    return 7;
  }
  else
  {
    // Color index value
    i = (int)(p[3] + 0.5);

    v.rgba[0] = _colormap[i][0];
    v.rgba[1] = _colormap[i][1];
    v.rgba[2] = _colormap[i][2];
    v.rgba[3] = _colormap[i][3];

    return 4;
  }
}


void
PostscriptBase::
delete_all()
  throw()
{
  std::list<Element *>::iterator i;
  for ( i = _element_list.begin(); i != _element_list.end(); i++ )
  {
    delete *i;
  }
  _element_list.clear();
}


} // namespace imagegl

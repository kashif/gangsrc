/* GANG Software
 * GEOM/geom/surfacegl/SurfDrawer.C
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

#include "opengl/OpenGL.H"
#include "SurfDrawer.H"

namespace geom {
namespace surfacegl {

SurfDrawer::
SurfDrawer()
    :
    _draw_normal(true),
    _draw_color(false),
    _normal_nudge(0.0),
    _transform_inv()
{
}

SurfDrawer::
~SurfDrawer()
{
}

void
SurfDrawer::
_draw() const
{
  // compute _transform_inv
  if (_use_transform)
  {
    uint i;
    for ( i = 0; i < MaterialSet::count(); i++ )
    {
      if (_materials->draw_normal(i))
      {
        _transform_inv.inv(_transform);
        break;
      }
    }
  }

  uint i;
  for ( i = 0; i < MaterialSet::count(); i++ )
  {
    if ( ! _materials->draw(i) ) { continue; }

    _draw_normal = _materials->draw_normal(i);
    if (_draw_normal) { surface()->compute_normal(); }

    _draw_color = surface()->has_array_color()
      && _materials->draw_color(i);

#if 0
    // default color
    if ( i == 0 )
    {
      glColor( surface()->fixed_color() );
    }
#endif
    _materials->begin(i);
    draw_element(i);
    _materials->end(i);
  }
}

void
SurfDrawer::
draw_element( uint i ) const
{
  if (i == MaterialSet::POINT) { draw_points(); }
  else if (i == MaterialSet::LINE) { draw_lines(); }
  else if (i == MaterialSet::BOUNDARY) { draw_boundary(); }
  else if (i == MaterialSet::SILHOUETTE) { draw_silhouette(); }
  else if (i == MaterialSet::BBOX) { draw_bbox(); }
  else { _draw_element(i); }
}

void
SurfDrawer::
_draw_element( uint item ) const
{
  bool shaded = _materials->shademodel(item);
  
  // note: should be drawn as triangles in case of
  //   non-convexity or self-intersection

  base::ArrayX<float,2U> const &gap = _materials->gap(item);

  if ( gap[0] == 0.0f && gap[1] == 0.0f )
  {
    // draw full faces
    uint i;
    for( i = 0; i < surface()->face_count(); i++)
    {
      if ( ! shaded )
      {
        draw_face_normal(i);
        draw_face_color(i);
      }
        
      uint j;
      uint m = surface()->face_count(i);
      glBegin(GL_POLYGON);
      for( j = 0; j < m; j++ )
      {
        uint k = surface()->face_vertex(i,j);
        if ( shaded )
        {
          draw_vertex_normal(k);
          draw_vertex_color(k);
        }
        draw_vertex(k);
      }
      glEnd();
    }
  }
  else if (gap[1] == 0.0f)
  {
    // draw smaller or larger faces
    uint i;
    for( i = 0; i < surface()->face_count(); i++ )
    {
      if ( ! shaded )
      {
        draw_face_normal(i);
        draw_face_color(i);
      }

      geom::Vertex3 c = surface()->face_center(i);
      c *= gap[0];

      geom::Vertex3 a;
      glBegin(GL_POLYGON);
      uint j;
      for( j = 0; j < surface()->face_count(i); j++ )
      {
        uint k = surface()->face_vertex(i,j);
        surface()->vertex( a, k );
        a *= 1.0-gap[0];
        a += c;

        if ( shaded )
        {
          draw_vertex_normal(k);
          draw_vertex_color(k);
        }
        draw_vertex(a);
      }
      glEnd();
    }
  }
  else
  {
    // draw faces with hole in middle
    uint i;
    for( i = 0; i < surface()->face_count(); i++)
    {
      if ( ! shaded )
      {
        draw_face_normal(i);
        draw_face_color(i);
      }
      geom::Vertex3 const &c = surface()->face_center(i);

      uint m = surface()->face_count(i);
      uint j0;
      glBegin(GL_QUAD_STRIP);
      for( j0 = 0; j0 <= m; j0++ )
      {
        uint j = ( j0 == m ? 0 : j0 );
        uint k = surface()->face_vertex(i,j);
        geom::Vertex3 v;
        surface()->vertex( v, k );
        
        geom::Vertex3 a = (Real(1.0-gap[0])*v) +
          (Real(gap[0])*c);
        geom::Vertex3 b = (Real(gap[1])*v) +
          (Real(1.0-gap[1])*c);
        if ( shaded )
        {
          draw_vertex_normal(k);
          draw_vertex_color(k);
        }

        if ( gap[0] <= 1.0 - gap[1] )
        {
          draw_vertex(b);
          draw_vertex(a);
        }
        else
        {
          draw_vertex(a);
          draw_vertex(b);
        }
      }
      glEnd();
    }
  }
}

void
SurfDrawer::
draw_points() const
{
  glBegin(GL_POINTS);
  uint i;
  for ( i = 0; i < surface()->vertex_count(); i++ )
  {
    draw_vertex_normal(i);
    draw_vertex_color(i);
    draw_vertex(i);
  }
  glEnd();
}

void
SurfDrawer::
draw_lines() const
{
  using std::list;

  list<list<uint> > const &line = surface()->line();
  list<list<uint> >::const_iterator i;
  for ( i = line.begin(); i != line.end(); i++ )
  {
    glBegin(GL_LINE_STRIP);
    list<uint>::const_iterator j;
    for ( j = (*i).begin(); j != (*i).end(); j++ )
    {
      draw_vertex_normal(*j);
      draw_vertex_color(*j);
      draw_vertex(*j);
    }
    glEnd();
  }
}

void
SurfDrawer::
draw_boundary() const
{
  using std::list;
  typedef std::pair<uint,uint> uint_pair;

  list<list<uint_pair> > boundary;
  surface()->boundary(boundary);

  list<list<uint_pair> >::const_iterator i;
  for ( i = boundary.begin(); i != boundary.end(); i++ )
  {
    glBegin(GL_LINES);
    list<uint_pair>::const_iterator j;
    for ( j = (*i).begin(); j != (*i).end(); j++ )
    {
      // draw the first point of the line segment
      uint p = (*j).first;
      draw_vertex_normal(p);
      draw_vertex_color(p);
      draw_vertex(p);

      // draw the second point of the line segment
      p = (*j).second;
      draw_vertex_normal(p);
      draw_vertex_color(p);
      draw_vertex(p);
    }
    glEnd();
  }
}


void
SurfDrawer::
draw_silhouette() const
{
  // return if the surface is a chopped GRID (edge() is then invalid)
  if ( surface()->type() == ::geom::surface0::Surface::GRID )
  {
    if (surface()->i_begin() != 0 ||
        surface()->i_count() != surface()->i_step() ||
        surface()->j_begin() != 0 ||
        surface()->j_count() != surface()->j_step() )
    {
      return;
    }
  }

  math::Matrix4<Real> proj;
  ::opengl::glGet( GL_PROJECTION_MATRIX, proj.data() );

  math::Matrix4<Real> model;
  ::opengl::glGet( GL_MODELVIEW_MATRIX, model.data() );

  math::Matrix4<Real> transform = proj;
  transform.mulleft( model );

  surface0::Surface::EdgeMap::const_iterator i;
  for( surface()->first_silhouette_segment(i, transform);
       i != surface()->edge().end();
       surface()->next_silhouette_segment(i) )
  {
    glBegin(GL_LINES);

    // draw the first point of the line segment
    uint j = (*i).first.first;
    draw_vertex_normal(j);
    draw_vertex_color(j);
    draw_normal_nudge(j);

    // draw the second point of the line segment
    j = (*i).first.second;
    draw_vertex_normal(j);
    draw_vertex_color(j);
    draw_normal_nudge(j);

    glEnd();
  }
}

void
SurfDrawer::
draw_bbox() const
{
#if 0
  glPushAttrib(GL_ALL_ATTRIB_BITS);
  glDisable(GL_LIGHTING);
  glEnable( GL_POINT_SMOOTH );
#endif
//  glEnable( GL_LINE_SMOOTH );

//  glPushMatrix();

#if 0
  glColor3f( 0.51, 0.51, 0.51 );

  // draw lines
  glLineWidth( 1.0f );
#endif

  geom::Box const &b = surface()->box();

  glBegin(GL_QUADS);


  // z planes
  glVertex3f( b.xmin, b.ymin, b.zmin );
  glVertex3f( b.xmin, b.ymax, b.zmin );
  glVertex3f( b.xmax, b.ymax, b.zmin );
  glVertex3f( b.xmax, b.ymin, b.zmin );

  glVertex3f( b.xmax, b.ymax, b.zmax );
  glVertex3f( b.xmin, b.ymax, b.zmax );
  glVertex3f( b.xmin, b.ymin, b.zmax );
  glVertex3f( b.xmax, b.ymin, b.zmax );

    // y planes
  glVertex3f( b.xmin, b.ymin, b.zmin );
  glVertex3f( b.xmax, b.ymin, b.zmin );
  glVertex3f( b.xmax, b.ymin, b.zmax );
  glVertex3f( b.xmin, b.ymin, b.zmax );

  glVertex3f( b.xmax, b.ymax, b.zmax );
  glVertex3f( b.xmax, b.ymax, b.zmin );
  glVertex3f( b.xmin, b.ymax, b.zmin );
  glVertex3f( b.xmin, b.ymax, b.zmax );

    // x planes
  glVertex3f( b.xmin, b.ymin, b.zmin );
  glVertex3f( b.xmin, b.ymin, b.zmax );
  glVertex3f( b.xmin, b.ymax, b.zmax );
  glVertex3f( b.xmin, b.ymax, b.zmin );

  glVertex3f( b.xmax, b.ymax, b.zmax );
  glVertex3f( b.xmax, b.ymin, b.zmax );
  glVertex3f( b.xmax, b.ymin, b.zmin );
  glVertex3f( b.xmax, b.ymax, b.zmin );
  glEnd();


#if 0
  glBegin(GL_LINES);
  // x-lines
  glVertex3f( b.xmin, b.ymin, b.zmin );
  glVertex3f( b.xmax, b.ymin, b.zmin );
  glVertex3f( b.xmin, b.ymin, b.zmax );
  glVertex3f( b.xmax, b.ymin, b.zmax );
  glVertex3f( b.xmin, b.ymax, b.zmin );
  glVertex3f( b.xmax, b.ymax, b.zmin );
  glVertex3f( b.xmin, b.ymax, b.zmax );
  glVertex3f( b.xmax, b.ymax, b.zmax );
  // y-lines
  glVertex3f( b.xmin, b.ymin, b.zmin );
  glVertex3f( b.xmin, b.ymax, b.zmin );
  glVertex3f( b.xmin, b.ymin, b.zmax );
  glVertex3f( b.xmin, b.ymax, b.zmax );
  glVertex3f( b.xmax, b.ymin, b.zmin );
  glVertex3f( b.xmax, b.ymax, b.zmin );
  glVertex3f( b.xmax, b.ymin, b.zmax );
  glVertex3f( b.xmax, b.ymax, b.zmax );
  // z-lines
  glVertex3f( b.xmin, b.ymin, b.zmin );
  glVertex3f( b.xmin, b.ymin, b.zmax );
  glVertex3f( b.xmin, b.ymax, b.zmin );
  glVertex3f( b.xmin, b.ymax, b.zmax );
  glVertex3f( b.xmax, b.ymin, b.zmin );
  glVertex3f( b.xmax, b.ymin, b.zmax );
  glVertex3f( b.xmax, b.ymax, b.zmin );
  glVertex3f( b.xmax, b.ymax, b.zmax );
  glEnd();
#endif

  // draw points
  glPointSize( 4.0f );

  glBegin(GL_POINTS);
  glVertex3f( b.xmin, b.ymin, b.zmin );
  glVertex3f( b.xmin, b.ymin, b.zmax );
  glVertex3f( b.xmin, b.ymax, b.zmin );
  glVertex3f( b.xmin, b.ymax, b.zmax );
  glVertex3f( b.xmax, b.ymin, b.zmin );
  glVertex3f( b.xmax, b.ymin, b.zmax );
  glVertex3f( b.xmax, b.ymax, b.zmin );
  glVertex3f( b.xmax, b.ymax, b.zmax );
  glEnd();

//  glPopMatrix();
#if 0
  glPopAttrib();
#endif
}

void
SurfDrawer::
draw_normal_nudge( uint i ) const
{
  // draws the ith vertex, nudged in the normal direction by _normal_nudge

  // get the vertex
  geom::Vertex4 v;
  surface()->vertex( v, i );

  // get the vertex normal
  geom::Normal3 const &n = surface()->vertex_normal(i);

  Real s = _normal_nudge * v[3];

  math::VectorX<Real,4U> x;
  // NOTE: is this right (v is homogeneous)
  x[0] = v[0] + s * n.x;
  x[1] = v[1] + s * n.y;
  x[2] = v[2] + s * n.z;
  x[3] = v[3];

  // draw the vertex
  ::opengl::glVertex( x );
}


void
SurfDrawer::
draw_vertex_color( uint i ) const
{
  if (_draw_color)
  {
    ::opengl::glColor( surface()->vertex_color(i) );
  }
}

void
SurfDrawer::
draw_vertex_normal( uint i ) const
{
  if (_draw_normal)
  {
    if ( _use_transform )
    {
      geom::Normal3 n;
      surface()->vertex_normal(n, i, _transform_inv, _projection_mode );
      ::opengl::glNormal( n );
    }
    else
    {
      geom::Normal3 const &n = surface()->vertex_normal(i);
      ::opengl::glNormal( n );
    }
  }
}

void
SurfDrawer::
draw_face_color( uint i ) const
{
  // draw color
  if (_draw_color)
  {
    ::opengl::glColor( surface()->face_color(i) );
  }
}

void
SurfDrawer::
draw_face_normal( uint i ) const
{
  if (_draw_normal)
  {
    if ( _use_transform )
    {
      geom::Normal3 n;
      surface()->face_normal(n, i, _transform_inv, _projection_mode );
      ::opengl::glNormal( n );
    }
    else
    {
      geom::Normal3 const &n = surface()->face_normal(i);
      ::opengl::glNormal( n );
    }
  }
}

void
SurfDrawer::
draw_vertex( uint k ) const
{
  // draw vertex (point in space)
  geom::Vertex4 v;
  if ( _use_transform )
  {
    surface()->vertex(v, k, _transform, _projection_mode );
  }
  else
  {
    surface()->vertex(v, k);
  }

  ::opengl::glVertex( v );
}

void
SurfDrawer::
draw_vertex( geom::Vertex3 const &v ) const
{
  // draw vertex (point in space)
  ::opengl::glVertex( v );
}

} // namespace surfacegl
} // namespace geom

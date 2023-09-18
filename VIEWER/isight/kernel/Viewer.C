/* GANG Software
 * VIEWER/isight/kernel/Viewer.C
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

#include "Viewer.H"

namespace isight {
namespace kernel {

Viewer::
Viewer()
    :
    Write(),
    _fade(true)
{
}

Viewer::
~Viewer()
{
}

void
Viewer::
insert_geomobject( geom::Surface const &g )
{
  geom::SurfaceGL *h = new geom::SurfaceGL;
  h->insert(g);
  insert_geomobject( h );
}

void
Viewer::
insert_geomobject( geom::SurfaceGL const &g )
{
  // copy the surface
  geom::SurfaceGL *h = new geom::SurfaceGL(g);
  insert_geomobject( h );
}

void
Viewer::
insert_geomobject( geom::SurfaceGL *g )
{
  context()->fade_enable( _fade && g->vertex_count() <= 2000 );

  // turn off the window's ability to draw
  enable_draw(false);

  // replace if (1) the "replace" button is on, and
  // (2) the previous object is still in the list of objects
  bool replace = viewer_ui()->replace_geomobject();
  uint n = GeomListSet::find( previous_geomobject() );
  if (n == geomlist_count()) { replace = false; }

  if ( ! replace )
  {
    viewer_ui()->show_window( ContextSet::find(), true);
  }

  // set the new geomobject's materials
  if ( viewer_ui()->geomobject_inherit_materials() )
  {
    if (replace)
    {
      // set g's materials to those of the previous object
      g->materials( *previous_geomobject() );
    }
    else
    {
      // set g's materials to those of the reference object
      g->materials( *reference_geomobject() );
    }
  }

  // cache the adress of the new object
  previous_geomobject() = g;

  /*
    insert the object
    g is inserted before the old surface is deleted because
    (1) looks smoother
    (2) g can inherit the space-position of the old surface
    (otherwise, g would be inserted in the default position)
  */

  // insert g into the geomlist
  GeomListSet::insert_geomobject0( g );

  // insert g into all windows
  ContextSet::insert_geomobject0(g);

  // update the select ui
  if (replace)
  {
    viewer_ui()->delete_geomobject_notify( geomlist_count() - 2 );
  }

  viewer_ui()->insert_geomobject_notify( g->name() );

  // delete the old object
  if (replace)
  {
    // delete object from ContextSet and GeomListSet
    delete_geomobject_( n );
  }

  // select the object
  DIE_IF( geomlist_count() == 0 );
  uint id = geomlist_count() - 1U;
  GeomListSet::select_geomobject0( id );

  // update the materials widgets
  geom_ui()->synchronize();
  // update the milieu widgets
  milieu_ui()->synchronize();

  // set the camera
  _position();

//  sync();

  // allow the window to draw
  enable_draw(true);


  // fade in the surface
  context()->fade();

  // turn off fade after first surface;
  if (_fade && g->vertex_count() <= 2000) {
    _fade = false;
  }

  //  sync();

  // refresh the window
  refresh_all();
}


void
Viewer::
_position()
{
  // (1) position the geomobject
  // (2) set the camera parameters

  // get the bounding box for the objects in the window
  geom::Box const &box = context()->box();
    
  // check that box is not huge
  float const BOUND = 1.0e5f;
  if ( math::abs(box.xmin) > BOUND || math::abs(box.xmax) > BOUND ||
       math::abs(box.ymin) > BOUND || math::abs(box.ymax) > BOUND ||
       math::abs(box.zmin) > BOUND || math::abs(box.zmax) > BOUND )
  {
    WARN("object is too big to center");
      return;
  }

  // compute the center for the objects
    
  // DIAMETER_SCALE scales the radius of the object into a z-shift
  double const DIAMETER_SCALE = 1.1;

  // center of object
  double diameter = 0.0;

  math::Vector3<double> corner_min( box.xmin, box.ymin, box.zmin );
  math::Vector3<double> corner_max( box.xmax, box.ymax, box.zmax );
  math::Vector3<double> center = 0.5*(corner_min+corner_max);
  // diameter of object
  diameter = (corner_max-corner_min).abs();

  // get the camera
  milieu::Camera cam = milieu_ui()->get_camera();

  // set the center and position of the window
  // NOTE: this is not changed when camera changes
  math::Vector3<double> position = -center;

  if (cam.mode == milieu::PERSPECTIVE)
  {
    position.z -= DIAMETER_SCALE*diameter;
  }
  // set the center
  context()->set_center( center, position );

  // set the perspective camera
  // heuristic setting znear and zfar
  milieu::Camera c1;
  c1.mode = milieu::PERSPECTIVE;
  c1.fov = cam.fov;
  c1.znear = 0.1*diameter;
  c1.zfar = 100.0*diameter;
    
  // set the orthographic camera
  // heuristic setting znear and zfar
  milieu::Camera c2;
  c2.mode = milieu::ORTHOGRAPHIC;
  c2.zoom = 0.5*diameter;
  c2.znear = -100.0*diameter;
  c2.zfar = 100.0*diameter;

  if (cam.mode == milieu::PERSPECTIVE)
  {
    milieu_ui()->set_camera(c2);
    milieu_ui()->set_camera(c1);
  }
  else if (cam.mode == milieu::ORTHOGRAPHIC)
  {
    milieu_ui()->set_camera(c1);
    milieu_ui()->set_camera(c2);
  }
  else { DIE(); }
}

void
Viewer::
show_geomobject_( uint id, bool state )
{
  DIE_IF( id == uint(-1) );

  // show the object
  context()->geomobject_showing( id, state );
  context()->refresh();
}

void
Viewer::
move_geomobject_( uint id, bool state )
{
  DIE_IF( id == uint(-1) );

  // move the object
  context()->geomobject_moving( id, state );
  context()->refresh();
}

void
Viewer::
select_geomobject_( uint id )
{
  DIE_IF( id == uint(-1) );

  // select the object
  GeomListSet::select_geomobject0(id);
  geom_ui()->material_synchronize();
  geom_ui()->meshclip_reset();
  geom_ui()->statistics_synchronize();
  // reset the custom color widgets
  geom_ui()->customcolor_reset();
}

void
Viewer::
delete_geomobject_(uint id)
{
  DIE_IF( id == uint(-1) );

  // delete the object
  _delete_geomobject(id);
  GeomListSet::delete_geomobject0(id);
}

void
Viewer::
select_window_( uint id )
{
  DIE_IF( id == uint(-1) );

  // select the window
  select_context0(id);

  // update the UI
  viewer_ui()->synchronize();
  milieu_ui()->synchronize();
}

void
Viewer::
delete_window_( uint id )
{
  DIE_IF( id == uint(-1) );

  // delete the window
  delete_context0(id);

#if 0
  windowsize_synchronize();
#endif

#if 0
  // update the UI
  ::isight::ui2::WinSelect::delete_window_nb(id);
#endif
}

void
Viewer::
new_window_()
{
  new_context0();

  {
    // this hack makes the window know its own size
    // it does NOT set the window size to 400 (???)
    base::ArrayX<uint,2U> x;
    x[0] = 400;
    x[1] = 400;
    viewer_ui()->windowsize_set(x);
  }

  enable_draw(false);

  // insert all geomobjects into the new window
  uint i;
  for ( i = 0; i < geomlist_count(); i++ )
  {
    context()->insert_geomobject( geomlist(i) );
  }
  context()->geomobject_reset_position();

  enable_draw(true);
  context()->refresh();
}

void
Viewer::
geometry_(
  motion::GeometryMode mode,
  motion::GeometryGroup group,
  uint dim )
{
  context()->geometry( mode, group, dim );

  if ( context()->standard_geometry() )
  {
    viewer_ui()->style(0U);
    milieu_ui()->reset_camera(milieu::PERSPECTIVE);
  }
  else
  {
    viewer_ui()->style(6U);
    milieu_ui()->reset_camera(milieu::ORTHOGRAPHIC);
  }
}

} // namespace kernel
} // namespace isight

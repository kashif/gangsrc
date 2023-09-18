/* GANG Software
 * VIEWER/isight/kernel/ContextSet.C
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

#include "base/String.H"
#include "ContextSet.H"

namespace isight {
namespace kernel {

ContextSet::
ContextSet()
    :
    GeomListSet(),
    ContextSetBase(),
    _context( (context::ContextBase *)0 ),
    _(),
    _context_id(0U)
{
}

ContextSet::
~ContextSet()
{
  // delete all contexts
  base::vector< context::ContextBase *>::iterator i;
  for ( i = _.begin(); i != _.end(); i++ )
  {
    delete *i;
  }
  _.clear();
}

void
ContextSet::
new_context0()
{
  new_context0( context_construct(this) );
}

void
ContextSet::
new_context0( context::ContextBase *w )
{
  // make the title
  {
    _window_title = viewer_name();
    _window_title += " | Window ";
    base::String s;
    s.to_string( _context_id++ + 1 );
    _window_title += s;
  }

  w->set_title(_window_title.c_str());

  // with default milieu
  _.push_back(w);

  _context = w;

  // select the window
  DIE_IF( context_count() == 0U);
  uint id = context_count() - 1U;
  select_context0( id );
}

void
ContextSet::
refresh_all()
{
  uint i;
  for ( i = 0; i < context_count(); i++ )
  {
    _[i]->refresh();
  }
}

void
ContextSet::
enable_draw(bool state)
{
  uint i;
  for ( i = 0; i < context_count(); i++ )
  {
    _[i]->enable_draw(state);
  }
}


void
ContextSet::
insert_geomobject0(
  geom::SurfaceGL *g )
{
  // insert g into all contexts
  uint i;
  for ( i = 0; i < context_count(); i++ )
  {
    context(i)->insert_geomobject( g );
  }
}


void
ContextSet::
_delete_geomobject( uint n )
{
  uint i;
  for ( i = 0; i < context_count(); i++ )
  {
    context(i)->delete_geomobject( n );
  }
  refresh_all();
}

void
ContextSet::
select_context0( uint n )
{
  _context = _[n];
  context()->make_current();
}

void
ContextSet::
delete_context0( uint n )
{
  if ( context_count() == 1 ) { return; }

  context(n)->show(false);
  delete _[n];
  _.erase( _.begin() + n );
  _context = _[0];
}

uint
ContextSet::
find( context::ContextBase const *w )
{
  // find w in _
  // returns context_count() if not found
  uint i;
  for ( i = 0; i < context_count(); i++ )
  {
    if (_[i] == w)
    {
      break;
    }
  }
  return i;
}

void
ContextSet::
focus_in_event(uint id )
{
#if 0
  select_context0(id);
#endif
}

int
ContextSet::
focus_in_event( context::ContextBase const *w )
{
  if ( w == context() ) { return 0; }

  uint n = find( w );
  if ( n != context_count() )
  {
    focus_in_event(n);
    return 1;
  }
  return 0;
}

} // namespace kernel
} // namespace isight

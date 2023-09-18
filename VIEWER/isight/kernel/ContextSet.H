/* GANG Software
 * VIEWER/isight/kernel/ContextSet.H
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

#ifndef isight_kernel_ContextSet_INCLUDED
#define isight_kernel_ContextSet_INCLUDED

#include "widget/ui/KeyBase.H"
#include "widget/ui/KeyHandler.H"
#include "geom/interface/SurfaceGL.H"
#include "isight/context/ContextBase.H"
#include "isight/context/ContextSetBase.H"
#include "GeomListSet.H"

namespace isight {
namespace kernel {

class ContextSet
  :
    public GeomListSet,
    public context::ContextSetBase
{

public:
  // constructor
  ContextSet();

  // destructor
  virtual ~ContextSet();

  // window title
  virtual base::String const &window_title()
    { return _window_title; }

  // test whether the id'th context is showing
  virtual bool window_showing_( uint id )
    { return static_cast<widget::ui::Window *>(context(id))->showing(); }

  // access to the current context
  virtual context::ContextBase *context()
    { DIE_IF(_context == (context::ContextBase *)0); return _context; }
  // access to the current context
  virtual context::ContextBase const *context() const
    { DIE_IF(_context == (context::ContextBase *)0); return _context; }

  virtual bool geomobject_showing_( uint id )
    { return context()->geomobject_showing(id); }
  virtual bool geomobject_moving_( uint id )
    { return context()->geomobject_moving(id); }
  virtual motion::Transform const &geomobject_position(uint id) const
    { return context()->geomobject_position(id); }
  virtual void geomobject_position(uint id, motion::Transform const &t)
    { context()->geomobject_position(id, t); }
//  virtual void enable_draw(bool state)
//    { context()->enable_draw(state); }

protected:

  // access to the nth context
  virtual context::ContextBase *context( uint n )
    { return _[n]; }
  // access to the nth context
  virtual context::ContextBase const *context( uint n ) const
    { return _[n]; }

  uint find()
    { uint n = find(_context); DIE_IF(n==context_count()); return n;}

  // set enable_draw to 'state' for all contexts in list
  void enable_draw( bool state );

  // refresh all contexts in list
  void refresh_all();

  // insert a surface into all contexts in list
  void insert_geomobject0( geom::SurfaceGL *g );

  // remove the n'th surface from all contexts
  void _delete_geomobject( uint n );

  // create a new context and put it in the list
  void new_context0();

  // select the id'th context
  void select_context0( uint id );

  // delete the id'th context
  void delete_context0( uint id );

  // connection functions -- collect virtuals with same name
  // from ViewerBase and ContextSetBase
  virtual ::isightui::ViewerUi *viewer_ui() = 0;
  virtual ::isightui::ViewerUi const *viewer_ui() const = 0;
  virtual void message( base::String const &text ) const = 0;

private:

  //
  void new_context0( context::ContextBase * );

  virtual char const *viewer_name() const = 0;

  virtual uint context_count() const { return _.size(); }

  // return a new context
  virtual context::ContextBase *context_construct( ContextSetBase *x ) = 0;

  // find w in the context list; return the index
  uint find( context::ContextBase const *w );

  virtual void focus_in_event( uint n );
  virtual int focus_in_event( context::ContextBase const *w );

  // the current context
  context::ContextBase *_context;

  // List of viewer contexts.
  base::vector< context::ContextBase *> _;

  // running id number for new contexts
  uint _context_id;

  // window title of last created context
  base::String _window_title;

  // disabled copy constructor
  ContextSet( ContextSet const & );
  // disabled assignment operator
  ContextSet &operator=( ContextSet const & );
};


} // namespace kernel
} // namespace isight

#endif // isight_kernel_ContextSet_INCLUDED

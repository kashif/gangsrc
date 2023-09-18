/* GANG Software
 * LAB/surflab/ui/Controls.C
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

#include "base/vector.H"
#include "base/Regex.H"
#include "lab/kernel/Evaluator.H"
#include "Controls.H"

namespace surflab {
namespace ui {

Controls::
Controls()
   :
    ::widget::ui::Dialog()
{
}

Controls::
~Controls()
{
}

void
Controls::
geometry_cb()
{
  _show();
}

void
Controls::
dimension_cb()
{
  _show();
}

void
Controls::
set( parser::KeyParser const &data )
{
  // geometry
  if ( data.get("geometry") == "parabolic" )
  {
    geometry_w()->set( 0U );
  }
  else if ( data.get("geometry") == "hyperbolic" )
  {
    geometry_w()->set( 1U );
  }
  else if ( data.get("geometry") == "elliptic" )
  {
    geometry_w()->set( 2U );
  }
  else
  { DIE(); }

  // dimension
  uint const DIM_OFFSET = 2;
  uint dim;
  lab::kernel::Evaluator::evaluator()->evaluate( dim, data.get("dim") );
  dimension_w()->set( dim - DIM_OFFSET );

  // variable names
  var1_w()->set( data.get("var1").c_str() );
  var2_w()->set( data.get("var2").c_str() );

  // functions
  uint i;
  for ( i = 0; i < COUNT; i++ )
  {
    base::String x;
    x.to_string(i+1);
    x = "x" + x;
    function_w(i)->set( data.get(x.c_str()).c_str() );
  }
  _show();
}

void
Controls::
get( parser::KeyParser &data ) const
{
  // geometry
  uint g = geometry_w()->get();
  if ( g == 0 )
  { data.set("geometry", "parabolic"); }
  else if ( g == 1 )
  { data.set("geometry", "hyperbolic"); }
  else if ( g == 2 )
  { data.set("geometry", "elliptic"); }
  else { DIE(); }

  // dimension
  uint const DIM_OFFSET = 2;
  base::String s;
  uint d = dimension_w()->get() + DIM_OFFSET;
  s.to_string( d );
  data.set("dim", s);

  // variable names
  data.set("var1", var1_w()->get() );
  data.set("var2", var2_w()->get() );

  uint i;
  for ( i = 0; i < COUNT; i++ )
  {
    base::String x;
    x.to_string(i+1);
    x = "x" + x;
    data.set(x.c_str(), function_w(i)->get());
  }
}

void
Controls::
_show()
{
  uint g = geometry_w()->get();
  uint d = 2U + dimension_w()->get();

  uint n = ( g == 0 ? d : d+1 );
  uint i;
  for ( i = 0; i < COUNT; i++ )
  {
    function_box_w(i)->show( i < n );
  }
}

bool
Controls::
command(
  base::String const &command,
  base::String const &argument,
  base::String &response )
{
  bool r = false;

  if ( command == "surflabGeometry" )
  {
    uint x;
    try {
      ::lab::kernel::Evaluator::evaluator()->evaluate( x, argument );
    }
    catch ( base::Exception ) {
      throw base::Exception("error in surflabGeometry");
    }
    geometry(x);
    r = true;
  }
  if ( command == "surflabDimension" )
  {
    uint x;
    try {
      ::lab::kernel::Evaluator::evaluator()->evaluate( x, argument );
    }
    catch ( base::Exception ) {
      throw base::Exception("error in surflabDimension");
    }
    dimension(x);
    r = true;
  }
  if ( command == "surflabVariables" )
  {
    base::vector<base::String> v;
    base::split( v, argument );
    if (v.size() != 2) {
      throw base::Exception("error in surflabVariables");
    }
    variable( v[0], v[1] );
    r = true;
  }
  if ( command == "surflabFunction" )
  {
    base::String n, f;
    split1( n, f, argument );
    uint x;
    try {
      ::lab::kernel::Evaluator::evaluator()->evaluate( x, n );
    }
    catch ( base::Exception ) {
      throw base::Exception("error in surflabFunction");
    }
    function( x, f );
    r = true;
  }

  return r;
}

} // namespace ui
} // namespace surflab

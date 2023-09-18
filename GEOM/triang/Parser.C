/* GANG Software
 * GEOM/triang/Parser.C
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
#include "base/Regex.H"
#include "math/Math.H"
#include "eval/Eval.H"
#include "Parser.H"

/*
Line: list of points joined by edges
Loop: list of points joined by edges, last point joined to first by edge
Point: list of points, unned

point: x1; x2; ...
line:  line specification: x1; x2; n
circle: circle specification: c; r; a1; a2; n
*/

namespace triang {

Parser::KeyValPair const Parser::_data_default[] =
{
  { "Loop",   "" },
  { "Line",   "" },
  { "Point",  "" },
  { "Hole",   "" },
  { "point",  "" },
  { "line",   "" },
  { "circle", "" }
};

Parser::
Parser()
    :
    parser::Parser(
      _data_default,
      sizeof(_data_default)/sizeof(KeyValPair)),
    _boundary_str( (base::vector<base::String> *)0 ),
    _vertex_v_v( (base::vector<Curve> *)0 ),
    _hole_v( (base::vector<std::pair<Real,Real> > *)0 ),
    _holes_ok(true),
    _curvecount(0),
    _curve(),
    _loop_start(0),
    _loop_first(true)
{
}

Parser::
~Parser()
{
}

void
Parser::
parse(
  base::vector<base::String> &boundary_str,
  base::vector<Curve> &vertex_v_v,
  base::vector<std::pair<Real,Real> > &hole_v,
  base::String const &s )
{
  _boundary_str = &boundary_str;
  _vertex_v_v = &vertex_v_v;
  _hole_v = &hole_v;
  _holes_ok = true;

  parser::Parser::parse(s);

  _boundary_str = (base::vector<base::String> *)0;
  _vertex_v_v = (base::vector<Curve> *)0;
  _hole_v = (base::vector<std::pair<Real,Real> > *)0;
}

void
Parser::
parse(
  base::vector<base::String> &boundary_str,
  base::vector<Curve> &vertex_v_v,
  base::String const &s )
{
  _boundary_str = &boundary_str;
  _vertex_v_v = &vertex_v_v;
  _holes_ok = false;

  parser::Parser::parse(s);

  _boundary_str = (base::vector<base::String> *)0;
  _vertex_v_v = (base::vector<Curve> *)0;
}

void
Parser::
initialize_cb()
{
  _curve.v.clear();
  _curve.joined = false;
  _curve.looped = false;
  _curvecount = 0;

  _boundary_str->clear();
  _vertex_v_v->clear();
  if (_holes_ok) { _hole_v->clear(); }
  _mode = NOTHING;
}

void
Parser::
finalize_cb()
{
  _insert_curve();
  _mode = NOTHING;

  if ( _vertex_v_v->empty() )
  { throw Exception( Exception::ERR_EMPTY, line_number() ); }
}

void
Parser::
_insert_curve()
{
  // insert previous curve
  if ( _curvecount != 0 && _mode != HOLE )
  {
    _vertex_v_v->push_back(_curve);
    _curve.v.clear();
    _curve.joined = false;
    _curve.looped = false;
  }
  _curvecount++;
}

void
Parser::
entry_cb(
  base::String const &key, base::String const &text )
{
  if ( key == "Loop" )
  {
    if ( ! text.empty() )
    { throw Exception( Exception::ERR_SYNTAX, line_number() ); }

    _insert_curve();
    _curve.joined = true;
    _curve.looped = true;

    // set mode
    _mode = LOOP;
  }
  else if ( key == "Line" )
  {
    if ( ! text.empty() )
    { throw Exception( Exception::ERR_SYNTAX, line_number() ); }

    _insert_curve();
    _curve.joined = true;
    _curve.looped = false;

    // set mode
    _mode = LINE;
  }
  else if ( key == "Point" )
  {
    if ( ! text.empty() )
    { throw Exception( Exception::ERR_SYNTAX, line_number() ); }

    _insert_curve();
    _curve.joined = false;
    _curve.looped = false;

    // set mode
    _mode = POINT;
  }
  else if ( _holes_ok && key == "Hole" )
  {
    DIE_IF( _hole_v == (base::vector<std::pair<Real,Real> > *)0 );

    if ( ! text.empty() )
    { throw Exception( Exception::ERR_SYNTAX, line_number() ); }

    _insert_curve();
    _curve.joined = false;
    _curve.looped = false;

    // set mode
    _mode = HOLE;
  }
  else if ( key == "point" )
  {
    // insert text
    insert_text(key, text);

    // parse the parameters describing the point list
    base::vector<std::pair<Real, Real> > v;
    _parse( v, text );
    insert_points(v);
  }
  else if ( key == "line" )
  {
    // insert text
    insert_text(key, text);

    // parse the parameters describing the line
    Line c;
    _parse( c, text );

    // insert the points

    base::vector<std::pair<Real,Real> > v;
    _generate( v, c );
    insert_points(v);
  }
  else if ( key == "circle" )
  {
    // insert text
    insert_text(key, text);

    // parse the parameters describing the circle or arc
    Circle c;
    _parse( c, text );

    base::vector<std::pair<Real,Real> > v;
    _generate( v, c );
    insert_points(v);
  }
  else
  { throw Exception( Exception::ERR_UNKNOWN_KEYWORD, line_number() ); }
}

void
Parser::
insert_points(
  base::vector<std::pair<Real,Real> > &v )
{
  uint k;

  if (_mode == HOLE)
  {
    DIE_IF( _hole_v == (base::vector<std::pair<Real,Real> > *)0 );
    for ( k = 0; k < v.size(); k++ )
    {
      _hole_v->push_back( v[k] );
    }
  }
  else
  {
    _curve.v.push_back(v);
  }
}

void
Parser::
_generate(
  base::vector<std::pair<Real,Real> > &v,
  Line const &c )
{
  v.clear();

  uint i;
  for ( i = 0; i < c.count; i++ )
  {
    std::pair<Real,Real> p;
    p.first = c.x1 + ( c.x2 - c.x1 ) * Real(i) / Real(c.count);
    p.second = c.y1 + ( c.y2 - c.y1 ) * Real(i) / Real(c.count);
    v.push_back(p);
  }
}

void
Parser::
_generate(
  base::vector<std::pair<Real,Real> > &v,
  Circle const &c )
{
  v.clear();

  uint i;
  for ( i = 0; i < c.count; i++ )
  {
    std::pair<Real,Real> p;
    Real a = c.angle0 + ( c.angle1 - c.angle0 ) * Real(i) / Real(c.count);
    p.first = c.centerx + c.radius * cos_(a);
    p.second = c.centery + c.radius * sin_(a);
    v.push_back(p);
  }
}

void
Parser::
_parse(
  base::vector<std::pair<Real,Real> > &P,
  base::String const &text )
{
  // parse point
  base::vector<base::String> v;
  base::split( v, text, ';' );
  if (v.size() == 0 )
  { throw Exception( Exception::ERR_MULTILINE, line_number() ); }
  
  uint i;
  for ( i = 0; i < v.size(); i ++ )
  {
    Complex z;
    try { eval::evaluate( z, v[i] ); }
    catch ( base::Exception const & )
    { throw Exception( Exception::ERR_POINT, line_number() ); }
    P.push_back( std::pair<Real, Real>( z.real(), z.imag() ) );
  }
}
  
void
Parser::
_parse(
  Line &c,
  base::String const &text )
{
  // parse line
  base::vector<base::String> v;
  base::split( v, text, ';' );
  if (v.size() != 3 )
  { throw Exception( Exception::ERR_LINE, line_number() ); }

  Complex z;
  try { eval::evaluate( z, v[0] ); }
  catch ( base::Exception const & )
  { throw Exception( Exception::ERR_LINE_X, line_number() ); }

  c.x1 = z.real();
  c.y1 = z.imag();

  try { eval::evaluate( z, v[1] ); }
  catch ( base::Exception const & )
  { throw Exception( Exception::ERR_LINE_Y, line_number() ); }
  
  c.x2 = z.real();
  c.y2 = z.imag();

  try { eval::evaluate( c.count, v[2] ); }
  catch ( base::Exception const & )
  { throw Exception( Exception::ERR_LINE_COUNT, line_number() ); }
}

void
Parser::
_parse(
  Circle &c,
  base::String const &text )
{
  // parse circle
  base::vector<base::String> v;
  base::split( v, text, ';' );
  if (v.size() != 5 )
  { throw Exception( Exception::ERR_CIRCLE, line_number() ); }

  Complex z;
  try { eval::evaluate( z, v[0] ); }
  catch ( base::Exception const & )
  { throw Exception( Exception::ERR_CIRCLE_CENTER, line_number() ); }
  c.centerx = z.real();
  c.centery = z.imag();
  
  try { eval::evaluate( c.radius, v[1] ); }
  catch ( base::Exception const & )
  { throw Exception( Exception::ERR_CIRCLE_RADIUS, line_number() ); }

  try { eval::evaluate( c.angle0, v[2] ); }
  catch ( base::Exception const & )
  { throw Exception( Exception::ERR_CIRCLE_ANGLE0, line_number() ); }
  
  try { eval::evaluate( c.angle1, v[3] ); }
  catch ( base::Exception const & )
  { throw Exception( Exception::ERR_CIRCLE_ANGLE1, line_number() ); }
  
  try { eval::evaluate( c.count, v[4] ); }
  catch ( base::Exception const & )
  { throw Exception( Exception::ERR_CIRCLE_COUNT, line_number() ); }
}

#if 0
void
Parser::
_parse(
  base::vector<std::pair<Real,Real> > &P,
  base::String const &text )
{
  // parse point
  base::vector<base::String> v;
  base::split( v, text, ';' );
  if (v.size() % 2 != 0 )
  { throw Exception( Exception::ERR_MULTILINE, line_number() ); }
  if (v.size() <= 1 )
  { throw Exception( Exception::ERR_MULTILINE, line_number() ); }
  
  uint i;
  for ( i = 0; i < v.size(); i += 2 )
  {
    std::pair<Real, Real> p;

    try { eval::evaluate( p.first, v[i] ); }
    catch ( base::Exception const & )
    { throw Exception( Exception::ERR_POINT_X, line_number() ); }

    try { eval::evaluate( p.second, v[i+1] ); }
    catch ( base::Exception const & )
    { throw Exception( Exception::ERR_POINT_Y, line_number() ); }

    P.push_back(p);
  }
}
  
void
Parser::
_parse(
  Line &c,
  base::String const &text )
{
  // parse line
  base::vector<base::String> v;
  base::split( v, text, ';' );
  if (v.size() != 5 )
  { throw Exception( Exception::ERR_LINE, line_number() ); }
  
  try { eval::evaluate( c.x1, v[0] ); }
  catch ( base::Exception const & )
  { throw Exception( Exception::ERR_LINE_X1, line_number() ); }
  
  try { eval::evaluate( c.y1, v[1] ); }
  catch ( base::Exception const & )
  { throw Exception( Exception::ERR_LINE_Y1, line_number() ); }
  
  try { eval::evaluate( c.x2, v[2] ); }
  catch ( base::Exception const & )
  { throw Exception( Exception::ERR_LINE_X2, line_number() ); }
  
  try { eval::evaluate( c.y2, v[3] ); }
  catch ( base::Exception const & )
  { throw Exception( Exception::ERR_LINE_Y2, line_number() ); }
  
  try { eval::evaluate( c.count, v[4] ); }
  catch ( base::Exception const & )
  { throw Exception( Exception::ERR_LINE_COUNT, line_number() ); }
}

void
Parser::
_parse(
  Circle &c,
  base::String const &text )
{
  // parse circle
  base::vector<base::String> v;
  base::split( v, text, ';' );
  if (v.size() != 6 )
  { throw Exception( Exception::ERR_CIRCLE, line_number() ); }

  try { eval::evaluate( c.centerx, v[0] ); }
  catch ( base::Exception const & )
  { throw Exception( Exception::ERR_CIRCLE_CENTERX, line_number() ); }
  
  try { eval::evaluate( c.centery, v[1] ); }
  catch ( base::Exception const & )
  { throw Exception( Exception::ERR_CIRCLE_CENTERY, line_number() ); }

  try { eval::evaluate( c.radius, v[2] ); }
  catch ( base::Exception const & )
  { throw Exception( Exception::ERR_CIRCLE_RADIUS, line_number() ); }

  try { eval::evaluate( c.angle0, v[3] ); }
  catch ( base::Exception const & )
  { throw Exception( Exception::ERR_CIRCLE_ANGLE0, line_number() ); }
  
  try { eval::evaluate( c.angle1, v[4] ); }
  catch ( base::Exception const & )
  { throw Exception( Exception::ERR_CIRCLE_ANGLE1, line_number() ); }
  
  try { eval::evaluate( c.count, v[5] ); }
  catch ( base::Exception const & )
  { throw Exception( Exception::ERR_CIRCLE_COUNT, line_number() ); }
}
#endif

void
Parser::
insert_text(
  base::String const &key,
  base::String const &text )
{
  // insert text into _boundary_str
  base::String s = key;
  s += " ";
  s += text;
  _boundary_str->push_back(s);
}

Real
Parser::
cos_(Real x)
{
  Real y = x/(2.0*math::pi);
  if ( y == 0.0 ) { return 1.0; }
  if ( y == 0.25 ) { return 0.0; }
  if ( y == 0.5 ) { return -1.0; }
  if ( y == 0.75 ) { return 0.0; }
  return math::cos( x );
}

Real
Parser::
sin_(Real x)
{
  Real y = x/(2.0*math::pi);
  if ( y == 0.0 ) { return 0.0; }
  if ( y == 0.25 ) { return 1.0; }
  if ( y == 0.5 ) { return 0.0; }
  if ( y == 0.75 ) { return -1.0; }
  return math::sin( x );
}

} // namespace triang

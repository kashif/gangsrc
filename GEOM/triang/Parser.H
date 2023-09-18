/* GANG Software
 * GEOM/triang/Parser.H
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

#ifndef triang_Parser_INCLUDED
#define triang_Parser_INCLUDED

#include "base/vector.H"
#include "parser/Parser.H"
#include "Exception.H"
#include "Common.H"

namespace triang {

/*
  Parse a boundary of a triangulated domain
*/
class Parser
  :
    protected parser::Parser
{

public:
  Parser();
  virtual ~Parser();

  void parse(
    base::vector<base::String> &boundary_str,
    base::vector<Curve> &vertex_v_v,
    base::vector<std::pair<Real,Real> > &hole_v,
    base::String const &s );

  void parse(
    base::vector<base::String> &boundary_str,
    base::vector<Curve> &vertex_v_v,
    base::String const &s );

protected:

private:

  enum Mode { NOTHING, LOOP, LINE, POINT, HOLE };
  Mode _mode;

  struct Line
  {
    Real x1;
    Real y1;
    Real x2;
    Real y2;
    uint count;
  };
  struct Circle
  {
    Real centerx;
    Real centery;
    Real radius;
    Real angle0;
    Real angle1;
    uint count;
  };

  virtual void initialize_cb();
  virtual void finalize_cb();
  virtual void entry_cb( base::String const &key, base::String const &val );

  
  void _generate( base::vector<std::pair<Real,Real> > &v, Line const &c );
  void _generate( base::vector<std::pair<Real,Real> > &v, Circle const &c );

  void _parse(
    base::vector<std::pair<Real, Real> > &v,
    base::String const &text );
  void _parse(
    Line &c,
    base::String const &text );
  void _parse(
    Circle &c,
    base::String const &text );

  void _insert_curve();

  void insert_points(
    base::vector<std::pair<Real,Real> > &v );

  void
  insert_text(
    base::String const &keyword,
    base::String const &text );
  
  static Real cos_(Real x);
  static Real sin_(Real x);

  static KeyValPair const _data_default[];

  base::vector<base::String> *_boundary_str;
  base::vector<Curve> *_vertex_v_v;
  base::vector<std::pair<Real,Real> > *_hole_v;

  bool _holes_ok;
  uint _curvecount;
  Curve _curve;

  uint _loop_start;
  bool _loop_first;

  // disabled copy constructor
  Parser( Parser const & );

  // disabled assignment operator
  Parser &operator=( Parser const & );

};

} // namespace triang

#endif // triang_Parser_INCLUDED

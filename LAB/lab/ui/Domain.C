/* GANG Software
 * LAB/lab/ui/Domain.C
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

#include "base/Regex.H"
#include "triang/Triangulator.H"
#include "lab/kernel/Evaluator.H"
#include "Domain.H"

namespace lab {
namespace ui {

char const *const
Exception::
_message0[] = {
  "",
  "Error in triangulated domain",
  "Error in triangulated domain: max area",
  "Error in triangulated domain: min angle",
  "Error in triangulated domain: smooth",
  "Error in triangulated domain: refine",
  "Error in triangulated domain: max area2",
  "Error in triangulated domain: curvature exp",
  "Error in triangulated domain: curvature cut",
  "Error in rectangular domain",
  "Error in polar domain",
  "Error in polar domain (exponental)",
  "Error in curve domain",
  "Error in domain file",
  "Error in domain"
};

Domain::
Domain()
{
}

Domain::
~Domain()
{
}

void
Domain::
reset()
{
  domain_choice_w()->set( RECTANGULAR );

  // set the widgets
  boundary_list_w()->set("");
  max_area_w()->set( 0.0f );
  min_angle_w()->set( 0.0f );
  smooth_w()->set( 0.0f );

  rect_a0_w()->set( "" );
  rect_count0_w()->set( "" );
  rect_a1_w()->set( "" );
  rect_count1_w()->set( "" );

  polar_center_w()->set( "" );
  polar_radius0_w()->set( "" );
  polar_radius1_w()->set( "" );
  polar_n_radius_w()->set( "" );
  polar_angle0_w()->set( "" );
  polar_angle1_w()->set( "" );
  polar_n_angle_w()->set( "" );
  polar_mode_w()->set( 0 );

#if 0
  line_x0_w()->set("");
  line_x1_w()->set("");
  line_count_w()->set("");

  circle_center_w()->set("");
  circle_radius_w()->set("");
  circle_angle0_w()->set("");
  circle_angle1_w()->set("");
  circle_count_w()->set("");
#endif

  domainfile_w()->set( "" );

  refine_w()->set(0);
}

void
Domain::
set( parser::KeyParser const &data )
{
  base::String const &domain = data.get("domain");
  set(domain);
}

void
Domain::
set( base::String const &domain )
{
  if ( base::match( "^[ \n\r\t]*rectangular[ \n\r\t]", domain ) )
  {
    _read_rectangular(domain);
  }
  else if ( base::match(
              "^[ \n\r\t]*polar[ \n\r\t]", domain ) )
  {
    _read_polar(domain);
  }
  else if ( base::match(
              "^[ \n\r\t]*polar_exp[ \n\r\t]", domain ) )
  {
    _read_polar_exp(domain);
  }
  else if ( base::match(
              "^[ \n\r\t]*curve[ \n\r\t]", domain ) )
  {
    _read_curve(domain);
  }
  else if ( base::match(
              "^[ \n\r\t]*triangulated[ \n\r\t]", domain ) )
  {
    _read_triangulated(domain);
  }
  else if ( base::match( "^[ \n\r\t]*file", domain ) )
  {
    _read_file(domain);
  }
  else
  {
    throw Exception( Exception::ERR_DOMAIN );
  }
}

void
Domain::
get( parser::KeyParser &data ) const
{
  // domain type
  int type = domain_choice_w()->get();

  if ( type == RECTANGULAR )
  {
    // rectangular
    base::String s;
    s = "rectangular ";
    s += rect_base_w()->get();
    s += "; ";
    s += rect_a0_w()->get();
    s += "; ";
    s += rect_count0_w()->get();
    s += "; ";
    s += rect_a1_w()->get();
    s += "; ";
    s += rect_count1_w()->get();
    data.set("domain", s);
  }
  else if ( type == POLAR )
  {
    // polar or polar exp
    int p = polar_mode_w()->get();
    base::String s;
    if ( p == 0 )
    {
      s = "polar ";
    }
    else if ( p == 1 )
    {
      s = "polar_exp ";
    }
    s += polar_center_w()->get();
    s += "; ";
    s += polar_radius0_w()->get();
    s += "; ";
    s += polar_radius1_w()->get();
    s += "; ";
    s += polar_n_radius_w()->get();
    s += "; ";
    s += polar_angle0_w()->get();
    s += "; ";
    s += polar_angle1_w()->get();
    s += "; ";
    s += polar_n_angle_w()->get();
    data.set("domain", s);
  }
#if 0
  else if ( type == LINE )
  {
    base::String s;
    s = "line ";
    s += line_x0_w()->get();
    s += "; ";
    s += line_x1_w()->get();
    s += "; ";
    s += line_count_w()->get();
    data.set("domain", s);
  }
  else if ( type == CIRCLE )
  {
    base::String s;
    s = "circle ";
    s += circle_center_w()->get();
    s += "; ";
    s += circle_radius_w()->get();
    s += "; ";
    s += circle_angle0_w()->get();
    s += "; ";
    s += circle_angle1_w()->get();
    s += "; ";
    s += circle_count_w()->get();
    data.set("domain", s);
  }
#endif
  else if ( type == CURVE )
  {
    // triangulated domain specifications
    base::String s;
    s = "curve\n";
    s += curve_list_w()->get();
    data.set("domain", s);
  }
  else if ( type == TRIANGULATED )
  {
    // triangulated domain specifications
    base::String s;
    s = "triangulated\nboundary\n";

    s += boundary_list_w()->get();
    s += "\n";

    base::String t;
    t.to_string( max_area_w()->get() );

    s += "max_area ";
    s += t;
    s += "\n";

    t.to_string( min_angle_w()->get() );
    s += "min_angle ";
    s += t;
    s += "\n";

    t.to_string( smooth_w()->get());
    s += "smooth ";
    s += t;
    s += "\n";

    // refine
    t.to_string( refine_w()->get() );
    s += "refine ";
    s += t;
    s += "\n";

    // max_area2
    t.to_string( max_area2_w()->get() );
    s += "max_area2 ";
    s += t;
    s += "\n";

    // curvature_exp
    t.to_string( curvature_exp_w()->get() );
    s += "curvature_exp ";
    s += t;
    s += "\n";

    // curvature_cut
    t.to_string( curvature_cut_w()->get() );
    s += "curvature_cut ";
    s += t;
    s += "\n";

    data.set("domain", s);
  }
  else if ( type == FILE )
  {
    base::String s;
    s = "file ";
    s += domainfile_w()->get();
    data.set("domain", s);
  }
  else
  {
    DIE();
  }

}

bool
Domain::
command(
  base::String const &command,
  base::String const &argument,
  base::String &response )
{
  bool r = false;

  if (command == "domain") {
    set(argument);
    r = true;
  }
  if (command == "domainRectangular") {
    _read_rectangular( "rectangular " + argument);
    r = true;
  }
  if (command == "domainPolar") {
    _read_polar( "polar " + argument);
    r = true;
  }
  if (command == "domainPolarExp") {
    _read_polar_exp( "polar_exp " + argument);
    r = true;
  }
  if (command == "domainCurve") {
    _read_curve( "curve " + argument);
    r = true;
  }
  if (command == "domainTriangulated") {
    _read_triangulated( "triangulated " + argument);
    r = true;
  }
  if (command == "domainFile") {
    _read_file( "file " + argument);
    r = true;
  }

  return r;
}

void
Domain::
_read_rectangular( base::String const &domain )
{
  base::vector<base::String> v;
  if ( ! base::match(
         "^[ \n\r\t]*rectangular[ \n\r\t]+(.*)$", domain, v ) )
  { throw Exception( Exception::ERR_DOMAIN_RECT ); }

  domain_choice_w()->set( RECTANGULAR );

  base::String s = v[1];
  base::split( v, s, ';' );
  if ( v.size() != 5 )
  { throw Exception( Exception::ERR_DOMAIN_RECT ); }
  rect_base_w()->set( v[0].c_str() );
  rect_a0_w()->set( v[1].c_str() );
  rect_count0_w()->set( v[2].c_str() );
  rect_a1_w()->set( v[3].c_str() );
  rect_count1_w()->set( v[4].c_str() );
}

void
Domain::
_read_polar( base::String const &domain )
{
  base::vector<base::String> v;
  if ( ! base::match(
         "^[ \n\r\t]*polar[ \n\r\t]+(.*)$", domain, v ) )
  { throw Exception( Exception::ERR_DOMAIN_POLAR ); }

  domain_choice_w()->set( POLAR );

  base::String s = v[1];
  base::split( v, s, ';' );
  if ( v.size() != 7 )
  { throw Exception( Exception::ERR_DOMAIN_POLAR ); }
  polar_center_w()->set( v[0].c_str() );
  polar_radius0_w()->set( v[1].c_str() );
  polar_radius1_w()->set( v[2].c_str() );
  polar_n_radius_w()->set( v[3].c_str() );
  polar_angle0_w()->set( v[4].c_str() );
  polar_angle1_w()->set( v[5].c_str() );
  polar_n_angle_w()->set( v[6].c_str() );
  polar_mode_w()->set( 0 );
}

void
Domain::
_read_polar_exp( base::String const &domain )
{
  base::vector<base::String> v;
  if ( ! base::match(
         "^[ \n\r\t]*polar_exp[ \n\r\t]+(.*)$", domain, v ) )
  { throw Exception( Exception::ERR_DOMAIN_POLAR_EXP ); }

  domain_choice_w()->set( POLAR );

  base::String s = v[1];
  base::split( v, s, ';' );
  if ( v.size() != 7 )
  { throw Exception( Exception::ERR_DOMAIN_POLAR_EXP ); }
  polar_center_w()->set( v[0].c_str() );
  polar_radius0_w()->set( v[1].c_str() );
  polar_radius1_w()->set( v[2].c_str() );
  polar_n_radius_w()->set( v[3].c_str() );
  polar_angle0_w()->set( v[4].c_str() );
  polar_angle1_w()->set( v[5].c_str() );
  polar_n_angle_w()->set( v[6].c_str() );
  polar_mode_w()->set( 1 );
}

void
Domain::
_read_curve( base::String const &domain )
{
  // triangulated domain
  base::vector<base::String> v;
  if ( ! base::match(
         "^[ \n\r\t]*curve[ \n\r\t]+(.*)$", domain, v ) )
  { throw Exception( Exception::ERR_DOMAIN_CURVE ); }

  // set notebook page
  domain_choice_w()->set( CURVE );

  // set the widgets

  // boundary
  curve_list_w()->set( v[1].c_str() );
}

void
Domain::
_read_triangulated( base::String const &domain )
{
  // triangulated domain
  base::vector<base::String> v;
  if ( ! base::match(
         "^[ \n\r\t]*triangulated[ \n\r\t]+(.*)$", domain, v ) )
  { throw Exception( Exception::ERR_TRIANGULATED ); }

  // set notebook page
  domain_choice_w()->set( TRIANGULATED );

  triang::Data parser;
  parser.parse( v[1] );

  // set the widgets

  // boundary
  boundary_list_w()->set( parser.get("boundary").c_str() );

  // max_area
  {
    float x;
    try {
      kernel::Evaluator::evaluator()->evaluate( x, parser.get("max_area") );
    }
    catch ( base::Exception const & )
    { throw Exception( Exception::ERR_MAX_AREA ); }
    max_area_w()->set( x );
  }
  
  // min_angle
  {
    float x;
    try {
      kernel::Evaluator::evaluator()->evaluate( x, parser.get("min_angle") );
    }
    catch ( base::Exception const & )
    { throw Exception( Exception::ERR_MIN_ANGLE ); }
    min_angle_w()->set( x );
  }

  // smooth
  {
    uint x;
    try {
      kernel::Evaluator::evaluator()->evaluate( x, parser.get("smooth") );
    }
    catch ( base::Exception const & )
    { throw Exception( Exception::ERR_SMOOTH ); }
    smooth_w()->set( (int)x );
  }
  
  // refine
  {
    uint x;
    try {
      kernel::Evaluator::evaluator()->evaluate( x, parser.get("refine") );
    }
    catch ( base::Exception const & )
    { throw Exception( Exception::ERR_REFINE ); }
    refine_w()->set( x );
  }
  
  // max_area2
  {
    float x;
    try {
      kernel::Evaluator::evaluator()->
        evaluate( x, parser.get("max_area2") );
    }
    catch ( base::Exception const & )
    { throw Exception( Exception::ERR_MAX_AREA2 ); }
    max_area2_w()->set( x );
  }
  
  // curvature_exp
  {
    float x;
    try {
      kernel::Evaluator::evaluator()->
        evaluate( x, parser.get("curvature_exp") );
    }
    catch ( base::Exception const & )
    { throw Exception( Exception::ERR_CURVATURE_EXP ); }
    curvature_exp_w()->set( x );
  }
  
  // curvature_cut
  {
    float x;
    try {
      kernel::Evaluator::evaluator()->
        evaluate( x, parser.get("curvature_cut") );
    }
    catch ( base::Exception const & )
    { throw Exception( Exception::ERR_CURVATURE_CUT ); }
    curvature_cut_w()->set( x );
  }
}

void
Domain::
_read_file( base::String const &domain )
{
  base::vector<base::String> v;
  if ( ! base::match(
         "^[ \n\r\t]*file[ \n\r\t]+(.*)$", domain, v ) )
  { throw Exception( Exception::ERR_DOMAIN_FILE ); }

  domain_choice_w()->set( FILE );

  domainfile_w()->set( v[1].c_str() );
}

} // namespace ui
} // namespace lab

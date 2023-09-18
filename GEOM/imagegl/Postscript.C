/* GANG Software
 * GEOM/imagegl/Postscript.C
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

/*
  Acknowledgements:
  This code is modified from GLP, an OpenGL to Postscript class library by
  Michael Sweet. http://www.easysw.com/~mike/imagegl/ .
*/

//#include <limits.h>
//#include <stdlib.h>
//#include <math.h>
#include "base/System.H"
#include "math/Math.H"
#include "Postscript.H"

namespace imagegl {

PostScript::
PostScript()
  throw()
    :
    PostscriptBase()
{
  _ostream = (::io::Ostream *)0;
  _page_count = 0;
  _status = 0;
  _EPS = false;
}

PostScript::
~PostScript()
  throw()
{
}

void
PostScript::
write( ::io::Ostream &o, bool EPS )
{
  DIE_IF( _status == 1 );
  _ostream = &o;
  _EPS = EPS;

  begin();
  draw();
  end();
  // NOTE: why draw twice?
  draw();
}

void
PostScript::
begin_()
  throw ( ::io::WriteException )
{
  if ( _status == 0 )
  {
    // Output the PostScript file header and prolog
    write_postscript_header(*_ostream);
    _status = 1;
  }
}

void
PostScript::
end_()
  throw ( ::io::WriteException )
{
  DIE_IF(_ostream == 0);
  DIE_IF(!_ostream);

  GLfloat rgba[4]; // RGBA background
  GLint viewport[4];

  // NOTE: memory leak?
  _status = 0;

  glGetIntegerv(GL_VIEWPORT, viewport);

  _page_count++;

  ::io::Ostream &o = *_ostream;

  o << "%%Page: " << _page_count << "\n";
  o << "%%PageBoundingBox: 0 0 " << viewport[2] << " "
            << viewport[3] << "\n";

  o << "gsave\n";

  if ( _fit_to_page )
  {
    o << "% Fit to page\n"
      "newpath clippath pathbbox\n"
      "/URy exch def\n"
      "/URx exch def\n"
      "/LLy exch def\n"
      "/LLx exch def\n"
      "/Width  URx LLx sub 0.005 sub def\n"
      "/Height URy LLy sub 0.005 sub def\n"
      "LLx LLy translate\n";
    
    o << "/XZoom Width " << viewport[2] << " div def\n";
    o << "/YZoom Height " << viewport[3] << " div def\n";

    o << "Width YZoom mul Height XZoom mul gt {\n"
      "       90 rotate\n"
      "       0 Width neg translate\n"
      "       Width Height /Width exch def /Height exch def\n";

    o  << "       /XZoom Width " << viewport[2] << " div def\n";
    o  << "       /YZoom Height " << viewport[3] << " div def\n";
    o   << "} if\n"
      "XZoom YZoom gt {\n"
      "       /YSize Height def\n";

    o   << "       /XSize " << viewport[2] << " YZoom mul def\n"
      "       /Scale YZoom def\n"
      "} {\n";

    o << "       /XSize Width def\n"
      "       /YSize " << viewport[3]
      << " XZoom mul def\n"
      "       /Scale XZoom def\n"
      "} ifelse\n";

      o << "Width  XSize sub 2 div\n"
      "Height YSize sub 2 div translate\n"
      "Scale Scale scale\n"
      "\n";
  }

  if ( _draw_background )
  {
    if ( _colormap == 0 )
    {
      glGetFloatv(GL_COLOR_CLEAR_VALUE, rgba);
    }
    else
    {
      int i;
      glGetIntegerv(GL_INDEX_CLEAR_VALUE, &i);
      rgba[0] = _colormap[i][0];
      rgba[1] = _colormap[i][1];
      rgba[2] = _colormap[i][2];
    }

    o << "% Draw background\n";
    o << rgba[0] << " " << rgba[1] << " " << rgba[2] << " C\n";
    o << "newpath\n";
    o << "       0 0 moveto\n";
    o << "       " << viewport[2] << " 0 lineto\n";
    o << "       " << viewport[2] << " " << viewport[3] << " lineto\n";
    o << "       0 " << viewport[3] << " lineto\n";
    o << "closepath fill\n";
    o << "\n";
  }

  // cycle through the elements
  std::list<Element *>::iterator i;
  for ( i = _element_list.begin(); i != _element_list.end(); i++ )
  {
    base::vector<CVertex> &v = (*i)->vertex;
    size_t n = v.size();
#if 0
    std::cerr << "polygon\n";
    int i0;
    for(i0=0;i0<n;i0++)
    {
      std::cerr << "  vertex: zmin="
                << (*i)->zmin << " zmax="
                << (*i)->zmax << " "
                << v[i0].xyz[0] << " "
                << v[i0].xyz[1] << " "
                << v[i0].xyz[2] << std::endl;
    }
#endif
    if ( n == 1 )
    {
      o << v[0].xyz[0] << " ";
            o << v[0].xyz[1] << " ";
            o << v[0].rgba[0] << " ";
            o << v[0].rgba[1] << " ";
            o << v[0].rgba[2] << " P\n";
    }
    else if ( n == 2 )
    {
      if ((*i)->shade)
      {
        o << v[1].xyz[0] << " ";
        o << v[1].xyz[1] << " ";
        o << v[1].rgba[0] << " ";
        o << v[1].rgba[1] << " ";
        o << v[1].rgba[2] << " ";
        o << v[0].xyz[0] << " ";
        o << v[0].xyz[1] << " ";
        o << v[0].rgba[0] << " ";
        o << v[0].rgba[1] << " ";
        o << v[0].rgba[2];
        o << " SL\n";
      }
      else
      {
        o << v[1].xyz[0] << " ";
        o << v[1].xyz[1] << " ";
        o << v[0].xyz[0] << " ";
        o << v[0].xyz[1] << " ";
        o << v[0].rgba[0] << " ";
        o << v[0].rgba[1] << " ";
        o << v[0].rgba[2];
        o << " L\n";
      }
    }
    else if ( n == 3 )
    {
      if ((*i)->shade)
      {
        o << v[2].xyz[0] << " ";
        o << v[2].xyz[1] << " ";
        o << v[2].rgba[0] << " ";
        o << v[2].rgba[1] << " ";
      o << v[2].rgba[2] << " ";
      o << v[1].xyz[0] << " ";
      o << v[1].xyz[1] << " ";
      o << v[1].rgba[0] << " ";
      o << v[1].rgba[1] << " ";
      o << v[1].rgba[2] << " ";
      o << v[0].xyz[0] << " ";
      o << v[0].xyz[1] << " ";
      o << v[0].rgba[0] << " ";
      o << v[0].rgba[1] << " ";
      o << v[0].rgba[2];
      o << " ST\n";
      }
      else
      {
      o << v[2].xyz[0] << " ";
      o << v[2].xyz[1] << " ";
      o << v[1].xyz[0] << " ";
      o << v[1].xyz[1] << " ";
      o << v[0].xyz[0] << " ";
      o << v[0].xyz[1] << " ";
      o << v[0].rgba[0] << " ";
      o << v[0].rgba[1] << " ";
      o << v[0].rgba[2];
      o << " T\n";
      }
    }
    else
    {
      // polygon with more than 3 vertices not implemented
      DIE();
    }
  }

  o << "grestore\n";

  if (!_EPS) {
    o << "showpage\n";
  }
  o << "%%end\n";
  if (!_EPS) {
    o << "%%Pages: " << _page_count << "\n";
  }
  o<< "%%EOF\n";

  o.flush();
  _ostream = 0;
}


void
PostScript::
write_postscript_header( ::io::Ostream &o )
  throw ( ::io::WriteException )
{
  if (_EPS) {
    o << "%!PS-Adobe-3.0 EPSF-3.0\n";
  }
  else {
    o << "%!PS-Adobe-3.0\n";
  }

  o << "%%LanguageLevel: 1\n";

#if 0
  o << "%%Title:\n"
    << "%%Creator:\n"
    << "%%CreationDate:\n"
    << "%%For:\n";
#endif

  if (!_EPS) {
    o << "%%Orientation: Portrait\n"
      << "%%Pages: (atend)\n";
  }

#if 0
  o << "%%BoundingBox:";
#endif

  o << "%%%Magnification: 1.000\n"
    << "%%EndComments\n"
    << "%%BeginProlog\n";

  if ( _greyscale )
  {
    o << "% Greyscale color command - r g b C\n"
      << "/C { 0.0820 mul exch 0.6094 mul add exch 0.3086 mul add neg 1.0 add setgray } bind def\n";
  }
  else
  {
    o << "% RGB color command - r g b C\n"
      << "/C { setrgbcolor } bind def\n";
  }
  o << "\n"

       "% Point primitive - x y r g b P\n"
       "/P { C newpath 0.5 0.0 360.0 arc closepath fill } bind def\n"
       "\n"

       "% Flat-shaded line - x2 y2 x1 y1 r g b L\n"
       "/L { C moveto lineto stroke } bind def\n"
       "\n"

       "% Smooth-shaded line - x2 y2 r2 g2 b2 x1 y1 r1 g1 b1 SL\n"
       "/SL {\n"
       " /b1 exch def\n"
       " /g1 exch def\n"
       " /r1 exch def\n"
       " /y1 exch def\n"
       " /x1 exch def\n"
       " /b2 exch def\n"
       " /g2 exch def\n"
       " /r2 exch def\n"
       " /y2 exch def\n"
       " /x2 exch def\n"
       "\n"
       " b2 b1 sub abs 0.01 gt\n"
       " g2 g1 sub abs 0.005 gt\n"
       " r2 r1 sub abs 0.008 gt\n"
       "     or or {\n"
       "         /bm b1 b2 add 0.5 mul def\n"
       "         /gm g1 g2 add 0.5 mul def\n"
       "         /rm r1 r2 add 0.5 mul def\n"
       "         /ym y1 y2 add 0.5 mul def\n"
       "         /xm x1 x2 add 0.5 mul def\n"
       "\n"
       "         x1 y1 r1 g1 b1 xm ym rm gm bm SL\n"
       "         xm ym rm gm bm x2 y2 r2 g2 b2 SL\n"
       " } {\n"
       "         x1 y1 x2 y2 r1 g1 b1 L\n"
       " } ifelse\n"
       "} bind def\n"
       "\n"

       "% Flat-shaded triangle - x3 y3 x2 y2 x1 y1 r g b T\n"
       "/T { C newpath moveto lineto lineto closepath fill } bind def\n"
       "\n"

       "% Smooth-shaded triangle - x3 y3 r3 g3 b3 x2 y2 r2 g2 b2 x1 y1 r1 g1 b1 ST\n"
       "/ST {\n"
       " /b1 exch def\n"
       " /g1 exch def\n"
       " /r1 exch def\n"
       " /y1 exch def\n"
       " /x1 exch def\n"
       " /b2 exch def\n"
       " /g2 exch def\n"
       " /r2 exch def\n"
       " /y2 exch def\n"
       " /x2 exch def\n"
       " /b3 exch def\n"
       " /g3 exch def\n"
       " /r3 exch def\n"
       " /y3 exch def\n"
       " /x3 exch def\n"
       "\n"
       " b2 b1 sub abs 0.05 gt\n"
       " g2 g1 sub abs 0.017 gt\n"
       " r2 r1 sub abs 0.032 gt\n"
       " b3 b1 sub abs 0.05 gt\n"
       " g3 g1 sub abs 0.017 gt\n"
       " r3 r1 sub abs 0.032 gt\n"
       " b2 b3 sub abs 0.05 gt\n"
       " g2 g3 sub abs 0.017 gt\n"
       " r2 r3 sub abs 0.032 gt\n"
       " or or or or or or or or {\n"
       "         /b12 b1 b2 add 0.5 mul def\n"
       "         /g12 g1 g2 add 0.5 mul def\n"
       "         /r12 r1 r2 add 0.5 mul def\n"
       "         /y12 y1 y2 add 0.5 mul def\n"
       "         /x12 x1 x2 add 0.5 mul def\n"
       "\n"
       "         /b13 b1 b3 add 0.5 mul def\n"
       "         /g13 g1 g3 add 0.5 mul def\n"
       "         /r13 r1 r3 add 0.5 mul def\n"
       "         /y13 y1 y3 add 0.5 mul def\n"
       "         /x13 x1 x3 add 0.5 mul def\n"
       "\n"
       "         /b32 b3 b2 add 0.5 mul def\n"
       "         /g32 g3 g2 add 0.5 mul def\n"
       "         /r32 r3 r2 add 0.5 mul def\n"
       "         /y32 y3 y2 add 0.5 mul def\n"
       "         /x32 x3 x2 add 0.5 mul def\n"
       "\n"
       "         x1 y1 r1 g1 b1 x12 y12 r12 g12 b12 x13 y13 r13 g13 b13\n"
       "         x2 y2 r2 g2 b2 x12 y12 r12 g12 b12 x32 y32 r32 g32 b32\n"
       "         x3 y3 r3 g3 b3 x32 y32 r32 g32 b32 x13 y13 r13 g13 b13\n"
       "         x32 y32 r32 g32 b32 x12 y12 r12 g12 b12 x13 y13 r13 g13 b13\n"
       "         ST ST ST ST\n"
       " } {\n"
       "         x1 y1 x2 y2 x3 y3 r1 g1 b1 T\n"
       " } ifelse\n"
       "} bind def\n"
    "\n";

   o << "%%EndProlog\n";
}

} // namespace imagegl

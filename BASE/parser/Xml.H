/* GANG Software
 * BASE/parser/Xml.H
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

#ifndef parser_Xml_INCLUDED
#define parser_Xml_INCLUDED

#include <expat.h>
#include <zlib.h>
#ifdef __linux__
#include <iostream>
#else
#include <istream>
#endif
#include <list>
#include "base/System.H"
#include "base/String.H"
#include "io/Istream.H"

namespace parser {

class Xml
{

public:
  Xml();
  virtual ~Xml();

  void parse( io::Istream &stream );

  uint line_number() const
    { DIE_IF(_parser == (XML_Parser)0);
    return XML_GetCurrentLineNumber( _parser ); }
  char const *message() const
    { DIE_IF(_parser == (XML_Parser)0);
    return XML_ErrorString(XML_GetErrorCode( _parser )); }

protected:
  typedef std::pair<char const *, char const *> Attribute;
  typedef std::list<Attribute> AttributeList;
  static char const *find( AttributeList const &, char const * );

  virtual void initialize() {}
  virtual void finalize() {}
  virtual void start_tag_cb(
    char const *tag, AttributeList const &attributes ) = 0;
  virtual void end_tag_cb( char const *tag ) = 0;
  base::String const &text() const
    { return _text; }

private:
  XML_Parser _parser;

  static void start_tag_cb_( void *p, char const *tag,
                             char const **attributes );

  static void end_tag_cb_(
    void *p, char const *tag )
    {
      static_cast<Xml *>(p)->end_tag_cb( tag );
      static_cast<Xml *>(p)->_text.erase();
    }

  static void text_cb_(
    void *p, char const *text, int len )
    {
      static_cast<Xml *>(p)->text_cb( text, len );
    }

  void text_cb( char const *text, int len );

  base::String _text;

  static uint const BUFFER_SIZE = 8192;
  char *_buffer;

  

  Xml( Xml const & );
  Xml &operator=( Xml const & );
};

} // namespace parser

#endif // parser_Xml_INCLUDED

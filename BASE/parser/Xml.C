/* GANG Software
 * BASE/parser/Xml.C
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

#include <strstream>
#include "base/System.H"
#include "Xml.H"

namespace parser {

Xml::
Xml()
{
  _parser = (XML_Parser *)0;
  _buffer = new char [BUFFER_SIZE];
}

Xml::
~Xml()
{
  delete [] _buffer;
}

void
Xml::
parse( io::Istream &stream )
{
  _parser = XML_ParserCreate(0);

  if (! _parser) {
    throw base::Exception( "XML parser error: out of memory" );
  }

  XML_SetUserData( _parser, this );
  XML_SetElementHandler( _parser, start_tag_cb_, end_tag_cb_ );
  XML_SetCharacterDataHandler( _parser, text_cb_ );

  initialize();

  bool done = false;

  while ( ! done ) {

    uint len = stream.read(_buffer, BUFFER_SIZE );

//    int done = ( ! stream );
    done = ( len == 0 );

    int r = XML_Parse(_parser, _buffer, len, done);

    if ( r == 0 )
    {
      // parse error
      throw base::Exception( message() );
    }
  }

  finalize();
}

void
Xml::
text_cb( char const *text, int len )
{
  _text.append(text, len);
}

void
Xml::
start_tag_cb_(
  void *p, char const *tag,
  char const **attributes )
{
  Xml *me = static_cast<Xml *>(p);

  me->_text.erase();

  AttributeList attribute_list;

  char const **a = attributes;
  while (*a != (char *)0)
  {
    attribute_list.push_back( Attribute(a[0], a[1]) );
    a += 2;
  }

  me->start_tag_cb( tag, attribute_list );
}

char const *
Xml::
find(AttributeList const &a, char const *key)
{
  AttributeList::const_iterator i;
  for (i=a.begin(); i!= a.end(); i++)
  {
    if ( ! strcmp( (*i).first, key ) )
    {
      return (*i).second;
    }
  }
  return (char *)0;
}

} // namespace parser

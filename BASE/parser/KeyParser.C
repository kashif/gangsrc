/* GANG Software
 * BASE/parser/KeyParser.C
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

#include "base/Exception.H"
#include "KeyParser.H"

namespace parser {

KeyParser::
KeyParser(
  base::String const &version_string,
  KeyValPair const *keyval,
  uint keyval_len )
    :
    Parser( version_string, keyval, keyval_len)
{
  reset();
}

KeyParser::
KeyParser(
  KeyValPair const *keyval,
  uint keyval_len )
    :
    Parser( keyval, keyval_len)
{
  reset();
}

KeyParser::
KeyParser( KeyParser const &a )
    :
    Parser(a)
{
}

KeyParser::
~KeyParser()
{
}

KeyParser &
KeyParser::
operator=( KeyParser const &a )
{
  if ( this == &a ) { return *this; }
  Parser::operator=(a);
  return *this;
}

void
KeyParser::
reset()
{
  Parser::reset();

  _.clear();

  uint i;
  for ( i = 0; i < _default_len; i++ )
  {
    char const *key = _default[i].key;
    char const *val = _default[i].val;
    _[key] = val;
  }
}

base::String const &
KeyParser::
get( base::String const &key ) const
{
  Hash::const_iterator i = _.find(key);
  if ( i == _.end() )
  {
    DIE();
    throw base::Exception( "KeyParser reference" );
  }
  return (*i).second;
}

void
KeyParser::
set( base::String const &key, base::String const &val )
{
  Hash::const_iterator i = _.find(key);
  if ( i == _.end() )
  {
    DIE();
    throw base::Exception( "KeyParser reference" );
  }
  _[key] = val;
}

void
KeyParser::
write( io::Ostream &o ) const
{
  o << _version_string << "\n\n";
  uint i;
  for ( i = 0; i < _default_len; i++ )
  {
    char const *key = _default[i].key;
    base::String val = get(key);
    o << key << " " << val << "\n";
  }
}

void
KeyParser::entry_cb(
  base::String const &key, base::String const &val )
{
  _[key] = val;
}

} // namespace parser

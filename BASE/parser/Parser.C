/* GANG Software
 * BASE/parser/Parser.C
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
#include "base/Regex.H"
#include "io/IstreamStream.H"
#include "Parser.H"

namespace parser {

Parser::
Parser(
  base::String const &version_string,
  KeyValPair const *keyval,
  uint keyval_len )
    :
    _version_string(version_string),
    _default(keyval),
    _default_len(keyval_len)
{
  reset();
}

Parser::
Parser(
  KeyValPair const *keyval,
  uint keyval_len )
    :
    _version_string(),
    _default(keyval),
    _default_len(keyval_len)
{
  reset();
}

Parser::
Parser( Parser const & )
{
  DIE();
}

Parser::
~Parser()
{
}

Parser &
Parser::
operator=( Parser const & )
{
  DIE();
  return *this;
}

void
Parser::
reset()
{
  _line_number = 0;
}

void
Parser::
parse( io::Istream &stream )
{
  reset();

  initialize_cb();

  base::String text;

  uint n;
  if ( ! _version_string.empty() )
  {
    n = getline( stream, text );
    if ( text != _version_string + "\n" )
    { throw base::Exception( "missing version string" ); }
    if ( n == 0 ) { finalize_cb(); return; }
  }
  base::String current_key;
  base::String current_text;

  for (;;)
  {
    // read a line
    n = getline( stream, text );
    if (n == 0) { break; }

#if 0
    std::cerr << "text=[" << text << "]\n";
#endif

    base::vector<base::String> v;

    // strip comments
    if ( base::match("^([^#]*)#.*\n$", text, v ) )
    {
      text = v[1];
      text += "\n";
    }
    else if ( base::match("^([^#*]*)#.*$", text, v ) )
    {
      text = v[1];
    }

    // try to match to a keyword
    if ( base::match("^[ \t\n]*([^ \t\n]+)[ \t\n]+(.*)$", text, v ) )
    {
      if ( find( v[1].c_str() ) )
      {
        // match found

        // callback for previous key-text pair
        _keyval_cb( current_key, current_text );

        // new key-text pair
        current_key = v[1];
        current_text = v[2];
      }
      else
      {
        // match not found
        if ( ! current_key.empty() )
        {
          current_text += text;
        }
      }
    }
  }
  // callback for previous key-text pair
  _keyval_cb( current_key, current_text );

  finalize_cb();
}

void
Parser::
_keyval_cb(
  base::String const &key,
  base::String const &val )
{
  if ( ! key.empty() )
  {
    base::String s(val);
    s.strip();

#if 0
    std::cerr << "keyval=[" << key << "][" << s << "]\n";
#endif
    entry_cb( key, s );
  }
}

bool
Parser::
find( char const *key ) const
{
  uint i;
  for ( i = 0; i < _default_len; i++ )
  {
    if ( ! strcmp( key, _default[i].key ) ) { return true; }
  }
  return false;
}

void
Parser::
parse( base::String const &s )
{
  std::strstream S;
  S << s;
  S.flush();
  io::IstreamStream in(S);
  parse(in);
}

void
Parser::
parse( std::istream &i )
{
  io::IstreamStream in(i);
  parse(in);
}

void
Parser::
parse_file( char const *filename )
{
  io::IstreamStream in(filename);
  parse(in);
}

uint
Parser::
getline( ::io::Istream &stream, base::String &s )
{
  s.erase();

  char c;
  for (;;)
  {
    uint n = stream.read(&c, 1);
    if ( n == 0 ) { return s.length(); }
    s += c;
    if (c == '\n') { _line_number++; break; }
  }
  return s.length();
}

} // namespace parser

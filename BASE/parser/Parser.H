/* GANG Software
 * BASE/parser/Parser.H
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

#ifndef parser_Parser_INCLUDED
#define parser_Parser_INCLUDED

#include "io/Istream.H"

namespace parser {

class Parser
{

public:

  typedef struct { char const *key, *val; } KeyValPair;

  // constructor
  Parser(
    base::String const &version_string,
    KeyValPair const *keyval,
    uint keyval_len );

  // constructor
  Parser(
    KeyValPair const *keyval,
    uint keyval_len );

  // copy constructor
  Parser( Parser const & );

  // destructor
  virtual ~Parser();

  // assignment operator
  Parser &operator=( Parser const & );

  virtual void parse( io::Istream &in );
  virtual void parse( base::String const & );
  virtual void parse( std::istream &in );
  virtual void parse_file( char const *filename );

  virtual uint line_number()
    { return _line_number; }

  virtual void reset();

protected:


  uint _line_number;
  base::String _version_string;
  KeyValPair const *_default;
  uint _default_len;

private:

  uint getline( ::io::Istream &stream, base::String &s );

  virtual void initialize_cb() {}
  virtual void finalize_cb() {}
  virtual void entry_cb(
    base::String const &key, base::String const &val ) = 0;

  void _keyval_cb(
    base::String const &key, base::String const &val );

  bool find( char const *key ) const;
};

} // namespace parser

#endif // parser_Parser_INCLUDED

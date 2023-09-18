/* GANG Software
 * BASE/parser/KeyParser.H
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

#ifndef parser_KeyParser_INCLUDED
#define parser_KeyParser_INCLUDED

#include <iostream>
#include <map>
#include "base/System.H"
#include "base/String.H"
#include "io/Istream.H"
#include "io/Ostream.H"
#include "Parser.H"

namespace parser {

class KeyParser
  :
    public Parser
{

public:

  // constructor
  KeyParser(
    base::String const &version_string,
    KeyValPair const *keyval,
    uint keyval_len );

  // constructor
  KeyParser(
    KeyValPair const *keyval,
    uint keyval_len );

  // copy constructor
  KeyParser( KeyParser const & );

  // destructor
  virtual ~KeyParser();

  // assignment operator
  KeyParser &operator=( KeyParser const & );

  virtual void write( io::Ostream &out ) const;

  virtual base::String const &get( base::String const &s ) const;
  virtual void set( base::String const &key, base::String const &val );

  virtual void reset();

protected:

  virtual void initialize_cb() {reset();}
  virtual void finalize_cb() {}
  virtual void entry_cb(
    base::String const &key, base::String const &val );

  typedef std::map<
    base::String, base::String, std::less<base::String> > Hash;
  Hash _;

private:
};

} // namespace parser

#endif // parser_KeyParser_INCLUDED

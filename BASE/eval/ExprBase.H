/* GANG Software
 * BASE/eval/ExprBase.H
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

#ifndef eval_ExprBase_INCLUDED
#define eval_ExprBase_INCLUDED

#include <iostream>
#include <iomanip>
#include "base/vector.H"
#include "base/String.H"
#include "base/Stl.H"

#if !defined(DISABLE_EVAL_NAMESPACE)
namespace eval {
#endif

//
template <class NUMBER>
struct expr_variable
{
#if 0

  // void constructor
  expr_variable() : _name(), _value() {};

  // copy constructor
  expr_variable( expr_variable<NUMBER> const &x ) :
      _name( x._name ), _value( x._value ) {};

  // destructor
  ~expr_variable() {};

  // assignment operator
  expr_variable<NUMBER> &operator=( expr_variable<NUMBER> const &x )
    { if ( this != &x )
    { _name = x._name; _value = x._value; }
    return *this; };
#endif
  //
  base::String _name;
  //
  NUMBER _value;
};


//
template <class NUMBER>
class expr_base
{

public:

  // constructor
  expr_base();

  // copy constructor
  expr_base( expr_base<NUMBER> const & );

  // destructor
  ~expr_base();

  // assignmet operator
  expr_base &operator=( expr_base<NUMBER> const & );

  //
  void create_variable( char const *, size_t len );
  //
  inline void create_variable( char const * );
  //
  inline void create_variable( base::String const & );

  //
  void set_variable( char const *, size_t len, NUMBER );
  //
  inline void set_variable( char const *, NUMBER );
  //
  inline void set_variable( base::String const &, NUMBER );

  //
  int get_variable( NUMBER &, char const *, size_t len ) const;
  //
  inline int get_variable( NUMBER &, char const * ) const;

  //
  int get_variable_key( char const *, size_t len ) const;
  //
  int get_variable( NUMBER &, uint key ) const;

  //
  void remove_variable( char const * );
  //
  void remove_variables();
  //
  void clear();
  //
  void dump( std::ostream & ) const;

  //
  enum types { NOTHING, OBJECT, IDENTIFIER, FUNCTION };

  struct element
  {
#if 0
    // void constructor
    element() :
        _type(NOTHING), _id(0), _fn_argcount(0), _id_base::String(), _x(0) {};
    // copy constructor
    element( element const &a ) :
        _type(a._type), _id(a._id), _fn_argcount(a._fn_argcount),
        _id_base::String(a._id_base::String), _x(a._x) {};
    // destructor
    ~element() {};
    // assignment operator
    element &operator=( element const &a )
      { if ( this != &a ) {
        _type = a._type; _id = a._id; _fn_argcount = a._fn_argcount;
        _id_base::String = a._id_base::String; _x = a._x; }
        return *this; };
#endif
    types  _type;
    uint _id;
    uint _fn_argcount;
    base::String _id_string;
    NUMBER _x;
  };

  //
  base::vector<element> _data;
  //
  base::vector<expr_variable<NUMBER> > _variable;

protected:

  //
  inline int find_variable( char const * ) const;
  //
  int find_variable( char const *, size_t ) const;

private:

};

template <class NUMBER>
expr_base<NUMBER>::
expr_base()
    :
    _data(),
    _variable()
{
}

template <class NUMBER>
expr_base<NUMBER>::
expr_base( expr_base<NUMBER> const &a )
    :
    _data( a._data ),
    _variable( a._variable )
{
}

template <class NUMBER>
expr_base<NUMBER>::
~expr_base()
{
}

template <class NUMBER>
expr_base<NUMBER> &
expr_base<NUMBER>::
operator=( expr_base<NUMBER> const &a )
{
  if ( this != &a )
  {
    _data = a._data;
    _variable = a._variable;
  }
  return *this;
}

template <class NUMBER>
void
expr_base<NUMBER>::
create_variable( char const *s, size_t len )
{
  if (find_variable(s, len) == -1 )
  {
    expr_variable<NUMBER> v;
    v._name.assign( s, len );
    _variable.push_back( v );
  }
}

template <class NUMBER>
void
expr_base<NUMBER>::
create_variable( char const *s )
{
  if (find_variable(s, strlen(s)) == -1 )
  {
    expr_variable<NUMBER> v;
    v._name.assign( s );
    _variable.push_back( v );
  }
}

template <class NUMBER>
void
expr_base<NUMBER>::
create_variable( base::String const &s )
{
  if (find_variable(s.data(), s.length()) == -1 )
  {
    expr_variable<NUMBER> v;
    v._name.assign( s );
    _variable.push_back( v );
  }
}

template <class NUMBER>
void
expr_base<NUMBER>::
set_variable( char const *s, size_t len, NUMBER x )
{
  int n = find_variable(s, len);
  if ( n == -1 )
  {
    expr_variable<NUMBER> v;
    v._name.assign( s, len );
    _variable.push_back(v);
    n = (int)_variable.size() - 1;
  }
  _variable[n]._value = x;
}

template <class NUMBER>
void
expr_base<NUMBER>::
set_variable( char const *s, NUMBER x )
{
  int n = find_variable(s, strlen(s));
  if ( n == -1 )
  {
    expr_variable<NUMBER> v;
    v._name.assign( s );
    _variable.push_back(v);
    n = (int)_variable.size() - 1;
  }
  _variable[n]._value = x;
}

template <class NUMBER>
void
expr_base<NUMBER>::
set_variable( base::String const &s, NUMBER x )
{
  int n = find_variable(s.data(), s.length());
  if ( n == -1 )
  {
    expr_variable<NUMBER> v;
    v._name.assign( s );
    _variable.push_back(v);
    n = (int)_variable.size() - 1;
  }
  _variable[n]._value = x;
}

template <class NUMBER>
int
expr_base<NUMBER>::
get_variable( NUMBER &x, char const *c, size_t len ) const
{
  int n = find_variable(c, len);
  if ( n >= 0 )
  {
    x = _variable[n]._value;
  }
  else
  {
    x = NUMBER();
  }
  return n;
}

template <class NUMBER>
int
expr_base<NUMBER>::
get_variable( NUMBER &x, char const *c ) const
{
  return get_variable( x, c, strlen(c) );
}

template <class NUMBER>
int
expr_base<NUMBER>::
get_variable( NUMBER &x, uint key ) const
{
  int r;
  if ( key < _variable.size() )
  {
    x = _variable[key]._value;
    r = 0;
  }
  else
  {
    x = NUMBER();
    r = 1;
  }
  return r;
}

template <class NUMBER>
int
expr_base<NUMBER>::
get_variable_key( char const *c, size_t len ) const
{
  return find_variable(c, len);
}



template <class NUMBER>
void
expr_base<NUMBER>::
remove_variable( char const * )
{
}

template <class NUMBER>
void
expr_base<NUMBER>::
remove_variables()
{
}

template <class NUMBER>
void
expr_base<NUMBER>::
clear()
{
  _data.clear();
}

template <class NUMBER>
void
expr_base<NUMBER>::
dump( std::ostream &o ) const
{
  USE(o);
  DIE();
  uint i;
  for ( i = 0; i < _data.size(); i++ )
  {
  }
}


template <class NUMBER>
int
expr_base<NUMBER>::
find_variable( char const *name, size_t len ) const
{
  uint i;
  size_t size = _variable.size();
  for ( i = 0; i < size; i++ )
  {
    if ( _variable[i]._name.length() == len &&
         memcmp( _variable[i]._name.data(), name, len)==0 )
    { break; }
  }
  return ( i == size ? -1 : int(i) );
}


template <class NUMBER>
int
expr_base<NUMBER>::
find_variable( char const *name ) const
{
  return find_variable( name, strlen(name) );
}


#if !defined(DISABLE_EVAL_NAMESPACE)
} // namespace eval
#endif

#endif // eval_ExprBase_INCLUDED

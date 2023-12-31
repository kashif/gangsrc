/* GANG Software
 * BASE/vrml/Lexer.H
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
// Generated by parse++


#ifndef vrml_Lexer_INCLUDED
#define vrml_Lexer_INCLUDED

/*
  Acknowledgements:
  This code is modified from a VRML 2.0 parser by Gavin Bell and Daniel Woods
  Copyright (C) 1996 Silicon Graphics, Inc.
*/

#include <stdio.h>
#include "base/vector.H"
#include "base/String.H"
#include "io/Istream.H"

namespace vrml {

class Lexer
{

public:
  Lexer();
  virtual ~Lexer();
  typedef char unsigned UCHAR;
  typedef char CHAR;

private:

  protected:
  typedef double Real;

  struct LvalStruct {
  enum {
    NOTHING,
    STRING, BOOL, INT,
    FLOAT, FLOATP2, FLOATP3, FLOATP4,
    INTV, STRINGV,
    FLOATV, FLOATV2, FLOATV3, FLOATV4
  } type;
  base::String _string;
  bool _bool;
  int _int;
  Real _float;
  Real _floatp[4];
  base::vector<Real> _floatv;
  base::vector<int> _intv;
  base::vector<base::String> _stringv;
  };

  int _lineno;
  int expectToken;
  int expectCoordIndex;
  bool parsing_mf;
  base::String tmpString;
  virtual void error( char const message[] ) = 0;
  io::Istream *_stream;

private:
  static char const *format;
  static char const *format2;
  char *skip_ws( char * );

protected:

  void _initialize();
  void _deinitialize();

  enum ParserKeys { VP_IDENTIFIER=257, VP_DEF=258, VP_USE=259, VP_PROTO=260, VP_EXTERNPROTO=261, VP_TO=262, VP_IS=263, VP_ROUTE=264, VP_SFN_0=265, VP_EVENTIN=266, VP_EVENTOUT=267, VP_FIELD=268, VP_EXPOSEDFIELD=269, VP_SF_BOOL=270, VP_SF_COLOR=271, VP_SF_FLOAT=272, VP_SF_INT32=273, VP_SF_ROTATION=274, VP_SF_TIME=275, VP_SF_IMAGE=276, VP_SF_STRING=277, VP_SF_VEC2F=278, VP_SF_VEC3F=279, VP_MF_COLOR=280, VP_MF_FLOAT=281, VP_MF_INT32=282, VP_MF_ROTATION=283, VP_MF_STRING=284, VP_MF_VEC2F=285, VP_MF_VEC3F=286, VP_SF_NODE=287, VP_MF_NODE=288 };
  enum StartConditions { NODE = 1, SFB, SFC, SFF, SFIMG, SFI, SFR, SFS, SFT, SFV2, SFV3, MFC, MFF, MFI, MFR, MFS, MFV2, MFV3, IN_SFS, IN_MFS, IN_SFIMG };
  int lex( LvalStruct &lval );

  void fatal_error( const CHAR msg[] );

private:

  struct BufferState
  {
    BufferState();
    CHAR *ch_buf;
    CHAR *buf_pos;
    size_t buf_size;
    size_t n_chars;
    int is_our_buffer;
    int is_interactive;
    int at_bol;
    int fill_buffer;
    int buffer_status;
  };

  BufferState *current_buffer;
  int leng;
  UCHAR hold_char;
  size_t n_chars;
  CHAR *c_buf_p;
  int init;
  int start;
  int did_buffer_switch_on_eof;
  int last_accepting_state;
  CHAR *last_accepting_cpos;
  int start_stack_ptr;
  int start_stack_depth;
  int *start_stack;

  void *flex_alloc( size_t );
  void *flex_realloc( void *, size_t );
  void flex_free( void * );
  int get_previous_state();
  int try_NUL_trans( int current_state );
  int get_next_buffer();
  void push_state( int new_state );
  void pop_state();
  int top_state();
  void switch_to_buffer( BufferState *new_buffer );
  void load_buffer_state();
  BufferState *create_buffer( int size );
  void delete_buffer( BufferState * b );
  void init_buffer( BufferState * b );
  void flush_buffer( BufferState * b );
  void restart();
  void unput( int c, CHAR *bp );
  void input( CHAR *buf, size_t &result, size_t max_size);
  int input();
  int wrap();
  void less( int, CHAR *bp, CHAR *cp );
  void DO_BEFORE_ACTION( CHAR *bp, CHAR *cp );
  BufferState *scan_buffer( CHAR *base, size_t size );
  BufferState *scan_string( const CHAR *str );
  BufferState *scan_bytes( const CHAR *bytes, int len );

  static const short int accept[];
  static const int ec[];
  static const int meta[];
  static const short int base[];
  static const short int def[];
  static const short int nxt[];
  static const short int chk[];


  static int const BUFFER_NEW;
  static int const BUFFER_NORMAL;
  static int const BUFFER_EOF_PENDING;
  static int const END_OF_BUFFER_CHAR;
  static int const BUF_SIZE;
  static int const EOB_ACT_CONTINUE_SCAN;
  static int const EOB_ACT_END_OF_FILE;
  static int const EOB_ACT_LAST_MATCH;
  static int const READ_BUF_SIZE;
  static int const NUM_RULES;
  static int const END_OF_BUFFER;
  static int const MORE_ADJ;
  static int const INITIAL;
  static int const START_STACK_INCR;
  static int const EXIT_FAILURE_;
  static int const CONSTANT1;
  static int const CONSTANT2;

  inline int BEGIN(int x) { return start = 1 + 2 * x; }
  inline int START() { return (start - 1)/2; }
  inline int STATE_EOF(int state) { return END_OF_BUFFER + state + 1; }
  inline int AT_BOL() { return current_buffer->at_bol; }

  CHAR *text;

  // disabled
  Lexer( Lexer const & );
  Lexer &operator=( Lexer const & );
};

} // namespace vrml

#endif // vrml_Lexer_INCLUDED


/* GANG Software
 * GEOM/geom/io/MathLexer.C
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

#include <stdlib.h>
#include "MathLexer.H"

#if defined(__sgi) && !defined(__GNUG__)
#pragma set woff 1110
#endif

namespace geom {
namespace io {

// constructor
MathLexer::
MathLexer()
{
  _initialize();

  _lineno = 1;
}

// destructor
MathLexer::~MathLexer() {
  _deinitialize();
}

void MathLexer::
input( CHAR *buf, size_t &result, size_t max_size )
{
  result = _stream->read( buf, max_size );
}

MathLexer::MathLexer( MathLexer const & )
{
  abort();
}

MathLexer &MathLexer::operator=( const MathLexer & )
{
  abort();
  return *this;
}

int const MathLexer::BUFFER_NEW = 0;
int const MathLexer::BUFFER_NORMAL = 1;
int const MathLexer::BUFFER_EOF_PENDING = 2;
int const MathLexer::END_OF_BUFFER_CHAR = 0;
int const MathLexer::BUF_SIZE = 16384;
int const MathLexer::EOB_ACT_CONTINUE_SCAN = 0;
int const MathLexer::EOB_ACT_END_OF_FILE = 1;
int const MathLexer::EOB_ACT_LAST_MATCH = 2;
int const MathLexer::READ_BUF_SIZE = 8192;
int const MathLexer::NUM_RULES = 14;
int const MathLexer::END_OF_BUFFER = 15;
int const MathLexer::MORE_ADJ = 0;
int const MathLexer::INITIAL = 0;
int const MathLexer::START_STACK_INCR = 25;
int const MathLexer::EXIT_FAILURE_ = 1;
int const MathLexer::CONSTANT1 = 71;
int const MathLexer::CONSTANT2 = 134;

void MathLexer::_initialize()
{
  current_buffer = (BufferState *)0;
  leng = 0;
  hold_char = 0;
  n_chars = 0;
  c_buf_p = (CHAR *)0;
  init = 1;
  start = 0;
  did_buffer_switch_on_eof = 0;
  last_accepting_state = 0;
  last_accepting_cpos = (CHAR *)0;
  start_stack_ptr = 0;
  start_stack_depth = 0;
  start_stack = (int *)0;
}

void MathLexer::_deinitialize()
{
  if (current_buffer != (BufferState *)0)
  {
    delete_buffer(current_buffer);
  }
}

MathLexer::BufferState::BufferState()
{
  ch_buf = (CHAR *)0;
  buf_pos = (CHAR *)0;
  buf_size = 0;
  n_chars = 0;
  is_our_buffer = 0;
  is_interactive = 0;
  at_bol = 0;
  fill_buffer = 0;
  buffer_status = 0;
}


const short int MathLexer::accept[71] =
{   0,
    0,    0,   15,   14,   12,   12,   14,   14,   11,   14,
    6,   14,   14,   14,    9,   10,   14,    7,    8,   12,
   12,   12,   12,    0,    0,    6,    6,    0,    6,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    1,    0,    0,    6,    0,    0,    0,   13,    0,
    0,    0,    0,    0,    0,    0,    5,    0,    2,    0,
    0,    0,    3,    0,    0,    0,    0,    0,    4,    0
};


const int MathLexer::ec[256] =
{   0,
    1,    1,    1,    1,    1,    1,    1,    1,    2,    3,
    2,    2,    2,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    2,    1,    1,    4,    1,    1,    1,    1,    5,
    6,    7,    8,    9,    8,   10,    1,   11,   12,   13,
   14,   13,   13,   13,   13,   13,   13,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,   15,    1,    1,
   16,    1,    1,    1,    1,    1,    1,    1,    1,   17,
    1,    1,   18,    1,    1,    1,    1,    1,    1,    1,
   19,    1,   20,   21,    1,    1,   22,    1,   23,    1,
   24,   25,   26,   27,   28,    1,    1,   29,    1,   30,
   31,   32,    1,   33,   34,    1,   35,    1,    1,    1,
   36,    1,   37,    1,   38,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1
};


const int MathLexer::meta[39] =
{   0,
    1,    1,    2,    1,    1,    1,    3,    1,    1,    3,
    3,    3,    3,    3,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1
};


const short int MathLexer::base[74] =
{   0,
    0,    0,  133,  134,   37,  128,  124,   32,  134,   36,
   44,   97,   98,   93,  134,  134,  105,  134,  134,   51,
  122,  121,  120,  116,   45,   53,   54,   50,   61,  100,
   92,   87,   92,  111,   63,  106,   68,   84,   79,   89,
   91,  105,   90,   72,   76,   83,   83,   86,  134,   79,
   75,   82,   81,   73,   78,   67,  134,   84,   85,   65,
   82,   73,  134,   60,   51,   49,   41,   18,  134,  134,
   90,   37,   93
};


const short int MathLexer::def[74] =
{   0,
   70,    1,   70,   70,   70,   71,   70,   70,   70,   70,
   72,   70,   70,   70,   70,   70,   70,   70,   70,   70,
   71,   71,   71,   73,   70,   72,   70,   70,   70,   70,
   70,   70,   70,   73,   73,   70,   70,   70,   70,   70,
   70,   73,   70,   70,   70,   70,   70,   70,   70,   70,
   70,   70,   70,   70,   70,   70,   70,   70,   70,   70,
   70,   70,   70,   70,   70,   70,   70,   70,   70,    0,
   70,   70,   70
};


const short int MathLexer::nxt[173] =
{   0,
    4,    5,    4,    6,    7,    4,    4,    8,    9,   10,
   11,   11,   11,   11,    4,   12,   13,   14,   15,   16,
    4,    4,    4,    4,    4,    4,   17,    4,    4,    4,
    4,    4,    4,    4,    4,    4,   18,   19,   20,   26,
   21,   25,   26,   26,   26,   26,   27,   27,   27,   27,
   28,   69,   20,   29,   21,   27,   27,   27,   27,   28,
   28,   36,   29,   68,   27,   27,   27,   27,   42,   35,
   37,   27,   27,   27,   27,   44,   67,   66,   45,   45,
   45,   45,   45,   45,   45,   45,   45,   45,   45,   45,
   22,   65,   22,   34,   64,   34,   63,   62,   61,   60,
   59,   58,   57,   56,   55,   54,   53,   52,   51,   50,
   37,   35,   49,   48,   47,   46,   43,   35,   41,   40,
   39,   38,   35,   23,   23,   23,   33,   32,   31,   30,
   24,   23,   70,    3,   70,   70,   70,   70,   70,   70,
   70,   70,   70,   70,   70,   70,   70,   70,   70,   70,
   70,   70,   70,   70,   70,   70,   70,   70,   70,   70,
   70,   70,   70,   70,   70,   70,   70,   70,   70,   70,
   70,   70
};


const short int MathLexer::chk[173] =
{   0,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    5,   72,
    5,    8,    8,    8,    8,    8,   10,   10,   10,   10,
   11,   68,   20,   11,   20,   25,   25,   25,   25,   26,
   27,   28,   26,   67,   27,   27,   27,   27,   35,   35,
   28,   29,   29,   29,   29,   37,   66,   65,   37,   37,
   37,   37,   44,   44,   44,   44,   45,   45,   45,   45,
   71,   64,   71,   73,   62,   73,   61,   60,   59,   58,
   56,   55,   54,   53,   52,   51,   50,   48,   47,   46,
   43,   42,   41,   40,   39,   38,   36,   34,   33,   32,
   31,   30,   24,   23,   22,   21,   17,   14,   13,   12,
    7,    6,    3,   70,   70,   70,   70,   70,   70,   70,
   70,   70,   70,   70,   70,   70,   70,   70,   70,   70,
   70,   70,   70,   70,   70,   70,   70,   70,   70,   70,
   70,   70,   70,   70,   70,   70,   70,   70,   70,   70,
   70,   70
};



int MathLexer::input()
{
  int c;

  *c_buf_p = hold_char;

  if ( *c_buf_p == END_OF_BUFFER_CHAR )
  {
    if ( c_buf_p < &current_buffer->ch_buf[n_chars] )
      *c_buf_p = '\0';
    else
    {
      int offset = (int)(c_buf_p - text);
      ++c_buf_p;

      switch ( get_next_buffer() )
      {
      case EOB_ACT_LAST_MATCH:
        restart();
      case EOB_ACT_END_OF_FILE:
      {
        if ( wrap() )
          return EOF;

        if ( ! did_buffer_switch_on_eof )
          restart();
        return input();
      }

      case EOB_ACT_CONTINUE_SCAN:
        c_buf_p = text + offset;
        break;
      }
    }
  }

  c = *(unsigned char *) c_buf_p;
  *c_buf_p = '\0';
  hold_char = *++c_buf_p;

  return c;
}


void MathLexer::less( int n, CHAR *bp, CHAR *cp )
{
  for (;;)
  {
    *cp = hold_char;
    c_buf_p = cp = bp + n - MORE_ADJ;
    DO_BEFORE_ACTION( bp, cp );
  }
}

void MathLexer::DO_BEFORE_ACTION( CHAR *bp, CHAR *cp )
{
  text = bp;
  leng = (int) (cp - bp);
  hold_char = *cp;
  *cp = '\0';
  c_buf_p = cp;
}

int MathLexer::lex( LvalStruct &lval )
{
  int current_state;
  CHAR *cp = (char *)0;
  CHAR *bp = (char *)0;
  int act;








  if ( init )
  {
    init = 0;

    if ( ! start )
      start = 1;

    if ( ! current_buffer )
      current_buffer =
        create_buffer( BUF_SIZE );

    load_buffer_state();
  }

  for(;;)
  {
    cp = c_buf_p;


    *cp = hold_char;


    bp = cp;

    current_state = start;
match:
    do
    {
      UCHAR c = ec[(int unsigned)(UCHAR)*cp];
      if ( accept[current_state] )
        {
        last_accepting_state = current_state;
        last_accepting_cpos = cp;
        }
      while ( chk[base[current_state] + c] != current_state )
        {
        current_state = (int) def[current_state];
        if ( current_state >= CONSTANT1 )
                c = meta[(unsigned int) c];
        }
      current_state = nxt[base[current_state] + (unsigned int) c];
      ++cp;
    }
    while ( base[current_state] != CONSTANT2 );

find_action:
    act = accept[current_state];
    if ( act == 0 )
    {
      cp = last_accepting_cpos;
      current_state = last_accepting_state;
      act = accept[current_state];
    }

    text = bp;
    leng = (int) (cp - bp);
    hold_char = *cp;
    *cp = '\0';
    c_buf_p = cp;

do_action:

    switch ( act )
{
      case 0:

      *cp = hold_char;
      cp = last_accepting_cpos;
      current_state = last_accepting_state;
      goto find_action;

case 1:

{
}
  break;
case 2:

{
TRACEX;
  lval.text = text;
  return R_Graphics;
}
  break;
case 3:

{
TRACEX;
  lval.text = text;
  return R_Graphics3D;
}
  break;
case 4:

{
TRACEX;
  lval.text = text;
  return R_SurfaceGraphics;
}
  break;
case 5:

{
TRACEX;
  lval.text = text;
  return R_Polygon;
}
  break;
case 6:

{
TRACEX;
  lval.text = text;
  return R_Real;
}
  break;
case 7:

{
TRACEX;
  lval.text = text;
  return R_leftBrace;
}
  break;
case 8:

{
TRACEX;
  lval.text = text;
  return R_rightBrace;
}
  break;
case 9:

{
TRACEX;
  lval.text = text;
  return R_leftBracket; 
}
  break;
case 10:

{
TRACEX;
  lval.text = text;
  return R_rightBracket;
}
  break;
case 11:

{
TRACEX;
  lval.text = text;
  return R_comma;
}
  break;
case 12:

{
}
  break;
case 13:

{
TRACEX;
  cleanup();
  throw ::io::ReadException(
	::io::ReadException::PARSE_ERROR,
	_stream->filename(), _lineno, "unknown text" );
}
  break;
case 14:
;
  break;

case (END_OF_BUFFER + INITIAL + 1):
	return 0;

  case END_OF_BUFFER:
  {

    int amount_of_matched_text = (int) (cp - text) - 1;

    *cp = hold_char;

    if ( current_buffer->buffer_status == BUFFER_NEW )
    {

      n_chars = current_buffer->n_chars;
      current_buffer->buffer_status = BUFFER_NORMAL;
    }


    if ( c_buf_p <= &current_buffer->ch_buf[n_chars] )
    {
      int next_state;

      c_buf_p = text + amount_of_matched_text;

      current_state = get_previous_state();



      next_state = try_NUL_trans( current_state );

      bp = text + MORE_ADJ;

      if ( next_state )
        {

        cp = ++c_buf_p;
        current_state = next_state;
        goto match;
        }

      else
        {
        cp = c_buf_p;
        goto find_action;
        }
    }

    else switch ( get_next_buffer() )
    {
      case EOB_ACT_END_OF_FILE:
        {
        did_buffer_switch_on_eof = 0;

        if ( wrap() )
                {

                c_buf_p = text + MORE_ADJ;

                act = STATE_EOF(START());
                goto do_action;
                }

        else
                {
                if ( ! did_buffer_switch_on_eof )
                        restart();
                }
        break;
        }

      case EOB_ACT_CONTINUE_SCAN:
        c_buf_p =
                text + amount_of_matched_text;

        current_state = get_previous_state();

        cp = c_buf_p;
        bp = text + MORE_ADJ;
        goto match;

      case EOB_ACT_LAST_MATCH:
        c_buf_p =
        &current_buffer->ch_buf[n_chars];

        current_state = get_previous_state();

        cp = c_buf_p;
        bp = text + MORE_ADJ;
        goto find_action;
    }
    break;
  }

  default:
    fatal_error(
      "flex internal error: no action found" );
}
  }
}

int MathLexer::get_next_buffer()
{
  CHAR *dest = current_buffer->ch_buf;
  CHAR *source = text;
  int number_to_move, i;
  int ret_val;

  if ( c_buf_p > &current_buffer->ch_buf[n_chars + 1] )
    fatal_error(
    "flex internal error: end of buffer missed" );

  if ( current_buffer->fill_buffer == 0 )
  {
    if ( c_buf_p - text - MORE_ADJ == 1 )
    {

      return EOB_ACT_END_OF_FILE;
    }

    else
    {

      return EOB_ACT_LAST_MATCH;
    }
  }

  number_to_move = (int) (c_buf_p - text) - 1;

  for ( i = 0; i < number_to_move; ++i )
    *(dest++) = *(source++);

  if ( current_buffer->buffer_status == BUFFER_EOF_PENDING )

    current_buffer->n_chars = n_chars = 0;

  else
  {
    int num_to_read =
      (int)(current_buffer->buf_size - number_to_move - 1);

    while ( num_to_read <= 0 )
    {
      BufferState * b = current_buffer;

      int c_buf_p_offset =
        (int) (c_buf_p - b->ch_buf);

      if ( b->is_our_buffer )
        {
        int new_size = (int)(b->buf_size * 2);

        if ( new_size <= 0 )
                b->buf_size += b->buf_size / 8;
        else
                b->buf_size *= 2;

        b->ch_buf = (CHAR *)
                flex_realloc( (void *) b->ch_buf,
                                 b->buf_size + 2 );
        }
      else

        b->ch_buf = 0;

      if ( ! b->ch_buf )
        fatal_error(
        "flex internal error: scanner input buffer overflow" );

      c_buf_p = &b->ch_buf[c_buf_p_offset];

      num_to_read = (int)(current_buffer->buf_size -
                        number_to_move - 1);
    }

    if ( num_to_read > READ_BUF_SIZE )
      num_to_read = READ_BUF_SIZE;


    input( (&current_buffer->ch_buf[number_to_move]),
      n_chars, num_to_read );

    current_buffer->n_chars = n_chars;
  }

  if ( n_chars == 0 )
  {
    if ( number_to_move == MORE_ADJ )
    {
      ret_val = EOB_ACT_END_OF_FILE;
      restart();
    }

    else
    {
      ret_val = EOB_ACT_LAST_MATCH;
      current_buffer->buffer_status =
        BUFFER_EOF_PENDING;
    }
  }

  else
    ret_val = EOB_ACT_CONTINUE_SCAN;

  n_chars += number_to_move;
  current_buffer->ch_buf[n_chars] = END_OF_BUFFER_CHAR;
  current_buffer->ch_buf[n_chars + 1] = END_OF_BUFFER_CHAR;

  text = &current_buffer->ch_buf[0];

  return ret_val;
}

int MathLexer::get_previous_state()
{
  int current_state;
  CHAR *cp;

  current_state = start;

  for ( cp = text + MORE_ADJ; cp < c_buf_p; ++cp )
  {
    UCHAR c = (*cp ? ec[(int unsigned)(UCHAR)*cp] : 1);
    if ( accept[current_state] )
    {
      last_accepting_state = current_state;
      last_accepting_cpos = cp;
    }
    while ( chk[base[current_state] + c] != current_state )
    {
      current_state = (int) def[current_state];
      if ( current_state >= CONSTANT1 )
        c = meta[(unsigned int) c];
    }
    current_state = nxt[base[current_state] + (unsigned int) c];
  }

  return current_state;
}

int MathLexer::try_NUL_trans( int current_state )
{
  int is_jam;
  CHAR *cp = c_buf_p;

  UCHAR c = 1;
  if ( accept[current_state] )
  {
    last_accepting_state = current_state;
    last_accepting_cpos = cp;
  }
  while ( chk[base[current_state] + c] != current_state )
  {
    current_state = (int) def[current_state];
    if ( current_state >= CONSTANT1 )
      c = meta[(unsigned int) c];
  }
  current_state = nxt[base[current_state] + (unsigned int) c];
  is_jam = ( current_state == CONSTANT1 - 1 );

  return is_jam ? 0 : current_state;
}

void MathLexer::unput( int c, CHAR *bp )
{
  CHAR *cp = c_buf_p;

  *cp = hold_char;

  if ( cp < current_buffer->ch_buf + 2 )
  {

    size_t number_to_move = n_chars + 2;
    CHAR *dest = &current_buffer->ch_buf[
                current_buffer->buf_size + 2];
    CHAR *source =
        &current_buffer->ch_buf[number_to_move];

    while ( source > current_buffer->ch_buf )
      *--dest = *--source;

    cp += (int) (dest - source);
    bp += (int) (dest - source);
    current_buffer->n_chars =
      n_chars = current_buffer->buf_size;

    if ( cp < current_buffer->ch_buf + 2 )
      fatal_error( "flex internal error: push-back overflow" );
  }

  *--cp = (CHAR) c;

  text = bp;
  hold_char = *cp;
  c_buf_p = cp;
}

void MathLexer::restart()
{
  if ( ! current_buffer )
    current_buffer = create_buffer( BUF_SIZE );

  init_buffer( current_buffer );
  load_buffer_state();
}

void MathLexer::switch_to_buffer( BufferState * new_buffer )
{
  if ( current_buffer == new_buffer )
    return;

  if ( current_buffer )
  {

    *c_buf_p = hold_char;
    current_buffer->buf_pos = c_buf_p;
    current_buffer->n_chars = n_chars;
  }

  current_buffer = new_buffer;
  load_buffer_state();


  did_buffer_switch_on_eof = 1;
}

void MathLexer::load_buffer_state()
{
  n_chars = current_buffer->n_chars;
  text = c_buf_p = current_buffer->buf_pos;
  hold_char = *c_buf_p;
}

MathLexer::BufferState *MathLexer::create_buffer( int size )
{
  BufferState *b;

  b = (BufferState *) flex_alloc( sizeof( BufferState ) );
  if ( ! b )
    fatal_error( "flex internal error: out of memory" );

  b->buf_size = size;


  b->ch_buf = (CHAR *) flex_alloc( b->buf_size + 2 );
  if ( ! b->ch_buf )
    fatal_error( "flex internal error: out of memory" );

  b->is_our_buffer = 1;

  init_buffer( b );

  return b;
}

void MathLexer::delete_buffer( BufferState * b )
{
  if ( ! b )
    return;

  if ( b == current_buffer )
  {
    current_buffer = (BufferState *)0;
  }

  if ( b->is_our_buffer )
  {
    flex_free( (void *) b->ch_buf );
  }

  flex_free( (void *) b );
}

void MathLexer::init_buffer( BufferState * b )
{
  flush_buffer( b );

  b->fill_buffer = 1;
  b->is_interactive = 0;
}

void MathLexer::flush_buffer( BufferState * b )
{
  if ( ! b )
    return;

  b->n_chars = 0;

  b->ch_buf[0] = END_OF_BUFFER_CHAR;
  b->ch_buf[1] = END_OF_BUFFER_CHAR;

  b->buf_pos = &b->ch_buf[0];

  b->at_bol = 1;
  b->buffer_status = BUFFER_NEW;

  if ( b == current_buffer )
    load_buffer_state();
}

MathLexer::BufferState *MathLexer::scan_buffer( CHAR *base, size_t size )
{
  BufferState * b;

  if ( size < 2 ||
       base[size-2] != END_OF_BUFFER_CHAR ||
       base[size-1] != END_OF_BUFFER_CHAR )

    return 0;

  b = (BufferState *) flex_alloc( sizeof( BufferState ) );
  if ( ! b )
    fatal_error( "flex internal error: out of memory" );

  b->buf_size = size - 2;
  b->buf_pos = b->ch_buf = base;
  b->is_our_buffer = 0;
  b->n_chars = b->buf_size;
  b->is_interactive = 0;
  b->at_bol = 1;
  b->fill_buffer = 0;
  b->buffer_status = BUFFER_NEW;

  switch_to_buffer( b );

  return b;
}

MathLexer::BufferState *MathLexer::scan_string( const CHAR *str )
{
  int len;
  for ( len = 0; str[len]; ++len )
    ;

  return scan_bytes( str, len );
}

MathLexer::BufferState *MathLexer::scan_bytes( const CHAR *bytes, int len )
{
  BufferState * b;
  CHAR *buf;
  size_t n;
  int i;


  n = len + 2;
  buf = (CHAR *) flex_alloc( n );
  if ( ! buf )
    fatal_error( "flex internal error: out of memory" );

  for ( i = 0; i < len; ++i )
    buf[i] = bytes[i];

  buf[len] = buf[len+1] = END_OF_BUFFER_CHAR;

  b = scan_buffer( buf, n );
  if ( ! b )
    fatal_error( "flex internal error: bad buffer" );


  b->is_our_buffer = 1;

  return b;
}

void MathLexer::push_state( int new_state )
{
  if ( start_stack_ptr >= start_stack_depth )
  {
    size_t new_size;

    start_stack_depth += START_STACK_INCR;
    new_size = start_stack_depth * sizeof( int );

    if ( ! start_stack )
      start_stack = (int *) flex_alloc( new_size );

    else
      start_stack = (int *) flex_realloc(
                (void *) start_stack, new_size );

    if ( ! start_stack )
      fatal_error(
      "flex internal error: out of memory expanding start-condition stack" );
  }

  start_stack[start_stack_ptr++] = START();

  BEGIN(new_state);
}

void MathLexer::pop_state()
{
  if ( --start_stack_ptr < 0 )
    fatal_error( "flex internal error: start-condition stack underflow" );

  BEGIN(start_stack[start_stack_ptr]);
}

int MathLexer::top_state()
{
  return start_stack[start_stack_ptr - 1];
}

void MathLexer::fatal_error( const CHAR msg[] )
{
  std::cerr << msg << std::endl;
  throw 1;
}

void *MathLexer::flex_alloc( size_t size )
{
  return (void *) malloc( size );
}

void *MathLexer::flex_realloc( void *ptr, size_t size )
{
  return (void *) realloc( (UCHAR *) ptr, size );
}

void MathLexer::flex_free( void *ptr )
{
  free( ptr );
}

int MathLexer::wrap()
{
  return 1;
}

} // namespace io
} // namespace geom

#if defined(__sgi) && !defined(__GNUG__)
#pragma set woff 1110
#endif

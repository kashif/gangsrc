/* GANG Software
 * LAB/lab/gtklab/LabMain.H
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

#ifndef lab_gtklab_LabMain_INCLUDED
#define lab_gtklab_LabMain_INCLUDED

#include "base/Getopt.H"
#include "io/IstreamStream.H"
#include "Lab.H"

namespace lab {
namespace gtklab {

template<class LAB>
class LabMain
{

public:
  // constructor
  LabMain( int argc, char **argv );

  // destructor
  virtual ~LabMain();

  int run();

protected:

private:

  int getopt();

  int _argc;
  char **_argv;
  uint _verbosity;
  uint _multithread;
  char const *_infile;
  base::String _background;
  bool _compute;
  bool _stdin;
  bool _command_mode;

  // disabled copy constructor
  LabMain( LabMain const & );

  // disabled assignment operator
  LabMain &operator=( LabMain const & );

};

template<class LAB>
LabMain<LAB>::
LabMain( int argc, char **argv )
    :
    _argc(argc),
    _argv(argv),
    _verbosity(0),
    _multithread(1),
    _infile( (char *)0 ),
    _background(),
    _compute(false),
    _stdin(false),
    _command_mode(false)
{
}

template<class LAB>
LabMain<LAB>::
~LabMain()
{
}

template<class LAB>
int
LabMain<LAB>::
getopt()
{
  using base::system;
  system->name( LAB::app_name() );
  system->copyright("(c) 2002 Nicholas Schmitt nick@math.umass.edu");
  system->usage( ( base::String(LAB::app_name()) +
                   base::String(" OPTIONS [file]")).c_str() );
  system->options(
    "  -b FILE: load FILE as background image\n"
    "  -c: read commands from stdin\n"
    "  -p(0|1): multithread off|on\n"
    "  -q(0|1): verbosity off|on\n"
    "  -s: read from stdin\n"
    "  -x: begin computation\n"
    "  -v: print version string and exit\n"
    "  -h: print usage message and exit\n"
    );

  base::Getopt::Options options[] =
    {
      { 'b', "background", true },
      { 'c', "command", false },
      { 'h', "help", false },
      { 'p', "multithread", true },
      { 'q', "verbosity", true },
      { 's', "stdin", false },
      { 'v', "version", false },
      { 'x', "run", false }
    };

  base::Getopt opt( options,
                    sizeof(options)/sizeof(base::Getopt::Options) );

  int r = opt.getopt( _argc, _argv );

  if ( r != 0 )
  {
    system->usage(opt.optopt(), r);
    return 1;
  }
  if ( opt.defined('h') )
  {
    system->help();
    return 1;
  }
  if ( opt.defined('v') )
  {
    system->print_version();
    return 1;
  }

  if ( opt.defined('p') )
  {
    opt.option('p').to_number( _multithread );
  }
  if ( opt.defined('q') )
  {
    opt.option('q').to_number( _verbosity );
  }
  if ( opt.defined('x') )
  {
    _compute = true;
  }
  if ( opt.defined('s') )
  {
    _stdin = true;
  }
  if ( opt.defined('b') )
  {
    _background = opt.option('b');
  }

  // input commands
  if ( opt.defined('c') )
  {
    _command_mode = true;
  }

  if ( _argc - opt.optind() > 1 )
  {
    system->usage();
    return 1;
  }

  // get input filename from the commandline
  _infile = (char *)0;

  if ( _argc - opt.optind() == 1 )
  {
    _infile = _argv[opt.optind()];
  }

  return 0;
}


template<class LAB>
int
LabMain<LAB>::
run()
{
  int r = getopt();
  if (r != 0) { return r; }

  gtk_init( &_argc, &_argv );

  LAB *X = new LAB;
  X->new_window();

  if (!_background.empty())
  {
    X->background_image( _background );
  }

  X->verbosity(_verbosity);
  X->multithread(_multithread);
  X->command_mode(_command_mode);

  if ( _stdin )
  {
    io::IstreamStream stream(std::cin);
    X->read_labfile( stream );
    if ( _compute ) { X->compute(); }
  }
  else if (_infile != (char *)0)
  {
    X->read_labfile(_infile);
    if ( _compute ) { X->compute(); }
  }

  gtk_main();

  delete X;

  return 0;
}

} // namespace gtklab
} // namespace lab

#endif // lab_gtklab_LabMain_INCLUDED

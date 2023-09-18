/* GANG Software
 * LAB/lab/cmdlab/LabMain.H
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

#ifndef lab_cmdlab_LabMain_INCLUDED
#define lab_cmdlab_LabMain_INCLUDED

#include <iostream>
#include "base/System.H"
#include "base/String.H"
#include "base/Getopt.H"
#include "io/OstreamStream.H"
#include "Lab.H"

namespace lab {
namespace cmdlab {

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
  base::String _infile;

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
    _multithread(1)
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
  system->usage( (base::String(LAB::app_name())+
                  base::String(" OPTIONS file > file")).c_str());
  system->options(
    "  -p(0|1): multithread off|on\n"
    "  -q(0|1): verbosity off|on\n"
    "  -v: print version string and exit\n"
    "  -h: print usage message and exit\n");

  base::Getopt::Options options[] =
    {
      { 'p', "multithread", true },
      { 'q', "verbosity", true },
      { 'v', "version", false },
      { 'h', "help", false }
    };

  base::Getopt opt( options,
                    sizeof(options)/sizeof(base::Getopt::Options) );

  int r = opt.getopt( _argc, _argv );

  if ( r != 0 )
  {
    system->usage(opt.optopt(), r);
    return 1;
  }
  else if ( opt.defined('h') )
  {
    system->help();
    return 1;
  }
  else if ( opt.defined('v') )
  {
    system->print_version();
    return 1;
  }

  if ( opt.defined('p') )
  {
    try {
      opt.option('p').to_number( _multithread );
    }
    catch ( base::Exception const & ) { return 1; }

  }
  if ( opt.defined('q') )
  {
    try {
      opt.option('q').to_number( _verbosity );
    }
    catch ( base::Exception const & ) { return 1; }
  }

  if ( _argc - opt.optind() != 1 )
  {
    system->usage();
    return 1;
  }

  _infile = _argv[opt.optind()];

  return 0;
}

template<class LAB>
int
LabMain<LAB>::
run()
{
  int r = getopt();
  if (r != 0) { return r; }

  LAB *X = new LAB;

  X->verbosity( _verbosity );
  X->multithread( _multithread );

  try
  {
    // read the surface data
    X->read_labfile(_infile);

    // compute and write the surface
    X->compute();

  }
  catch ( base::Exception const &e)
  {
    std::cerr << base::system->name() << ": " << e.message() << "\n"
              << base::system->name() << ": Computation failed\n";
    r = 1;
  }

  delete X;

  return r;
}

} // namespace cmdlab
} // namespace lab

#endif // lab_cmdlab_LabMain_INCLUDED

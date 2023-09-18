/* GANG Software
 * VIEWER/isight/gtkmain/main.C
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

#include <stdlib.h>
#include "base/String.H"
#include "base/System.H"
#include "base/Getopt.H"
#include "base/Regex.H"
#include "io/IstreamStream.H"
#include "isight/interface/IsightGtk.H"

static int main_( int argc, char *argv[] );

int
main( int argc, char *argv[] )
{
  return base::System::run( main_, argc, argv );
}

int
main_( int argc, char *argv[] )
{
  using base::system;
  system->name("isight");
  system->copyright("(c) 2002 Nicholas Schmitt nick@math.umass.edu");
  system->usage("isight OPTIONS [file]");
  system->options(
    "  -b FILE: load FILE as background image\n"
    "  -c: read commands from stdin\n"
    "  -v: print version string and exit\n"
    "  -h: print usage message and exit\n"
    "  -s TYPE: read file of type TYPE from stdin\n"
    );

  base::Getopt::Options options[] =
    {
      { 'b', "background", true },
      { 'c', "command", false },
      { 'h', "help", false },
      { 's', "stdin", true },
      { 'v', "version", false }
    };

  base::Getopt opt( options,
                    sizeof(options)/sizeof(base::Getopt::Options) );

  int r = opt.getopt( argc, argv );

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

  gtk_init( &argc, &argv );

  // create viewer
  isight::IsightGtk *_viewer = new isight::IsightGtk();
  _viewer->new_window();

  if ( opt.defined('b') )
  {
    _viewer->background_image( opt.option('b').c_str() );
  }

  // read files
  base::vector<base::String> filename;
  char const **f = (char const **)(argv + opt.optind());
  while( *f != (char *)0 )
  {
    filename.push_back(base::String(*f));
    f++;
  }
  _viewer->read( filename );

  // read file from stdin
  if ( opt.defined('s') )
  {
    base::String s = opt.option('s');
    geom::FileMode filemode = geom::FILEMODE_UNSPECIFIED;
    if (s == "isx") { filemode = geom::FILEMODE_ISX; }
    else if (s == "jvx") { filemode = geom::FILEMODE_JVX; }
    else if (s == "vrml") { filemode = geom::FILEMODE_VRML; }
    else if (s == "oogl") { filemode = geom::FILEMODE_OOGL; }
    else if (s == "math") { filemode = geom::FILEMODE_MATHEMATICA; }
    else { std::cerr << "isight: unknown file mode option to -s\n"; exit(1); }
    io::IstreamStream stream(std::cin);
    _viewer->read( stream, filemode );
  }

  // input commands
  if ( opt.defined('c') )
  {
    _viewer->command_mode();
  }

  gtk_main();

  delete _viewer;

  return 0;
}

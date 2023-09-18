/* GANG Software
 * LAB/lab/ui/Ui.C
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
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include "base/String.H"
#include "base/System.H"
#include "base/String.H"
#include "base/Regex.H"
#include "base/Stl.H"
#include "base/Exception.H"
#include "eval/Eval.H"
#include "Ui.H"

namespace lab {
namespace ui {

Ui::
Ui()
    :
    Compute(),
    Domain(),
    Sequence(),
    Read(),
    Write()
{
#if FIX
  Sequence::reset();
#endif
}

Ui::
~Ui()
{
}

void
Ui::
show_all(bool state)
{
  compute_p()->show_d(state);
  domain_p()->show_d(state);
  sequence_p()->show_d(state);
  read_p()->show_d(state);
  write_p()->show_d(state);
}

void
Ui::
enable_tooltips(bool state)
{
  compute_p()->enable_tooltips_d(state);
  domain_p()->enable_tooltips_d(state);
  sequence_p()->enable_tooltips_d(state);
  read_p()->enable_tooltips_d(state);
  write_p()->enable_tooltips_d(state);
}

void
Ui::
clear_ui()
{
  Compute::reset();

#if 0
  // NOTE: is this right?
  Compute::set_name( surface_name_v().c_str() );
#endif

  Domain::reset();
  Sequence::reset();
}


void
Ui::
set_ui_from_data_v()
{
  set_ui_from_data();

  Compute::set(data());
  Domain::set(data());
  Read::set(data());
  Sequence::set(data());
  Write::set(data());
}

void
Ui::
set_data_from_ui_v()
{
  set_data_from_ui();

  Compute::get(data());
  Domain::get(data());
  Read::get(data());
  Sequence::get(data());
  Write::get(data());
}

bool
Ui::
command(
  base::String const &command,
  base::String const &argument,
  base::String &response )
{
  return
    compute_p()->command(command, argument, response) ||
    domain_p()->command(command, argument, response) ||
    sequence_p()->command(command, argument, response) ||
    read_p()->command(command, argument, response) ||
    write_p()->command(command, argument, response);
}


void
Ui::
controls_file( ::widget::ui::KeyBase &p )
{
  base::String read_str = "Open ";
  read_str += lab_name();
  read_str += " File...";

  // CTRL-O = Read Lab File
  p.insert(
    read_str.c_str(),     GDK_O, MOD_CTRL_SHIFT,
    static_cast< ::lab::ui::Ui *>(this),
    &::lab::ui::Ui::toggle_raise_show_read );

  base::String write_str = "Save ";
  write_str += lab_name();
  write_str += " File...";

  // CTRL-S = Write Lab File
  p.insert(
    write_str.c_str(),    GDK_S, MOD_CTRL_SHIFT,
    this,
    &::lab::ui::Ui::toggle_raise_show_write );
}

void
Ui::
controls( ::widget::ui::KeyBase &p )
{
  // CTRL-X = Compute Surface
  p.insert(
    "Compute Surface", GDK_X, MOD_CTRL_SHIFT,
    this,
    &::lab::ui::Ui::compute );

  // CTRL-C = Compute Widget
  p.insert(
    "Compute...",      GDK_C, MOD_CTRL_SHIFT,
    this,
    &::lab::ui::Ui::toggle_raise_show_compute );

  // controls
  base::String s = lab_name();
  s += "...";

  // CTRL-L = Lab Widget
  p.insert(
    s.c_str(),         GDK_L, MOD_CTRL_SHIFT,
    this,
    &::lab::ui::Ui::toggle_raise_show_controls );

  // CTRL-D = Domain Widget
  p.insert(
    "Domain...",       GDK_D, MOD_CTRL_SHIFT,
    this,
    &::lab::ui::Ui::toggle_raise_show_domain );

  // CTRL-U = Sequence Widget
  p.insert(
    "Sequence...",     GDK_U, MOD_CTRL_SHIFT,
    this,
    &::lab::ui::Ui::toggle_raise_show_sequence );
}

} // namespace ui
} // namespace lab

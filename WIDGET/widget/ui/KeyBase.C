/* GANG Software
 * WIDGET/widget/ui/KeyBase.C
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

#include "KeyBase.H"

/*
  GDK_SHIFT_MASK    = 1 << 0,
  GDK_LOCK_MASK     = 1 << 1, //(caps lock)
  GDK_CONTROL_MASK  = 1 << 2,
  GDK_MOD1_MASK     = 1 << 3,
  GDK_MOD2_MASK     = 1 << 4,
  GDK_MOD3_MASK     = 1 << 5,
  GDK_MOD4_MASK     = 1 << 6,
  GDK_MOD5_MASK     = 1 << 7,
  GDK_BUTTON1_MASK  = 1 << 8,
  GDK_BUTTON2_MASK  = 1 << 9,
  GDK_BUTTON3_MASK  = 1 << 10,
  GDK_BUTTON4_MASK  = 1 << 11,
  GDK_BUTTON5_MASK  = 1 << 12,
  GDK_RELEASE_MASK  = 1 << 13,
*/

GdkModifierType const MOD_NONE = GdkModifierType(0);
GdkModifierType const MOD_SHIFT = GDK_SHIFT_MASK;
GdkModifierType const MOD_CTRL = GDK_CONTROL_MASK;
GdkModifierType const MOD_ALT = GDK_MOD1_MASK;
GdkModifierType const MOD_CTRL_SHIFT = GdkModifierType(MOD_CTRL | MOD_SHIFT); 
GdkModifierType const MOD_CTRL_ALT = GdkModifierType(MOD_CTRL | MOD_ALT);

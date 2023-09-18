/* GANG Software
 * VIEWER/isight/cmd/ContextCmd.H
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

#ifndef isight_cmd_ContextCmd_INCLUDED
#define isight_cmd_ContextCmd_INCLUDED

#include "isight/context/ContextSetBase.H"
#include "isight/context/Context.H"
#include "opengl/PixMap.H"

namespace isight {
namespace cmd {

class ContextCmd
  :
    public isight::context::Context
{

public:
  // constructor
  ContextCmd( isight::context::ContextSetBase *base );

  // destructor
  virtual ~ContextCmd();


  static uint const WIDTH = 500U;
  static uint const HEIGHT = 500U;

  // widget::Widget
  virtual void show( bool state = true ) {}
  virtual bool showing() const { return false; }

  // widget::Window
  virtual void set_title( char const * ) {}
  virtual uint width() const { return WIDTH; }
  virtual uint height() const { return HEIGHT; }
  virtual uint x_position() const { return 0; }
  virtual uint y_position() const { return 0; }
  virtual void resize( uint width, uint height ) {}
  virtual void reposition( uint x, uint y ) {}
  virtual void raise( bool state = true ) {}
  virtual void raise_show( bool state = true ) {}
  virtual void toggle_raise_show() {}

  // widget::GLWindow
  virtual uint area_width() const { return WIDTH; }
  virtual uint area_height() const { return HEIGHT; }
  virtual void make_current() {}
  virtual void refresh() {}
  virtual void enable_draw(bool) {}

protected:

private:
  virtual void swap_buffers() { WARN(); }
  virtual widget::ui::Idler *idler() { return &_idler; }

  opengl::PixMap *_pixmap;


  struct Idler
    :
    public widget::ui::Idler
  {
    virtual void enable(bool) {}
  };
  Idler _idler;

  // disabled copy constructor
  ContextCmd( ContextCmd const & );
  // disabled assignment operator
  ContextCmd &operator=( ContextCmd const & );

};

} // namespace cmd
} // namespace isight

#endif // isight_cmd_ContextCmd_INCLUDED

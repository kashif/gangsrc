/* GANG Software
 * WIDGET/gtk/widget1/Netscape.C
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

/* Adapted from code from gaim-0.10.0 - http://www.marko.net/gaim/

 * Copyright (C) 1996 Netscape Communications Corporation, all rights reserved.
 * Created: Jamie Zawinski <jwz@netscape.com>, 24-Dec-94.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <math.h>
#if defined(__sgi) && !defined(__GNUG__)
#pragma set woff 1174
#endif
extern "C"
{
#include <gdk/gdkprivate.h>
#include <gdk/gdkx.h>
#include <gtk/gtk.h>
}
#if defined(__sgi) && !defined(__GNUG__)
#pragma reset woff 1174
#endif
#include <iostream>
#include "Netscape.H"

namespace gtk {
namespace widget1 {

Netscape::
Netscape()
{
}

Netscape::
~Netscape()
{
}

gint clean_pid(void *dummy)
{
  int status;
  pid_t pid;

  pid = waitpid(-1, &status, WNOHANG);

  if (pid == 0)
    return TRUE;

  return FALSE;
}

#ifdef DEBUG_NETSCAPE
static const char *progname = "GANG";
static char debug_buff[1024];
void
debug_print(char const *message)
{ std::cerr << message << "\n"; }
#endif

static const char *expected_mozilla_version = "1.1";

#define MOZILLA_VERSION_PROP   "_MOZILLA_VERSION"
#define MOZILLA_LOCK_PROP      "_MOZILLA_LOCK"
#define MOZILLA_COMMAND_PROP   "_MOZILLA_COMMAND"
#define MOZILLA_RESPONSE_PROP  "_MOZILLA_RESPONSE"

static GdkAtom XA_MOZILLA_VERSION  = 0;
static GdkAtom XA_MOZILLA_LOCK     = 0;
static GdkAtom XA_MOZILLA_COMMAND  = 0;
static GdkAtom XA_MOZILLA_RESPONSE = 0;


static int netscape_lock;


static Window
VirtualRootWindowOfScreen(Screen *screen)
{
  static Screen *save_screen = (Screen *)0;
  static Window root = (Window)0;

  if (screen != save_screen)
  {
    Display *dpy = DisplayOfScreen(screen);
    Atom __SWM_VROOT = None;
    unsigned int i;
    Window rootReturn, parentReturn, *children;
    unsigned int numChildren;

    root = RootWindowOfScreen(screen);

    // go look for a virtual root
    __SWM_VROOT = XInternAtom(dpy, "__SWM_VROOT", False);
    if (XQueryTree(dpy, root, &rootReturn, &parentReturn,
                   &children, &numChildren))
    {
      for (i = 0; i < numChildren; i++)
      {
        Atom actual_type;
        int actual_format;
        unsigned long nitems, bytesafter;
        Window *newRoot = (Window *)0;

        if (XGetWindowProperty(dpy, children[i],
                               __SWM_VROOT, 0, 1, False, XA_WINDOW,
                               &actual_type, &actual_format,
                               &nitems, &bytesafter,
                               (unsigned char **) &newRoot) == Success
            && newRoot)
        {
          root = *newRoot;
          break;
        }
      }
      if (children)
        XFree((char *)children);
    }

    save_screen = screen;
  }

  return root;
}

// The following code is Copyright (C) 1989 X Consortium

static
Window TryChildren(
  Display *dpy,
  Window win,
  Atom WM_STATE );

// Find a window with WM_STATE, else return win itself, as per ICCCM

static Window GClientWindow(
  Display *dpy,
  Window win )
{
  Atom WM_STATE;
  Atom type = None;
  int format;
  unsigned long nitems, after;
  unsigned char *data;
  Window inf;

  WM_STATE = XInternAtom(dpy, "WM_STATE", True);
  if (!WM_STATE)
    return win;
  XGetWindowProperty(dpy, win, WM_STATE, 0, 0, False, AnyPropertyType,
                     &type, &format, &nitems, &after, &data);
  if (type)
  {
    XFree(data);
    return win;
  }

  inf = TryChildren(dpy, win, WM_STATE);
  if (!inf)
    inf = win;

  XFree(data);

  return inf;
}

static
Window TryChildren(
  Display *dpy,
  Window win,
  Atom WM_STATE )
{
  Window root, parent;
  Window *children;
  unsigned int nchildren;
  unsigned int i;
  Atom type = None;
  int format;
  unsigned long nitems, after;
  unsigned char *data;
  Window inf = 0;

  if (!XQueryTree(dpy, win, &root, &parent, &children, &nchildren))
    return 0;
  for (i = 0; !inf && (i < nchildren); i++)
  {
    XGetWindowProperty(dpy, children[i], WM_STATE, 0, 0, False,
                       AnyPropertyType, &type, &format, &nitems,
                       &after, &data);
    if (type)
      inf = children[i];

    XFree(data);
  }
  for (i = 0; !inf && (i < nchildren); i++)
    inf = TryChildren(dpy, children[i], WM_STATE);
  if (children) XFree((char *)children);
  return inf;
}

// END X Consortium code



static void
mozilla_remote_init_atoms()
{
  if (!XA_MOZILLA_VERSION)
    XA_MOZILLA_VERSION = gdk_atom_intern(MOZILLA_VERSION_PROP, 0);
  if (!XA_MOZILLA_LOCK)
    XA_MOZILLA_LOCK = gdk_atom_intern(MOZILLA_LOCK_PROP, 0);
  if (! XA_MOZILLA_COMMAND)
    XA_MOZILLA_COMMAND = gdk_atom_intern(MOZILLA_COMMAND_PROP, 0);
  if (! XA_MOZILLA_RESPONSE)
    XA_MOZILLA_RESPONSE = gdk_atom_intern(MOZILLA_RESPONSE_PROP, 0);
}

static GdkWindow *mozilla_remote_find_window()
{
  int i;
  Window root = VirtualRootWindowOfScreen(DefaultScreenOfDisplay(gdk_display));
  Window root2, parent, *kids;
  unsigned int nkids;
  Window result = 0;
  Window tenative = 0;
  unsigned char *tenative_version = 0;

  if (!XQueryTree (gdk_display, root, &root2, &parent, &kids, &nkids))
  {
#ifdef DEBUG_NETSCAPE
    sprintf( debug_buff, "%s: XQueryTree failed on display %s\n", progname,
             DisplayString (gdk_display));
    debug_print(debug_buff);
#endif
    return 0;
  }

  // root != root2 is possible with virtual root WMs.

  if (!(kids && nkids))
  {
#ifdef DEBUG_NETSCAPE
    sprintf( debug_buff, "%s: root window has no children on display %s\n",
             progname, DisplayString (gdk_display));
    debug_print(debug_buff);
#endif
    return 0;
  }

  for (i = nkids-1; i >= 0; i--)
  {
    Atom type;
    int format;
    unsigned long nitems, bytesafter;
    unsigned char *version = 0;
    Window w = GClientWindow (gdk_display, kids[i]);
    int status = XGetWindowProperty (gdk_display, w, XA_MOZILLA_VERSION,
                                     0, (65536 / sizeof (long)),
                                     False, XA_STRING,
                                     &type, &format, &nitems, &bytesafter,
                                     &version);

    if (! version)
      continue;

    if (strcmp ((char *) version, expected_mozilla_version) &&
        !tenative)
    {
      tenative = w;
      tenative_version = version;
      continue;
    }
    XFree(version);
    if (status == Success && type != None)
    {
      result = w;
      break;
    }
  }

  XFree(kids);

  if (result && tenative)
  {
#ifdef DEBUG_NETSCAPE
    sprintf( debug_buff,
             "%s: warning: both version %s (0x%x) and version\n"
             "\t%s (0x%x) are running.  Using version %s.\n",
             progname, tenative_version, (unsigned int) tenative,
             expected_mozilla_version, (unsigned int) result,
             expected_mozilla_version);
    debug_print(debug_buff);
#endif
    XFree(tenative_version);
    return gdk_window_foreign_new((uint)result);
  }
  else if (tenative)
  {
#ifdef DEBUG_NETSCAPE
    sprintf( debug_buff,
             "%s: warning: expected version %s but found version\n"
             "\t%s (0x%x) instead.\n",
             progname, expected_mozilla_version,
             tenative_version, (unsigned int) tenative);
    debug_print(debug_buff);
#endif
    XFree(tenative_version);
    return gdk_window_foreign_new((uint)tenative);
  }
  else if (result)
  {
    return gdk_window_foreign_new((uint)result);
  }
  else
  {
#ifdef DEBUG_NETSCAPE
    sprintf( debug_buff, "%s: not running on display %s\n", progname,
             DisplayString (gdk_display));
    debug_print(debug_buff);
#endif
    return 0;
  }
}


static char *lock_data = 0;

static void
mozilla_remote_obtain_lock (GdkWindow *window)
{
  Bool locked = False;

  if (!lock_data)
  {
    lock_data = (char *)g_malloc (255);
    sprintf( lock_data, "pid%d@", getpid ());
    if (gethostname (lock_data + strlen (lock_data), 100))
    {
      return;
    }
  }

  do {
    int result;
    GdkAtom actual_type;
    gint actual_format;
    gint nitems;
    unsigned char *data = 0;

    result = gdk_property_get (window, XA_MOZILLA_LOCK,
                               XA_STRING, 0,
                               (65536 / sizeof (long)), 0,
                               &actual_type, &actual_format,
                               &nitems, &data);
    if (result != Success || actual_type == None)
    {
#ifdef DEBUG_NETSCAPE
      // It's not now locked - lock it.
      sprintf( debug_buff, "%s: (writing " MOZILLA_LOCK_PROP
               " \"%s\" to 0x%p)\n",
               progname, lock_data, (void *)window);
      debug_print(debug_buff);
#endif

      gdk_property_change(window, XA_MOZILLA_LOCK, XA_STRING,
                          8, (GdkPropMode)PropModeReplace,
                          (unsigned char *) lock_data,
                          strlen (lock_data));
      locked = True;
    }

    if (!locked)
    {
      // Then just fuck it.
      if (data)
        g_free(data);
      return;
    }
    if (data)
      g_free(data);
  } while (!locked);
}


static void
mozilla_remote_free_lock (GdkWindow *window)
{
  int result = 0;
  GdkAtom actual_type;
  gint actual_format;
  gint nitems;
  unsigned char *data = 0;

#ifdef DEBUG_NETSCAPE
  sprintf( debug_buff, "%s: (deleting " MOZILLA_LOCK_PROP
           " \"%s\" from 0x%p)\n",
           progname, lock_data, (void *)window);
  debug_print(debug_buff);
#endif

  result = gdk_property_get(window, XA_MOZILLA_LOCK, XA_STRING,
                            0, (65536 / sizeof (long)),
                            1, &actual_type, &actual_format,
                            &nitems, &data);
  if (result != Success)
  {
#ifdef DEBUG_NETSCAPE
    sprintf( debug_buff, "%s: unable to read and delete " MOZILLA_LOCK_PROP
             " property\n",
             progname);
    debug_print(debug_buff);
#endif
    return;
  }
  else if (!data || !*data)
  {
#ifdef DEBUG_NETSCAPE
    sprintf( debug_buff, "%s: invalid data on " MOZILLA_LOCK_PROP
             " of window 0x%p.\n",
             progname, (void *)window);
    debug_print(debug_buff);
#endif
    return;
  }
  else if (strcmp ((char *) data, lock_data))
  {
#ifdef DEBUG_NETSCAPE
    sprintf( debug_buff, "%s: " MOZILLA_LOCK_PROP
             " was stolen!  Expected \"%s\", saw \"%s\"!\n",
             progname, lock_data, data);
    debug_print(debug_buff);
#endif
   return;
  }

  if (data)
    g_free(data);
}


static int
mozilla_remote_command (GdkWindow *window, const char *command,
                        Bool raise_p)
{
  int result = 0;
  Bool done = False;
  char *new_command = 0;

  // The -noraise option is implemented by passing a "noraise" argument
  // to each command to which it should apply.

  if (!raise_p)
  {
    char *close;
    new_command = (char *)g_malloc (strlen (command) + 20);
    strcpy (new_command, command);
    close = strrchr (new_command, ')');
    if (close)
      strcpy (close, ", noraise)");
    else
      strcat (new_command, "(noraise)");
    command = new_command;
  }

#ifdef DEBUG_NETSCAPE
  sprintf( debug_buff, "%s: (writing " MOZILLA_COMMAND_PROP " \"%s\" to 0x%p)\n",
           progname, command, (void *)window);
  debug_print(debug_buff);
#endif

  gdk_property_change(window, XA_MOZILLA_COMMAND, XA_STRING, 8,
                      GDK_PROP_MODE_REPLACE, (unsigned char *) command,
                      strlen (command));

  while (!done)
  {
    GdkEvent *event;

    event = gdk_event_get();

    if (!event)
      continue;

    if (event->any.window != window)
    {
      gtk_main_do_event(event);
      continue;
    }

    if (event->type == GDK_DESTROY &&
        event->any.window == window)
    {
#ifdef DEBUG_NETSCAPE
      // Print to warn user...*/
      sprintf( debug_buff, "%s: window 0x%p was destroyed.\n",
               progname, (void *)window);
      debug_print(debug_buff);
#endif
      result = 6;
      goto DONE;
    } else if (event->type == GDK_PROPERTY_NOTIFY &&
               event->property.state == GDK_PROPERTY_NEW_VALUE &&
               event->property.window == window &&
               event->property.atom == XA_MOZILLA_RESPONSE)
    {
      GdkAtom actual_type;
      gint actual_format, nitems;
      unsigned char *data = 0;

      result = gdk_property_get (window, XA_MOZILLA_RESPONSE,
                                 XA_STRING, 0,
                                 (65536 / sizeof (long)),
                                 1,
                                 &actual_type, &actual_format,
                                 &nitems, &data);


      if (result == Success && data && *data)
      {
#ifdef DEBUG_NETSCAPE
        sprintf( debug_buff, "%s: (server sent " MOZILLA_RESPONSE_PROP
                 " \"%s\" to 0x%p.)\n",
                 progname, data, (void *)window);
        debug_print(debug_buff);
#endif
      }

      if (result != Success)
      {
#ifdef DEBUG_NETSCAPE
        sprintf( debug_buff, "%s: failed reading " MOZILLA_RESPONSE_PROP
                 " from window 0x%p.\n",
                 progname, (void *)window);
        debug_print(debug_buff);
#endif
        result = 6;
        done = True;
      } else if (!data || strlen((char *) data) < 5)
      {
#ifdef DEBUG_NETSCAPE
        sprintf( debug_buff, "%s: invalid data on " MOZILLA_RESPONSE_PROP
                 " property of window 0x%p.\n",
                 progname, (void *)window);
        debug_print(debug_buff);
#endif
        result = 6;
        done = True;
      } else if (*data == '1')
      {
        // positive preliminary reply
#ifdef DEBUG_NETSCAPE
        sprintf( debug_buff, "%s: %s\n", progname, data + 4);
        debug_print(debug_buff);
#endif
        // keep going
        done = False;
      } else if (!strncmp ((char *)data, "200", 3))
      {
        result = 0;
        done = True;
      } else if (*data == '2')
      {
#ifdef DEBUG_NETSCAPE
        sprintf( debug_buff, "%s: %s\n", progname, data + 4);
        debug_print(debug_buff);
#endif

        result = 0;
        done = True;
      } else if (*data == '3')
      {
#ifdef DEBUG_NETSCAPE
        sprintf( debug_buff, "%s: internal error: "
                 "server wants more information?  (%s)\n",
                 progname, data);
        debug_print(debug_buff);
#endif
        result = 3;
        done = True;
      } else if (*data == '4' || *data == '5')
      {
#ifdef DEBUG_NETSCAPE
        sprintf( debug_buff, "%s: %s\n", progname, data + 4);
        debug_print(debug_buff);
#endif
        result = (*data - '0');
        done = True;
      } else {
#ifdef DEBUG_NETSCAPE
        sprintf( debug_buff,
                 "%s: unrecognised " MOZILLA_RESPONSE_PROP
                 " from window 0x%p: %s\n",
                 progname, (void *)window, data);
        debug_print(debug_buff);
#endif
        result = 6;
        done = True;
      }

      if (data)
        g_free(data);
    }
    else if (event->type == GDK_PROPERTY_NOTIFY &&
             event->property.window == window &&
             event->property.state == GDK_PROPERTY_DELETE &&
             event->property.atom == XA_MOZILLA_COMMAND)
    {
#ifdef DEBUG_NETSCAPE
      sprintf( debug_buff, "%s: (server 0x%p has accepted "
               MOZILLA_COMMAND_PROP ".)\n",
               progname, (void *)window);
      debug_print(debug_buff);
#endif
    }
    gdk_event_free(event);
  }

  DONE:

  if (new_command)
    g_free (new_command);

  return result;
}


gint check_netscape(char *msg)
{
  int status;
  GdkWindow *window;

  mozilla_remote_init_atoms ();
  window = mozilla_remote_find_window();

  if (window)
  {
    XSelectInput(
      gdk_display,
      GDK_WINDOW_XWINDOW(window),
      (PropertyChangeMask|StructureNotifyMask));

    mozilla_remote_obtain_lock(window);

    status = mozilla_remote_command(window, msg, False);

    if (status != 6)
      mozilla_remote_free_lock(window);

    gtk_timeout_add(1000, (GtkFunction)clean_pid, 0);

    netscape_lock = 0;

    g_free(msg);
    return FALSE;
  } else
    return TRUE;
}


static void
netscape_command(char *command)
{
  int status;
  pid_t pid;
  GdkWindow *window;

  if (netscape_lock)
    return;

  netscape_lock = 1;

  mozilla_remote_init_atoms();
  window = mozilla_remote_find_window();

  if (window)
  {
    XSelectInput(
      gdk_display,
      GDK_WINDOW_XWINDOW(window),
      (PropertyChangeMask|StructureNotifyMask));

    mozilla_remote_obtain_lock(window);

    status = mozilla_remote_command(window, command, False);

    if (status != 6)
      mozilla_remote_free_lock(window);

    netscape_lock = 0;

    gdk_window_destroy (window);
  } else {
    pid = fork();
    if (pid == 0)
    {
      char *args[2];

      args[0] = g_strdup("netscape");
      args[1] = 0;
      execvp(args[0], args);
      printf("Hello%d\n", getppid());

      _exit(0);
    } else {
      char *tmp = g_strdup(command);
      gtk_timeout_add(200, (GtkFunction)check_netscape, tmp);
    }
  }

}

void
Netscape::
open_url(char const *url)
{
  char *command = (char *)g_malloc(1024);

  g_snprintf(command, 1024, "OpenURL(%s)", url);
  netscape_command(command);
  g_free(command);
}

void
Netscape::
add_bookmark(char const *url)
{
  char *command = (char *)g_malloc(1024);

  g_snprintf(command, 1024, "AddBookmark(%s)", url);
  netscape_command(command);
  g_free(command);
}

#if 0
void
Netscape::
open_url_new_window(char const *url)
{
  char *command = (char *)g_malloc(1024);

  g_snprintf(command, 1024, "OpenURL(%s, new-window)", url);
  netscape_command(command);
  g_free(command);
}
#endif

void
Netscape::
open_url_new_window(char const *url)
{
  mozilla_remote_init_atoms();
  GdkWindow *window = mozilla_remote_find_window();
  if (window == (GdkWindow *)0)
  {
    char *command = (char *)g_malloc(1024);
    g_snprintf(command, 1024, "OpenURL(%s)", url);
    netscape_command(command);
    g_free(command);
  }
  else
  {
    char *command = (char *)g_malloc(1024);
    g_snprintf(command, 1024, "OpenURL(%s, new-window)", url);
    netscape_command(command);
    g_free(command);
  }
}

} // namespace widget1
} // namespace gtk

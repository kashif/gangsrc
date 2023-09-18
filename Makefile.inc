# GANG Software Makefile
# Wed Sep 18 16:39:46 2002


# Linux gcc Makefile.inc

# c flags
C_FLAGS = -O3 -Wall -ansi -march=i386 -mcpu=i686 -D_GNU_SOURCE -D_THREAD_SAFE -D_SVID_SOURCE -D_BSD_SOURCE -D_ISOC9X_SOURCE -D_FILE_OFFSET_BITS=64


# commands
C_COMPILE = gcc -c $(C_FLAGS)
CPP_COMPILE = g++ -c $(C_FLAGS)
SHARED = g++ -shared
LINK = g++ $(C_FLAGS)
MAKEDEPEND = g++ -M $(C_FLAGS)


# include directories
INC_DIR = \
  -I/usr/include/gtk-1.2 \
  -I/usr/include/glib-1.2 \
  -I/usr/lib/glib/include \
  -I/usr/X11R6/include \
  -I/usr/X11R6/include/X11


# library directories
LIB_DIR = \
  -Llib \
  -L/usr/X11R6/lib


# libraries
LIB_GL = -lGL -lGLU -lX11 -lXmu -lXi -lm
LIB_IMAGE = -ljpeg -lpng -ltiff
LIB_GMP = -lgmp
LIB_IMLIB = -lgdk_imlib
LIB_GLUT = -lglut -lGL -lGLU -lX11 -lXmu -lXi -lm
LIB_COMPLEX = 
LIB_BLAS = -lblas -lm
LIB_M = -lm
LIB_THREAD = -lpthread
LIB_GDK = -lgdk -lglib -lm
LIB_GTK = -lgtk -lgdk -lglib -lm
LIB_LAPACK = -llapack -lblas -lf2c -lm
LIB_REGEX = 
LIB_XML = -lexpat
LIB_MEMORY = 
LIB_Z = -lz
LIB_GTKGL = -lgtkgl

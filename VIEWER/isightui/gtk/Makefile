# GANG Software Makefile
# Wed Sep 18 16:39:46 2002


include ../../../Makefile.inc

CPP_FILES = \
  Ui.C \
  Mouse.C \
  Geometry.C \
  WindowSize.C \
  Geometry_.C \
  Mouse_.C \
  WindowSize_.C \
  Read_.C \
  Read.C \
  Write_.C \
  Window.C \
  Window_.C \
  Style_.C \
  Style.C \
  Write.C \
  GeomObject_.C \
  WriteConfig.C \
  WriteConfig_.C \
  GeomObject.C \
  Shortcut_.C

C_FILES =

O_FILES = $(CPP_FILES:.C=.o) $(C_FILES:.c=.o)

all : $(O_FILES)

.C.o :
	$(CPP_COMPILE) -o $@ -I../../../BASE -I../../../WIDGET -I../../../GEOM -I../../../VIEWER -I../../../LAB -I../../../APP $(INC_DIR) $<

.c.o :
	$(C_COMPILE) -o $@ -I../../../BASE -I../../../WIDGET -I../../../GEOM -I../../../VIEWER -I../../../LAB -I../../../APP $(INC_DIR) $<

clean :
	- rm -f $(TARGET) $(O_FILES)

depend :
	$(MAKEDEPEND) $(CPP_FILES) $(C_FILES) -I../../../BASE -I../../../WIDGET -I../../../GEOM -I../../../VIEWER -I../../../LAB -I../../../APP $(INC_DIR) > Makefile.dep


clean-depend :
	- rm -f Makefile.dep; touch Makefile.dep

include Makefile.dep

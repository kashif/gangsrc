# GANG Software Makefile
# Wed Sep 18 16:39:46 2002


include ../../../Makefile.inc

TARGET = mrbubblelab-gtk

CPP_FILES = \
  main.C \
  MrBubbleLab.C

C_FILES =

O_FILES = $(CPP_FILES:.C=.o) $(C_FILES:.c=.o)

LIB = \
  $(COMPLEX_LIB) $(BLAS_LIB) -lm -lpthread -lz

$(TARGET) : $(O_FILES)
	$(LINK) -o $(TARGET) ../../../LAB/mrbubblelab/kernel/Lab.o ../../../LAB/mrbubblelab/kernel/MrBubble.o ../../../LAB/mrbubblelab/kernel/Exception.o ../../../LAB/mrbubblelab/kernel/Data.o ../../../LAB/mrbubblelab/ui/Controls.o ../../../LAB/mrbubblelab/ui/Ui.o ../../../LAB/mrbubblelab/gtk/Controls_.o ../../../LAB/mrbubblelab/gtk/Controls.o ../../../LAB/mrbubblelab/gtk/Ui.o ../../../LAB/mrbubblelab/gtklab/MrBubbleLab.o $(O_FILES) -L../../../lib $(LIB_DIR) $(LIB) -lgang_base -lgang_thread -lgang_eval -lgang_math -lgang_io -lgang_parser -lgang_widget -lgang_triang -lgang_geom -lgang_lab -lgang_gtk -lgang_image -lgang_viewer -lgang_viewergtk -lgang_geomgtk -lgang_labgtk -lgang_opengl $(LIB_GTK) $(LIB_GL) $(LIB_GTKGL) $(LIB_IMAGE) $(LIB_XML) $(LIB_COMPLEX) $(LIB_Z) $(LIB_THREAD) $(LIB_REGEX) $(LIB_M)
	 strip $(TARGET)

.C.o :
	$(CPP_COMPILE) -o $@ -I../../../BASE -I../../../WIDGET -I../../../GEOM -I../../../VIEWER -I../../../LAB -I../../../APP $(INC_DIR) $<

.c.o :
	$(C_COMPILE) -o $@ -I../../../BASE -I../../../WIDGET -I../../../GEOM -I../../../VIEWER -I../../../LAB -I../../../APP $(INC_DIR) $<

clean :
	- rm -f $(TARGET) $(O_FILES)

depend :
	$(MAKEDEPEND) $(INC_DIR) $(CPP_FILES) -I../../../BASE -I../../../WIDGET -I../../../GEOM -I../../../VIEWER -I../../../LAB -I../../../APP $(INC_DIR) > Makefile.dep

clean-depend :
	- rm -f Makefile.dep; touch Makefile.dep

include Makefile.dep

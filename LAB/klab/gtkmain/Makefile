# GANG Software Makefile
# Wed Sep 18 16:39:46 2002


include ../../../Makefile.inc

TARGET = klab-gtk

CPP_FILES = \
  main.C \
  KLab.C

C_FILES =

O_FILES = $(CPP_FILES:.C=.o) $(C_FILES:.c=.o)

LIB = \
  $(COMPLEX_LIB) $(BLAS_LIB) -lm -lpthread -lz

$(TARGET) : $(O_FILES)
	$(LINK) -o $(TARGET) ../../../LAB/klab/kernel/Lab.o ../../../LAB/klab/kernel/Sym.o ../../../LAB/klab/kernel/Integrator.o ../../../LAB/klab/kernel/Exception.o ../../../LAB/klab/kernel/Data.o ../../../LAB/klab/ui/Controls.o ../../../LAB/klab/ui/Ui.o ../../../LAB/klab/gtk/Controls_.o ../../../LAB/klab/gtk/Controls.o ../../../LAB/klab/gtk/Ui.o ../../../LAB/klab/gtklab/KLab.o $(O_FILES) -L../../../lib $(LIB_DIR) $(LIB) -lgang_base -lgang_thread -lgang_eval -lgang_math -lgang_io -lgang_parser -lgang_widget -lgang_triang -lgang_geom -lgang_lab -lgang_gtk -lgang_image -lgang_viewer -lgang_viewergtk -lgang_geomgtk -lgang_labgtk -lgang_opengl -lgang_loop $(LIB_GTK) $(LIB_GL) $(LIB_GTKGL) $(LIB_IMAGE) $(LIB_XML) $(LIB_LAPACK) $(LIB_COMPLEX) $(LIB_Z) $(LIB_THREAD) $(LIB_REGEX) $(LIB_M)
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

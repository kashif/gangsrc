# GANG Software Makefile
# Wed Sep 18 16:39:46 2002


include ../../../Makefile.inc

TARGET = minlab-cmd

CPP_FILES = \
  main.C \
  MinLab.C

C_FILES =

O_FILES = $(CPP_FILES:.C=.o) $(C_FILES:.c=.o)

LIB = \
  $(COMPLEX_LIB) $(BLAS_LIB) -lm -lpthread -lz

$(TARGET) : $(O_FILES)
	$(LINK) -o $(TARGET) ../../../LAB/minlab/kernel/Lab.o ../../../LAB/minlab/kernel/Exception.o ../../../LAB/minlab/kernel/Data.o ../../../LAB/minlab/kernel/LabBase.o ../../../LAB/minlab/ui/Controls.o ../../../LAB/minlab/ui/Ui.o ../../../LAB/minlab/cmd/Controls.o ../../../LAB/minlab/cmd/Ui.o ../../../LAB/minlab/cmdlab/MinLab.o $(O_FILES) -L../../../lib $(LIB_DIR) $(LIB) -lgang_base -lgang_thread -lgang_eval -lgang_math -lgang_io -lgang_parser -lgang_widget -lgang_triang -lgang_geom -lgang_lab $(LIB_XML) $(LIB_COMPLEX) $(LIB_Z) $(LIB_THREAD) $(LIB_REGEX) $(LIB_M)
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

# GANG Software Makefile
# Wed Sep 18 16:39:46 2002


all :
	cd BASE/base; $(MAKE)
	cd BASE/math; $(MAKE)
	cd BASE/io; $(MAKE)
	cd BASE/eval; $(MAKE)
	cd BASE/vrml; $(MAKE)
	cd BASE/parser; $(MAKE)
	cd BASE/image; $(MAKE)
	cd BASE/glut; $(MAKE)
	cd BASE/thread; $(MAKE)
	cd WIDGET/app/ui; $(MAKE)
	cd WIDGET/app/cmd; $(MAKE)
	cd WIDGET/app/gtk; $(MAKE)
	cd WIDGET/app/app; $(MAKE)
	cd WIDGET/widget/cmd; $(MAKE)
	cd WIDGET/widget/ui; $(MAKE)
	cd WIDGET/gtk/widgetc; $(MAKE)
	cd WIDGET/gtk/widget0; $(MAKE)
	cd WIDGET/gtk/widget1; $(MAKE)
	cd GEOM/geom/surface; $(MAKE)
	cd GEOM/geom/io; $(MAKE)
	cd GEOM/geom/interface; $(MAKE)
	cd GEOM/geom/surface0; $(MAKE)
	cd GEOM/geom/surfacegl; $(MAKE)
	cd GEOM/geomui/cmd; $(MAKE)
	cd GEOM/geomui/gtk; $(MAKE)
	cd GEOM/geomui/ui; $(MAKE)
	cd GEOM/geomui/interface; $(MAKE)
	cd GEOM/triang; $(MAKE)
	cd GEOM/milieu/kernel; $(MAKE)
	cd GEOM/milieu/cmd; $(MAKE)
	cd GEOM/milieu/gtk; $(MAKE)
	cd GEOM/milieu/opengl; $(MAKE)
	cd GEOM/milieu/ui; $(MAKE)
	cd GEOM/milieu/interface; $(MAKE)
	cd GEOM/motion; $(MAKE)
	cd GEOM/opengl; $(MAKE)
	cd GEOM/imagegl; $(MAKE)
	cd VIEWER/isight/cmd; $(MAKE)
	cd VIEWER/isight/context; $(MAKE)
	cd VIEWER/isight/gtk; $(MAKE)
	cd VIEWER/isight/interface; $(MAKE)
	cd VIEWER/isight/kernel; $(MAKE)
	cd VIEWER/isightui/interface; $(MAKE)
	cd VIEWER/isightui/ui; $(MAKE)
	cd VIEWER/isightui/gtk; $(MAKE)
	cd VIEWER/isightui/cmd; $(MAKE)
	cd LAB/bubbletonlab/cmd; $(MAKE)
	cd LAB/bubbletonlab/gtk; $(MAKE)
	cd LAB/bubbletonlab/kernel; $(MAKE)
	cd LAB/bubbletonlab/ui; $(MAKE)
	cd LAB/bubbletonlab/cmdlab; $(MAKE)
	cd LAB/bubbletonlab/gtklab; $(MAKE)
	cd LAB/mrbubblelab/cmd; $(MAKE)
	cd LAB/mrbubblelab/gtk; $(MAKE)
	cd LAB/mrbubblelab/kernel; $(MAKE)
	cd LAB/mrbubblelab/ui; $(MAKE)
	cd LAB/mrbubblelab/cmdlab; $(MAKE)
	cd LAB/mrbubblelab/gtklab; $(MAKE)
	cd LAB/cmclab/ui; $(MAKE)
	cd LAB/cmclab/cmd; $(MAKE)
	cd LAB/cmclab/gtk; $(MAKE)
	cd LAB/cmclab/kernel; $(MAKE)
	cd LAB/cmclab/cmdlab; $(MAKE)
	cd LAB/cmclab/gtklab; $(MAKE)
	cd LAB/surflab/cmd; $(MAKE)
	cd LAB/surflab/gtk; $(MAKE)
	cd LAB/surflab/kernel; $(MAKE)
	cd LAB/surflab/ui; $(MAKE)
	cd LAB/surflab/cmdlab; $(MAKE)
	cd LAB/surflab/gtklab; $(MAKE)
	cd LAB/minlab/cmd; $(MAKE)
	cd LAB/minlab/gtk; $(MAKE)
	cd LAB/minlab/kernel; $(MAKE)
	cd LAB/minlab/ui; $(MAKE)
	cd LAB/minlab/cmdlab; $(MAKE)
	cd LAB/minlab/gtklab; $(MAKE)
	cd LAB/klab/cmd; $(MAKE)
	cd LAB/klab/gtk; $(MAKE)
	cd LAB/klab/kernel; $(MAKE)
	cd LAB/klab/ui; $(MAKE)
	cd LAB/klab/cmdlab; $(MAKE)
	cd LAB/klab/gtklab; $(MAKE)
	cd LAB/lab/kernel; $(MAKE)
	cd LAB/lab/gtk; $(MAKE)
	cd LAB/lab/ui; $(MAKE)
	cd LAB/lab/cmd; $(MAKE)
	cd LAB/lab/gtklab; $(MAKE)
	cd LAB/lab/cmdlab; $(MAKE)
	cd LAB/loop; $(MAKE)
	cd lib; $(MAKE)
	cd VIEWER/isight/cmdmain; $(MAKE)
	cd VIEWER/isight/gtkmain; $(MAKE)
	cd LAB/bubbletonlab/gtkmain; $(MAKE)
	cd LAB/bubbletonlab/cmdmain; $(MAKE)
	cd LAB/mrbubblelab/gtkmain; $(MAKE)
	cd LAB/mrbubblelab/cmdmain; $(MAKE)
	cd LAB/cmclab/cmdmain; $(MAKE)
	cd LAB/cmclab/gtkmain; $(MAKE)
	cd LAB/surflab/cmdmain; $(MAKE)
	cd LAB/surflab/gtkmain; $(MAKE)
	cd LAB/minlab/gtkmain; $(MAKE)
	cd LAB/minlab/cmdmain; $(MAKE)
	cd LAB/klab/gtkmain; $(MAKE)
	cd LAB/klab/cmdmain; $(MAKE)

install : all
	cp lib/libgang_*.so /usr/local/lib/
	cp -r surfaces/* /usr/local/lib/
	cp scripts/* /usr/local/bin/
	cp VIEWER/isight/cmdmain/isight-cmd VIEWER/isight/gtkmain/isight-gtk LAB/bubbletonlab/gtkmain/bubbletonlab-gtk LAB/bubbletonlab/cmdmain/bubbletonlab-cmd LAB/mrbubblelab/gtkmain/mrbubblelab-gtk LAB/mrbubblelab/cmdmain/mrbubblelab-cmd LAB/cmclab/cmdmain/cmclab-cmd LAB/cmclab/gtkmain/cmclab-gtk LAB/surflab/cmdmain/surflab-cmd LAB/surflab/gtkmain/surflab-gtk LAB/minlab/gtkmain/minlab-gtk LAB/minlab/cmdmain/minlab-cmd LAB/klab/gtkmain/klab-gtk LAB/klab/cmdmain/klab-cmd /usr/local/bin/

depend :
	cd BASE/base; $(MAKE) depend
	cd BASE/math; $(MAKE) depend
	cd BASE/io; $(MAKE) depend
	cd BASE/eval; $(MAKE) depend
	cd BASE/vrml; $(MAKE) depend
	cd BASE/parser; $(MAKE) depend
	cd BASE/image; $(MAKE) depend
	cd BASE/glut; $(MAKE) depend
	cd BASE/thread; $(MAKE) depend
	cd WIDGET/app/ui; $(MAKE) depend
	cd WIDGET/app/cmd; $(MAKE) depend
	cd WIDGET/app/gtk; $(MAKE) depend
	cd WIDGET/app/app; $(MAKE) depend
	cd WIDGET/widget/cmd; $(MAKE) depend
	cd WIDGET/widget/ui; $(MAKE) depend
	cd WIDGET/gtk/widgetc; $(MAKE) depend
	cd WIDGET/gtk/widget0; $(MAKE) depend
	cd WIDGET/gtk/widget1; $(MAKE) depend
	cd GEOM/geom/surface; $(MAKE) depend
	cd GEOM/geom/io; $(MAKE) depend
	cd GEOM/geom/interface; $(MAKE) depend
	cd GEOM/geom/surface0; $(MAKE) depend
	cd GEOM/geom/surfacegl; $(MAKE) depend
	cd GEOM/geomui/cmd; $(MAKE) depend
	cd GEOM/geomui/gtk; $(MAKE) depend
	cd GEOM/geomui/ui; $(MAKE) depend
	cd GEOM/geomui/interface; $(MAKE) depend
	cd GEOM/triang; $(MAKE) depend
	cd GEOM/milieu/kernel; $(MAKE) depend
	cd GEOM/milieu/cmd; $(MAKE) depend
	cd GEOM/milieu/gtk; $(MAKE) depend
	cd GEOM/milieu/opengl; $(MAKE) depend
	cd GEOM/milieu/ui; $(MAKE) depend
	cd GEOM/milieu/interface; $(MAKE) depend
	cd GEOM/motion; $(MAKE) depend
	cd GEOM/opengl; $(MAKE) depend
	cd GEOM/imagegl; $(MAKE) depend
	cd VIEWER/isight/cmd; $(MAKE) depend
	cd VIEWER/isight/context; $(MAKE) depend
	cd VIEWER/isight/gtk; $(MAKE) depend
	cd VIEWER/isight/interface; $(MAKE) depend
	cd VIEWER/isight/kernel; $(MAKE) depend
	cd VIEWER/isightui/interface; $(MAKE) depend
	cd VIEWER/isightui/ui; $(MAKE) depend
	cd VIEWER/isightui/gtk; $(MAKE) depend
	cd VIEWER/isightui/cmd; $(MAKE) depend
	cd LAB/bubbletonlab/cmd; $(MAKE) depend
	cd LAB/bubbletonlab/gtk; $(MAKE) depend
	cd LAB/bubbletonlab/kernel; $(MAKE) depend
	cd LAB/bubbletonlab/ui; $(MAKE) depend
	cd LAB/bubbletonlab/cmdlab; $(MAKE) depend
	cd LAB/bubbletonlab/gtklab; $(MAKE) depend
	cd LAB/mrbubblelab/cmd; $(MAKE) depend
	cd LAB/mrbubblelab/gtk; $(MAKE) depend
	cd LAB/mrbubblelab/kernel; $(MAKE) depend
	cd LAB/mrbubblelab/ui; $(MAKE) depend
	cd LAB/mrbubblelab/cmdlab; $(MAKE) depend
	cd LAB/mrbubblelab/gtklab; $(MAKE) depend
	cd LAB/cmclab/ui; $(MAKE) depend
	cd LAB/cmclab/cmd; $(MAKE) depend
	cd LAB/cmclab/gtk; $(MAKE) depend
	cd LAB/cmclab/kernel; $(MAKE) depend
	cd LAB/cmclab/cmdlab; $(MAKE) depend
	cd LAB/cmclab/gtklab; $(MAKE) depend
	cd LAB/surflab/cmd; $(MAKE) depend
	cd LAB/surflab/gtk; $(MAKE) depend
	cd LAB/surflab/kernel; $(MAKE) depend
	cd LAB/surflab/ui; $(MAKE) depend
	cd LAB/surflab/cmdlab; $(MAKE) depend
	cd LAB/surflab/gtklab; $(MAKE) depend
	cd LAB/minlab/cmd; $(MAKE) depend
	cd LAB/minlab/gtk; $(MAKE) depend
	cd LAB/minlab/kernel; $(MAKE) depend
	cd LAB/minlab/ui; $(MAKE) depend
	cd LAB/minlab/cmdlab; $(MAKE) depend
	cd LAB/minlab/gtklab; $(MAKE) depend
	cd LAB/klab/cmd; $(MAKE) depend
	cd LAB/klab/gtk; $(MAKE) depend
	cd LAB/klab/kernel; $(MAKE) depend
	cd LAB/klab/ui; $(MAKE) depend
	cd LAB/klab/cmdlab; $(MAKE) depend
	cd LAB/klab/gtklab; $(MAKE) depend
	cd LAB/lab/kernel; $(MAKE) depend
	cd LAB/lab/gtk; $(MAKE) depend
	cd LAB/lab/ui; $(MAKE) depend
	cd LAB/lab/cmd; $(MAKE) depend
	cd LAB/lab/gtklab; $(MAKE) depend
	cd LAB/lab/cmdlab; $(MAKE) depend
	cd LAB/loop; $(MAKE) depend
	cd lib; $(MAKE) depend
	cd VIEWER/isight/cmdmain; $(MAKE) depend
	cd VIEWER/isight/gtkmain; $(MAKE) depend
	cd LAB/bubbletonlab/gtkmain; $(MAKE) depend
	cd LAB/bubbletonlab/cmdmain; $(MAKE) depend
	cd LAB/mrbubblelab/gtkmain; $(MAKE) depend
	cd LAB/mrbubblelab/cmdmain; $(MAKE) depend
	cd LAB/cmclab/cmdmain; $(MAKE) depend
	cd LAB/cmclab/gtkmain; $(MAKE) depend
	cd LAB/surflab/cmdmain; $(MAKE) depend
	cd LAB/surflab/gtkmain; $(MAKE) depend
	cd LAB/minlab/gtkmain; $(MAKE) depend
	cd LAB/minlab/cmdmain; $(MAKE) depend
	cd LAB/klab/gtkmain; $(MAKE) depend
	cd LAB/klab/cmdmain; $(MAKE) depend

clean :
	cd BASE/base; $(MAKE) clean
	cd BASE/math; $(MAKE) clean
	cd BASE/io; $(MAKE) clean
	cd BASE/eval; $(MAKE) clean
	cd BASE/vrml; $(MAKE) clean
	cd BASE/parser; $(MAKE) clean
	cd BASE/image; $(MAKE) clean
	cd BASE/glut; $(MAKE) clean
	cd BASE/thread; $(MAKE) clean
	cd WIDGET/app/ui; $(MAKE) clean
	cd WIDGET/app/cmd; $(MAKE) clean
	cd WIDGET/app/gtk; $(MAKE) clean
	cd WIDGET/app/app; $(MAKE) clean
	cd WIDGET/widget/cmd; $(MAKE) clean
	cd WIDGET/widget/ui; $(MAKE) clean
	cd WIDGET/gtk/widgetc; $(MAKE) clean
	cd WIDGET/gtk/widget0; $(MAKE) clean
	cd WIDGET/gtk/widget1; $(MAKE) clean
	cd GEOM/geom/surface; $(MAKE) clean
	cd GEOM/geom/io; $(MAKE) clean
	cd GEOM/geom/interface; $(MAKE) clean
	cd GEOM/geom/surface0; $(MAKE) clean
	cd GEOM/geom/surfacegl; $(MAKE) clean
	cd GEOM/geomui/cmd; $(MAKE) clean
	cd GEOM/geomui/gtk; $(MAKE) clean
	cd GEOM/geomui/ui; $(MAKE) clean
	cd GEOM/geomui/interface; $(MAKE) clean
	cd GEOM/triang; $(MAKE) clean
	cd GEOM/milieu/kernel; $(MAKE) clean
	cd GEOM/milieu/cmd; $(MAKE) clean
	cd GEOM/milieu/gtk; $(MAKE) clean
	cd GEOM/milieu/opengl; $(MAKE) clean
	cd GEOM/milieu/ui; $(MAKE) clean
	cd GEOM/milieu/interface; $(MAKE) clean
	cd GEOM/motion; $(MAKE) clean
	cd GEOM/opengl; $(MAKE) clean
	cd GEOM/imagegl; $(MAKE) clean
	cd VIEWER/isight/cmd; $(MAKE) clean
	cd VIEWER/isight/context; $(MAKE) clean
	cd VIEWER/isight/gtk; $(MAKE) clean
	cd VIEWER/isight/interface; $(MAKE) clean
	cd VIEWER/isight/kernel; $(MAKE) clean
	cd VIEWER/isightui/interface; $(MAKE) clean
	cd VIEWER/isightui/ui; $(MAKE) clean
	cd VIEWER/isightui/gtk; $(MAKE) clean
	cd VIEWER/isightui/cmd; $(MAKE) clean
	cd LAB/bubbletonlab/cmd; $(MAKE) clean
	cd LAB/bubbletonlab/gtk; $(MAKE) clean
	cd LAB/bubbletonlab/kernel; $(MAKE) clean
	cd LAB/bubbletonlab/ui; $(MAKE) clean
	cd LAB/bubbletonlab/cmdlab; $(MAKE) clean
	cd LAB/bubbletonlab/gtklab; $(MAKE) clean
	cd LAB/mrbubblelab/cmd; $(MAKE) clean
	cd LAB/mrbubblelab/gtk; $(MAKE) clean
	cd LAB/mrbubblelab/kernel; $(MAKE) clean
	cd LAB/mrbubblelab/ui; $(MAKE) clean
	cd LAB/mrbubblelab/cmdlab; $(MAKE) clean
	cd LAB/mrbubblelab/gtklab; $(MAKE) clean
	cd LAB/cmclab/ui; $(MAKE) clean
	cd LAB/cmclab/cmd; $(MAKE) clean
	cd LAB/cmclab/gtk; $(MAKE) clean
	cd LAB/cmclab/kernel; $(MAKE) clean
	cd LAB/cmclab/cmdlab; $(MAKE) clean
	cd LAB/cmclab/gtklab; $(MAKE) clean
	cd LAB/surflab/cmd; $(MAKE) clean
	cd LAB/surflab/gtk; $(MAKE) clean
	cd LAB/surflab/kernel; $(MAKE) clean
	cd LAB/surflab/ui; $(MAKE) clean
	cd LAB/surflab/cmdlab; $(MAKE) clean
	cd LAB/surflab/gtklab; $(MAKE) clean
	cd LAB/minlab/cmd; $(MAKE) clean
	cd LAB/minlab/gtk; $(MAKE) clean
	cd LAB/minlab/kernel; $(MAKE) clean
	cd LAB/minlab/ui; $(MAKE) clean
	cd LAB/minlab/cmdlab; $(MAKE) clean
	cd LAB/minlab/gtklab; $(MAKE) clean
	cd LAB/klab/cmd; $(MAKE) clean
	cd LAB/klab/gtk; $(MAKE) clean
	cd LAB/klab/kernel; $(MAKE) clean
	cd LAB/klab/ui; $(MAKE) clean
	cd LAB/klab/cmdlab; $(MAKE) clean
	cd LAB/klab/gtklab; $(MAKE) clean
	cd LAB/lab/kernel; $(MAKE) clean
	cd LAB/lab/gtk; $(MAKE) clean
	cd LAB/lab/ui; $(MAKE) clean
	cd LAB/lab/cmd; $(MAKE) clean
	cd LAB/lab/gtklab; $(MAKE) clean
	cd LAB/lab/cmdlab; $(MAKE) clean
	cd LAB/loop; $(MAKE) clean
	cd lib; $(MAKE) clean
	cd VIEWER/isight/cmdmain; $(MAKE) clean
	cd VIEWER/isight/gtkmain; $(MAKE) clean
	cd LAB/bubbletonlab/gtkmain; $(MAKE) clean
	cd LAB/bubbletonlab/cmdmain; $(MAKE) clean
	cd LAB/mrbubblelab/gtkmain; $(MAKE) clean
	cd LAB/mrbubblelab/cmdmain; $(MAKE) clean
	cd LAB/cmclab/cmdmain; $(MAKE) clean
	cd LAB/cmclab/gtkmain; $(MAKE) clean
	cd LAB/surflab/cmdmain; $(MAKE) clean
	cd LAB/surflab/gtkmain; $(MAKE) clean
	cd LAB/minlab/gtkmain; $(MAKE) clean
	cd LAB/minlab/cmdmain; $(MAKE) clean
	cd LAB/klab/gtkmain; $(MAKE) clean
	cd LAB/klab/cmdmain; $(MAKE) clean

clean-depend :
	cd BASE/base; $(MAKE) clean-depend
	cd BASE/math; $(MAKE) clean-depend
	cd BASE/io; $(MAKE) clean-depend
	cd BASE/eval; $(MAKE) clean-depend
	cd BASE/vrml; $(MAKE) clean-depend
	cd BASE/parser; $(MAKE) clean-depend
	cd BASE/image; $(MAKE) clean-depend
	cd BASE/glut; $(MAKE) clean-depend
	cd BASE/thread; $(MAKE) clean-depend
	cd WIDGET/app/ui; $(MAKE) clean-depend
	cd WIDGET/app/cmd; $(MAKE) clean-depend
	cd WIDGET/app/gtk; $(MAKE) clean-depend
	cd WIDGET/app/app; $(MAKE) clean-depend
	cd WIDGET/widget/cmd; $(MAKE) clean-depend
	cd WIDGET/widget/ui; $(MAKE) clean-depend
	cd WIDGET/gtk/widgetc; $(MAKE) clean-depend
	cd WIDGET/gtk/widget0; $(MAKE) clean-depend
	cd WIDGET/gtk/widget1; $(MAKE) clean-depend
	cd GEOM/geom/surface; $(MAKE) clean-depend
	cd GEOM/geom/io; $(MAKE) clean-depend
	cd GEOM/geom/interface; $(MAKE) clean-depend
	cd GEOM/geom/surface0; $(MAKE) clean-depend
	cd GEOM/geom/surfacegl; $(MAKE) clean-depend
	cd GEOM/geomui/cmd; $(MAKE) clean-depend
	cd GEOM/geomui/gtk; $(MAKE) clean-depend
	cd GEOM/geomui/ui; $(MAKE) clean-depend
	cd GEOM/geomui/interface; $(MAKE) clean-depend
	cd GEOM/triang; $(MAKE) clean-depend
	cd GEOM/milieu/kernel; $(MAKE) clean-depend
	cd GEOM/milieu/cmd; $(MAKE) clean-depend
	cd GEOM/milieu/gtk; $(MAKE) clean-depend
	cd GEOM/milieu/opengl; $(MAKE) clean-depend
	cd GEOM/milieu/ui; $(MAKE) clean-depend
	cd GEOM/milieu/interface; $(MAKE) clean-depend
	cd GEOM/motion; $(MAKE) clean-depend
	cd GEOM/opengl; $(MAKE) clean-depend
	cd GEOM/imagegl; $(MAKE) clean-depend
	cd VIEWER/isight/cmd; $(MAKE) clean-depend
	cd VIEWER/isight/context; $(MAKE) clean-depend
	cd VIEWER/isight/gtk; $(MAKE) clean-depend
	cd VIEWER/isight/interface; $(MAKE) clean-depend
	cd VIEWER/isight/kernel; $(MAKE) clean-depend
	cd VIEWER/isightui/interface; $(MAKE) clean-depend
	cd VIEWER/isightui/ui; $(MAKE) clean-depend
	cd VIEWER/isightui/gtk; $(MAKE) clean-depend
	cd VIEWER/isightui/cmd; $(MAKE) clean-depend
	cd LAB/bubbletonlab/cmd; $(MAKE) clean-depend
	cd LAB/bubbletonlab/gtk; $(MAKE) clean-depend
	cd LAB/bubbletonlab/kernel; $(MAKE) clean-depend
	cd LAB/bubbletonlab/ui; $(MAKE) clean-depend
	cd LAB/bubbletonlab/cmdlab; $(MAKE) clean-depend
	cd LAB/bubbletonlab/gtklab; $(MAKE) clean-depend
	cd LAB/mrbubblelab/cmd; $(MAKE) clean-depend
	cd LAB/mrbubblelab/gtk; $(MAKE) clean-depend
	cd LAB/mrbubblelab/kernel; $(MAKE) clean-depend
	cd LAB/mrbubblelab/ui; $(MAKE) clean-depend
	cd LAB/mrbubblelab/cmdlab; $(MAKE) clean-depend
	cd LAB/mrbubblelab/gtklab; $(MAKE) clean-depend
	cd LAB/cmclab/ui; $(MAKE) clean-depend
	cd LAB/cmclab/cmd; $(MAKE) clean-depend
	cd LAB/cmclab/gtk; $(MAKE) clean-depend
	cd LAB/cmclab/kernel; $(MAKE) clean-depend
	cd LAB/cmclab/cmdlab; $(MAKE) clean-depend
	cd LAB/cmclab/gtklab; $(MAKE) clean-depend
	cd LAB/surflab/cmd; $(MAKE) clean-depend
	cd LAB/surflab/gtk; $(MAKE) clean-depend
	cd LAB/surflab/kernel; $(MAKE) clean-depend
	cd LAB/surflab/ui; $(MAKE) clean-depend
	cd LAB/surflab/cmdlab; $(MAKE) clean-depend
	cd LAB/surflab/gtklab; $(MAKE) clean-depend
	cd LAB/minlab/cmd; $(MAKE) clean-depend
	cd LAB/minlab/gtk; $(MAKE) clean-depend
	cd LAB/minlab/kernel; $(MAKE) clean-depend
	cd LAB/minlab/ui; $(MAKE) clean-depend
	cd LAB/minlab/cmdlab; $(MAKE) clean-depend
	cd LAB/minlab/gtklab; $(MAKE) clean-depend
	cd LAB/klab/cmd; $(MAKE) clean-depend
	cd LAB/klab/gtk; $(MAKE) clean-depend
	cd LAB/klab/kernel; $(MAKE) clean-depend
	cd LAB/klab/ui; $(MAKE) clean-depend
	cd LAB/klab/cmdlab; $(MAKE) clean-depend
	cd LAB/klab/gtklab; $(MAKE) clean-depend
	cd LAB/lab/kernel; $(MAKE) clean-depend
	cd LAB/lab/gtk; $(MAKE) clean-depend
	cd LAB/lab/ui; $(MAKE) clean-depend
	cd LAB/lab/cmd; $(MAKE) clean-depend
	cd LAB/lab/gtklab; $(MAKE) clean-depend
	cd LAB/lab/cmdlab; $(MAKE) clean-depend
	cd LAB/loop; $(MAKE) clean-depend
	cd lib; $(MAKE) clean-depend
	cd VIEWER/isight/cmdmain; $(MAKE) clean-depend
	cd VIEWER/isight/gtkmain; $(MAKE) clean-depend
	cd LAB/bubbletonlab/gtkmain; $(MAKE) clean-depend
	cd LAB/bubbletonlab/cmdmain; $(MAKE) clean-depend
	cd LAB/mrbubblelab/gtkmain; $(MAKE) clean-depend
	cd LAB/mrbubblelab/cmdmain; $(MAKE) clean-depend
	cd LAB/cmclab/cmdmain; $(MAKE) clean-depend
	cd LAB/cmclab/gtkmain; $(MAKE) clean-depend
	cd LAB/surflab/cmdmain; $(MAKE) clean-depend
	cd LAB/surflab/gtkmain; $(MAKE) clean-depend
	cd LAB/minlab/gtkmain; $(MAKE) clean-depend
	cd LAB/minlab/cmdmain; $(MAKE) clean-depend
	cd LAB/klab/gtkmain; $(MAKE) clean-depend
	cd LAB/klab/cmdmain; $(MAKE) clean-depend


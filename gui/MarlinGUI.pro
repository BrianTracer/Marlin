######################################################################
# QMAKE File for MarlinGUI
######################################################################

TEMPLATE = app
CONFIG -= moc
CONFIG += create_prl link_prl
INCLUDEPATH += $(MARLIN)/include $(LCIO)/src/cpp/include
#DEFINES += MARLIN_QT
unix:LIBS += `. $(MARLINWORKDIR)/bin/marlin_libs.sh` -L$(MARLINWORKDIR)/lib -lMarlin
DESTDIR = $(MARLINWORKDIR)/bin/

OBJECTS_DIR = $(MARLINWORKDIR)/tmp/MarlinGUI/obj
                                                                                                                                                             
# Input
HEADERS	=   mainwindow.h \
	    nparamvecset.h \
	    nparamvecsetd.h \
	    aprocdelegate.h \
	    iprocdelegate.h \
	    paramdelegate.h \
	    gparamdelegate.h \
	    icoldelegate.h \
	    icoltdelegate.h \
	    ocoldelegate.h \
	    flowlayout.h \
	    addprocdialog.h \
	    addcondition.h \
	    editcondition.h \
	    guihelp.h \
	    dialog.h
	      
SOURCES =   main.cpp \
	    mainwindow.cpp \
	    nparamvecset.cpp \
	    nparamvecsetd.cpp \
	    aprocdelegate.cpp \
	    iprocdelegate.cpp \
	    paramdelegate.cpp \
	    gparamdelegate.cpp \
	    icoldelegate.cpp \
	    icoltdelegate.cpp \
	    ocoldelegate.cpp \
	    flowlayout.cpp \
	    addprocdialog.cpp \
	    addcondition.cpp \
	    editcondition.cpp \
	    guihelp.cpp \
	    dialog.cpp
#unix:!mac:LIBS+= -lm


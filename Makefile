#############################################################################
# Makefile for building: bymol
# Generated by qmake (2.01a) (Qt 4.8.4) on: Fri Jan 3 06:02:17 2014
# Project:  bymol.pro
# Template: app
# Command: /usr/lib/i386-linux-gnu/qt4/bin/qmake -unix -o Makefile bymol.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_NO_DEBUG -DQT_OPENGL_LIB -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4/QtOpenGL -I/usr/include/qt4 -I. -I/usr/X11R6/include -I.
LINK          = g++
LFLAGS        = -Wl,-O1
LIBS          = $(SUBLIBS)  -L/usr/lib/i386-linux-gnu -L/usr/X11R6/lib -lQtOpenGL -lQtGui -lQtCore -lGL -lGLU -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/lib/i386-linux-gnu/qt4/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = DrawWidget.cpp \
		Main.cpp \
		MainWindow.cpp \
		GLConf.cpp \
		MolConf.cpp \
		MolData.cpp \
		MarchingCube.cpp \
		XYZFile.cpp \
		I_info.cpp \
		VASPFile.cpp \
		CubeFile.cpp moc_MainWindow.cpp \
		qrc_bymol.cpp
OBJECTS       = DrawWidget.o \
		Main.o \
		MainWindow.o \
		GLConf.o \
		MolConf.o \
		MolData.o \
		MarchingCube.o \
		XYZFile.o \
		I_info.o \
		VASPFile.o \
		CubeFile.o \
		moc_MainWindow.o \
		qrc_bymol.o
DIST          = /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/opengl.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		bymol.pro
QMAKE_TARGET  = bymol
DESTDIR       = 
TARGET        = bymol

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: bymol.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/opengl.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/i386-linux-gnu/libQtOpenGL.prl \
		/usr/lib/i386-linux-gnu/libQtGui.prl \
		/usr/lib/i386-linux-gnu/libQtCore.prl
	$(QMAKE) -unix -o Makefile bymol.pro
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/common/gcc-base.conf:
/usr/share/qt4/mkspecs/common/gcc-base-unix.conf:
/usr/share/qt4/mkspecs/common/g++-base.conf:
/usr/share/qt4/mkspecs/common/g++-unix.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/release.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/opengl.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/i386-linux-gnu/libQtOpenGL.prl:
/usr/lib/i386-linux-gnu/libQtGui.prl:
/usr/lib/i386-linux-gnu/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -unix -o Makefile bymol.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/bymol1.0.0 || $(MKDIR) .tmp/bymol1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/bymol1.0.0/ && $(COPY_FILE) --parents DrawWidget.h MainWindow.h GLConf.h MolConf.h MolData.h MarchingCube.h XYZFile.h I_info.h VASPFile.h CubeFile.h .tmp/bymol1.0.0/ && $(COPY_FILE) --parents bymol.qrc .tmp/bymol1.0.0/ && $(COPY_FILE) --parents DrawWidget.cpp Main.cpp MainWindow.cpp GLConf.cpp MolConf.cpp MolData.cpp MarchingCube.cpp XYZFile.cpp I_info.cpp VASPFile.cpp CubeFile.cpp .tmp/bymol1.0.0/ && (cd `dirname .tmp/bymol1.0.0` && $(TAR) bymol1.0.0.tar bymol1.0.0 && $(COMPRESS) bymol1.0.0.tar) && $(MOVE) `dirname .tmp/bymol1.0.0`/bymol1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/bymol1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_MainWindow.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_MainWindow.cpp
moc_MainWindow.cpp: MainWindow.h
	/usr/lib/i386-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) MainWindow.h -o moc_MainWindow.cpp

compiler_rcc_make_all: qrc_bymol.cpp
compiler_rcc_clean:
	-$(DEL_FILE) qrc_bymol.cpp
qrc_bymol.cpp: bymol.qrc \
		rotzp.png \
		molconf.png \
		editcopy.png \
		rotyp.png \
		filesave.png \
		rotxp.png \
		rotzm.png \
		fileopen.png \
		rotym.png \
		icon.png \
		antialias.png \
		glconf.png \
		stick.png \
		smallball.png \
		quality.png \
		rotxm.png \
		zoomout.png \
		zoomin.png \
		bigball.png
	/usr/lib/i386-linux-gnu/qt4/bin/rcc -name bymol bymol.qrc -o qrc_bymol.cpp

compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_rcc_clean 

####### Compile

DrawWidget.o: DrawWidget.cpp DrawWidget.h \
		MolData.h \
		GLConf.h \
		MolConf.h \
		I_info.h \
		CubeFile.h \
		XYZFile.h \
		VASPFile.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o DrawWidget.o DrawWidget.cpp

Main.o: Main.cpp MainWindow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Main.o Main.cpp

MainWindow.o: MainWindow.cpp MainWindow.h \
		DrawWidget.h \
		MolData.h \
		GLConf.h \
		MolConf.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o MainWindow.o MainWindow.cpp

GLConf.o: GLConf.cpp GLConf.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o GLConf.o GLConf.cpp

MolConf.o: MolConf.cpp MolConf.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o MolConf.o MolConf.cpp

MolData.o: MolData.cpp MolConf.h \
		MolData.h \
		GLConf.h \
		MarchingCube.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o MolData.o MolData.cpp

MarchingCube.o: MarchingCube.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o MarchingCube.o MarchingCube.cpp

XYZFile.o: XYZFile.cpp XYZFile.h \
		MolData.h \
		GLConf.h \
		MolConf.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o XYZFile.o XYZFile.cpp

I_info.o: I_info.cpp I_info.h \
		MolData.h \
		GLConf.h \
		MolConf.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o I_info.o I_info.cpp

VASPFile.o: VASPFile.cpp VASPFile.h \
		MolData.h \
		GLConf.h \
		MolConf.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o VASPFile.o VASPFile.cpp

CubeFile.o: CubeFile.cpp CubeFile.h \
		MolData.h \
		GLConf.h \
		MolConf.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o CubeFile.o CubeFile.cpp

moc_MainWindow.o: moc_MainWindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_MainWindow.o moc_MainWindow.cpp

qrc_bymol.o: qrc_bymol.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qrc_bymol.o qrc_bymol.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:


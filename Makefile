#############################################################################
# Makefile for building: project_chen681
# Generated by qmake (2.01a) (Qt 4.8.1) on: Sun May 17 16:20:58 2015
# Project:  project_chen681.pro
# Template: app
# Command: /usr/bin/qmake -o Makefile project_chen681.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_WEBKIT -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -m64 -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -m64 -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++-64 -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I. -Ilib -I.
LINK          = g++
LFLAGS        = -m64 -Wl,-O1
LIBS          = $(SUBLIBS)  -L/usr/lib/x86_64-linux-gnu -lQtGui -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake
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

SOURCES       = loginWindow.cpp \
		main.cpp \
		mainWindow.cpp \
		Movie.cpp \
		Netflix.cpp \
		profileWindow.cpp \
		recommendWindow.cpp \
		resultWindow.cpp \
		signUpWindow.cpp \
		User.cpp \
		lib/md5.cpp moc_loginWindow.cpp \
		moc_mainWindow.cpp \
		moc_profileWindow.cpp \
		moc_recommendWindow.cpp \
		moc_resultWindow.cpp \
		moc_signUpWindow.cpp
OBJECTS       = loginWindow.o \
		main.o \
		mainWindow.o \
		Movie.o \
		Netflix.o \
		profileWindow.o \
		recommendWindow.o \
		resultWindow.o \
		signUpWindow.o \
		User.o \
		md5.o \
		moc_loginWindow.o \
		moc_mainWindow.o \
		moc_profileWindow.o \
		moc_recommendWindow.o \
		moc_resultWindow.o \
		moc_signUpWindow.o
DIST          = /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		project_chen681.pro
QMAKE_TARGET  = project_chen681
DESTDIR       = 
TARGET        = project_chen681

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

Makefile: project_chen681.pro  /usr/share/qt4/mkspecs/linux-g++-64/qmake.conf /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/x86_64-linux-gnu/libQtGui.prl \
		/usr/lib/x86_64-linux-gnu/libQtCore.prl
	$(QMAKE) -o Makefile project_chen681.pro
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/common/gcc-base.conf:
/usr/share/qt4/mkspecs/common/gcc-base-unix.conf:
/usr/share/qt4/mkspecs/common/g++-base.conf:
/usr/share/qt4/mkspecs/common/g++-unix.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/release.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/x86_64-linux-gnu/libQtGui.prl:
/usr/lib/x86_64-linux-gnu/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -o Makefile project_chen681.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/project_chen6811.0.0 || $(MKDIR) .tmp/project_chen6811.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/project_chen6811.0.0/ && $(COPY_FILE) --parents loginWindow.h mainWindow.h Movie.h Netflix.h profileWindow.h recommendWindow.h resultWindow.h signUpWindow.h User.h lib/map.h lib/md5.h lib/mergeSort.h lib/queue.h lib/set.h .tmp/project_chen6811.0.0/ && $(COPY_FILE) --parents loginWindow.cpp main.cpp mainWindow.cpp Movie.cpp Netflix.cpp profileWindow.cpp recommendWindow.cpp resultWindow.cpp signUpWindow.cpp User.cpp lib/md5.cpp .tmp/project_chen6811.0.0/ && (cd `dirname .tmp/project_chen6811.0.0` && $(TAR) project_chen6811.0.0.tar project_chen6811.0.0 && $(COMPRESS) project_chen6811.0.0.tar) && $(MOVE) `dirname .tmp/project_chen6811.0.0`/project_chen6811.0.0.tar.gz . && $(DEL_FILE) -r .tmp/project_chen6811.0.0


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

compiler_moc_header_make_all: moc_loginWindow.cpp moc_mainWindow.cpp moc_profileWindow.cpp moc_recommendWindow.cpp moc_resultWindow.cpp moc_signUpWindow.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_loginWindow.cpp moc_mainWindow.cpp moc_profileWindow.cpp moc_recommendWindow.cpp moc_resultWindow.cpp moc_signUpWindow.cpp
moc_loginWindow.cpp: Netflix.h \
		Movie.h \
		lib/set.h \
		lib/map.h \
		lib/mergeSort.h \
		User.h \
		lib/md5.h \
		mainWindow.h \
		resultWindow.h \
		profileWindow.h \
		signUpWindow.h \
		recommendWindow.h \
		loginWindow.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) loginWindow.h -o moc_loginWindow.cpp

moc_mainWindow.cpp: Netflix.h \
		Movie.h \
		lib/set.h \
		lib/map.h \
		lib/mergeSort.h \
		User.h \
		lib/md5.h \
		resultWindow.h \
		profileWindow.h \
		mainWindow.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) mainWindow.h -o moc_mainWindow.cpp

moc_profileWindow.cpp: Netflix.h \
		Movie.h \
		lib/set.h \
		lib/map.h \
		lib/mergeSort.h \
		User.h \
		lib/md5.h \
		profileWindow.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) profileWindow.h -o moc_profileWindow.cpp

moc_recommendWindow.cpp: Netflix.h \
		Movie.h \
		lib/set.h \
		lib/map.h \
		lib/mergeSort.h \
		User.h \
		lib/md5.h \
		recommendWindow.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) recommendWindow.h -o moc_recommendWindow.cpp

moc_resultWindow.cpp: Netflix.h \
		Movie.h \
		lib/set.h \
		lib/map.h \
		lib/mergeSort.h \
		User.h \
		lib/md5.h \
		resultWindow.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) resultWindow.h -o moc_resultWindow.cpp

moc_signUpWindow.cpp: Netflix.h \
		Movie.h \
		lib/set.h \
		lib/map.h \
		lib/mergeSort.h \
		User.h \
		lib/md5.h \
		signUpWindow.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) signUpWindow.h -o moc_signUpWindow.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
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
compiler_clean: compiler_moc_header_clean 

####### Compile

loginWindow.o: loginWindow.cpp loginWindow.h \
		Netflix.h \
		Movie.h \
		lib/set.h \
		lib/map.h \
		lib/mergeSort.h \
		User.h \
		lib/md5.h \
		mainWindow.h \
		resultWindow.h \
		profileWindow.h \
		signUpWindow.h \
		recommendWindow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o loginWindow.o loginWindow.cpp

main.o: main.cpp Movie.h \
		lib/set.h \
		lib/map.h \
		lib/mergeSort.h \
		User.h \
		lib/queue.h \
		Netflix.h \
		lib/md5.h \
		loginWindow.h \
		mainWindow.h \
		resultWindow.h \
		profileWindow.h \
		signUpWindow.h \
		recommendWindow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

mainWindow.o: mainWindow.cpp mainWindow.h \
		Netflix.h \
		Movie.h \
		lib/set.h \
		lib/map.h \
		lib/mergeSort.h \
		User.h \
		lib/md5.h \
		resultWindow.h \
		profileWindow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mainWindow.o mainWindow.cpp

Movie.o: Movie.cpp Movie.h \
		lib/set.h \
		lib/map.h \
		lib/mergeSort.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Movie.o Movie.cpp

Netflix.o: Netflix.cpp Netflix.h \
		Movie.h \
		lib/set.h \
		lib/map.h \
		lib/mergeSort.h \
		User.h \
		lib/md5.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Netflix.o Netflix.cpp

profileWindow.o: profileWindow.cpp profileWindow.h \
		Netflix.h \
		Movie.h \
		lib/set.h \
		lib/map.h \
		lib/mergeSort.h \
		User.h \
		lib/md5.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o profileWindow.o profileWindow.cpp

recommendWindow.o: recommendWindow.cpp recommendWindow.h \
		Netflix.h \
		Movie.h \
		lib/set.h \
		lib/map.h \
		lib/mergeSort.h \
		User.h \
		lib/md5.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o recommendWindow.o recommendWindow.cpp

resultWindow.o: resultWindow.cpp resultWindow.h \
		Netflix.h \
		Movie.h \
		lib/set.h \
		lib/map.h \
		lib/mergeSort.h \
		User.h \
		lib/md5.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o resultWindow.o resultWindow.cpp

signUpWindow.o: signUpWindow.cpp signUpWindow.h \
		Netflix.h \
		Movie.h \
		lib/set.h \
		lib/map.h \
		lib/mergeSort.h \
		User.h \
		lib/md5.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o signUpWindow.o signUpWindow.cpp

User.o: User.cpp User.h \
		Movie.h \
		lib/set.h \
		lib/map.h \
		lib/mergeSort.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o User.o User.cpp

md5.o: lib/md5.cpp lib/md5.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o md5.o lib/md5.cpp

moc_loginWindow.o: moc_loginWindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_loginWindow.o moc_loginWindow.cpp

moc_mainWindow.o: moc_mainWindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_mainWindow.o moc_mainWindow.cpp

moc_profileWindow.o: moc_profileWindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_profileWindow.o moc_profileWindow.cpp

moc_recommendWindow.o: moc_recommendWindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_recommendWindow.o moc_recommendWindow.cpp

moc_resultWindow.o: moc_resultWindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_resultWindow.o moc_resultWindow.cpp

moc_signUpWindow.o: moc_signUpWindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_signUpWindow.o moc_signUpWindow.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

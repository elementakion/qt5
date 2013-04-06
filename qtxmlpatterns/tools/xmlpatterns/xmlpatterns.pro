TEMPLATE = app
TARGET = xmlpatterns
QT -= gui
QT += xmlpatterns-private

DESTDIR = $$QT.xmlpatterns.bins
target.path = $$[QT_INSTALL_BINS]
INSTALLS += target

# This ensures we get stderr and stdout on Windows.
CONFIG += console

# This ensures that this is a command-line program on OS X and not a GUI application.
CONFIG -= app_bundle

# Note that qcoloroutput.cpp and qcoloringmessagehandler.cpp are also used internally
# in libQtXmlPatterns. See src/xmlpatterns/api/api.pri.
SOURCES = main.cpp                          \
          qapplicationargument.cpp          \
          qapplicationargumentparser.cpp    


HEADERS = main.h                            \
          qapplicationargument.cpp          \
          qapplicationargumentparser.cpp    


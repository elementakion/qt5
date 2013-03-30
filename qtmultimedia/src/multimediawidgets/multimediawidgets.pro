# distinct from QtMultimedia
TARGET = QtMultimediaWidgets
QT = core gui multimedia-private widgets-private
contains(QT_CONFIG, opengl)|contains(QT_CONFIG, opengles2) {
   QT_PRIVATE += opengl
} else {
   DEFINES += QT_NO_OPENGL
}

load(qt_module)

PRIVATE_HEADERS += \
    qvideowidget_p.h \
    qpaintervideosurface_p.h \

PUBLIC_HEADERS += \
    qtmultimediawidgetdefs.h \
    qcameraviewfinder.h \
    qgraphicsvideoitem.h \
    qvideowidgetcontrol.h \
    qvideowidget.h

SOURCES += \
    qcameraviewfinder.cpp \
    qpaintervideosurface.cpp \
    qvideowidgetcontrol.cpp \
    qvideowidget.cpp

mac {
    !simulator {
        PRIVATE_HEADERS += qpaintervideosurface_mac_p.h
        OBJECTIVE_SOURCES += qpaintervideosurface_mac.mm
    }
    LIBS += -framework AppKit -framework QuartzCore -framework QTKit
}

maemo6 {
    contains(QT_CONFIG, opengles2) {
        PRIVATE_HEADERS += qeglimagetexturesurface_p.h
        SOURCES += qeglimagetexturesurface.cpp

        SOURCES += qgraphicsvideoitem_maemo6.cpp

        LIBS += -lX11
    } else {
        SOURCES += qgraphicsvideoitem.cpp
    }
}

!maemo* {
    SOURCES += qgraphicsvideoitem.cpp
}

HEADERS += $$PUBLIC_HEADERS $$PRIVATE_HEADERS


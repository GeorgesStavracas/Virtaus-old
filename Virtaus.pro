TARGET = Virtaus
TEMPLATE = app

QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


SOURCES += main.cpp\
    virtaus-window.cpp \
    collection-view.cpp \
    core/data-reader.cpp \
    core/collection.cpp \
    dialogs/about-dialog.cpp \
    new-collection-wizard.cpp \
    dialogs/preferences-dialog.cpp \
    core/data-writer.cpp \
    basic-info-page.cpp \
    animated-stacked-widget.cpp \
    diagram/diagram-row.cpp \
    diagram/product-view.cpp \
    diagram/diagram-view.cpp

HEADERS  += virtaus-window.h \
    collection-view.h \
    core/data-reader.h \
    core/collection.h \
    dialogs/about-dialog.h \
    new-collection-wizard.h \
    dialogs/preferences-dialog.h \
    core/data-writer.h \
    basic-info-page.h \
    animated-stacked-widget.h \
    diagram/diagram-row.h \
    diagram/product-view.h \
    diagram/diagram-view.h

FORMS    += virtaus-window.ui \
    collection-view.ui \
    dialogs/about-dialog.ui \
    new-collection-wizard.ui \
    dialogs/preferences-dialog.ui \
    basic-info-page.ui \
    diagram/diagram-row.ui \
    diagram/product-view.ui

TRANSLATIONS += \
    languages/virtaus_pt.tr\

RC_FILE = virtaus.rc

RESOURCES += \
    resources.qrc

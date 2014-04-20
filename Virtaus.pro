TARGET = Virtaus
TEMPLATE = app

QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets xml


SOURCES += main.cpp\
    virtaus-window.cpp \
    collection-view.cpp \
    core/data-reader.cpp \
    core/collection.cpp \
    dialogs/about-dialog.cpp \
    dialogs/wizards/new-collection-wizard.cpp \
    dialogs/preferences-dialog.cpp \
    core/data-writer.cpp \
    dialogs/wizards/basic-info-page.cpp \
    widgets/animated-stacked-widget.cpp \
    diagram/diagram-row.cpp \
    diagram/product-view.cpp \
    diagram/diagram-view.cpp \
    virtaus-application.cpp \
    core/settings.cpp \
    collection-info-view.cpp \
    sets-view.cpp \
    collection-data-page.cpp \
    widgets/cover-art-widget.cpp \
    dialogs/wizards/create-collection-page.cpp \
    widgets/cover-art-scene.cpp \
    widgets/cover-art-item.cpp \
    category-view.cpp \
    collection-options-view.cpp

HEADERS  += virtaus-window.h \
    collection-view.h \
    core/data-reader.h \
    core/collection.h \
    dialogs/about-dialog.h \
    dialogs/wizards/new-collection-wizard.h \
    dialogs/preferences-dialog.h \
    core/data-writer.h \
    dialogs/wizards/basic-info-page.h \
    widgets/animated-stacked-widget.h \
    diagram/diagram-row.h \
    diagram/product-view.h \
    diagram/diagram-view.h \
    virtaus-application.h \
    core/settings.h \
    collection-info-view.h \
    sets-view.h \
    collection-data-page.h \
    core/types.h \
    widgets/cover-art-widget.h \
    dialogs/wizards/create-collection-page.h \
    widgets/cover-art-scene.h \
    widgets/cover-art-item.h \
    category-view.h \
    collection-options-view.h

FORMS    += virtaus-window.ui \
    collection-view.ui \
    dialogs/about-dialog.ui \
    dialogs/wizards/new-collection-wizard.ui \
    dialogs/preferences-dialog.ui \
    dialogs/wizards/basic-info-page.ui \
    diagram/diagram-row.ui \
    diagram/product-view.ui \
    collection-info-view.ui \
    sets-view.ui \
    collection-data-page.ui \
    widgets/cover-art-widget.ui \
    dialogs/wizards/create-collection-page.ui \
    category-view.ui \
    collection-options-view.ui

TRANSLATIONS += \
    languages/virtaus_pt.tr\

RC_FILE = virtaus.rc

RESOURCES += \
    resources.qrc

#include "virtaus-window.h"
#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    VirtausWindow *w = new VirtausWindow;
    w->showMaximized();

    return a.exec();
}

#include "virtaus-application.h"

int main(int argc, char *argv[])
{

    VirtausApplication app(argc, argv);

    app.showGUI();

    return app.exec();
}

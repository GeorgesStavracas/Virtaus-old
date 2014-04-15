#include "virtaus-application.h"

int main(int argc, char *argv[])
{



    VirtausApplication* app;

    app = VirtausApplication::getInstance(argc, argv);

    app->showGUI();

    return app->exec();
}

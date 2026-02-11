#include "PhotoEditorQT.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    PhotoEditorQT window;
    window.show();
    return app.exec();
}

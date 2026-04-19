#include "PhotoEditorQT.h"
#include <QtWidgets/QApplication>
#include <QSharedMemory>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    QSharedMemory sharedMemory("acidhood999_PhotoEditorQT_UniqueKey");

    if (sharedMemory.attach())
    {
        QMessageBox::warning(nullptr, "Warning", "The application is already launched!");
        return 0;
    }

    if (!sharedMemory.create(1)) return 0;

    PhotoEditorQT window;
    window.show();
    return app.exec();
}

#include <QtGui>
#include <QFile>
#include "TextWindow.h"

int main(int argc, char ** argv)
{
    QApplication app(argc, argv);

    TextWindow window;
    window.resize(600, 400);

    QRect rect = QApplication::desktop()->availableGeometry();
    window.move(rect.center() - window.rect().center());
    window.show();
    return app.exec();
}

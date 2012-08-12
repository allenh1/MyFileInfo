#include <QtGui>
#include <QFile>
#include "MainWindow.h"

int main(int argc, char ** argv)
{
    QApplication app(argc, argv);
    MainWindow w(argc,argv);
    w.show();
    app.connect(&app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()));
    //for(;;)
    //	;
    //system("pause");
    return app.exec();
}

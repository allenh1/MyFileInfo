#ifndef TEXTWINDOW_H
#define TEXTWINDOW_H
#include <QtGui>
#include <QtWidgets>
#include "File.h"
#include <QList>
#include <QIcon>

class TextWindow : public QMainWindow
{
    Q_OBJECT

public:
    TextWindow();

private:

    ///Q_SLOTS GO HERE
    Q_SLOT void open(); //signal = Q_SIGNAL; emit = Q_EMIT; foreach= Q_FOREACH   USE Q MACROS!
    Q_SLOT void save();
    Q_SLOT void quit();
    Q_SLOT void getSize();
    Q_SLOT void getDirectory();
    Q_SLOT QString getList();

    QTextEdit *textEdit;

    QAction *openAction;
    QAction *saveAction;
    QAction *openDirectoryAction;
    QAction *exitAction;
    QIcon *myIcon;

    void sortFiles();
    void getFiles(QString dirName);
    void addFile(FileInfo file);

    double totalSize;

    QMenu *fileMenu;

    QString currentFile;
    QList<FileInfo> fileList;
};

#endif // TEXTWINDOW_H

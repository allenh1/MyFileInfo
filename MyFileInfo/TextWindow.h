#ifndef TEXTWINDOW_H
#define TEXTWINDOW_H
#include <QtGui>
#include "File.h"
#include <QList>

class TextWindow : public QMainWindow
{
    Q_OBJECT

public:
    TextWindow();

private slots:
    void open();
    void save();
    void quit();
    void getSize();
    void getDirectory();
    QString getList();

private:
    QTextEdit *textEdit;

    QAction *openAction;
    QAction *saveAction;
    QAction *openDirectoryAction;
    QAction *exitAction;
    void sortFiles();
    void getFiles(QString dirName);

    double totalSize;

    QMenu *fileMenu;

    QString currentFile;
    QList<FileInfo> fileList;
};

#endif // TEXTWINDOW_H

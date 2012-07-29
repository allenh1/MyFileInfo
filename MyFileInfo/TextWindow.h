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
    QString getList();

private:
    QTextEdit *textEdit;

    QAction *openAction;
    QAction *saveAction;
    QAction *exitAction;
    void sortFiles();

    int totalSize;

    QMenu *fileMenu;

    QString currentFile;
    QList<FileInfo> fileList;
};

#endif // TEXTWINDOW_H

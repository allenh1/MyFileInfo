#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtWidgets>
#include <QTimer>
#include <QtAlgorithms>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include "ui_MainWindow.h"
#include "File.h"

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(int argc, char** argv, QWidget *parent = 0);

private:
    ///Q_SLOTS GO HERE
    Q_SLOT void open(); //signal = Q_SIGNAL; emit = Q_EMIT; foreach= Q_FOREACH   USE Q MACROS!
    Q_SLOT void save();
    Q_SLOT void quit();
    Q_SLOT void getSize();
    Q_SLOT void getDirectory();
    Q_SLOT QString getList();

    QAction *openAction;
    QAction *saveAction;
    QAction *openDirectoryAction;
    QAction *exitAction;
    QIcon *myIcon;

    void sortFiles();
    void getFiles(QString dirName);
    void addFile(FileInfo file);
    void setLabels();

    double totalSize;

    QString currentFile;
    QList<FileInfo> fileList;

    Ui::MainWindow ui;
};

#endif // MAINWINDOW_H

// Copyright 2020 Hunter L. Allen
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.


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
#include <MyFileInfo/File.h>

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(int argc, char** argv, QWidget *parent = 0);
  ~MainWindow() override = default;

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

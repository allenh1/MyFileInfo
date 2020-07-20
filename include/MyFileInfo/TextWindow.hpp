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


#ifndef TEXTWINDOW_HPP
#define TEXTWINDOW_HPP

#include <MyFileInfo/File.hpp>

#include <QtGui>
#include <QtWidgets>
#include <QList>
#include <QIcon>

class TextWindow: public QMainWindow
{
  Q_OBJECT

public:
  TextWindow();

private:
  ///Q_SLOTS GO HERE
  Q_SLOT void open();   //signal = Q_SIGNAL; emit = Q_EMIT; foreach= Q_FOREACH   USE Q MACROS!
  Q_SLOT void save();
  Q_SLOT void quit();
  Q_SLOT void getSize();
  Q_SLOT void getDirectory();
  Q_SLOT QString getList();

  QTextEdit * textEdit;

  QAction * openAction;
  QAction * saveAction;
  QAction * openDirectoryAction;
  QAction * exitAction;
  QIcon * myIcon;

  void sortFiles();
  void getFiles(QString dirName);
  void addFile(FileInfo file);

  double totalSize;

  QMenu * fileMenu;

  QString currentFile;
  QList < FileInfo > fileList;
};

#endif // TEXTWINDOW_H

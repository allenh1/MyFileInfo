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


#include <MyFileInfo/TextWindow.hpp>

TextWindow::TextWindow()
{
  openAction = new QAction(tr("&Open"), this);
  openDirectoryAction = new QAction(tr("&Open Folder"), this);
  saveAction = new QAction(tr("&Save"), this);
  exitAction = new QAction(tr("E&xit"), this);

  connect(openAction, SIGNAL(triggered()), this, SLOT(getSize()));
  connect(openDirectoryAction, SIGNAL(triggered()), this, SLOT(getDirectory()));
  connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));
  connect(exitAction, SIGNAL(triggered()), this, SLOT(quit()));

  fileMenu = menuBar()->addMenu(tr("&File"));
  fileMenu->addAction(openAction);
  fileMenu->addAction(openDirectoryAction);
  fileMenu->addAction(saveAction);
  fileMenu->addSeparator();
  fileMenu->addAction(exitAction);

  setWindowIcon(QIcon(":/images/icon.xpm"));

  textEdit = new QTextEdit;
  setCentralWidget(textEdit);

  setWindowTitle(tr("MyFileInfo"));
}

void TextWindow::quit()
{
  QMessageBox messageBox;
  messageBox.setWindowTitle(tr("Exit"));
  messageBox.setText(tr("Do you really want to quit?"));
  messageBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
  messageBox.setDefaultButton(QMessageBox::No);

  if (messageBox.exec() == QMessageBox::Yes) {
    qApp->quit();
  }
}//end void

void TextWindow::open()
{
  QString fileName =
    QFileDialog::getOpenFileName(
    this, tr("Open File"), "", tr(
      "Text Files (*.txt);; C++ Files (*.cpp *.h *.cc)"));
  currentFile = fileName;

  if (fileName != "") {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
      QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
      return;
    }    //end if

    QTextStream in( & file);
    textEdit->setText(in.readAll());
    file.close();
  }  //end if
}//open file dialog

void TextWindow::save()
{
  QString fileName =
    QFileDialog::getSaveFileName(
    this, tr("Save File"), "", tr(
      "Text Files (*.txt);;C++ Files (*.cpp *.h *.cc)"));

  if (fileName != "") {
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
      QMessageBox::critical(this, tr("Error"), tr("Could not save file"));
      return;
    }    //end if
    else {
      QTextStream stream( & file);
      stream << textEdit->toPlainText();
      stream.flush();
      file.close();
    }    //end else
  }  //end if
}//void for saving the file

QString TextWindow::getList()
{
  sortFiles();
  QString output;
  QString FileSize;

  for (int x = 0; x < fileList.size(); x++) {
    QString theString = fileList.at(x).getString;

    output += theString;
    output += "\n";
  }  //add all files in the list.

  int divisions = 0;

  while (totalSize > 1024)
  {totalSize /= 1024.0; divisions++;}

  FileSize.setNum(totalSize);

  if (divisions == 0) {
    FileSize += " Bytes";
  } else if (divisions == 1) {
    FileSize += " KB";
  } else if (divisions == 2) {
    FileSize += " MB";
  } else if (divisions == 3) {
    FileSize += " GB";
  } else if (divisions == 4) {
    FileSize += " TB";
  }

  QString numberOfFiles;
  numberOfFiles.setNum(fileList.size());

  output += "\nNumber of Files: ";
  output += numberOfFiles;
  output += "\nTotal: ";
  output += FileSize;
  return output;
}//returns a string for file output.

void TextWindow::sortFiles()
{
  QList < FileInfo > sortedList;
  double total = 0;

  while (fileList.size() > 0) {
    int max = 0; int maxIndex = 0;

    for (int x = 0; x < fileList.size(); x++) {
      int xSize = fileList.at(x).getSize;
      if (xSize > max)
      {max = fileList.at(x).getSize; maxIndex = x;}
    }    //end for x.

    sortedList.push_back(fileList.at(maxIndex));
    fileList.removeAt(maxIndex);
  }  //void sorts the file list.

  fileList.clear();

  for (int z = 1; z < sortedList.size(); z++) {
    FileInfo toCompare = sortedList.at(z - 1);
    FileInfo toCompareTo = sortedList.at(z);

    if (toCompareTo.compareTo(toCompare))
    {sortedList.removeAt(z); z--;}
  }  //remove duplicates.

  for (int y = 0; y < sortedList.size(); y++) {
    fileList.push_back(sortedList.at(y));
    total += sortedList.at(y).getSize;
  }  //end for x.

  totalSize = total;
}//sort the files by size.

void TextWindow::addFile(FileInfo file)
{
  bool madeInsert = false;

  for (int x = 0; x < fileList.size(); x++) {
    int xSize = fileList.at(x).getSize;
    if (xSize > file.getSize) {
      fileList.insert(x, file);
      madeInsert = true;
      break;
    }    //end if
  }  //end for x.

  if (!madeInsert) {
    fileList.push_back(file);
  }
}//add a file to the sorted list

void TextWindow::getFiles(QString dirName)
{
  QDir currentDir(dirName);
  QStringList list = currentDir.entryList(QDir::Files);
  QStringList list2 = currentDir.entryList(QDir::NoDotAndDotDot);

  for (int y = 0; y < list2.size(); y++) {
    QString fileName;
    if (dirName != "/") {
      fileName = dirName + "/" + list2.at(y);
    } else {
      fileName = "/" + list2.at(y);
    }
    getFiles(fileName);
  }  //recursive call to getFiles.

  for (int x = 0; x < list.size(); x++) {
    QString fileName = dirName + "/" + list.at(x);
    QFile file(fileName);

    int int_size = file.size();
    QString FileName = fileName;
    FileInfo toPush(FileName, int_size);
    addFile(toPush);
    file.close();
  }  //end for x.
}//add all files from a directory to the list.

void TextWindow::getDirectory()
{
  QString dirName = QFileDialog::getExistingDirectory(this, tr("Open Dir"));
  QString output;
  QDir myDir(dirName);
  QStringList list = myDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);

  getFiles(dirName);

  for (int x = 0; x < list.size(); x++) {
    QString fileName;
    if (dirName != "/") {
      fileName = dirName + "/" + list.at(x);
    } else {
      fileName = "/" + list.at(x);
    }
    getFiles(fileName);
  }  //end for x.

  output = getList();
  textEdit->setText(output);
}//add an entire directory.

void TextWindow::getSize()
{
  QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("All Files (*)"));
  currentFile = fileName;

  if (fileName != "") {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
      QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
      return;
    }    //end if
    int int_size = file.size();
    QString FileName = fileName;
    FileInfo toPush(FileName, int_size);

    fileList.push_back(toPush);
    QString output;
    output = getList();

    textEdit->setText(output);
    file.close();
  }  //end if
}//open file dialog

#include "MainWindow.h"
MainWindow::MainWindow(int argc, char **argv, QWidget *parent)
{
    ui.setupUi(this);

    connect(ui.actionOpen_File, SIGNAL(triggered()), this, SLOT(getSize()));
    connect(ui.actionOpen_Folder, SIGNAL(triggered()), this, SLOT(getDirectory()));
    connect(ui.actionSave_List, SIGNAL(triggered()), this, SLOT(save()));
    connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(quit()));
}

void MainWindow::quit()
{
    QMessageBox messageBox;
    messageBox.setWindowTitle(tr("Exit"));
    messageBox.setText(tr("Do you really want to quit?"));
    messageBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    messageBox.setDefaultButton(QMessageBox::No);

    if (messageBox.exec() == QMessageBox::Yes)
        qApp->quit();
}//end void

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Text Files (*.txt);; C++ Files (*.cpp *.h *.cc)"));
    currentFile = fileName;

    if (fileName != "")
    {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return;
        }//end if


        //QTextStream in(&file);
        //textEdit->setText(in.readAll());
        file.close();
    }//end if
}//open file dialog

void MainWindow::save()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("Text Files (*.txt);;C++ Files (*.cpp *.h *.cc)"));

    if (fileName != "")
    {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly))
        {
            QMessageBox::critical(this, tr("Error"), tr("Could not save file"));
            return;
        }//end if

        else
        {
            QTextStream stream(&file);
            stream << getList();
            stream.flush();
            file.close();
        }//end else
    }//end if
}//void for saving the file

QString MainWindow::getList()
{
    sortFiles();
    QString output;
    QString FileSize;

    for (int x = 0; x < fileList.size(); x++)
    {
        QString theString = fileList.at(x).getString;

        output += theString;
        output += "\n";
    }//add all files in the list.

    int divisions = 0;

    while (totalSize > 1024)
    { totalSize /= 1024.0; divisions++; }

    FileSize.setNum(totalSize);

    if (divisions == 0)
        FileSize += " Bytes";
    else if (divisions == 1)
        FileSize += " KB";
    else if (divisions == 2)
        FileSize += " MB";
    else if (divisions == 3)
        FileSize += " GB";
    else if (divisions == 4)
        FileSize += " TB";

    QString numberOfFiles;
    numberOfFiles.setNum(fileList.size());

    output += "\nNumber of Files: ";
    output += numberOfFiles;
    output += "\nTotal: ";
    output += FileSize;
    return output;
}//returns a string for file output.

void MainWindow::setLabels()
{
    QString FileSize;
    QString numberOfFiles;

    numberOfFiles.setNum(fileList.size() - 1);

    int divisions = 0;

    while (totalSize > 1024)
    { totalSize /= 1024.0; divisions++; }

    FileSize.setNum(totalSize);

    if (divisions == 0)
        FileSize += " Bytes";
    else if (divisions == 1)
        FileSize += " KB";
    else if (divisions == 2)
        FileSize += " MB";
    else if (divisions == 3)
        FileSize += " GB";
    else if (divisions == 4)
        FileSize += " TB";

    ui.FileCount->setText(numberOfFiles);
    ui.TotalSize->setText(FileSize);
}

void MainWindow::sortFiles()
{
    QList<FileInfo> sortedList;
    double total = 0;

    while (fileList.size() > 0)
    {
        int max = 0; int maxIndex = 0;

        for (int x = 0; x < fileList.size(); x++)
        {
            int xSize = fileList.at(x).getSize;
            if (xSize > max)
            { max = fileList.at(x).getSize; maxIndex = x; }
        }//end for x.

        sortedList.push_back(fileList.at(maxIndex));
        fileList.removeAt(maxIndex);
    }//void sorts the file list.

    fileList.clear();

    for (int z = 1; z < sortedList.size(); z++)
    {
        FileInfo toCompare = sortedList.at(z - 1);
        FileInfo toCompareTo = sortedList.at(z);

        if (toCompareTo.compareTo(toCompare))
        { sortedList.removeAt(z); z--; }
    }//remove duplicates.

    for (int y = 0; y < sortedList.size(); y++)
    {
        fileList.push_back(sortedList.at(y));
        total += sortedList.at(y).getSize;
    }//end for x.

    totalSize = total;
}//sort the files by size.

void MainWindow::addFile(FileInfo file)
{
    bool madeInsert = false;

    for (int x = 0; x < fileList.size(); x++)
    {
        int xSize = fileList.at(x).getSize;
        if (xSize > file.getSize)
        {
            fileList.insert(x, file);
            madeInsert = true;
            break;
        }//end if
    }//end for x.

    if (!madeInsert)
        fileList.push_back(file);
}//add a file to the sorted list

void MainWindow::getFiles(QString dirName)
{
    QDir currentDir(dirName);
    QStringList list = currentDir.entryList(QDir::Files);
    QStringList list2 = currentDir.entryList(QDir::NoDotAndDotDot);

    for (int y = 0; y < list2.size(); y++)
    {
        QString fileName;
        if (dirName != "/")
            fileName = dirName + "/" + list2.at(y);
        else
            fileName = "/" + list2.at(y);
        getFiles(fileName);
    }//recursive call to getFiles.

    for (int x = 0; x < list.size(); x++)
    {
        QString fileName = dirName + "/" + list.at(x);
        QFile file(fileName);

        int int_size = file.size();
        QString FileName = fileName;
        FileInfo toPush(FileName, int_size);
        addFile(toPush);
        file.close();
    }//end for x.
}//add all files from a directory to the list.

void MainWindow::getDirectory()
{
    QString dirName = QFileDialog::getExistingDirectory(this, tr("Open Dir"));
    QDir myDir(dirName);
    QStringList list = myDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);

    getFiles(dirName);

    for (int x = 0; x < list.size(); x++)
    {
        QString fileName;
        if (dirName != "/")
            fileName = dirName + "/" + list.at(x);
        else
            fileName = "/" + list.at(x);
        getFiles(fileName);
    }//end for x.

    //output = getList();
    //textEdit->setText(output);
    sortFiles(); //sort before display
    ui.FileList->clear();

    for (int x = 0; x < fileList.size(); x++)
    {
        QString current;
        current = fileList.at(x).getString;
        ui.FileList->addItem(current);
    }//end for x.
    setLabels();
}//add an entire directory.

void MainWindow::getSize()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("All Files (*)"));
    currentFile = fileName;

    if (fileName != "")
    {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return;
        }//end if
        int int_size = file.size();
        QString FileName = fileName;
        FileInfo toPush(FileName, int_size);

        fileList.push_back(toPush);
        QString output;
        output = getList();

        sortFiles(); //sort before display
        ui.FileList->clear();

        for (int x = 0; x < fileList.size(); x++)
        {
            QString current;
            current = fileList.at(x).getString;
            ui.FileList->addItem(current);
        }//end for x.
        file.close();
    }//end if
}//open file dialog


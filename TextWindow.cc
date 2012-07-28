#include "TextWindow.h"

TextWindow::TextWindow()
{
    openAction = new QAction(tr("&Open"), this);
    saveAction = new QAction(tr("&Save"), this);
    exitAction = new QAction(tr("E&xit"), this);

    connect(openAction, SIGNAL(triggered()), this, SLOT(getSize()));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));
    connect(exitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    textEdit = new QTextEdit;
    setCentralWidget(textEdit);

    setWindowTitle(tr("Notepad"));
}

void TextWindow::quit()
{
    QMessageBox messageBox;
    messageBox.setWindowTitle(tr("Notepad"));
    messageBox.setText(tr("Do you really want to quit?"));
    messageBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    messageBox.setDefaultButton(QMessageBox::No);

    if (messageBox.exec() == QMessageBox::Yes)
        qApp->quit();
}//end void

void TextWindow::open()
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

        QTextStream in(&file);
        textEdit->setText(in.readAll());
        file.close();
    }//end if
}//open file dialog

void TextWindow::save()
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
            stream << textEdit->toPlainText();
            stream.flush();
            file.close();
        }//end else
    }//end if
}//void for saving the file

void TextWindow::getSize()
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

        QString stream;
        stream = textEdit->toPlainText();
        QString FileInfo;
        QString FileSize;
        double file_size = file.size(); //raw size in bytes
        int divisions = 0;

        while (file_size > 1024)
        { file_size /= 1024.0; divisions++; }

        FileSize.setNum(file_size);

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

        if (stream.size() > 1)
            FileInfo = stream + "\n" + fileName + ": " + FileSize;
        else
            FileInfo = stream + fileName + ": " + FileSize;

        textEdit->setText(FileInfo);
        file.close();
    }//end if
}//open file dialog

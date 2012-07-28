#ifndef TEXTWINDOW_H
#define TEXTWINDOW_H
#include <QtGui>

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

private:
    QTextEdit *textEdit;

    QAction *openAction;
    QAction *saveAction;
    QAction *exitAction;

    QMenu *fileMenu;

    QString currentFile;
};

#endif // TEXTWINDOW_H

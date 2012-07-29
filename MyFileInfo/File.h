#ifndef FILEINFO_H
#define FILEINFO_H

#include <QString>
#include <QList>
#include <QFile>
#include <string.h>

class FileInfo
{
public:
    FileInfo(QString name, int _size);

    void toString();
    QString getString;
private:
    int size;
    QString filename;
};
#endif

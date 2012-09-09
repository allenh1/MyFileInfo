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

    bool compareTo(FileInfo other);

    QString getString;
    int getSize;

    bool operator < (const FileInfo& f2) const
    {
        FileInfo other = f2;
        return size < other.getSize;
    }//less than operator

    bool operator > (const FileInfo& f2) const
    {
        FileInfo other = f2;
        return size > other.getSize;
    }//greater than operator

    bool operator == (const FileInfo& f2) const
    {
        FileInfo other = f2;
        return size == other.getSize;
    }

private:
    int size;
    QString filename;
};
#endif

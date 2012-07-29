#include "File.h"

FileInfo::FileInfo(QString name, int _size)
{
    filename = name;
    size = _size;
    toString();

    getSize = size;
}//construct a file object

void FileInfo::toString()
{
    QString FileSize;
    double file_size = size; //raw size in bytes
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

    QString toReturn;
    toReturn = filename + ": " + FileSize;

    getString = toReturn;
}//returns the file as a string

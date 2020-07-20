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

  bool operator < (const FileInfo & f2) const
  {
    FileInfo other = f2;
    return size < other.getSize;
  }  //less than operator

  bool operator > (const FileInfo & f2) const
  {
    FileInfo other = f2;
    return size > other.getSize;
  }  //greater than operator

  bool operator == (const FileInfo & f2) const
  {
    FileInfo other = f2;
    return size == other.getSize;
  }

private:
  int size;
  QString filename;
};
#endif

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


#include <MyFileInfo/File.hpp>

FileInfo::FileInfo(QString name, int _size)
{
  filename = name;
  size = _size;
  toString();

  getSize = size;
}//construct a file object

bool FileInfo::compareTo(FileInfo other)
{return other.size == this->size && other.filename == this->filename;}

void FileInfo::toString()
{
  QString FileSize;
  double file_size = size;   //raw size in bytes
  int divisions = 0;

  while (file_size > 1024)
  {file_size /= 1024.0; divisions++;}

  FileSize.setNum(file_size);

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

  QString toReturn;
  toReturn = filename + ": " + FileSize;

  getString = toReturn;
}//returns the file as a string

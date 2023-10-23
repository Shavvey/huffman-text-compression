#pragma once
#include "file-handler.hpp"
#include <cstdint>
#include <fstream>

// uses a file path to append the size nad stringMinHeap
// filePath: the file name and directory specified to create compressed file
void FileRoutine::writeFile(std::string filePath, char *stringMinHeap,
                            int size) {
  std::fstream file;
  // open file using fstream in binary and append mode
  file.open(filePath, std::ios::binary | std::ios::app);
  // cast to char and write to file
  file.write(reinterpret_cast<char *>(size), sizeof(size));
  // write the serialMinHeap string to the file
  file.write(stringMinHeap, sizeof(stringMinHeap));
}
// after writing the stringMinHeap and size, write characters
// encodings, for this we need the frequnecy data and found characters
// to construct a minheap that can give us encodings
// byte will be used by write file to append to end of file
std::byte FileRoutine::getEncoding(hff::HuffmanTree huffTree) {}

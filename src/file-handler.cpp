#pragma once
#include "file-handler.hpp"
#include <cstdint>
#include <fstream>

// uses a file path to append the size nad stringMinHeap
// filePath: the file name and directory specified to create compressed file
void FileRoutine::writeFile(std::string filePath, std::string heapString) {
  // using basic file stream provided by cpp standard library
  std::ofstream file;
  // open file using fstream in binary and append mode
  file.open(filePath, std::ios::binary | std::ios::out);
  hff::SerializedMinHeap serialMinHeap = hff::serializeFromString(heapString);
  // cast to c-like string and write to the file based on size of string
  file.write((char *)&serialMinHeap, serialMinHeap.size);
  file.close();
}
// after writing the stringMinHeap and size, write characters
// encodings, for this we need the frequnecy data and found characters
// to construct a minheap that can give us encodings
// byte will be used by write file to append to end of file
std::byte FileRoutine::getEncoding(hff::HuffmanTree huffTree) {}

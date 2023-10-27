#pragma once
#include "file-handler.hpp"
#include <cstdint>
#include <fstream>

// uses a file path to append the size and stringMinHeap
// filePath: the file name and directory specified to create compressed file
void FileRoutine::writeFile(std::string filePath, std::string heapString) {
  // using basic file stream provided by cpp standard library
  std::ofstream file;
  // open file using fstream in binary mode
  file.open(filePath, std::ios::binary | std::ios::out);
  // create a serialized minHeap from the created heap string
  hff::SerializedMinHeap serialMinHeap = hff::serializeFromString(heapString);
  file.write((char *)&serialMinHeap.data, serialMinHeap.size);
  file.close();
}
// after writing the stringMinHeap and size, write characters
// encodings, for this we need the frequnecy data and found characters
// to construct a minheap that can give us encodings
// byte will be used by write file to append to end of file
std::byte FileRoutine::getEncoding(hff::HuffmanTree huffTree) {}

// I want to be able to recover minHeap from the binary written inside the file
// using this function
void FileRoutine::printDecodedMinHeap(std::string filePath,
                                      hff::SerializedMinHeap serialMinHeap) {
  std::ifstream file;
  file.open(filePath, std::ios::binary | std::ios::in);
  char c;
  int index = 0;

  printf("Heap size %d\n", serialMinHeap.size);
  while (index < serialMinHeap.size) {
    file.get(c);
    for (int i = 0; i < 8; i++) {
      std::cout << ((c >> i) & 1);
    }
    std::cout << '\t';
    index++;
  }
}

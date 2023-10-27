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
  file.write((char *)serialMinHeap.data.data(), serialMinHeap.size);
  file.close();
}
// after writing the stringMinHeap and size, write characters
// encodings, for this we need the frequnecy data and found characters
// to construct a minheap that can give us encodings
// byte will be used by write file to append to end of file
std::byte FileRoutine::getEncoding(hff::HuffmanTree huffTree) {}

// I want to be able to recover minHeap from the binary written inside the file
// using this function
void FileRoutine::printDecodedMinHeap(std::string filePath) {
  std::ifstream file;
  file.open(filePath, std::ios::binary | std::ios::in);
  char c;
  int index = 0;
  std::string heapString;
  file.get(c);
  // find the null terminator of the string again
  while (c != '\0') {
    std::bitset<8> b((unsigned char)c);
    std::cout << b;
    std::cout << '\t' << (char)b.to_ulong();
    std::cout << std::endl;
    heapString.push_back((char)b.to_ulong());
    index++;
    file.get(c);
  }
  std::cout << "Recovered string: " + heapString << std::endl;
}
const std::string FileRoutine::getSerialMinHeap(std::string filePath) {
  std::ifstream file;
  file.open(filePath, std::ios::binary | std::ios::in);
  char c;
  int index = 0;
  std::string heapString;
  file.get(c);
  // find the null terminator of the string again
  while (c != '\0') {
    std::bitset<8> b((unsigned char)c);
    std::cout << b;
    heapString.push_back((char)b.to_ulong());
    index++;
    file.get(c);
  }
  return heapString;
}

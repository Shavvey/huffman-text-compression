#pragma once
#include "file-handler.hpp"
#include <cstdint>
#include <fstream>

// uses a file path to append the size nad stringMinHeap
// filePath: the file name and directory specified to create compressed file
// NOTE: this isnt working you need to use something simpler for this jesus
// christ
void FileRoutine::writeFile(std::string filePath, std::string heapString) {
  // using basic file stream provided by cpp standard library
  std::ofstream file;
  // open file using fstream in binary mode
  file.open(filePath, std::ios::binary | std::ios::out);
  hff::SerializedMinHeap serialMinHeap = hff::serializeFromString(heapString);
  // cast to c-like string and write to the file based on size of string
  std::vector<std::byte> bytes;
  bytes.reserve(std::size(heapString));
  // lambda expression to convert heapstring to bytes
  std::transform(std::begin(heapString), std::end(heapString),
                 std::back_inserter(bytes),
                 [](char c) { return std::byte(c); });
  file.write((char *)&bytes, serialMinHeap.size);
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
                                      hff::SerializedMinHeap serialMinHeap) {}

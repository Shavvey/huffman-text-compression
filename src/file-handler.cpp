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
std::byte FileRoutine::getEncoding(hff::HuffmanTree huffTree, char c) {
  unsigned char data = huffTree.huffmanEncode(c);
  return (std::byte)data;
}

// I want to be able to recover minHeap from the binary written inside the file
// using this function
void FileRoutine::printDecodedMinHeap(std::string filePath) {
  std::ifstream file;
  file.open(filePath, std::ios::binary | std::ios::in);
  char c;
  std::string heapString;
  file.get(c);
  // find the null terminator of the string again
  while (c != '\0') {
    std::bitset<8> b((unsigned char)c);
    std::cout << b;
    std::cout << '\t' << (char)b.to_ulong();
    std::cout << std::endl;
    heapString.push_back((char)b.to_ulong());
    file.get(c);
  }
  std::cout << "Recovered string: " + heapString << std::endl;
}
const std::string FileRoutine::getSerialMinHeap(std::string filePath) {
  std::ifstream file;
  file.open(filePath, std::ios::binary | std::ios::in);
  char c;
  std::string heapString;
  file.get(c);
  // read the file until the null terminator is reached
  // this should be the end of the heapstring
  while (c != '\0') {
    // extract the byte from teh file
    std::bitset<8> b((unsigned char)c);
    std::cout << b;
    // build heapstring back up from each byte read from file
    heapString.push_back((char)b.to_ulong());
    file.get(c);
  }
  return heapString;
}
// process the file produce charFreqList
void FileRoutine::FileHandler::processFile(std::string filePath) {
  // open file stream and read from it
  std::ifstream file(filePath, std::ios::in);
}

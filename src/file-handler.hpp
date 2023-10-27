#pragma once
#include "huffman-tree.hpp"
#include <fstream>
namespace FileRoutine {
class FileHandler {
  // public fileds!
public:
  std::string filePath;
  // default constructor and destructor are being used for now
  FileHandler();
  ~FileHandler();
  // private fields
private:
#define LIMIT 26
  int size;
  std::vector<char> fileChars;
  std::vector<int> fileFreq;
};

/*FUNCTION PROTOTYPING*/
void writeFile(std::string, std::string);
std::byte getEncoding(hff::HuffmanTree);
void printDecodedMinHeap(std::string);
const std::string getSerialMinHeap(std::string);
} // namespace FileRoutine

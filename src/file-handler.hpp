#pragma once
#include "huffman-tree.hpp"
#include <fstream>
#include <list>
namespace FileRoutine {
class FileHandler {
  // public fileds!
public:
  std::string filePath;
  // default constructor and destructor are being used for now
  FileHandler(std::string fileInputPath, std::string fileOutputPath){
      // call write methods to that process input file
      // call write methods that turn processed data into the compressed huffman
      // version

  };
  // private fields
private:
#define LIMIT 26
  int size;
  // encountered characters
  std::list<char> fileChars;
  // the relative frequencies of each character encoutered in the file
  std::list<int> fileFreq;
};

/*FUNCTION PROTOTYPING*/
void writeFile(std::string, std::string);
std::byte getEncoding(hff::HuffmanTree, char);
void printDecodedMinHeap(std::string);
const std::string getSerialMinHeap(std::string);

} // namespace FileRoutine

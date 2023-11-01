#pragma once
#include "huffman-tree.hpp"
#include <fstream>
#include <list>
namespace FileRoutine {
class FileHandler {
  // class method declarations
  void processFile(std::string);
  char *getFileCharacters();
  int *getFileFrequencies();
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
  // size of the file?
  int size;
  // should be a list of encountered characters there relative frequencies in
  // the file
  // using an unordered_map to map characters inside a file to relative
  // frequency
  std::unordered_map<char, int> charFreqMap;
};

/*FUNCTION PROTOTYPING*/
void writeFile(std::string, std::string);
std::byte getEncoding(hff::HuffmanTree, char);
void printDecodedMinHeap(std::string);
const std::string getSerialMinHeap(std::string);

} // namespace FileRoutine

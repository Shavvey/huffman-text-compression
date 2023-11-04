#pragma once
#include "huffman-tree.hpp"
#include <fstream>
#include <list>
// create a namespace for file routine methods and functions
namespace FileRoutine {
class FileHandler {
  // class method declarations
  void processFile(std::string);
  char *getFileCharacters();
  int *getFileFrequencies();
  void printFileFrequnecies();
  void printFileCharacters();
  // public fileds!
public:
  std::string fileIn;
  std::string fileOut;
  // default constructor and destructor are being used for now
  FileHandler(std::string fileInputPath, std::string fileOutputPath) {
    // call write methods to that process input file
    // call write methods that turn processed data into the compressed huffman
    // version
    fileIn = fileInputPath;
    fileOut = fileOutputPath;
  };
  // when file handler is destroyed we should free the pointers for the file
  // frequencies and
  //  file characters
  ~FileHandler() {
    delete fileFreq;
    delete fileChars;
    charFreqMap.clear();
  }
  // private fields
private:
  // size of the file?
  int size;
  // should be a list of encountered characters there relative frequencies in
  // the file
  // using an unordered_map to map characters inside a file to relative
  // frequency
  std::unordered_map<char, int> charFreqMap;
  int *fileFreq;
  char *fileChars;
};

/*FUNCTION PROTOTYPING*/
// write file with the proper huffman encodings
void writeFile(std::string, std::string);
// get each encoding from the huffman tree
std::string getEncoding(hff::HuffmanTree, char);
void printDecodedMinHeap(std::string);
const std::string getSerialMinHeap(std::string);

std::string convertToBinary(unsigned int);
} // namespace FileRoutine

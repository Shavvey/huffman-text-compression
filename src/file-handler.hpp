#pragma once
#include "huffman-tree.hpp"
#include <fstream>
#include <list>
// create a namespace for file routine methods and functions
namespace FileRoutine {
class FileHandler {
  // class method declarations
  void processFile(std::string);
  // i should probably make this functions!
  char *getFileCharacters();
  int *getFileFrequencies();
  // test methods to make sure the file frequencies and chars are remembered
  void printFileFrequnecies();
  void printFileCharacters();
  // driver methods, should be built with the smaller functions and methods!!
  void huffmanEncrypt();
  void huffmanDecrypt();
  // public fileds!
public:
  std::string fileIn;
  std::string fileOut;
  FileHandler(std::string fileInputPath, std::string fileOutputPath) {
    fileIn = fileInputPath;
    fileOut = fileOutputPath;
    // for the constructor all we need is to store filepath for our input and
    // output
    // decryption and encryption methods should do the rest
  };
  // when file handler is destroyed we should free the pointers for the file
  // frequencies and
  //  file characters
  ~FileHandler() {
    // free up the fileFreq and fileChars pointers
    delete fileFreq;
    delete fileChars;
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
std::string convertToBinary(struct hff::huffCode);
} // namespace FileRoutine

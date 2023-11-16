#pragma once
#include "huffman-tree.hpp"
#include <fstream>
#include <list>
// create a namespace for file routine methods and functions
namespace FileRoutine {
class FileHandler {
  // class method declarations
public:
  void processFile(std::string);
  // i should probably make this functions!
  void getFileCharacters();
  void getFileFrequencies();
  // test methods to make sure the file frequencies and chars are remembered
  void printFileFrequnecies();
  void printFileCharacters();
  // driver methods, should be built with the smaller functions and methods!!
  void huffmanEncrypt();
  void huffmanDecrypt();
  // public fileds!
  std::string fileIn;
  std::string fileOut;
  FileHandler(std::string fileInputPath, std::string fileOutputPath) {
    fileIn = fileInputPath;
    fileOut = fileOutputPath;
    // for the constructor all we need is to store filepath for our input and
    // output
    // decryption and encryption methods should do the rest
  };
  ~FileHandler() {}
  // private fields
  // size of the file?
  int size;
  // should be a list of encountered characters there relative frequencies in
  // the file
  // using an unordered_map to map characters inside a file to relative
  // frequency
  std::unordered_map<char, int> charFreqMap;
  // a store of file characters inside a linked list
  // this will be broken down into a simpler array so that
  // huffman code can use it in it's constructor
  std::list<char> fileChars;
  // a store of file frequencies, it's the same as `fileChars`
  std::list<int> fileFreq;
};

/*FUNCTION PROTOTYPING*/
// write file with the proper huffman encodings
void writeSerialMinHeap(std::string, std::string);
// get each encoding from the huffman tree
std::string getEncoding(hff::HuffmanTree, char);
void printDecodedMinHeap(std::string);
const std::string getSerialMinHeap(std::string);
std::string convertToBinary(unsigned int);
std::bitset<8> getByteFromChar(char);
char decodeFileChar(char, hff::MinHeapNode *, int);
} // namespace FileRoutine

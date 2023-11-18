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
  std::string fileDecoded;
  std::string fileEncoded;
  FileHandler(std::string fileEncodePath, std::string fileDecodePath,
              bool flag) {
    // file with the huffman encodings we create
    fileDecoded = fileEncodePath;
    // file with just the plaintext characters
    fileEncoded = fileDecodePath;
    // for the constructor all we need is to store filepath for our input and
    // output
  };
  ~FileHandler() {}
  int const MAX_CODE_LENGTH;
  int size;
  std::unordered_map<char, int> charFreqMap;
  std::list<char> fileChars;
  std::list<int> fileFreq;
  hff::MinHeapNode *root_tree;
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
void rightPaddingZeroes(std::string *, int);
void huffmanTreeFromFile();
} // namespace FileRoutine

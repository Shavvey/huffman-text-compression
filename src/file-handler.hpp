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
  FileHandler(std::string fileEncodePath, std::string fileDecodePath) {
    // file with the huffman encodings we create
    fileDecoded = fileEncodePath;
    // file with just the plaintext characters
    fileEncoded = fileDecodePath;
    // 1: procceed with encyption routine
    // 0: proceed with decrypiton routine
    std::unordered_map<char, int> charFreqMap;

    processFile(fileDecodePath);
  };
  ~FileHandler() {}
  std::unordered_map<char, int> charFreqMap;
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

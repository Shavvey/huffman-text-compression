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
  FileHandler(const std::string fileEncodePath,
              const std::string fileDecodePath) {
    // file with the huffman encodings we create
    fileDecoded = fileEncodePath;
    // file with just the plaintext characters
    fileEncoded = fileDecodePath;

    processFile(fileDecodePath);
  };
  ~FileHandler() {}
  // map of file characters and their relative frequencies
  // used during the encoding step
  std::unordered_map<char, int> charFreqMap;
};

/*FUNCTION PROTOTYPING*/
// write file with the proper huffman encodings
void writeSerialMinHeap(const std::string, const std::string);
// get each encoding from the huffman tree
std::string getEncoding(hff::HuffmanTree, char);
void printDecodedMinHeap(const std::string);
const std::string getSerialMinHeap(const std::string);
std::string convertToBinary(unsigned int);
char decodeFileChar(char, hff::MinHeapNode *, int);
void rightPaddingZeroes(std::string *, int);
void huffmanTreeFromFile();
std::ostream &operator<<(std::ostream &os, const std::vector<bool> &v);
std::ostream &operator<<(std::ostream &os, int arr[]);
// generic template function
template <typename T>
std::vector<bool> getBits(T value, unsigned int, unsigned int);

template <class T>
T getValue(const std::vector<bool> &, unsigned int, unsigned int);
template <class T>
void append_bitset(std::vector<bool> &, const std::vector<T> &, size_t);
void fillBitset(std::vector<bool> &);
void writeBitset(const std::vector<bool> &, uint32_t, const std::string &);
const std::vector<bool> readBitset(const std::string &);
const long getFileSize(const std::string &);
std::vector<bool> bitsFromString(const std::string &);
} // namespace FileRoutine

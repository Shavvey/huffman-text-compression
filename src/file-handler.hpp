// only one header defintion of the file
#pragma once
// include all the definitions of for the huffman tree
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
    fileDecoded = fileDecodePath;
    // file with just the plaintext characters
    fileEncoded = fileEncodePath;

    processFile(fileDecodePath);
  };
  ~FileHandler() {}
  // map of file characters and their relative frequencies
  // used during the encoding step
  std::unordered_map<char, int> charFreqMap;
};

/*FUNCTION PROTOTYPING*/
// write file with the proper huffman encodings

int intFromBits(const std::vector<bool> &v);
void writeEncodings(const std::string, const std::string);
// get each encoding from the huffman tree
std::string getEncoding(hff::HuffmanTree tree, char c);
std::vector<bool> getBitsFromCode(hff::HuffmanTree tree, char c);
void printDecodedMinHeap(const std::string filepath);
std::string convertToBinary(unsigned int);
char decodeFileChar(char c, hff::MinHeapNode *treeNode, int bin);
void rightPaddingZeroes(std::string *, int);
void huffmanTreeFromFile();
std::ostream &operator<<(std::ostream &os, const std::vector<bool> &v);
std::ostream &operator<<(std::ostream &os, int arr[]);

template <typename T>
std::vector<bool> getBits(T value, unsigned int num_bits, unsigned int offset);

template <typename T>
void append_bitset(std::vector<bool> &, const std::vector<T> &, size_t);

void fillBitset(std::vector<bool> &bitset);
void writeBitset(const std::vector<bool> &bitsets, uint32_t num_valid_bits,
                 const std::string &filePath);
const std::vector<bool> readBitset(const std::string &filePath);
const long getFileSize(const std::string &filepath);
std::vector<bool> bitsFromString(const std::string &string);
std::vector<bool> huffCodeToBits(struct hff::huffCode &code);
void flushBitSet(const std::vector<bool> &bitsets, uint32_t numValidBits,
                 const std::string &filePath);
} // namespace FileRoutine

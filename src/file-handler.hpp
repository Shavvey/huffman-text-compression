// only one header definition of the file
#pragma once
// include all the definitions for the huffman tree
#include "huffman-tree.hpp"
// create a namespace for file routine methods and functions
namespace FileRoutine {
class FileHandler {
  // class method declarations
public:
  std::unordered_map<char, int> processFile(std::string);
  // driver methods, should be built with the smaller functions and methods!!
  void huffmanEncrypt();
  void huffmanDecrypt();
  void writeEncodings(const std::string &filePath,
                      const std::string &heapString,
                      const hff::HuffmanTree &tree);
  std::vector<bool> getEncryptedFileChar(const hff::HuffmanTree &tree);
  // public fields!
  std::string fileDecoded;
  std::string fileEncoded;
  FileHandler(const std::string fileEncodePath,
              const std::string fileDecodePath) {
    // file with the huffman encodings we create
    fileDecoded = fileDecodePath;
    // file with just the plain text characters
    fileEncoded = fileEncodePath;
    // use the specified plain text file produce a map of
    // the characters and their specified frequencies inside the file
    charFreqMap = processFile(fileDecodePath);
  };
  std::unordered_map<char, int> charFreqMap;
};

/*FUNCTION PROTOTYPING*/
int intFromBits(const std::vector<bool> &v);
// get each encoding from the huffman tree
std::string getEncoding(hff::HuffmanTree tree, char c);
std::vector<bool> getBitsFromCode(hff::HuffmanTree tree, char c);
void decodeFile(const std::vector<bool> text_bitset,
                const hff::HuffmanTree tree);
std::string convertToBinary(unsigned int);
char decodeFileChar(char c, hff::MinHeapNode *treeNode, int bin);
void rightPaddingZeroes(std::string *, int);
hff::HuffmanTree huffmanTreeFromFile(std::vector<bool> string_bitset);
std::ostream &operator<<(std::ostream &os, const std::vector<bool> &v);
std::ostream &operator<<(std::ostream &os, int arr[]);
void printBitRegions(const std::string &fileEncoded);
template <typename T>
std::vector<bool> getBits(T value, unsigned int num_bits, unsigned int offset);
void fillBitset(std::vector<bool> &bitset);
void writeBitset(const std::vector<bool> &bitsets, uint32_t num_valid_bits,
                 const std::string &filePath);
const std::vector<bool> readBitset(const std::string &filePath);
const long getFileSize(const std::string &filepath);
std::vector<bool> bitsFromString(const std::string &string);
std::vector<bool> huffCodeToBits(struct hff::huffCode &code);
std::vector<bool> getBitsFromCode(hff::HuffmanTree tree, char c);
} // namespace FileRoutine

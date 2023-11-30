#include "file-handler.hpp"
#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <vector>
// initially i was using `bitset` to write
// values, but it seems I needed to read and write
// the bits direclty, so I need to make much dumber functions
// to accomplish this.

// source:
// https://leimao.github.io/blog/CPP-Read-Write-Arbitrary-Bits/#Introduction
// overloading the basic << operator for vecotrs
// just a nicer way to display these values, because
// i am going to be using *a lot* of vectors
std::ostream &FileRoutine::operator<<(std::ostream &os,
                                      const std::vector<bool> &v) {
  // print out brackets to nake it look prettier
  os << "[";
  // look through each entry and print them
  for (int i = 0; i < v.size(); ++i) {
    os << v.at(i);
    // print comma to seperate values a litter better
    if (i != v.size() - 1) {
      os << ", ";
    }
  }
  // print out brackets
  os << "]";
  return os;
}

std::ostream &FileRoutine::operator<<(std::ostream &os, int arr[]) {
  for (int i = 0; i < 10; i++) {
    std::cout << arr[i] << " ";
  }
  std::cout << std::endl;
  return os;
}

// used when we need to get a bit representation of each value
// important thing to know is that we need the number of bits a value type
// represents for example normally an int is 4 bytes, so we set `num_bits` to be
// 4
template <typename T>
std::vector<bool> FileRoutine::getBits(T value, unsigned int num_bits,
                                       unsigned int offset) {
  // collect bits into this vector
  std::vector<bool> bits;
  size_t value_bits = sizeof(value) * 8;
  // assert trips we start getting bits outside target value
  assert(num_bits + offset <= value_bits);
  for (int i = 0; i < num_bits; i++) {
    bool bit = (value >> (value_bits - 1 - offset - i)) & 1U;
    bits.push_back(bit);
  }
  // returrn the collected bits from the given value types
  return bits;
}

// get value from the bit representation, in order to do this we need to know
// the size, in the number of bits, of the value type being extracted
template <typename T>
T FileRoutine::getValue(const std::vector<bool> &bits, unsigned int num_bits,
                        unsigned int offset) {
  T value = 0;
  for (int i = 0; i < num_bits; i++) {
    bool bit = bits.at(i);
    unsigned int shift = sizeof(T) - 1 - offset - i;
    if (bit == true) {
      value |= (1U << shift);
    }
  }
  return value;
}

// append more bits to an already existing given bitset with the other bits
template <typename T>
void append_bitset(std::vector<bool> &bitsets, const std::vector<T> &values,
                   size_t bitset_size) {
  for (int i = 0; i < values.size(); i++) {
    T value = values.at(i);
    std::vector<bool> bits =
        get_bits(value, bitset_size, sizeof(value) * 8 - bitset_size);

    // append given bits

    bitsets.insert(bitsets.end(), bits.begin(), bits.end());
  }
}
// fill a given bitset so that its size is divisible by 8,
// so that we can write the bitset using each byte
void FileRoutine::fillBitset(std::vector<bool> &bitsets) {
  // If the size of bitsets is not divisible by 8,
  // Append 0s to the end to make the size of bitsets divisible by 8.
  size_t original_size = bitsets.size();
  for (int i = 0; i < (8 - original_size % 8) % 8; i++) {
    bitsets.push_back(0);
  }
}

void FileRoutine::writeBitset(const std::vector<bool> &bitsets,
                              uint32_t num_valid_bits,
                              const std::string &filepath) {
  // size of bitset should be divisible by 8, otherwise throw an error
  assert(bitsets.size() % 8 == 0);
  std::fstream fhand;
  // trunc will clear the file
  fhand.open(filepath, fhand.binary | fhand.trunc | fhand.out);
  if (!fhand.is_open()) {
    std::cerr << "Failed to open " << filepath << std::endl;
  } else {
    fhand.write(reinterpret_cast<char *>(&num_valid_bits),
                sizeof(num_valid_bits));
    size_t num_bytes = bitsets.size() / 8;
    for (int i = 0; i < num_bytes; i++) {
      // ch: 00000000
      char ch = 0;
      for (int j = 0; j < 8; j++) {
        int k = i * 8 + j;
        ch |= (bitsets.at(k) << (8 - j - 1));
      }
      fhand.write(&ch, sizeof(ch));
    }
  }
  fhand.close();
}

// read bit set from a written file
const std::vector<bool> FileRoutine::readBitset(const std::string &filepath) {
  std::fstream fhand;
  std::vector<bool> bitsets;
  uint32_t num_valid_bits = 0;
  fhand.open(filepath, fhand.binary | fhand.in);
  if (!fhand.is_open()) {
    std::cerr << "Failed to open " << filepath << std::endl;
  } else {
    fhand.read(reinterpret_cast<char *>(&num_valid_bits),
               sizeof(num_valid_bits));
    while (fhand.peek() != EOF) {
      char ch;
      fhand.read(&ch, sizeof(ch));
      std::vector<bool> bits = FileRoutine::getBits(ch, sizeof(ch) * 8, 0);
      bitsets.insert(bitsets.end(), bits.begin(), bits.end());
    }
  }
  // contruct valid bitset
  std::vector<bool> valid_bitsets{bitsets.begin(),
                                  bitsets.begin() + num_valid_bits};
  return valid_bitsets;
}

// get the filesize using a given filepath
// param: filepath: specify the filepath to open
// returns a count based on the number of byte exist between
// the start and the end of the file
const long FileRoutine::getFileSize(const std::string &filepath) {
  long filesize = 0;
  // create file handler using file stream constructor
  std::fstream file_handler;
  file_handler.open(filepath, file_handler.binary | file_handler.in);
  if (!file_handler.is_open()) {
    // print to standard error if we can't open the file
    std::cerr << "Failed to open " << filepath << std::endl;
  } else {
    // goto end of the file
    file_handler.seekg(0, std::ios::end);
    // return the file stream position, this will be used to find filesize
    filesize = file_handler.tellg();
  }
  return filesize;
}

// uses a file path to append the size and stringMinHeap
// filePath: the file name and directory specified to create compressed file
// heapString: a string of character that can be used to rebuild the minHeap,
// which is the data structure chosen for the huffman encoding tree
void FileRoutine::writeSerialMinHeap(const std::string filePath,
                                     const std::string heapString) {
  // open file using fstream in binary mode
  std::ofstream file(filePath, std::ofstream::binary | std::ios::out);
  // create a serialized minHeap from the created heap string
  // cast to c-like string and write to the file based on size of string
  std::vector<std::byte> bytes;
  bytes.reserve(std::size(heapString));
  // create a serialized min heap from the heap string
  hff::SerializedMinHeap serialMinHeap = hff::serializeFromString(heapString);
  file.write((char *)serialMinHeap.data.data(), serialMinHeap.size);
  // close the file
  file.close();
}

// return bitstring of encoding, can recast to back to binary
std::string FileRoutine::getEncoding(hff::HuffmanTree huffTree, char c) {
  struct hff::huffCode code = huffTree.huffmanEncode(c);
  // NOTE: delete this afterwards, this is just for testing
  printf("Code's value %d\n", code.sum);
  printf("Code's size %d\n", code.size);
  // inti empty string
  std::string binarystring = convertToBinary(code.sum);
  // pad the string with zeroes to the right until the string is 4 characters
  // this makes each huffman code provided a fixed length, and thus decoding
  // should be easier
  rightPaddingZeroes(&binarystring, 4);
  printf("Codes's binary string %s\n", binarystring.c_str());
  return binarystring;
}

std::string FileRoutine::convertToBinary(unsigned int n) {
  if (n == 0) {
    return "0";
  }
  std::stack<char> charStack;
  while (n != 0) {
    char c = (n % 2) ? '1' : '0';
    // printf("%c", c);
    //  push binary digit onto stack
    charStack.push(c);
    n /= 2;
  }
  // reverse order to construct binary string
  std::string binarystring;
  // use the stack to reverse the binary characters and
  // use this to create the final binary string
  while (!charStack.empty()) {
    char c = charStack.top();
    charStack.pop();
    binarystring.push_back(c);
  }
  return binarystring;
}

// I want to be able to recover minHeap from the binary written inside the file
// using this function
void FileRoutine::printDecodedMinHeap(const std::string filePath) {
  std::ifstream file;
  file.open(filePath, std::ios::binary | std::ios::in);
  char c;
  std::string heapString;
  file.get(c);
  // find the null terminator of the string again
  while (c != '\0') {
    // construct a 8-bit binary string for each character
    // this is essentially just a fancy of way of grabin each byte in file
    std::bitset<8> b((unsigned char)c);
    if (c == '\n') {
      std::cout << "00000010";
      std::cout << '\t' << "\\n" << std::endl;
    } else {
      std::cout << b;
      std::cout << '\t' << (char)b.to_ulong();
      std::cout << std::endl;
    }
    heapString.push_back((char)b.to_ulong());
    file.get(c);
  }
  std::cout << "Recovered string: " + heapString << std::endl;
}
std::vector<bool> getBitsetFromString(const std::string &s) {}

const std::string FileRoutine::getSerialMinHeap(const std::string filePath) {
  std::ifstream file(filePath, std::ifstream::binary | std::ios::in);
  char c;
  std::string heapString;
  file.get(c);
  // read the file until the null terminator is reached
  // this should be the end of the heapstring
  while (c != '\0') {
    // extract the byte from teh file
    std::bitset<8> b((unsigned char)c);
    std::cout << b;
    // build heapstring back up from each byte read from file
    heapString.push_back((char)b.to_ulong());
    file.get(c);
  }
  // closing the file, even though it file stream will probably be destructed
  // anyway
  file.close();
  return heapString;
}

// process the file produce charFreqList, this list can then be
// decomposed into file frequency and file character arrays
void FileRoutine::FileHandler::processFile(std::string filePath) {
  // open file stream and read from it
  std::ifstream file(filePath, std::ios::in | std::ifstream::binary);
  char fileChar;
  // read until the end of file
  while (!file.eof()) {
    // get the next fileChar in the file
    file.get(fileChar);
    // create an iterator based on found char
    std::unordered_map<char, int>::iterator found = charFreqMap.find(fileChar);
    // if the char isn't found inside the hash table then we create a new entry
    if (found == charFreqMap.end()) {
      // insert file char pair and set key value to one
      charFreqMap.insert({fileChar, 1});
      // once the key value pair is created, we can increment
      // the frequnecy value for each successive look we do in the file
    } else {
      // increment the key value if the fileChar has already been found
      found->second = found->second + 1;
    }
  }
}

// simple string padding funciton that adds zeroes until target is reached
void FileRoutine::rightPaddingZeroes(std::string *inputString, int pad_length) {
  int size = (*inputString).size();
  while ((pad_length - size) > 0) {
    (*inputString).push_back('0');
    size++;
  }
}

void FileRoutine::FileHandler::huffmanEncrypt() {
  // process the input file, returing the map of chars and frequency data
  processFile(fileDecoded);
  std::cout << "Constructing Huffman Tree\n";
  hff::HuffmanTree tree(charFreqMap);
  // print out tree if you would like, (kinda messy for large trees)
  hff::printCurrentTree(tree.root);
  // create heap string can represents the `minHeap`
  std::string heapString = hff::minHeapToString(tree.root);
  writeSerialMinHeap(fileEncoded, heapString);
  // open input file
  std::ifstream fileInput(fileDecoded, std::ios::in);
  // open ouput file stream in output and append mode
  std::ofstream fileOutput(fileEncoded, std::ofstream::binary | std::ios::app |
                                            std::ios::out);
  char fileChar;
  std::cout << "==Encoding Huffman Codes== \n";

  // just testing out if we can still find the minHeap string after
  // huffman codes can be generated and written to the output file
  printDecodedMinHeap(fileEncoded);
  // file input and file output
  int len[MAX_TREE_HEIGHT], top = 0;
  hff::printCodes(tree.root, len, top);
  fileInput.close();
  fileOutput.close();
}
void FileRoutine::huffmanTreeFromFile() {}

void FileRoutine::FileHandler::huffmanDecrypt() {}

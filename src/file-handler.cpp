#include "file-handler.hpp"
#include <algorithm>
#include <bitset>
#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

// initially i was using `bitset` to write
// values, but it seems I needed to read and write
// the bits directly, so I need to make much dumber functions
// to accomplish this.
// source:
// https://leimao.github.io/blog/CPP-Read-Write-Arbitrary-Bits/#Introduction
// overloading the basic << operator for vectors
std::ostream &FileRoutine::operator<<(std::ostream &os,
                                      const std::vector<bool> &v) {
  // print out brackets to make it look prettier
  os << "[";
  // look through each entry and print them
  for (int i = 0; i < v.size(); ++i) {
    os << v.at(i);
    // print comma to separate values a litter better
    if (i != v.size() - 1) {
      os << ", ";
    }
  }
  // print out brackets
  os << "]";
  return os;
}

// overloading output stream operator to print out entire integer array
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
  // return the collected bits from the given value types
  return bits;
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

// write the bitset given a filename
void FileRoutine::writeBitset(const std::vector<bool> &bitset,
                              uint32_t numValidBits,
                              const std::string &filePath) {
  // size of bitset should be divisible by 8, otherwise throw an error
  assert((bitset.size() % 8 == 0) && "bitset should be a multiple of 8");
  std::fstream fhand;
  // `trunc` will clear the file
  fhand.open(filePath, fhand.binary | fhand.trunc | fhand.out);
  if (!fhand.is_open()) {
    std::cerr << "Failed to open " << filePath << std::endl;
  } else {
    fhand.write(reinterpret_cast<char *>(&numValidBits), sizeof(numValidBits));
    size_t numByte = bitset.size() / 8;
    for (int i = 0; i < numByte; i++) {
      // ch: 00000000
      char c = 0;
      for (int j = 0; j < 8; j++) {
        int k = i * 8 + j;
        c |= (bitset.at(k) << (8 - j - 1));
      }
      fhand.write(&c, sizeof(c));
    }
  }
  fhand.close();
}

std::vector<bool>
FileRoutine::FileHandler::getEncryptedFileChar(const hff::HuffmanTree &tree) {
  std::vector<bool> bitset;
  // output file, should produced the encrypted text
  std::ofstream fileOut;
  fileOut.open(fileEncoded, fileOut.binary | fileOut.out | fileOut.app);

  // input file, should the plain text characters
  std::ifstream fileIn;
  fileIn.open(fileDecoded, fileIn.in);
  // holds each char from 'fileIn'
  char fileChar;
  // while we have not reached the end of file
  while (!fileIn.eof()) {
    fileIn.get(fileChar);
    // std::cout << "File char being encoded: " << fileChar << std::endl;
    std::vector<bool> huffCodeBits = getBitsFromCode(tree, fileChar);
    // std::cout << "File char conversion to bits: " << huffCodeBits <<
    // std::endl;
    //  insert huff codes bits into the larger bitset
    bitset.insert(bitset.end(), huffCodeBits.begin(), huffCodeBits.end());
  }
  fileIn.close();
  // make sure final bitset can be broken into bytes for writing process
  // we accomplish this by just filling the bitset until its a multiple of 8
  fillBitset(bitset);
  return bitset;
}

// read bit set from a written file
const std::vector<bool> FileRoutine::readBitset(const std::string &filepath) {
  // append bitset of entire heapstring to the end of the bitset field
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
      // append the bitset with successfully read char
      bitsets.insert(bitsets.end(), bits.begin(), bits.end());
    }
  }
  // construct valid bitset
  std::vector<bool> valid_bitsets{bitsets.begin(),
                                  bitsets.begin() + num_valid_bits};
  return valid_bitsets;
}

// get the file size using a given file path
// param: file path: specify the filepath to open
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
    // return the file stream position, this will be used to find file size
    filesize = file_handler.tellg();
  }
  return filesize;
}

// filePath: the file name and directory specified to create compressed file
// heapString: a string of character that can be used to rebuild the minHeap,
// which is the data structure chosen for the huffman encoding tree
void FileRoutine::FileHandler::writeEncodings(const std::string &filePath,
                                              const std::string &heapString,
                                              const hff::HuffmanTree &tree) {
  // convert heap string to bitset
  std::vector<bool> bitsetHeapString = FileRoutine::bitsFromString(heapString);
  int size = heapString.size();
  std::vector<bool> bitsetField = getBits<int>(size, sizeof(int) * 8, 0);
  // append bitset of entire heapstring to the end of the bitset field
  bitsetField.insert(bitsetField.end(), bitsetHeapString.begin(),
                     bitsetHeapString.end());
  std::vector<bool> textBitset = getEncryptedFileChar(tree);
  // append text bitset to final bitset
  bitsetField.insert(bitsetField.end(), textBitset.begin(), textBitset.end());
  // write this bitset to the file
  std::reverse(bitsetField.begin(), bitsetField.end());
  writeBitset(bitsetField, bitsetField.size(), filePath);
  // use helper function to write the encrypted text characters
  getEncryptedFileChar(tree);
}

// return a bit string of encoding, can recast to back to binary
// tree: the huffman tree used to look up each char
// c: the character that is being looked up
// uses huffman encode using the map between chars and their respective huffman
// code
std::string FileRoutine::getEncoding(hff::HuffmanTree tree, char c) {
  struct hff::huffCode code = tree.huffmanEncode(c);
  // NOTE: delete this afterwards, this is just for testing
  printf("Code's value %d\n", code.sum);
  printf("Code's size %d\n", code.size);
  // init empty string
  std::string binaryString = convertToBinary(code.sum);
  // pad the string with zeroes to the right until the string is 4 characters
  // this makes each huffman code provided a fixed length, and thus decoding
  // should be easier
  std::cout << "Code's binary string: " << binaryString << std::endl;
  // return binary string created
  return binaryString;
}
std::vector<bool> FileRoutine::getBitsFromCode(hff::HuffmanTree tree, char c) {
  // look up code from its char
  struct hff::huffCode code = tree.huffmanEncode(c);
  // std::cout << "Sum of code huff code: " << code.sum << std::endl;
  // convert huff code to a bits
  return huffCodeToBits(code);
}
// simple function to return a bit string represented from an unsigned integer
std::string FileRoutine::convertToBinary(unsigned int n) {
  if (n == 0) {
    return "0";
  }
  std::stack<char> charStack;
  while (n != 0) {
    char c = (n % 2) ? '1' : '0';
    //  push binary digit onto stack
    charStack.push(c);
    n /= 2;
  }
  // reverse order to construct binary string
  std::string binarystring(charStack.top(), charStack.size());
  std::reverse(binarystring.begin(), binarystring.end());
  return binarystring;
}

// convert the huff code given to a simple vector in the smallest available size
std::vector<bool> FileRoutine::huffCodeToBits(struct hff::huffCode &code) {
  std::vector<bool> bit_set(code.size);

  int n = code.sum;
  int i = 0;
  while (n != 0) {
    // check divisibility, if current number has a factor of two return true,
    // otherwise false
    bool b = (n % 2) ? 1 : 0;
    bit_set.at(i) = b;
    // divide sum by two
    n /= 2;
    i++;
  }
  // reverse the order of the bitset
  std::reverse(bit_set.begin(), bit_set.end());
  return bit_set;
}

// an integer value from a given bits inside vector v
int FileRoutine::intFromBits(const std::vector<bool> &v) {
  int retval = 0;
  int i = 0;
  for (std::vector<bool>::const_iterator itr = v.begin(); itr != v.end();
       itr++, i++) {
    if (*itr) {
      retval |= 1 << i;
    }
  }
  return retval;
}

// prints the decoded output the file given, should be the encoded version of
// file using its huffman tree
void FileRoutine::FileHandler::decodeFile(std::vector<bool> text_bitset,
                                          const hff::HuffmanTree tree) {
  // name of the text file produced
  // this is comically stupid to just name it output but whatever
  std::string output = "output.txt";
  // NOTE: since we fill the text_bitset, we need to keep track
  //  of how many characters we have decoded from the bitset
  //  and make sure it does not exceed the original size of characters
  //  from the plaintext file
  int charCount = getNumChars(fileDecoded);
  std::reverse(text_bitset.begin(), text_bitset.end());
  // decode the text bitset
  // first iterate across the bitset
  std::fstream fileOutput(output, std::ios::out);
  fileOutput.clear();
  hff::MinHeapNode *root = tree.root;
  std::vector<bool>::const_iterator itr = text_bitset.begin();
  int numDecode = 0;
  while (numDecode < charCount) {
    (*itr) ? root = root->right : root = root->left;
    // if i is one, move right; otherwise move left
    if (hff::isLeaf(root)) {
      // put character decoded from huffman tree into the textfile
      fileOutput.put(root->data);
      // go back to tree root
      root = tree.root;
      // int that keeps track of successfully decoded chars
      numDecode++;
    }
    // increment iterator to goto next element in `text_bitset`
    itr++;
  }
  fileOutput.close();
}

// function to just grab all the bits inside a file an print out the bit region
// supposedly encoding from each
void FileRoutine::printBitRegions(const std::string &fileEncoded) {
  // recover the bitset from the file read out
  std::vector<bool> bitset = readBitset(fileEncoded);
  // bitset can't be empty after this step, so abort using this assert if it is
  assert((bitset.size() > 0) && "bitset must not be empty!");
  // NOTE: not a lot of robust error handling with this, be careful!
  std::vector<bool> INT_BITSET(bitset.end() - (sizeof(int) * 8), bitset.end());
  int size = intFromBits(INT_BITSET);
  std::vector<bool> STRING_BITSET(
      bitset.end() - (sizeof(char) * size * 8 + sizeof(int) * 8),
      bitset.end() - (sizeof(int) * 8));
  std::vector<bool> TEXT_BITSET(
      bitset.begin(),
      bitset.end() - (sizeof(char) * size * 8 + sizeof(int) * 8));
  std::cout << "Total bitset recovered from file " << fileEncoded << " : "
            << bitset << std::endl;
  std::cout << "Integer field: " << INT_BITSET << std::endl;
  std::cout << "Heap string field: " << STRING_BITSET << std::endl;
  std::cout << "Binary encodings of original text: " << TEXT_BITSET
            << std::endl;
}

std::vector<bool> FileRoutine::bitsFromString(const std::string &s) {
  // number of bits for each character
  const int NUM_BITS{8};
  const int OFFSET{0};
  std::vector<bool> bits;
  // reserve bitset size given that this is a string of ASCII characters
  // ignore the null characters of string
  for (int j = 0; j < s.size(); j++) {
    char value = s.at(j);
    // collect bits into this vector
    size_t value_bits = sizeof(value) * 8;
    // assert trips we start getting bits outside target value
    assert(NUM_BITS + OFFSET <= value_bits);
    for (int i = 0; i < NUM_BITS; i++) {
      bool bit = (value >> (value_bits - 1 - OFFSET - i)) & 1U;
      bits.push_back(bit);
    }
  }
  return bits;
}

// process the file by creating mapping each encountered char to a frequency
// (number of times encountered inside the file)
std::unordered_map<char, int>
FileRoutine::FileHandler::processFile(std::string filePath) {
  // open file stream and read from it
  std::ifstream file(filePath, std::ios::in | std::ifstream::binary);
  char fileChar;
  std::unordered_map<char, int> charFreqMap;
  // read until the end of file
  while (!file.eof()) {
    // get the next fileChar in the file
    file.get(fileChar);
    // create an iterator based on found char
    std::unordered_map<char, int>::iterator found = charFreqMap.find(fileChar);
    // if the char isn't found inside the hash table then we create a new entry
    if (found == charFreqMap.end()) {
      // insert file char pair and set key value to one, this happens each newly
      // encountered char not already inside dictionary/map
      charFreqMap.insert({fileChar, 1});
      // once the key value pair is created, we can increment
      // the frequency value for each successive look we do in the file
    } else {
      // increment the key value if the fileChar has already been found
      found->second = found->second + 1;
    }
  }
  return charFreqMap;
}

// simple string padding function that adds zeroes until target is reached
void FileRoutine::rightPaddingZeroes(std::string *inputString, int pad_length) {
  int size = (*inputString).size();
  // while we the size is below the pad length
  while ((pad_length - size) > 0) {
    // append string with a zero
    (*inputString).push_back('0');
    // increment size
    size++;
  }
}

void FileRoutine::FileHandler::huffmanEncrypt() {
  // process the input file, returning the map of chars and frequency data
  std::cout << "Constructing Huffman Tree" << std::endl;
  hff::HuffmanTree tree(charFreqMap);
  // print out tree if you would like, (kinda messy for large trees)
  hff::printCurrentTree(tree.root);
  // create heap string can represents the `minHeap`
  std::string heapString = hff::minHeapToString(tree.root);
  int len[MAX_TREE_HEIGHT], top = 0;
  tree.populateCharCodes(tree.root, len, top);
  // write the binary encodings for the each character, should be based on the
  // huffman tree also, the minheap will be serialized as a string and embedded
  // inside the file (reversed to garble the string a little)
  writeEncodings(fileEncoded, heapString, tree);
  // delete the created tree, freeing its memory
  hff::deleteTree(tree.root);
}

// create the huffman tree from the encoded file
// string_bitset: constant reference to the bitset representing the heapstring
hff::HuffmanTree
FileRoutine::huffmanTreeFromFile(std::vector<bool> string_bitset) {
  // iterate through the bitset and grab each bool and construct a byte using it
  std::vector<bool>::const_iterator itr = string_bitset.begin();
  std::string heapstring;
  while (itr != string_bitset.end()) {
    // construct a new byte as new bools are read
    std::bitset<8> byte;
    for (int i = 0; i < 8; i++) {
      byte[i] = *itr;
      itr++;
    }
    // convert new decoded byte into a char
    char c = (char)byte.to_ulong();
    heapstring.push_back(c);
  }
  // reverse the heapstring
  std::reverse(heapstring.begin(), heapstring.end());
  // create a minheap from the serialized minheap embedded inside the file
  hff::MinHeapNode *root = hff::minHeapFromString(heapstring);
  hff::printTree(root);
  // construct a huffman tree object uses the pointer to the root
  hff::HuffmanTree tree(root);
  return tree;
}

int FileRoutine::getNumChars(const std::string &file) {
  int count = 0;
  // line of the opened file
  std::string line;
  // open a file input stream
  std::ifstream fileInput(file);
  assert((fileInput.is_open()) && "Error opening file");
  // grab each line of the text file
  while (getline(fileInput, line)) {
    // increment count based on line length
    count += line.length();
  }
  return count;
}

// decryption routine, should be composed of more simple functions and methods
void FileRoutine::FileHandler::huffmanDecrypt() {
  // first retrieve the bitset
  std::vector<bool> bitset = readBitset(fileEncoded);
  // abort if the read bitset is zero
  assert((bitset.size() > 0) && "bitset must not be empty!");
  // construct the tree uses its char freq map
  std::vector<bool> INT_BITSET(bitset.end() - (sizeof(int) * 8), bitset.end());
  // size taken from the integer field inside the bitset
  int size = intFromBits(INT_BITSET);
  // bitset inside the file that stores the heap string
  std::vector<bool> STRING_BITSET(
      bitset.end() - (sizeof(char) * size * 8 + sizeof(int) * 8),
      bitset.end() - (sizeof(int) * 8));
  std::vector<bool> TEXT_BITSET(
      bitset.begin(),
      bitset.end() - (sizeof(char) * size * 8 + sizeof(int) * 8));
  // retrieve tree using the decoded heapstring
  hff::HuffmanTree tree = huffmanTreeFromFile(STRING_BITSET);
  // decode the file using the `text_bitset` and the tree
  decodeFile(TEXT_BITSET, tree);
  // delete the tree after decryption
  hff::deleteTree(tree.root);
}

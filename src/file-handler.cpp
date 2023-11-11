#include "file-handler.hpp"
#include <cstdint>
#include <fstream>

// uses a file path to append the size and stringMinHeap
// filePath: the file name and directory specified to create compressed file
void FileRoutine::writeFile(std::string filePath, std::string heapString) {
  // using basic file stream provided by cpp standard library
  std::ofstream file;
  // open file using fstream in binary mode
  file.open(filePath, std::ios::binary | std::ios::out);
  // create a serialized minHeap from the created heap string
  hff::SerializedMinHeap serialMinHeap = hff::serializeFromString(heapString);
  file.write((char *)serialMinHeap.data.data(), serialMinHeap.size);
  file.close();
}
// return bitstring of encoding, can recast to back to binary
std::string FileRoutine::getEncoding(hff::HuffmanTree huffTree, char c) {
  struct hff::huffCode code = huffTree.huffmanEncode(c);
  std::string s = convertToBinary(code);
  return s;
}

std::string FileRoutine::convertToBinary(struct hff::huffCode code) {
  uint b = (uint)code.sum;
  std::string binary = "";
  uint mask = code.size * 2;
  while (mask > 0) {
    // used mask to and with unsigned input, to find each digit
    // one at a time
    binary += ((b & mask) == 0) ? '0' : '1';
    mask >>= 1;
  }
  std::cout << binary << std::endl;
  return binary;
}
// I want to be able to recover minHeap from the binary written inside the file
// using this function
void FileRoutine::printDecodedMinHeap(std::string filePath) {
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
    std::cout << b;
    std::cout << '\t' << (char)b.to_ulong();
    std::cout << std::endl;
    heapString.push_back((char)b.to_ulong());
    file.get(c);
  }
  std::cout << "Recovered string: " + heapString << std::endl;
}
const std::string FileRoutine::getSerialMinHeap(std::string filePath) {
  std::ifstream file(filePath, std::ios::binary | std::ios::in);
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
  std::ifstream file(filePath, std::ios::in);
  char fileChar;
  // read until the end of file
  while (!file.eof()) {
    // get the next fileChar in the file
    file.get(fileChar);
    // create an iterator based on found char
    std::unordered_map<char, int>::iterator found = charFreqMap.find(fileChar);
    // if the char isn't found inside the hash table then we create a new entry
    if (found == charFreqMap.end()) {
      // insert file char pair and get key value to one
      charFreqMap.insert({fileChar, 1});
    } else {
      // increment the key value if the fileChar has already been found
      found->second = found->second + 1;
    }
  }
}
// returns a pointer to an array that holds file characters
void FileRoutine::FileHandler::getFileCharacters() {

  for (auto itr : charFreqMap) {
    char c = itr.first;
    fileChars.push_back(c);
  }
}
// a pointer to an array that holds the file frequencies of each characters
// inside the file
void FileRoutine::FileHandler::getFileFrequencies() {
  for (auto itr : charFreqMap) {
    int i = itr.second;
    fileFreq.push_back(i);
  }
}
void FileRoutine::FileHandler::huffmanEncrypt() {
  // process the input file, returing the map of chars and frequency data
  processFile(fileIn);
  // get file frequency and file character information
  getFileCharacters();
  getFileFrequencies();
  // print  them out
  // printFileCharacters();
  // printFileFrequnecies();
}

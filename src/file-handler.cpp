#include "file-handler.hpp"
#include <cstdint>
#include <fstream>

// uses a file path to append the size and stringMinHeap
// filePath: the file name and directory specified to create compressed file
// heapString: a string of character that can be used to rebuild the minHeap,
// which is the data structure chosen for the huffman encoding tree
void FileRoutine::writeSerialMinHeap(std::string filePath,
                                     std::string heapString) {
  // open file using fstream in binary mode
  std::ofstream file(filePath, std::ios::binary | std::ios::out);
  // create a serialized minHeap from the created heap string
  hff::SerializedMinHeap serialMinHeap = hff::serializeFromString(heapString);
  file.write((char *)serialMinHeap.data.data(), serialMinHeap.size);
  // close the file
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
// returns a pointer to an array that holds file characters
void FileRoutine::FileHandler::getFileCharacters() {

  for (const std::pair<int, char> itr : charFreqMap) {
    char c = itr.first;
    fileChars.push_back(c);
  }
}
// a pointer to an array that holds the file frequencies of each characters
// inside the file
void FileRoutine::FileHandler::getFileFrequencies() {
  for (const std::pair<int, char> itr : charFreqMap) {
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
  int freq[fileFreq.size()];
  int k = 0;
  // grab reference for each element in the list
  for (int const &i : fileFreq) {
    // put each file frequency into the array
    freq[k++] = i;
  }
  char arr[fileChars.size()];
  k = 0;
  for (int const &i : fileChars) {
    // put each file char into the array
    arr[k++] = i;
  }
  int size = sizeof(arr) / sizeof(arr[0]);
  // construct huffman tree based on data
  std::cout << "Constructing Huffman Tree\n";
  hff::HuffmanTree tree(arr, freq, size);
  // print out tree if you would like, (kinda messy for large trees)
  hff::printCurrentTree(tree.root);
  // create heap string can represents the `minHeap`
  std::string heapString = hff::minHeapToString(tree.root);
  writeSerialMinHeap(fileOut, heapString);
  // open input file
  std::ifstream fileInput(fileIn, std::ios::in);
  // open ouput file stream in output and append mode
  std::ofstream fileOutput(fileOut,
                           std::ios::binary | std::ios::app | std::ios::out);
  char fileChar;
  std::cout << "==Encoding Huffman Codes== \n";
  while (!fileInput.eof()) {
    // get the fileChar from the in file
    fileInput.get(fileChar);
    std::string huffCode = getEncoding(tree, fileChar);
    int size = huffCode.size();
    // write the huffcode to the specified file output
    fileOutput.write(huffCode.c_str(), size);
  }
  // just testing out if we can still find the minHeap string after
  // huffman codes can be generated and written to the output file
  printDecodedMinHeap(fileOut);
  // file input and file output
  int len[MAX_TREE_HEIGHT], top = 0;
  hff::printCodes(tree.root, len, top);
  fileInput.close();
  fileOutput.close();
}
void FileRoutine::FileHandler::huffmanDecrypt() {
  std::string decodedMinHeap = FileRoutine::getSerialMinHeap(fileOut);
  // create root for huffman tree based on decoded string of `minHeap`
  hff::MinHeapNode *root = hff::minHeapFromString(decodedMinHeap);
  // loop through file and determine when the null character is hit
  int nullFlag = 0;
  // construct file handler based on file output (the binary target)
  std::ifstream fileInput(fileOut, std::ios::in);
  char fileChar;
  // track the ammount of times we have iterated through, after null is
  // encountered
  int iter_length = 0;
  while (fileInput.eof()) {
    // get character from file input
    fileInput.get(fileChar);
    if (fileChar == '\0') {
      nullFlag = 1;
    }
    if (nullFlag) {

      hff::MinHeapNode *tree = root;
      fileInput.get(fileChar);
      // copy root pointer
      while (!hff::isLeaf(root)) {
        std::bitset<8> byte;
        int length = iter_length % 8;
        if (length == 0) {
          // grab new byte each 8 iteration lengths
          byte = getByteFromChar(fileChar);
        }
        (byte[length]) ? tree = tree->left : tree = tree->right;
        iter_length++;
      }
      // once we have hit a leaf, we have found our character, so write it.
      printf("Data decoded %c\n", tree->data);
    }
  }
}

std::bitset<8> FileRoutine::getByteFromChar(char c) {
  // simple function to return a cast from char
  return std::bitset<8>(c);
}

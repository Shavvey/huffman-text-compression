#include "file-handler.hpp"
#include "huffman-tree.hpp"
// Driver Code
int main() {
  // create file handle
  // just a way to get target file and output file name
  // and do a bunch of sutff with it
  FileRoutine::FileHandler fileHandle("example.txt", "example.bin");
  fileHandle.huffmanEncrypt();
  FileRoutine::printDecodedMinHeap(fileHandle.fileEncoded);
  std::string s = "111";
  // pass by reference of the string
  FileRoutine::rightPaddingZeroes(&s, 4);
  std::cout << s << std::endl;
  std::string binary_string = "1110011100";
  // we can use this to convert each string into binary
  for (std::size_t i = 0; i < binary_string.size(); i++) {
    std::cout << std::bitset<1>(binary_string.c_str()[i]);
  }
  std::cout << std::endl;
  return EXIT_SUCCESS;
}

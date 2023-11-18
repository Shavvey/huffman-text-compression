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
  return EXIT_SUCCESS;
}

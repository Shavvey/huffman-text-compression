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
  std::string s = "cole";
  std::vector<bool> bitset = FileRoutine::getBits(s, 8 * s.size(), 8);
  std::cout << &bitset;
  return EXIT_SUCCESS;
}

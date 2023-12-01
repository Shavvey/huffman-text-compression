#include "file-handler.hpp"
#include "huffman-tree.hpp"

int main() {
  // create file handle
  // just a way to get target file and output file name
  // and do a bunch of sutff with it
  FileRoutine::FileHandler fileHandle("example.txt", "example.bin");
  fileHandle.huffmanEncrypt();
  FileRoutine::printDecodedMinHeap(fileHandle.fileEncoded);
  // use ostream override in FileRoutine for this
  using namespace FileRoutine;
  char j = 'c';
  int k = 8;
  int i = 0;
  std::vector<bool> bitset = FileRoutine::getBits(j, k, i);
  std::cout << bitset << std::endl;
  return EXIT_SUCCESS;
}

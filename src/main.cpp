// include code that interacts with the encrypted and decrypted files
#include "file-handler.hpp"
// include code that create the huffman tree
#include "huffman-tree.hpp"

int main() {
  // create file handle
  // just a way to get target file and output file name
  // and do a bunch of sutff with it
  FileRoutine::FileHandler fileHandle("example.bin", "example.txt");
  fileHandle.huffmanEncrypt();
  // use ostream override in FileRoutine for this
  struct hff::huffCode code;
  code.sum = 16;
  code.size = 4;
  using namespace FileRoutine;

  std::vector<bool> bits = huffCodeToBits(code);
  std::cout << "Bits created: " << bits << std::endl;

  return EXIT_SUCCESS;
}

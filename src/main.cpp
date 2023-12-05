#include "file-handler.hpp"
#include "huffman-tree.hpp"

int main() {
  // create file handle
  // just a way to get target file and output file name
  // and do a bunch of sutff with it
  FileRoutine::FileHandler fileHandle("example.bin", "example.txt");
  fileHandle.huffmanEncrypt();
  // use ostream override in FileRoutine for this
  using namespace FileRoutine;
  std::string s = "cole";
  std::cout << "size of string: " << s.size() << std::endl;
  std::vector<bool> bitset = bitsFromString(s);
  std::cout << bitset << std::endl;
  return EXIT_SUCCESS;
}

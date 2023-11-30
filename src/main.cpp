#include "file-handler.hpp"
#include "huffman-tree.hpp"

int main() {
  // create file handle
  // just a way to get target file and output file name
  // and do a bunch of sutff with it
  FileRoutine::FileHandler fileHandle("example.txt", "example.bin");
  fileHandle.huffmanEncrypt();
  FileRoutine::printDecodedMinHeap(fileHandle.fileEncoded);
  int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int arr2[10] = {11, 22, 33, 44, 55, 66, 77, 88, 99, 100};
  std::vector<bool> v = {1, 0, 1, 0, 1, 0, 1};
  // use ostream override in FileRoutine for this
  using namespace FileRoutine;
  std::cout << arr << arr2;
  std::cout << v << std::endl;
  return EXIT_SUCCESS;
}

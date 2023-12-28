// include code that interacts with the encrypted and decrypted files
#include "file-handler.hpp"
// include code that create the huffman tree

int main() {
  // create file handle
  // just a way to get target file and output file name
  // and do a bunch of sutff with it
  FileRoutine::FileHandler fileHandle("example.bin", "example.txt");
  // encrypt file and save as `example.bin`
  fileHandle.huffmanEncrypt();
  // decrypt file using `example.bin` the output should be the same as
  // `example.txt`
  fileHandle.huffmanDecrypt();
  return EXIT_SUCCESS;
}

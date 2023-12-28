// include code that interacts with the encrypted and decrypted files
#include "file-handler.hpp"

int main() {
  // open file handle
  FileRoutine::FileHandler fileHandle("example.bin", "example.txt");
  // encrypt file and save as `example.bin`
  fileHandle.huffmanEncrypt();
  // decrypt file using `example.bin` the output should be the same as
  // `example.txt`
  fileHandle.huffmanDecrypt();
  return EXIT_SUCCESS;
}

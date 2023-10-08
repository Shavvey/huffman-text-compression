#include "file-handler.hpp"
#include "huffman-tree.hpp"
#include <cstdint>
#include <fstream>

// uses a file path to append the size nad stringMinHeap
void FileRoutine::writeFile(std::string filePath, char *stringMinHeap,
                            int size) {
  std::fstream file;
  // open file using fstream in binary and append mode
  file.open(filePath, std::ios::binary | std::ios::app);
  file.write(reinterpret_cast<char *>(size), sizeof(size));
  // write the serialMinHeap string to the file
  file.write(stringMinHeap, sizeof(stringMinHeap));
}
void encodeFile() {}

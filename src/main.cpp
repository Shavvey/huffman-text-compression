#include "huffman-tree.hpp"
// driver code
int main() {

  char arr[] = {'a', 'b', 'c', 'd', 'e', 'f'};
  int freq[] = {5, 9, 12, 13, 16, 45};

  int size = sizeof(arr) / sizeof(arr[0]);
  huffmanCodes(arr, freq, size);

  return EXIT_SUCCESS;
}

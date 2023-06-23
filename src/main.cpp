#include "huffman-tree.hpp"
// Driver Code
int main() {

  char arr[] = {'a', 'b', 'c', 'd', 'e', 'f'};
  int freq[] = {5, 9, 12, 13, 16, 45};

  int size = sizeof(arr) / sizeof(arr[0]);

  hff::huffmanCodes(arr, freq, size);

  return 0;
}

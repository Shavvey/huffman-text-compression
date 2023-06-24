#include "huffman-tree.hpp"
// Driver Code
int main() {
  // found characters
  char arr[] = {'a', 'b', 'c', 'd', 'e', 'f'};
  // relative frequencies of each character
  int freq[] = {5, 9, 12, 13, 16, 45};
  // the ammount of characters found = and stored in the array
  int size = sizeof(arr) / sizeof(arr[0]);
  // generated huffman codes given each characters and their frequencies
  hff::huffmanCodes(arr, freq, size);

  return 0;
}

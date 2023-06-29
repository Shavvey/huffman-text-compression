#include "huffman-tree.hpp"
// Driver Code
int main() {
  // found characters
  char arr[] = {'a', 'b', 'c', 'd', 'e', 'f'};
  // relative frequencies of each character
  int freq[] = {5, 9, 12, 13, 16, 45};
  // the ammount of characters found = and stored in the array
  int size = sizeof(arr) / sizeof(arr[0]);
  hff::MinHeapNode *root = hff::buildHuffmanTree(arr, freq, size);
  // making sure methods and class constructor is working properly
  hff::HuffmanTree tree = hff::HuffmanTree(arr, freq, size);
  tree.printHuffmanTree();
  // generated huffman codes given each characters and their frequencies
  hff::huffmanCodes(arr, freq, size);
  hff::printCurrentTree(root);
  std::string heapString = hff::minHeapToString(root);
  hff::SerializedMinHeap serialMinHeap = hff::serializeFromString(heapString);
  hff::printBytes(serialMinHeap);
  hff::MinHeapNode *rootFromString = hff::minHeapFromString(heapString);
  hff::printCurrentTree(rootFromString);
  return EXIT_SUCCESS;
}

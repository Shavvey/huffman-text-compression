// class definition + function prototyping of huffman-tree!
#include "huffman-tree.hpp"

hff::MinHeapNode *newNode(char charIn, unsigned freq) {
  hff::MinHeapNode *node = new hff::MinHeapNode;
  // initialze right and left parent to null
  node->left = node->right = NULL;
  node->charIn = charIn;
  node->freq = freq;

  return node;
}
// creates the minHeap used in huffman tree
hff::MinHeap *createMinHeap(unsigned capacity) {
  hff::MinHeap *minHeap = new hff::MinHeap;
  // initial size should be zero
  minHeap->size = 0;
  minHeap->capacity = capacity;
  // size of array in bytes should be the ammount of nodes contained within the
  // heap and the size of each node in bytes
  minHeap->array = (hff::MinHeapNode **)malloc(minHeap->capacity *
                                               sizeof(hff::MinHeapNode *));

  return minHeap;
}

// helper function to swap two given min heap nodes
void swapMinHeapNode(hff::MinHeapNode **first, hff::MinHeapNode **second) {
  hff::MinHeapNode *temp = *first;
  *first = *second;
  *second = temp;
}

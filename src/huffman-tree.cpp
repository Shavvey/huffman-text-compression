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

void minHeapify(hff::MinHeap *minHeap, int index) {
  int smallest = index;
  // given left child based on the passed index
  int left = 2 * index + 1;
  // given right child based on the passewd index
  int right = 2 * index + 2;
  if (left < minHeap->size &&
      minHeap->array[left]->freq < minHeap->array[smallest]->freq)
    smallest = left;

  if (right < minHeap->size &&
      minHeap->array[right]->freq < minHeap->array[smallest]->freq)
    smallest = right;

  if (smallest != index) {
    swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[index]);
    minHeapify(minHeap, smallest);
  }
}
// helper function to query whether size of the heap is one
int isSizeOne(hff::MinHeap *minHeap) { return minHeap->size == 1; }

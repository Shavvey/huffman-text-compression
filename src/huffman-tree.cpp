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
bool isSizeOne(hff::MinHeap *minHeap) { return minHeap->size == 1; }

hff::MinHeapNode *extractMin(hff::MinHeap *minHeap) {
  hff::MinHeapNode *top = minHeap->array[0];
  // throw heap node at the top of heap and call heapify
  minHeap->array[0] = minHeap->array[minHeap->size - 1];
  // decrement size of heap
  --minHeap->size;
  minHeapify(minHeap, 0);

  return top;
}
// standard function to insert a new node inside a heap given a root entry point
void insertMinHeap(hff::MinHeap *minHeap, hff::MinHeapNode *minHeapNode) {
  ++minHeap->size;
  int i = minHeap->size - 1;
  while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {

    minHeap->array[i] = minHeap->array[(i - 1) / 2];
    i = (i - 1) / 2;
  }

  minHeap->array[i] = minHeapNode;
}

// build minHeap given a root entry point, standard function
void buildMinHeap(hff::MinHeap *minHeap) {
  int n = minHeap->size - 1;
  int i;
  for (i = (n - 1) / 2; i >= 0; --i) {
    minHeapify(minHeap, i);
  }
}

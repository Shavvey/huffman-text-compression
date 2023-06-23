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
// helper function to helper print out the contents of the array
void printArr(int arr[], int n) {
  for (int i = 0; i < n; i++) {
    std::cout << arr[i];
  }
  std::cout << "\n";
}
// helper function to see whether is given node is a leaf inside the heap
bool isLeaf(hff::MinHeapNode *current) {
  return !(current->left) && !(current->right);
}

// creates a min heap of capacity
// equal to size and inserts all character of data[]
hff::MinHeap *createAndBuildHeap(char data[], int freq[], int size) {
  hff::MinHeap *minHeap = createMinHeap(size);
  for (int i = 0; i < size; ++i) {
    minHeap->array[i] = newNode(data[i], freq[i]);
  }
  minHeap->size = size;
  buildMinHeap(minHeap);
  return minHeap;
}

// main function to build huffman tree
hff::MinHeapNode *buildHuffmanTree(char data[], int freq[], int size) {
  hff::MinHeapNode *left, *right, *top;
  // create min heap of capacity equal to size
  hff::MinHeap *minHeap = createAndBuildHeap(data, freq, size);
  // iterate until we reach a size of 1 for the heap
  while (!isSizeOne(minHeap)) {
    // extract the two minimums
    left = extractMin(minHeap);
    right = extractMin(minHeap);
    // $ is special value used for intermediate nodes that don't encode for
    // chars
    top = newNode('$', left->freq + right->freq);
    top->left = left;
    top->right = right;
    insertMinHeap(minHeap, top);
  }
  // the remaing node should be the root node of the tree
  return extractMin(minHeap);
}
void printCodes(hff::MinHeapNode *root, int arr[], int top) {
  // assign 0 to left edges and recurse
  if (root->left) {
    arr[top] = 0;
    printCodes(root->left, arr, top++);
  }
  // assign 1 to right edge and recurse
  if (root->right) {
    arr[top] = 1;
    printCodes(root->right, arr, top++);
  }
  // if encountering a leaf node then print the character and its codes using
  // arr[]
  if (isLeaf(root)) {
    std::cout << root->charIn << ": ";
    printArr(arr, top);
  }
}

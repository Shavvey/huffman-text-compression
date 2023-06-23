#include "huffman-tree.hpp"
#include <cstdlib>
#include <iostream>
using namespace std;

// This constant can be avoided by explicitly
// calculating height of Huffman Tree
#define MAX_TREE_HT 100

// A utility function allocate a new
// min heap node with given character
// and frequency of the character
struct hff::MinHeapNode *hff::newNode(char data, unsigned freq) {
  struct MinHeapNode *temp =
      (struct hff::MinHeapNode *)malloc(sizeof(struct MinHeapNode));

  temp->left = temp->right = NULL;
  temp->data = data;
  temp->freq = freq;

  return temp;
}

// A utility function to create
// a min heap of given capacity
struct hff::MinHeap *createMinHeap(unsigned capacity)

{

  struct hff::MinHeap *minHeap =
      (struct hff::MinHeap *)malloc(sizeof(struct hff::MinHeap));

  // current size is 0
  minHeap->size = 0;

  minHeap->capacity = capacity;

  minHeap->array = (struct hff::MinHeapNode **)malloc(
      minHeap->capacity * sizeof(struct MinHeapNode *));
  return minHeap;
}

void hff::swapMinHeapNode(struct hff::MinHeapNode **a,
                          struct hff::MinHeapNode **b) {

  struct hff::MinHeapNode *t = *a;
  *a = *b;
  *b = t;
}

// The standard minHeapify function.
void hff::minHeapify(struct hff::MinHeap *minHeap, int index)

{

  int smallest = index;
  int left = 2 * index + 1;
  int right = 2 * index + 2;

  if (left < minHeap->size &&
      minHeap->array[left]->freq < minHeap->array[smallest]->freq)
    smallest = left;

  if (right < minHeap->size &&
      minHeap->array[right]->freq < minHeap->array[smallest]->freq)
    smallest = right;

  if (smallest != index) {
    hff::swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[index]);
    hff::minHeapify(minHeap, smallest);
  }
}

// A utility function to check
// if size of heap is 1 or not
bool hff::isSizeOne(struct hff::MinHeap *minHeap) {
  return (minHeap->size == 1);
}

// A standard function to extract
// minimum value node from heap
struct hff::MinHeapNode *extractMin(struct hff::MinHeap *minHeap)

{

  struct hff::MinHeapNode *temp = minHeap->array[0];
  minHeap->array[0] = minHeap->array[minHeap->size - 1];

  --minHeap->size;
  minHeapify(minHeap, 0);

  return temp;
}

// A utility function to insert
// a new node to Min Heap
void hff::insertMinHeap(struct hff::MinHeap *minHeap,
                        struct hff::MinHeapNode *minHeapNode)

{

  ++minHeap->size;
  int i = minHeap->size - 1;

  while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {

    minHeap->array[i] = minHeap->array[(i - 1) / 2];
    i = (i - 1) / 2;
  }

  minHeap->array[i] = minHeapNode;
}

// A standard function to build min heap
void hff::buildMinHeap(struct hff::MinHeap *minHeap)

{

  int n = minHeap->size - 1;
  int i;

  for (i = (n - 1) / 2; i >= 0; --i)
    hff::minHeapify(minHeap, i);
}

// A utility function to print an array of size n
void hff::printArr(int arr[], int n) {
  int i;
  for (i = 0; i < n; ++i)
    cout << arr[i];

  cout << "\n";
}

// Utility function to check if this node is leaf
bool hff::isLeaf(struct MinHeapNode *root)

{

  return !(root->left) && !(root->right);
}

// Creates a min heap of capacity
// equal to size and inserts all character of
// data[] in min heap. Initially size of
// min heap is equal to capacity
struct hff::MinHeap *hff::createAndBuildMinHeap(char data[], int freq[],
                                                int size)

{

  struct hff::MinHeap *minHeap = hff::createMinHeap(size);

  for (int i = 0; i < size; ++i)
    minHeap->array[i] = hff::newNode(data[i], freq[i]);

  minHeap->size = size;
  buildMinHeap(minHeap);

  return minHeap;
}

// The main function that builds Huffman tree
struct hff::MinHeapNode *hff::buildHuffmanTree(char data[], int freq[],
                                               int size)

{
  struct hff::MinHeapNode *left, *right, *top;

  struct hff::MinHeap *minHeap = hff::createAndBuildMinHeap(data, freq, size);

  // Iterate while size of heap doesn't become 1
  while (!hff::isSizeOne(minHeap)) {

    // freq items from min heap
    left = hff::extractMin(minHeap);
    right = hff::extractMin(minHeap);

    top = hff::newNode('$', left->freq + right->freq);

    top->left = left;
    top->right = right;

    hff::insertMinHeap(minHeap, top);
  }

  return hff::extractMin(minHeap);
}

void hff::printCodes(struct hff::MinHeapNode *root, int arr[], int top)

{

  // Assign 0 to left edge and recur
  if (root->left) {

    arr[top] = 0;
    hff::printCodes(root->left, arr, top + 1);
  }

  // Assign 1 to right edge and recur
  if (root->right) {

    arr[top] = 1;
    hff::printCodes(root->right, arr, top + 1);
  }

  if (hff::isLeaf(root)) {

    cout << root->data << ": ";
    printArr(arr, top);
  }
}

void hff::huffmanCodes(char data[], int freq[], int size)

{
  // Construct Huffman Tree
  struct MinHeapNode *root = hff::buildHuffmanTree(data, freq, size);

  // Print Huffman codes using
  // the Huffman tree built above
  int arr[MAX_TREE_HT], top = 0;

  hff::printCodes(root, arr, top);
}

// Driver code
int main() {

  char arr[] = {'a', 'b', 'c', 'd', 'e', 'f'};
  int freq[] = {5, 9, 12, 13, 16, 45};

  int size = sizeof(arr) / sizeof(arr[0]);

  hff::huffmanCodes(arr, freq, size);

  return 0;
}

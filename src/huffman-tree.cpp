#include "huffman-tree.hpp"
using namespace hff;

struct hff::MinHeapNode *hff::newNode(char data, unsigned freq) {
  struct MinHeapNode *node =
      (struct hff::MinHeapNode *)malloc(sizeof(struct MinHeapNode));

  node->left = node->right = NULL;
  node->data = data;
  node->freq = freq;

  return node;
}

// A utility function to create
// a min heap of given capacity
struct hff::MinHeap *hff::createMinHeap(unsigned capacity) {
  // entry pointer to minHeap, should be the root
  struct hff::MinHeap *minHeap =
      (struct hff::MinHeap *)malloc(sizeof(struct hff::MinHeap));

  // current size is 0
  minHeap->size = 0;

  minHeap->capacity = capacity;

  minHeap->array = (struct hff::MinHeapNode **)malloc(
      minHeap->capacity * sizeof(struct MinHeapNode *));
  return minHeap;
}
// helper function to swap the pointers of two references to nodes stored on the
// minHeap
void hff::swapMinHeapNode(struct hff::MinHeapNode **first,
                          struct hff::MinHeapNode **second) {
  // first create a temp variable to stored a single pointer
  struct hff::MinHeapNode *temp = *first;
  // swap the first pointer with the second pointer
  *first = *second;
  // swap the second pointer, stored inside temp. with the first pointer
  *second = temp;
}

// The standard minHeapify function
void hff::minHeapify(struct hff::MinHeap *minHeap, int index) {
  // initialize smallest value to the current index
  int smallest = index;
  // compute the left child of the indexed heap node
  int left = 2 * index + 1;
  // compute the right child of the inedex heap node
  int right = 2 * index + 2;

  if (left < minHeap->size &&
      minHeap->array[left]->freq < minHeap->array[smallest]->freq)
    smallest = left;

  if (right < minHeap->size &&
      minHeap->array[right]->freq < minHeap->array[smallest]->freq)
    smallest = right;

  if (smallest != index) {
    // swap nodes and call heapify
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
struct hff::MinHeapNode *hff::extractMin(struct hff::MinHeap *minHeap) {

  struct hff::MinHeapNode *temp = minHeap->array[0];
  minHeap->array[0] = minHeap->array[minHeap->size - 1];

  --minHeap->size;
  minHeapify(minHeap, 0);

  return temp;
}

// A utility function to insert
// a new node to Min Heap
void hff::insertMinHeap(struct hff::MinHeap *minHeap,
                        struct hff::MinHeapNode *minHeapNode) {

  // increment size of heap
  ++minHeap->size;
  int i = minHeap->size - 1;

  while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {

    minHeap->array[i] = minHeap->array[(i - 1) / 2];
    i = (i - 1) / 2;
  }
  minHeap->array[i] = minHeapNode;
}

// A standard function to build min heap
void hff::buildMinHeap(struct hff::MinHeap *minHeap) {

  int n = minHeap->size - 1;
  int i;

  for (i = (n - 1) / 2; i >= 0; --i)
    hff::minHeapify(minHeap, i);
}

// A utility function to print an array of size n
void hff::printArr(int arr[], int n) {
  for (int i = 0; i < n; ++i)
    std::cout << arr[i];

  std::cout << "\n";
}

// Utility function to check if this node is leaf
bool hff::isLeaf(struct MinHeapNode *root) {
  return !(root->left) && !(root->right);
}

// Creates a min heap of a given capacity
struct hff::MinHeap *hff::createAndBuildMinHeap(char data[], int freq[],
                                                int size) {

  struct hff::MinHeap *minHeap = hff::createMinHeap(size);

  for (int i = 0; i < size; ++i)
    minHeap->array[i] = hff::newNode(data[i], freq[i]);

  minHeap->size = size;
  // build heap from the given character and frequency data
  hff::buildMinHeap(minHeap);

  return minHeap;
}

// The main function that builds Huffman tree
struct hff::MinHeapNode *hff::buildHuffmanTree(char data[], int freq[],
                                               int size) {
  struct hff::MinHeapNode *left, *right, *top;

  // created pointer should be the root, the entry point into the min heap
  struct hff::MinHeap *minHeap = hff::createAndBuildMinHeap(data, freq, size);

  // Iterate while size of heap doesn't become 1
  while (!hff::isSizeOne(minHeap)) {

    // freq items from min heap
    left = hff::extractMin(minHeap);
    right = hff::extractMin(minHeap);
    // $ is special character used to mark intermediate nodes in the heap
    // thes intermediate nodes do not code for any characters
    top = hff::newNode('$', left->freq + right->freq);

    top->left = left;
    top->right = right;

    hff::insertMinHeap(minHeap, top);
  }

  return hff::extractMin(minHeap);
}

void hff::printCodes(struct hff::MinHeapNode *root, int arr[], int top) {

  // assign 0 to left edge and recur
  if (root->left) {

    arr[top] = 0;
    // recurse using the left edge?
    hff::printCodes(root->left, arr, top + 1);
  }

  // assign 1 to right edge and recur
  if (root->right) {

    arr[top] = 1;
    // recurse using the right edge?
    hff::printCodes(root->right, arr, top + 1);
  }

  if (hff::isLeaf(root)) {

    std::cout << root->data << ": ";
    printArr(arr, top);
  }
}

void hff::huffmanCodes(char data[], int freq[], int size) {
  // construct Huffman Tree using frequency and character data
  struct MinHeapNode *root = hff::buildHuffmanTree(data, freq, size);

  // print Huffman codes using
  // the Huffman tree built above
  int arr[MAX_TREE_HEIGHT], top = 0;

  // print codes from constructed huffman tree
  hff::printCodes(root, arr, top);
}
// simple helper function to find the largest of two numbers
int max(int a, int b) { return (a > b) ? a : b; }
// another helper function used in string representation of binary-tree
int hff::power(int base, int exponent) {
  // i really like ternary operators
  return (exponent != 0) ? base * power(base, exponent - 1) : 1;
}
int hff::maxDepth(hff::MinHeapNode *root) {
  if (root == NULL) {
    return 0;
  }
  int left_depth = maxDepth(root->left);
  int right_depth = maxDepth(root->right);
  // compare left and left depth values
  int max_val = max(left_depth, right_depth);
  return max_val + 1;
}
// recursive path from the tree how far left and right we need to index into
// the 2D character array
void hff::pathRecursive(hff::MinHeapNode *root, char ***res, int d, int depth,
                        int left, int right) {
  // if recursive path hits a branch (or root isnt created) or is past the max
  // depth we return out of the function call
  if (root == NULL || d == depth) {
    // early return if root passed does not exist
    return;
  }
  // calculate mid point, used to move left and right based on the midpoint of
  // each node
  int mid = (left + right) / 2;
  res[d][mid] = (char *)malloc(sizeof(char) * 4);
  snprintf(res[d][mid], 100, "%c", root->data);
  hff::pathRecursive(root->left, res, d + 1, depth, left, mid - 1);
  hff::pathRecursive(root->right, res, d + 1, depth, mid + 1, right);
}
// gets a string representation of the tree
// its pretty ugly but it works!
char ***hff::printTree(hff::MinHeapNode *root) {
  int depth = maxDepth(root);
  int width = power(depth, 2) - 1;

  int *return_size = &depth;
  // init the 2 dimensional character array, based on depth and width calc
  char ***res = (char ***)malloc(sizeof(char **) * depth);
  for (int i = 0; i < depth; i++) {
    res[i] = (char **)malloc(sizeof(char *) * width);
    for (int j = 0; j < width; j++) {
      res[i][j] = (char *)" ";
    }
  }
  // take recursive path through binary tree
  hff::pathRecursive(root, res, 0, depth, 0, width - 1);
  return res;
}
// print current tree as a 2D string representation
void hff::printCurrentTree(hff::MinHeapNode *root) {
  int depth = maxDepth(root);
  int width = power(depth, 2) - 1;
  int *return_size;
  //  create the 2D representation of the character array
  char ***out = printTree(root);
  // traverse through array and print out result
  for (int i = 0; i < depth; i++) {
    for (int j = 0; j < width; j++) {
      printf("%s", out[i][j]);
    }
    printf("\n");
  }
}
// class method implementaing of printing the huffman tree
// this is just pretty much a rewrite of printCurrentTree
// but as a method
void hff::HuffmanTree::printHuffmanTree() {
  int depth = maxDepth(root);
  int width = power(depth, 2) - 1;
  int *return_size;
  //  create the 2D representation of the character array
  char ***out = printTree(root);
  // traverse through array and print out result
  for (int i = 0; i < depth; i++) {
    for (int j = 0; j < width; j++) {
      printf("%s", out[i][j]);
    }
    printf("\n");
  }
}

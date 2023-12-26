#include "huffman-tree.hpp"
// include the namespace so i dont have to keep referencing it
using namespace hff;

hff::MinHeapNode *hff::newNode(char data, unsigned int freq) {
  // allocate memory on the heap to store a new node
  MinHeapNode *node = new MinHeapNode;
  // assign fields of newly allocated node based on args
  node->left = node->right = NULL;
  // set data field using the passed arg
  node->data = data;
  // set freq field using the passed arg
  node->freq = freq;
  // return new node so that it can be added to minHeap
  return node;
}

// A utility function to create
// a min heap of given capacity
hff::MinHeap *hff::createMinHeap(unsigned capacity) {
  // entry pointer to minHeap, should be the root
  // allcoate memory for minHeap onto the heap
  hff::MinHeap *minHeap = new MinHeap;
  // size initially is 0 when the min heap is created
  minHeap->size = 0;
  // capacity of the minheap, this tells use how much space we need to allocate
  // using malloc
  minHeap->capacity = capacity;
  // allocate memory to min heap array based on total capacity given
  minHeap->array =
      // a simple array of pointers to keep track of all the allocations
      (hff::MinHeapNode **)malloc(minHeap->capacity * sizeof(MinHeapNode *));
  // array chould possibly be deleted in a destructor later
  return minHeap;
}
// helper function to swap the pointers of two references to nodes stored on the
// minHeap
void hff::swapMinHeapNode(hff::MinHeapNode **first, hff::MinHeapNode **second) {
  // first create a temp variable to stored a single pointer
  struct hff::MinHeapNode *temp = *first;
  // swap the first pointer with the second pointer
  *first = *second;
  // swap the second pointer, stored inside temp. with the first pointer
  *second = temp;
}

// The standard minHeapify function
void hff::minHeapify(hff::MinHeap *minHeap, int index) {
  // initialize smallest value to the current index
  int smallest = index;
  // compute the left child of the indexed heap node
  int left = 2 * index + 1;
  // compute the right child of the inedex heap node
  int right = 2 * index + 2;
  // using size as a sentinel value, while preforming swaps down the tree if
  // needed
  if (left < minHeap->size &&
      minHeap->array[left]->freq < minHeap->array[smallest]->freq) {
    smallest = left;
  }
  if (right < minHeap->size &&
      minHeap->array[right]->freq < minHeap->array[smallest]->freq) {
    smallest = right;
  }

  if (smallest != index) {
    // swap nodes and call heapify
    hff::swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[index]);
    hff::minHeapify(minHeap, smallest);
  }
}

// A utility function to check
// if size of heap is 1 or not
bool hff::isSizeOne(hff::MinHeap *minHeap) { return (minHeap->size == 1); }

// A standard function to extract
// minimum value node from heap
hff::MinHeapNode *hff::extractMin(hff::MinHeap *minHeap) {

  hff::MinHeapNode *temp = minHeap->array[0];
  minHeap->array[0] = minHeap->array[minHeap->size - 1];

  // NOTE: look at documentation for extract min
  --minHeap->size;
  // heapify the root node after extraction is performed
  minHeapify(minHeap, 0);

  return temp;
}

// A utility function to insert
// a new node to Min Heap
void hff::insertMinHeap(hff::MinHeap *minHeap, hff::MinHeapNode *minHeapNode) {

  // increment size of heap
  ++minHeap->size;
  int i = minHeap->size - 1;

  while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {

    minHeap->array[i] = minHeap->array[(i - 1) / 2];
    // look up parent node
    i = (i - 1) / 2;
  }
  minHeap->array[i] = minHeapNode;
}
// get parent from its child
int hff::getParent(int child) { return (child - 1) / 2; }
// get left child from parent
int hff::getLeftChild(int parent) { return 2 * parent + 1; }
// get right child from parent
int hff::getRightChild(int parent) { return 2 * parent; }

// A standard function to build min heap
void hff::buildMinHeap(hff::MinHeap *minHeap) {

  int n = minHeap->size - 1;
  for (int i = (n - 1) / 2; i >= 0; --i)
    hff::minHeapify(minHeap, i);
}

// A utility function to print an array of size n
void hff::printArr(int arr[], int n) {
  for (int i = 0; i < n; ++i)
    std::cout << arr[i];

  std::cout << "\n";
}
// sum an array that is meant to represent a binary array
// it returns a decimalized sum based on the binary digit
// represented by the array
int hff::sumArr(int arr[], int n) {
  int sum = 0;
  for (int i = 0; i < n; ++i) {
    sum = sum + arr[i] * (power(2, n - i - 1));
  }
  return sum;
}

// Utility function to check if this node is leaf
bool hff::isLeaf(hff::MinHeapNode *root) {
  // if node a is a leaf, by definition it has no children
  return !(root->left) && !(root->right);
}

// Creates a min heap of a given capacity
hff::MinHeap *hff::createAndBuildMinHeap(char data[], int freq[], int size) {

  hff::MinHeap *minHeap = hff::createMinHeap(size);

  for (int i = 0; i < size; ++i) {
    minHeap->array[i] = hff::newNode(data[i], freq[i]);
  }

  minHeap->size = size;
  // build heap from the given character and frequency data
  hff::buildMinHeap(minHeap);

  return minHeap;
}

// The main function that builds Huffman tree
hff::MinHeapNode *hff::buildHuffmanTree(char data[], int freq[], int size) {
  hff::MinHeapNode *left, *right, *top;

  // created pointer should be the root, the entry point into the min heap
  hff::MinHeap *minHeap = hff::createAndBuildMinHeap(data, freq, size);

  // Iterate while size of heap doesn't become 1
  while (!hff::isSizeOne(minHeap)) {

    // freq items from min heap
    left = hff::extractMin(minHeap);
    right = hff::extractMin(minHeap);
    // $ is special character used to mark intermediate nodes in the heap
    // these intermediate nodes do not code for any characters
    top = hff::newNode('$', left->freq + right->freq);

    top->left = left;
    top->right = right;

    hff::insertMinHeap(minHeap, top);
  }

  return hff::extractMin(minHeap);
}

// recursive function to navigate the leafs of minheap node and print out the
// weighting of encoded characters
void hff::printCodes(hff::MinHeapNode *root, int arr[], int top) {

  // assign 0 to left edge and recurse
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
    hff::printArr(arr, top);
  }
}

void hff::huffmanCodes(char data[], int freq[], int size) {
  // construct Huffman Tree using frequency and character data
  MinHeapNode *root = hff::buildHuffmanTree(data, freq, size);

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
// compute the max depth of a given node using recursion
int hff::maxDepth(hff::MinHeapNode *root) {
  if (root == NULL) {
    return 0;
  }
  // recurse down the left tree
  int left_depth = maxDepth(root->left);
  // recurse down the right tree
  int right_depth = maxDepth(root->right);
  // compare left and right depth values
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
    // or max depth is reached
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
std::string hff::minHeapToString(hff::MinHeapNode *root) {
  // probably should raise an error?
  if (!root) {
    return "";
  }
  // building a
  std::string s = "";
  // create a queue of node pointers to build the string
  std::queue<hff::MinHeapNode *> q;
  q.push(root);
  while (!q.empty()) {
    hff::MinHeapNode *currentNode = q.front();
    q.pop();
    if (currentNode == NULL) {
      // if current node is null append '#'
      // which is a special character used to indication a null pointer, when
      // rebuilding the heap from a given string
      s.append("#");
    } else {
      // printf("%c\n", currentNode->data);
      s.push_back(currentNode->data);
    }
    if (currentNode != NULL) {
      q.push(currentNode->left);
      q.push(currentNode->right);
    }
  }
  // null terminate the string
  s.push_back('\0');
  // print the string to standard output, this is just for testing purposes
  std::cout << s << std::endl;
  return s;
}

hff::MinHeapNode *hff::minHeapFromString(std::string data) {
  if (data.size() == 0) {
    return NULL;
  }
  // using a stringstream to iterate over the string and get each character
  std::stringstream s(data);
  char c;
  // get another character from stringstream
  c = s.get();
  // since we don't need the frequency data after the heap is constructed
  // each of the frequncy values are just set to 0
  hff::MinHeapNode *root = hff::newNode(c, 0);
  std::queue<hff::MinHeapNode *> q;
  q.push(root);
  while (!q.empty()) {
    hff::MinHeapNode *node = q.front();
    q.pop();
    // get another character from the string stream
    c = s.get();
    // if "#" is present then children should be null
    if (c == '#') {
      node->left = NULL;
    } else {
      // create new left node and push it onto the queue
      hff::MinHeapNode *leftNode = hff::newNode(c, 0);
      node->left = leftNode;
      q.push(leftNode);
    }
    c = s.get();
    if (c == '#') {
      node->right = NULL;
    } else {
      // create and new right node and push it onto the queue
      hff::MinHeapNode *rightNode = hff::newNode(c, 0);
      node->right = rightNode;
      q.push(rightNode);
    }
  }
  return root;
}
SerializedMinHeap hff::serializeFromString(std::string heapString) {
  // struct that contains all the information stored inside minHeap,
  // this will be stored inside the compress textfile,
  // so that the uncompressed file can be recovered
  SerializedMinHeap serialHeap;
  std::stringstream s(heapString);
  int size = 0;
  // holds each char of the serialized min heap string
  unsigned char data = '\n';
  // create a vector that will be the serialized version of heap
  // afterward will will use this to write information to file about the
  // compressed text
  std::vector<std::byte> serializedBytes;
  while (data != '\0') {
    // get a character from the stringstream
    data = s.get();
    std::byte bytes = std::byte(data);
    serializedBytes.push_back(bytes);
    size++;
  }
  serialHeap.size = size;
  serialHeap.data = serializedBytes;
  return serialHeap;
}
void hff::printBytes(hff::SerializedMinHeap minHeap) {
  for (auto itr = minHeap.data.begin(); itr != minHeap.data.end(); ++itr) {
    // print out hexadecimal string
    printf("%hhx", static_cast<unsigned char>(*itr));
  }
  // print newline
  printf("\n");
}

// root-right-left
// print out a simple in order traversal of the tree, given its root
void hff::printInOrder(hff::MinHeapNode *root) {
  if (root == NULL) {
    return;
  }
  hff::printInOrder(root->left);
  printf(" %c", root->data);
  hff::printInOrder(root->right);
}

// root-left-right
// print out tree in a pre order fashion
void hff::printPreOrder(hff::MinHeapNode *root) {
  if (root == NULL) {
    return;
  }
  printf(" %c", root->data);
  hff::printInOrder(root->left);
  hff::printPreOrder(root->right);
}
// left-right-root
// prints out tree in a post order fashion
void hff::printPostOrder(hff::MinHeapNode *root) {
  if (root == NULL) {
    return;
  }
  hff::printPostOrder(root->left);
  hff::printPostOrder(root->right);
  printf(" %c", root->data);
}
char hff::HuffmanTree::huffmanDecode(std::string bitString) {
  // cast bit string to a stream of characters
  std::stringstream s(bitString);
  hff::MinHeapNode *current = root;
  char data;
  // get the first character
  char c = s.get();
  // we can continue looping until the end of file is reached
  for (int i = 0; i < bitString.length(); i++) {
    if (c == '1') {
      data = (isLeaf(root)) ? current->data : '\0';
      // traverse to right sub tree
      current = current->right;
    } else if (c == '0') {
      data = (isLeaf(root)) ? current->data : '\0';
      // travserse to left sub tree
      current = current->left;
    }
    // get another character
    c = s.get();
  }
  return data;
}
// simple method to return the huffman code from a given char
struct huffCode hff::HuffmanTree::huffmanEncode(char charEncoded) {
  struct huffCode code = huffmanCodes[charEncoded];
  return code;
}

void hff::HuffmanTree::populateCharCodes(hff::MinHeapNode *root,
                                         int arr[MAX_TREE_HEIGHT], int top) {

  // if the left child exists, recurse down left subtree
  if (root->left) {

    arr[top] = 0;
    // each step along the left is represented with a 0
    hff::HuffmanTree::populateCharCodes(root->left, arr, top + 1);
  }

  //  if the right child exists, recurse down the right subtree
  if (root->right) {

    arr[top] = 1;
    // each step along the right is represented with a 1
    hff::HuffmanTree::populateCharCodes(root->right, arr, top + 1);
  }

  if (hff::isLeaf(root)) {
    struct huffCode code;
    code.sum = hff::sumArr(arr, top);
    code.size = top;
    huffmanCodes[root->data] = code;
    printf("Data stored: %d\n", huffmanCodes[root->data].sum);
  }
}

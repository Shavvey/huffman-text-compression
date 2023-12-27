// create only one header file definition
#pragma once
/*IMPORTS*/
#include <cstddef>
#include <string>
#include <unordered_map>
#include <vector>

// name spacing all the huffman libraries because i really like typing :: in
// every single line of code
namespace hff {
#define MAX_TREE_HEIGHT 256
/*DEFINITIONS*/
struct MinHeapNode {
  // input character for
  char data;
  // its frequency inside a given text file
  unsigned freq;
  // left and right references to nodes inside the huffman tree
  MinHeapNode *right;
  MinHeapNode *left;
};

struct MinHeap {
  // current size of min heap
  unsigned size;
  // capacity of min heap
  unsigned capacity;
  // array of minHeap node pointers
  struct MinHeapNode **array;
};

// just a simple struct to represent the huffman code
struct huffCode {
  int sum;
  int size;
};

// new struct to carry the serialized version of the min heap
struct SerializedMinHeap {
  int size;
  // using a vector that contains each byte
  std::vector<std::byte> data;
};

/*FUNCTION PROTOTYPING*/
hff::MinHeapNode *newNode(char, unsigned);
hff::MinHeap *createMinHeap(unsigned);
hff::MinHeapNode *extractMin(hff::MinHeap *minHeap);
void swapMinHeapNode(hff::MinHeapNode **, hff::MinHeapNode **);
void minHeapify(hff::MinHeap *, int);
bool isSizeOne(hff::MinHeap *);
void insertMinHeap(hff::MinHeap *, hff::MinHeapNode *);
void buildMinHeap(hff::MinHeap *);
void printArr(int[], int);
bool isLeaf(hff::MinHeapNode *);
hff::MinHeap *createAndBuildMinHeap(char *, int *, int);
hff::MinHeapNode *buildHuffmanTree(char *, int *, int);
void printCodes(hff::MinHeapNode *, int *, int);
void huffmanCodes(char *, int *, int);
int maxDepth(hff::MinHeapNode *);
void pathRecursive(hff::MinHeapNode *, char ***, int, int, int, int);
char ***printTree(hff::MinHeapNode *);
void printCurrentTree(hff::MinHeapNode *);
int power(int, int);
std::string minHeapToString(hff::MinHeapNode *);
hff::MinHeapNode *minHeapFromString(std::string);
void printBytes(hff::SerializedMinHeap);
hff::SerializedMinHeap serializeFromString(std::string);
void printInOrder(hff::MinHeapNode *);
void printPreOrder(hff::MinHeapNode *);
void printPostOrder(hff::MinHeapNode *);
int getParent(int);
int getLeftChild(int);
int getRightChild(int);
int sumArr(int *, int);
void deleteTree(hff::MinHeapNode *root);
class HuffmanTree {
public:
  // public fields!
  hff::MinHeapNode *root;
  std::unordered_map<char, struct huffCode> huffmanCodes;
  // class methods declarations!
  void printHuffmanTree();
  char huffmanDecode(std::string);
  struct huffCode huffmanEncode(char);
  void populateCharCodes(MinHeapNode *, int[MAX_TREE_HEIGHT], int);
  // class constructor
  HuffmanTree(char *data, int *freq, int size) {
    // build to minHeap and return a reference to it inside the root
    root = hff::buildHuffmanTree(data, freq, size);
    // arr of values of character codes
    int arr[MAX_TREE_HEIGHT];
    // used in recursive call in `populateCharCodes`
    int top = 0;
    populateCharCodes(root, arr, top);
  }

  // secondary constructor where it takes the map of characters and frequencies
  HuffmanTree(std::unordered_map<char, int> fileCharFreq) {
    int const size = fileCharFreq.size();
    int freq[size];
    char chars[size];
    int k = 0;
    for (auto itr = fileCharFreq.begin(); itr != fileCharFreq.end(); itr++) {
      chars[k] = itr->first;
      freq[k] = itr->second;
      ++k;
    }
    // build huffman tree based on map of characters and their file frequencies
    root = hff::buildHuffmanTree(chars, freq, size);
  }
  // just a simple construct to convert a root into a full huffman tree
  HuffmanTree(hff::MinHeapNode *_root) { root = _root; }
};
} // namespace hff

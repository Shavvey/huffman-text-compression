// create only one header file definition
#pragma once
/*IMPORTS*/
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
// namespacing all the huffman libraries because i really like typing :: in
// every single line of code
namespace hff {
#define MAX_TREE_HEIGHT 256
/*DEFINTIONS*/
struct MinHeapNode {
  // input character for
  char data;
  // its frequency inside a given textfile
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
  // array of minheap node pointers
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
hff::MinHeap *createAndBuildMinHeap(char[], int[], int);
hff::MinHeapNode *buildHuffmanTree(char[], int[], int);
void printCodes(hff::MinHeapNode *, int[], int);
void huffmanCodes(char[], int[], int);
int maxDepth(hff::MinHeapNode *);
void pathRecursive(hff::MinHeapNode *, char ***, int, int, int, int);
char ***printTree(hff::MinHeapNode *);
void printCurrentTree(hff::MinHeapNode *);
int power(int, int);
std::string minHeapToString(hff::MinHeapNode *);
hff::MinHeapNode *minHeapFromString(std::string);
void printBytes(hff::SerializedMinHeap);
hff::SerializedMinHeap serializeFromString(std::string);
// giving up on string simplification for now
// std::string postProcessString(std::string);
// std::string preProcessString(std::string);
void printInOrder(hff::MinHeapNode *);
void printPreOrder(hff::MinHeapNode *);
void printPostOrder(hff::MinHeapNode *);
int getParent(int);
int sumArr(int *, int);
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
};
} // namespace hff

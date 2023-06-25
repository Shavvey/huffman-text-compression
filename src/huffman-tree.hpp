// create only one header file definition
#pragma once
/*IMPORTS*/
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
// namespacing all the huffman libraries because i really like typing :: in
// every single line of code
namespace hff {

#define MAX_TREE_HEIGHT 100

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
/*FUNCTION PROTOTYPING*/
hff::MinHeapNode *newNode(char, unsigned);
hff::MinHeap *createMinHeap(unsigned);
hff::MinHeapNode *extractMin(struct hff::MinHeap *minHeap);
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
class HuffmanTree {
public:
  // public fields!
  hff::MinHeapNode *root;
  HuffmanTree(char *data, int *freq, int size) {
    root = hff::buildHuffmanTree(data, freq, size);
  }
  // class methods declarations!
  void printHuffmanTree();
};
} // namespace hff

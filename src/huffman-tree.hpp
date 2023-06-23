// create only one header file definition
#pragma once
/*IMPORTS*/
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
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
/*FUNCTION PROTOTYPING*/
struct hff::MinHeapNode *newNode(char, unsigned);
struct hff::MinHeap *createMinHeap(unsigned);
hff::MinHeapNode *extractMin(hff::MinHeap *minHeap);
void swapMinHeapNode(hff::MinHeapNode **, hff::MinHeapNode **);
void minHeapify(hff::MinHeap *, int);
bool isSizeOne(hff::MinHeap *);
void insertMinHeap(hff::MinHeap *, hff::MinHeapNode *);
void buildMinHeap(hff::MinHeap *);
void printArr(int[], int);
bool isLeaf(hff::MinHeapNode *);
struct hff::MinHeap *createAndBuildMinHeap(char[], int[], int);
struct hff::MinHeapNode *buildHuffmanTree(char[], int[], int);
void printCodes(hff::MinHeapNode *, int[], int);
void huffmanCodes(char[], int[], int);
// namespace hff
// Maybe encapsulate this stuff inside a class?
class HuffmanTree {};
} // namespace hff

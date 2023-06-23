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
  unsigned char charIn;
  // its frequency inside a given textfile
  u_int32_t freq;
  // left and right references to nodes inside the huffman tree
  MinHeapNode *right;
  MinHeapNode *left;
};

struct MinHeap {
  // current size of min heap
  u_int32_t size;
  // capacity of min heap
  u_int32_t capacity;
  // array of minheap node pointers
  struct MinHeapNode **array;
};
} // namespace hff
/*FUNCTION PROTOTYPING*/
hff::MinHeapNode *newNode(char, unsigned);
hff::MinHeap *createMinHeap(unsigned);
void swapMinHeapNode(hff::MinHeapNode **, hff::MinHeapNode **);
void minHeapify(hff::MinHeap, int);
bool isSizeOne(hff::MinHeap *);
void insertMinHeap(hff::MinHeap *, hff::MinHeapNode *);
void buildMinHeap(hff::MinHeap *);
void printArr(int[], int);
bool isLeaf(hff::MinHeapNode *);
hff::MinHeap *createAndBuildHeap(char[], int[], int);
hff::MinHeapNode *buildHuffmanTree(char[], int[], int);
void printCodes(hff::MinHeapNode *, int[], int);
void huffmanCodes(char[], int[], int);
// namespace hff
// Maybe encapsulate this stuff inside a class?
class HuffmanTree {};

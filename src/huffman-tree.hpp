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
// Maybe encapsulate this stuff inside a class?
class HuffmanTree {};

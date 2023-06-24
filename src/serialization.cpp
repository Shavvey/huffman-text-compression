#include "huffman-tree.hpp"
std::string minHeapToString(hff::MinHeapNode *root) {
  // probably should raise an error?
  if (!root)
    return "";
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
      s.append(std::to_string(currentNode->data));
    }
  }
}

// class definition + function prototyping of huffman-tree!
#include "huffman-tree.hpp"
// pass char and frequency value to create a node for the huffman tree
hff::Node *insertNode(hff::HuffTree &tree, unsigned char charEncoded,
                      int freq) {
  return tree.root;
}

hff::Node *createNode(hff::HuffTree &tree) {
  if (tree.root == NULL) {
    tree.root = new hff::Node;
    return tree.root;
  } else {
    return new hff::Node;
  }
}

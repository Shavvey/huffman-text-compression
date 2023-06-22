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

/*DEFINTIONS*/
struct Node {
  // character stored by the nodes this will be used to encoded and decode a
  // textifle
  char charEncoded;
  // its frequency inside a given textfile
  int frequency;
  // left and right references to nodes inside the huffman tree
  Node *right;
  Node *left;
  // parent reference
  Node *parent;
};

// top-level class that stores each huffman binary tree
class HuffTree {
public:
  // reference to root node of created binary tree
  Node *root;
  // !! constructor !!
  HuffTree() {
    // set all references to other nodes to zero explicitly to null
    // when tree is first constructed, allocate memory to root
    // this root will serve as the entry point into the binary tree
    root = new Node;
    root->left = NULL;
    root->right = NULL;
    root->parent = NULL;
  };
};
} // namespace hff

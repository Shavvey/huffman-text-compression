// create only one header file definition
#pragma once
/*IMPORTS*/
#include <cstddef>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>

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
};

// top-level class that stores each huffman binary tree
class HuffTree {
public:
  // reference to root node of created binary tree
  Node *root;
  // !! constructor !!
  HuffTree() {
    // set all references to other nodes to zero explicitly
    // when a new tree is constructing
    root = NULL;
    root->left = NULL;
    root->right = NULL;
  };
};

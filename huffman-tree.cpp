#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>

struct HuffNode {
  char charEncoded;
  int frequency;
  HuffNode *right;
  HuffNode *left;
};

class HuffTree {
public:
  // reference to root node of created binary tree
  HuffNode *root;
};

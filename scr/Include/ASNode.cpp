#include "ASNode.h"
#include <limits>

ASNode::ASNode(int _x, int _y)
    : x(_x), y(_y), walkable(true), parent(nullptr), g(std::numeric_limits<int>::infinity()), h(0) {}

int ASNode::f() const { return g + h; }

int ASNode::get_x() const { return x; }
int ASNode::get_y() const { return y; }

void ASNode::set_walkable(bool w) { walkable = w; }
bool ASNode::get_walkable() const { return walkable; }

void ASNode::set_parent(ASNode* p) { parent = p; }
ASNode* ASNode::get_parent() const { return parent; }

int ASNode::get_g() const { return g; }
int ASNode::get_h() const { return h; }
void ASNode::set_g(int val) { g = val; }
void ASNode::set_h(int val) { h = val; }

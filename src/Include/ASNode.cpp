#include "ASNode.h"
#include <limits>

ASNode::ASNode()
    : x(0), y(0), walkable(true), parent(nullptr),
      g(std::numeric_limits<double>::infinity()),
      h(0) {}

ASNode::ASNode(int _x, int _y)
    : x(_x), y(_y), walkable(true), parent(nullptr),
      g(std::numeric_limits<double>::infinity()),
      h(0) {}

double ASNode::f() const { return g + h; }

int ASNode::get_x() const { return x; }
int ASNode::get_y() const { return y; }

bool ASNode::get_walkable() const { return walkable; }
void ASNode::set_walkable(bool w) { walkable = w; }

void ASNode::set_parent(ASNode* p) { parent = p; }
ASNode* ASNode::get_parent() const { return parent; }

void ASNode::set_g(double val) { g = val; }
void ASNode::set_h(double val) { h = val; }

double ASNode::get_g() const { return g; }
double ASNode::get_h() const { return h; }

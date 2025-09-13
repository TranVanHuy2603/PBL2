#include "ASNode.h"
#include <limits>

ASNode::ASNode(double _x, double _y)
    : x(_x), y(_y), walkable(true), parent(nullptr), g(std::numeric_limits<double>::infinity()), h(0) {}

double ASNode::f() const { return g + h; }

double ASNode::get_x() const { return x; }
double ASNode::get_y() const { return y; }

void ASNode::set_walkable(bool w) { walkable = w; }
bool ASNode::get_walkable() const { return walkable; }

void ASNode::set_parent(ASNode* p) { parent = p; }
ASNode* ASNode::get_parent() const { return parent; }

double ASNode::get_g() const { return g; }
double ASNode::get_h() const { return h; }
void ASNode::set_g(double val) { g = val; }
void ASNode::set_h(double val) { h = val; }

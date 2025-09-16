#include "ASNode.h"
#include <limits>

ASNode::ASNode() : x(0), y(0), walkable(true), parent(nullptr),
                   g(std::numeric_limits<double>::infinity()), 
                   h(std::numeric_limits<double>::infinity()) {}

ASNode::ASNode(double x, double y)
{
    this->x = x;
    this->y = y;
    this->walkable = true;
    this->parent = nullptr;
    this->g = std::numeric_limits<double>::infinity(); // INT_MAX
    this->h = 0;
}

double ASNode::f() const { return g + h; }

double ASNode::get_x() const { return x; }
double ASNode::get_y() const { return y; }

void ASNode::set_walkable(bool w) { walkable = w; }
bool ASNode::get_walkable() const { return walkable; }

void ASNode::set_parent(ASNode *p) { parent = p; }
ASNode *ASNode::get_parent() const { return parent; }

double ASNode::get_g() const { return g; }
double ASNode::get_h() const { return h; }
void ASNode::set_g(double val) { g = val; }
void ASNode::set_h(double val) { h = val; }

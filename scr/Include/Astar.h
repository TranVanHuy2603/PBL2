#pragma once
#include "ASNode.h"
#include "Quadtree.h"
#include "Vector.h"

Vector<ASNode *> return_path(ASNode *);
Vector<ASNode *> get_neighbors(ASNode *node, Vector<Vector<ASNode>> &);
void updateGridWalkable(Vector<Vector<ASNode>> &, Quadtree *qt, double = 1.0);
double heuristic(ASNode *, ASNode *);
Vector<ASNode *> astar(ASNode *, ASNode *, Quadtree *,
                       Vector<Vector<ASNode>> &, double = 1.0);

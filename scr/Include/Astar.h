#pragma once
#include "ASNode.h"
#include "Quadtree.h"

#include <vector>
using namespace std;

vector<ASNode *> return_path(ASNode *);
vector<ASNode *> get_neighbors(ASNode *node, vector<vector<ASNode>> &);
void updateGridWalkable(vector<vector<ASNode>> &, Quadtree *qt, double = 1.0);
double heuristic(ASNode *, ASNode *);
vector<ASNode *> astar(ASNode *, ASNode *, Quadtree *,
                       vector<vector<ASNode>> &, double = 1.0);

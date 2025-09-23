#include "ASNode.h"
#include "Priorityqueue.h"
#include "Entity.h"
#include "Quadtree.h"
#include <vector>
#include <set>
#include <utility>
#include <cmath>
#include <algorithm>

using namespace std;

double heuristic(ASNode *a, ASNode *b) // uoc luong khoang cach
{
    return abs(a->get_x() - b->get_x()) + abs(a->get_y() - b->get_y());
}

vector<ASNode *> return_path(ASNode *node) // tra ve duong di
{
    vector<ASNode *> path;
    while (node)
    {
        path.push_back(node);
        node = node->get_parent();
    }
    reverse(path.begin(), path.end());
    return path;
}

vector<ASNode *> get_neighbors(ASNode *node, vector<vector<ASNode>> &grid)
{
    vector<ASNode *> neighbors;
    double dx[8] = {-1, 1, 0, 0, -1, -1, 1, 1};
    double dy[8] = {0, 0, -1, 1, 1, -1, -1, 1};
    double w = grid.size();
    double h = grid[0].size();

    for (int i = 0; i < 8; i++)
    {
        double nx = node->get_x() + dx[i];
        double ny = node->get_y() + dy[i];
        if (nx >= 0 && ny >= 0 && nx < w && ny < h && grid[nx][ny].get_walkable())
            neighbors.push_back(&grid[nx][ny]);
    }
    return neighbors;
}

struct CompareASNode
{ // ham so sanh
    bool operator()(ASNode *a, ASNode *b) const
    {
        return a->f() < b->f();
    }
};

void updateGridWalkable(vector<vector<ASNode>> &grid, Quadtree *qt, double cellSize)
{
    Vector<Entity *> entities;
    qt->query(Rect(0, 0, grid.size() * cellSize, grid[0].size() * cellSize), entities);

    for (Entity *e : entities)
    {
        if (!e->is_walkable())
        {
            double gx = e->get_x() / cellSize;
            double gy = e->get_y() / cellSize;

            if (gx >= 0 && gy >= 0 && gx < grid.size() && gy < grid[0].size())
                grid[gx][gy].set_walkable(false);
        }
    }
}

vector<ASNode *> astar(ASNode *start, ASNode *goal, Quadtree *qt,
                       vector<vector<ASNode>> &grid, double cellSize = 1.0)
{
    updateGridWalkable(grid, qt, cellSize);

    Priorityqueue<ASNode *, CompareASNode> openSet;
    set<ASNode *> closeSet;

    start->set_g(0);
    start->set_h(heuristic(start, goal));
    openSet.push(start);

    while (!openSet.isEmpty())
    {
        ASNode *cur = openSet.top();
        openSet.pop();

        if (cur == goal)
            return return_path(cur); // tim thay duong di, tra ve duong di

        closeSet.insert(cur); // them node vao danh sach da xet

        // lay cac node hang xom
        vector<ASNode *> neighbors = get_neighbors(cur, grid);

        for (ASNode *n : neighbors)
        {
            if (closeSet.count(n))
                continue; // neu da xet thi bo qua

            double tentative_g = cur->get_g() + 1; // chi phi di chuyen tu cur den n (4 huong)

            // neu node chua co trong openSet hoac chi phi nho hon thi cap nhat
            if (tentative_g < n->get_g())
            {
                n->set_parent(cur);           // cap nhat node cha
                n->set_g(tentative_g);        // cap nhat g
                n->set_h(heuristic(n, goal)); // cap nhat h

                // neu node chua co trong openSet thi them vao
                if (find(openSet.getHeap().begin(), openSet.getHeap().end(), n) == openSet.getHeap().end())
                    openSet.push(n);
            }
        }
    }

    return {}; // khong tim thay duong di
}
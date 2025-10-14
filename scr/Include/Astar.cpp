#include "Astar.h"
#include "Priorityqueue.h"
#include "Set.h"
#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

double heuristic(ASNode *a, ASNode *b)
{
    return abs(a->get_x() - b->get_x()) + abs(a->get_y() - b->get_y());
}

Vector<ASNode *> return_path(ASNode *node)
{
    Vector<ASNode *> path;
    while (node)
    {
        path.push_back(node);
        node = node->get_parent();
    }
    reverse(path.begin(), path.end());
    return path;
}

Vector<ASNode *> get_neighbors(ASNode *node, Vector<Vector<ASNode>> &grid)
{
    Vector<ASNode *> neighbors;
    int w = grid.get_size();
    int h = grid[0].get_size();
    int dx[8] = {-1, 1, 0, 0, -1, -1, 1, 1};
    int dy[8] = {0, 0, -1, 1, 1, -1, -1, 1};

    for (int i = 0; i < 8; i++)
    {
        int nx = node->get_x() + dx[i];
        int ny = node->get_y() + dy[i];

        if (nx >= 0 && ny >= 0 && nx < w && ny < h && grid[nx][ny].get_walkable())
            neighbors.push_back(&grid[nx][ny]);
    }
    return neighbors;
}


struct CompareASNode
{
    bool operator()(ASNode *a, ASNode *b) const
    {
        return a->f() < b->f();
    }
};

void updateGridWalkable(Vector<Vector<ASNode>> &grid, Quadtree *qt, double cellSize)
{
    Vector<Entity *> entities;
    qt->query(Rect(0, 0, grid.get_size() * cellSize, grid[0].get_size() * cellSize), entities);

    for (Entity *e : entities)
    {
        if (!e->is_walkable())
        {
            // Ép về int và clamp vào kích thước grid
            int ix = std::clamp(static_cast<int>(e->get_x() / cellSize), 0, static_cast<int>(grid.get_size()) - 1);
            int iy = std::clamp(static_cast<int>(e->get_y() / cellSize), 0, static_cast<int>(grid[0].get_size()) - 1);

            grid[ix][iy].set_walkable(false);
        }
    }
}


Vector<ASNode *> astar(ASNode *start, ASNode *goal, Quadtree *qt,
                       Vector<Vector<ASNode>> &grid, double cellSize)
{
    updateGridWalkable(grid, qt, cellSize);

    Priorityqueue<ASNode *, CompareASNode> openSet;
    Set<ASNode *> closeSet;

    start->set_g(0);
    start->set_h(heuristic(start, goal));
    openSet.push(start);

    while (!openSet.isEmpty())
    {
        ASNode *cur = openSet.top();
        openSet.pop();

        if (cur == goal)
            return return_path(cur);

        closeSet.insert(cur);

        Vector<ASNode *> neighbors = get_neighbors(cur, grid);
        for (ASNode *n : neighbors)
        {
            if (closeSet.count(n))
                continue;

            double tentative_g = cur->get_g() + 1;

            if (tentative_g < n->get_g())
            {
                n->set_parent(cur);
                n->set_g(tentative_g);
                n->set_h(heuristic(n, goal));

                if (find(openSet.getHeap().begin(), openSet.getHeap().end(), n) == openSet.getHeap().end())
                    openSet.push(n);
            }
        }
    }

    return {};
}

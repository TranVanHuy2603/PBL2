#include "GBFS.h"
#include <limits>
#include <unordered_set>

struct CompareH
{
    bool operator()(ASNode *a, ASNode *b) const
    {
        return a->get_h() > b->get_h(); // h nhỏ thì ưu tiên
    }
};

Vector<ASNode *> GBFS(Vector<Vector<ASNode>> &grid, ASNode *start, ASNode *goal)
{
    Priorityqueue<ASNode *, CompareH> openList;
    std::unordered_set<ASNode *> inOpen;
    std::unordered_set<ASNode *> closed;

    // Reset parent của start
    start->set_parent(nullptr);

    // Tính heuristics ban đầu
    auto heuristic = [&](ASNode *a)
    {
        return abs(a->get_x() - goal->get_x()) +
               abs(a->get_y() - goal->get_y());
    };

    start->set_h(heuristic(start));
    openList.push(start);
    inOpen.insert(start);

    while (!openList.isEmpty())
    {
        ASNode *current = openList.top();
        openList.pop();        
        inOpen.erase(current);

        // Nếu đến đích → reconstruct path
        if (current == goal)
        {
            Vector<ASNode *> path;
            while (current)
            {
                path.push_back(current);
                current = current->get_parent();
            }
            // Đảo ngược đường đi
            for (int i = 0; i < path.get_size() / 2; i++)
                std::swap(path[i], path[path.get_size() - i - 1]);
            return path;
        }

        closed.insert(current);

        // 4 hướng
        int dx[4] = {-1, 1, 0, 0};
        int dy[4] = {0, 0, -1, 1};

        for (int k = 0; k < 4; ++k)
        {
            int nx = current->get_x() + dx[k];
            int ny = current->get_y() + dy[k];

            if (ny < 0 || ny >= grid.get_size() || nx < 0 || nx >= grid[0].get_size())
                continue;

            ASNode *neighbor = &grid[ny][nx];

            if (!neighbor->get_walkable())
                continue;

            if (closed.count(neighbor))
                continue;

            // Nếu chưa có trong openList → thêm vào
            if (!inOpen.count(neighbor))
            {
                neighbor->set_parent(current);
                neighbor->set_h(heuristic(neighbor));
                openList.push(neighbor);
                inOpen.insert(neighbor);
            }
        }
    }

    return Vector<ASNode *>(); // không tìm thấy đường
}

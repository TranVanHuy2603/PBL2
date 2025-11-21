#include "Monster.h"
#include "ASNode.h"
#include <cmath>
#include <algorithm>

using namespace std;

Monster::Monster() {}
Monster::Monster(int x, int y, int hp_max, int damage, double damage_range,
                 double attack_speed, int gold, int exp)
    : LivingEntity(x, y, hp_max), damage(damage), damage_range(damage_range),
      attack_speed(attack_speed), gold(gold), exp(exp)
{;
    attackcooldown = 0.f; 
    type = "Monster";
    if (!texture.loadFromFile("assets/monster/Monster.png"))
        cout << "Error load Monster\n";
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
    sprite.setScale(0.3, 0.3);

    hpBarSize = sf::Vector2f(100.f, 10.f); // chiều rộng, chiều cao thanh HP
    hpBack.setSize(hpBarSize);
    hpBack.setFillColor(sf::Color(100, 100, 100));
    hpBar.setSize(hpBarSize);
    hpBar.setFillColor(sf::Color::Red);
}

int Monster::get_gold() const { return gold; }
int Monster::get_exp() const { return exp; }

void Monster::draw(sf::RenderWindow &window)
{
    if (!status)
        return;
    window.draw(sprite);
    window.draw(hpBack);
    window.draw(hpBar);
}

void Monster::movePath(const Vector<sf::Vector2f> &path, float deltaTime)
{
    // Kiểm tra nếu đã đi hết đường hoặc không có đường
    if (path.empty() || currentTarget >= path.get_size())
        return;

    sf::Vector2f targetPos = path[currentTarget];
    float dx = targetPos.x - x;
    float dy = targetPos.y - y;

    // Tính khoảng cách Euclide
    float dist = std::sqrt(dx * dx + dy * dy);

    // Nếu đã đến rất gần điểm mục tiêu (sai số < 2.0f cho mượt hơn)
    if (dist < 2.0f)
    {
        currentTarget++; // CHỈ tăng index khi đã đến nơi
    }
    else
    {
        // Tăng tốc độ lên, 1.0f là quá chậm.
        // Nên dùng biến thành viên hoặc truyền vào (ví dụ 100.0f)
        float moveSpeed = 10.0f;

        // Chuẩn hóa vector hướng và di chuyển
        x += (dx / dist) * moveSpeed * deltaTime;
        y += (dy / dist) * moveSpeed * deltaTime;

        sprite.setPosition(x, y);

        // TUYỆT ĐỐI KHÔNG để currentTarget++ ở đây
    }
}
void Monster::attack(LivingEntity *target, float deltaTime)
{
    if (!target)
        return; // neu khong co muc tieu

    if (attackcooldown > 0.f) // neu van chua hoi chieu thi giam xuong
        attackcooldown -= deltaTime;

    if (attackcooldown <= 0.f) // neu da hoi chieu xong thi tan cong
    {
        target->take_damage(damage);         // gay sat thuong len muc tieu
        attackcooldown = 1.f / attack_speed; // reset lai thoi gian hoi chieu
    }
}

void Monster::update(float deltaTime, Castle *castle, Character *player,
                     Quadtree *qt, Vector<Vector<ASNode>> &grid, double cellSize)
{
    if (!status)
        return;

    // 1️⃣ Xác định mục tiêu gần nhất
    int target;
    sf::Vector2f targetPos;
    sf::Vector2f mpos = sprite.getPosition();
    sf::Vector2f cpos = castle->get_sprite().getPosition();
    sf::Vector2f ppos = player->get_sprite().getPosition();

    float d_castle = std::hypot(mpos.x - cpos.x, mpos.y - cpos.y);
    float d_player = std::hypot(mpos.x - ppos.x, mpos.y - ppos.y);

    if (d_castle < d_player)
    {
        target = 0;
        targetPos = cpos;
    }
    else
    {
        target = 1;
        targetPos = ppos;
    }

    // 2️⃣ Kiểm tra trong phạm vi tấn công
    float dist = std::hypot(mpos.x - targetPos.x, mpos.y - targetPos.y);

    if (attackcooldown > 0.f)
        attackcooldown -= deltaTime;
        
    if (dist <= damage_range)
    {
        if (target == 0) 
        {
            attack(castle, deltaTime);
        }
        else 
        {
            attack(player, deltaTime);
        }
    }

    updateRandomMovement(deltaTime);

    // 4️⃣ Tìm đường đi bằng GBFS
    // int startCol = static_cast<int>(std::floor(x / cellSize));
    // int startRow = static_cast<int>(std::floor(y / cellSize));
    // startCol = std::max(0, std::min(startCol, grid[0].get_size() - 1));
    // startRow = std::max(0, std::min(startRow, grid.get_size() - 1));
    // int goalCol = std::clamp(static_cast<int>(targetPos.x / cellSize), 0, grid[0].get_size() - 1);
    // int goalRow = std::clamp(static_cast<int>(targetPos.y / cellSize), 0, grid.get_size() - 1);

    // // std::cout << "Monster grid: " << startCol << "," << startRow
    // //           << "  Target grid: " << goalCol << "," << goalRow << "\n";

    // ASNode *startNode = &grid[startRow][startCol];
    // ASNode *goalNode = &grid[goalRow][goalCol];

    // // 4️⃣ Chỉ tính đường đi mới khi path cũ hết hoặc mục tiêu thay đổi
    // if (pathPositions.empty() || currentTarget >= pathPositions.get_size())
    // {
    //     Vector<ASNode *> newpath = GBFS(grid, startNode, goalNode);
    //     if (!newpath.empty())
    //     {
    //         pathPositions.clear();
    //         for (ASNode *node : newpath)
    //         {
    //             pathPositions.push_back(sf::Vector2f(node->get_x() * cellSize, node->get_y() * cellSize));
    //         }
    //         currentTarget = 0;
    //     }
    // }

    // // 5️⃣ Di chuyển theo đường đi
    // movePath(pathPositions, deltaTime);

    float hpPercent = static_cast<float>(get_hp()) / get_hp_max();
    hpBar.setSize(sf::Vector2f(hpBarSize.x * hpPercent, hpBarSize.y));

    // Căn giữa đầu quái
    sf::FloatRect bounds = sprite.getGlobalBounds();
    hpBack.setPosition(bounds.left + bounds.width / 2.f - hpBarSize.x / 2.f,
                       bounds.top - hpBarSize.y - 5.f); // 5 px cách đầu sprite
    hpBar.setPosition(hpBack.getPosition());
}

void Monster::updateRandomMovement(float deltaTime)
{
    static std::default_random_engine engine(static_cast<unsigned long>(time(nullptr)));
    static std::uniform_int_distribution<int> dirDist(0, 7); // 8 hướng

    // Chọn trạng thái đi/dừng khi hết thời gian
    if (randomMoveDuration <= 0.f)
    {
        if (isMoving)
        {
            isMoving = false;
            randomMoveDuration = 5.f; // dừng 5 giây
        }
        else
        {
            isMoving = true;
            randomDir = dirDist(engine);
            // Cập nhật hướng moveDir dựa trên randomDir
            switch (randomDir)
            {
            case 0: moveDir = {0.f, -1.f}; break;
            case 1: moveDir = {0.f, 1.f}; break;
            case 2: moveDir = {-1.f, 0.f}; break;
            case 3: moveDir = {1.f, 0.f}; break;
            case 4: moveDir = {-1.f, -1.f}; break;
            case 5: moveDir = {1.f, -1.f}; break;
            case 6: moveDir = {-1.f, 1.f}; break;
            case 7: moveDir = {1.f, 1.f}; break;
            }
            float len = std::sqrt(moveDir.x*moveDir.x + moveDir.y*moveDir.y);
            if (len != 0.f) moveDir /= len;
            randomMoveDuration = 2.f; // đi 2 giây
        }
    }

    // Nếu đang di chuyển
    if (isMoving)
    {
        float moveSpeed = 50.f;
        x += moveDir.x * moveSpeed * deltaTime;
        y += moveDir.y * moveSpeed * deltaTime;

        // Kiểm tra biên và đảo hướng
        if (x < minX)  { x = minX;  moveDir.x *= -1; }
        if (x > maxX)  { x = maxX;  moveDir.x *= -1; }
        if (y < minY)  { y = minY;  moveDir.y *= -1; }
        if (y > maxY)  { y = maxY;  moveDir.y *= -1; }

        sprite.setPosition(x, y);
    }

    randomMoveDuration -= deltaTime;
}


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
{
    ;
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

    moveDir = {0.f, 0.f};
    moveTimer = static_cast<float>(rand() % 100) / 50.f + 0.5f; // 0.5 - 2.5 giây
    speed = 100.f + rand() % 50;                                // tốc độ 100-150
}

Monster::~Monster() {}

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

    // Xác định mục tiêu gần nhất
    sf::Vector2f mpos = sprite.getPosition();
    sf::Vector2f cpos = castle->get_sprite().getPosition();
    sf::Vector2f ppos = player->get_sprite().getPosition();

    float d_castle = std::hypot(mpos.x - cpos.x, mpos.y - cpos.y);
    float d_player = std::hypot(mpos.x - ppos.x, mpos.y - ppos.y);

    sf::Vector2f targetPos = (d_castle < d_player ? cpos : ppos);
    bool targetCastle = (d_castle < d_player);

    float dist = std::hypot(mpos.x - targetPos.x, mpos.y - targetPos.y);

    // Giảm cooldown
    if (attackcooldown > 0.f)
        attackcooldown -= deltaTime;

    bool inRange = (dist <= damage_range);

    if (inRange)
    {
        if (attackcooldown <= 0.f)
        {
            if (targetCastle)
                attack(castle, deltaTime);
            else
                attack(player, deltaTime);
        }
    }
    else
    {
        updateRandomMovement(deltaTime);
        {
        }
        // Cập nhật thanh HP
        float hpPercent = get_hp() / (float)get_hp_max();
        hpBar.setSize(sf::Vector2f(hpBarSize.x * hpPercent, hpBarSize.y));

        sf::FloatRect bounds = sprite.getGlobalBounds();
        hpBack.setPosition(bounds.left + bounds.width / 2.f - hpBarSize.x / 2.f,
                           bounds.top - hpBarSize.y - 5.f);
        hpBar.setPosition(hpBack.getPosition());
    }
}

void Monster::updateRandomMovement(float deltaTime)
{
    // Khi hết thời gian đi → chọn hướng mới
    if (moveTimer <= 0.f)
    {
        int k = rand() % 8; // 8 hướng
        switch (k)
        {
        case 0:
            moveDir = {0.f, -1.f};
            break; // lên
        case 1:
            moveDir = {0.f, 1.f};
            break; // xuống
        case 2:
            moveDir = {-1.f, 0.f};
            break; // trái
        case 3:
            moveDir = {1.f, 0.f};
            break; // phải
        case 4:
            moveDir = {-1.f, -1.f};
            break; // lên trái
        case 5:
            moveDir = {1.f, -1.f};
            break; // lên phải
        case 6:
            moveDir = {-1.f, 1.f};
            break; // xuống trái
        case 7:
            moveDir = {1.f, 1.f};
            break; // xuống phải
        }

        // Chuẩn hóa vector
        float len = std::sqrt(moveDir.x * moveDir.x + moveDir.y * moveDir.y);
        if (len != 0.f)
            moveDir /= len;

        // Random thời gian đi cho hướng này
        moveTimer = 0.5f + static_cast<float>(rand() % 100) / 50.f; // 0.5 - 2.5 giây
    }

    // Cập nhật vị trí
    x += moveDir.x * speed * deltaTime;
    y += moveDir.y * speed * deltaTime;

    // Giới hạn bản đồ 6500 x 3500
    if (x < 0.f)
    {
        x = 0.f;
        moveDir.x = -moveDir.x;
    }
    if (x > 6500.f)
    {
        x = 6500.f;
        moveDir.x = -moveDir.x;
    }
    if (y < 0.f)
    {
        y = 0.f;
        moveDir.y = -moveDir.y;
    }
    if (y > 3500.f)
    {
        y = 3500.f;
        moveDir.y = -moveDir.y;
    }

    sprite.setPosition(x, y);

    moveTimer -= deltaTime;
}

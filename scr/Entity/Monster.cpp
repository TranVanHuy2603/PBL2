#include "Monster.h"
#include "ASNode.h"
#include <cmath>

Monster::Monster() {}
Monster::Monster(int x, int y, int hp_max, int damage, double damage_range,
                 double attack_speed, int gold, int exp)
    : LivingEntity(x, y, hp_max), damage(damage), damage_range(damage_range),
      attack_speed(attack_speed), gold(gold), exp(exp),
      isMoving(false), isAttacking(false) // Khởi tạo các biến trạng thái
{
    type = "Monster";
 
    if (!texture.loadFromFile("assets/monster/monster_spritesheet.png"))
        cout << "Error load Monster Spritesheet\n";

    sprite.setTexture(texture);
    sprite.setPosition(x, y);
    sprite.setScale(2.f, 2.f); // Tăng kích thước để nhìn rõ hơn

    loadAnimations();
    idleAnim.applyToSprite(sprite, false); // Áp dụng frame đầu tiên

    pathRecalculateTimer = 0.f;
}

void Monster::loadAnimations()
{
    const int frameWidth = 128;  // <-- Điều chỉnh cho khớp với file ảnh của bạn
    const int frameHeight = 128; // <-- Điều chỉnh cho khớp với file ảnh của bạn
    const int frameCount = 4;

    // Gán texture cho tất cả animation
    idleAnim.setTexture(texture);
    walkAnim.setTexture(texture);
    attackAnim.setTexture(texture);
    deathAnim.setTexture(texture);

    // Thêm frame cho từng animation
    for (int i = 0; i < frameCount; ++i)
        idleAnim.addFrame(sf::IntRect(i * frameWidth, 0 * frameHeight, frameWidth, frameHeight));
    for (int i = 0; i < frameCount; ++i)
        walkAnim.addFrame(sf::IntRect(i * frameWidth, 1 * frameHeight, frameWidth, frameHeight));
    for (int i = 0; i < frameCount; ++i)
        attackAnim.addFrame(sf::IntRect(i * frameWidth, 2 * frameHeight, frameWidth, frameHeight));
    for (int i = 0; i < frameCount; ++i)
        deathAnim.addFrame(sf::IntRect(i * frameWidth, 3 * frameHeight, frameWidth, frameHeight));

    // Cấu hình
    idleAnim.setFrameDuration(0.15f);
    walkAnim.setFrameDuration(0.1f);
    attackAnim.setFrameDuration(0.12f);
    deathAnim.setFrameDuration(0.15f);
    deathAnim.setLoop(false); // Animation chết không lặp lại

    // Đặt origin vào tâm để xoay/lật cho đúng
    sprite.setOrigin(frameWidth / 2.f, frameHeight / 2.f);
}

int Monster::get_gold() const { return gold; }
int Monster::get_exp() const { return exp; }
int Monster::get_damage() const {return this->damage; }

void Monster::draw(sf::RenderWindow &window)
{
    if (!status)
        return;
    window.draw(sprite);
}

void Monster::set_path(const Vector<sf::Vector2f> &newpath) // gan path cho quai
{
    path = newpath;
    currentTarget = 0;
}

void Monster::movePath(float deltatime) // cho quai di theo path
{
    if (currentTarget < static_cast<int>(path.get_size())) // kiem tra con diem nao trong duong di khong
    {
        sf::Vector2f target = path[currentTarget];               // diem dich hien tai trong path/dime tiep theo
        sf::Vector2f pos = sprite.getPosition();                 // vi tri cua quai
        sf::Vector2f dir = target - pos;                         // huong vecto tu quai toi diem ke tiep
        float length = std::sqrt(dir.x * dir.x + dir.y * dir.y); // do dai cua vecto do

        if (length > 1.f) // chuan hoa de quai di chuyen muot hon
        {
            dir /= length;
            pos += dir * deltatime * 100.f;
            sprite.setPosition(pos);
        }
        else
        {
            currentTarget++; // chuyen toi diem tiep theo
        }
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
    if (!status) {
        deathAnim.update(deltaTime);
        deathAnim.applyToSprite(sprite, false);

        return;
    }
    // 1.Xac dinh muc tieu gan nhat
    LivingEntity *targetEntity;                             // muc tieu
    sf::Vector2f targetpos;                                 // toa do muc tieu
    sf::Vector2f mpos = sprite.getPosition();               // vi tri cua quai
    sf::Vector2f cpos = castle->get_sprite().getPosition(); // vi tri cua thanh tri
    sf::Vector2f ppos = player->get_sprite().getPosition(); // vi tri cua nguoi choi

    bool shouldFlip = (sprite.getPosition().x > targetpos.x);
    // khoang cach tu quai den thanh tri
    float d_castle = std::sqrt((mpos.x - cpos.x) * (mpos.x - cpos.x) + (mpos.y - cpos.y) * (mpos.y - cpos.y));
    // khoang cach tu quai den nguoi choi
    float d_player = std::sqrt((mpos.x - ppos.x) * (mpos.x - ppos.x) + (mpos.y - ppos.y) * (mpos.y - ppos.y));

    // xac diinh muc tieu nao gan quai nhat
    if (d_castle < d_player)
    {
        targetEntity = castle;
        targetpos = cpos;
    }
    else
    {
        targetEntity = player;
        targetpos = ppos;
    }

    // 2.kiem tra muc tieu co nam trong vung gay sat thong khong
    float dx = mpos.x - targetpos.x;
    float dy = mpos.y - targetpos.y;
    float dist = std::sqrt(dx * dx + dy * dy);

    if (dist <= damage_range) // neu co the gay sat thuong
    {
        isAttacking = true;
        isMoving = false;
        attack(targetEntity, deltaTime);
        path.clear();
    }

    else // neu khong thi cho di the A* de toi muc tieu
    {
        isAttacking = false;
        isMoving = true;
        // dua ve toa do tren grid
        int startX = std::clamp(static_cast<int>(mpos.x / cellSize), 0, static_cast<int>(grid.get_size()) - 1);
        int startY = std::clamp(static_cast<int>(mpos.y / cellSize), 0, static_cast<int>(grid[0].get_size()) - 1);
        int goalX = std::clamp(static_cast<int>(targetpos.x / cellSize), 0, static_cast<int>(grid.get_size()) - 1);
        int goalY = std::clamp(static_cast<int>(targetpos.y / cellSize), 0, static_cast<int>(grid[0].get_size()) - 1);

        ASNode *start = &grid[startX][startY];
        ASNode *goal = &grid[goalX][goalY];

        // tim duong di cho quai bang A*
        Vector<ASNode *> newpath = astar(start, goal, qt, grid, cellSize);

        if (!newpath.empty())
        {
            Vector<sf::Vector2f> realpath; // chuyen tu node thanh path voi toa do thuc
            for (ASNode *node : newpath)
            {                                                                                         // duyet tat ca cac node
                realpath.push_back(sf::Vector2f(node->get_x() * cellSize, node->get_y() * cellSize)); // toa do thuc de quai di
            }
            set_path(realpath); // gan path cho quai
        }

        movePath(deltaTime); // di theo path
    }

    // Cập nhật animation dựa trên trạng thái
    if (isAttacking)
    {
        attackAnim.update(deltaTime);
        attackAnim.applyToSprite(sprite, shouldFlip);
    }
    else if (isMoving)
    {
        walkAnim.update(deltaTime);
        walkAnim.applyToSprite(sprite, shouldFlip);
    }
    else
    {
        idleAnim.update(deltaTime);
        idleAnim.applyToSprite(sprite, shouldFlip);
    }

}

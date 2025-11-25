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
    attackcooldown = 0.f;
    type = "Monster";

    if (!texture.loadFromFile("assets/monster/Monster.png"))
        cout << "Error load Monster\n";

    sprite.setTexture(texture);
    sprite.setPosition(x, y);
    sprite.setScale(0.3, 0.3);

    // HP Bar
    hpBarSize = sf::Vector2f(100.f, 10.f);
    hpBack.setSize(hpBarSize);
    hpBack.setFillColor(sf::Color(100, 100, 100));
    hpBar.setSize(hpBarSize);
    hpBar.setFillColor(sf::Color::Red);

    // Random move
    moveDir = {0.f, 0.f};
    moveTimer = static_cast<float>(rand() % 100) / 50.f + 0.5f;
    speed = 100.f + rand() % 50;

    // Attack highlight circle
    attackCircle.setRadius(damage_range);
    attackCircle.setOrigin(damage_range, damage_range);
    attackCircle.setFillColor(sf::Color(255, 50, 50, 60)); // vàng mờ
    attackCircleTimer = 0.f;
}

Monster::~Monster() {}

int Monster::get_gold() const { return gold; }
int Monster::get_exp() const { return exp; }

void Monster::draw(sf::RenderWindow &window)
{
    if (!status)
        return;

    // Vẽ vòng tròn tấn công nếu đang hiển thị
    if (attackCircleTimer > 0.f)
        window.draw(attackCircle);

    window.draw(sprite);
    window.draw(hpBack);
    window.draw(hpBar);
}

void Monster::attack(LivingEntity *target, float deltaTime)
{
    if (!target)
        return;

    if (attackcooldown > 0.f)
        attackcooldown -= deltaTime;

    if (attackcooldown <= 0.f)
    {
        target->take_damage(damage);
        attackcooldown = 1.f / attack_speed;
    }
}

void Monster::update(float deltaTime, Castle *castle, Character *player,
                     Quadtree *qt)
{
    if (!status)
        return;

    // Target selection
    sf::Vector2f mpos = sprite.getPosition();
    sf::Vector2f cpos = castle->get_sprite().getPosition();
    sf::Vector2f ppos = player->get_sprite().getPosition();

    float d_castle = std::hypot(mpos.x - cpos.x, mpos.y - cpos.y);
    float d_player = std::hypot(mpos.x - ppos.x, mpos.y - ppos.y);

    sf::Vector2f targetPos = (d_castle < d_player ? cpos : ppos);
    bool targetCastle = (d_castle < d_player);

    float dist = std::hypot(mpos.x - targetPos.x, mpos.y - targetPos.y);

    // Cooldown
    if (attackcooldown > 0.f)
        attackcooldown -= deltaTime;

    bool inRange = (dist <= damage_range);

    if (inRange)
    {
        if (attackcooldown <= 0.f)
        {
            // Attack
            if (targetCastle)
                attack(castle, deltaTime);
            else
                attack(player, deltaTime);

            // Hiện vòng tròn vàng khi tấn công
            attackCircleTimer = 0.2f;
        }
    }
    else
    {
        updateRandomMovement(deltaTime);
    }

    // HP bar update
    float hpPercent = get_hp() / (float)get_hp_max();
    hpBar.setSize(sf::Vector2f(hpBarSize.x * hpPercent, hpBarSize.y));

    sf::FloatRect bounds = sprite.getGlobalBounds();
    hpBack.setPosition(bounds.left + bounds.width / 2.f - hpBarSize.x / 2.f,
                       bounds.top - hpBarSize.y - 5.f);
    hpBar.setPosition(hpBack.getPosition());

    // Update attack highlight circle
    if (attackCircleTimer > 0.f)
    {
        attackCircleTimer -= deltaTime;

        attackCircle.setPosition(
            bounds.left + bounds.width / 2.f,
            bounds.top + bounds.height / 2.f
        );
    }
}

void Monster::updateRandomMovement(float deltaTime)
{
    if (moveTimer <= 0.f)
    {
        isMoving = !isMoving;

        if (isMoving)
        {
            int k = rand() % 8;
            switch (k)
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

            float len = std::sqrt(moveDir.x * moveDir.x + moveDir.y * moveDir.y);
            if (len != 0.f)
                moveDir /= len;

            moveTimer = 2.f;
        }
        else
        {
            moveTimer = 5.f;
        }
    }

    if (isMoving)
    {
        x += moveDir.x * speed * deltaTime;
        y += moveDir.y * speed * deltaTime;

        if (x < minX) { x = minX; moveDir.x = -moveDir.x; }
        if (x > maxX) { x = maxX; moveDir.x = -moveDir.x; }
        if (y < minY) { y = minY; moveDir.y = -moveDir.y; }
        if (y > maxY) { y = maxY; moveDir.y = -moveDir.y; }

        sprite.setPosition(x, y);
    }

    moveTimer -= deltaTime;
}

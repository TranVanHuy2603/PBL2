#include "Character.h"
#include "Rect.h"
#include "EntityManager.h"
#include <SFML/Graphics.hpp>
#include <cmath>

const int frameW = 128;
const int frameH = 128;
// dung trong ham craft_weapon()
struct Recipe // cong thuc che che tao vu khi
{
    int wood;
    int coal;
    int iron;
    int gold;
    int diamond;
    int emerald;
};
struct WeaponInfo // thuoc tinh cua vu khi duoc che tao
{
    int damage;
    double damage_range;
    double attack_speed;
    const char *texture;
    const char *sound;
};
// theo thu tu la Wood, Coal, Iron, Gold, Diamond, Emerald
Recipe recipes[(int)WeaponType::Count] = {
    {0, 0, 0, 0, 0, 0}, // BareHand
    {6, 4, 0, 0, 0, 0}, // WoodenSword
    {3, 5, 6, 0, 0, 0}, // IronSwood
    {6, 3, 7, 0, 0, 0}, // Ax
    {6, 2, 4, 5, 0, 0}, // Bow
    {5, 4, 4, 4, 3, 2}  // Gun
};
// theo thu tu la Damage, Damage_range, Attack_speed, texture
WeaponInfo weaponInfos[(int)WeaponType::Count] = {
    {5, 70.0, 2.0, "assets/weapon/barehand.png", "assets/audio/handsound.mp3"},           // HareHand
    {8, 110.0, 2.5, "assets/weapon/woodensword.png", "assets/audio/wodenswordsound.mp3"}, // WoodenSword
    {15, 125.0, 2.3, "assets/weapon/ironsword.png", "assets/audio/ironswordsound.mp3"},   // IronSwood
    {20, 80.0, 1.9, "assets/weapon/ax.png", "assets/audio/axsound.mp3"},                  // Ax
    {12, 150.0, 2.0, "assets/weapon/bow.png", "assets/audio/bowsound.mp3"},               // Bow
    {25, 200.0, 2.0, "assets/weapon/gun.png", "assets/audio/gunsound.mp3"}                // Gun
};
//--------------------------------------------------------------------

// === SỬ DỤNG ENTITY::SPRITE ===
Character::Character(int x, int y, int hp_max, int exp_max)
    : LivingEntity(x, y, hp_max), level(1), gold(0), exp(0), exp_max(exp_max)
{
    type = "Character";

    // ====== Load texture ======
    if (!texture.loadFromFile("assets/character/character_spritesheet.png"))
        std::cout << "Error load character texture\n";

    if (!hurtTexture.loadFromFile("assets/character/character_hurt.png"))
        std::cout << "Error load hurt texture\n";

    if (!dustTexture.loadFromFile("assets/effects/dust.png"))
        std::cout << "Error loading dust texture\n";
    // ====== Setup sprite ======
    Entity::sprite.setTexture(texture);
    Entity::sprite.setPosition((float)x, (float)y);
    Entity::sprite.setScale(2.f, 2.f);
    Entity::sprite.setOrigin(frameH / 4.f, frameW / 6.f);

    // ====== Setup animation ======
    loadAnimations();
    // Khi khởi tạo, ta chỉ muốn nhân vật ĐỨNG YÊN — không chạy animation
    idleAnim.reset();
    idleAnim.stop();

    // Gán frame đầu tiên của idle vào sprite để hiển thị đúng khung tĩnh
    idleAnim.applyToSprite(Entity::sprite, true);


    // ====== Setup gameplay ======
    hp = hp_max;
    isDead = false;
    isHurt = false;
    hurtTimer = 0.f;
    facing = Direction::Right;
    isMoving = false;
    isAttacking = false;
    hitTriggered = false;
    hitFrameIndex = 2; // frame thứ 2 của animation Attack sẽ gây sát thương

    // ====== Weapon ======
    craft_weapon(WeaponType::BareHand);
}

Character::~Character()
{
    for (auto *w : weapons)
    {
        delete w;
    }
    weapons.clear();
}

// getter
int Character::get_gold() const { return gold; }
int Character::get_exp() const { return exp; }
int Character::get_exp_max() const { return exp_max; }
Bag Character::get_bag() const { return bag; }
Bag &Character::get_bag() { return bag; }
int Character::get_indexWeapon() const { return indexWeapon; }
Vector<Weapons *> &Character::get_weapons() { return weapons; }
int Character::get_level() const { return level; }
sf::Texture Character::get_texture() const { return texture; }

int Character::get_resource_amount(ResourceType type) const
{
    switch (type)
    {
    case ResourceType::Wood:
        return bag.getWood();
    case ResourceType::Stone:
        return bag.getStone();
    case ResourceType::Sand:
        return bag.getSand();
    case ResourceType::Coal:
        return bag.getCoal();
    case ResourceType::Iron:
        return bag.getIron();
    case ResourceType::Gold:
        return bag.getGold();
    case ResourceType::Diamond:
        return bag.getDiamond();
    case ResourceType::Emerald:
        return bag.getEmerald();
    default:
        return 0;
    }
}

sf::Vector2f Character::get_position() const
{
    return Entity::sprite.getPosition();
}

sf::Vector2f Character::getSize() const
{
    sf::FloatRect bounds = Entity::sprite.getGlobalBounds();
    return sf::Vector2f(bounds.width, bounds.height);
}

void Character::set_position(const sf::Vector2f &pos)
{
    Entity::sprite.setPosition(pos);
}

// setter
void Character::set_indexWeapon(int value) { indexWeapon = value; }
void Character::setScale(float x, float y) { Entity::sprite.setScale(x, y); }
void Character::set_texture(String texturepath)
{
    texture.loadFromFile(texturepath.c_str());
    Entity::sprite.setTexture(texture);
}

// dung de nhat vang, kim cuong va nang cap nha
void Character::incr_gold(int value) { this->gold += value; }
void Character::incr_exp(int value) { this->exp += value; }
void Character::decr_gold(int value) { this->gold -= value; }
void Character::decr_exp(int value) { this->exp -= value; }

void Character::levelUp() // tang level
{
    if (level < 5)
    {
        level++;
        exp = 0;
        hp_max += 50;
        exp_max += 50;
        hp = hp_max;
    }
}

void Character::level_up_castle(Castle *castle)
{
    if (gold >= castle->get_cost()) // kiem tra vang co du de nang cap khong
    {
        castle->level_up();            // nang level
        decr_gold(castle->get_cost()); // tru vang ngoi choi hien co
    }
}

void Character::attack(Quadtree &qt)
{
    weapons[indexWeapon]->attack(qt, this); // tan cong bang vu khi
    std::cout << "Nhan vat tan cong\n";
}

void Character::add_weapon(Weapons *newWeapon)
{
    weapons.push_back(newWeapon);
    if (indexWeapon == -1)
    {
        indexWeapon = 0;
    }
}

void Character::switch_weapon(int index)
{
    if (index >= 0 && index < weapons.get_size())
    {
        set_indexWeapon(index);
    }
}

bool Character::craft_weapon(WeaponType type)
{
    int index = static_cast<int>(type);
    const Recipe &r = recipes[index];

    if (bag.getWood() < r.wood || bag.getCoal() < r.coal || bag.getIron() < r.iron ||
        bag.getGold() < r.gold || bag.getDiamond() < r.diamond || bag.getEmerald() < r.emerald)
    {
        return false;
    }

    bag.decr_Wood(r.wood);
    bag.decr_Coal(r.coal);
    bag.decr_Iron(r.iron);
    bag.decr_Gold(r.gold);
    bag.decr_Diamond(r.diamond);
    bag.decr_Emerald(r.emerald);

    const WeaponInfo &info = weaponInfos[index];
    Weapons *w = new Weapons(type, info.damage, info.damage_range, info.attack_speed, info.texture, info.sound);

    weapons.push_back(w);
    if (!weapons.empty())
        std::cout << "Da tao vu khi\n";
    indexWeapon = weapons.get_size() - 1;
    return true;
}

void Character::takeDamage(float dmg)
{
    if (isDead)
        return;
    hp -= dmg;
    if (hp <= 0)
    {
        hp = 0;
        isDead = true;
        deathAnim.play();
    }
    else
    {
        isHurt = true;
        hurtTimer = 0.5f; // Thời gian bị thương
        hurtAnim.play();
    }
}


// ====== Animation ===========

void Character::loadAnimations()
{
    const int frameWidth = 128;
    const int frameHeight = 128;
    const int frameCount = 6;

    idleAnim.setTexture(texture);
    walkAnim.setTexture(texture);
    attackAnim.setTexture(texture);
    deathAnim.setTexture(texture);
    hurtAnim.setTexture(hurtTexture);

    // ===== Idle =====
    for (int i = 0; i < frameCount; ++i)
        idleAnim.addFrame(sf::IntRect(i * frameWidth, 0 * frameHeight, frameWidth, frameHeight));

    // ===== Walk =====
    for (int i = 0; i < frameCount; ++i)
        walkAnim.addFrame(sf::IntRect(i * frameWidth, 1 * frameHeight, frameWidth, frameHeight));

    // ===== Attack =====
    for (int i = 0; i < frameCount; ++i)
        attackAnim.addFrame(sf::IntRect(i * frameWidth, 2 * frameHeight, frameWidth, frameHeight));

    // ===== Death =====
    for (int i = 0; i < frameCount; ++i)
        deathAnim.addFrame(sf::IntRect(i * frameWidth, 3 * frameHeight, frameWidth, frameHeight));

    // ===== Animation config =====
    idleAnim.setFrameDuration(0.15f);
    walkAnim.setFrameDuration(0.1f);
    attackAnim.setFrameDuration(0.08f);
    deathAnim.setFrameDuration(0.15f);
    deathAnim.setLoop(false);

    // ===== Hurt animation (từ ảnh khác) =====
    sf::Vector2u hurtSize = hurtTexture.getSize();
    int hurtFrameW = hurtSize.x / 4;
    int hurtFrameH = hurtSize.y;
    for (int i = 0; i < 4; ++i)
        hurtAnim.addFrame(sf::IntRect(i * hurtFrameW, 0, hurtFrameW, hurtFrameH));
    hurtAnim.setFrameDuration(0.1f);
    hurtAnim.setLoop(false);

    // ===== Khởi tạo sprite mặc định =====
    idleAnim.reset();
    idleAnim.stop();
    Entity::sprite.setTexture(texture);
    Entity::sprite.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));

    // QUAN TRỌNG: Đặt origin vào TÂM của khung hình
    Entity::sprite.setOrigin(frameWidth / 2.f, frameHeight / 2.f);
}

void Character::handleInput(float dt)
{
    if (isDead || isAttacking || isHurt) {
        isMoving = false;
        return;
    }

    sf::Vector2f move(0.f, 0.f);
    isMoving = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        move.y -= 100.f * dt;
        isMoving = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        move.y += 100.f * dt;
        isMoving = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        move.x -= 100.f * dt;
        facing = Direction::Left;
        isMoving = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        move.x += 100.f * dt;
        facing = Direction::Right;
        isMoving = true;
    }

    Entity::sprite.move(move);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !isAttacking)
    {
        isAttacking = true;
        attackAnim.play();
        hitTriggered = false;
    }
}

void Character::update(float dt, Quadtree& qt, EntityManager& manager)
{
    bool shouldFlip = (facing == Direction::Left);
    if (isDead)
    {
        deathAnim.update(dt);
        deathAnim.applyToSprite(Entity::sprite, true);
        if (deathAnim.isFinished())
        {
            Entity::sprite.setColor(sf::Color(255, 255, 255, 0)); // ẩn sprite
        }
        return;
    }

    if (isHurt)
    {
        hurtTimer -= dt;
        hurtAnim.update(dt);
        hurtAnim.applyToSprite(Entity::sprite, true);
        Entity::sprite.setColor(sf::Color(255, 100, 100));

        if (hurtTimer <= 0.f || hurtAnim.isFinished())
        {
            isHurt = false;
            Entity::sprite.setColor(sf::Color::White);
        }
        return;
    }

    if (isAttacking)
    {
        attackAnim.update(dt);
        attackAnim.applyToSprite(Entity::sprite, shouldFlip);

        if (attackAnim.getCurrentFrameIndex().x == hitFrameIndex && !hitTriggered)
        {
            attack(qt);
            hitTriggered = true;
            manager.createWeaponEffect(weapons[indexWeapon], get_position());
        }

        if (attackAnim.isFinished())
        {
            isAttacking = false;
            idleAnim.play();
        }
    }

    else if (isMoving)
    {
        walkAnim.update(dt);
        walkAnim.applyToSprite(Entity::sprite, shouldFlip);
    }
    else
    {
        idleAnim.update(dt);
        idleAnim.applyToSprite(Entity::sprite, shouldFlip);
    }
    weapons[indexWeapon]->updateAnimation(dt, get_position(), shouldFlip);
    updateDustEffect(dt);
    
}

void Character::updateDustEffect(float dt)
{
    // Logic 1: Tạo hạt bụi mới nếu nhân vật đang di chuyển
    if (isMoving && dustSpawnClock.getElapsedTime().asSeconds() > 0.15f)
    {
        // Tạo một sprite mới cho hạt bụi
        sf::Sprite particle(dustTexture);
        particle.setScale(0.5f, 0.5f); // Thu nhỏ hạt bụi
        particle.setOrigin(dustTexture.getSize().x / 2.f, dustTexture.getSize().y / 2.f);

        // Đặt vị trí ban đầu ở chân nhân vật
        sf::Vector2f pos = get_position();
        pos.y += getSize().y / 2.f - 20; // Điều chỉnh vị trí Y cho phù hợp
        particle.setPosition(pos);

        // Thêm hạt bụi vào danh sách để quản lý
        dustParticles.push_back(particle);
        dustSpawnClock.restart(); // Reset đồng hồ đếm
    }

    // Logic 2: Cập nhật tất cả các hạt bụi đang có
    for (size_t i = 0; i < dustParticles.get_size(); )
    {
        // Cho hạt bụi bay lên trên
        dustParticles[i].move(0, -30.f * dt);

        // Làm mờ dần hạt bụi
        sf::Color color = dustParticles[i].getColor();
        if (color.a < 10) // Nếu đã gần như trong suốt
        {
            // Xóa hạt bụi khỏi danh sách
            dustParticles.erase(dustParticles.begin() + i);
        }
        else
        {
            // Giảm độ trong suốt (alpha)
            color.a -= static_cast<unsigned char>(200.f * dt);
            dustParticles[i].setColor(color);
            // Chỉ tăng i nếu không xóa phần tử
            ++i;
        }
    }
}

void Character::draw(sf::RenderWindow& window)
{
    // Vẽ các hạt bụi TRƯỚC (để chúng ở phía sau nhân vật)
    for (const auto& particle : dustParticles)
    {
        window.draw(particle);
    }

    // Vẽ sprite nhân vật (gọi hàm của lớp cha)
    LivingEntity::draw(window);

    // Vẽ vũ khí SAU (để nó ở phía trước nhân vật)
    weapons[indexWeapon]->draw(window);
}


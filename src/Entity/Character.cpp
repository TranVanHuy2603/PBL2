#include "Character.h"
#include "Entity.h"
#include "Quadtree.h"
#include "Rect.h"
#include <SFML/Graphics.hpp>
#include <cmath>

struct WeaponInfo // thuoc tinh cua vu khi duoc che tao
{
    String name;
    int damage;
    double damage_range;
    double attack_speed;
    String texture;
    String sound;
};

WeaponInfo weaponInfos[(int)WeaponType::Count] = {
    {"Tay",5 , 190.0, 2.3, "assets/weapon/barehand.png", "assets/audio/handsound.mp3"},          // HareHand
    {"Kiem go", 8, 240.0, 2.5, "assets/weapon/woodensword.png", "assets/audio/wodenswordsound.mp3"}, // WoodenSword
    {"Kiem sat", 15, 270.0, 2.3, "assets/weapon/ironsword.png", "assets/audio/ironswordsound.mp3"},   // IronSwood
    {"Riu", 20, 190.0, 1.9, "assets/weapon/ax.png", "assets/audio/axsound.mp3"},                 // Ax
    {"Cung ten", 12, 270.0, 2.0, "assets/weapon/bow.png", "assets/audio/bowsound.mp3"},               // Bow
    {"Sung", 25, 440.0, 2.0, "assets/weapon/gun.png", "assets/audio/gunsound.mp3"}                // Gun
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

Character::Character() {}

Character::Character(int x, int y, int hp_max, int exp_max, int lives)
    : LivingEntity(x, y, hp_max), level(1), gold(0), exp(0), exp_max(exp_max), lives(lives)
{
    type = "Character";
    if (!upTexture.loadFromFile("assets/character/up.png") || !downTexture.loadFromFile("assets/character/down.png") ||
        !leftTexture.loadFromFile("assets/character/left.png") || !rightTexture.loadFromFile("assets/character/right.png") ||
        !texture.loadFromFile("assets/character/Character.png"))
        cout << "error load character\n";
    sprite.setTexture(upTexture);         // gan hinh anh nha vat cho sprite de ive ra cua so game
    sprite.setPosition(this->x, this->y); // set vi tri cua hinh anh la toa  do cua nhan vat
    sprite.setScale(0.8, 0.8);
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
int Character::get_lives() const { return lives; }
int Character::get_level() const { return level; }
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
    return sprite.getPosition();
}

bool Character::get_status() const
{
    return status;
}

sf::Vector2f Character::getSize() const
{
    sf::FloatRect bounds = sprite.getGlobalBounds();
    return sf::Vector2f(bounds.width, bounds.height);
}

// setter
void Character::set_indexWeapon(int value) { indexWeapon = value; }
void Character::setScale(float x, float y) { sprite.setScale(x, y); }

// dung de nhat vang, kim cuong va nang cap nha
void Character::incr_gold(int value) { this->gold += value; }
void Character::incr_exp(int value) { this->exp += value; }
void Character::decr_gold(int value) { this->gold -= value; }
void Character::decr_exp(int value) { this->exp -= value; }

void Character::levelUp() // tang level
{
    if (level <= 9)
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

void Character::handleInput(double deltaTime)
{
    sf::Vector2f move(0.f, 0.f);
    bool moving = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        move.y -= 100.f * deltaTime;
        sprite.setTexture(upTexture);
        moving = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        move.y += 100.f * deltaTime;
        sprite.setTexture(downTexture);
        moving = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        move.x -= 100.f * deltaTime;
        sprite.setTexture(leftTexture);
        moving = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        move.x += 100.f * deltaTime;
        sprite.setTexture(rightTexture);
        moving = true;
    }

    if (!moving)
        sprite.setTexture(texture); // đứng yên

    sprite.move(move);
    x = sprite.getPosition().x;
    y = sprite.getPosition().y;
}

void Character::update(float deltatime)
{
}

void Character::attack(Quadtree &qt, Quest &quest)
{
    weapons[indexWeapon]->attack(qt, this, quest); // tan cong bang vu khi
}

void Character::add_weapon(Weapons *newWeapon) // them vu khi moi
{
    weapons.push_back(newWeapon);
    if (indexWeapon == -1)
    {
        indexWeapon = 0;
    }
}

void Character::switch_weapon(int index) // doi vu khi
{
    if (index >= 0 && index < weapons.get_size())
    {
        set_indexWeapon(index);
    }
}

bool Character::craft_weapon(WeaponType type)
{
    int index = static_cast<int>(type); // lay so nguyen tuong ung voi chi so cong thuc trong mang
    const Recipe &r = recipes[index];   // lay ra cong thuc
    // kiem tra du nguyen lieu khong
    if (bag.getWood() < r.wood || bag.getCoal() < r.coal || bag.getIron() < r.iron || bag.getGold() < r.gold || bag.getDiamond() < r.diamond || bag.getEmerald() < r.emerald)
    {
        return false;
    }
    // tru nguyen lieu
    bag.decr_Wood(r.wood);
    bag.decr_Coal(r.coal);
    bag.decr_Iron(r.iron);
    bag.decr_Gold(r.gold);
    bag.decr_Diamond(r.diamond);
    bag.decr_Emerald(r.emerald);
    // tao vu khi moi
    const WeaponInfo &info = weaponInfos[index]; // thuoc tinh cus vu khi
    Weapons *w = new Weapons(type, info.name, info.texture, info.damage, info.damage_range, info.attack_speed, info.texture, info.sound);

    weapons.push_back(w);
    if (!weapons.empty())
        cout << "Da tao vu khi\n";        // them vu khi vao cho nhan vat
    indexWeapon = weapons.get_size() - 1; // cho nhan vat su dung vu khi ngay
    return true;
}

void Character::take_damage(int value)
{
    hp -= value;
    cout << "tru mau\n";
    if (hp <= 0)
    {
        if (lives > 0) // còn mạng thì trừ mạng và hồi hp
        {
            lives--;
            hp = hp_max;
            cout << "Tru mot mang\n";
            static Audio diesound("assets/audio/die.mp3");
            diesound.setVolume(30);
            diesound.playSound();
        }
        else // hết mạng
        {
            hp = 0;
            status = false; // nhân vật chết
            cout << "Nhan vat chet\n";
        }
    }
}

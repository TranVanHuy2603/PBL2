#include "Character.h"
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
    {"Tay", 7, 190.0, 2.3, "assets/weapon/barehand.png", "assets/audio/handsound.ogg"},              // HareHand
    {"Kiem go", 10, 240.0, 2.5, "assets/weapon/woodensword.png", "assets/audio/wodenswordsound.ogg"}, // WoodenSword
    {"Kiem sat", 15, 270.0, 2.3, "assets/weapon/ironsword.png", "assets/audio/ironswordsound.ogg"},  // IronSwood
    {"Riu", 50, 190.0, 1.9, "assets/weapon/ax.png", "assets/audio/axsound.ogg"},                     // Ax
    {"Cung ten", 20, 270.0, 2.0, "assets/weapon/bow.png", "assets/audio/bowsound.ogg"},              // Bow
    {"Sung", 30, 440.0, 2.0, "assets/weapon/gun.png", "assets/audio/gunsound.ogg"}                   // Gun
};

// theo thu tu la Wood, stone, sand Coal, Iron, Gold, Diamond, Emerald
Recipe recipes[(int)WeaponType::Count] = {
    {0, 0, 0, 0, 0, 0, 0, 0}, // BareHand
    {6, 4, 2, 2, 1, 0, 0, 0}, // WoodenSword
    {3, 5, 3, 4, 6, 1, 0, 0}, // IronSwood
    {6, 3, 5, 3, 7, 2, 1, 1}, // Ax
    {6, 2, 3, 4, 4, 5, 3, 2}, // Bow
    {9, 4, 5, 5, 6, 4, 6, 6}  // Gun
};

Character::Character() {}

Character::Character(int x, int y, int hp_max, int exp_max, int lives)
    : LivingEntity(x, y, hp_max), level(1), gold(0), exp(0), exp_max(exp_max), lives(lives)
{
    type = "Character";
    // Up
    if (!up.loadFromFile("assets/character/up.png"))
        std::cerr << "Failed to load up.png\n";

    // Right
    if (!right_cung.loadFromFile("assets/character/right_cung.png"))
        std::cerr << "Failed to load right_cung.png\n";
    if (!right_kiemgo.loadFromFile("assets/character/right_kiemgo.png"))
        std::cerr << "Failed to load right_kiemgo.png\n";
    if (!right_kiemsat.loadFromFile("assets/character/right_kiemsat.png"))
        std::cerr << "Failed to load right_kiemsat.png\n";
    if (!right_riu.loadFromFile("assets/character/right_riu.png"))
        std::cerr << "Failed to load right_riu.png\n";
    if (!right_sung.loadFromFile("assets/character/right_sung.png"))
        std::cerr << "Failed to load right_sung.png\n";
    if (!right_hand.loadFromFile("assets/character/right_hand.png"))
        std::cerr << "Failed to load right_hand.png\n";

    // Down
    if (!down_cung.loadFromFile("assets/character/down_cung.png"))
        std::cerr << "Failed to load down_cung.png\n";
    if (!down_kiemgo.loadFromFile("assets/character/down_kiemgo.png"))
        std::cerr << "Failed to load down_kiemgo.png\n";
    if (!down_kiemsat.loadFromFile("assets/character/down_kiemsat.png"))
        std::cerr << "Failed to load down_kiemsat.png\n";
    if (!down_riu.loadFromFile("assets/character/down_riu.png"))
        std::cerr << "Failed to load down_riu.png\n";
    if (!down_sung.loadFromFile("assets/character/down_sung.png"))
        std::cerr << "Failed to load down_sung.png\n";
    if (!down_hand.loadFromFile("assets/character/down_hand.png"))
        std::cerr << "Failed to load down_hand.png\n";

    // Left
    if (!left_cung.loadFromFile("assets/character/left_cung.png"))
        std::cerr << "Failed to load left_cung.png\n";
    if (!left_kiemgo.loadFromFile("assets/character/left_kiemgo.png"))
        std::cerr << "Failed to load left_kiemgo.png\n";
    if (!left_kiemsat.loadFromFile("assets/character/left_kiemsat.png"))
        std::cerr << "Failed to load left_kiemsat.png\n";
    if (!left_riu.loadFromFile("assets/character/left_riu.png"))
        std::cerr << "Failed to load left_riu.png\n";
    if (!left_sung.loadFromFile("assets/character/left_sung.png"))
        std::cerr << "Failed to load left_sung.png\n";
    if (!left_hand.loadFromFile("assets/character/left_hand.png"))
        std::cerr << "Failed to load left_hand.png\n";

    sprite.setTexture(down_hand);         // gan hinh anh nha vat cho sprite de ive ra cua so game
    sprite.setPosition(this->x, this->y); // set vi tri cua hinh anh la toa  do cua nhan vat
    sprite.setScale(0.8, 0.8);
    craft_weapon(WeaponType::BareHand);
}

Character::~Character()
{
    for (auto *w : weapons)
    {
        delete w;
        w = nullptr;
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
        exp_max = exp_max + 120;
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
    float speed = 140.f; // ← tốc độ nhân vật

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        move.y -= speed * deltaTime;
        sprite.setTexture(up);
        moving = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        move.y += speed * deltaTime;
        moving = true;
        WeaponType type = weapons[indexWeapon]->get_type();
        switch (type)
        {
        case WeaponType::BareHand:
            sprite.setTexture(down_hand);
            break;
        case WeaponType::WoodenSword:
            sprite.setTexture(down_kiemgo);
            break;
        case WeaponType::IronSwood:
            sprite.setTexture(down_kiemsat);
            break;
        case WeaponType::Ax:
            sprite.setTexture(down_riu);
            break;
        case WeaponType::Bow:
            sprite.setTexture(down_cung);
            break;
        case WeaponType::Gun:
            sprite.setTexture(down_sung);
            break;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        move.x -= speed * deltaTime;
        moving = true;
        WeaponType type = weapons[indexWeapon]->get_type();
        switch (type)
        {
        case WeaponType::BareHand:
            sprite.setTexture(left_hand);
            break;
        case WeaponType::WoodenSword:
            sprite.setTexture(left_kiemgo);
            break;
        case WeaponType::IronSwood:
            sprite.setTexture(left_kiemsat);
            break;
        case WeaponType::Ax:
            sprite.setTexture(left_riu);
            break;
        case WeaponType::Bow:
            sprite.setTexture(left_cung);
            break;
        case WeaponType::Gun:
            sprite.setTexture(left_sung);
            break;
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        move.x += speed * deltaTime;
        moving = true;
        WeaponType type = weapons[indexWeapon]->get_type();
        switch (type)
        {
        case WeaponType::BareHand:
            sprite.setTexture(right_hand);
            break;
        case WeaponType::WoodenSword:
            sprite.setTexture(right_kiemgo);
            break;
        case WeaponType::IronSwood:
            sprite.setTexture(right_kiemsat);
            break;
        case WeaponType::Ax:
            sprite.setTexture(right_riu);
            break;
        case WeaponType::Bow:
            sprite.setTexture(right_cung);
            break;
        case WeaponType::Gun:
            sprite.setTexture(right_sung);
            break;
        }
    }

    if (!moving)
    {
        WeaponType type = weapons[indexWeapon]->get_type();
        switch (type)
        {
        case WeaponType::BareHand:
            sprite.setTexture(down_hand);
            break;
        case WeaponType::WoodenSword:
            sprite.setTexture(down_kiemgo);
            break;
        case WeaponType::IronSwood:
            sprite.setTexture(down_kiemsat);
            break;
        case WeaponType::Ax:
            sprite.setTexture(down_riu);
            break;
        case WeaponType::Bow:
            sprite.setTexture(down_cung);
            break;
        case WeaponType::Gun:
            sprite.setTexture(down_sung);
            break;
        }
    }

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
    for (int i = 0; i < weapons.get_size(); i++)
    {
        if (type == weapons[i]->get_type())
        {
            return true;
        }
    }
    int index = static_cast<int>(type); // lay so nguyen tuong ung voi chi so cong thuc trong mang
    const Recipe &r = recipes[index];   // lay ra cong thuc
    // kiem tra du nguyen lieu khong
    if (bag.getWood() < r.wood || bag.getSand() < r.sand || bag.getStone() < r.stone || bag.getCoal() < r.coal || bag.getIron() < r.iron || bag.getGold() < r.gold || bag.getDiamond() < r.diamond || bag.getEmerald() < r.emerald)
    {
        return false;
    }
    // tru nguyen lieu
    bag.decr_Wood(r.wood);
    bag.decr_Sand(r.sand);
    bag.decr_Stone(r.stone);
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
            static Audio diesound("assets/audio/die.ogg");
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

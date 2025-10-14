#include "Castle.h"

static const String castleTextures[] = {
    "assets/castle/castle_lv1.png",
    "assets/castle/castle_lv2.png",
    "assets/castle/castle_lv3.png",
    "assets/castle/castle_lv4.png",
    "assets/castle/castle_lv5.png"};

Castle::Castle() {}

Castle::Castle(int x, int y, int hp_max, int cost)
    : LivingEntity(x, y, hp_max), level(0), cost(cost)
{
    walkable = false;

    // tai anh lau dai
    if (!texture.loadFromFile("assets/castle/castle_lv0.png"))
        std::cout << "Loi tai anh lau dai\n";

    sprite.setTexture(texture);
    sprite.setScale(0.9f, 0.9f);

    // dat goc toa do o giua day lau dai
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.f, bounds.height);

    // dat vi tri lau dai theo toa do truyen vao
    sprite.setPosition(x, y);

    // thanh mau nen
    hpBarBack.setSize(sf::Vector2f(200.f, 10.f));
    hpBarBack.setFillColor(sf::Color(150, 0, 0));
    hpBarBack.setOutlineColor(sf::Color::Black);
    hpBarBack.setOutlineThickness(1.f);

    // thanh mau chinh
    hpBar.setSize(sf::Vector2f(200.f, 10.f));
    hpBar.setFillColor(sf::Color(0, 255, 0));

    // vi tri co dinh cua thanh mau tren man hinh
    hpBarBack.setPosition(4000.f - 100.f, 1800.f); // can giua (200 rong)
    hpBar.setPosition(4000.f - 100.f, 1800.f);
}

int Castle::get_level() const { return level; }
int Castle::get_cost() const { return cost; }
int Castle::get_hp() const { return hp; }

void Castle::set_level(int value) { level = value; }
void Castle::set_cost(int value) { cost = value; }
void Castle::set_hp(int value) { hp = value; }

void Castle::set_texture(const String &filetexture)
{
    if (!texture.loadFromFile(filetexture.c_str()))
    {
        std::cout << "Loi tai anh: " << filetexture << "\n";
        return;
    }

    sprite.setTexture(texture);
    sprite.setScale(0.9f, 0.9f);

    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.f, bounds.height);
}

void Castle::level_up()
{
    // nang cap lau dai toi da 5 cap
    if (level < 5)
    {
        level++;
        cost += 50;
        hp += 50;
        set_texture(castleTextures[level - 1]);
    }
}

void Castle::update(float deltatime)
{
    // hoi mau theo thoi gian
    int currentHP = get_hp();
    currentHP += static_cast<int>(1 * deltatime);
    if (currentHP > get_hp_max())
        currentHP = get_hp_max();
    set_hp(currentHP);

    // tinh phan tram mau
    float hpPercent = static_cast<float>(currentHP) / get_hp_max();
    float fullWidth = 200.f;
    hpBar.setSize(sf::Vector2f(fullWidth * hpPercent, 10.f));

    // doi mau theo muc mau
    if (hpPercent > 0.5f)
        hpBar.setFillColor(sf::Color(0, 255, 0)); // xanh
    else if (hpPercent > 0.25f)
        hpBar.setFillColor(sf::Color(255, 255, 0)); // vang
    else
        hpBar.setFillColor(sf::Color(255, 0, 0)); // do

    // GIU VI TRI CO DINH cho thanh mau
    hpBarBack.setPosition(4000.f - 100.f, 1500.f);
    hpBar.setPosition(4000.f - 100.f, 1500.f);
}

void Castle::render(sf::RenderWindow &window)
{
    // ve lau dai va thanh mau
    window.draw(sprite);
    window.draw(hpBarBack);
    window.draw(hpBar);
}

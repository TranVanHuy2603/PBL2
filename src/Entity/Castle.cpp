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
    sprite.setScale(1.8f, 1.8f);

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
    hpBarBack.setPosition(x - 100.f, y - bounds.height - 10.f);
    hpBar.setPosition(x - 100.f, y - bounds.height - 10.f);
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
    sprite.setScale(1.8f, 1.8f);

    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.f, bounds.height);
}

void Castle::level_up()
{
    // nang cap lau dai toi da 5 cap
    if (level < 5)
    {
        level++;
        cost += 50 * level;
        hp += 50;
        set_texture(castleTextures[level - 1]);
    }
}

void Castle::update(float deltatime)
{
    // Tính phần trăm HP
    float hpPercent = static_cast<float>(hp) / get_hp_max();
    float hpWidth = 350.f; // chiều rộng thanh HP
    hpBar.setSize(sf::Vector2f(hpWidth * hpPercent, 10.f));

    // đổi màu theo HP
    if (hpPercent > 0.5f) hpBar.setFillColor(sf::Color::Green);
    else if (hpPercent > 0.25f) hpBar.setFillColor(sf::Color::Yellow);
    else hpBar.setFillColor(sf::Color::Red);

    // Vị trí lâu đài
    sf::Vector2f castlePos = sprite.getPosition();
    float scaledHeight = sprite.getLocalBounds().height * sprite.getScale().y;

    // **Cập nhật vị trí HP bar trên đỉnh lâu đài, căn giữa**
    hpBarBack.setPosition(castlePos.x - hpWidth / 2.f, castlePos.y - scaledHeight);
    hpBar.setPosition(castlePos.x - hpWidth / 2.f, castlePos.y - scaledHeight);
}

void Castle::render(sf::RenderWindow &window)
{
    // ve lau dai va thanh mau
    window.draw(sprite);
    window.draw(hpBarBack);
    window.draw(hpBar);
}

#include "Castle.h"

static const String castleTextures[] = {
    // "assets/castle_lv1.png",
    // "assets/castle_lv2.png",
    // "assets/castle_lv3.png",
    // "assets/castle_lv4.png",
    // "assets/castle_lv4.png"
};

Castle::Castle() {}
Castle::Castle(int x, int y, int hp_max, int cost)
       :LivingEntity(x, y, hp_max), level(0), cost(cost)
{ 
    walkable = false; 
    if (!texture.loadFromFile("assets/castle_lv0.png")) cout << "Error load Castle\n";
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
    sprite.setScale(0.2, 0.2);
}

int Castle::get_level() const { return level; }
int Castle::get_cost() const { return cost; }
int Castle::get_hp() const { return hp; }
void Castle::set_level(int value) { level = value;  }
void Castle::set_cost(int value) { cost = value; }
void Castle::set_hp(int value) { hp = value; }
void Castle::set_texture(string filetexture) 
{
    sf::Texture tt;
    tt.loadFromFile(filetexture);
    sprite.setTexture(tt);
}
void Castle::level_up()
{
    if (level <= 5)
    {
        level++;
        cost += 50;
        set_texture(castleTextures[level - 1].c_str());
    }
}

void Castle::update(float deltatime) 
{
    int hp = get_hp();
    hp += static_cast<int>(1 * deltatime); // hoi mau
    if (hp > get_hp_max()) 
    {        
        hp = get_hp_max();
    }
    set_hp(hp);

    set_texture(castleTextures[level].c_str());
}
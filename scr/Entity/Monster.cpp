#include "Monster.h"

Monster::Monster() {}
Monster::Monster(int x, int y, double radius, bool walkable,
                 int hp, int hp_max, int damage,
                 double damage_range, double attack_speed, int gold, int exp)
    : LivingEntity(x, y, radius, walkable, hp, hp_max,
                   damage, damage_range, attack_speed)
{
    this->gold = gold;
    this->exp = exp;
    this->type = "Monster";
}

int Monster::get_gold() const { return gold; }
int Monster::get_exp() const { return exp; }

void Monster::update(float deltaTime) 
{
}

void Monster::draw(sf::RenderWindow &)
{
}

std::string Monster::serialize() const {
    std::ostringstream ss;
    ss << x << "," 
       << y << ","
       << radius << "," 
       << walkable << ","
       << hp << "," 
       << hp_max << ","
       << damage << "," 
       << damage_range << ","
       << attack_speed << ","
       << gold << ","
       << exp;
    return ss.str();
}


void Monster::deserialize(std::istream& in) {
    char comma;

    in >> x >> comma
       >> y >> comma
       >> radius >> comma
       >> walkable >> comma
       >> hp >> comma
       >> hp_max >> comma
       >> damage >> comma
       >> damage_range >> comma
       >> attack_speed >> comma
       >> gold >> comma
       >> exp;
}

#include "Weapons.h"
#include "Monster.h"
#include "Entity.h"
#include "Character.h"
#include <cmath>

using namespace std;

Weapons::Weapons(WeaponType type, int damage, double damage_range, double attack_speed,const string &texture)
    : damage(damage), damage_range(damage_range), attack_speed(attack_speed)
{
    this->texture.loadFromFile(texture);
    this->sprite.setTexture(this->texture);
}

int Weapons::get_damage() { return damage; }
double Weapons::get_damage_range() { return damage_range; }
double Weapons::get_attack_speed() { return attack_speed; }

void Weapons::attack(Quadtree &qt, Character *nv)
{
    sf::FloatRect bound = nv->get_sprite().getGlobalBounds();                          // lay ra hinh chu nhat chua nhan vat
    sf::Vector2f center(bound.left + bound.width / 2.f, bound.top + bound.height / 2); // lay ra tam
    // dung quadtree de lay ra nhung vat the xung quanh nhan vat
    Rect range(center.x, center.y, damage_range, damage_range); // tao mot hinh chu nhat bao quanh vung gay sat thuong
    Vector<Entity *> found;                                     // vecto luu cac vat the xung quanh nhan vat
    qt.query(range, found);                                     // lay ra at hte nam gan nhan vat

    for (auto e : found)
    {
        sf::FloatRect eBound = e->get_sprite().getGlobalBounds();
        sf::Vector2f eCenter(eBound.left + eBound.width / 2.f, eBound.top + eBound.height / 2); // lay ra tam cua tung vat the

        float dx = center.x - eCenter.x;        // lay khoang cach truc x
        float dy = center.y - eCenter.y;        // lay khoang cach truc y
        float d = std::sqrt(dx * dx + dy * dy); // khoang cach thuc te

        if (d > damage_range)
            continue;

        if (Monster *m = dynamic_cast<Monster *>(e))
        {
            m->take_damage(damage);
            if (!m->get_status()) // neu nhu quai chet
            {
                nv->incr_gold(m->get_gold()); // tang vang
                nv->incr_exp(m->get_exp());   // tang exp
                if (nv->get_exp() >= nv->get_exp_max())
                {
                    nv->levelUp(); // tang level
                }
            }
        }
        else if (Resource *r = dynamic_cast<Resource *>(e))
        {
            r->set_status();
            nv->get_bag().add(r->get_type());
            qt.remove(r);
        }
        else
        {

        }
    }
}

void Weapons::draw(sf::RenderWindow &window)
{
    window.draw(this->sprite);
}

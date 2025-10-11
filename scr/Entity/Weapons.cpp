#include "Weapons.h"
#include "Monster.h"
#include "Entity.h"
#include "Character.h"
#include "Audio.h"
#include <cmath>

using namespace std;

Weapons::Weapons(WeaponType type, int damage, double damage_range, double attack_speed,const String &texture, const String &sound)
    : damage(damage), damage_range(damage_range), attack_speed(attack_speed)
{
    this->texture.loadFromFile(texture.c_str()); //load texture tu file hinh anh
    this->sprite.setTexture(this->texture);

    this->attackCooldown = 1 / attack_speed; //thoi gian giua cac lan danh

    this->sound.loadSound(sound.c_str());
}

int Weapons::get_damage() { return damage; }
double Weapons::get_damage_range() { return damage_range; }
double Weapons::get_attack_speed() { return attack_speed; }

void Weapons::attack(Quadtree &qt, Character *nv)
{
    static Audio collectSound("assets/audio/collect.mp3");
    static Audio levelupSound("assets/audio/levelup.mp3");

    if (attackClock.getElapsedTime().asSeconds() < attackCooldown) //neu chua hoi chieu thi bo qua
        return;

    sound.playSound();
    sf::FloatRect bound = nv->get_sprite().getGlobalBounds();                          // lay ra hinh chu nhat chua nhan vat
    sf::Vector2f center(bound.left + bound.width / 2.f, bound.top + bound.height / 2.f); // lay ra tam
    // dung quadtree de lay ra nhung vat the xung quanh nhan vat
    Rect range(center.x, center.y, damage_range, damage_range); // tao mot hinh chu nhat bao quanh vung gay sat thuong
    Vector<Entity *> found;                                     // vecto luu cac vat the xung quanh nhan vat
    qt.query(range, found);  
    if (!found.empty()) cout << "Da tim duoc muc tieu\n";
    else cout << "Khong tim duoc muc tieu\n"; 
                                       // lay ra at hte nam gan nhan vat

    for (auto e : found)
    {
        sf::FloatRect eBound = e->get_sprite().getGlobalBounds();
        sf::Vector2f eCenter(eBound.left + eBound.width / 2.f, eBound.top + eBound.height / 2); // lay ra tam cua tung vat the

        float dx = center.x - eCenter.x;        // lay khoang cach truc x
        float dy = center.y - eCenter.y;        // lay khoang cach truc y
        float d = std::sqrt(dx * dx + dy * dy); // khoang cach thuc te

        if (d > damage_range)
            {
                cout << "Nam ngoai vung\n"; 
                continue;
            }

        if (Monster *m = dynamic_cast<Monster *>(e))
        {
            m->take_damage(damage);
            cout << "Takedamage\n";
            if (!m->get_status()) // neu nhu quai chet
            {
                cout << "Quai chet\n";
                nv->incr_gold(m->get_gold()); // tang vang
                nv->incr_exp(m->get_exp());   // tang exp
                if (nv->get_exp() >= nv->get_exp_max())
                {
                    nv->levelUp(); // tang level
                    levelupSound.playSound();
                }
                qt.remove(m);
            }
        }
        else if (Resource *r = dynamic_cast<Resource *>(e))
        {
            r->take_damage();
            if (!r->get_status())
            {
                collectSound.playSound();
                nv->incr_gold(r->get_gold());
                nv->incr_exp(r->get_exp());

                switch(r->get_type()) {
                    case ResourceType::Wood: nv->get_bag().add(ResourceType::Wood); break;
                    case ResourceType::Stone: nv->get_bag().add(ResourceType::Stone); break;
                    case ResourceType::Sand: nv->get_bag().add(ResourceType::Sand); break;
                    case ResourceType::Coal: nv->get_bag().add(ResourceType::Coal); break;
                    case ResourceType::Iron: nv->get_bag().add(ResourceType::Iron); break;
                    case ResourceType::Gold: nv->get_bag().add(ResourceType::Gold); break;
                    case ResourceType::Diamond: nv->get_bag().add(ResourceType::Diamond); break;
                    case ResourceType::Emerald: nv->get_bag().add(ResourceType::Emerald); break;
                }
                qt.remove(r);
                if (nv->get_exp() >= nv->get_exp_max())
                {
                    nv->levelUp(); // tang level
                    levelupSound.playSound();
                }
                qt.remove(r);
            }
        }
        else
        {

        }
    }
    attackClock.restart(); //reset sau khi tan cong
}

void Weapons::draw(sf::RenderWindow &window)
{
    window.draw(this->sprite);
}

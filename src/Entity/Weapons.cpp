#include "Weapons.h"
#include "Monster.h"
#include "Entity.h"
#include "Character.h"
#include "Quest.h"
#include "Audio.h"
#include <cmath>

using namespace std;

Weapons::Weapons(WeaponType type, const String name, const String path, int damage, double damage_range, double attack_speed, const String &texture, const String &soundPath)
    : type(type), name(name), path(path), damage(damage), damage_range(damage_range), attack_speed(attack_speed)
{
    this->texture.loadFromFile(path.c_str()); // load texture tu file hinh anh
    this->sprite.setTexture(this->texture);

    this->attackCooldown = 1 / attack_speed; // thoi gian giua cac lan danh

    if (!sound.loadSound(soundPath.c_str())) cout << "Loi khi tai am thanh vu khi vi sai duong dan\n";

    attackCircle.setRadius(damage_range);
    attackCircle.setFillColor(sf::Color::Transparent); // trong suốt
    attackCircle.setOutlineColor(sf::Color::Red);      // viền đỏ
    attackCircle.setOutlineThickness(2.5f);
    attackCircle.setOrigin(damage_range, damage_range); // gốc là tâm
}

int Weapons::get_damage() { return damage; }
double Weapons::get_damage_range() { return damage_range; }
double Weapons::get_attack_speed() { return attack_speed; }

void Weapons::attack(Quadtree &qt, Character *nv, Quest &quest)
{
    static Audio collectSound("assets/audio/collect.ogg");
    static Audio levelupSound("assets/audio/levelup.ogg");

    sf::FloatRect bounds = nv->get_sprite().getGlobalBounds();
    sf::Vector2f center(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
    attackCircle.setPosition(center);
    showAttackCircle = true;
    attackCircleClock.restart();

    if (attackClock.getElapsedTime().asSeconds() < attackCooldown) // neu chua hoi chieu thi bo qua
        return;

    sound.playSound();
    sf::FloatRect bound = nv->get_sprite().getGlobalBounds(); // lay ra hinh chu nhat chua nhan vat
    // dung quadtree de lay ra nhung vat the xung quanh nhan vat
    Rect range(center.x, center.y, damage_range + 50, damage_range + 100); // tao mot hinh chu nhat bao quanh vung gay sat thuong
    Vector<Entity *> found;                                     // vecto luu cac vat the xung quanh nhan vat
    qt.query(range, found);
    if (!found.empty())
        cout << "Da tim duoc muc tieu\n";
    else
        cout << "Khong tim duoc muc tieu\n";
    // lay ra at hte nam gan nhan vat

    for (auto e : found)
    {
        sf::FloatRect eBound = e->get_sprite().getGlobalBounds();
        sf::Vector2f eCenter(eBound.left + eBound.width / 2.f, eBound.top + eBound.height / 2); // lay ra tam cua tung vat the

        sf::Vector2f playerCenter(bound.left + bound.width / 2.f, bound.top + bound.height / 2.f);
        sf::Vector2f entityCenter(eBound.left + eBound.width / 2.f, eBound.top + eBound.height / 2.f);

        float dx = playerCenter.x - entityCenter.x;
        float dy = playerCenter.y - entityCenter.y;

        float distance = std::sqrt(dx * dx + dy * dy) - 30;

        if (distance > damage_range)
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
                quest.addTarget(2, *nv);
                quest.addTarget(3, *nv);
                static Audio deathSound("assets/audio/monster_die.ogg");
                deathSound.playSound();
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

                switch (r->get_type())
                {
                case ResourceType::Wood:
                    nv->get_bag().add(ResourceType::Wood);
                    quest.addTarget(0, *nv);
                    break;
                case ResourceType::Stone:
                    nv->get_bag().add(ResourceType::Stone);
                    break;
                case ResourceType::Sand:
                    nv->get_bag().add(ResourceType::Sand);
                    break;
                case ResourceType::Coal:
                    nv->get_bag().add(ResourceType::Coal);
                    break;
                case ResourceType::Iron:
                    nv->get_bag().add(ResourceType::Iron);
                    break;
                case ResourceType::Gold:
                    nv->get_bag().add(ResourceType::Gold);
                    quest.addTarget(5, *nv);
                    break;
                case ResourceType::Diamond:
                    nv->get_bag().add(ResourceType::Diamond);
                    quest.addTarget(1, *nv);
                    break;
                case ResourceType::Emerald:
                    nv->get_bag().add(ResourceType::Emerald);
                    quest.addTarget(4, *nv);
                    break;
                }
                qt.remove(r);
                if (nv->get_exp() >= nv->get_exp_max())
                {
                    nv->levelUp(); // tang level
                    if (nv->get_level() == 5)
                    {
                        quest.addTarget(6, *nv);
                    }
                    levelupSound.playSound();
                }
                qt.remove(r);
            }
        }
        else
        {
        }
    }
    attackClock.restart(); // reset sau khi tan cong
}

void Weapons::draw(sf::RenderWindow &window)
{
    // Nếu đang hiển thị vòng tròn
    if (showAttackCircle)
    {
        window.draw(attackCircle);
        if (attackCircleClock.getElapsedTime().asSeconds() > 0.015f) // hiển thị 0.5 giây
            showAttackCircle = false;
    }
}

WeaponType Weapons::get_type() const { return type; }
String Weapons::get_name() const { return name; }
String Weapons::get_path() const { return path; }
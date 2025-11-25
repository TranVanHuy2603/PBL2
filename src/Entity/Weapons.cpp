#include "Weapons.h"
#include "Monster.h"
#include "Quest.h"
#include <cmath>

using namespace std;

struct TargetPriority
{
    Entity* entity;
    float distance; // khoảng cách tới nhân vật

    TargetPriority() : entity(nullptr), distance(0.f) {}
    TargetPriority(Entity* e, float d) : entity(e), distance(d) {}
};

struct CompareDistance
{
    bool operator()(const TargetPriority& a, const TargetPriority& b) const
    {
        return a.distance < b.distance;
    }
};

Weapons::Weapons(WeaponType type, const String name, const String path, int damage, double damage_range, double attack_speed, const String &texture, const String &soundPath)
    : type(type), name(name), path(path), damage(damage), damage_range(damage_range), attack_speed(attack_speed)
{
    this->texture.loadFromFile(path.c_str()); // load texture tu file hinh anh
    this->sprite.setTexture(this->texture);

    this->attackCooldown = 1 / attack_speed; // thoi gian giua cac lan danh

    if (!sound.loadSound(soundPath.c_str())) cout << "Loi khi tai am thanh vu khi vi sai duong dan\n";

    attackCircle.setRadius(damage_range);
    attackCircle.setFillColor(sf::Color(255, 255, 0, 50)); // trong suốt
    attackCircle.setOrigin(damage_range, damage_range); // gốc là tâm
}

Weapons::~Weapons() {}

int Weapons::get_damage() { return damage; }
double Weapons::get_damage_range() { return damage_range; }
double Weapons::get_attack_speed() { return attack_speed; }

void Weapons::attack(Quadtree &qt, Character *nv, Quest &quest)
{
    static Audio collectSound("assets/audio/collect.ogg");
    static Audio levelupSound("assets/audio/levelup.ogg");
    static Audio deathSound("assets/audio/monster_die.ogg");

    sf::FloatRect bounds = nv->get_sprite().getGlobalBounds();
    sf::Vector2f center(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
    attackCircle.setPosition(center);
    showAttackCircle = true;
    attackCircleClock.restart();

    if (attackClock.getElapsedTime().asSeconds() < attackCooldown)
        return;

    sound.playSound();

    Rect range(center.x, center.y, damage_range * 2 + 30, damage_range * 2 + 30);
    Vector<Entity *> found;
    qt.query(range, found);

    if (found.empty())
    {
        cout << "Khong tim duoc muc tieu\n";
        attackClock.restart();
        return;
    }

    Priorityqueue<TargetPriority, CompareDistance> pq;
    for (auto e : found)
    {
        sf::FloatRect eBound = e->get_sprite().getGlobalBounds();
        sf::Vector2f entityCenter(eBound.left + eBound.width / 2.f, eBound.top + eBound.height / 2.f);

        float dx = center.x - entityCenter.x;
        float dy = center.y - entityCenter.y;
        float distance = sqrt(dx * dx + dy * dy);

        if (distance <= damage_range)
        {
            pq.push(TargetPriority(e, distance));
        }
    }

    while (!pq.isEmpty())
    {
        TargetPriority tp = pq.top();
        pq.pop();
        Entity* e = tp.entity;

        if (Monster *m = dynamic_cast<Monster *>(e))
        {
            m->take_damage(damage);
            if (!m->get_status()) // quái chết
            {
                int newHp = static_cast<int>(nv->get_hp_max() * 0.02f + nv->get_hp());
                nv->set_hp(min(newHp, nv->get_hp_max()));

                quest.addTarget(2, *nv);
                quest.addTarget(3, *nv);

                deathSound.playSound();

                nv->incr_gold(m->get_gold());
                nv->incr_exp(m->get_exp());

                if (nv->get_exp() >= nv->get_exp_max())
                {
                    nv->levelUp();
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
                case ResourceType::Wood: nv->get_bag().add(ResourceType::Wood); quest.addTarget(0, *nv); break;
                case ResourceType::Stone: nv->get_bag().add(ResourceType::Stone); break;
                case ResourceType::Sand: nv->get_bag().add(ResourceType::Sand); break;
                case ResourceType::Coal: nv->get_bag().add(ResourceType::Coal); break;
                case ResourceType::Iron: nv->get_bag().add(ResourceType::Iron); break;
                case ResourceType::Gold: nv->get_bag().add(ResourceType::Gold); quest.addTarget(5, *nv); break;
                case ResourceType::Diamond: nv->get_bag().add(ResourceType::Diamond); quest.addTarget(1, *nv); break;
                case ResourceType::Emerald: nv->get_bag().add(ResourceType::Emerald); quest.addTarget(4, *nv); break;
                }

                if (nv->get_exp() >= nv->get_exp_max())
                {
                    nv->levelUp();
                    if (nv->get_level() == 5) quest.addTarget(6, *nv);
                    levelupSound.playSound();
                }

                qt.remove(r);
            }
        }
    }

    attackClock.restart();
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
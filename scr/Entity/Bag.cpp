#include "Bag.h"

Bag::Bag() {};
void Bag::add(ResourceType type)
{
    switch (type)
    {
    case ResourceType::Wood:
        Wood++;
        break;
    case ResourceType::Stone:
        Stone++;
        break;
    case ResourceType::Sand:
        Sand++;
        break;
    case ResourceType::Coal:
        Coal++;
        break;
    case ResourceType::Iron:
        Iron++;
        break;
    case ResourceType::Gold:
        Gold++;
        break;
    case ResourceType::Diamond:
        Diamond++;
        break;
    case ResourceType::Emerald:
        Emerald++;
        break;
    }
}

bool Bag::consume(ResourceType type, int amount)
{
    switch (type)
    {

    case ResourceType::Wood:
        if (Wood >= amount)
        {
            Wood -= amount;
            return true;
        }
        break;
    case ResourceType::Stone:
        if (Stone >= amount)
        {
            Stone -= amount;
            return true;
        }
        break;
    case ResourceType::Sand:
        if (Sand >= amount)
        {
            Sand -= amount;
            return true;
        }
        break;
    case ResourceType::Coal:
        if (Coal >= amount)
        {
            Coal -= amount;
            return true;
        }
        break;
    case ResourceType::Iron:
        if (Iron >= amount)
        {
            Iron -= amount;
            return true;
        }
        break;
    case ResourceType::Gold:
        if (Gold >= amount)
        {
            Gold -= amount;
            return true;
        }
        break;
    case ResourceType::Diamond:
        if (Diamond >= amount)
        {
            Diamond -= amount;
            return true;
        }
        break;
    case ResourceType::Emerald:
        if (Emerald >= amount)
        {
            Emerald -= amount;
            return true;
        }
        break;
    }
    return false;
}

int Bag::getWood() const { return Wood; }
int Bag::getStone() const { return Stone; }
int Bag::getSand() const { return Sand; }
int Bag::getCoal() const { return Coal; }
int Bag::getIron() const { return Iron; }
int Bag::getGold() const { return Gold; }
int Bag::getDiamond() const { return Diamond; }
int Bag::getEmerald() const { return Emerald; }

int Bag::decr_Wood(int value) { Wood -= value ;}
int Bag::decr_Stone(int value) { Stone -= value; }
int Bag::decr_Sand(int value) { Sand -= value; }
int Bag::decr_Coal(int value) { Coal -= value; }
int Bag::decr_Iron(int value) { Iron -= value; }
int Bag::decr_Gold(int value) { Gold -= value; }
int Bag::decr_Diamond(int value) { Diamond -= value; }
int Bag::decr_Emerald(int value) { Emerald -= value; }
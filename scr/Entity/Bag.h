#pragma once
#include "Resource.h"
#include <string>

using namespace std;

class Bag
{
private:
    int Wood;    // Go
    int Stone;   // Đa
    int Sand;    // Cat
    int Coal;    // Than
    int Iron;    // Sat
    int Gold;    // Vang
    int Diamond; // Kim cuong
    int Emerald;

public:
    Bag();
    void add(ResourceType);
    bool consume(ResourceType, int);
    int getQuantity(ResourceType);
    int getWood() const;
    int getStone() const;
    int getSand() const;
    int getCoal() const;
    int getIron() const;
    int getGold() const;
    int getDiamond() const;
    int getEmerald() const;
};
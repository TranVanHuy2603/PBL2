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

    void decr_Wood(int);
    void decr_Stone(int);
    void decr_Sand(int);
    void decr_Coal(int);
    void decr_Iron(int);
    void decr_Gold(int);
    void decr_Diamond(int);
    void decr_Emerald(int);
};
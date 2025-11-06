#pragma once

#include <SFML/Graphics.hpp>
#include "CharacterUI.h"
#include "WeaponCraftUI.h"
#include "UpgradeCastleUI.h"
#include "Character.h"
#include "Castle.h"

class UIManager
{
private:
    CharacterUI characterUI;
    WeaponCraftUI weaponCraftUI;
    UpgradeCastleUI upgradeCastleUI;

public:
    UIManager();

    void handleEvent(sf::Event& event, sf::RenderWindow& window, Character* player, Castle* castle);
    void update(const Character* player, const sf::RenderWindow& window);
    void render(sf::RenderWindow& window);
};
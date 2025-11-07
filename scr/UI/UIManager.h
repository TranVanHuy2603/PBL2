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
    // const sf::Font& font;
    CharacterUI characterUI;
    WeaponCraftUI weaponCraftUI;
    UpgradeCastleUI upgradeCastleUI;

public:
    UIManager(const sf::Font& font);

    void handleEvent(sf::Event& event, sf::RenderWindow& window, Character* player, Castle* castle);
    void update(const Character* player, const sf::RenderWindow& window);
    void render(sf::RenderWindow& window);
};
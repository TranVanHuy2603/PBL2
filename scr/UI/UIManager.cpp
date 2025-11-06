#include "UIManager.h"

UIManager::UIManager()
{
    // Hàm khởi tạo có thể để trống vì các đối tượng UI đã tự khởi tạo
}

void UIManager::handleEvent(sf::Event& event, sf::RenderWindow& window, Character* player, Castle* castle)
{
    // Chuyển sự kiện đến các thành phần UI có tương tác
    weaponCraftUI.handleEvent(event, player);
    upgradeCastleUI.handleEvent(event, player, castle);
}

void UIManager::update(const Character* player, const sf::RenderWindow& window)
{
    // Cập nhật các thành phần UI cần thay đổi mỗi frame (như thanh HP, tài nguyên)
    characterUI.update(player, window);
}

void UIManager::render(sf::RenderWindow& window)
{
    // Vẽ tất cả các thành phần UI lên màn hình
    // Thứ tự vẽ rất quan trọng
    characterUI.render(window);
    upgradeCastleUI.render(window);
    weaponCraftUI.render(window);
}
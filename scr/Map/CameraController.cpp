#include "CameraController.h"

CameraController::CameraController(const sf::Vector2f& windowSize, const sf::FloatRect& bounds)
    : worldBounds(bounds), moveSpeed(300.f), zoomLevel(1.f)
{
    view.setSize(windowSize);
    view.setCenter(windowSize / 2.f); // ban đầu ở giữa cửa sổ
}

void CameraController::handleInput(const sf::RenderWindow& window, float deltaTime) {
    sf::Vector2f move(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        move.y -= moveSpeed * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        move.y += moveSpeed * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        move.x -= moveSpeed * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        move.x += moveSpeed * deltaTime;

    view.move(move);
    clampToBounds();

    // zoom bằng chuột cuộn
    if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {
        // nhấn giữ chuột giữa + lăn sẽ zoom
    }
}

void CameraController::follow(const sf::Vector2f& target) {
    view.setCenter(target);
    clampToBounds();
}

void CameraController::zoom(float factor) {
    zoomLevel *= factor;
    view.zoom(factor);
    clampToBounds();
}

const sf::View& CameraController::getView() const {
    return view;
}

void CameraController::setCenter(const sf::Vector2f& center) {
    view.setCenter(center);
    clampToBounds();
}

void CameraController::clampToBounds() {
    sf::Vector2f size = view.getSize();
    sf::Vector2f center = view.getCenter();

    float halfW = size.x / 2.f;
    float halfH = size.y / 2.f;

    if (center.x - halfW < worldBounds.left)
        center.x = worldBounds.left + halfW;
    if (center.y - halfH < worldBounds.top)
        center.y = worldBounds.top + halfH;
    if (center.x + halfW > worldBounds.left + worldBounds.width)
        center.x = worldBounds.left + worldBounds.width - halfW;
    if (center.y + halfH > worldBounds.top + worldBounds.height)
        center.y = worldBounds.top + worldBounds.height - halfH;

    view.setCenter(center);
}

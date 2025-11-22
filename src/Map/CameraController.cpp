#include "CameraController.h"
#include <algorithm>

CameraController::CameraController(const sf::Vector2f& windowSize, const sf::FloatRect& bounds)
    : worldBounds(bounds), moveSpeed(300.f), zoomLevel(1.0f)
{
    view.setSize(windowSize);
    view.setCenter(windowSize / 2.f); // ban đầu ở giữa cửa sổ
}

void CameraController::handleInput(const sf::RenderWindow& window, float deltaTime) {
    sf::Vector2f move(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) move.y -= moveSpeed * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) move.y += moveSpeed * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) move.x -= moveSpeed * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) move.x += moveSpeed * deltaTime;

    view.move(move);
    clampToBounds();

}

void CameraController::handleEvent(const sf::Event &event)
{
    if (event.type == sf::Event::MouseWheelScrolled &&
        event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
    {
        float factor = 1.f;
        if (event.mouseWheelScroll.delta > 0)
            factor = 1.f - zoomSpeed; // zoom in
        else
            factor = 1.f + zoomSpeed; // zoom out

        zoom(factor);
    }

    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::F)
        {
            zoom(1.f + zoomSpeed);
        }
        else if (event.key.code == sf::Keyboard::G)
        {
            zoom(1.f - zoomSpeed);
        }
    }
}

void CameraController::follow(const sf::Vector2f& target) {
    view.setCenter(target);
    clampToBounds();
}

void CameraController::zoom(float factor) {
    float newZoom = zoomLevel * factor;
    newZoom = std::clamp(newZoom, minZoom, maxZoom);
    factor = newZoom / zoomLevel;

    zoomLevel = newZoom;
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

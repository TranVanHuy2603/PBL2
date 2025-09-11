#include <SFML/Graphics.hpp>

int HEIGHT = 900;
int WEIGHT = 1300;
const int size = 50;
struct SnakeSegment
{
    int x, y;
};

enum Direction {Up, Down, Left, Right};

int main()
{
    sf::RenderWindow window(sf::VideoMode(WEIGHT, HEIGHT), "Ran san moi");
    window.setFramerateLimit(8);
    sf::Event event;

    std::vector<SnakeSegment> snake = {{WEIGHT / 2 / size, HEIGHT / 2 / size}};
    SnakeSegment food = {rand() % (WEIGHT / size), rand() % (HEIGHT / size)};
    Direction dir = Right;
    bool check = true;

    sf::Font font;
    if (!font.loadFromFile("assets/arial.ttf")) return -1;

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if ((event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left) && dir != Left) dir = Left;
                else if ((event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right) && dir != Right) dir = Right;
                else if ((event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up) && dir != Up) dir = Up;
                else if ((event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down) && dir != Down) dir = Down;
            }
        }

        if (check)
        {
            SnakeSegment newHead = snake.front();
            switch (dir)
            {
                case Up: newHead.y--; break;
                case Down: newHead.y++; break;
                case Left: newHead.x--; break;
                case Right: newHead.x++; break;
            }

            if (newHead.x < 0 || newHead.x >= WEIGHT / size || newHead.y < 0 || newHead.y >= HEIGHT / size)
            {
                check = false;
            }

            for (auto &segmennt : snake) 
            {
                if (newHead.x == segmennt.x && newHead.y == segmennt.y)
                {
                    check = false;
                }
            }

            snake.insert(snake.begin(), newHead);

            if (newHead.x == food.x && newHead.y == food.y) 
            {
                int border_thickness = 2; 
                food.x = border_thickness + rand() % ((WEIGHT / size) - 2 * border_thickness);
                food.y = border_thickness + rand() % ((HEIGHT / size) - 2 * border_thickness);

            }
            else 
            {
                snake.pop_back();
            }
        }

        window.clear(sf::Color::Cyan);

        float thickness = 20.f;
        sf::RectangleShape border(sf::Vector2f(WEIGHT - thickness, HEIGHT - thickness));
        border.setFillColor(sf::Color::Transparent);
        border.setOutlineThickness(thickness);
        border.setOutlineColor(sf::Color::Red);
        border.setPosition(thickness / 2, thickness / 2);
        window.draw(border);

            sf::RectangleShape rect(sf::Vector2f(size - 1, size - 1));
            rect.setFillColor(sf::Color::Green);
            for (auto &seg : snake)
            {
                rect.setPosition(seg.x * size, seg.y * size);
                window.draw(rect);
            }

            sf::CircleShape cir(size / 2);
            cir.setFillColor(sf::Color::Red);
            cir.setPosition(food.x * size, food.y * size);
            window.draw(cir);
        if (!check)
        {
            sf::Text gameOver;
            gameOver.setFont(font);
            gameOver.setString("GAME OVER");
            gameOver.setCharacterSize(120); // kích thước chữ
            gameOver.setFillColor(sf::Color::Red);

            // Căn giữa cửa sổ
            float x = (WEIGHT - gameOver.getLocalBounds().width) / 2;
            float y = (HEIGHT - gameOver.getLocalBounds().height) / 2;
            gameOver.setPosition(x, y);
            window.draw(gameOver);
        }
        window.display();
    }
    return 0;
}

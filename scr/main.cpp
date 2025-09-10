#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>

int main()
{
    sf::RenderWindow window(sf::VideoMode(900.f, 900.f), "Flappy Bird");

    sf::Texture chim;
    if (!chim.loadFromFile("Data/chim.png")) return -1;

    sf::Sprite bird;
    bird.setTexture(chim);
    bird.setPosition(100.f, 300.f);
    bird.setScale(0.12f, 0.12f);

    float birdV = 0.f;
    const float g = 600.f;
    const float jumpStrength = -250.f;

    sf::Music bgMusic;
    if (!bgMusic.openFromFile("Data/background.ogg"))
    return -1; 
    bgMusic.setLoop(true);  
    bgMusic.play(); 
    bgMusic.setVolume(100.f);

    sf::Texture gameOverTex;
    if (!gameOverTex.loadFromFile("Data/overbgr.jpg")) return -1;
    sf::Sprite gameOverSprite;
    gameOverSprite.setTexture(gameOverTex);
    gameOverSprite.setScale(0.5f, 0.5f); 
    gameOverSprite.setPosition(150.f, 0.f);

    sf::SoundBuffer jumpBuffer;
    if (!jumpBuffer.loadFromFile("Data/jump.ogg")) return -1;
    sf::Sound jumpSound;
    jumpSound.setBuffer(jumpBuffer);
    jumpSound.setVolume(70.f);

    sf::SoundBuffer gameOverBuffer;
    if (!gameOverBuffer.loadFromFile("Data/gameover.ogg")) return -1;
    sf::Sound gameOverSound;
    gameOverSound.setBuffer(gameOverBuffer);
    gameOverSound.setVolume(100.f);

    std::vector<sf::RectangleShape> obstacles;
    const float obstacleWidth = 80.f;
    const float gapHeight = 250.f;
    const float osbtacleSpeeed = 200.f;
    sf::Clock spawnClock;

    int score = 0;
    sf::Font font;
    if (!font.loadFromFile("Data/arial.ttf")) return -1;

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(50);
    scoreText.setFillColor(sf::Color::Black);
    scoreText.setPosition(15.f, 15.f);

    sf::Clock clock;
    bool gameOver = false;
    bool playedGameOverSound = false;

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    while (window.isOpen())
    {
        sf::Event event;
        sf::Time dt = clock.restart();
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (!gameOver && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
            {
                birdV = jumpStrength;
                jumpSound.play();
            }
        }
        if (!gameOver)
        {
            birdV += g * dt.asSeconds();
            bird.move(0.f, birdV * dt.asSeconds());

            if (spawnClock.getElapsedTime().asSeconds() > 2.f)
            {
                spawnClock.restart();
                float gapY = 100.f + static_cast<float>(std::rand() % 300);

                sf::RectangleShape top(sf::Vector2f(obstacleWidth, gapY));
                top.setFillColor(sf::Color::Green);
                top.setPosition(800.f, 0.f);

                sf::RectangleShape bottom(sf::Vector2f(obstacleWidth, 900.f - gapY - gapHeight));
                bottom.setFillColor(sf::Color::Green);
                bottom.setPosition(800.f, gapY + gapHeight);

                obstacles.push_back(top);
                obstacles.push_back(bottom);
            }
            
            for (auto& obs : obstacles)
            {
                obs.move(-osbtacleSpeeed * dt.asSeconds(), 0.f);
            }
            
            obstacles.erase(std::remove_if(obstacles.begin(), obstacles.end(),
                [](sf::RectangleShape& obs){ return obs.getPosition().x + obs.getSize().x < 0; }),
                obstacles.end());
            
                for (auto& obs : obstacles)
            {
                if (bird.getGlobalBounds().intersects(obs.getGlobalBounds()))
                {
                    gameOver = true;
                    break;
                }
            }

            if (bird.getPosition().y > 600.f || bird.getPosition().y < 0.f)
                gameOver = true;

            for (auto& obs : obstacles)
            {
                if (!gameOver && obs.getPosition().x + obstacleWidth < bird.getPosition().x && obs.getFillColor() == sf::Color::Green)
                {
                    score += 1;
                    obs.setFillColor(sf::Color::Red);
                }
            }

            scoreText.setString("Score: " + std::to_string(score / 2));
        }
        window.clear(sf::Color::Cyan);
        window.draw(bird);
        for (auto& obs : obstacles)
            window.draw(obs);
        window.draw(scoreText);

        if (gameOver)
        {
            sf::Text gameOverText;
            gameOverText.setFont(font);
            gameOverText.setCharacterSize(80);
            gameOverText.setFillColor(sf::Color::Red);
            gameOverText.setString("GAME OVER");
            gameOverText.setPosition(250.f, 250.f);
            window.draw(gameOverSprite);
            if (!playedGameOverSound) {
            gameOverSound.play();
            playedGameOverSound = true;
    }
        }

        window.display();
    }
    return 0;
}

#include <Graphics.hpp>
#include <System.hpp>
#include <Window.hpp>
#include <cmath>

int main()
{
    constexpr float speedX = 100.f;
    constexpr float amplitudeY = 80.f;
    constexpr float periodY = 2;
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;
    constexpr float BALL_SIZE = 40;
    sf::Vector2f speed = { 100.f, 75.f };
    const sf::Vector2f position = { 10, 350 };

    sf::RenderWindow window(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), "Sinusoid");
    sf::Clock clock;

    sf::CircleShape shape(BALL_SIZE);
    shape.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        const float time = clock.getElapsedTime().asSeconds();
        const float wavePhase = time * float(2 * M_PI);
        const float x = speedX * time;
        const float y = amplitudeY * std::sin(wavePhase / periodY);
        const sf::Vector2f offset = { x, y };

        shape.setPosition(position + offset);

        window.clear();
        window.draw(shape);
        window.display();
    }
}
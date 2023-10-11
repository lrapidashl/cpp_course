#include <Graphics.hpp>
#include <cmath>
#include <iostream>

float toDegrees(double radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

sf::Sprite initSprite(sf::Texture& texture, const std::string& spriteName)
{
    if (!texture.loadFromFile(spriteName))
    {
        exit(-1);
    }
    texture.setSmooth(true);
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setOrigin((float)texture.getSize().x / 2, (float)texture.getSize().y / 2);
    return sprite;
}

void onMouseRelease(const sf::Event::MouseButtonEvent& event, sf::Vector2f& releasePosition)
{
    releasePosition = { float(event.x), float(event.y) };
}

void pollEvents(sf::RenderWindow& window, sf::Vector2f& releasePosition)
{
    sf::Event event{};
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonReleased:
                onMouseRelease(event.mouseButton, releasePosition);
                break;
            default:
                break;
        }
    }
}

void updateBoar(float deltaTime, sf::Sprite& boar, sf::Sprite& knight)
{
    const float speed = 200;

    const sf::Vector2f boarPosition = boar.getPosition();
    const sf::Vector2f knightPosition = knight.getPosition();
    const sf::Vector2f deltaPosition = knightPosition - boarPosition;
    const auto deltaPositionLength = (float)std::sqrt(std::pow(deltaPosition.x, 2) + std::pow(deltaPosition.y, 2));

    if (boarPosition.x > knightPosition.x)
    {
        boar.setScale(-1, 1);
    }
    else if (boarPosition.x < knightPosition.x)
    {
        boar.setScale(1, 1);
    }

    sf::Vector2f direction = { 0, 0 };
    if (deltaPositionLength != 0)
    {
        direction = {deltaPosition.x / deltaPositionLength, deltaPosition.y / deltaPositionLength};
    }
    const sf::Vector2f positionOffset = direction * speed * deltaTime;

    boar.move(positionOffset);
}

void updateKnight(sf::Sprite& knight, sf::Vector2f releasePosition)
{
    const sf::Vector2f position = knight.getPosition();
    if (position.x > releasePosition.x)
    {
        knight.setScale(-1, 1);
    }
    else if (position.x < releasePosition.x)
    {
        knight.setScale(1, 1);
    }
    knight.setPosition(releasePosition);
}

void update(sf::Clock& clock, sf::Sprite& boar, sf::Sprite& knight, sf::Vector2f releasePosition)
{
    const float deltaTime = clock.restart().asSeconds();
    updateBoar(deltaTime, boar, knight);
    updateKnight(knight, releasePosition);
}

void redrawFrame(sf::RenderWindow& window, sf::Sprite& boar, sf::Sprite& knight)
{
    window.clear(sf::Color::White);
    window.draw(knight);
    window.draw(boar);
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
            sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }),
            "Prints mouse events to terminal",
            sf::Style::Default,
            settings);
    sf::Clock clock;

    sf::Texture boarTexture;
    sf::Texture knightTexture;
    sf::Sprite boar = initSprite(boarTexture, "Baton.png");
    sf::Sprite knight = initSprite(knightTexture, "Knight.png");
    knight.setPosition({ 400, 300 });
    sf::Vector2f releasePosition;
    while (window.isOpen())
    {
        pollEvents(window, releasePosition);
        update(clock, boar, knight, releasePosition);
        redrawFrame(window, boar, knight);
    }
}
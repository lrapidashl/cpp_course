#include <Graphics.hpp>
#include <cmath>
#include <algorithm>

float toDegrees(double radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

void init(sf::ConvexShape& pointer)
{
    pointer.setPointCount(3);
    pointer.setPoint(0, { 40, 0 });
    pointer.setPoint(1, { -20, -20 });
    pointer.setPoint(2, { -20, 20 });
    pointer.setPosition({ 400, 300 });
    pointer.setFillColor(sf::Color(0xFF, 0x80, 0x00));
}

void onMouseMove(const sf::Event::MouseMoveEvent& event, sf::Vector2f& mousePosition)
{
    mousePosition = { float(event.x), float(event.y) };
}

void pollEvents(sf::RenderWindow& window, sf::Vector2f& mousePosition)
{
    sf::Event event{};
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseMoved:
                onMouseMove(event.mouseMove, mousePosition);
                break;
            default:
                break;
        }
    }
}

void update(sf::Clock& clock, const sf::Vector2f& mousePosition, sf::ConvexShape& pointer)
{
    const float deltaTime = clock.restart().asSeconds();
    const float rotationSpeed = 100;
    float rotation = pointer.getRotation();

    const sf::Vector2f delta = mousePosition - pointer.getPosition();
    const double angle = atan2(double(delta.y), double(delta.x));
    float newRotation = toDegrees(angle);
    if (std::abs(rotation - newRotation) > std::abs(rotation - newRotation - 360))
    {
        newRotation = newRotation + 360;
    }

    float rotationDirect = 0;
    if (rotation > newRotation)
    {
        rotationDirect = -1;
    }
    else if (rotation < newRotation)
    {
        rotationDirect = 1;
    }

    pointer.setRotation(pointer.getRotation() + rotationDirect * rotationSpeed * deltaTime);
}

void redrawFrame(sf::RenderWindow& window, sf::ConvexShape& pointer)
{
    window.clear();
    window.draw(pointer);
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

    sf::ConvexShape pointer;
    sf::Vector2f mousePosition;

    init(pointer);
    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        update(clock, mousePosition, pointer);
        redrawFrame(window, pointer);
    }
}
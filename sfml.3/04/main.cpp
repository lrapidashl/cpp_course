#include <Graphics.hpp>
#include <cmath>
#include <algorithm>
#include <iostream>

struct Arrow
{
    sf::ConvexShape head;
    sf::RectangleShape stem;
    sf::Vector2f position;
    float rotation = 0;
};

sf::Vector2f toCartesian(float radius, float angle)
{
    return {
        radius * std::cos(angle),
        radius * std::sin(angle),
    };
}

float toDegrees(double radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

float toRadians(float angle)
{
    return angle * (float)M_PI / 180;
}

void updateArrowElements(Arrow& arrow)
{
    const sf::Vector2f headOffset = toCartesian(40, arrow.rotation);
    arrow.head.setPosition(arrow.position + headOffset);
    arrow.head.setRotation(toDegrees(arrow.rotation));

    const sf::Vector2f stemOffset = toCartesian(-10, arrow.rotation);
    arrow.stem.setPosition(arrow.position + stemOffset);
    arrow.stem.setRotation(toDegrees(arrow.rotation));
}

void initArrow(Arrow& arrow)
{
    arrow.position = {400, 300 };

    arrow.head.setPointCount(3);
    arrow.head.setPoint(0, { 40, 0 });
    arrow.head.setPoint(1, { -20, -20 });
    arrow.head.setPoint(2, { -20, 20 });
    arrow.head.setFillColor(sf::Color(0xFF, 0x00, 0x00));

    arrow.stem.setSize({ 80, 20 });
    arrow.stem.setOrigin({ 40, 10 });
    arrow.stem.setFillColor((sf::Color(0xF0, 0xA0, 0x00)));

    updateArrowElements(arrow);
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

void update(sf::Clock& clock, const sf::Vector2f& mousePosition, Arrow& arrow)
{
    const float deltaTime = clock.restart().asSeconds();
    const float rotationSpeed = 100;
    float rotation = toDegrees(arrow.rotation);

    const sf::Vector2f delta = mousePosition - arrow.position;
    const double angle = atan2(double(delta.y), double(delta.x));
    auto newRotation = toDegrees((float)angle);
    if (std::abs(rotation - newRotation) > std::abs(rotation - newRotation + 360))
    {
        newRotation = newRotation - 360;
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

    std::cout << arrow.rotation << ' ' << newRotation << std::endl;

    arrow.rotation += toRadians(rotationDirect * rotationSpeed * deltaTime);

    updateArrowElements(arrow);
}

void redrawFrame(sf::RenderWindow& window, Arrow& arrow)
{
    window.clear();
    window.draw(arrow.stem);
    window.draw(arrow.head);
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

    Arrow arrow;
    sf::Vector2f mousePosition;

    initArrow(arrow);
    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        update(clock, mousePosition, arrow);
        redrawFrame(window, arrow);
    }
}
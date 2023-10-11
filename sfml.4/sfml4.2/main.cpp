#include <Graphics.hpp>
#include <cmath>

float toDegrees(double radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

void init(sf::ConvexShape& arrow)
{
    arrow.setPointCount(7);
    arrow.setPoint(0, { -50, -20 });
    arrow.setPoint(1, { 0, -20 });
    arrow.setPoint(2, { 0, -40 });
    arrow.setPoint(3, { 50, 0 });
    arrow.setPoint(4, { 0, 40 });
    arrow.setPoint(5, { 0, 20 });
    arrow.setPoint(6, { -50, 20 });
    arrow.setPosition({ 400, 300 });
    arrow.setFillColor(sf::Color::Yellow);
    arrow.setOutlineColor(sf::Color::Black);
    arrow.setOutlineThickness(2);
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

void update(sf::Clock& clock, sf::ConvexShape& arrow, sf::Vector2f mousePosition)
{
    const float speed = 200;
    const float rotationSpeed = 900;
    const float deltaTime = clock.restart().asSeconds();

    const sf::Vector2f position = arrow.getPosition();
    const sf::Vector2f deltaPosition = mousePosition - position;
    const auto deltaPositionLength = (float)std::sqrt(std::pow(deltaPosition.x, 2) + std::pow(deltaPosition.y, 2));

    sf::Vector2f direction = { 0, 0 };
    if (deltaPositionLength != 0)
    {
        direction = {deltaPosition.x / deltaPositionLength, deltaPosition.y / deltaPositionLength};
    }
    const sf::Vector2f positionOffset = direction * speed * deltaTime;

    const float rotation = arrow.getRotation();
    const double angle = atan2(double(deltaPosition.y), double(deltaPosition.x));
    float newRotation = toDegrees(angle);
    if (std::abs(rotation - newRotation) > std::abs(rotation - newRotation - 360))
    {
        newRotation = newRotation + 360;
    }

    float rotationDirection = 0;
    if (rotation > newRotation)
    {
        rotationDirection = -1;
    }
    else if (rotation < newRotation)
    {
        rotationDirection = 1;
    }

    const float rotationOffset = rotationDirection * rotationSpeed * deltaTime;

    arrow.move(positionOffset);
    arrow.rotate(rotationOffset);
}

void redrawFrame(sf::RenderWindow& window, sf::ConvexShape& arrow)
{
    window.clear(sf::Color::White);
    window.draw(arrow);
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

    sf::ConvexShape arrow;
    sf::Vector2f mousePosition;


    init(arrow);
    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        update(clock, arrow, mousePosition);
        redrawFrame(window, arrow);
    }
}
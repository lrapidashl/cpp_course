#include <Graphics.hpp>

void init(sf::ConvexShape& arrow)
{
    arrow.setPointCount(7);
    arrow.setPoint(0, { -20, 50 });
    arrow.setPoint(1, { -20, 0 });
    arrow.setPoint(2, { -40, 0 });
    arrow.setPoint(3, { 0, -50 });
    arrow.setPoint(4, { 40, 0 });
    arrow.setPoint(5, { 20, 0 });
    arrow.setPoint(6, { 20, 50 });
    arrow.setPosition({ 400, 300 });
    arrow.setFillColor(sf::Color::Yellow);
    arrow.setOutlineColor(sf::Color::Black);
    arrow.setOutlineThickness(2);
}

void pollEvents(sf::RenderWindow& window)
{
    sf::Event event{};
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
        }
    }
}

void update(sf::ConvexShape& pointer)
{
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

    init(arrow);
    while (window.isOpen())
    {
        pollEvents(window);
        update(arrow);
        redrawFrame(window, arrow);
    }
}
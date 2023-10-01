#include <Graphics.hpp>
#include <System.hpp>
#include <Window.hpp>
#include <cmath>

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;
    constexpr int pointCount = 200;
    constexpr float rotationSpeed = 100;
    constexpr float traectoryRadius = 100;
    constexpr float speed = 100;
    float currAngle = 0;
    sf::Vector2f position = { 400, 300 };
    float roseAngle = 0;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
            sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), "rose",
            sf::Style::Default, settings);

    sf::Clock clock;

    sf::ConvexShape rose;
    rose.setPosition(position);
    rose.setFillColor(sf::Color(0xFF, 0x09, 0x80));

    sf::ConvexShape roadCircle;
    roadCircle.setPosition(position);
    roadCircle.setFillColor(sf::Color::White);

    sf::ConvexShape roadInnerCircle;
    roadInnerCircle.setPosition(position);
    roadInnerCircle.setFillColor(sf::Color::Black);

    rose.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; pointNo++)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        float roseRadius = 200 * std::sin(6 * angle);
        sf::Vector2f point = {
            roseRadius * std::sin(angle),
            roseRadius * std::cos(angle)
        };
        rose.setPoint(pointNo, point);
    }

    roadCircle.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; pointNo++)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = {
                (traectoryRadius + 210) * std::sin(angle),
                (traectoryRadius + 210) * std::cos(angle)
        };
        roadCircle.setPoint(pointNo, point);
    }

    roadInnerCircle.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; pointNo++)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = {
                (traectoryRadius + 200) * std::sin(angle),
                (traectoryRadius + 200) * std::cos(angle)
        };
        roadInnerCircle.setPoint(pointNo, point);
    }

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

        const float deltaTime = clock.restart().asSeconds();
        currAngle += float(2 * M_PI) / float(360 / speed / deltaTime);
        sf::Vector2f offset = {
                traectoryRadius * std::sin(currAngle),
                traectoryRadius * std::cos(currAngle)
        };
        roseAngle += deltaTime * rotationSpeed;
        rose.setPosition(position + offset);
        rose.setRotation(roseAngle);

        window.clear();
        window.draw(roadCircle);
        window.draw(roadInnerCircle);
        window.draw(rose);
        window.display();
    }
}
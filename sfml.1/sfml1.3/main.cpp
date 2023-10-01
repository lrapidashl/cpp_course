#include <Graphics.hpp>
#include <System.hpp>
#include <Window.hpp>

void drawCircle(sf::RenderWindow& window, float x, float y, float r, sf::Color c)
{
    sf::CircleShape shape(r);
    shape.setPosition({ x, y });
    shape.setFillColor(c);
    window.draw(shape);
}

void drawRectangle(sf::RenderWindow& window, float x, float y, float w, float h, sf::Color c, float r = 0)
{
    sf::RectangleShape shape;
    shape.setSize({ w, h });
    shape.setRotation(r);
    shape.setPosition({ x, y });
    shape.setFillColor(c);
    window.draw(shape);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 740, 700 }), "House");

    window.clear();

    sf::ConvexShape roof;
    roof.setFillColor(sf::Color(0x5D, 0x1E, 0x17));
    roof.setPointCount(4);
    roof.setPoint(0, { 20, 380 });
    roof.setPoint(1, { 225, 235 });
    roof.setPoint(2, { 515, 235 });
    roof.setPoint(3, { 720, 380 });
    window.draw(roof);

    drawCircle(window, 470, 145, 20, sf::Color(0xBF, 0xBF, 0xBF));
    drawCircle(window, 480, 115, 25, sf::Color(0xBF, 0xBF, 0xBF));
    drawCircle(window, 500, 70, 30, sf::Color(0xBF, 0xBF, 0xBF));
    drawCircle(window, 520, 20, 35, sf::Color(0xBF, 0xBF, 0xBF));

    drawRectangle(window, 70, 380, 600, 300, sf::Color(0x4D, 0x2E, 0x0B));
    drawRectangle(window, 125, 470, 90, 210, sf::Color(0x18, 0x17, 0x17));
    drawRectangle(window, 455, 230, 40, 80, sf::Color(0x3B, 0x38, 0x38));
    drawRectangle(window, 440, 180, 70, 50, sf::Color(0x3B, 0x38, 0x38));

    window.display();

    sf::sleep(sf::seconds(5));
}
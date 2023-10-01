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
    sf::RenderWindow window(sf::VideoMode({ 140, 370 }), "Traffic light");

    window.clear();

    drawRectangle(window, 20, 20, 100, 330, sf::Color(0x43, 0x43, 0x43));
    drawCircle(window, 25, 35, 45, sf::Color(0x0, 0x8D, 0x0F));
    drawCircle(window, 25, 140, 45, sf::Color(0xFF, 0xCC, 0x26));
    drawCircle(window, 25, 245, 45, sf::Color(0xF2, 0x0, 0x0));

    window.display();

    sf::sleep(sf::seconds(5));
}
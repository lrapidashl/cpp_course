#include <D:/CppDistro/MinGW/include/SFML/Graphics.hpp>
#include <D:/CppDistro/MinGW/include/SFML/System.hpp>
#include <D:/CppDistro/MinGW/include/SFML/Window.hpp>

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
    sf::RenderWindow window(sf::VideoMode({ 420, 200 }), "OAD");

    window.clear();

    drawCircle(window, 20, 20, 50, sf::Color::White);
    drawCircle(window, 30, 30, 40, sf::Color::Black);
    drawRectangle(window, 20, 70, 100, 50, sf::Color::Black);
    drawCircle(window, 20, 80, 50, sf::Color::White);
    drawCircle(window, 30, 90, 40, sf::Color::Black);
    drawRectangle(window, 20, 80, 100, 50, sf::Color::Black);
    drawRectangle(window, 20, 70, 10, 60, sf::Color::White);
    drawRectangle(window, 110, 70, 10, 60, sf::Color::White);

    drawRectangle(window, 200, 20, 10, 167, sf::Color::Blue, -18);
    drawRectangle(window, 200, 20, 10, 167, sf::Color::Blue, 18);
    drawRectangle(window, 170, 120, 70, 10, sf::Color::Blue);

    drawCircle(window, 300, 20, 50, sf::Color::Red);
    drawCircle(window, 310, 30, 40, sf::Color::Black);
    drawRectangle(window, 300, 70, 100, 50, sf::Color::Black);
    drawRectangle(window, 300, 20, 50, 100, sf::Color::Black);
    drawCircle(window, 300, 80, 50, sf::Color::Red);
    drawCircle(window, 310, 90, 40, sf::Color::Black);
    drawRectangle(window, 300, 80, 100, 50, sf::Color::Black);
    drawRectangle(window, 300, 80, 50, 100, sf::Color::Black);
    drawRectangle(window, 300, 20, 10, 160, sf::Color::Red);
    drawRectangle(window, 300, 20, 50, 10, sf::Color::Red);
    drawRectangle(window, 300, 170, 50, 10, sf::Color::Red);
    drawRectangle(window, 390, 70, 10, 60, sf::Color::Red);

    window.display();

    sf::sleep(sf::seconds(5));
}
#include <D:/CppDistro/MinGW/include/SFML/Graphics.hpp>
#include <D:/CppDistro/MinGW/include/SFML/System.hpp>
#include <D:/CppDistro/MinGW/include/SFML/Window.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Rectangle And Circle");

    window.clear();

    sf::ConvexShape triangle;
    triangle.setFillColor(sf::Color(0xFF, 0x80,0));
    triangle.setPosition({ 200, 120 });
    triangle.setPointCount(3);
    triangle.setPoint(0, { 50, -20 });
    triangle.setPoint(1, { 50, 20 });
    triangle.setPoint(2, { -100, 0 });
    window.draw(triangle);

    sf::ConvexShape trapeze;
    trapeze.setFillColor(sf::Color(0xFF, 0, 0xFF));
    trapeze.setPosition({ 400, 300 });
    trapeze.setPointCount(4);
    trapeze.setPoint(0, { -90, 0 });
    trapeze.setPoint(1, { 90, 0 });
    trapeze.setPoint(2, { 120, 60 });
    trapeze.setPoint(3, { -120, 60 });
    window.draw(trapeze);

    window.display();

    sf::sleep(sf::seconds(5));
}
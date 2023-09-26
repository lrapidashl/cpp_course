#include <D:/CppDistro/MinGW/include/SFML/Graphics.hpp>
#include <D:/CppDistro/MinGW/include/SFML/System.hpp>
#include <D:/CppDistro/MinGW/include/SFML/Window.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "title");

    window.clear();

    sf::CircleShape shape1(40);
    shape1.setPosition({ 200, 120 });
    shape1.setFillColor(sf::Color(0xFF, 0x0, 0x0));
    window.draw(shape1);

    window.display();

    sf::sleep(sf::seconds(5));
}
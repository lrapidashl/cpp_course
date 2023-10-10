#include <Graphics.hpp>
#include <iostream>

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
            case sf::Event::MouseButtonPressed:
                std::cout << "Mouse pressed,"
                          << " x = " << event.mouseButton.x
                          << " y = " << event.mouseButton.y
                          << std::endl;
                break;
            case sf::Event::MouseButtonReleased:
                std::cout << "Mouse released,"
                          << " x = " << event.mouseButton.x
                          << " y = " << event.mouseButton.y
                          << std::endl;
                break;
            default:
                break;
        }
    }
}

void redrawFrame(sf::RenderWindow& window)
{
    window.clear();
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

    while (window.isOpen())
    {
        pollEvents(window);
        redrawFrame(window);
    }
}
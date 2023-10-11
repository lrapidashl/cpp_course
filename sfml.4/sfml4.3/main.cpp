#include <Graphics.hpp>

sf::Sprite initImage(const std::string& imgName)
{
    static sf::Texture texture;
    if (!texture.loadFromFile(imgName))
    {
        exit(-1);
    }
    texture.setSmooth(true);
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition({400, 300});
    return sprite;
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

void update(sf::Sprite& pointer)
{
}

void redrawFrame(sf::RenderWindow& window, sf::Sprite& sprite)
{
    window.clear(sf::Color::White);
    window.draw(sprite);
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

    sf::Sprite sprite = initImage("Baton.png");
    while (window.isOpen())
    {
        pollEvents(window);
        update(sprite);
        redrawFrame(window, sprite);
    }
}
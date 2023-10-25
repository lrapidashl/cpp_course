#include <Graphics.hpp>
#include <vector>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;

struct Ball
{
    sf::Vector2f position = { 0, 0 };
    sf::Vector2f speed = { 100, 100 };
    sf::Color color = sf::Color::Red;
    float radius = 20;
    sf::CircleShape shape = *new sf::CircleShape;
};

void updateBall(Ball& ball)
{
    ball.shape.setRadius(ball.radius);
    ball.shape.setOrigin(ball.radius / 2, ball.radius / 2);
    ball.shape.setPosition(ball.position);
    ball.shape.setFillColor(ball.color);
}

void init(std::vector<Ball>& balls)
{
    balls = {
            {{ 100, 100 }, {100, 100}, sf::Color::Red},
            {{ 200, 150 }, {-100, 200}, sf::Color::Yellow},
            {{ 400, 100 }, {200, -100}, sf::Color::Green},
            {{ 150, 300 }, {-200, -200}, sf::Color::Blue},
            {{ 300, 400 }, {500, 400}, sf::Color::White}
    };

    for (Ball& ball : balls)
    {
        updateBall(ball);
    }
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

void ballBorderCollision(Ball& ball)
{
    if (ball.position.x <= ball.radius)
    {
        ball.position.x = ball.radius;
        ball.speed.x *= -1;
    }
    if (ball.position.x >= WINDOW_WIDTH - ball.radius)
    {
        ball.position.x = WINDOW_WIDTH - ball.radius;
        ball.speed.x *= -1;
    }
    if (ball.position.y <= ball.radius)
    {
        ball.position.y = ball.radius;
        ball.speed.y *= -1;
    }
    if (ball.position.y >= WINDOW_HEIGHT - ball.radius)
    {
        ball.position.y = WINDOW_HEIGHT - ball.radius;
        ball.speed.y *= -1;
    }
}

void update(sf::Clock& clock, std::vector<Ball>& balls)
{
    const float dt = clock.restart().asSeconds();
    for (Ball& ball : balls)
    {
        ball.position += ball.speed * dt;
        ballBorderCollision(ball);
        updateBall(ball);
    }
}

void redrawFrame(sf::RenderWindow& window, std::vector<Ball>& balls)
{
    window.clear();
    for (const Ball& ball : balls)
    {
        window.draw(ball.shape);
    }
    window.display();
}

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
            sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }),
            "Prints mouse events to terminal",
            sf::Style::Default,
            settings);

    sf::Clock clock;
    std::vector<Ball> balls;
    init(balls);
    while (window.isOpen())
    {
        pollEvents(window);
        update(clock, balls);
        redrawFrame(window, balls);
    }
}
#include <Graphics.hpp>
#include <vector>
#include <cmath>
#include <random>
#include <cassert>

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

struct PRNG
{
    std::mt19937 engine;
};

void initGenerator(PRNG& generator)
{
    std::random_device device;
    generator.engine.seed(device());
}

template<typename type>
type random(PRNG& generator, type minValue, type maxValue)
{
    assert(minValue <= maxValue);

    std::uniform_real_distribution<float> distribution(minValue, maxValue);

    return (type)distribution(generator.engine);
}

template<typename type>
type randomTwo(PRNG& generator, type firstValue, type secondValue)
{
    std::uniform_real_distribution<float> distribution(0, 1);

    return distribution(generator.engine) > 0.5 ? firstValue : secondValue;
}

float getVectorLength(sf::Vector2f vector)
{
    return std::sqrt((float)(std::pow(vector.x, 2) + std::pow(vector.y, 2)));
}

sf::Vector2f getNormalVector(sf::Vector2f vector)
{
    return vector / getVectorLength(vector);
}

float scalar(sf::Vector2f vector1, sf::Vector2f vector2)
{
    return vector1.x * vector2.x + vector1.y * vector2.y;
}

void updateBall(Ball& ball)
{
    ball.shape.setRadius(ball.radius);
    ball.shape.setOrigin(ball.radius / 2, ball.radius / 2);
    ball.shape.setPosition(ball.position);
    ball.shape.setFillColor(ball.color);
}

void updateBalls(std::vector<Ball>& balls)
{
    for (Ball& ball : balls)
    {
        updateBall(ball);
    }
}

void init(std::vector<Ball>& balls)
{
    PRNG generator;
    initGenerator(generator);

    balls = {
            {{ 100, 100 }, { 0, 0 }, sf::Color::Red},
            {{ 200, 150 }, { 0, 0 }, sf::Color::Yellow},
            {{ 400, 100 }, { 0, 0 }, sf::Color::Green},
            {{ 150, 300 }, { 0, 0 }, sf::Color::Blue},
            {{ 300, 400 }, { 0, 0 }, sf::Color::White}
    };

    for (Ball& ball : balls)
    {
        ball.speed = {(float)random<int>(generator, 50, 500) * randomTwo<float>(generator, -1, 1),
                      (float)random<int>(generator, 50, 500) *  randomTwo<float>(generator, -1, 1)};
    }

    updateBalls(balls);
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

void ballsCollision(std::vector<Ball>& balls)
{
    for (size_t i = 0; i < balls.size(); i++)
    {
        for (size_t j = i + 1; j < balls.size(); j++)
        {
            const sf::Vector2f deltaPosition = balls[j].position - balls[i].position;
            if (getVectorLength(deltaPosition) <= balls[i].radius + balls[i].radius)
            {
                balls[i].position -= getNormalVector(deltaPosition)
                                     * (std::abs(getVectorLength(deltaPosition) - (balls[i].radius + balls[i].radius)) / 2);
                balls[j].position += getNormalVector(deltaPosition)
                                     * (std::abs(getVectorLength(deltaPosition) - (balls[i].radius + balls[i].radius)) / 2);
                sf::Vector2f iSpeed = scalar(balls[i].speed - balls[j].speed, balls[i].position - balls[j].position)
                                      / (float)std::pow(getVectorLength(balls[i].position - balls[j].position), 2)
                                      * (balls[i].position - balls[j].position);
                sf::Vector2f jSpeed = scalar(balls[j].speed - balls[i].speed, balls[j].position - balls[i].position)
                                      / (float)std::pow(getVectorLength(balls[j].position - balls[i].position), 2)
                                      * (balls[j].position - balls[i].position);
                balls[i].speed -= iSpeed;
                balls[j].speed -= jSpeed;
            }
        }
    }
}

void update(sf::Clock& clock, std::vector<Ball>& balls)
{
    const float dt = clock.restart().asSeconds();
    for (Ball& ball : balls)
    {
        ball.position += ball.speed * dt;
        ballBorderCollision(ball);
    }
    ballsCollision(balls);
    updateBalls(balls);
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
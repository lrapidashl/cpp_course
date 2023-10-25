#include <Graphics.hpp>
#include <vector>
#include <cmath>
#include <random>
#include <cassert>
#include <iostream>

constexpr unsigned WINDOW_WIDTH = 1600;
constexpr unsigned WINDOW_HEIGHT = 900;

struct Ball
{
    sf::Vector2f position = { 0, 0 };
    sf::Vector2f speed = { 100, 100 };
    sf::Color color = sf::Color::Red;
    float radius = 20;
    sf::CircleShape shape = *new sf::CircleShape;
    float lifetime = 0;
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

bool areCloseAbsolute(float a, float b, float tolerance = 0.001f)
{
    return std::abs(a - b) < tolerance;
}

bool areCloseRelative(float a, float b, float tolerance = 0.001f)
{
    return std::abs((a - b) / b) < tolerance;
}

bool areFuzzyEqual(float a, float b, float tolerance = 0.001f)
{
    if (std::abs(b) > 1.f)
    {
        return areCloseRelative(a, b, tolerance);
    }
    return areCloseAbsolute(a, b, tolerance);
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
    ball.shape.setOrigin(ball.radius, ball.radius);
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

void createBall(sf::Vector2f position, std::vector<Ball>& balls)
{
    PRNG generator;
    initGenerator(generator);

    Ball ball{ position };
    ball.speed = {(float)random<int>(generator, 50, 500) * randomTwo<float>(generator, -1, 1),
                  (float)random<int>(generator, 50, 500) *  randomTwo<float>(generator, -1, 1)};
    ball.color = sf::Color(random<int16_t>(generator, 0x00, 0xFF),
                           random<int16_t>(generator, 0x00, 0xFF),
                           random<int16_t>(generator, 0x00, 0xFF));
    ball.radius = random<float>(generator, 20, 200);

    balls.push_back(ball);

    updateBall(ball);
}

void onMouseRelease(const sf::Event::MouseButtonEvent& event, std::vector<Ball>& balls)
{
    createBall({ float(event.x), float(event.y) }, balls);
}

void pollEvents(sf::RenderWindow& window, std::vector<Ball>& balls)
{
    sf::Event event{};
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonReleased:
                onMouseRelease(event.mouseButton, balls);
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
            if (getVectorLength(deltaPosition) <= balls[i].radius + balls[j].radius)
            {
                sf::Vector2f iStartSpeed = balls[i].speed;
                sf::Vector2f jStartSpeed = balls[j].speed;
                auto iMass = 1;
                auto jMass = 1;
                sf::Vector2f dPosition = getNormalVector(deltaPosition)
                                     * (std::abs(getVectorLength(deltaPosition) - (balls[j].radius + balls[i].radius)) / 2);
                float iSpeedProjection = scalar(iStartSpeed - jStartSpeed, balls[i].position - balls[j].position)
                        / (float)(getVectorLength(balls[i].position - balls[j].position));
                float jSpeedProjection = scalar(jStartSpeed - iStartSpeed, balls[j].position - balls[i].position)
                        / (float)(getVectorLength(balls[j].position - balls[i].position));
                balls[i].position -= dPosition;
                balls[j].position += dPosition;
                balls[i].speed -= iSpeedProjection
                        * getNormalVector(balls[i].position - balls[j].position);
                balls[j].speed -= jSpeedProjection
                        * getNormalVector(balls[j].position - balls[i].position);

                bool isLawOfConservationOfEnergyObserved = areFuzzyEqual(
                        (float)(iMass * pow(getVectorLength(iStartSpeed), 2) + jMass * pow(getVectorLength(jStartSpeed), 2)),
                        (float)(iMass * pow(getVectorLength(balls[i].speed), 2) + jMass * pow(getVectorLength(balls[j].speed),2)));
                bool isLawOfConservationOfMomentumObserved = areFuzzyEqual(
                        iStartSpeed.x + iStartSpeed.y + jStartSpeed.x + jStartSpeed.y,
                        balls[i].speed.x + balls[i].speed.y + balls[j].speed.x + balls[j].speed.y);
                assert(isLawOfConservationOfEnergyObserved);
                assert(isLawOfConservationOfMomentumObserved);
            }
        }
    }
}

void removeDeathBalls(std::vector<Ball>& balls)
{
    auto removeBalls = [&](const Ball& ball) -> bool
    {
        return ball.lifetime > 10;
    };
    auto iterator = std::remove_if(balls.begin(), balls.end(), removeBalls);
    balls.erase(iterator, balls.end());
}

void updateBallsLifetime(float time, std::vector<Ball>& balls)
{
    for (Ball& ball : balls)
    {
        ball.lifetime += time;
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
    updateBallsLifetime(dt, balls);
    removeDeathBalls(balls);
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
            sf::Style::Fullscreen,
            settings);

    sf::Clock clock;
    std::vector<Ball> balls;
    while (window.isOpen())
    {
        pollEvents(window, balls);
        update(clock, balls);
        redrawFrame(window, balls);
    }
}
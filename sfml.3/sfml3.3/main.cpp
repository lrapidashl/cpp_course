#include <Graphics.hpp>
#include <cmath>

struct Eye
{
    sf::ConvexShape white;
    sf::ConvexShape pupil;
    sf::Vector2f position;
    float pupilAngle = 0;
};

sf::Vector2f toCartesian(float angle, float radiusX, float radiusY = 0)
{
    radiusY = (radiusY == 0) ? radiusX : radiusY;
    return {
        radiusX * std::cos(angle),
        radiusY * std::sin(angle),
    };
}

float toDegrees(double radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

float toRadians(float angle)
{
    return angle * (float)M_PI / 180;
}

void updateEyeElements(Eye& eye, sf::Vector2f mousePosition = { 0, 0 })
{
    const sf::Vector2f pupilTrackRadius = { 20, 20 };
    eye.white.setPosition(eye.position);

    if (std::pow(mousePosition.x - eye.position.x, 2) * std::pow(pupilTrackRadius.y, 2) +
        std::pow(mousePosition.y - eye.position.y, 2) * std::pow(pupilTrackRadius.x, 2) <=
        std::pow(pupilTrackRadius.y, 2) * std::pow(pupilTrackRadius.x, 2))
    {
        eye.pupil.setPosition(mousePosition);
    }
    else
    {
        const sf::Vector2f pupilOffset = toCartesian(eye.pupilAngle, pupilTrackRadius.x, pupilTrackRadius.y);
        eye.pupil.setPosition(eye.position + pupilOffset);
    }
}

void initEye(Eye& eye, sf::Vector2f position)
{
    const unsigned pointCount = 200;
    const float heightScale = 2;
    const sf::Vector2f whiteRadius = { 50, 50 * heightScale };
    const sf::Vector2f pupilRadius = { 15, 15 * heightScale };
    eye.position = position;

    eye.white.setPointCount(pointCount);
    eye.pupil.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; pointNo++)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f whitePoint = toCartesian(angle, whiteRadius.x, whiteRadius.y);
        sf::Vector2f pupilPoint = toCartesian(angle, pupilRadius.x, pupilRadius.y);
        eye.white.setPoint(pointNo, whitePoint);
        eye.pupil.setPoint(pointNo, pupilPoint);
    }

    eye.white.setFillColor(sf::Color::White);

    eye.pupil.setFillColor(sf::Color::Black);

    updateEyeElements(eye);
}

void onMouseMove(const sf::Event::MouseMoveEvent& event, sf::Vector2f& mousePosition)
{
    mousePosition = { float(event.x), float(event.y) };
}

void pollEvents(sf::RenderWindow& window, sf::Vector2f& mousePosition)
{
    sf::Event event{};
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseMoved:
                onMouseMove(event.mouseMove, mousePosition);
                break;
            default:
                break;
        }
    }
}

void update(const sf::Vector2f& mousePosition, Eye& eye)
{
    const sf::Vector2f delta = mousePosition - eye.position;
    const double angle = atan2(double(delta.y), double(delta.x));
    eye.pupilAngle = (float)angle;

    updateEyeElements(eye, mousePosition);
}

void redrawFrame(sf::RenderWindow& window, Eye& RightEye, Eye& LeftEye)
{
    window.clear();
    window.draw(RightEye.white);
    window.draw(RightEye.pupil);
    window.draw(LeftEye.white);
    window.draw(LeftEye.pupil);
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

    Eye RightEye;
    Eye LeftEye;
    sf::Vector2f mousePosition;

    initEye(RightEye, { 340, 300});
    initEye(LeftEye, { 460, 300});
    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        update(mousePosition, RightEye);
        update(mousePosition, LeftEye);
        redrawFrame(window, RightEye, LeftEye);
    }
}
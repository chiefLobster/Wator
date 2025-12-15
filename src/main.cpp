#include <iostream>
#include <SFML/Graphics.hpp>
#include "WatorGame.hpp"
#include "WatorGraphics.hpp"

static constexpr size_t SIZE_X = 10, SIZE_Y = 10;
static constexpr float TileWidth = 35.f;

static constexpr unsigned long long WINDOW_WIDTH = SIZE_X * TileWidth,
    WINDOW_HEIGHT = SIZE_Y * TileWidth;

using GridType = Grid<SIZE_X, SIZE_Y>;
using GraphicsType = Graphics<SIZE_X, SIZE_Y>;

template<size_t SAMPLE_SIZE>
class FpsCounter
{
    size_t frameNumber;
    sf::Clock clock;

public:
    void operator()();

    constexpr FpsCounter() : frameNumber(0), clock() { clock.restart(); }
    ~FpsCounter() { std::cout << "\n"; }
};

static void processKeyPress(sf::RenderWindow& window, GraphicsType& graphics,
    GridType& grid, const sf::Event::KeyPressed* keyPressed)
{
    using sf::Keyboard::Scan;
    switch (keyPressed->scancode)
    {
    case Scan::Escape:
        window.close();
        break;

    case Scan::P:
    case Scan::Space:
        // TODO: pause
        break;
    case Scan::R:
        // TODO: reset
        break;

        // TODO: add speed controls

    default:
        break;
    }
}

static void processEvents(sf::RenderWindow& window, GraphicsType& graphics, GridType& grid)
{
    while (const std::optional event = window.pollEvent())
    {
        // TODO: are any other events important?
        if (event->is<sf::Event::Closed>())
            window.close();
        else if (event->is<sf::Event::FocusGained>())
            ; // TODO
        else if (event->is<sf::Event::FocusLost>())
            ; // TODO
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            processKeyPress(window, graphics, grid, keyPressed);
    }
}

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Wator");
    window.setFramerateLimit(144);
    window.setPosition({100, 100});

    GraphicsType graphics(TileWidth);
    GridType grid;
    sf::Clock clock;
    sf::Time stepTime; // TODO: init and update when speed is changed
    FpsCounter<256> fpsCount;

    sf::Time elapsed = sf::Time::Zero;
    while (window.isOpen())
    {
        processEvents(window, graphics, grid);

        if (clock.isRunning()) {
            elapsed += clock.restart();
            if (elapsed > stepTime) {
                // TODO: step the simulation
            }
        }

        window.clear();
        graphics.set(grid);
        graphics.draw(window);
        window.display();

        fpsCount();
    }
}

template <size_t SAMPLE_SIZE>
void FpsCounter<SAMPLE_SIZE>::operator()()
{
    if (++frameNumber < SAMPLE_SIZE) return;

    frameNumber = 0;
    const float t = clock.restart().asSeconds() / SAMPLE_SIZE;
    std::cout << "\rrender time: "
        << t
        << " sec, fps: "
        << 1 / t
        << "    ";
    std::cout.flush();
}

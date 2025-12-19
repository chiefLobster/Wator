#ifndef WATOR_GRAPHICS_HPP
#define WATOR_GRAPHICS_HPP

#include <array>
#include <SFML/Graphics.hpp>
#include "WatorGame.hpp"

// undefine this to remove the lines
#undef WATOR_GRAPHICS_ENABLE_LINES

template<PosInt SIZE_X, PosInt SIZE_Y>
class Graphics
{
#ifdef WATOR_GRAPHICS_ENABLE_LINES
    // config for the lines
    // vertical lines
    static constexpr size_t NUM_VERT_LINES = SIZE_X - 1;
    // horizontal lines
    static constexpr size_t NUM_HORI_LINES = SIZE_Y - 1;
    static constexpr sf::Color lineColor = sf::Color(52, 52, 52);

    // 2 vertices for each line
    std::array<sf::Vertex, 2 * (NUM_VERT_LINES + NUM_HORI_LINES)> lines;
#endif
    // 2 triangles needed for each rectangle (6 vertices total)
    std::array<sf::Vertex, 6 * SIZE_X * SIZE_Y> triangles;

public:
    using GridType = Grid<SIZE_X, SIZE_Y>;

    // set the whole grid
    void set(const GridType&);

    void set(size_t i, sf::Color color);

    // draw the current state
    void draw(sf::RenderWindow&, const sf::RenderStates& = sf::RenderStates::Default) const;

    // prepare the positions in the vertex buffer
    constexpr Graphics(float TileLength);
};


template<PosInt SIZE_X, PosInt SIZE_Y>
constexpr Graphics<SIZE_X, SIZE_Y>::Graphics(float TileLength)
    : triangles()
#ifdef WATOR_GRAPHICS_ENABLE_LINES
    ,lines()
#endif
{
    // position for the triangles
    size_t i = 0;
    float y_low = 0.f;
    for (size_t y = 0; y < SIZE_Y; ++y, y_low += TileLength) {
        float x_low = 0.f;
        for (size_t x = 0; x < SIZE_X; ++x, x_low += TileLength) {
            const float y_high = y_low + TileLength, x_high = x_low + TileLength;

            triangles[i+0].position = {x_low, y_low};
            triangles[i+1].position = {x_high, y_low};
            triangles[i+2].position = {x_low, y_high};
            triangles[i+3].position = {x_high, y_low};
            triangles[i+4].position = {x_low, y_high};
            triangles[i+5].position = {x_high, y_high};
            i += 6;
        }
    }

#ifdef WATOR_GRAPHICS_ENABLE_LINES
    // color and position for the lines
    const float totalHeight = TileLength * SIZE_Y;
    const float totalWidth = TileLength * SIZE_X;

    i = 0;
    // vertical lines
    float pos = TileLength;
    while (i < NUM_VERT_LINES * 2)
    {
        lines[i].color = lineColor;
        lines[i+1].color = lineColor;
        lines[i].position = {pos, 0.f};
        lines[i+1].position = {pos, totalHeight};
        i += 2;
        pos += TileLength;
    }
    // horizontal lines
    pos = TileLength;
    while (i < lines.size())
    {
        lines[i].color = lineColor;
        lines[i+1].color = lineColor;
        lines[i].position = {0.f, pos};
        lines[i+1].position = {totalWidth, pos};
        i += 2;
        pos += TileLength;
    }
#endif
}

template<PosInt SIZE_X, PosInt SIZE_Y>
void Graphics<SIZE_X, SIZE_Y>::set(const GridType& grid)
{
    for (size_t i = 0; i < SIZE_X * SIZE_Y; ++i)
    {
        switch (grid[i].getMode())
        {
            case Tile::Mode::Empty:
                set(i * 6, sf::Color::Black);
                break;
            case Tile::Mode::Fish:
                set(i * 6, sf::Color::Green);
                break;
            case Tile::Mode::Shark:
                set(i * 6, sf::Color::Blue);
                break;
        }
    }
}

template <PosInt SIZE_X, PosInt SIZE_Y>
void Graphics<SIZE_X, SIZE_Y>::set(size_t i, sf::Color color)
{
    triangles[i+0].color = color;
    triangles[i+1].color = color;
    triangles[i+2].color = color;
    triangles[i+3].color = color;
    triangles[i+4].color = color;
    triangles[i+5].color = color;
}

template<PosInt SIZE_X, PosInt SIZE_Y>
void Graphics<SIZE_X, SIZE_Y>::draw(sf::RenderWindow& window, const sf::RenderStates& rStates) const
{
    window.draw(triangles.data(), triangles.size(), sf::PrimitiveType::Triangles, rStates);
#ifdef WATOR_GRAPHICS_ENABLE_LINES
    window.draw(lines.data(), lines.size(), sf::PrimitiveType::Lines, rStates);
#endif
}

#endif

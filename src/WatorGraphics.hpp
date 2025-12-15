#ifndef WATOR_GRAPHICS_HPP
#define WATOR_GRAPHICS_HPP

#include <array>
#include <SFML/Graphics.hpp>
#include "WatorGame.hpp"

template<PosInt SIZE_X, PosInt SIZE_Y>
class Graphics
{
    // config for the lines
    // vertical lines
    static constexpr size_t NUM_VERT_LINES = SIZE_X + 1;
    // horizontal lines
    static constexpr size_t NUM_HORI_LINES = SIZE_Y + 1;
    static constexpr sf::Color lineColor = sf::Color(52, 52, 52);

    // 2 vertices for each line
    std::array<sf::Vertex, 2 * NUM_X_LINES + NUM_Y_LINES> lines;
    // 2 triangles needed for each rectangle (6 vertices total)
    std::array<sf::Vertex, 6 * SIZE_X * SIZE_Y> triangles;

public:
    using GridType = Grid<SIZE_X, SIZE_Y>;

    // set the whole grid
    void set(const GridType&);

    // draw the current state
    void draw(sf::RenderWindow&, const sf::RenderStates& = sf::RenderStates::Default) const;

    // prepare the positions in the vertex buffer
    constexpr Graphics(float TileLength);
};


template<PosInt SIZE_X, PosInt SIZE_Y>
constexpr Graphics<SIZE_X, SIZE_Y>::Graphics(float TileLength) : triangles(), lines()
{
    // position for the triangles

    for (size_t y = 0; y < SIZE_Y; ++y) {
        for (size_t x = 0; x < SIZE_X; ++x) {
            const float x_low = TileLength * x,
                y_low = TileLength * y;
                x_high = x_low + TileLength,
                y_high = y_low + TileLength;

            triangles[i+0].position = {x_low, y_low};
            triangles[i+1].position = {x_high, y_low};
            triangles[i+2].position = {x_low, y_high};
            triangles[i+3].position = {x_high, y_low};
            triangles[i+4].position = {x_low, y_high};
            triangles[i+5].position = {x_high, y_high};
        }
    }

    // color and position for the lines

    const float totalHeight = TileLength * SIZE_Y;
    const float totalWidth = TileLength * SIZE_X;

    // vertical lines
    for (size_t i = 0; i < NUM_VERT_LINES; ++i) {
        lines[i*2].color = lineColor;
        lines[i*2+1].color = lineColor;

        const float x_pos = TileLength * i;
        lines[i*2].position = {x_pos, 0.f}
        lines[i*2+1].positon = {x_pos, totalHeight};
    }

    // horizontal lines
    for (size_t i = NUM_VERT_LINES; i < NUM_VERT_LINES + NUM_HORI_LINES; ++i) {
        lines[i*2].color = lineColor;
        lines[i*2+1].color = lineColor;

        const float y_pos = TileLength * i;
        lines[i*2].position = {0.f, y_pos}
        lines[i*2+1].positon = {totalWidth, y_pos};
    }
}

template<PosInt SIZE_X, PosInt SIZE_Y>
void Graphics<SIZE_X, SIZE_Y>::set(const GridType& grid)
{
    // TODO: iterate through all positions on the grid and extract the required color
    // then set the color on the vertex buffer
}

template<PosInt SIZE_X, PosInt SIZE_Y>
void Graphics<SIZE_X, SIZE_Y>::draw(sf::RenderWindow& window, const sf::RenderStates& rStates) const
{
    window.draw(triangles.data(), triangles.size(), sf::PrimitiveType::Triangles, rStates);
    window.draw(lines.data(), lines.size(), sf::PrimitiveType::Lines, rStates);
}

#endif

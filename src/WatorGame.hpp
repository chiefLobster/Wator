#ifndef WATOR_GAME_HPP
#define WATOR_GAME_HPP

#include <stdint.h>
#include <iostream>
#include <array>

class Tile
{
    Tile()=default;

public:
    enum Mode {
        Empty,
        Fish,
        Shark
    };
    
    [[nodiscard]] Mode getMode() const;

    // named constructors
    // TODO: add arguments to each of these (maybe except makeEmpty)

    [[nodiscard]] static constexpr Tile makeEmpty();
    [[nodiscard]] static constexpr Tile makeFish();
    [[nodiscard]] static constexpr Tile makeShark();

    // TODO: more methods and the data member(s)
};

// integer type to use for all positions
using PosInt = uint8_t;

template<PosInt SIZE_X, PosInt SIZE_Y>
class Grid
{
    // a grid of size zero might have some trouble
    // and it is probably not wanted anyways
    static_assert(SIZE_X && SIZE_Y, "Grid of size zero detected.");
    // every position must have a unique id in the range of `PosInt`
    static_assert(static_cast<size_t>(SIZE_X) * SIZE_Y <= std::numeric_limits<PosInt>::max(),
        "The type `PosInt` is not wide enough to support all possible positions.");

    std::array<Tile, SIZE_X * SIZE_Y> data;

public:
    Grid()=default;

    // aliases, visible from outside
    static constexpr PosInt LENGTH_X = SIZE_X;
    static constexpr PosInt LENGTH_Y = SIZE_Y;

    // TODO: add methods for accessing the elements
    // e.g. a method with just an id and a method with x and y
};

#endif // include gate

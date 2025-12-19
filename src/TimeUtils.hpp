#ifndef WATOR_TIME_UTILS_HPP
#define WATOR_TIME_UTILS_HPP

#include <iostream>
#include <chrono>

using FrameCountType = unsigned;
using ClockType = std::chrono::steady_clock;

template<FrameCountType SAMPLE_SIZE>
class FpsCounter
{
    FrameCountType frameNumber;
    ClockType::time_point start;

public:
    void operator()();

    FpsCounter() : frameNumber(0), start(ClockType::now()) {}
    ~FpsCounter() { std::cout << "\n"; }
};

template <unsigned SAMPLE_SIZE>
void FpsCounter<SAMPLE_SIZE>::operator()()
{
    if (++frameNumber < SAMPLE_SIZE) return;

    // reset the counter
    frameNumber = 0;
    // measure the time
    const ClockType::time_point end = ClockType::now();
    const ClockType::duration delta = end - start;
    // reset the start
    start = end;

    // overflow is almost impossible (i think)
    // TODO: check this crazy claim above
    // average time used for rendering
    const auto rTime = std::chrono::duration_cast<std::chrono::microseconds>(delta);
    // estimated frames per second
    using period = ClockType::period;
    const auto fps = (period::den * SAMPLE_SIZE) / (delta.count() * period::num);

    std::cout << "\rrender time: "
        << rTime.count() / SAMPLE_SIZE
        << "us, fps: "
        << fps
        << "    ";
    std::cout.flush();
}

#endif // include gate

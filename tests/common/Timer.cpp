#include <iomanip>
#include "common/Timer.hpp"

void Timer::start()
{
    start_time = clock();
}

void Timer::stop()
{
    stop_time = clock();
}

double Timer::elapsed() const
{
    double time = (double)(stop_time - start_time) / CLOCKS_PER_SEC * 1000;
    return time;
}

std::ostream &operator<<(std::ostream &os, const Timer &timer)
{
    os << std::fixed << std::setprecision(3) << timer.elapsed() << " ms";
    return os;
}

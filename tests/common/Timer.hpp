#ifndef TIMER_HPP
#define TIMER_HPP

#include <time.h>
#include <iostream>

class Timer
{
public:
    void start();
    void stop();
    double elapsed() const;
private:
    clock_t start_time;
    clock_t stop_time;
};

std::ostream &operator<<(std::ostream &os, const Timer &timer);

#endif /* TIMER_HPP */
#include <iostream>
#include <iomanip>

class Counter {
private:
    int count;
public:
    Counter() : count(0) {}
    void increment() { count++; }
    int getCount() const { return count; }
    void reset() { count = 0; }
};

class Clock {
private:
    int hours;
    int minutes;
    int seconds;
    Counter* counter; // Clock needs to know about Counter
public:
    Clock(Counter* counter) : hours(0), minutes(0), seconds(0), counter(counter) {}

    void tick() {
        seconds++;
        if (seconds >= 60) {
            seconds = 0;
            minutes++;
            if (minutes >= 60) {
                minutes = 0;
                hours++;
                if (hours >= 24) {
                    hours = 0;
                }
            }
        }
        counter->increment(); // Increment the counter each time the clock ticks
    }

    std::string getTime() const {
        std::ostringstream oss;
        oss << std::setw(2) << std::setfill('0') << hours << ":"
            << std::setw(2) << std::setfill('0') << minutes << ":"
            << std::setw(2) << std::setfill('0') << seconds;
        return oss.str();
    }

    void reset() {
        hours = 0;
        minutes = 0;
        seconds = 0;
    }
};

int main() {
    Counter counter;
    Clock clock(&counter);

    // Tick the clock 10 times
    for (int i = 0; i < 10; ++i) {
        clock.tick();
        std::cout << "Current time: " << clock.getTime() << std::endl;
    }

    std::cout << "Total ticks: " << counter.getCount() << std::endl;

    return 0;
}

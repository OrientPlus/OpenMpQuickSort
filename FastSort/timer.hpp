#include <chrono>
#include <iostream>


template<typename DurationType>
class Timer
{
public:
	Timer() :running(false) {};

    void start() 
    {
        startTime = std::chrono::steady_clock::now();
        running = true;
    }

    void stop() 
    {
        endTime = std::chrono::steady_clock::now();
        running = false;
    }

    friend std::ostream& operator<<(std::ostream& os, const Timer<DurationType>& timer) 
    {
        if (timer.running)
            throw std::runtime_error("Timer is still running!");
        else 
        {
            auto duration = std::chrono::duration_cast<DurationType>(timer.endTime - timer.startTime);
            os << duration.count();
        }
        return os;
    }

private:
	bool running;
    std::chrono::time_point<std::chrono::steady_clock> startTime, endTime;
};
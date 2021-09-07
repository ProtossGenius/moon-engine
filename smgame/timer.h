#pragma once
#include <ctime>
#include <functional>
#include <map>
#include <mutex>

namespace smgame {
enum {
    Second = 1000,
    Minute = 60 * Second,
    Hour   = 60 * Minute,
    Day    = 24 * Hour,
    Week   = 7 * Day,
};

// it can accept the task what will run some-time later.
class timer {
  public:
    timer()
        : m_now(clock()) {}
    ~timer() {}
    timer(const timer &) = delete;
    timer(timer &&)      = delete;

  public:
    clock_t Now() { return m_now; }
    void    update(); // upate time now.
    void    addTask(clock_t t, std::function<void()> task) {
        std::lock_guard<std::mutex> _(lock);
        m_cache.insert({t, task});
    }

  private:
    clock_t                                       m_now;
    std::multimap<clock_t, std::function<void()>> m_tasks, m_cache;
    std::mutex                                    lock;
};

inline timer &GlobalTimer() {
    static timer t;
    return t;
}
} // namespace smgame
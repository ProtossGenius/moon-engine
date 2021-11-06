#pragma once
#include <ctime>
#include <functional>
#include <queue>
#include <mutex>
#include <thread>
#include <vector>

namespace smgame {
enum {
    Second = 1000,
    Minute = 60 * Second,
    Hour   = 60 * Minute,
    Day    = 24 * Hour,
    Week   = 7 * Day,
};

typedef std::pair<clock_t, std::function<void()>> task_pair;

struct next_task {
bool operator() (const task_pair& lhs,
		const task_pair& rhs) const {
	return lhs.first < rhs.first;
}
};

// it can accept the task what will run some-time later.
class timer {
  public:
    timer()
        :m_trd([this](){this->update();}){
			m_trd.detach();
		}
    ~timer() {}
    timer(const timer &) = delete;
    timer(timer &&)      = delete;

  public:
    void    addTask(clock_t t, std::function<void()> task) {
        std::lock_guard<std::mutex> _(lock);
        m_tasks.push({t, task});
    }

  private:
    void    update(); 
  private:
    std::priority_queue<		task_pair, std::vector<task_pair>,		next_task	   	> m_tasks;
    std::mutex                                    lock;
	std::thread m_trd;
};

inline timer &GlobalTimer() {
    static timer t;
    return t;
}
} // namespace smgame

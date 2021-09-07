#include "timer.h"

namespace smgame {
void timer::update() {
    m_now = clock();
    {
        std::lock_guard<std::mutex> _(lock);
        for (auto iter = m_cache.begin(); iter != m_cache.end();) {
            m_tasks.insert({iter->first, iter->second});
            m_cache.erase(iter);
        }
    }

    for (auto iter = m_tasks.begin(); iter != m_tasks.end();) {
        if (iter->first > m_now) break;
        iter->second();
        m_tasks.erase(iter++);
    }
}
} // namespace smgame

#include "timer.h"

namespace smgame {
void timer::update() {
	while (true) {
		std::lock_guard<std::mutex> _ (lock);
    	auto m_now = clock();
		if (m_tasks.empty()){break;}
		task_pair p = m_tasks.top();
		if (p.first < m_now){
			m_tasks.pop();
			p.second();

		}
	}
}

} // namespace smgame

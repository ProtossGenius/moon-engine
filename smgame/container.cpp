#include "container.h"

namespace smgame {
	void Container::add(const UnitList& list)
	{
		m_size += list.size();
		for (auto it : list) {
			add(it->type(), it);
		}
	}

	UnitList Container::del(UnitType type, size_t count)
	{
		auto& lst = m_store[type];
		count = count > lst.size() ? lst.size() : count;
		UnitList out;
		m_size -= count;
		while (count--) {
			out.push_back(lst.back());
			lst.pop_back();
		}
		return out;
	}
	void Container::forEach(std::function<void(const Unit&)> func)
	{
		for (auto& uList : m_store) {
			for (auto unit : uList.second) {
				func(*unit);
			}
		}
	}
	void Container::forEach(UnitType type, std::function<void(const Unit&)> func)
	{
		auto& uList = m_store[type];
		for (auto unit : uList) {
			func(*unit);
		}
	}
}
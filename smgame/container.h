#pragma once
#include <map>
#include <memory>
#include <list>
#include "unit.h"
#include <functional>
namespace smgame {
	using UnitList = std::list<std::shared_ptr<Unit>>;
	using UnitStore = std::map<UnitType, UnitList>;
	// Container like bags .
	class Container {
	public:
		Container():m_size(0){}
	private:
		UnitStore m_store;
		size_t m_size;
	public:
		const UnitList& asList(UnitType type) { return m_store[type]; }
		size_t count(UnitType type) { return m_store[type].size(); }
		size_t count() { return m_size; }
		void add(const UnitList& list);
		UnitList del(UnitType type, size_t count);
		void forEach(std::function<void(const Unit&)> func);
		void forEach(UnitType type, std::function<void(const Unit&)> func);
	private:
		void add(UnitType type, std::shared_ptr<Unit> list) { m_store[type].push_back(list); }
	};
}
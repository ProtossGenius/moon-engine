#pragma once
#include "unit.h"
#include <string>
#include "Serializable.h"
namespace smgame {
	enum class EventType
	{
		EventTypeUnit = 0,
		EventTypeArea = 1,
	};

	class Event :public Serializable{
	public:
		virtual void Act(Unit& unit) = 0;
		virtual EventType getType() const = 0;
		virtual Event& parseMsg(const std::string&) override = 0;// return itself.
		virtual std::string asMessage() const override = 0;
	};

	namespace x2d {
		class AreaEvent :public Event {
		public:
			AreaEvent(const Rectangle& area): m_area(area){}
		public:
			EventType getType() const override { return EventType::EventTypeArea; }
			virtual AreaEvent& parseMsg(const std::string&) override = 0;// return itself.
			virtual std::string asMessage() const override = 0;
			virtual void Act(Unit& unit, const Rectangle& unitArea) = 0;
			void Act(Unit& unit) { Act(unit, Rectangle::Zero); }
		public:
			const Rectangle& area() const { return m_area; }
		private:
			Rectangle m_area;
		};
	}
	
}
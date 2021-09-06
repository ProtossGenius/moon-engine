#pragma once
#include <string>
#include <functional>
#include "errors.h"
#include "Serializable.h"
namespace smgame {

	struct FloatAttrib { typedef float Type; };
	struct DoubleAttrib{ typedef double Type; };
	struct Int32Attrib{ typedef int32_t Type; };
	struct Int64Attrib{ typedef int64_t Type; };
	struct StringAttrib{ typedef std::string Type; };
	/* 
	// class Attributes's Member-functions's template's struct as ...
	struct TestAttribType {
		typedef FloatAttrib Trait;
		enum{AttribID = 0};
		enum{TraitID = 0};
	};
	*/
	class AttributesItf;
	inline void doNothing(AttributesItf*){}
	class AttributesItf :public Serializable{
	private:
		int AttribType;
		std::function<void(AttributesItf*)> m_changeDo;
	private:
		virtual float       getAttrib(size_t attrib, FloatAttrib) const = 0;
		virtual double      getAttrib(size_t attrib, DoubleAttrib) const = 0;
		virtual int32_t     getAttrib(size_t attrib, Int32Attrib) const = 0;
		virtual int64_t     getAttrib(size_t attrib, Int64Attrib) const = 0;
		virtual std::string getAttrib(size_t attrib, StringAttrib) const = 0;
		virtual void setAttrib(size_t attrib, float       val) = 0;
		virtual void setAttrib(size_t attrib, double      val) = 0;
		virtual void setAttrib(size_t attrib, int32_t     val) = 0;
		virtual void setAttrib(size_t attrib, int64_t     val) = 0;
		virtual void setAttrib(size_t attrib, std::string val) = 0;
	public:
		AttributesItf(int attribType):AttribType(attribType), m_changeDo(doNothing){}
	public:

		virtual AttributesItf& parseMsg(const std::string&) override= 0;// return itself.
		virtual std::string asMessage() const override = 0;

		int getAttribType() { return AttribType; }
		void whenChange(std::function<void(AttributesItf*)> changeDo) {
			m_changeDo = changeDo;
		}
		template<typename Attrib>
		typename Attrib::Trait::Type getAttrib() const{
			if (Attrib::AttribType != AttribType) {
				throw SMGAME_ERROR("Attrib not suit. Except AttribType is: " + std::to_string(AttribType) +
					", Use AttribID is : " + std::to_string(Attrib::AttribType) + ", AttribID = " +
					std::to_string(Attrib::AttribID) + ", template Attrib's Name is " + typeid(Attrib).name());
			}
			return getAttrib(Attrib::AttribID, typename Attrib::Trait());
		}
		
		template<typename Attrib>
		void setAttrib(typename Attrib::Trait::Type val) {
			if (Attrib::AttribType != AttribType) {
				throw SMGAME_ERROR("Attrib not suit. Except AttribType is: " + std::to_string(AttribType) +
					", Use AttribID is : " + std::to_string(Attrib::AttribType) + ", AttribID = " +
					std::to_string(Attrib::AttribID) + ", template Attrib's Name is " + typeid(Attrib).name());
			}
			setAttrib(Attrib::AttribID, val);
		}

	public:
		virtual ~AttributesItf() {}
	};
}
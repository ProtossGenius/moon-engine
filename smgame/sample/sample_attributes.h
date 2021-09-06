#pragma once
#include "smgame/attributes_itf.h"
#include <vector>
#include "userdef.h"
namespace smgame_sample {
	using namespace smgame;
	class Attribute :public AttributesItf {
	public:
		Attribute(int attribType, size_t floatSize, size_t doubleSize, size_t int32Size, size_t int64Size, size_t strSize) :
			AttributesItf(attribType),
		floats(floatSize), doubles(doubleSize), int32s(int32Size), int64s(int64Size), strings(strSize){}

	public:
		friend void AttribParseMsg(Attribute&, const std::string&);
		friend std::string AttribAsMessage(const Attribute&);
	public:
		//TODO: Serializable;
		Attribute& parseMsg(const std::string& msg) override { 
			AttribParseMsg(*this, msg);
			return *this; }// return itself.
		std::string asMessage() const override { return AttribAsMessage(*this); }

	private:
		float       getAttrib(size_t attrib, FloatAttrib) const override {	return floats[attrib];}
		double      getAttrib(size_t attrib, DoubleAttrib) const override { return doubles[attrib]; }
		int32_t     getAttrib(size_t attrib, Int32Attrib) const override { return int32s[attrib]; }
		int64_t     getAttrib(size_t attrib, Int64Attrib) const override { return int64s[attrib]; }
		std::string getAttrib(size_t attrib, StringAttrib) const override { return strings[attrib]; }
		void setAttrib(size_t attrib, float       val) override {floats[attrib] = val;	}
		void setAttrib(size_t attrib, double      val) override { doubles[attrib] = val; }
		void setAttrib(size_t attrib, int32_t     val) override { int32s[attrib] = val; }
		void setAttrib(size_t attrib, int64_t     val) override { int64s[attrib] = val; }
		void setAttrib(size_t attrib, std::string val) override { strings[attrib] = val; }
	private:
		std::vector<float> floats;
		std::vector<double> doubles;
		std::vector<int32_t> int32s;
		std::vector<int64_t> int64s;
		std::vector<std::string> strings;

	};
}

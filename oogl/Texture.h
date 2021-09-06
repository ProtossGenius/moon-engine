#pragma once

#include "Renderer.h"
#include "stb_image/stb_image.h"
namespace oogl {
	union ARGB_UNION
	{
		int argb;
		int8_t arr[4];
		ARGB_UNION(int argb) :argb(argb) {}
		ARGB_UNION(int8_t a, int8_t r, int8_t g, int8_t b) :arr{ b, g, r, a } {}
	};

	class ARGB {
	public:
		ARGB() :m_argbUnion(0) {}
		ARGB(int argb) :m_argbUnion(argb) {}
		ARGB(int8_t a, int8_t r, int8_t g, int8_t b) :m_argbUnion{ a, r, g, b } {}
	public:
		void argb(int argb) { m_argbUnion.argb = argb; }
		int argb()const { return m_argbUnion.argb; }
		void a(int8_t a) { m_argbUnion.arr[3] = a; }
		int8_t a() const { return m_argbUnion.arr[3]; }
		void r(int8_t r) { m_argbUnion.arr[2] = r; }
		int8_t r()const { return m_argbUnion.arr[2]; }
		void g(int8_t g) { m_argbUnion.arr[1] = g; }
		int8_t g() const { return m_argbUnion.arr[1]; }
		void b(int8_t b) { m_argbUnion.arr[0] = b; }
		int8_t b() const { return m_argbUnion.arr[0]; }

	public:
		int distance(const ARGB& rhs) const; //calc argb's distanse. 
	private:
		ARGB_UNION m_argbUnion;
	};

	inline int distance(const ARGB& lhs, const ARGB& rhs) { return lhs.distance(rhs); }

	class Texture
	{
	private:
		unsigned int m_RendererID;
		std::string m_FilePath;
		unsigned char* m_LocalBuffer;
		int m_Width, m_Height, m_BPP;

	public:
		Texture(const std::string& path):Texture(path, false, 0, 0){}
		Texture(const std::string& path, bool do_trans, ARGB trans_color, int trans_distance);
		~Texture();

		void Bind(unsigned int slot = 0)const;
		void Unbind()const;

		unsigned int ID() const { return m_RendererID; }
		int GetWidth() const { return m_Width; }
		int GetHeight() const { return m_Height; }

	};
}
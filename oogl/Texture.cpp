#include "Texture.h"
#include <iostream>
#include <math.h>
using namespace std;
namespace oogl {
	template<typename Type>
	Type _2(Type n) { return n * n; }
	int ARGB::distance(const ARGB& rhs) const
	{
		return int(sqrt(_2(r() - rhs.r()) + _2(g() - rhs.g()) + _2(b() - rhs.b())));
	}


	Texture::Texture(const std::string& path, bool do_trans, ARGB trans_color, int trans_distance) :m_FilePath(path), m_LocalBuffer(nullptr), m_Width(0), m_Height(0),
		m_BPP(0)
	{
		stbi_set_flip_vertically_on_load(1);
		m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);
		int all = m_Width * m_Height;
		int* array = (int*)m_LocalBuffer;
		for (int i = 0; i < all; ++i) {
			ARGB current(array[i]);
			if (distance(trans_color, current) < trans_distance) {
				current.a(0);
				array[i] = current.argb();
			}
		}

		GLCall(glGenTextures(1, &m_RendererID));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));

		if (m_LocalBuffer) {
			stbi_image_free(m_LocalBuffer);
		}
	}

	Texture::~Texture()
	{
		GLCall(glDeleteTextures(1, &m_RendererID));
	}

	void Texture::Bind(unsigned int slot) const
	{
		GLCall(glActiveTexture(GL_TEXTURE0 + slot));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
	}

	void Texture::Unbind() const
	{
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	}

}

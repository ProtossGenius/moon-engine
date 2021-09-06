#pragma once
#include <memory>
#include <string>
namespace oogl {
	
	template <typename Type>
	class Manager
	{
	public:
		virtual std::shared_ptr<Type> set(const std::string& path, std::shared_ptr<Type> val) = 0;
		virtual std::shared_ptr<Type> get(const std::string& path) = 0;
		virtual void free(const std::string& path) = 0;
		virtual ~Manager() {}
	private:

	};

	class Texture;
	Manager<Texture>& getTextureMgr();

	class Shader;
	Manager<Shader>& getShaderMgr();

}
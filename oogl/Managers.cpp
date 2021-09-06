#include "Managers.h"
#include <map>
#include "Texture.h"
#include "Shader.h"
namespace oogl {
	

	template<typename Type>
	class OManager : public Manager<Type> {
	typedef std::map<std::string, std::shared_ptr<Type>> Store;
	public:
		std::shared_ptr<Type> get(const std::string& path) override {
			auto iterTexture = m_tstore.find(path);
			if (iterTexture != m_tstore.end()) {
				return iterTexture->second;
			}

			auto tt = std::make_shared<Type>(path);
			m_tstore[path] = tt;
			return tt;
		}

		std::shared_ptr<Type> set(const std::string& path, std::shared_ptr<Type> val) {
			m_tstore[path] = val;
			return val;
		}

		void free(const std::string& path)override {
			m_tstore.erase(path);
		}
	private:
		Store m_tstore;
	};

	template<typename Type>
	Manager<Type>& getManager()
	{
		static OManager<Type> mgr;
		return mgr;
	}


	Manager<Texture>& getTextureMgr() {
		return getManager<Texture>();
	}

	Manager<Shader>& getShaderMgr() {
		return getManager<Shader>();
	}

}
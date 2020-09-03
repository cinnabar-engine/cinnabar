#ifndef _OBJECT_MANAGER_H_ 
#define _OBJECT_MANAGER_H_

#include <glad/glad.h>

#include "../ce_util.h"


#define OBJMAN ce::ObjectManager::GetInstance()
#define ISCLASS(type) std::is_same<T,type>::value;

template <class K, class V>
bool existInMap(std::map<K, V>& map, K& key) {
	return map.find(key) != map.end();
}
template <class K, class V>
unsigned getNextID(std::map<K, V>& map) {
	return map.size();
}

template <class K, class V>
void addToMap(std::map<K, V>& map, K& key, V& value) {
	map.insert(std::pair<K, V>(key, value));
}

template <class T>
PTR<T> getObject(OBJMAP(T)& map, std::string& name) {
	return map.at(name);
}

template <class T, class I>
PTR<T> createObject(OBJMAP(T)& map, I& info) {
	unsigned id = getNextID(map);
	PTR<T> object = PTR<T>(new T(info));
	addToMap(map, info.name, object);
	return object;
}

namespace ce {
	class Shader;
	class Mesh;
	class Texture;
	class Material;
	class GameObject;
	class Component;

	enum class CE_OBJ_TYPE {
		SHADER,
		MESH,
		TEXTURE,
		MATERIAL,
		GAME_OBJECT,
		COMPONENT
	};

	class ObjectManager {
	private:

		inline static ObjectManager* instance = 0;

		OBJMAP(Shader) shaders;
		OBJMAP(Mesh) meshes;
		OBJMAP(Texture) textures;
		OBJMAP(Material) materials;
		OBJMAP(GameObject) gameObjects;
		OBJMAP(Component) components;

		ObjectManager() {};
		~ObjectManager() {};
	public:
		static ObjectManager* GetInstance() {
			if (instance == 0) {
				instance = new ObjectManager();
			}
			return instance;
		}

		template <class T>
		int RegisterObject(T* obj, CE_OBJ_TYPE type) {
			int id = -1;
			switch (type)
			{
			case ce::CE_OBJ_TYPE::SHADER:
				id = getNextID(shaders);
				addToMap(shaders,obj->getName(), PTR<Shader>(obj));
				break;
			case ce::CE_OBJ_TYPE::MESH:
				id = getNextID(meshes);
				addToMap(meshes, obj->getName(), PTR<Mesh>(obj));
				break;
			case ce::CE_OBJ_TYPE::TEXTURE:
				id = getNextID(textures);
				addToMap(textures, obj->getName(), PTR<Texture>(obj));
				break;
			case ce::CE_OBJ_TYPE::MATERIAL:
				id = getNextID(materials);
				addToMap(materials, obj->getName(), PTR<Material>(obj));
				break;
			case ce::CE_OBJ_TYPE::GAME_OBJECT:
				id = getNextID(gameObjects);
				addToMap(gameObjects,obj->getName(), PTR<GameObject>(obj));
				break;
			case ce::CE_OBJ_TYPE::COMPONENT:
				id = getNextID(components);
				addToMap(components, obj->getName(), PTR<Component>(obj));
				break;
			default:
				break;
			}
			return id;
		}
	};
}

#endif // !_OBJECT_MANAGER_H_

#ifndef _RESOURCE_MANAGER_H
#define _RESOURCE_MANAGER_H
#include "cLog.hpp"
#include <memory>
#include <map>

template<typename T>
class ResourceManager {
private:
	static ResourceManager<T>* mInstance;
	ResourceManager<T>();

	//map of paths to texture ptrs
	std::map< std::string, std::unique_ptr<T>> mResources;
	//boost::mutex mResourceMutex;

public:
	~ResourceManager<T>();
	static ResourceManager<T>* instance();

	T& get(std::string path);
};

template<typename T>
ResourceManager<T>* ResourceManager<T>::mInstance = nullptr;

template<typename T>
ResourceManager<T>::ResourceManager() {

}

template<typename T>
ResourceManager<T>::~ResourceManager() {

}

template <typename T>
ResourceManager<T>* ResourceManager<T>::instance() {
	if (!mInstance) {
		mInstance = new ResourceManager<T>();
	}
	return mInstance;
}

template<typename T>
T& ResourceManager<T>::get(std::string path) {
	//lock the mutex
	//boost::lock_guard<boost::mutex> lock(mResourceMutex);

	//if path does not exist as a key in the map
	if (!mResources.count(path)) {
		//load texture from path
		std::unique_ptr<T> res(new T);
		if (!res->loadFromFile(path))
			cLog::inst()->print(3, "ResourceManager", "Texture at '" + path + "' could not be loaded");

		//put the texture into the map (move it instead of copying)
		mResources.insert(std::make_pair(path, std::move(res)));
	}

	//return reference to the texture
	return *mResources.at(path);
}//unlock the mutex here when lock_guard goes out of scope
#endif
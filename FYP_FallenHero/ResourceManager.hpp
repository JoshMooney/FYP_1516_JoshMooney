#ifndef _RESOURCE_MANAGER_H
#define _RESOURCE_MANAGER_H
#include "cLog.hpp"
#include <memory>
#include <map>

/**
*	@class ResourceManager Can be used for loading any data type thanks to its use of templates
*	@brief This class is ultra light weight and can be implemented easly something i tend to forget if im using
*	this class is how to actually call its singleton. When using the ResourceManager you must declare the type you 
*	wish to use before any method call e.g. ResourceManager<sf::Texture>::instance()->get(File name here);
*/
template<typename T>
class ResourceManager {
private:
	static ResourceManager<T>* mInstance;		//!<This is the instance of the resourceManager and is required as part of the singleton pattern if confused: https://en.wikipedia.org/wiki/Singleton_pattern
	ResourceManager<T>();						//!<Template default constructor for the class

	/**
	*	@brief This container stores the resource in a map for easy access
	*	@param std::string - The route to the resource as a string
	*	@param std::unique_ptr<T> - A unique pointer to a templated resource
	*/
	std::map< std::string, std::unique_ptr<T>> mResources;
	//boost::mutex mResourceMutex;

public:
	~ResourceManager<T>();						//!<Publicly available deconstructor for the class				
	static ResourceManager<T>* instance();      //!<Fetches the current instance of the Manager is required to achieve the singleton pattern
                                                
	/**
	*	@brief Gets the resouce and if it does not exist it creates and stores that resource
	*	@param std::string This is the path to the file on the computer
	*/	
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
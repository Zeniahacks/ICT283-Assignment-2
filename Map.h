#ifndef MAP_H
#define MAP_H

#include <map>

/**
 * @class Map
 * @brief A template wrapper class for the standard C++ std::map container.
 *
 * This class provides a dynamic, heap-allocated wrapper around std::map,
 * implementing the Rule of Three (Destructor, Copy Constructor, Assignment Operator)
 * and providing specific methods for insertion and retrieval that handle
 * key and value pointers, as required by the application's design.
 *
 * @tparam K The type of the key (must be comparable).
 * @tparam V The type of the value.
 */
template<typename K, typename V>
class Map {
private:
	/**
	 * @brief Pointer to the internal standard C++ map container.
	 */
	std::map<K, V>* internalMap;

public:
	/**
	 * @brief Default constructor.
	 *
	 * Initializes and dynamically allocates the internal std::map.
	 */
	Map() {
		internalMap = new std::map<K, V>();
	}

	/**
	 * @brief Destructor.
	 *
	 * Frees the dynamically allocated internal std::map.
	 */
	~Map() {
		delete internalMap;
	}

	/**
	 * @brief Copy constructor (Rule of Three).
	 *
	 * Performs a deep copy of the internal map from the 'other' Map object.
	 * @param other The Map object to copy from.
	 */
	Map(const Map& other) {
		internalMap = new std::map<K, V>(*(other.internalMap));
	}

	/**
	 * @brief Assignment operator (Rule of Three).
	 *
	 * Performs a deep copy assignment. Cleans up existing resources
	 * and copies the internal map from the 'other' Map object.
	 * @param other The Map object to assign from.
	 * @return Map& A reference to the current Map object.
	 */
	Map& operator=(const Map& other) {
		if (this != &other) {
			delete internalMap;
			internalMap = new std::map<K, V>(*(other.internalMap));
		}
		return *this;
	}

	/**
	 * @brief Inserts a key-value pair into the map.
	 *
	 * Keys and values are passed as pointers, but the dereferenced copies
	 * are stored in the internal map (copy semantics).
	 * @param key A constant pointer to the key to insert.
	 * @param value A constant pointer to the value to insert.
	 */
	void insert(const K* key, const V* value) {
		(*internalMap)[*key] = *value;
	}

	/**
	 * @brief Checks if the map contains the specified key.
	 * @param key A constant pointer to the key to search for.
	 * @return bool True if the key is found, false otherwise.
	 */
	bool contains(const K* key) const {
		return internalMap->find(*key) != internalMap->end();
	}

	/**
	 * @brief Retrieves a pointer to the value associated with the specified key (mutable version).
	 *
	 * Behaves like std::map operator[]: if the key does not exist, it is inserted
	 * with a default-constructed value.
	 * @param key A constant pointer to the key.
	 * @return V* A mutable pointer to the value.
	 */
	V* at(const K* key) {
		return &(*internalMap)[*key];
	}

	/**
	 * @brief Retrieves a constant pointer to the value associated with the specified key (constant version).
	 *
	 * Behaves like std::map::at(): throws an exception if the key is not found.
	 * @param key A constant pointer to the key.
	 * @return const V* A constant pointer to the value.
	 */
	const V* at(const K* key) const {
		return &internalMap->at(*key);
	}

	/**
	 * @brief Returns the number of key-value pairs in the map.
	 * @return size_t The size of the map.
	 */
	size_t size() const { return internalMap->size(); }

	// Iterator support (C++11-compatible)
	/**
	 * @brief Returns an iterator pointing to the first element in the map (mutable).
	 * @return typename std::map<K, V>::iterator An iterator to the beginning.
	 */
	typename std::map<K, V>::iterator begin() { return internalMap->begin(); }

	/**
	 * @brief Returns an iterator referring to the past-the-end element in the map (mutable).
	 * @return typename std::map<K, V>::iterator An iterator to the end.
	 */
	typename std::map<K, V>::iterator end() { return internalMap->end(); }

	/**
	 * @brief Returns a const iterator pointing to the first element in the map (constant).
	 * @return typename std::map<K, V>::const_iterator A const iterator to the beginning.
	 */
	typename std::map<K, V>::const_iterator begin() const { return internalMap->begin(); }

	/**
	 * @brief Returns a const iterator referring to the past-the-end element in the map (constant).
	 * @return typename std::map<K, V>::const_iterator A const iterator to the end.
	 */
	typename std::map<K, V>::const_iterator end() const { return internalMap->end(); }
};

#endif // MAP_H

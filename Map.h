#ifndef MAP_H
#define MAP_H

#include <map>

template<typename K, typename V>
class Map {
private:
    std::map<K, V>* internalMap;

public:
    Map() {
        internalMap = new std::map<K, V>();
    }

    ~Map() {
        delete internalMap;
    }

    // Copy constructor
    Map(const Map& other) {
        internalMap = new std::map<K, V>(*(other.internalMap));
    }

    // Assignment operator
    Map& operator=(const Map& other) {
        if (this != &other) {
            delete internalMap;
            internalMap = new std::map<K, V>(*(other.internalMap));
        }
        return *this;
    }

    // Pointer-based insert (key and value passed as pointers)
    void insert(const K* key, const V* value) {
        (*internalMap)[*key] = *value;
    }

    bool contains(const K* key) const {
        return internalMap->find(*key) != internalMap->end();
    }

    V* at(const K* key) {
        return &(*internalMap)[*key];
    }

    const V* at(const K* key) const {
        return &internalMap->at(*key);
    }

    size_t size() const { return internalMap->size(); }

    // Iterator support (C++11-compatible)
    typename std::map<K, V>::iterator begin() { return internalMap->begin(); }
    typename std::map<K, V>::iterator end() { return internalMap->end(); }
    typename std::map<K, V>::const_iterator begin() const { return internalMap->begin(); }
    typename std::map<K, V>::const_iterator end() const { return internalMap->end(); }
};

#endif // MAP_H

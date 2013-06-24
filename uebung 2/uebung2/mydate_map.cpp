#include "mydate_map.h"
#include <iostream>
namespace MyDate {

	// getters
	Map::Node* Map::getRootNode() { return m_root; }
	size_t Map::size() const { return m_size; }

	Map::MapIterator Map::insert(Map::key_t& key, Map::mapped_t& value) {
		return insert(Pair(key,value));
	}

	Map::MapIterator Map::insert(const Map::Pair& pair) {
        Map::Node *parent = 0;
        Map::Node **target = &m_root;						// starting with root
        while(*target) {									
            if (m_order(pair, (*target)->value())) {
                parent = *target;							// left smaller value
                target = &((*target)->m_left);
            } else if (m_order((*target)->value(), pair)) {
                parent = *target;							// right: larger value 
                target = &((*target)->m_right);
            } else break;									// already there
        }

		// actual insertion
        if (*target) (*target)->m_pair = pair;				// replace value if node exists
        else { 
			*target = new Node(pair, &m_order, parent);		// or create new leaf with value
			++m_size;
		}
        return MapIterator(this, *target);
    }

	Map::MapIterator Map::insert(Map::key_t& key) {
		return insert(Pair(key,mapped_t()));
	}

	// find by key
	Map::MapIterator Map::find(const Map::key_t& key) const {
		return MapIterator(this, m_root->find(key));
	}

	// find by value
	Map::MapIterator Map::find(const Map::mapped_t& value) const {
		return MapIterator(this, m_root->find(value));
	}

	// find pair
	Map::MapIterator Map::find(const Map::Pair& pair) const {
		return MapIterator(this, m_root->find(pair));
    }

	const Map::MapIterator Map::findReadOnly(const Map::key_t& key) const {
		return Map::MapIterator(this, m_root->find(key));
	}

	bool Map::contains(const Map::key_t& key) const {
		return isEmpty() ? false : m_root->find(key) && m_root->find(key)->m_pair.first == key;
	}

	bool Map::isEmpty() const {
		return m_root == 0;
	}

	// operators
	Map::mapped_t& Map::operator [] (const Map::key_t& key) {
		if(this->contains(key)) {
			Map::MapIterator iter = find(key);
			if(iter != end()) return iter->second;		// return found pair	
		}
		Map::Pair pair = Pair(key,Map::mapped_t());		// create default pair
		insert(pair);									// and insert new pair	
		return find(pair)->second;
	}

	const Map::mapped_t& Map::operator [] (const Map::key_t& key) const {
		if(isEmpty()) return M_NOT_IN_MAP;
		Map::MapIterator iter = findReadOnly(key);
		return iter != end() ? iter->second : M_NOT_IN_MAP;				
	}

	Map Map::operator = (Map& other) {
		return Map(other);
	}

	// miscellaneous 

	Map::MapIterator Map::begin(){
		return m_root ? Map::MapIterator(this, m_root->findFirst()) : Map::MapIterator(this, 0);
    }

    Map::MapIterator Map::end() const {
        return Map::MapIterator(this, 0);
    }

    Map::MapIterator Map::first() {
        return begin();
    }

    Map::MapIterator Map::last() {
		return m_root ? Map::MapIterator(this, m_root->findLast()) : Map::MapIterator(this, 0);
    }
}
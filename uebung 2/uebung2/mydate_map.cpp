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

	// find by key
	Map::MapIterator Map::find(const Map::key_t& key) {
		return find(Pair(key, mapped_t()));
	}

	// find by value
	Map::MapIterator Map::find(const Map::mapped_t& value) {
		return find(Pair(key_t(), value)); // ZODO doesn't find a value
	}

	// find pair, basically finds if there is a key with that value
	Map::MapIterator Map::find(const Map::Pair& pair) {
		return MapIterator(this, m_root->find(pair));
    }

	const Map::mapped_t Map::findReadOnly(const Map::key_t& key) const {
		return 0;
	}

	bool Map::contains(const Map::key_t& key) const {
		return m_root->find(key) == 0;
	}

	// operators
	const Map::mapped_t& Map::operator [] (const Map::key_t& key) {
		Map::Pair pair = Pair(key,Map::mapped_t()); // create default pair to search for key
		Map::MapIterator iter = find(pair);

		if(iter != end()) cout << "<" << iter->first << "," << iter->second << ">" << endl;

        if(iter != end()) return iter->second;		// return found pair	
        insert(pair);								// or insert new pair	
        return find(pair)->second;
	}

	void Map::operator = (Map& map) {
	}

	// miscellaneous 

	Map::MapIterator Map::begin(){
		return m_root ? Map::MapIterator(this, m_root->findFirst()) : Map::MapIterator(this, 0);
    }

    Map::MapIterator Map::end(){
        return Map::MapIterator(this, 0);
    }

    Map::MapIterator Map::first() {
        return begin();
    }

    Map::MapIterator Map::last() {
		return m_root ? Map::MapIterator(this, m_root->findLast()) : Map::MapIterator(this, 0);
    }
}
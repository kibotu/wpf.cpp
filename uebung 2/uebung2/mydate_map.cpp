#include "mydate_map.h"

namespace MyDate {

	// getters
	Map::Node* Map::getRootNode() { return m_root; }
	size_t Map::size() const{ return m_size; }

	// setters
	void Map::insert(Map::key_t key, Map::mapped_t value) { 
		Node *parent = 0;
		Node **target = &m_root;                // starting with root
		while(*target) {                        // find where value needs to go
			if (m_order(value, (*target)->value())) {
				parent = *target;               // smaller value goes left
				target = &((*target)->m_left);
			} else if (m_order((*target)->value(), value)) {
				parent = *target;               // larger value goes right
				target = &((*target)->m_right);
			} else {
				break;                          // it's there already!
			}
		}
		if (*target) {
			(*target)->m_value = value;         // replace value if node exists
		} else {
			*target = new Node(value, &m_order, parent);    // or create new leaf with value
			m_size++;
		}
	}
	void Map::insert(Map::pair pair) { insert(pair.first(), pair.second()); }
	void Map::insert(Map::key_t key, int id) { }

	// basic functions
	Map::Node* Map::find(const Map::mapped_t& value) { return m_root->find(value); }
	Map::Node* Map::find(const Map::pair& pair) { return m_root->find(pair.second()); }
	Map::Node* Map::find(const key_t& key) { return 0; }
	const Map::mapped_t Map::findReadOnly(Map::Node& last, const key_t& key) const { return 0; }
	bool Map::contains(Map::Node& last, const key_t& key) { return false; }

	// operators
	const Map::mapped_t& Map::operator[](const Map::key_t& key) {
            pair keypair = pair(key,mapped_t());  // create default pair to search for key
            Node* result = find(keypair); // return found pair
			if(result) return result->m_value;
			insert(keypair);  // or insert default pair
            return find(keypair)->m_value;
    }

	void Map::operator = (Map& map) { }
}
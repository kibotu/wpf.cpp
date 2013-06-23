#ifndef MYDATE_MAP_H
#define MYDATE_MAP_H

#include <string>
#include <utility>
#include <iostream>
#include "mydate.h"
#include "order.h"

namespace MyDate {

	class Map {

	public:

		typedef Date key_t;
		typedef std::string mapped_t;
		typedef std::pair<key_t, mapped_t> Pair;
		typedef Less<Pair> order_t;

		class Node {

		public:

			Pair m_pair;
			order_t *m_order;
			Node *m_up, *m_left, *m_right;

			explicit Node(const Pair &pair, order_t *order = &order_t(), Node *parent = 0) : m_pair(pair), m_order(order), m_left(0), m_right(0), m_up(parent) { }
			explicit Node(const key_t &key, const mapped_t &value, order_t *order = &order_t(), Node *parent = 0) : m_pair(Pair(key,value)), m_order(order), m_left(0), m_right(0), m_up(parent) { }
			~Node() { 
				/*if(m_up) delete m_up;
				if(m_left) delete m_left;
				if(m_right) delete m_right;*/
			}
			Pair& value() { return m_pair; }

			Node* find(const Pair&value) {
				if((*m_order)(m_pair, value)) return m_right ? m_right->find(value) : 0;		// larger value: try right         
				else if((*m_order)(value, m_pair)) return m_left ? m_left->find(value) : 0;		// smaller value: try left
				else return this;																// equal value
			}
			Node* find(const key_t& key) {
				if(m_pair.first < key) return m_right ? m_right->find(key) : 0;					         
				else if(key <m_pair.first) return m_left ? m_left->find(key) : 0;				
				else return this;	
			}
			Node* find(const mapped_t& value) {
				if(m_pair.second < value) return m_right ? m_right->find(value) : 0;			         
				else if(value <m_pair.second) return m_left ? m_left->find(value) : 0;			
				else return this;																
			}
			Node* insert(const key_t& key, const mapped_t& value) { }
			Node* findFirst(){ return m_left == 0 ? this : m_left->findFirst(); }				// leftmost node
			Node* findLast(){ return m_right == 0 ? this : m_right->findFirst(); }				// rightmost node             
		};
		
		class MapIterator {

			const Map *m_map;
			Node *m_node;

		public:

			MapIterator(const Map *tree, Node *node) : m_map(tree), m_node(node) { }
			Pair& operator*() { return m_node->value(); }
			Pair* operator->() { return &m_node->value(); }
			const bool operator==(const MapIterator &rhs) const { return m_node == rhs.m_node; } // iterators are equal if they point to same node
			const bool operator!=(const MapIterator &rhs) const { return !(*this == rhs); }

			MapIterator& operator++() {
				if (!m_node) return *this;  // stay at end
				if( m_node->m_right != 0 ) m_node = m_node->m_right->findFirst();  // if we can go right, go to leftmost node in right subtree
				else {
					Node *cur = m_node->m_up;  // otherwise, go up until larger node or 0
					while(cur && m_map->m_order(cur->value(), m_node->value()))	cur = cur->m_up;
					m_node = cur;
				}
				return *this;
			}

			MapIterator& operator--() {
				if (!m_node) {
					m_node = m_map->m_root->findLast(); // if at end, go back to last node
					return *this;
				}
				if( m_node->m_left != 0 ) m_node = m_node->m_left->findLast(); // if we can go left, go to rightmost node in left subtree
				else {
					Node *cur = m_node->m_up; // otherwise go up until smaller node or 0
					while(cur && m_map->m_order(m_node->value(), cur->value())) cur = cur->m_up;
					m_node = cur;
				}
				return *this;
			}
		};

		Node* m_root;
		size_t m_size;
		const mapped_t M_NOT_IN_MAP;
		order_t m_order;

		// con-/destructor
		Map():m_root(0),m_size(0),M_NOT_IN_MAP(mapped_t()), m_order(order_t()) {}
		~Map() { if(m_root != 0) { delete(m_root); } }

		// getters
		Node* getRootNode();
		size_t size() const;

		// setters
		MapIterator insert(key_t& key, mapped_t& value);
		MapIterator insert(const Pair& pair); // if there is a key with that value, if not overwrite existing key with new value

		// basic functions
		MapIterator find(const key_t& key);
		MapIterator find(const mapped_t& value);
		MapIterator find(const Pair& pair);
		const MapIterator findReadOnly(const Map::key_t& key) const;
		bool contains(const key_t& key) const;

		// operators
		mapped_t& operator [] (const key_t& key);
		const mapped_t& operator [] (const key_t& key) const;
		void operator = (Map& map);

		// miscellaneous 
		MapIterator begin();
        MapIterator end() const;
        MapIterator first();
        MapIterator last();
	};
}

#endif // MYDATE_MAP_H

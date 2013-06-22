#ifndef MYDATE_MAP_H
#define MYDATE_MAP_H

#include <string>
#include "mydate.h"
#include "pair.h"
#include "order.h"

namespace MyDate {

	class Map {

	public:

		typedef Date key_t;
		typedef string mapped_t;
		typedef Pair<key_t, mapped_t> pair;

		class Node{

		public:

			Less<pair> *m_order; 
			pair m_value;
			Node *m_left;
			Node *m_right;
			Node *m_up;

			Node(const pair &value, Less<pair> *order, Node *up = 0): m_value(value), m_order(order), m_left(0), m_right(0), m_up(up) { }

			pair& value() { return m_value; }
			Node* findFirst() { return m_left == 0 ? this : m_left->findFirst(); } 
			Node* findLast() { return m_right == 0 ? this : m_right->findFirst(); }

			Node* find(const pair&value){
				// larger value? try right
				if((*m_order)(m_value, value)) return m_right ? m_right->find(value) : 0;
				// smaller value? try left
				else if((*m_order)(value, m_value)) return m_left ? m_left->find(value) : 0;		
				// equal value is found
				else return this;
			}
		};

		// constructors
		Map():m_root(0),m_size(0),m_order(Less<pair>()) {}
		~Map() { if(m_root != 0) { delete(m_root); } }

		// getters
		Node* getRootNode();
		size_t size() const;

		// setters
		void insert(key_t key, mapped_t value);
		void insert(pair pair);
		void insert(key_t key, int id);

		// basic functions
		Node* find(const key_t& key);
		Node* find(const mapped_t& value);
		Node* find(const pair& pair);
		const mapped_t findReadOnly(Node& last, const key_t& key) const;
		bool contains(Node& last, const key_t& key);

		// operators
		const mapped_t& operator [] (const key_t& key);
		void operator = (Map& map);

	protected:

		// variables
		Node* m_root; 
		size_t m_size; 
		Less<pair> m_order;
		const mapped_t M_NOT_IN_MAP;  
	};
}	 

#endif // MYDATE_MAP_H
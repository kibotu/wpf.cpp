#ifndef MAP_H
#define MAP_H

#include <utility>
#include "tree.h"

namespace MyMap{

    template<typename KeyT, typename ValueT, template<typename> class OrderT=Less>
    class Map {

    public:

        typedef std::pair<KeyT, ValueT> Pair;
        typedef TreeIterator<Pair, OrderT> Iterator;
        typedef Tree<Pair> Tree;

    private:

        Tree m_tree;

    public:

        Map():m_tree(Tree()) { }

        ValueT& operator[](const KeyT& key){
            Pair pair = Pair(key,ValueT());		
            Iterator iter = m_tree.find(pair);
            if(iter != end()) {
                return iter->second;         
            }
            insert(pair);						
            return m_tree.find(pair)->second;
        }

        Iterator insert(const Pair& v_pair){ return m_tree.insert(v_pair); }
        Iterator find(const KeyT& key){ return m_tree.find(Pair(key,0)); }
        Iterator begin(){ return m_tree.begin(); }
        Iterator end(){ return m_tree.end(); }
        Iterator first(){ return m_tree.first(); }
        Iterator last(){ return m_tree.last(); }
        const KeyT& min(){ return (*m_tree.first()).first(); }
        const KeyT& max(){ return (*m_tree.last()).first(); }
        void clear(){ m_tree.clear();}
    };
}
#endif // MAP_H

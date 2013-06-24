#ifndef TREE_H
#define TREE_H

#include <iostream>
#include "order.h"

namespace MyMap {

    template<typename T, typename O> class Tree;
    template<typename T, typename O> class TreeIterator;

    template<typename T, typename O>
    class TreeNode{

        friend class Tree<T, O>;
        friend class TreeIterator<T, O>;

        TreeNode *m_left;
        TreeNode *m_right;
        TreeNode *m_up;

        O *m_order;     // for convenience

        T m_value;

        public:
        TreeNode(const T &value, O *order, TreeNode<T, O> *up = 0):
            m_left(0),
            m_right(0),
            m_up(up),
            m_order(order),
            m_value(value)
        { }

        T& value(){
            return m_value;
        }

        TreeNode<T,O>* find(const T&value){
            if((*m_order)(m_value, value)){             // larger value: try right
                if(m_right) return m_right->find(value);
                return 0;
            } else if((*m_order)(value, m_value)) {     // smaller value: try left
                if(m_left) return m_left->find(value);
                return 0;
            } else {
                return this;                            // equal value is found
            }
        }

        TreeNode<T,O>* findFirst(){            // leftmost node
            if (m_left == 0) return this;
            return m_left->findFirst();
        }

        TreeNode<T,O>* findLast(){              // rightmost node
            if (m_right == 0) return this;
            return m_right->findFirst();
        }

    };


    // =========================
    // Tree
    // ==========

    template<typename T, typename O=Less<T> >
    class Tree{

        friend class TreeIterator<T, O>;

    public:
        typedef TreeIterator<T, O> iterator;
        typedef TreeNode<T, O> node;

    private:
        node *m_root;
        O m_order;

    public:
        Tree(){
            m_root = 0;
            m_order = O();
        }

        ~Tree() {
            clear();
        }

        /* insert value into tree, replacing it if exists, and return iterator pointing to the value */
        iterator insert(const T& value) {
            node *parent = 0;
            node **target = &m_root;                // starting with root
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
                *target = new node(value, &m_order, parent);    // or create new leaf with value
            }
            return iterator(this, *target);
        }

        void clear() {
            deleteTree(m_root);
            m_root = 0;
        }

        iterator begin() {
            if (!m_root) {
                return iterator(this, 0);
            }
            return iterator(this, m_root->findFirst());
        }

        iterator end() {
            return iterator(this, 0);
        }

        iterator first() {
            return begin();
        }

        iterator last() {
            if (!m_root) {
                return iterator(this, 0);
            }
            return iterator(this, m_root->findLast());
        }

        iterator find(const T& value) {
            return iterator(this, m_root->find(value));
        }

    private:
        /* frees memory occupied by the nodes of the tree with root n */
        void deleteTree(node *n) {
            if (n) {
                if(n->m_left) deleteTree(n->m_left);
                if(n->m_right) deleteTree(n->m_right);
                delete n;
            }
        }

    };


    // =========================
    // TreeIterator
    // ==========

    template<typename T, typename O>
    class TreeIterator{

        Tree<T,O> *m_tree;
        TreeNode<T,O> *m_node;

        public:
            TreeIterator(Tree<T,O> *tree, TreeNode<T,O> *node):
                    m_tree(tree),
                    m_node(node)
            { }

            T& operator*(){
                return m_node->value();
            }

            T* operator->() {
                return &m_node->value();
            }

            TreeIterator<T,O>& operator++(){
                if (!m_node) {
                    return *this;                   // stay at end
                }
                if( m_node->m_right != 0 ){                 // if we can go right,
                    m_node = m_node->m_right->findFirst();  // go to leftmost node in right subtree
                } else {
                    TreeNode<T,O> *current = m_node->m_up;  // otherwise, go up until larger node or 0
                    while(current && m_tree->m_order(current->value(), m_node->value())){
                        current = current->m_up;
                    }
                    m_node = current;
                }
                return *this;
            }

            TreeIterator<T,O>& operator--(){
                if (!m_node) {
                    m_node = m_tree->m_root->findLast();    // if at end, go back to last node
                    return *this;
                }
                if( m_node->m_left != 0 ){                  // if we can go left,
                    m_node = m_node->m_left->findLast();    // go to rightmost node in left subtree
                } else {
                    TreeNode<T,O> *current = m_node->m_up;  // otherwise go up until smaller node or 0
                    while(current && m_tree->m_order(m_node->value(), current->value())){
                        current = current->m_up;
                    }
                    m_node = current;
                }
                return *this;
            }

            bool operator==(const TreeIterator<T,O> &rhs) {
                return m_node == rhs.m_node;                // iterators are equal if they point to same node
            }

            bool operator!=(const TreeIterator<T,O> &rhs) {
                return !(*this == rhs);
            }

    };
}


#endif // TREE_H

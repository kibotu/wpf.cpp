#ifndef NODE_H
#define NODE_H

#include <string>
using namespace std;

class Node
{
    string m_value;
    Node* m_next;

public:
    Node(const string& value = string()) : m_value(value), m_next(0){}
    ~Node(){
        if(m_next) delete m_next;
    }

    bool contains(const string& value) {
        if(value == m_value) return true;
        if(m_next) return m_next->contains(value);
        else return false;
    }

    Node* append(const string& value);

    Node& operator=() {

        m_next->~Node();

        // build new list

        return *this;
    }
};

#endif // NODE_H


Node* Node::append(const string& value){
    if(!m_next)
        return m_next = new Node(value);
    else
        m_next->m_next->append(value);
}

#ifndef LIST_H
#define LIST_H

#include "structurerepresentor.h"
#include <fstream>

template<typename K,typename V>
class List:public StructureRepresentor<K,V>
{
public:
    List();
    ~List();

    void insert(K data,V value)override;
    void remove(K key)override;
    V find(K key)override;
    void randomInsert()override;
    void writeDotFile(const char* filename)override;
    StructureRepresentor<K,V>* Union(StructureRepresentor<K,V>*s)override;
    StructureRepresentor<K,V>* Intersection(StructureRepresentor<K,V>*s)override;
    StructureRepresentor<K,V>* SymDiff(StructureRepresentor<K,V>*s)override;
    StructureRepresentor<K,V>* Diff(StructureRepresentor<K,V>*s)override;
    vector<pair<K,V>> getKeys()override;
    void sort()override;
    void clear()override;
private:
    void pop_front();

    template<typename T1, typename T2>
    class Node
    {
    public:
        Node*next;
        K key;
        V value;
        Node(T1 data = T1(), T2 value = T2(), Node*next=NULL)
        {
            this->key = data;
            this->value = value;
            this->next = next;
        }
    };
    int Size;
    Node<K, V> *head;
};
template<typename K, typename V>
List<K,V>::List()
{
    Size = 0;
    head = NULL;
    StructureRepresentor<K,V>::type = StructureRepresentor<K,V>::Type::LinkedList;
}
template<typename K, typename V>
List<K, V>::~List()
{
    clear();
}

template<typename K, typename V>
void List<K, V>::pop_front()
{
    Node<K,V>*temp = head;
    head = head->next;
    delete temp;
    Size--;
}
template<typename K, typename V>
void List<K, V>::clear()
{
    while (Size)
    {
        pop_front();
    }
}
template<typename K, typename V>
void List<K, V>::insert(K data,V value)
{
    head = new Node<K,V>(data,value,head);
    Size++;
}

template<typename K, typename V>
void List<K, V>::remove(K key)
{
    Node<K, V>* current = head;
    if (current && current->key == key)
    {
        Node<K, V>* removed = head;
        head = head->next;
        delete head;
        Size--;
    }
    else
    {
        while (current->next && current->next->key != key)
        {
            current = current->next;
        }
        if (current->next)
        {
            Node<K, V>* removed = current->next;
            current->next = current->next->next;
            delete removed;
            Size--;
        }
    }
}
template<typename K, typename V>
V List<K, V>::find(K key)
{
    Node<K, V>* current = head;
    if (current && current->key == key)
    {
        return current->value;
    }
    else
    {
        while (current->next && current->next->key != key)
        {
            current = current->next;
        }
        if (current->next)
        {
            return current->next->value;
        }
        else
        {
            return V();
        }
    }
}

template<typename K,typename V>
void List<K,V>::randomInsert()
{

}

template<typename K,typename V>
void List<K,V>::writeDotFile(const char *filename)
{
    std::ofstream fout(filename);
    fout << "digraph{node[shape=record]\n" << std::endl;

    Node<K,V>*cur = head;
        while(cur)
        {
            fout << "      " << (quintptr)cur;
            fout << "[label=\"";
            fout << "{key: " << cur->key << "|val:" << cur->value << "}";
            fout << "\"];" << std::endl;
            cur = cur->next;
        }
        fout << "\n\n";

        cur = head;

        fout << (quintptr)cur;
        cur = cur->next;
        while(cur)
        {
            fout << "->" << (quintptr)cur << ";\n";
            fout << (quintptr)cur;
            cur = cur->next;
        }
        fout << "->end;\n";
    fout << "}";
}

template<typename K, typename V>
StructureRepresentor<K, V> *List<K, V>::Union( StructureRepresentor<K, V> *s)
{
    vector<pair<K,V>>p1 = this->getKeys();
    vector<pair<K,V>>p2 = s->getKeys();
    StructureRepresentor<K,V>*sr = new List<K,V>;
    for(pair<K,V>p:p1)
    {
        sr->insert(p.first,p.second);
    }
    for(pair<K,V>p:p2)
    {
        sr->insert(p.first,p.second);
    }
    return sr;
}

template<typename K, typename V>
StructureRepresentor<K, V> *List<K, V>::Intersection( StructureRepresentor<K, V> *s)
{

}

template<typename K, typename V>
StructureRepresentor<K, V> *List<K, V>::SymDiff( StructureRepresentor<K, V> *s)
{

}

template<typename K, typename V>
StructureRepresentor<K, V> *List<K, V>::Diff( StructureRepresentor<K, V> *s)
{

}

template<typename K, typename V>
vector<pair<K,V>> List<K, V>::getKeys()
{
    vector<pair<K,V>>key_val;
    Node<K,V>*cur = head;
    while(cur)
    {
        key_val.emplace_back(cur->key,cur->value);
        cur = cur->next;
    }
    return key_val;
}

template<typename K, typename V>
void List<K,V>::sort()
{

}
#endif // LIST_H

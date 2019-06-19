#ifndef LIST_H
#define LIST_H

#include "structurerepresentor.h"
#include <fstream>

template<typename K,typename V>
class List:public StructureRepresentor<K,V>
{
public:
    List();
    ~List()override;

    void insert(const K& data,const V& value)override;
    void remove(const K& key)override;
    V find(const K& key)override;
    void writeDotFile(const char* filename)override;
    StructureRepresentor<K,V>* Union(StructureRepresentor<K,V>*s)override;
    StructureRepresentor<K,V>* Intersection(StructureRepresentor<K,V>*s)override;
    StructureRepresentor<K,V>* SymDiff(StructureRepresentor<K,V>*s)override;
    StructureRepresentor<K,V>* Diff(StructureRepresentor<K,V>*s)override;
    vector<pair<K,V>> getKeys()override;
    void sortByKey()override;
    void sortByValue()override;
    void clear()override;
    bool isEmpty()override;
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
    Node<K,V>*operator[](int index);
    void swap(Node<K,V>*n1,Node<K,V>*n2);

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
typename List<K,V>::template Node<K, V> *List<K,V>::operator[](int index)
{
    if(index < Size && index >= 0)
    {
        Node<K,V>*cur = head;
        for(int i = 0; i < index; i++)
            cur = cur->next;
        return cur;
    }
    else
        return  nullptr;

}

template<typename K, typename V>
void List<K,V>::swap(Node<K, V> *n1, Node<K, V> *n2)
{
    int a = n1->key;
    n1->key = n2->key;
    n2->key = a;

    a = n1->value;
    n1->value = n2->value;
    n2->value = a;

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
bool List<K,V>::isEmpty()
{
    return Size == 0;
}
template<typename K, typename V>
void List<K, V>::insert(const K& data,const V& value)
{
    head = new Node<K,V>(data,value,head);
    Size++;
}

template<typename K, typename V>
void List<K, V>::remove(const K& key)
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
V List<K, V>::find(const K& key)
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
void List<K,V>::writeDotFile(const char *filename)
{


    Node<K,V>*cur = head;
    if(cur)
    {
        std::ofstream fout(filename);
        fout << "digraph{node[shape=record]\n" << std::endl;
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
    vector<pair<K,V>>p1 = this->getKeys();
    vector<pair<K,V>>p2 = s->getKeys();
    StructureRepresentor<K,V>*I = new List<K,V>;
    for(pair<K,V>p:p1)
    {
        auto element = std::find_if(p2.begin(),p2.end(),[p](const pair<int,int>&pair){return pair.second == p.second;});
        if(element !=p2.end())
        {
            I->insert(element->first,element->second);
        }
    }
    return I;
}

template<typename K, typename V>
StructureRepresentor<K, V> *List<K, V>::SymDiff( StructureRepresentor<K, V> *s)
{
    StructureRepresentor<K, V> *inters = this->Intersection(s);
    StructureRepresentor<K, V> *diff1 = this->Diff(inters);
    StructureRepresentor<K, V> *diff2 = s->Diff(inters);
    StructureRepresentor<K, V> *res = diff1->Union(diff2);
    delete inters,diff1,diff2;
    return res;
}

template<typename K, typename V>
StructureRepresentor<K, V> *List<K, V>::Diff( StructureRepresentor<K, V> *s)
{
    vector<pair<K,V>>p1 = this->getKeys();
    vector<pair<K,V>>p2 = s->getKeys();
    StructureRepresentor<K,V>*D = new List<K,V>;
    for(pair<K,V>p:p1)
    {
        auto element = std::find_if(p2.begin(),p2.end(),[p](const pair<int,int>&pair){return pair.second == p.second;});
        if(element == p2.end())
        {
            D->insert(p.first,p.second);
        }
    }
    return D;
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
void List<K,V>::sortByKey()
{
    for(int i = 0; i < Size; i++)
    {
        for(int j = 1; j < Size-i;j++)
        {
            Node<K,V>*n1 = this->operator[](j-1);
            Node<K,V>*n2 = this->operator[](j);
            if(n1&&n2)
            {
                if(n1->key>n2->key)
                {
                   this->swap(n1,n2);
                }
            }
        }
    }
}

template<typename K, typename V>
void List<K,V>::sortByValue()
{
    for(int i = 0; i < Size; i++)
    {
        for(int j = 1; j < Size-i;j++)
        {
            Node<K,V>*n1 = this->operator[](j-1);
            Node<K,V>*n2 = this->operator[](j);
            if(n1&&n2)
            {
                if(n1->value>n2->value)
                {
                   this->swap(n1,n2);
                }
            }
        }
    }
}

#endif // LIST_H

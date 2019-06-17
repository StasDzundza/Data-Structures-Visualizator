#ifndef OSRBTREE_H
#define OSRBTREE_H

#include <utility>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <iostream>
#include "structurerepresentor.h"

using namespace std;

enum Color { black, red };

template<typename Key, typename T>
class OSTreeRB:public StructureRepresentor<Key,T>
{
private:
    struct Node
    {
        Node() :color{ black }, left{ nullptr }, right{ nullptr }, parent{ nullptr }, size{ 0 } {};
        pair<Key, T> value;
        Node* left;
        Node* right;
        Node* parent;
        Color color;
        unsigned int size;
    };

    Node* root;
    Node* null_node = new Node{};
    void LeftRotate(Node* x);
    void RightRotate(Node* x);
    void InsertFixup(Node* x);
    void DeleteFixup(Node *x);
    void DeleteNodeHelper(Node *z);
    Node* OS_SelectHelper(unsigned, Node*x);
    unsigned OS_RankHelper(Node* x);
    void WriteToGV(ofstream & fout, Node* x);
    void OS_Select(unsigned);
    void OS_Rank(Key key);
    Node* Find(Key value);
    bool isEmpty(){return root == null_node;}

public:

    OSTreeRB();

    void writeDotFile(const char* fileName)
    {
        ofstream fout(fileName);
        fout << "digraph {\n";
        WriteToGV(fout, root);
        fout << "}";
        fout.close();
    }
    void insert(Key key,T value);
    void remove(Key key);
    T find(Key value);
    void randomInsert()override;
    StructureRepresentor<Key,T>* Union( StructureRepresentor<Key,T>*s)override;
    StructureRepresentor<Key,T>* Intersection( StructureRepresentor<Key,T>*s)override;
    StructureRepresentor<Key,T>* SymDiff( StructureRepresentor<Key,T>*s)override;
    StructureRepresentor<Key,T>* Diff( StructureRepresentor<Key,T>*s)override;
    vector<pair<Key,T>> getKeys()override;
    void sort()override;
    void clear()override;


};

//конструктор
template<typename Key, typename T>
OSTreeRB<Key, T>::OSTreeRB()
{
    OSTreeRB::root = null_node;
}

template<typename Key, typename T>
void OSTreeRB<Key, T>::LeftRotate(Node* x)
{
    Node* y = x->right;

    x->right = y->left;
    if (y->left != null_node)y->left->parent = x;

    y->parent = x->parent;
    if (x->parent == null_node)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;


    y->left = x;//x->right->left = parent
    x->parent = y;//x's parent now right

    y->size = x->size;
    x->size = x->left->size + x->right->size + 1;
}

//правий поворот
template<typename Key, typename T>
void OSTreeRB<Key, T>::RightRotate(Node* x)
{
    Node* y = x->left;

    x->left = y->right;//x->left = x->left->right
    if (y->right != null_node)y->right->parent = x;//x->left->right parent now x

    y->parent = x->parent;//x->left's parent is now x's parent
    if (x->parent == null_node)
    {
        root = y;
    }
    else if (x == x->parent->right)
    {
        x->parent->right = y;
    }
    else
    {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;

    y->size = x->size;
    x->size = x->left->size + x->right->size + 1;
}

template<typename Key, typename T>
void OSTreeRB<Key, T>::InsertFixup(Node* x)
{
    while (x->parent->color == red)
    {
        if (x->parent == x->parent->parent->left)//if new element's parent to the left then uncle to the right
        {
            Node* y = x->parent->parent->right;//uncle to the right
            if (y->color == red)//2nd case (recolour parent, grandparent, and uncle)
            {
                x->parent->color = black;
                y->color = black;
                x->parent->parent->color = red;
                x = x->parent->parent;
            }
            else //if uncle is black
            {
                if (x == x->parent->right)//3rd case (rotate parent in the opposite direction of new elem)
                {
                    x = x->parent;
                    LeftRotate(x);
                }
                //4th case (rotate grandparent in the opposite direction of our elem, recolour parent and grandparent)
                x->parent->color = black;
                x->parent->parent->color = red;
                RightRotate(x->parent->parent);
            }
        }
        else//if new element's parent to the right then uncle to the left
        {
            Node* y = x->parent->parent->left;
            if (y->color == red)//2nd case (recolour parent, grandparent, and uncle)
            {
                x->parent->color = black;
                y->color = black;
                x->parent->parent->color = red;
                x = x->parent->parent;
            }
            else //if uncle is black
            {
                if (x == x->parent->left)//3rd case (rotate parent in the opposite direction of new elem)
                {
                    x = x->parent;
                    RightRotate(x);
                }
                //4th case (rotate grandparent in the opposite direction of our elem, recolour parent and grandparent)
                x->parent->color = black;
                x->parent->parent->color = red;
                LeftRotate(x->parent->parent);
            }
        }
    }
    root->color = black;//first case
}

template<typename Key, typename T>
void OSTreeRB<Key, T>::insert(Key key,T value)
{
    Node* current, * parent, * x;

    parent = null_node;
    current = root;
    while (current != null_node)
    {
        parent = current;
        current->size++;
        current = (key < current->value.first) ? current->left : current->right;
    }
    x = new Node;
    x->value.first = key;
    x->value.second = value;
    x->parent = parent;
    x->left = null_node;
    x->right = null_node;
    x->color = red;
    x->size = 1;

    if (parent == null_node)
    {
        root = x;
    }
    else if (key < parent->value.first)
    {
        parent->left = x;
    }
    else
    {
        parent->right = x;
    }

    InsertFixup(x);
}

const string colors[]{ "black","red" };

//function for graphviz
template<typename Key, typename T>
void OSTreeRB<Key, T>::WriteToGV(ofstream& fout, Node* p)
{
    if (p != null_node) {
        fout << p->value.second << "[shape=record,label=\" {" << p->value.second << "}\", color=\"" << colors[p->color] << "\"];\n";//сама структура
        fout << p->value.second << "->" << p->left->value.second << ";\n";
        fout << p->value.second << "->" << p->right->value.second << ";\n";

        if (p->right != null_node) {
            WriteToGV(fout, p->right);
        }
        if (p->right != null_node) cout << " /\n";
        cout << p->value.first;
        if (p->color == black) cout << " \'black\' ";
        else cout << " \'red\' ";
        cout << "size:" << p->size;
        cout << p->value.second;

        if (p->left != null_node) {
            cout << " \\\n";
            WriteToGV(fout, p->left);
        }
    }
}

//пошук за ключем
template<typename Key, typename T>
T OSTreeRB<Key, T>::find(Key value)
{
    Node* current = root;
    while (current != null_node)
    {
        if (value == current->value.first)
            return current->value.second;
        else
        {
            current = (value < current->value.first) ? current->left : current->right;
        }
    }
    return T();
}

//відновлення властивостей після видалення
template<typename Key, typename T>
void OSTreeRB<Key, T>::DeleteFixup(Node* x)
{
    if (x == nullptr)return;
    while (x != root && x->color == black)
    {
        if (x == x->parent->left)
        {
            Node* w = x->parent->right;//brother on the right
            if (w->color == red)//case (brother is red)
            {
                w->color = black;
                x->parent->color = red;
                LeftRotate(x->parent);
                w = x->parent->right;
            }
            if (w->left->color == black && w->right->color == black) //brother is black and both children are black
            {
                w->color = red;//make brother red
                x = x->parent;//continue with father if black
            }
            else
            {
                if (w->right->color == black) //case black brother on the right and red child on the left
                {
                    w->left->color = black;
                    w->color = red;
                    RightRotate(w);
                    w = x->parent->right;
                }
                //continue with case black brother on the right and red child on the right
                w->color = x->parent->color;
                x->parent->color = black;
                w->right->color = black;
                LeftRotate(x->parent);
                x = root;
            }
        }
        else
        {
            Node* w = x->parent->left;//brother on the left
            if (w->color == red) //case (brother is red)
            {
                w->color = black;
                x->parent->color = red;
                RightRotate(x->parent);
                w = x->parent->left;
            }
            if (w->right->color == black && w->left->color == black) //brother is black and both children are black
            {
                w->color = red;//make brother red
                x = x->parent;//continue with father
            }
            else
            {
                if (w->left->color == black) //case black brother on the left and red child on the right
                {
                    w->right->color = black;
                    w->color = red;
                    LeftRotate(w);
                    w = x->parent->left;
                }
                //continue with case black brother on the left and red child on the left
                w->color = x->parent->color;
                x->parent->color = black;
                w->left->color = black;
                RightRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = black;
}

//видалення вузла за ключем
template<typename Key, typename T>
void OSTreeRB<Key, T>::remove(Key key)
{
    Node* x = Find(key);
    DeleteNodeHelper(x);
}

//допоміжна функція для видалння
template<typename Key, typename T>
void OSTreeRB<Key, T>::DeleteNodeHelper(Node* z)
{
    if (!z) return;
    Node* temp = z;
    while ((temp != root || temp == root) && temp != null_node)
    {
        temp->size--;
        temp = temp->parent;
    }

    Node* x, * y;
    if (!z || z == null_node) return;
    if (z->left == null_node || z->right == null_node) {
        /* y has a NIL node as a child */
        y = z;
    }
    else {
        /* find tree successor with a NIL node as a child */
        y = z->right;
        y->size--;
        while (y->left != null_node) y = y->left, y->size--;
    }
    /* x is y's only child */
    if (y->left != null_node)
        x = y->left;
    else
        x = y->right;
    /* remove y from the parent chain */
    x->parent = y->parent;
    if (y->parent)
        if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
    else
        root = x;
    if (y != z) z->value = y->value;
    if (y->color == black)
        DeleteFixup(x);
    free(y);
}

//пошук елемента з заданим рангом і
template<typename Key, typename T>
void OSTreeRB<Key, T>::OS_Select(unsigned i)
{
    try
    {
        cout << OS_SelectHelper(i, root)->value.first << endl;
    }
    catch (string error)
    {
        error += to_string(i);
        cout << error << endl;
    }
}

//допоміжна функція для пошуку елемента з заданим рангом і в піддереві з коренем x
template<typename Key, typename T>
typename OSTreeRB<Key, T>::Node* OSTreeRB<Key, T>::OS_SelectHelper(unsigned i, Node* x)
{
    if (x == null_node)throw string("There is no element with such rank: ");
    unsigned r;
    if (x->left != null_node)
        r = x->left->size + 1;
    else r = 1;
    if (i == r)return x;
    else if (i < r)
        return OS_SelectHelper(i, x->left);
    else return OS_SelectHelper(i - r, x->right);
}

//пошук рангу елемента key
template<typename Key, typename T>
void OSTreeRB<Key, T>::OS_Rank(Key key)
{
    try
    {
        Node* x = Find(key);
        cout << OS_RankHelper(x) << endl;
    }
    catch (string error)
    {
        error += key;
        cout << error << endl;
    }
}

template<typename Key, typename T>
typename OSTreeRB<Key, T>::Node* OSTreeRB<Key,T>::Find(Key value)
{
    Node* current = root;
    while (current != null_node)
    {
        if (value == current->value.first)
            return current;
        else
        {
            current = (value < current->value.first) ? current->left : current->right;
        }
    }
    return nullptr;
}

//допоміжна функція пошуку рангу елемента
template<typename Key, typename T>
unsigned OSTreeRB<Key, T>::OS_RankHelper(Node* x)
{
    if (x == nullptr)throw string("There is no element with such key: ");
    unsigned r;
    if (x->left != null_node)
    {
        r = x->left->size + 1;
    }
    else r = 1;
    Node* y = x;
    while (y != root)
    {
        if (y == y->parent->right)
        {
            if (y->parent->left)
            {
                r = r + y->parent->left->size + 1;
            }
            else r = r + 1;
        }
        y = y->parent;
    }
    return r;
}

template<typename Key, typename T>
StructureRepresentor<Key,T> *OSTreeRB<Key,T>::Union( StructureRepresentor<Key,T> *s)
{
    vector<pair<Key,T>>p1 = this->getKeys();
    vector<pair<Key,T>>p2 = s->getKeys();
    StructureRepresentor<Key,T>*sr = new OSTreeRB<Key,T>;
    for(pair<Key,T>p:p1)
    {
        sr->insert(p.first,p.second);
    }
    for(pair<Key,T>p:p2)
    {
        sr->insert(p.first,p.second);
    }
    return sr;
}

template<typename Key, typename T>
StructureRepresentor<Key,T> *OSTreeRB<Key,T>::Intersection( StructureRepresentor<Key,T> *s)
{
    vector<pair<Key,T>>p1 = this->getKeys();
    vector<pair<Key,T>>p2 = s->getKeys();
    StructureRepresentor<Key,T>*I = new OSTreeRB<Key,T>;
    for(pair<Key,T>p:p1)
    {
        auto element = std::find_if(p2.begin(),p2.end(),[p](const pair<int,int>&pair){return pair.second == p.second;});
        if(element !=p2.end())
        {
            I->insert(element->first,element->second);
        }
    }
    return I;
}

template<typename Key, typename T>
StructureRepresentor<Key,T> *OSTreeRB<Key,T>::SymDiff( StructureRepresentor<Key,T> *s)
{

}

template<typename Key, typename T>
StructureRepresentor<Key,T> *OSTreeRB<Key,T>::Diff( StructureRepresentor<Key,T> *s)
{

}

template<typename Key, typename T>
vector<pair<Key,T>> OSTreeRB<Key,T>::getKeys()
{
    vector<pair<Key,T>>key_val;
    if(this->isEmpty())
        return key_val;

    stack<Node *> s;
    s.push(this->root);
    while (!s.empty())
    {
        Node *temp = s.top();
        s.pop();
        if (temp->left != nullptr)
            s.push(temp->left);

        if (temp->right != nullptr)
            s.push(temp->right);
        key_val.emplace_back(temp->value.first,temp->value.second);
    }
    return key_val;
}

template<typename Key, typename T>
void OSTreeRB<Key,T>::sort()
{

}

template<typename Key, typename T>
void OSTreeRB<Key,T>::clear()
{

}

template<typename Key, typename T>
void OSTreeRB<Key,T>::randomInsert()
{

}


#endif // OSRBTREE_H

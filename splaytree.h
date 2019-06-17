#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#include<fstream>
#include<string>
#include<utility>
#include "structurerepresentor.h"

using std::pair;
using std::string;
using std::ofstream;
template<typename T, typename _Val>
struct SplayNode
{
    T key;
    _Val value;
    SplayNode *left, *right;
    SplayNode(const T &key, const _Val& value)
    {
        this->key = key;
        this->value = value;
        left = right = nullptr;
    }
    SplayNode(const pair<T,_Val> &value) : SplayNode(value.first, value.second)
    {}
};

template<typename T, typename _Val>
class Splay_Tree : public StructureRepresentor<T,_Val>
{
    using Node = SplayNode<T,_Val>;
private:

    bool isEmpty(){return tree == nullptr; }
    void bst_print_dot_aux(Node* node, ofstream& stream);

    Node *rightRotate(Node *y);
    Node *leftRotate(Node *x);

    Node *splay(Node *root, const T &key);

    Node *search(Node *root, const T &key);
    Node *insert(Node *root, const pair<T, _Val> &value);
    Node* delete_key(Node *root, const T &key);
    void* fillKeys(vector<pair<T,_Val>> &key_vals,Node*cur);


    void print_tree(Node* root, int shift);
    void freeMemory(Node * root);
    Node* tree;
public:
    Splay_Tree();
    ~Splay_Tree();

    //bool isEmpty() override{return tree == nullptr; }
    void insert( T key,  _Val value) override;
    void remove( T key) override;
    void clear() override;
    _Val find(T key) override;
    void randomInsert()override;
    void writeDotFile(const char *fileName) override;
    StructureRepresentor<T,_Val>* Union( StructureRepresentor<T,_Val>*s)override;
    StructureRepresentor<T,_Val>* Intersection( StructureRepresentor<T,_Val>*s)override;
    StructureRepresentor<T,_Val>* SymDiff( StructureRepresentor<T,_Val>*s)override;
    StructureRepresentor<T,_Val>* Diff( StructureRepresentor<T,_Val>*s)override;
    vector<pair<T,_Val>> getKeys()override;
    void sort()override;
};

#include "splaytree.h"

//template class Splay_Tree<int,int>;

template<typename T,class _Val>
void Splay_Tree<T,_Val>::bst_print_dot_aux(Node * node, ofstream & fout)
{
    if(!node){
        return;
    }
    fout << "      " << (quintptr)node;
    fout << "[label=\"";
    fout << "{key: " << node->key << "|val:" << node->value << "}";
    fout << "\"];" << std::endl;

    if(node->left != nullptr){
        fout << (quintptr)node << "->" << (quintptr)node->left << ";\n";
        bst_print_dot_aux(node->left, fout);
    }
    if(node->right != nullptr){
        fout << (quintptr)node << "->" << (quintptr)node->right << ";\n";
        bst_print_dot_aux(node->right, fout);
    }
}
// A utility function to right rotate subtree rooted with y
//				y                                     x
//             / \     Zig (Right Rotation)          /  \
//            x   T3   – - – - – - – - - ->         T1   y
//           / \       < - - - - - - - - -              / \
//          T1  T2     Zag (Left Rotation)            T2   T3
template<class T, class _Val>
typename Splay_Tree<T, _Val>::Node* Splay_Tree<T, _Val>::rightRotate(Node *y)
{
    Node *x = y->left;
    y->left = x->right;
    x->right = y;
    return x;
}

// A utility function to left rotate subtree rooted with x
//				y                                     x
//             / \     Zig (Right Rotation)          /  \
//            x   T3   – - – - – - – - - ->         T1   y
//           / \       < - - - - - - - - -              / \
//          T1  T2     Zag (Left Rotation)            T2   T3
template<class T,class _Val>
typename Splay_Tree<T,_Val>::Node* Splay_Tree<T,_Val>::leftRotate(Node *x)
{
    Node *y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

// This function brings the key at root if key is present in tree.
// If key is not present, then it brings the last accessed item at
// root.  This function modifies the tree and returns the new root
template<class T,class _Val>
typename Splay_Tree<T,_Val>::Node* Splay_Tree<T,_Val>::splay(Node *root, const T &key)
{
    // Base cases: root is NULL or key is present at root
    if (root == nullptr || root->key == key)
        return root;

    // Key lies in left subtree
    if (root->key > key)
    {
        // Key is not in tree, we are done
        if (root->left == nullptr) return root;

        // Zig-Zig (Left Left)
        if (root->left->key > key)
        {
            // First recursively bring the key as root of left-left
            root->left->left = splay(root->left->left, key);

            // Do first rotation for root, second rotation is done after else
            root = rightRotate(root);
        }
        else if (root->left->key < key) // Zag-Zig (Left Right)
        {
            // First recursively bring the key as root of left-right
            root->left->right = splay(root->left->right, key);

            // Do first rotation for root->left
            if (root->left->right != nullptr)
                root->left = leftRotate(root->left);
        }

        // Do second rotation for root
        return (root->left == nullptr) ? root : rightRotate(root);
    }
    else // Key lies in right subtree
    {
        // Key is not in tree, we are done
        if (root->right == nullptr) return root;

        // Zig-Zag (Right Left)
        if (root->right->key > key)
        {
            // Bring the key as root of right-left
            root->right->left = splay(root->right->left, key);

            // Do first rotation for root->right
            if (root->right->left != nullptr)
                root->right = rightRotate(root->right);
        }
        else if (root->right->key < key)// Zag-Zag (Right Right)
        {
            // Bring the key as root of right-right and do first rotation
            root->right->right = splay(root->right->right, key);
            root = leftRotate(root);
        }

        // Do second rotation for root
        return (root->right == nullptr) ? root : leftRotate(root);
    }
}

// The search function for Splay tree.  Note that this function
// returns the new root of Splay Tree.  If key is present in tree
// then, it is moved to root.
template<class T,class _Val>
typename Splay_Tree<T,_Val>::Node* Splay_Tree<T,_Val>::search(Node *root, const T &key)
{
    return splay(root, key);
}

// Function to insert a new key k in splay tree with given root
template<class T, class _Val>
typename Splay_Tree<T,_Val>::Node* Splay_Tree<T,_Val>::insert(Node *root, const pair<T,_Val> &k)
{

    // Simple Case: If tree is empty
    if (root == nullptr) return new Node(k);

    // Bring the closest leaf node to root
    root = splay(root, k.first);

    // If key is already present, then return
    if (root->key == k.first) return root;

    // Otherwise allocate memory for new node
    Node *newnode = new Node(k);

    // If root's key is greater, make root as right child
    // of newnode and copy the left child of root to newnode
    if (root->key > k.first)
    {
        newnode->right = root;
        newnode->left = root->left;
        root->left = nullptr;
    }

    // If root's key is smaller, make root as left child
    // of newnode and copy the right child of root to newnode
    //left child of root is smaller that key, otherwise left child would stay in root
    else
    {
        newnode->left = root;
        newnode->right = root->right;
        root->right = NULL;
    }

    return newnode; // newnode becomes new root
}

// The delete function for Splay tree. Note that this function
// returns the new root of Splay Tree after removing the key
template<class T, class _Val>
typename Splay_Tree<T, _Val>::Node* Splay_Tree<T, _Val>::delete_key(Node *root, const T &key)
{
    if (!root)
        return nullptr;

    // Splay the given key
    root = splay(root, key);

    // If key is not present, then
    // return root
    if (key != root->key)
        return root;

    // If key is present
    // If left child of root does not exist
    // make root->right as root
    Node *temp;
    if (!root->left)
    {
        temp = root;
        root = root->right;
    }

    // Else if left child exits
    else
    {
        temp = root;

        /*Note: Since key == root->key,
        so after Splay(root->left_child, key),
        the tree we get will have no right child tree
        and maximum node in left subtree will get splayed*/
        // New root
        root = splay(root->left, key);

        // Make right child of previous root  as
        // new root's right child
        root->right = temp->right;
    }

    // free the previous root node, that is,
    // the node containing the key
    delete temp;

    // return root of the new Splay Tree
    return root;
}

template<typename T, typename _Val> void Splay_Tree<T, _Val>::freeMemory(Node * root)
{
    if (!root)
        return;

    freeMemory(root->left);
    freeMemory(root->right);

    delete root;
}

template<typename T, typename _Val>
Splay_Tree<T,_Val>::Splay_Tree() : tree(nullptr)
{
    StructureRepresentor<T,_Val>::type = StructureRepresentor<T,_Val>::Type::SplayTree;
}


template<typename T, typename _Val> Splay_Tree<T,_Val>:: ~Splay_Tree()
{
    freeMemory(tree);
}

template<typename T, typename _Val> _Val Splay_Tree<T, _Val>::find(T key)
{
    tree = search(tree, key);
    if(tree->key == key)
        return tree->value;
    else {
        return _Val();
    }
}

template<typename T, typename _Val>
void Splay_Tree<T, _Val>::randomInsert()
{

}
template<typename T, typename _Val> void Splay_Tree<T, _Val>::insert( T key, _Val value)
{
    tree = insert(tree, std::make_pair(key,value));
}
template<typename T, typename _Val> void Splay_Tree<T, _Val>::remove( T key)
{
    tree = delete_key(tree, key);
}

template<typename T, typename _Val>
void Splay_Tree<T,_Val>::clear()
{
    freeMemory(tree);
    tree = nullptr;
}

template<typename T, typename _Val>
void Splay_Tree<T,_Val>::writeDotFile(const char * path)
{
    ofstream fout(path);

    fout << "digraph BST {\n";
    fout << "    node [fontname=\"Arial\"\n    fontsize = \"16\"\n    shape = \"record\"];\n";
    if(!this->isEmpty()){
        bst_print_dot_aux(tree, fout);
    }
    fout << "}\n";
    fout.close();
}

template<typename T, typename _Val>
StructureRepresentor<T,_Val> *Splay_Tree<T,_Val>::Union( StructureRepresentor<T,_Val> *s)
{
    vector<pair<T,_Val>>p1 = this->getKeys();
    vector<pair<T,_Val>>p2 = s->getKeys();
    StructureRepresentor<T,_Val>*sr = new Splay_Tree<T,_Val>;
    for(pair<T,_Val>p:p1)
    {
        sr->insert(p.first,p.second);
    }
    for(pair<T,_Val>p:p2)
    {
        sr->insert(p.first,p.second);
    }
    return sr;
}

template<typename T, typename _Val>
StructureRepresentor<T,_Val> *Splay_Tree<T,_Val>::Intersection( StructureRepresentor<T,_Val> *s)
{
    vector<pair<T,_Val>>p1 = this->getKeys();
    vector<pair<T,_Val>>p2 = s->getKeys();
    StructureRepresentor<T,_Val>*I = new Splay_Tree<T,_Val>;
    for(pair<T,_Val>p:p1)
    {
        auto element = std::find_if(p2.begin(),p2.end(),[p](const pair<int,int>&pair){return pair.second == p.second;});
        if(element !=p2.end())
        {
            I->insert(element->first,element->second);
        }
    }
    return I;
}

template<typename T, typename _Val>
StructureRepresentor<T,_Val> *Splay_Tree<T,_Val>::SymDiff( StructureRepresentor<T,_Val> *s)
{
    StructureRepresentor<T,_Val> *inters = this->Intersection(s);
    StructureRepresentor<T,_Val> *diff1 = this->Diff(inters);
    StructureRepresentor<T,_Val> *diff2 = s->Diff(inters);
    StructureRepresentor<T,_Val> *res = diff1->Union(diff2);
    return res;
}

template<typename T, typename _Val>
StructureRepresentor<T,_Val> *Splay_Tree<T,_Val>::Diff( StructureRepresentor<T,_Val> *s)
{
    vector<pair<T,_Val>>p1 = this->getKeys();
    vector<pair<T,_Val>>p2 = s->getKeys();
    StructureRepresentor<T,_Val>*D = new Splay_Tree<T,_Val>;
    for(pair<T,_Val>p:p1)
    {
        auto element = std::find_if(p2.begin(),p2.end(),[p](const pair<int,int>&pair){return pair.second == p.second;});
        if(element == p2.end())
        {
            D->insert(p.first,p.second);
        }
    }
    return D;
}

template<typename T, typename _Val>
vector<pair<T,_Val>> Splay_Tree<T,_Val>::getKeys()
{
    vector<pair<T,_Val>>key_val;
    if(this->isEmpty())
        return key_val;

    stack<Node *> s;
    s.push(this->tree);
    while (!s.empty())
    {
        Node *temp = s.top();
        s.pop();
        if (temp->left != nullptr)
            s.push(temp->left);

        if (temp->right != nullptr)
            s.push(temp->right);
        key_val.emplace_back(temp->key,temp->value);
    }
    return key_val;
}

template<typename T, typename _Val>
void Splay_Tree<T,_Val>::sort()
{

}

#endif // SPLAYTREE_H

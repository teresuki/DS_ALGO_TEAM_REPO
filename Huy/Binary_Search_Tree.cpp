// Binary Search Tree -- just write all in one for easy checking first
/* Regardless of how hard the problem is, just focus on working and not distract, you can solve it */

/* Name: Truong Quang Huy
   ID: 18602
   Class: CS2019 - VGU
*/

#include <iostream>
using namespace std;

struct Node
{
    int key;
    Node* left_child;
    Node* right_child;
    Node* parent;
};

/* wrong way to write node-deleting function,
   the problem here is that  I dont know */
void delete_old_nodes(Node*& x)
{
    if(x->left_child != nullptr)
        delete_old_nodes(x->left_child);

    if(x->right_child != nullptr)
        delete_old_nodes(x->right_child);

    delete x;
    x = nullptr;
}

// 2nd way to free the memory of a tree
void post_order_traversal_delete(Node* x)
{
    if(x != nullptr)
    {
        post_order_traversal_delete(x->left_child);
        post_order_traversal_delete(x->right_child);
        delete x;
    }
}

// in-order traversal => print the tree in sorted order
void in_order_traversal(Node* x)
{
    if (x != nullptr)
    {
        in_order_traversal(x->left_child);
        cout << x->key << " ";
        in_order_traversal(x->right_child);
    }
}



// Search for a key k at node x
// want to search entire tree => go from the root
/* recursive search */
Node* tree_search_1(Node* x, int k)
{
    if(x == nullptr || x->key == k)
        return x;

    if(k < x->key)
        return tree_search_1(x->left_child, k);
    else
        return tree_search_1(x->right_child, k);
}

/* iterative search */
Node* tree_search_2(Node* x, int k)
{
    while(x != nullptr && x->key != k)
    {
        if(k < x->key)
            x = x->left_child;
        else
            x = x->right_child;
    }

    return x;   // return an pointer to a node contain k or NULL
}

// Tree minimum
Node* tree_minimum(Node* x)
{
    while(x->left_child != nullptr)
        x = x->left_child;

    return x;   /* go to the left most node */
}

// Tree maximum
Node* tree_maximum(Node* x)
{
    while(x->right_child != nullptr)
        x = x->right_child;

    return x;               /* go to the right most node */
}

// Tree successor, the algorithm of Prof.Toulose is right, it is the in-order successor
Node* tree_successor(Node* x)
{
    if(x->right_child != nullptr)   /* x has a right sub-tree */
        return tree_minimum(x->right_child);

    Node* y = x->parent;            /* go left-up, find smaller node, go right-up, find bigger node */
                                    /* here, we are finding the in-order successor, go left-up until right-up */
    while(y != nullptr && x == y->right_child)  // still go left-up until root
    {
        x = y;
        y = y->parent;
    }

    return y;   // return NULL if the node x is the right-most node that has no in-order successor
}

// Create a new node
Node* new_node(int k)
{
    Node* temp = new Node;

    temp->key = k;
    temp->left_child = temp->right_child = temp->parent = nullptr;

    return temp;
}

/* Insert a node */
void insert_node(Node*& root, Node* z)   // z is new node created by new_node() function
{
    /* the true meaning of double pointer: when you pass a pointer into a function, you just pass a copy of value
    of pointer, when the function terminated, the copy value will be free out of memory then if you want to change
    the pointer's value (not value at the address of location that pointer points to), you need to pass it as a
    double pointer (create a double pointer point to the pointer that you want to change in the function
    and retain its value afterward */
    /* C++ support a better way: that is reference to pointer Node*& root => easier to use */

    Node * y = nullptr;
    Node * x = root;
    // Node * temp = &root;

    while(x != nullptr)
    {
        y = x;
        if(z->key <= x->key)    /* not distinct */
            x = x->left_child;
        else
            x = x->right_child;
    }

    z->parent = y;
    if (root == nullptr)
    {
        root = z;

    }
    else if(z->key <= y->key)   /* not distinct */
        y->left_child = z;
    else
        y->right_child =z;
}

/* Insert a node -- function overloading */
void insert_node(Node*& root, int k)   // z is new node created by new_node() function
{
    Node* z = new_node(k);
    Node* y = nullptr;
    Node* x = root;

    while(x != nullptr)
    {
        y = x;
        if(z->key < x->key)    /* must be distinct */
            x = x->left_child;
        else
            x = x->right_child;
    }
    z->parent = y;

    if (y == nullptr)
    {
        root = z;
    }
    else if(z->key < y->key)   /* must be distinct */
        y->left_child = z;
    else
        y->right_child =z;
}

// transplant(T,u, v), replace the subtree rooted at u by
// the subtree rooted at v
void transplant(Node*& root, Node* u, Node* v)
{

    if(u->parent == nullptr)     // u is the root of the tree
        root = v;
    else if(u == u->parent->left_child)
        u->parent->left_child = v;
    else
        u->parent->right_child = v; /* need delete old sub-tree at u here ? */

    if(v != nullptr) // ? no need, but null pointer mean nothing so maybe needed
        v->parent = u->parent;
}

// Tree-Delete: 4 cases
void delete_1_node(Node*& root, Node* z)
{
    if(z->left_child == nullptr)            // case 1: z has no left child
        transplant(root, z, z->right_child);
    else if(z->right_child == nullptr)     // case 2: z has no right child
        transplant(root, z, z->left_child);
    else    // z has 2 children
    {
        Node* y = tree_minimum(z->right_child);

        if(y->parent != z)                  // case 4: successor of z is not its child
        {
            transplant(root, y, y->right_child);    // replace y by its right child
            y->right_child = z->right_child;        /* connect right child of z to y              */
            y->right_child->parent = y;             /* turn z's right child in to y's right child */
        }
        transplant(root, z, y);             // case 3: successor of z is its child
        y->left_child = z->left_child;      /* tricky here, turn z->left_child into y->left_child */
        y->left_child->parent = y;          /* , need both lines of code                          */
    }
}

void BST_sort(int arr[], int arr_size, Node*& root)
{
    for(int i = 0; i < arr_size; i++)
        insert_node(root, arr[i]);

    // in_order_traversal(root);
}

void tree_print(Node* x, const string prefix = "", bool is_left = false)
{
    if(x->parent != nullptr)
        cout << prefix << (is_left ? "L--" : "R--");
    else
        cout << "--";   // for the root case

    cout << x->key <<endl;

    if(x->left_child != nullptr)
        tree_print(x->left_child, prefix+(is_left ? "|   " : "    "),true);

    if(x->right_child != nullptr)
        tree_print(x->right_child, prefix+(is_left ? "|   " : "    "),false);
}

int main(void)
{
    Node* x = nullptr;
    // the problem is, if x = nullptr => always reset after each function
    // if not null ptr => already value => 1 node of garbage

    int arr[] = {2, 1, 3, 4, 5, 0, 9, 7, 8, 6};
    int arr_size = sizeof(arr) / sizeof(arr[0]);

    cout << "The original tree from the array: " << endl;
    BST_sort(arr, arr_size, x);
    tree_print(x);
    cout << "Sorted by in-order traversal: " << endl;
    in_order_traversal(x);
    cout << endl << endl << endl;

    cout << "Delete node with the key 3 from the tree: " << endl;
    Node* z = tree_search_2(x, 3);
    delete_1_node(x, z);
    tree_print(x);
    cout << "Sorted by in-order traversal: " << endl;
    in_order_traversal(x);
    cout << endl;


    delete_old_nodes(x);

    return 0;
}

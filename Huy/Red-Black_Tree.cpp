// Red-Black Tree -- a self-balancing search-tree that guarantees
// every basic dynamic-set operation take O(lg n) time in the worst case
/* Note: for Query operation: Search, Min/Max, Successor/Predecessor => passed by value
         for Modifying operation: Insert, Delete, Left/Right-Rotate  => passed by reference/double pointer
*/
/* Name: Truong Quang Huy
   ID: 18602
   Class: CS2019 - VGU
*/

#include <iostream>
using namespace std;

struct Node
{
    int key;
    char color;
    Node *p, *left, *right;
};


/* in-order tree walk */
void in_order_traversal(Node* x)
{
    if(x != nullptr)
    {
        in_order_traversal(x->left);
        cout << x->key << endl;
        in_order_traversal(x->right);
    }
}


/* recursive search -- still O(lg n) */
Node* tree_search(Node* x, int k)
{
    if(x == nullptr || x->key ==k)
        return x;

    if(k < x->key)
        return tree_search(x->left, k);
    else
        return tree_search(x->right, k);
}


/* MINIMUM(x) -- return a pointer to the minimum element in the subtree rooted at x */
Node* tree_minimum(Node *x)     // no need to pass by ref here because it's a query function
{
    while(x->left != nullptr)
        x = x->left;

    return x;
}


/* MAXIMUM(x) -- return a pointer to the maximum element in the subtree rooted at x */
Node* tree_maximum(Node *x)
{
    while(x->right!= nullptr)
        x = x->right;

    return x;
}


/* SUCESSOR(x) -- return a pointer to the next element of x in in-order tree walk */
Node* tree_successor(Node* x)
{
    if(x->right != nullptr)
        return tree_minimum(x->right);

    Node* y = x->p;
    while(y != nullptr && x == y->right)
    {
        x = y;
        y = y->p;
    }

    return y;
}


/* PREDECESSOR(x) -- return a pointer to the previous element of x in in-order tree walk */
Node* tree_predecessor(Node* x)
{
    if(x->left != nullptr)
        return tree_maximum(x->left);

    Node* y = x->p;
    while(y != nullptr && x == y->left)
    {
        x = y;
        y = y->p;
    }

    return y;
}


/* new_node(k) -- create a new node with the key value k and the satellite data = ? */
Node* new_node(int k)
{
    Node* temp = new Node;

    temp->key = k;
    temp->left = temp->right = temp->p = nullptr;

    return temp;
}

void left_rotate(Node*& root, Node* x)      // need to pass by reference
{
    Node* y = x->right;     // set y, must assume that y != nullptr ? or must use T.Nil sentinel ?

    x->right = y->left;
    if(y->left != nullptr)
        y->left->p = x;

    y->p = x->p;    // link x's parent to y
    if(x->p == nullptr)
        root = y;
    else if(x == x->p->left)
        x->p->left = y;
    else
        x->p->right = y;

    y->left = x;
    x->p = y;
}

void right_rotate(Node*& root, Node* y)
{
    Node* x = y->left;

    y->left = x->right;     // turn x's right subtree into y's left subtree
    if(x->right != nullptr)
        x->right->p = y;

    x->p = y->p;    // link y's parent to x
    if(y->p == nullptr)
        root = x;
    else if(y == y->p->left)
        y->p->left = x;
    else
        y->p->right = x;

    x->right = y;
    y->p = x;
}


void RB_insert_Fixup(Node*& root, Node*& z)
{
    while((z != root) && (z->color != 'B') && (z->p->color == 'R'))
    {
        if(z->p == z->p->p->left)
        {
            Node* y = z->p->p->right;
            if((y != nullptr) && y->color == 'R')
            {
                z->p->color = 'B';
                y->color = 'B';
                z->p->p->color = 'R';
                z = z->p->p;
            }
            else
            {
                if(z == z->p->right)
                {
                    z = z->p;
                    left_rotate(root, z);
                }
                z->p->color = 'B';
                z->p->p->color = 'R';
                right_rotate(root, z->p->p);
            }
        }
        else
        {
            Node* y = z->p->p->left;
            if((y != nullptr) && y->color == 'R')
            {
                z->p->color = 'B';
                y->color = 'B';
                z->p->p->color = 'R';
                z = z->p->p;
            }
            else
            {
                if(z == z->p->left)
                {
                    z = z->p;
                    right_rotate(root, z);
                }
                z->p->color = 'B';
                z->p->p->color = 'R';
                left_rotate(root, z->p->p);
            }
        }
    }

    root->color = 'B';
}


/* RB-INSERT(T, z) -- insert node z, whose key is assumed to have already been filled in
   by new_node(k) function into the red-black tree T (represented by its root)*/
void RB_insert(Node*& root, Node*& z)   // needed and should pass by ref to pointer here
{
     Node* y = nullptr;
     Node* x = root;

     while(x != nullptr)
     {
         y = x;     // trailing pointer
         if(z->key < x->key)
            x = x->left;
         else
            x = x->right;
     }

     z->p = y;
     if(y == nullptr)
        root = z;
     else if(z->key < y->key)
        y->left = z;
     else
        y->right = z;

     z->color = 'R';

     RB_insert_Fixup(root, z);
}

void RB_insert(Node*& root, int k)
{
    Node* z = new_node(k);

    RB_insert(root, z);
}

void tree_print(Node* x, const string prefix = "", bool is_left = false)
{
    if(x->p != nullptr)
        cout << prefix << (is_left ? "L--" : "R--");
    else
        cout << "--";   // for the root case

    cout << x->key << '(' << x->color << ')' << endl;

    if(x->left != nullptr)
        tree_print(x->left, prefix+(is_left ? "|   " : "    "),true);

    if(x->right != nullptr)
        tree_print(x->right, prefix+(is_left ? "|   " : "    "),false);
}


// free memory of tree
void post_order_delete(Node* x)
{
    if(x != nullptr)
    {
        post_order_delete(x->left);
        post_order_delete(x->right);
        delete x;
    }
}


// Driver code
int main(void)
{
    int arr[] = {11, 1, 2, 7, 5, 8, 14, 15};
    int arr_size = sizeof arr / sizeof arr[0];
    Node* root = nullptr;

    for(int i = 0; i < arr_size; i++)
    {
        Node* temp = new_node(arr[i]);
        RB_insert(root, temp);
    }

    tree_print(root);
    in_order_traversal(root);
	
	post_order_delete(root);
	
    return 0;
}

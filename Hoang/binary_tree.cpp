/*
 * Binary Search Tree
 * 
 * 1st July
 * Teresuki
*/

#include <iostream>
#include <vector>
using namespace std;

struct Node
{
    int key;
    Node* left;
    Node* right;
    Node* parent;

    Node(int key)
    {
        this->key = key;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }

    bool leftChild()
    {
        if(left != nullptr){
            return true;
        }
        else return false;
    }

    bool rightChild()
    {
        if(right != nullptr){
            return true;
        }
        else return false;
    }
};

struct BinaryTree
{
    Node* root;

    BinaryTree()
    {
        root = nullptr;
    }

    Node* minNode(Node* node)
    {
        Node* temp = node;
        while(temp->leftChild())
         temp = temp->left;
        return temp;
    }
    Node* maxNode(Node* node)
    {
        Node* temp = node;
        while(temp->rightChild())
         temp = temp->right;
        return temp;
    }

    void insert(Node* node, Node* rootR)
    {
        //There is no root node yet.
        if(root == nullptr)
         root = node;
        else
        {
            if(node->key <= rootR->key)
            {
                if(rootR->leftChild())
                 insert(node, rootR->left);
                else
                 rootR->left = node;
            }

            else if(node->key > rootR->key)
            {
                if(rootR->rightChild())
                 insert(node, rootR->right);
                else
                 rootR->right = node;
            }
        }
     
    }

    //node should be root as the first parameter
    //Encounter is used if you want to delete a node with duplicated key in the tree
    void deleteNode(Node* node, int key, Node* parent = nullptr, int encounter = 1)
    {
        static int enc = 0;

        if(key == node->key)
        {
            enc++;
            if(enc < encounter) goto here;
            //From Left, From Right
            bool fLeft = false, fRight = false;
            if(node == parent->left) fLeft = true;
            if(node == parent->right) fRight = true;

            if(fLeft)
            {
                //No children
                if(node->leftChild() == 0 && node->rightChild() == 0)
                {
                    parent->left = nullptr;
                }
                //Left Child
                else if(node->leftChild() == 1 && node->rightChild() == 0)
                {
                    parent->left = node->left;
                }
                //Right child
                else if(node->leftChild() == 0 && node->rightChild() == 1)
                {
                    parent->left = node->right;
                }
                //Has two children
                else if(node->leftChild() == 1 && node->rightChild() == 1)
                {
                    Node* temp = new Node(0); // 0 as temporary key
                    Node* successor = new Node(0);
                    successor = minNode(node->right);

                    deleteNode(node->right, successor->key, node);
                    node->key = successor->key;
                    return ;
                }
            }
            
            //Pretty much identical to fLeft
            else if(fRight)
            {
                //No children
                if(node->leftChild() == 0 && node->rightChild() == 0)
                {
                    parent->right = nullptr;
                }
                //Left Child
                else if(node->leftChild() == 1 && node->rightChild() == 0)
                {
                    parent->right = node->left;
                }
                //Right child
                else if(node->leftChild() == 0 && node->rightChild() == 1)
                {
                    parent->left = node->right;
                }
                //Has two children
                else if(node->leftChild() == 1 && node->rightChild() == 1)
                {
                    Node* successor = new Node(0);
                    successor = minNode(node->right);

                    deleteNode(node->right, successor->key, node);
                    node->key = successor->key;
                    return ;
                }
            }

        }
        here:
        if(key != node->key || enc < encounter)
        {
            parent = node;
            if(key <= node->key)
            {
                deleteNode(node->left, key, parent);
            }
            else if(key > node->key)
            {
                deleteNode(node->right, key, parent);
            }
        }

    }

    void inorder(Node* root)
    {
        if(root->leftChild()){
            inorder(root->left);
        }

        cout << root->key  << " ";

        if(root->rightChild()){
            inorder(root->right);
        }
    }

   void printTree2D(Node* node, int space)
   {
       if (node == NULL)
        return ;
       space += 2;

       printTree2D(node->right, space);
       cout << endl;
       for(int i = 1; i < space; ++i)
        cout << "   ";
       cout << node->key << endl;

       printTree2D(node->left, space);
   }
};

int main()
{
    BinaryTree bt;
    vector<Node*> nodes;

    vector<int> keys = {8, 4, 2, 6, 5, 7, 10, 9, 15, 12, 20};
    for(int i = 0; i < keys.size(); ++i)
    {
        Node* node = new Node(keys[i]);
        nodes.push_back(node);
        bt.insert(nodes[i], bt.root);
    }

    bt.printTree2D(bt.root, 2);
    cout << "Inorder Traversal:";
    bt.inorder(bt.root); cout << endl;

    
    //If you want to delete a number whose key
    //appears multiple times in the tree,
    //Add parameter: bt.root, occurence_count
    //Eg: Delete node with key = 5 that appears the second time: 
    //  bt.deleteNode (bt.root, 5, bt.root, 2);
    int delete_key = 4;
    cout << "Deleting number " << delete_key << endl;
    bt.deleteNode(bt.root, delete_key);

    bt.printTree2D(bt.root, 2);
    cout << "Inorder Traversal:";
    bt.inorder(bt.root);

    return 0;
}
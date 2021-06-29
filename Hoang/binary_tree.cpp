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

    Node* minNode()
    {
        Node* temp = root;
        while(temp->leftChild())
         temp = temp->left;
        return temp;
    }
    Node* maxNode()
    {
        Node* temp = root;
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

    vector<int> keys = {5, 3, 8, 2, 4};
    for(int i = 0; i < keys.size(); ++i)
    {
        Node* node = new Node(keys[i]);
        nodes.push_back(node);
        bt.insert(nodes[i], bt.root);
    }
    
    cout << "Node list: ";
    for(int i = 0; i < nodes.size(); ++i)
     cout << nodes[i]->key << " ";
    cout << endl;

    bt.printTree2D(bt.root, 2);
    cout << "Inorder Traversal:";
    bt.inorder(bt.root);

    
    return 0;
}
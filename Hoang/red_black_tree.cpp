/*
 * Red Black Tree
 * 
 * 2nd July
 * Teresuki
*/

#include <iostream>
#include <vector>

using namespace std;

enum colors {black , red};

struct Node
{
    int key;
    Node* left;
    Node* right;
    Node* parent;
    colors color;

    Node(int key)
    {
        this->key = key;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        color = red;
    }
    bool leftChild(){
        if(left != nullptr)
            return true;
        else return false;
    }
    bool rightChild(){
        if(right != nullptr)
            return true;
        else return false;
    }
};

struct RedBlackTree
{
    Node* root;
    Node* NIL = new Node(-1); // NIL nodes' value are given default as -1
    int blackHeigth;

    RedBlackTree()
    {
        root = nullptr;
        NIL->color = black;
        NIL->left = nullptr;
        NIL->right = nullptr;
    }
    
    void printBlackHeigth(){
        Node* temp = new Node(0);
        temp = root;
        int bHeight = 0;
        while(temp->left != nullptr){
            temp = temp->left;
            if(temp->color == black) ++bHeight;
        }
        blackHeigth = bHeight;
        cout << "Black Height of this tree is: " << bHeight << endl;
    }
    Node* minNode(Node* node){
        Node* temp = node;
        while(temp->leftChild())
         temp = temp->left;
        return temp;
    }
    Node* maxNode(Node* node){
        Node* temp = node;
        while(temp->rightChild())
         temp = temp->right;
        return temp;
    }

    void leftRotate(Node* gp, Node* parent, Node* node, bool NodeFLeft){
      Node* gpParent = new Node(0);
      gpParent = gp->parent;

      if(gp == root) root = parent; // Update the root in the binary tree
      if(gpParent != nullptr){
        if(gp == gpParent->left)
         gpParent->left = parent;
        else
         gpParent->right = parent;
      }

      //Line
      if(!NodeFLeft)
      {
          gp->parent = parent;
          gp->right = parent->left;
          parent->left = gp;
          parent->parent = gpParent;
      }
      //Triangle
      else
      {
          gp->parent = parent;
          gp->right = node;
          parent->left = gp;
          parent->parent = gpParent;
          node->parent = gp;
      }
    }

    void rightRotate(Node* gp, Node* parent, Node* node, bool NodeFLeft){
      Node* gpParent = new Node(0);
      gpParent = gp->parent;
      
      if(gp == root) root = parent; // Update the root in the binary tree
      if(gpParent != nullptr){
        if(gp == gpParent->left)
         gpParent->left = parent;
        else
         gpParent->right = parent;
      }

      //Line
      if(NodeFLeft){
          gp->parent = parent;
          gp->left = NIL;
          parent->right = gp;
          parent->parent = gpParent;
      }
      //Triangle
      else{
          node->left = parent;
          node->right = gp;
          parent->parent = node;
          parent->right = NIL;
          gp->parent = node;
          gp->left = NIL;
      }
    }

    void insert_fix(Node* node, bool NodeFLeft){
        Node* parent = new Node(0);
        Node* gp = new Node(0);
        Node* uncle = new Node(0);

        parent = node->parent;
        gp = parent->parent;

        //Parent is the left child of Grandparent
        bool ParentFLeft = (parent == gp->left);
        if(ParentFLeft)
         uncle = gp->right; 
        else
         uncle = gp->left;
            
        if(uncle->color == black){
            if(ParentFLeft)
             rightRotate(gp, parent, node, NodeFLeft);        
            else
             leftRotate(gp, parent, node, NodeFLeft);
            //Recoloring
            gp->color = red;
            parent->color = black;  
        }
        else{
            //Recoloring
            parent->color = black;
            uncle->color = black;
            gp->color = red;

            if(root->color == red)
             root->color = black;

            if(gp->parent != nullptr){
              if(gp->parent->color == red)
              insert_fix(gp, (gp == gp->parent->left) );
             }
        }
    }

    void insert(Node* node, Node* rootR){
        //There is no root node yet
        if(root == nullptr){
            root = node;
            root->color = black;
            root->left = NIL;
            root->right = NIL;
        }
        //There is already a root node
        else{
            //If the key is smaller than the node's key
            if(node->key <= rootR->key)
            {
                //If there is a child on the left and it's not NIL
                if(rootR->leftChild() && rootR->left != NIL)
                 insert(node, rootR->left);
                
                else{
                    rootR->left = node;
                    node->parent = rootR;
                    node->left = NIL;
                    node->right = NIL;
                    if(rootR->color == red)
                     insert_fix(node, true);
                 }
            }
            //If the key is larger than the node's key
            else
            {
                //If there is a child on the right and it's not NIL
                if(rootR->rightChild() && rootR->right != NIL)
                 insert(node, rootR->right);
                
                else{
                    rootR->right = node;
                    node->parent = rootR;
                    node->left = NIL;
                    node->right = NIL;
                    if(rootR->color == red)
                     insert_fix(node, false);
                 }
            }
        }
    }

    void inorder(Node* root){
        if(root->leftChild()){
            inorder(root->left);
        }

        if(root->key != -1)
        cout << root->key  << " ";

        if(root->rightChild()){
            inorder(root->right);
        }
    }

   void printTree2D(Node* node, int space){
       if (node == NULL)
        return ;
       space += 2;

       printTree2D(node->right, space);
       cout << endl;
       for(int i = 1; i < space; ++i)
        cout << "   ";

        if(node->color == red) cout << "(R)";
        else                   cout << "(B)";

        if(node->key == -1) cout << "NIL" << endl;
        else cout << node->key << endl;

       printTree2D(node->left, space);
   }
};

int main()
{
    RedBlackTree rbt;
    vector<Node*> nodes;

    //Change your input here:
    vector<int> keys = {8, 4, 2, 6, 5, 7, 1};
    for(int i = 0; i < keys.size(); ++i)
    {
        Node* node = new Node(keys[i]);
        nodes.push_back(node);
        rbt.insert(nodes[i], rbt.root);
    }

    rbt.printTree2D(rbt.root, 2);
    cout << "Inorder Traversal:";
    rbt.inorder(rbt.root); cout << endl;
    rbt.printBlackHeigth();

    return 0;
}
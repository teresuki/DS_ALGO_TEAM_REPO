/*
 * Red Black Tree
 * 
 * 1st July
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


struct RedBlackTree
{
    Node* root;
    Node* NIL = new Node(-1);
    int blackHeigth;

    RedBlackTree()
    {
        root = nullptr;
        NIL->color = black;
        NIL->left = nullptr;
        NIL->right = nullptr;
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

    Node* getNode(int key, Node* rootR)
    {
        if(key < rootR->key)
         getNode(key, rootR->left);
        else if(key > rootR->key)
         getNode(key, rootR->right);
        else if(key == rootR->key)
         return rootR;
    }

    void leftRotate(Node* gp, Node* parent, Node* node, bool NodeFLeft)
    {
      Node* gpParent = new Node(0);
      gpParent = gp->parent;
    
      //Line
      if(!NodeFLeft)
      {
          if(gpParent != nullptr)
          {
              if(gp == gpParent->left)
               gpParent->left = parent;
              else
               gpParent->right = parent;
          }
          gp->parent = parent;
          gp->right = NIL;
          parent->left = gp;
          parent->parent = gpParent;
        //Recoloring
         gp->color = red;
         parent->color = black;
         if(gp == this->root)
         this->root = parent;
      }
      //Triangle
      else
      {
          if(gpParent != nullptr)
          {
              if(gp == gpParent->left)
               gpParent->left = node;
              else
               gpParent->right = node;
          }
          node->right = parent;
          node->left = gp;
          parent->parent = node;
          parent->left = NIL;
          gp->parent = node;
          gp->right = NIL;
          //Recoloring
          gp->color = red;
          node->color = black;
          if(gp == this->root)
           this->root = node;
      }

    }

    void rightRotate(Node* gp, Node* parent, Node* node, bool NodeFLeft)
    {
      Node* gpParent = new Node(0);
      gpParent = gp->parent;
    
      //Line
      if(NodeFLeft)
      {
          if(gpParent != nullptr)
          {
              if(gp == gpParent->left)
               gpParent->left = parent;
              else
               gpParent->right = parent;
          }
          gp->parent = parent;
          gp->left = NIL;
          parent->right = gp;
          parent->parent = gpParent;
        //Recoloring
         gp->color = red;
         parent->color = black;
         if(gp == this->root)
         this->root = parent;
      }
      //Triangle
      else
      {
          if(gpParent != nullptr)
          {
              if(gp == gpParent->left)
               gpParent->left = node;
              else
               gpParent->right = node;
          }
          node->left = parent;
          node->right = gp;
          parent->parent = node;
          parent->right = NIL;
          gp->parent = node;
          gp->left = NIL;
          //Recoloring
          gp->color = red;
          node->color = black;
          if(gp == this->root)
           this->root = node;
      }

    }

    void insert_fix(Node* node, bool NodeFLeft)
    {
        
        Node* parent = new Node(0);
        parent = node->parent;

        if(node->color == black) return ;

        if(parent->color == red)
        {
            //gp == Grandparent
            Node* gp = new Node(0);
            gp = parent->parent;

            Node* uncle = new Node(0);

            //Parent From Left
            bool ParentFLeft = (parent == gp->left);

            //If parent is the left child of gp
            if(ParentFLeft)
             uncle = gp->right; //Uncle is the right child of gp

            //If parent is the right child of gp
            else
             uncle = gp->left;//Uncle is the left child of gp
            
            //If the uncle is black
            if(uncle->color == black)
            {
                
                if(ParentFLeft)
                 rightRotate(gp, parent, node, NodeFLeft);
                else
                 leftRotate(gp, parent, node, NodeFLeft);

            }
            else if(uncle->color == red)
            {
                parent->color = black;
                uncle->color = black;
                gp->color = red;
            }

            if(root->color == red)
             root->color = black;
            
            if(parent->parent != nullptr)
             {
                 NodeFLeft = (parent == (parent->parent->left) );
                 insert_fix(parent, NodeFLeft);
             }
            
        }
        
    }

    void insert(Node* node, Node* rootR)
    {
        //There is no root node yet
        if(root == nullptr)
        {
            root = node;
            root->color = black;
            root->left = NIL;
            root->right = NIL;
        }
        //There is already a root node
        else
        {
            //If the key is smaller than the node's key
            if(node->key <= rootR->key)
            {
                //If there is a child on the left and it's not NIL
                if(rootR->leftChild() && rootR->left != NIL)
                 insert(node, rootR->left);
                
                else
                 {
                    rootR->left = node;
                    node->parent = rootR;
                    node->left = NIL;
                    node->right = NIL;
                    insert_fix(node, true);
                 }
            }
            //If the key is larger than the node's key
            else if(node->key > rootR->key)
            {
                //If there is a child on the right and it's not NIL
                if(rootR->rightChild() && rootR->right != NIL)
                 insert(node, rootR->right);
                
                else
                 {
                    rootR->right = node;
                    node->parent = rootR;
                    node->left = NIL;
                    node->right = NIL;
                    insert_fix(node, false);
                 }
            }
        }
    }

    void inorder(Node* root)
    {
        if(root->leftChild()){
            inorder(root->left);
        }

        if(root->key != -1)
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
        if(node->color == red) cout << "(R)";
        else                   cout << "(B)";
       cout << node->key << endl;

       printTree2D(node->left, space);
   }

};


int main()
{
    RedBlackTree rbt;
    vector<Node*> nodes;

    vector<int> keys = {8, 4, 2, 6, 5, 7};
    for(int i = 0; i < keys.size(); ++i)
    {
        Node* node = new Node(keys[i]);
        nodes.push_back(node);
        rbt.insert(nodes[i], rbt.root);
    }

    rbt.printTree2D(rbt.root, 2);
    cout << "Inorder Traversal:";
    rbt.inorder(rbt.root); cout << endl;


    return 0;
}
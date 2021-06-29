#include <iostream>
#include <vector>
#include <string.h>
#include <conio.h>

// black = 0, red =1
enum color
{
    black,
    red
};
class Node
{
public:
    double value = -1;
    bool color = black; // black = 0
    Node *left = NULL;
    Node *right = NULL;
    Node *p = NULL;

    Node() {}
    Node(double value, bool color)
    {
        this->value = value;
        this->color = color;
    }
    bool hasTwoChildren()
    {
        return (right && left);
    }
    bool hasOneChild()
    {
        return ((right || left) && !(hasTwoChildren()));
    }
    Node *getOnlyChild()
    {
        if (this->hasOneChild())
        {
            if (left)
            {
                return left;
            }
            else
            {
                return right;
            }
        }
    }

    virtual ~Node()
    {
        std::cout << "Node " << value << " deleted" << '\n';
        left = nullptr;
        right = nullptr;
        free(left);
        free(right);
        free(p);
    }
};

class RedBlackTree
{
private:
    std::vector<Node *> listNode;
    Node *root = new Node();
    int height = 0;
    int tempHeight = 0;

public:
    RedBlackTree() {}
    RedBlackTree(double value)
    {
        Node *temp = new Node(value, black);
        root = new Node(value, black);
        listNode.push_back(temp);
        height = 1;
    }
    Node *getNodeRoot()
    {
        return root;
    }
    int getHeight()
    {
        return height;
    }
    void leftRotate(Node *x)
    {
        Node *y = x->right;
        x->right = y->left;
        if (y->left->value != -1)
        {
            y->left->p = x;
        }
        y->p = x->p;

        // assign parent node correctly
        if (x->p == NULL)
        {
            root = y;
        }
        else if (x == x->p->left)
        {
            x->p->left = y;
        }
        else
        {
            x->p->right = y;
        }

        y->left = x;
        x->p = y;
    }

    void rightRotate(Node *y)
    {
        Node *x = y->left;
        y->left = x->right;
        if (x->right->value != -1)
        {
            x->right->p = y;
        }
        x->p = y->p;

        // assign parent
        if (y->p == NULL)
        {
            root = x;
        }
        else if (y == y->p->left)
        {
            y->p->left = x;
        }
        else
        {
            y->p->right = y;
        }
        // finish assign
        x->right = y;
        y->p = x;
    }
    void insertNode(double value, int &heightTemp)
    {
        Node *insert = new Node(value, red);
        listNode.push_back(insert);
        Node *y = new Node();
        Node *x = root;

        // find position for insert node
        while (x->value != -1)
        {
            heightTemp++;
            if (heightTemp >= height)
            {
                height = heightTemp;
            }
            y = x;
            std::cout << "y value " << y->value << '\n';
            if (insert->value < x->value)
            {
                x = x->left;
            }
            else
            {
                x = x->right;
            }
        }
        std::cout << insert->value << '\n';
        // assign all connection  to insert node
        insert->p = y;
        if (y->value == -1)
        {
            root = insert;
            root->color = black;
            root->p = NULL;
        }
        else if (insert->value < y->value)
        {
            std::cout << "insert left" << '\n';
            y->left = insert;
        }
        else
        {
            y->right = insert;
        }
        insert->right = new Node();
        insert->left = new Node();
        insert->color = red;
        insertNodeFix(insert);
    }

    void insertNodeFix(Node *node)
    {
        if (node->p)
            while (node->p->color == red)
            {
                if (node->p->p)
                {
                    if (node->p == node->p->p->left)
                    {
                        // y is uncle of node
                        Node *y = node->p->p->right;

                        // case 1: y is red
                        if (y->color == red)
                        {
                            node->p->color = black;
                            y->color = black;
                            node->p->p->color = red;
                            node = node->p->p;
                            if (node == root)
                            {
                                break;
                            }
                        }
                        // case 2: y is black and node is right child
                        else if (node == node->p->right)
                        {
                            node = node->p;
                            leftRotate(node);
                            if (node == root)
                            {
                                break;
                            }
                        }

                        // case 3:
                        if (node->p)
                        {
                            if (node->p->p)
                            {
                                node->p->color = black;
                                node->p->p->color = red;
                                rightRotate(node->p->p);
                            }
                        }
                    }

                    // case 4, 5, 6
                    else
                    {
                        // y is uncle of node
                        Node *y = node->p->p->left;

                        // case 4: y is red
                        if (y->color == red)
                        {
                            node->p->color = black;
                            y->color = black;
                            node->p->p->color = red;
                            node = node->p->p;
                            if (node == root)
                            {
                                break;
                            }
                        }

                        // case 5: y is black and node is left child
                        else if (node == node->p->left)
                        {
                            node = node->p;
                            rightRotate(node);
                            if (node == root)
                            {
                                break;
                            }
                        }

                        // case 6:
                        if (node->p)
                        {
                            if (node->p->p)
                            {
                                node->p->color = black;
                                node->p->p->color = red;
                                leftRotate(node->p->p);
                            }
                        }
                    }
                }
                root->color = black;
            }
    }
    // reduce argument
    void insertNode(double value)
    {
        int height = 0;
        insertNode(value, height);
    }

    Node *findNode(int value, Node *find)
    {
        if (value != find->value)
        {
            if (value > find->value)
            {
                findNode(value, find->right);
            }
            else
            {
                findNode(value, find->left);
            }
        }
        else if (value == find->value)
        {
            return find;
        }
        else
        {
            std::cout << "Cannot find node" << '\n';
            return NULL;
        }
    }

    // reduced argument find node
    Node *findNode(int value)
    {
        Node *find = root;
        // return findNode(value, root);
        while (find != NULL && find->value != value)
        {
            if (value > find->value)
            {
                find = find->right;
            }
            else
            {
                find = find->left;
            }
        }
        return find;
    }

    void printAllNode()
    {
        for (int i = 0; i < listNode.size(); i++)
        {
            std::cout << listNode[i]->value << ' ';
        }
        std::cout << '\n';
    }

    void preorderTraversal(Node *node)
    {
        if (node)
        {
            std::cout << node->value << ' ';
            preorderTraversal(node->left);
            preorderTraversal(node->right);
        }
    }
    void preorderTraversal()
    {
        preorderTraversal(root);
        std::cout << '\n';
    }

    void inorderTraversal(Node *node)
    {
        Node *p = node;
        if (p)
        {
            inorderTraversal(p->left);
            std::cout << p->value << ' ';
            inorderTraversal(p->right);
        }
    }
    void inorderTraversal()
    {
        inorderTraversal(root);
        std::cout << '\n';
    }

    Node *getNodeMin(Node *node)
    {
        if (node->left)
        {
            node = node->left;
            getNodeMin(node);
        }
        else
        {
            return node;
        }
    }

    void printBT(const std::string prefix, Node *node, bool isLeft)
    {
        if (node != nullptr)
        {
            std::cout << prefix;

            std::cout << (isLeft ? "L" : "R");
            std::cout << (node->color ? "Red " : "Blk ");

            // print the value of the node
            std::cout << node->value << std::endl;

            // enter the next tree level - left and right branch
            printBT(prefix + (isLeft ? "    " : "    "), node->left, true);
            printBT(prefix + (isLeft ? "    " : "    "), node->right, false);
        }
    }
    // reduced print binary tree (postorder)
    void printBT()
    {
        printBT("", root, false);
    }
};

int main()
{

    int array[13] = {13, 6, 15, 17, 20, 9, 4, 3, 7, 2, 18, 8, 5};
    int array2[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    RedBlackTree bst1;
    Node *root = bst1.getNodeRoot();
    for (int i = 0; i < 13; i++)
    {
        bst1.insertNode(array[i]);
        bst1.printBT();
    }
    bst1.inorderTraversal();
    bst1.preorderTraversal();
    bst1.printAllNode();
}

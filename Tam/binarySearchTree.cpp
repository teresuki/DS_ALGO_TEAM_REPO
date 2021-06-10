#include <iostream>
#include <vector>
#include <string.h>

class Node
{
public:
    double value;
    Node *left = NULL;
    Node *right = NULL;

    Node() {}
    Node(double value)
    {
        this->value = value;
    }
    void setValue(double value)
    {
        this->value = value;
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
    }
};

class BinarySearchTree
{
private:
    std::vector<Node *> listNode;
    Node *root;
    int indexRoot = 0;
    int height = 0;
    int tempHeight = 0;

public:
    BinarySearchTree() {}
    BinarySearchTree(double value)
    {
        Node *temp = new Node(value);
        root = new Node(value);
        listNode.push_back(temp);
        indexRoot = 0;
        height = 1;
    }
    Node *getNodeRoot()
    {
        return root;
    }
    int getIndexRoot()
    {
        return indexRoot;
    }
    int getHeight()
    {
        return height;
    }
    void insertNode(double value, Node *node, int &heightTemp)
    {
        Node *insert = new Node(value);
        if (value >= node->value)
        {
            if (node->right != NULL)
            {
                insertNode(value, node->right, heightTemp);
            }
            else
            {
                node->right = insert;
                listNode.insert(listNode.begin() + heightTemp, insert);
            }
        }
        else
        {
            if (node->left != NULL)
            {
                insertNode(value, node->left, heightTemp);
            }
            else
            {
                node->left = insert;
                listNode.insert(listNode.begin() + heightTemp, insert);
            }
        }
        heightTemp++;
        if (heightTemp >= height)
        {
            height = heightTemp;
        }
    }

    // reduce argument
    void insertNode(double value)
    {
        int height = 0;
        insertNode(value, root, height);
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

    // find parent of value
    Node *findParent(int value, Node *find)
    {
        if (find->left != NULL)
        {
            std::cout << "left: " << find->left->value << '\n';
            if (find->left->value == value)
            {
                return find;
            }
        }
        if (find->right != NULL)
        {
            std::cout << "right: " << find->right->value << '\n';
            if (find->right->value == value)
            {
                return find;
            }
        }
        if (find->value > value)
        {
            findParent(value, find->left);
        }
        else if (find->value <= value)
        {
            findParent(value, find->right);
        }
    }
    // reduced find parent node
    Node *findParent(int value)
    {
        // Node *parent =
        // std::cout << "Parent value : " << parent->value << '\n';
        return findParent(value, root);
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
    
    void deleteNode(int value, Node *find)
    {
        if (value != find->value)
        {
            if (value > find->value)
            {
                deleteNode(value, find->right);
            }
            else
            {
                deleteNode(value, find->left);
            }
        }
        else
        {
            if (find->hasTwoChildren())
            {
                std::cout << "Delete mode with 2 chilren" << '\n';
                Node *min = getNodeMin(find->right);
                double minRight = min->value;
                std::cout << "Min of the right subtree: " << minRight << '\n';
                Node *parent = findParent(minRight);
                if (min->right)
                {
                    parent->left = min->right;
                    std::cout << "Free parent" << '\n';
                }
                delete (min);
                find->value = minRight;
            }
            else if (find->hasOneChild())
            {
                Node *child = find->getOnlyChild();
                std::cout << "Delete node with 1 child" << '\n';
                find->value = child->value;
                find->left = child->left;
                find->right = child->right;
                delete (child);
            }
            else
            {
                std::cout << "Node is leaf" << '\n';
                Node *parent = findParent(value);
                if (parent->left)
                {
                    if (parent->left->value == value)
                    {
                        parent->left = nullptr;
                        std::cout << "Free parent" << '\n';
                    }
                }
                else
                {
                    parent->right = nullptr;
                    std::cout << "Free parent" << '\n';
                }
                delete (find);
            }
        }
    }
};

int main()
{
    int array[12] = {13, 6, 15, 17, 20, 9, 4, 3, 7, 2, 18, 8};
    BinarySearchTree bst1(array[0]);
    Node *root = bst1.getNodeRoot();
    for (int i = 1; i < 12; i++)
    {
        bst1.insertNode(array[i]);
    }
    bst1.printBT();
    bst1.deleteNode(6, root);
    bst1.printBT();
}

#include <iostream>
#include <vector>
using namespace std;

struct Node
{
    int frequency;
    char letter;
    Node *left;
    Node *right;

    Node() {}

    Node(const Node &otherNode)
        : frequency(otherNode.frequency), letter(otherNode.letter), left(otherNode.left), right(otherNode.right)
    {
    }

    Node(int frequency)
    {
        this->frequency = frequency;
        left = nullptr;
        right = nullptr;
    }

    bool leftChild()
    {
        if (left != nullptr)
        {
            return true;
        }
        else
            return false;
    }

    bool rightChild()
    {
        if (right != nullptr)
        {
            return true;
        }
        else
            return false;
    }
};

struct BinaryTree
{
    Node *root;

    BinaryTree()
    {
        root = nullptr;
    }

    Node *minNode(Node *node)
    {
        Node *temp = node;
        while (temp->leftChild())
            temp = temp->left;
        return temp;
    }
    Node *maxNode(Node *node)
    {
        Node *temp = node;
        while (temp->rightChild())
            temp = temp->right;
        return temp;
    }

    void insert(Node *node, Node *rootR)
    {
        //There is no root node yet.
        if (root == nullptr)
            root = node;
        else
        {
            if (node->frequency <= rootR->frequency)
            {
                if (rootR->leftChild())
                    insert(node, rootR->left);
                else
                    rootR->left = node;
            }

            else if (node->frequency > rootR->frequency)
            {
                if (rootR->rightChild())
                    insert(node, rootR->right);
                else
                    rootR->right = node;
            }
        }
    }

    //node should be root as the first parameter
    //Encounter is used if you want to delete a node with duplicated frequency in the tree
    void deleteNode(Node *node, int frequency, Node *parent = nullptr, int encounter = 1)
    {
        static int enc = 0;

        if (frequency == node->frequency)
        {
            enc++;
            if (enc < encounter)
                goto here;

            //From Left, From Right
            bool fLeft = false, fRight = false;
            if (node == parent->left)
                fLeft = true;
            if (node == parent->right)
                fRight = true;

            if (fLeft)
            {
                //No children
                if (node->leftChild() == 0 && node->rightChild() == 0)
                {
                    parent->left = nullptr;
                }
                //Left Child
                else if (node->leftChild() == 1 && node->rightChild() == 0)
                {
                    parent->left = node->left;
                }
                //Right child
                else if (node->leftChild() == 0 && node->rightChild() == 1)
                {
                    parent->left = node->right;
                }
                //Has two children
                else if (node->leftChild() == 1 && node->rightChild() == 1)
                {
                    Node *successor = new Node(0);
                    successor = minNode(node->right);

                    deleteNode(node->right, successor->frequency, node);
                    node->frequency = successor->frequency;
                    return;
                }
            }

            //Pretty much identical to fLeft
            else if (fRight)
            {
                //No children
                if (node->leftChild() == 0 && node->rightChild() == 0)
                {
                    parent->right = nullptr;
                }
                //Left Child
                else if (node->leftChild() == 1 && node->rightChild() == 0)
                {
                    parent->right = node->left;
                }
                //Right child
                else if (node->leftChild() == 0 && node->rightChild() == 1)
                {
                    parent->left = node->right;
                }
                //Has two children
                else if (node->leftChild() == 1 && node->rightChild() == 1)
                {
                    Node *successor = new Node(0);
                    successor = minNode(node->right);

                    deleteNode(node->right, successor->frequency, node);
                    node->frequency = successor->frequency;
                    return;
                }
            }
        }
    here:
        if (frequency != node->frequency || enc < encounter)
        {
            parent = node;
            if (frequency <= node->frequency)
            {
                deleteNode(node->left, frequency, parent);
            }
            else if (frequency > node->frequency)
            {
                deleteNode(node->right, frequency, parent);
            }
        }
    }

    void inorder(Node *root)
    {
        if (root->leftChild())
        {
            inorder(root->left);
        }

        cout << root->frequency << " ";

        if (root->rightChild())
        {
            inorder(root->right);
        }
    }

    void printTree2D(Node *node, int space)
    {
        if (node == NULL)
            return;
        space += 2;

        printTree2D(node->right, space);
        cout << endl;
        for (int i = 1; i < space; ++i)
            cout << "   ";
        cout << node->frequency << "(" << node->letter << ")" << endl;

        printTree2D(node->left, space);
    }

    void printEncodeTable(Node *node, string encodeString)
    {
        if (node == NULL)
            return;

        printEncodeTable(node->left, encodeString + "0");
        if (node->leftChild() == false && node->rightChild() == false)
        {
            cout << node->letter << ":" << encodeString << endl;
            encodeString = encodeString.substr(0, encodeString.size() - 1);
        }
        printEncodeTable(node->right, encodeString + "1");
    }
};

Node *huffmanEncode(vector<Node> &theList)
{
    Node *root = nullptr;

    while (theList.size() > 1)
    {
        Node *z = new Node();
        Node *x = new Node(theList[0]);
        Node *y = new Node(theList[1]);

        z->left = x;
        z->right = y;
        z->letter = '#'; // No Letter
        z->frequency = x->frequency + y->frequency;

        theList.erase(theList.begin());
        theList.erase(theList.begin());
        for (int i = 0; i < theList.size(); ++i)
        {
            if (z->frequency <= theList[i].frequency)
            {
                theList.insert(theList.begin() + i, *z);
                break;
            }
            if (i == theList.size() - 1)
            {
                theList.push_back(*z);
                break;
            }
        }
        root = z;
        //cout << "Foobar" << endl;
    }
    return root;
}

int main()
{
    BinaryTree bt;
    vector<Node> nodeList;
    nodeList.resize(26);
    for (int i = 0; i < 26; ++i)
    {
        nodeList[i].frequency = i + 1;
        nodeList[i].left = nullptr;
        nodeList[i].right = nullptr;
    }

    nodeList[0].letter = 'Z';
    nodeList[1].letter = 'Q';
    nodeList[2].letter = 'X';
    nodeList[3].letter = 'J';
    nodeList[4].letter = 'K';
    nodeList[5].letter = 'V';
    nodeList[6].letter = 'B';
    nodeList[7].letter = 'P';
    nodeList[8].letter = 'Y';
    nodeList[9].letter = 'G';
    nodeList[10].letter = 'F';
    nodeList[11].letter = 'W';
    nodeList[12].letter = 'M';
    nodeList[13].letter = 'U';
    nodeList[14].letter = 'C';
    nodeList[15].letter = 'L';
    nodeList[16].letter = 'D';
    nodeList[17].letter = 'R';
    nodeList[18].letter = 'H';
    nodeList[19].letter = 'S';
    nodeList[20].letter = 'N';
    nodeList[21].letter = 'I';
    nodeList[22].letter = 'O';
    nodeList[23].letter = 'A';
    nodeList[24].letter = 'T';
    nodeList[25].letter = 'E';

    Node *root = huffmanEncode(nodeList);
    bt.printEncodeTable(root, "");

    return 0;
}
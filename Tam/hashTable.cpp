#include <iostream>
#include <string>
#include <math.h>
#include <time.h>
using namespace std;

class Node
{
public:
    Node *previous = nullptr;
    Node *next = nullptr;
    string value = "";
    Node() {}
    Node(string value)
    {
        this->value = value;
    }
    virtual ~Node()
    {
        previous = nullptr;
        next = nullptr;
        cout << "Node " << value << " deleted" << '\n';
    }
};

class List
{
public:
    Node *head = nullptr;
    List() {}
    List(Node *head)
    {
        this->head = head;
    }
    Node *getHead()
    {
        return head;
    }
    void pushNode(string value)
    {
        Node *temp = new Node(value);
        head->previous = temp;
        temp->next = head;
        head = temp;
    }
    Node *findNode(string value)
    {
        Node *temp = head;
        while (temp->value != value)
        {
            temp = temp->next;
        }
        return temp;
    }
    void deleteNode(string value)
    {
        Node *temp = findNode(value);
        if (temp == head)
        {
            head = temp->next;
        }
        if (temp->next)
        {
            temp->next->previous = temp->previous;
        }
        if (temp->previous)
        {
            temp->previous->next = temp->next;
        }
        delete (temp);
    }

    void printNode()
    {
        if (head != NULL)
        {
            Node *temp = head;

            while (temp != nullptr)
            {
                cout << temp->value << " <-> ";
                temp = temp->next;
            }
        }
        cout << '\n';
    }
};

int convertStringToInt(string s)
{
    int result = 0;
    for (int i = 0; i < s.size(); i++)
    {
        int j = s.size() - i - 1;
        result += s[i] * pow(128, j);
    }
    return result;
}

int hashString(string k)
{
    int result = 0;
    for (int i = 0; i < k.size(); i++)
    {
        int j = k.size() - i - 1;
        result += (int)k[i] * pow(128, j);
    }
    std::cout << result << '\n';
    result = result % 101;
    int hashValue = result;
    return hashValue;
}

string getRandomString(int length)
{
    string a = "";
    for (int i = 0; i < length; i++)
    {
        a += rand() % 26 + 65;
    }
    return a;
}

// chaining by using linked list
void insertString(List **T, string k)
{
    int index = hashString(k);
    // if T[index] is NULL add a List head
    if (T[index] == NULL)
    {
        Node *head = new Node(k);
        List *list = new List(head);
        T[index] = list;
    }
    // T[index] has a list push string k to the existed list
    else
    {
        T[index]->pushNode(k);
    }
}
int main()
{
    srand(time(NULL));
    string a = "CLRS";
    std::cout << convertStringToInt(a);
    List *T[101];
    for (int i = 0; i < 101; i++)
    {
        T[i] = NULL;
    }
    for (int i = 0; i < 200; i++)
    {
        a = getRandomString(4);
        insertString(T, a);
    }
    for (int i = 0; i < 101; i++)
    {
        cout << i << ' ';
        if (T[i])
        {
            T[i]->printNode();
        }
        else
        {
            cout << '\n';
        }
    }
}
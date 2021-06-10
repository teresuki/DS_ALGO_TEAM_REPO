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

// collision avoid by using linked list only(chaining)
void insertKey(List **T, string k)
{
    int index = hashString(k);

    // if T[index] has a list, push string k to the existed list
    if (T[index])
    {
        T[index]->pushNode(k);
    }

    // T[index] is NULL, add a List head
    else
    {
        Node *head = new Node(k);
        List *list = new List(head);
        T[index] = list;
    }
}
// delete key for hash table with only linked list
void deleteKey(List **T, string k)
{
    int index = hashString(k);
    if (T[index])
    {
        T[index]->deleteNode(k);
    }
    else
    {
        cout << "Invalid key" << '\n';
    }
}

// find key for hash table with only linked list
Node *findKey(List **T, string k)
{
    int index = hashString(k);
    if (T[index])
    {
        return T[index]->findNode(k);
    }
    else
    {
        cout << "Invalid key" << '\n';
    }
}

// collision avoid by using linear probing and linked list
void insertKeyProbing(List **T, string k)
{
    int probe = 0;
    int index = hashString(k);
    for (probe; probe < 101; probe++)
    {
        int newIndex = (index + probe) % 101;
        // T[index] has a list, increase probe
        if (T[newIndex])
        {
            ;
        }
        // T[index] is NULL, add a List head
        else
        {
            Node *head = new Node(k);
            List *list = new List(head);

            T[newIndex] = list;
            break;
            return;
        }
    }
    // if there are no open address, push it to the orginal list
    if (probe == 101)
    {
        T[index]->pushNode(k);
    }
}
// find and delete function for hash tabel with probe need to be added

int main()
{
    srand(time(NULL));
    string a = "CLRS";
    List *TLinkedList[101];
    List *TProbe[101];
    int hashTableLength = 101;
    int numberOfKey = 101;

    // initialize hash table
    for (int i = 0; i < hashTableLength; i++)
    {
        TLinkedList[i] = NULL;
        TProbe[i] = NULL;
    }

    // insert keys to hash table
    for (int i = 0; i < numberOfKey; i++)
    {
        a = getRandomString(4);
        insertKey(TLinkedList, a);
        insertKeyProbing(TProbe, a);
    }

    // print hash table
    cout << "Hash Table with only linked list" << '\n';
    for (int i = 0; i < hashTableLength; i++)
    {
        cout << i << ' ';
        if (TLinkedList[i])
        {
            TLinkedList[i]->printNode();
        }
        else
        {
            cout << '\n';
        }
    }
    cout << "Hash Table with probe and liked list" << '\n';
    for (int i = 0; i < hashTableLength; i++)
    {
        cout << i << ' ';
        if (TProbe[i])
        {
            TProbe[i]->printNode();
        }
        else
        {
            cout << '\n';
        }
    }

    // test find and delete function for both hash table
    // now the function for probing is not functioning
    cout << "Find key value: " << findKey(TLinkedList, a)->value << '\n';
    cout << "Find key value: " << findKey(TProbe, a)->value << '\n';
    deleteKey(TLinkedList, a);
    deleteKey(TProbe, a);
    if (findKey(TLinkedList, a))
    {
        cout << "Find key value after delete: " << findKey(TLinkedList, a)->value << '\n';
    }
    if (findKey(TProbe, a))
    {
        cout << "Find key value after delete: " << findKey(TProbe, a)->value << '\n';
    }
}

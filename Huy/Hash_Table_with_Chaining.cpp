// Implementing Hash Table -- Everything seen impossible until it's done, keep focusing
/* Name: Truong Quang Huy
   ID: 18602
   Class: CS2019 - VGU
*/

#include <iostream>
#include <string>
#include <cmath>
using namespace std;


/* double  linked list */
struct Node
{
    string key;     // key here is a 4 character string
    Node* prev;
    Node* next;
    // no satellite data here, may be an object containing a lot of info
};


Node* List_search(Node* list_head, string k)
{
    Node* x = list_head;

    while(x != nullptr && x->key != k)  // iterative search => efficient
        x = x->next;

    return x;   // no need to use 'delete' here because of no 'new'
}


// creating a new node
Node* new_node(string key)
{
    Node* x = new Node;

    x->key = key;
    x->prev = x->next = nullptr;

    return x;   // x will be killed at the end of the function, the return value here is a copy of x
                // that is the  address point to the new Node which stay in heap and is not be killed
}


/* insert new node in the head of the list */
void List_insert(Node*& list_head, Node* x)
{
    x->next = list_head;

    if(list_head != nullptr)   // need to understand, nullptr does not have prev pointer
        list_head->prev = x;   //  and also dereferencing a null pointer cause segmentation fault error

    list_head = x;       // like a magic, but it's correct because x->next = list_head

    x->prev = nullptr;   // x become a new list_head
}


/* delete a node from the list */
void List_delete(Node*& list_head, Node* x) // also need to pass the head by pointer to pointer or reference to pointer here
{                                           // because it's a modifying operation
    if(x == nullptr)
    {
        cout << "The deleted element is not found" << endl;
        return;
    }

    if(x->prev != nullptr)
        x->prev->next = x->next;    // linked 1
    else
        list_head = x->next;

    if(x->next != nullptr)
        x->next->prev = x->prev;    // linked 2
}


/* function overloading, string version */
void List_delete(Node*& list_head, string k)
{
    Node* x = List_search(list_head, k);

    List_delete(list_head, x);
}


/* display all elements in the list*/
void List_view(Node* list_head)
{
    Node* x = list_head;    // maybe no need because the list_head here is just a copy of pointer list_head
                            // the original list_head is not affected by this function, but I want to use a new pointer
                            // to be more clear here.
    while(x != nullptr)
    {
        cout << x->key;
        x = x->next;
        if(x != nullptr)
            cout << "-";
    }

    cout << endl;
}


// free the memory in the heap
void delete_linked_list(Node* x)
{
    if(x->next != nullptr)
        delete_linked_list(x->next);

    delete x;
}


/* hash table with chaining */
Node* T[100] = { nullptr };     // array of 100 pointers to 100 linked lists


/* computing the h(k) value */
int hash_function(string key)   // key is the 4 alphabet string
{
    if(key.size() != 4)
    {
        cout << "Wrong key!";
        exit(-1);
    }

    int k = key[0]*pow(128, 3) + key[1]*pow(128, 2) + key[2]*pow(128, 1) + key[3]*pow(128, 0);

    return k % 100;
}


/* insert a value to hash table */
void Hash_Table_Insert(Node* T[], string key) // assume the size of hash table is 100 => not put size as argument
{
    int hash_value = hash_function(key);

    if(List_search(T[hash_value], key) == nullptr)  // additional check to avoid duplicate element
        List_insert(T[hash_value], new_node(key));
    else
        cout << "Duplicate elemement!";
}


/* search a value in the hash table, return nullptr if not found */
Node* Hash_Table_Search(Node* T[], string key)
{
    int hash_value = hash_function(key);

    return List_search(T[hash_value], key);
}


/* delete a value in the hash table */
void Hash_Table_Delete(Node* T[], string key)
{
    int hash_value = hash_function(key);

    List_delete(T[hash_value], List_search(T[hash_value], key));
}


/* Hash Table view */
void Hash_Table_View(Node* T[])
{
    for(int i = 0; i < 100; i++)
    {
        if(T[i] != nullptr)
        {
            cout << "h(k)=" << i << ": ";
            List_view(T[i]);
        }
    }
    cout << endl;
}


/* free the memory in the heap of the hash table*/
void delete_Hash_Table(Node* T[])
{
    for(int i = 0; i < 100; i++)
        if(T[i] != nullptr)
            delete_linked_list(T[i]);
}

int main(void)
{
    string key_1 = "CLRS";
    string key_2 = "TQHK";
    string key_3 = "abcc";

    Hash_Table_Insert(T, key_1);
    Hash_Table_Insert(T, key_2);
    Hash_Table_Insert(T, key_3);

    cout << "Initial Hash Table" << endl;
    Hash_Table_View(T);

    cout << "Delete the element with the key \"abcc\" " << endl;
    Hash_Table_Delete(T, "abcc");
    Hash_Table_View(T);

    cout << "Search for the element with the key \"TQHK\": " << endl;
    if(Hash_Table_Search(T, "TQHK"))
        cout << "Found!" << endl;
    else
        cout << "Not Found!" << endl;

    cout << "Search for the element with the key \"TQaH\": " << endl;
    if(Hash_Table_Search(T, "TQaH"))
        cout << "Found!" << endl;
    else
        cout << "Not Found!" << endl;

    delete_Hash_Table(T);

    return 0;
}


/* Old design -- the best design is the "simplest" one */
///* slot in hash table with chaining*/
//struct slot
//{
//    int h_k;    // more correct, hash value of k, not k
//    Node* linked_list;
//};

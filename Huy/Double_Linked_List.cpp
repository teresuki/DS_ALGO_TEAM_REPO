// Double linked-list, focus and clear, finish the work
/* Name: Truong Quang Huy
   ID: 18602
   Class: CS2019 - VGU
*/

#include <iostream>
using namespace std;

struct Node
{
    int key;
    Node* prev;
    Node* next;
};

Node* new_node(int k)
{
    Node* x = new Node;

    x->key = k;
    x->prev = x->next = nullptr;

    return x;   // x will be killed at the end of the function, the return value here is a copy of x
                // that is the  address point to the new Node which stay in heap and is not be killed
}

/* in this fundamental Data Structure and Algorithm, we do not need to use OOP => more complex */
Node* List_search(Node* list_head, int k)
{
    Node* x = list_head;

    while(x != nullptr && x->key != k)  // iterative search => efficient
        x = x->next;

    return x;   // no need to use 'delete' here because of no 'new'
}

/* insert new node in the head of the list */
void List_insert(Node** list_head, Node* x)
{
    x->next = *list_head;

    if(*list_head != nullptr)   // need to understand
        (*list_head)->prev = x; // nullptr does not have prev pointer and also dereferencing a null pointer cause segmentation fault error

    *list_head = x;      // like a magic, but it's correct because x->next = list_head
                         // => already write down old list_head
    x->prev = nullptr;   // x become a new list_head
}

/* delete a node from the list */
void List_delete(Node** list_head, Node* x) // also need to pass the head by pointer to pointer or reference to pointer here
{                                           // because it's a modifying operation
    if(x == nullptr)
    {
        cout << "The deleted element is not found" << endl;
        return;
    }
    if(x->prev != nullptr)
        x->prev->next = x->next;    // linked 1
    else
        *list_head = x->next;

    if(x->next != nullptr)
        x->next->prev = x->prev;    // linked 2
}

/* function overloading, int version */
void List_delete(Node** list_head, int k)
{
    Node* x = List_search(*list_head, k);

    List_delete(list_head, x);
}

/* display all elements in the list*/
void List_view(Node* list_head)
{
    Node* x = list_head;    // maybe no need because the list_head here is just a copy of pointer list_head
                            // the real list_head is not affected by this function, but I want to use a new pointer
                            // to be more clear here.
    while(x != nullptr)
    {
        cout << x->key;
        x = x->next;
        if(x != nullptr)
            cout << "-";
    }

    cout << endl << endl;
}

// test case
void insert_an_array_to_the_list(Node** list_head)
{
    int arr[] = {3, 6, 1, 5, 2, 7};
    int arr_size = sizeof arr / sizeof arr[0];

    /* fix this bug the hard and correct way -- double pointer */
    Node** temp = list_head;
    for(int i = 0; i < arr_size; i++)
    {
        List_insert(temp, new_node(arr[i]));
    }
}


// free the memory in the heap
void delete_linked_list(Node* x)
{
    if(x->next != nullptr)
        delete_linked_list(x->next);

    delete x;
}


// driver code
int main(void)
{
    Node* list_head = nullptr;
    Node** temp = &list_head;

    insert_an_array_to_the_list(temp); // if put list view outside insert_array function => also need double pointer here
    List_view(list_head);

    cout << "Delete the element with the key 5" << endl;
    List_delete(temp, 5);
    List_view(list_head);

    cout << "Delete the element with the key 0" << endl;
    List_delete(temp, 0);
    List_view(list_head);

    delete_linked_list(list_head);
    // for the case of duplicating elements but you should implement like this way, add a loop => lower the efficiency
    // use "count" or "hash map" for solving this
    /*
    while(List_search(list_head, 3) != nullptr)
        List_delete(temp, List_search(list_head, 3));   */

    return 0;
}

// Linked List

#include <iostream>
using namespace std;

struct Node
{
  int data;
  Node* next;
};

//Insert a node after a given node in the linked list
/* Example
 Original Linked List: 10->20->30
 Add 40 after 20
 New Linked List: 10->20->40->30
*/
void insert_After(Node* prev_node, Node* new_node)
{
  // 20-> 30 to  20 -> 30
  // 40          40 ---^
  new_node->next = prev_node->next;
  // 20 -> 30  to  20 -> 40 -> 30
  // 40 ---^
  prev_node->next = new_node;
}

void print(Node* node)
{
  if(node->next != NULL)
  {
      cout << node->data << " --> ";
      print(node->next);
  }
  else
  {
      cout << node->data << "\n";
  }
}

int main()
{
  Node *n1, *n2, *n3;
  n1 = new Node();
  n2 = new Node();
  n3 = new Node();

  n1->data = 10; n1->next = n2;
  n2->data = 20; n2->next = n3;
  n3->data = 30; n3->next = NULL;



  //New Node
  Node* n4;
  n4 = new Node();
  n4->data = 40;

  //Driver Print Test
  cout << "Original Linked List: \n";
  print(n1);

  insert_After(n2, n4);
  cout << "New Linked List after Insertion: \n";
  print(n1);

  return 0;
}

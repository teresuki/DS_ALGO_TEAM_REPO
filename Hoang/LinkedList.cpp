// Linked List

#include <iostream>
using namespace std;

/* Example:
   0        1        2
 [10] --> [20] --> [30]
*/
//Every Node will have a value and a pointer to the next node
//The final node's pointer will point to NULL

struct Node
{
  int data;
  Node* next;
};

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
  n3->data = 30; n3->next = nullptr;

  //Driver Print Test
  cout << "Linked List: ";
  print(n1);

  return 0;
}

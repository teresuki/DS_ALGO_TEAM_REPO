// Linked List

#include <iostream>
using namespace std;

struct Node
{
  int data;
  Node* next;
};

Node* getNode(Node* node, int position)
{
    static int pos = 0;
    if(pos != position)
    {
        ++pos;
        getNode(node->next, position);
    }
    else
    {
      //Reset the static value.
      pos = 0;
      return node;
    }
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
  Node *n1, *n2, *n3, *n4;
  n1 = new Node();
  n2 = new Node();
  n3 = new Node();
  n4 = new Node();

  n1->data = 10; n1->next = n2;
  n2->data = 20; n2->next = n3;
  n3->data = 30; n3->next = n4;
  n4->data = 40; n4->next = NULL;


  //Driver Print Test
  cout << "Printing the Linked List Value using getNode function: ";
  for(int i = 0; i < 4; ++i)
  {
      cout << getNode(n1, i)->data << " ";
  }
  
  return 0;
}

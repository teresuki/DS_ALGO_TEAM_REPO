// Linked List

#include <iostream>
using namespace std;

struct Node
{
  int data;
  Node* next;
};

/* Delete a node in a linked list 
 given it's head and position of that node
 
 Example:
  [10] -> [20] -> [30] -> [40]
  deleteNode(Node* head, 2)
  [10] -> [20] -> [40]
 */
void deleteNode(Node* &node, int position)
{
    static int pos = 0;
    //If the desired deleted node is the head.
    if(position == 0)
    {
        node->next = NULL;
        delete(node);
    }
    else
    {
        //Traverse to the node before the desired deleted node.
        if (pos < position-1)
        {
            ++pos;
            deleteNode(node->next, position);
        }
        else
        {
            //Store the node after the desired deleted node
            Node* temp = node->next->next;
            //Unlink the desired deleted node from the after node.
            node->next->next = NULL;
            //Free the memory of the desired deleted node.
            delete(node->next);
            //Link the before node to the after node.
            node->next = temp;
            delete(temp);
        }

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
  cout << "Before Delete: ";
  print(n1);

  cout << "After Delete: ";
  deleteNode(n1, 2);
  //Note, if you delete the head, the next head will be n2!
  print(n1);


  return 0;
}

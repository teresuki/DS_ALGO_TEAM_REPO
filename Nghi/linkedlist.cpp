#include <iostream>
#include <vector>

using namespace std;

class Item {
public:
	Item* prev;
	Item* next;
	int key;

	Item(int key)
	: key{key} {}
};

class LinkedList {
private:
	Item* head;
public:
	LinkedList() {}
	LinkedList(Item* head)
	: head{head} {}

	Item* searchItem(int k) {
		Item* x = head;
		while ((x!=0)&&(x->key!=k)) {
			x = x->next;
		}
		return x;
	}

	void insertItem(Item* x) {
		x->next = head;
		if(head!=0) {
			head->prev = x;
		}
		head = x;
		x->prev = 0;
	}

	void deleteItem(Item* x) {
		if (x->next!=0) {
			(x->next)->prev = x->prev;
		}
		if (x->prev!=0) {
			(x->prev)->next = x->next;
		}
		else {
			head = x->next;
		}
	}

	void printList() {
		Item* x = head;
		while (x!=0) {
			cout<<x->key<<"\t";
			x = x->next;
		}
		cout<<endl;
	}
};

int main() {
	Item* a = new Item(7);
	Item* b = new Item(0);
	Item* c = new Item(1);
	Item* d = new Item(2);
	LinkedList list(a);
	list.insertItem(b);
	list.insertItem(c);
	list.insertItem(d);
	list.printList();
	Item* x = list.searchItem(0);
	list.deleteItem(x);
	list.printList();
}
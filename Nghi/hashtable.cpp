#include <iostream>
#include <array>
#include <string>
#include <cmath>

using namespace std;

#define SIZE 100

int gcd(int a, int b)
{
    // Everything divides 0
    if (a == 0)
       return b;
    if (b == 0)
       return a;
  
    // base case
    if (a == b)
        return a;
  
    // a is greater
    if (a > b)
        return gcd(a-b, b);
    return gcd(a, b-a);
}

class Item {
public:
	Item* prev;
	Item* next;
	string key;

	Item(string key)
	: key{key} {}
};

class LinkedList {
private:
	Item* head;
public:
	LinkedList() {}
	LinkedList(Item* head)
	: head{head} {}

	Item* searchItem(string k) {
		Item* x = head;
		while ((x!=0)&&(x->key.compare(k)!=0)) {
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

class HashTableChain {
public:
	array<LinkedList*, SIZE> hash_table;
	int m = 8;
	double A = (1.0*rand())/RAND_MAX;

	HashTableChain() {
		hash_table.fill(nullptr);
	}

	int hash(int k) {
		double value = (1.0*k)*A;
		double fraction = modf(value, &fraction);
		fraction*=m;
		return floor(fraction);
	}

	void table_insert(string key_string) {
		int key = 0;
		for (int i = 0; i<4; i++) {
			key+= (key_string.at(i)*pow(128,3-i));
		}
		int index = hash(key);
		cout<<hash_table.at(index)<<endl;
		if (hash_table.at(index) == nullptr) {
			Item* item = new Item(key_string);
			hash_table.at(index) = new LinkedList(item);
		}
		else {
			Item* item = new Item(key_string);
			hash_table.at(index)->insertItem(item);
		}
	}
	Item* table_search(string key_string) {
		int key = 0;
		for (int i = 0; i<4; i++) {
			key+= (key_string.at(i)*pow(128,3-i));
		}
		int index = hash(key);
		if (hash_table.at(index) != nullptr) {
			return hash_table.at(index)->searchItem(key_string);
		}
		else {
			return nullptr;
		}
	}
	void table_delete(string key_string) {
		int key = 0;
		for (int i = 0; i<4; i++) {
			key+= (key_string.at(i)*pow(128,3-i));
		}
		int index = hash(key);
		if (hash_table.at(index) != nullptr) {
			Item* temp = hash_table.at(index)->searchItem(key_string);
			hash_table.at(index)->deleteItem(temp);
		}
		else {
			cout<<"Can't delete because there's no such item."<<endl;
		}
	}
};

class HashTableLinear {
public:
	array<string,100> hash_table;
	int m = 8; //m is used inside the hash function, and is chosen because it = 2^3
	double A = (1.0*rand())/RAND_MAX; //A is used inside the hash function
	int probe_factor = 3;

	int hash(int k) {
		double value = (1.0*k)*A;
		double fraction = modf(value, &fraction);
		fraction*=m;
		return floor(fraction);
	}

	int probing(int x) {
		return probe_factor*x;
	}

	void table_insert(string key_string) {
		int key = 0;
		for (int i = 0; i<4; i++) {
			key+= (key_string.at(i)*pow(128,3-i));
		}
		int x = 1;
		int keyHash = hash(key);
		int index = keyHash%SIZE;
		while (index<100) {
			if (hash_table.at(index).compare("")==0) {
				hash_table.at(index) = key_string;
				return;
			}
			else {
				index = (keyHash + probing(x))%SIZE;
				x++;
			}
		}
		cout<<"Out of space. Bye."<<endl;
	}

	int table_search(string key_string) {
		int key = 0;
		for (int i = 0; i<4; i++) {
			key+= (key_string.at(i)*pow(128,3-i));
		}
		int x = 1;
		int keyHash = hash(key);
		int index = keyHash;
		int count = 0;
		while (index<100 && count<100) {
			if (hash_table.at(index).compare(key_string)==0) {
				return index;
			}
			else {
				index = (keyHash + probing(x))%SIZE;
				x++;
			}
			count++;
		}
		cout<<"No such item."<<endl;
		return -1;
	}
	void table_delete(string key_string) {
		int key = 0;
		for (int i = 0; i<4; i++) {
			key+= (key_string.at(i)*pow(128,3-i));
		}
		int x = 1;
		int keyHash = hash(key);
		int index = keyHash;
		while (index<100) {
			if (hash_table.at(index).compare(key_string)==0) {
				hash_table.at(index) = "";
				return;
			}
			else {
				index = (keyHash + probing(x))%SIZE;
				x++;
			}
			cout<<"Can't delete because no such item."<<endl;
		}
	}
};

int main() {
	cout<<"LINEAR PROBING DEMO: "<<endl;
	HashTableLinear tl;
	tl.table_insert("abcd");
	cout<<tl.table_search("abcd")<<endl;
	tl.table_delete("abcd");
	cout<<tl.table_search("abcd")<<endl;

	cout<<endl<<endl<<"CHAINING DEMO: "<<endl;
	HashTableChain tc;
	tc.table_insert("abcd");
	cout<<tc.table_search("abcd")<<endl;
	tc.table_delete("abcd");
	cout<<tc.table_search("abcd")<<endl;
}
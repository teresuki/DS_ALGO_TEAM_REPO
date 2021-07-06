// Hash Table using Linear Probing(earliest type of Open Addressing) to deal with the collision
// Not so effective because it is limited by the size of hash table
/* Finised Him! */
/* Name: Truong Quang Huy
   ID: 18602
   Class: CS2019 - VGU
*/

#include <iostream>
#include <cmath>
#include <string>
using namespace std;


/* Hash Table with Linear Probing */
string T[100] = { "" };  // KISS principle


/* computing the h(k) value */
int hash_function(string key, int i)   // key is the 4 alphabet string
{
    if(key.size() != 4)
    {
        cout << "Wrong key!";
        exit(-1);
    }

    int k = key[0]*pow(128, 3) + key[1]*pow(128, 2) + key[2]*pow(128, 1) + key[3]*pow(128, 0) + i;

    return k % 100;
}


/* Hash Table Insert */
int Hash_Table_Insert(string T[], string key)    // pass an array by its pointer to the 1st => no need reference
{
    int i = 0;

    do
    {
        int j = hash_function(key, i);
        if(T[j] == "")
        {
            T[j] = key;
            return j;
        }
        else
            i++;
    }
    while(i < 100);

    cout << "Hash table overflow" << endl;
    exit(-1);
}


/* Hash Table Search */
int Hash_Table_Search(string T[], string key)
{
    int i = 0;
    int j;

    do
    {
        j = hash_function(key, i);

        if(T[j] == key)
            return j;
        else
            i++;
    }
    while(T[j] != "" && i < 100);    // must be "AND" here, De-Morgan law

    return -1;
}


/* Hash Table Delete */
void Hash_Table_Delete(string T[], string key)
{
    int j = Hash_Table_Search(T, key);

    if(j == -1)
        cout << "The deleted element is not found!" << endl;
    else
        T[j] = "";
}


/* Hash Table View */
void Hash_Table_View(string T[])
{
    for(int i = 0; i < 100; i++)
        if(T[i] != "")
            cout << "h(k)=" << i << ":   " << T[i] << endl;

    cout << endl;
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
    if(Hash_Table_Search(T, "TQHK") != -1)
        cout << "Found!" << endl;
    else
        cout << "Not Found!" << endl;

    cout << "Search for the element with the key \"TQaH\": " << endl;
    if(Hash_Table_Search(T, "TQaH") != -1)
        cout << "Found!" << endl;
    else
        cout << "Not Found!" << endl;

    return 0;

}

// Huffman code with built-in priority queue
// the vector alone maybe not match ?

#include <iostream>
#include <queue>
#include <map>
#include <string>
using namespace std;

// Huffman tree node
struct Node
{
    char letter;
    int frequency;
    Node *left, *right;
};

// Create a new tree Node
Node* new_node(char letter, int frequency, Node* left, Node* right)
{
    Node* temp = new Node();    // zero initialization, left = right = nullptr;

    temp->letter = letter;
    temp->frequency = frequency;
    temp->left = left;
    temp->right = right;

    return temp;
}

// Comparison function for ordering the queue, just like a function pointer
struct compare
{
    bool operator()(const Node* left, const Node* right) const
    {
        return left->frequency > right->frequency;
    }   /* very clear that the left element has the higher frequency than the right one
           => descending order */
};

// for clean code, smart, meaningful name -> better understanding
bool is_leaf(Node* x)
{
    return (x->left == nullptr) && (x->right == nullptr);    // ? do I need also check the right one ?
}

// Traverse the Huffman tree and get the Huffman codecvt
void Huffman_encode(Node* x, string str, map<char, string>& Huffman_code) // need pass by reference
{
    if(x == nullptr)    // for "aaa" case, go to the end of
        return;         // tree, need to terminate

    // x is a leaf node
    if(is_leaf(x))
        Huffman_code[x->letter] = (str != "") ? str : "0";  /* need for "aaa" case */

    Huffman_encode(x->left, str + "0", Huffman_code);
    Huffman_encode(x->right, str + "1", Huffman_code);
}

// Traverse the Huffman tree and decode the bit string
void Huffman_decode(Node* x, int& string_index, string str)
{
    if(x == nullptr)
        return;

    // x is a leaf node
    if(is_leaf(x))
    {
        cout << x->letter;  // temporary solution, need optimize later
        return;             /* terminate the function */
    }

    string_index++;

    if(str[string_index] == '0')    // go left
        Huffman_decode(x->left, string_index, str);
    else
        Huffman_decode(x->right, string_index, str);
}

// Construct the Huffman tree and make the encode table
void construct_Huffman_tree(string input_text)
{
    // for empty string
    if(input_text == "")
        return;

    // count the frequency of each letter and store it in a map (like a hash table)
    map<char, int> frequency;
    for(char letter : input_text)   // max ảo <=> for(int i = 0; i < input_text.size(), i++)
        frequency[letter]++;

    /* Create a priority queue to store current Nodes of the Huffman tree */
    priority_queue<Node*, vector<Node*>, compare> the_list;
    /* priority_queue in C++ is just a container adaptor, built on top of other containers:
       vector, array or deque => need to explicit declare underlying container here(vector)*/

    // add the node to the priority queue
    for(auto element : frequency)   // traverse the priority queue
        the_list.push(new_node(element.first, element.second, nullptr, nullptr));

    /* Build up the tree from the priority queue */
    while(the_list.size() > 1)
    {
        Node* x = the_list.top();   the_list.pop();
        Node* y = the_list.top();   the_list.pop();

        Node* z = new_node('?', x->frequency + y->frequency, x, y);
        the_list.push(z);
    }   // the problem with vector is that after I sort, something go wrong :{

    // then we have a Huffman tree
    // and the remaining element in the priority queue is the root
    Node* root = the_list.top();

    // Traverse the Huffman tree and store Huffman code in a (hash) table (a map)
    map<char, string> Huffman_code;
    Huffman_encode(root, "", Huffman_code);

    /* Print out the solution */
    cout << "The original string is: " << endl;
    cout << input_text;

    cout << "\nThe Huffman encoding table is: " << endl;
    for(auto element: Huffman_code)
        cout << element.first << "  " << element.second << endl;

    cout << "\nThe encoded bit string is: " << endl;
    string encoded_string;
    for(char letter: input_text)
        encoded_string += Huffman_code[letter];
    cout << encoded_string << endl;


    cout << "\nThe decoded bit string is: " << endl;
    if(is_leaf(root))   // special case: input string contains only 1 letter: a, aa, aaa
    {
        while(root->frequency--)    // need check
            cout << root->letter;
    }
    else
    {
        int string_index = -1;  // must start from -1 because index++ in decode function => string[0]
        while(string_index < (int)input_text.size() - 1)	// index go from 0 to size() - 1
            Huffman_decode(root, string_index, encoded_string);
    }
}

int main(void)
{
    string input_string = "aaabca";
    construct_Huffman_tree(input_string);

    return 0;
}

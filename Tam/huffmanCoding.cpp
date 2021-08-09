#include <iostream>
#include <vector>
#include <string>
#include <map>

// English Alphabet frequency (Concise Oxford Dictionary (9th edition, 1995))
// E   11.1607%		M	3.0129%
// A	8.4966%		H	3.0034%
// R	7.5809%		G	2.4705%
// I	7.5448%		B	2.0720%
// O	7.1635%		F	1.8121%
// T	6.9509%		Y	1.7779%
// N	6.6544%		W	1.2899%
// S	5.7351%		K	1.1016%
// L	5.4893%		V	1.0074%
// C	4.5388%		X	0.2902%
// U	3.6308%		Z	0.2722%
// D	3.3844%		J	0.1965%
// P	3.1671%		Q	0.1962%
// can make a general case but it is not neccessary(because all the encoding is the same for different words)
struct Node
{
    char character;
    int frequency;
    Node *left = nullptr;
    Node *right = nullptr;
    Node(char c, int f)
    {
        this->character = c;
        this->frequency = f;
    }
};

class HuffmanPrefixCode
{
public:
    std::vector<Node *> list;
    std::string plainText;
    std::string characterList;
    std::vector<std::string> encodingList;
    std::map<char, std::string> encodingTable;
    void inputString(std::string plainText)
    {
        this->plainText = plainText;
    }
    void getFrequency()
    {
        for (int i = 0; i < plainText.size(); i++)
        {
            char character = plainText[i];
            bool isExisted = false;
            int index;
            for (int j = 0; j < list.size(); j++)
            {
                if (list[j]->character == character)
                {
                    isExisted = true;
                    index = j;
                    break;
                }
            }
            if (isExisted)
            {
                list[index]->frequency++;
            }
            else
            {
                Node *temp = new Node(character, 1);
                list.push_back(temp);
            }
        }
    }

    void sortList()
    {
        for (int i = 0; i < list.size(); i++)
        {
            for (int j = i + 1; j < list.size(); j++)
            {
                if (list[i]->frequency < list[j]->frequency)
                {
                    std::swap(list[i], list[j]);
                }
            }
        }
    }

    void getCharacterList()
    {
        for (int i = 0; i < list.size(); i++)
        {
            characterList += list[i]->character;
        }
    }
    Node *extractMin()
    {
        int minIndex = list.size() - 1;
        char c = list[minIndex]->character;
        int f = list[minIndex]->frequency;
        Node *min = new Node(c, f);
        min->left = list[minIndex]->left;
        min->right = list[minIndex]->right;
        list.erase(list.end() - 1);
        return min;
    }

    void huffmanEncoding()
    {
        getFrequency();
        sortList();
        getCharacterList();
        while (list.size() > 1)
        {
            Node *x = extractMin();
            Node *y = extractMin();
            int sumFrequency = x->frequency + y->frequency;
            Node *z = new Node('-', sumFrequency);
            z->left = x;
            z->right = y;
            list.push_back(z);
            sortList();
        }
    }

    void printBT(const std::string prefix, Node *node, bool isLeft)
    {
        if (node != nullptr)
        {
            std::cout << prefix;

            std::cout << (isLeft ? "0: " : "1: ");

            // print the value of the node
            std::cout << node->character << std::endl;

            // enter the next tree level - left and right branch
            printBT(prefix + "    ", node->left, true);
            printBT(prefix + "    ", node->right, false);
        }
    }
    void printBT()
    {
        printBT("", list[0], true);
    }

    void getEncoding(const std::string encodingString, Node *node, char c)
    {
        if (node != nullptr)
        {
            if (node->character == c)
            {
                encodingList.push_back(encodingString);
            }
            else
            {
                if (node->left != nullptr)
                {
                    getEncoding(encodingString + "0", node->left, c);
                }
                if (node->right != nullptr)
                {
                    getEncoding(encodingString + "1", node->right, c);
                }
            }
        }
    }
    void encoding()
    {
        huffmanEncoding();
        printBT();
        for (int i = 0; i < characterList.size(); i++)
        {
            getEncoding("", list[0], characterList[i]);
            std::cout << characterList[i] << ": " << encodingList[i] << '\n';
            encodingTable.insert(std::make_pair(characterList[i], encodingList[i]));
        }
    }

    void outputString()
    {
        std::string encoding;
        for (int i = 0; i < plainText.size(); i++)
        {
            encoding = encoding + encodingTable.find(plainText[i])->second;
        }
        std::cout << "Output encoding string: " << encoding << '\n';
    }
};

void test();
int main()
{
    test();
}

void test()
{
    HuffmanPrefixCode hpc;
    hpc.inputString("floccinaucinihilipilification");
    hpc.encoding();
    hpc.outputString();
}
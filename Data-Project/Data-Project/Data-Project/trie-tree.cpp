#include<iostream>
#include<fstream>
using namespace std;

#define a 26
class Node {
public:

	Node* childNodes[a];
	string value;
	bool  End_Word;

	Node()
	{

		for (int i = 0; i < a; i++)
		{
			childNodes[i] = NULL;
		}
		End_Word = false;
	}
};
class Trie_Tree
{
	Node* root;
public:
	Trie_Tree()
	{

		root = new Node;
	}

	Node* insert_key(string value)
	{
		Node* currentNode = root;
		
		for (int i = 0; i < value.size(); i++)
		{
			if (currentNode->childNodes[value[i] - 'a'] == NULL)
			{

				Node* newNode = new Node();
				currentNode->childNodes[value[i] - 'a'] = newNode;
				currentNode->childNodes[value[i] - 'a']->value = value[i];
			}
			currentNode = currentNode->childNodes[value[i] - 'a'];
		}
		currentNode->End_Word = true;
		return root;
	}

	void function(Node* root, string key, string sug[], int& count)
	{
		if (count >= 10)
		{
			return;
		}

		if (root->End_Word == true)
		{
			sug[count] = key;
			count++;
		}

		for (int i = 0; i < 26; i++)
		{
			Node* find = root->childNodes[i];
			if (find != NULL)
			{
				function(find, key + find->value, sug, count);
			}
		}
	}

	void suggestions(string key, string sug[], int& count)
	{
		Node* temp_node = root;
		for (int i = 0; i < key.size(); i++)
		{
			if (temp_node->childNodes[key[i] - 'a'] != NULL)
			{
				temp_node = temp_node->childNodes[key[i] - 'a'];
			}
			else
			{
				return;
			}
		}

		function(temp_node, key, sug, count);
	}

};
int main()
{
	Trie_Tree* obj = new Trie_Tree();
	ifstream read;
	string data;
	
	read.open("outfile.txt");
	while (!read.eof())
	{
		read >> data;
		int n = data.size();
		for (int i = 0; i < n; i++)
		{
			obj->insert_key(data);
		}
	}
	read.close();

	int count = 0;
	string arr[10];

	cout << "Enter the word for suggestion: ";
	cin >> data;

	obj->suggestions(data, arr, count);

	cout << "\n\n\n";
	for (int i = 0; i < count; i++)
	{
		cout << arr[i] << endl;
	}


	return 0;
}
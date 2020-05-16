#include <iostream>
#include <string>
#include <vector>
using namespace std;
class LinkedList
{
	//Simple node class to hold values and the pointer to the next node.
	struct Node
	{
		Node *next;
		string val;
		Node(string v) : next(nullptr), val(v){};
	};
	Node *head;
	int size;

public:
	LinkedList() : head(nullptr), size(0){};
	//Splits the given text  into 80 character segments if needed
	void splitText(vector<string> &strings, string &textToAdd)
	{
		while (textToAdd.length() > 80)
		{
			string newString = textToAdd.substr(0, 80);
			textToAdd = textToAdd.substr(80);
			strings.push_back(newString);
		}
		strings.push_back(textToAdd);
	}
	//Adds text to the end of a linked list. May add multiple lines if needed.
	void insertEnd(string textToAdd)
	{
		vector<string> strings;
		splitText(strings, textToAdd);
		for (string text : strings)
		{
			Node *newNode = new Node(text);
			if (head == nullptr)
			{
				head = newNode;
				size++;
				continue;
			}
			Node *temp = head;
			while (temp->next != nullptr)
			{
				temp = temp->next;
			}
			temp->next = newNode;
			size++;
		}
	}
	void insert(int index, string textToAdd)
	{
		if (index >= size + 2 || index <= 0)
			return;
		vector<string> strings;
		splitText(strings, textToAdd);
		int counter = index - 2;
		for (string text : strings)
		{
			Node *newNode = new Node(text);
			if (head == nullptr)
			{
				head = newNode;
				size++;
				continue;
			}
			Node *temp = head;
			if (index == 1 && counter == -1)
			{
				newNode->next = temp;
				head = newNode;
				size++;
				continue;
			}

			for (int i = 0; i < counter; i++)
			{
				temp = temp->next;
			}
			newNode->next = temp->next;
			temp->next = newNode;
			counter++;
			size++;
		}
	}
	void deleteNode(int index)
	{
		if (index >= size + 1 || index <= 0 || head == nullptr)
			return;
		Node *temp = head;
		Node *beforeTemp = head;
		bool runThroughOnce = false;
		if (index == 1)
		{
			head = temp->next;
			delete temp;
			size--;
			return;
		}
		while (index > 1)
		{
			temp = temp->next;
			if (!runThroughOnce)
			{
				runThroughOnce = true;
			}
			else
			{
				beforeTemp = beforeTemp->next;
			}
			index--;
		}
		beforeTemp->next = temp->next;
		delete temp;
		size--;
		return;
	}
	void edit(int index, string textToAdd)
	{
		if (index >= size + 2 || index <= 0 || head == nullptr)
			return;
		vector<string> strings;
		splitText(strings, textToAdd);
		int counter = index - 1;
		bool edited = false;
		for (string text : strings)
		{
			Node *temp = head;
			for (int i = 0; i < counter; i++)
			{
				temp = temp->next;
			}
			if (!edited)
			{
				temp->val = text;
				edited = true;
			}
			else
			{
				Node *newNode = new Node(text);
				newNode->next = temp->next;
				temp->next = newNode;
				counter++;
				size++;
			}
		}
	}
	void search(string text)
	{ //TODO DO IMPLEMENTATION WITH TEXT BEING OVER 80 CHARS
		bool found = false;
		int line = 1;
		Node *temp = head;
		while (temp != nullptr)
		{
			if (temp->val.find(text) != -1)
			{
				found = true;
				cout << line << " " << temp->val << "\n";
			}
			line++;
			temp = temp->next;
		}

		if (!found)
		{
			cout << "not found"
				 << "\n";
		}
	}
	//Prints the linked list
	void print()
	{
		Node *temp = head;
		int i = 1;
		while (temp != nullptr)
		{
			cout << i++ << " " << temp->val << "\n";
			temp = temp->next;
		}
	}
};
//Finds where the quotations starts, ends, and creates a string that doesn't contain the quotes
string returnStringWithoutQuotes(string &input)
{
	int pos = input.find("\"") + 1;
	int end = input.length() - pos - 1;
	string val = input.substr(pos, end);
	return val;
}
//Gets the number  n from the format insert n "whatever text". Works with multiple digits
int getIndexFromInput(string &input)
{
	int firstPos = -1;
	for (int i = 0; i < input.length(); i++)
	{
		if (isdigit(input[i]) && firstPos == -1)
		{
			firstPos = i;
			continue;
		}
		else if (firstPos != -1 && !isdigit(input[i]))
		{
			return stoi(input.substr(firstPos, i - firstPos));
		}
	}
	if (firstPos != -1)
	{
		return stoi(input.substr(firstPos, input.length()));
	}
	return -1;
}
int main()
{
	LinkedList list;
	string input = "";
	while (getline(cin, input))
	{
		//Get the first word from whatever the user typed in
		string command = input.substr(0, input.find_first_of(" "));
		if (command == "insertEnd")
		{
			list.insertEnd(returnStringWithoutQuotes(input));
		}
		else if (command == "insert")
		{
			int index = getIndexFromInput(input);
			list.insert(index, returnStringWithoutQuotes(input));
		}
		else if (command == "print")
		{
			list.print();
		}
		else if (command == "edit")
		{
			int index = getIndexFromInput(input);
			list.edit(index, returnStringWithoutQuotes(input));
		}
		else if (command == "search")
		{
			list.search(returnStringWithoutQuotes(input));
		}
		else if (command == "delete")
		{
			int index = getIndexFromInput(input);
			list.deleteNode(index);
		}
		if (input == "quit")
		{
			return 0;
		}
	}
	return 0;
}

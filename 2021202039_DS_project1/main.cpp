#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include "Result.h"
#pragma warning (disable:4996)
#define _CRT_SECURE_NO_WARNINGS
#define SOLUTION_H

using namespace std;

void PrintErrorCode(int code) {
	cout << "===============ERROR===============" << endl;
	cout << code << endl;
	cout << "===================================" << endl << endl;
}

void PrintSuccess(string cmd) {
	cout << "===============" << cmd << "=============== " << endl;
	cout << "SUCCESS" << endl;
	cout << "===================================" << endl << endl;
}

class Loaded_List_Node {
public:
	string filename;
	string filedirec;
	int filenum;
	int nodenum;	//for directory node
	//1d linked list
	Loaded_List_Node* next;
	Loaded_List_Node* prev;
	//2d linked list
	Loaded_List_Node* down;
	Loaded_List_Node* up;
};

class Loaded_List {
public:
	Loaded_List() { head = NULL; tail = NULL; phead = NULL; ptail = NULL; nodenum = 0; }
	~Loaded_List();
	Loaded_List_Node* Insert2dLoaded_List_Node(string fname, string fdirec, int fnum);
	void PrintListAfterLOAD();
	void PrintListAfterLOADatLOADTXT();
	int ExistLoaded_List_Node(string fname, string fdirec, int fnum);
	int ExistLoaded_List_Node_FileNum(int fnum);
	Loaded_List_Node* Insert1dLoaded_List_Node(string fname, string fdirec, int fnum);
	Loaded_List_Node* InsertDirecNode(string fdirec);
	Loaded_List_Node* Insert2dLoaded_List_Node_withoutIndex(string fname, string fdirec, int fnum);
	int DeleteFirstNode(string fdirec);
	int Delete2dNode(string fdirec, string fname);
	string LoadedListExists();
	void PrintList();
	void PrintListatPrintTXT();
	void PrintDirectoryFolder();
	void SaveList();
private:
	Loaded_List_Node* head;
	Loaded_List_Node* tail;
	Loaded_List_Node* phead;
	Loaded_List_Node* ptail;
	Loaded_List_Node* dhead;	//directory head
	int nodenum;
};

class Database_BST_Node {
public:
	Database_BST_Node* left;
	Database_BST_Node* right;
	string filename;
	string filedirec;
	int filenum;
};

class Database_BST {
public:
	Database_BST() { root = NULL; leaf = NULL; };
	~Database_BST() {};

	void InsertNode(string fdirec, string fname, int fnum);
	string getFileName(int fnum);
	string getFileDirec(int fnum);
	string PreorderFind(int fnum);
	Database_BST_Node* Preorder(Database_BST_Node* node, int fnum);
	Database_BST_Node* FindMinimum(Database_BST_Node* node);
	Database_BST_Node* DeleteNode(int fnum, Database_BST_Node* node);
	void RemoveNode(int x);
	bool CheckNodeExists(string fdirec, string fname, int fnum);
	bool BSTExists();
	bool CheckNumberExists(int fnum);
	void PrintInorder();
	void Inorder(Database_BST_Node* node);
	void PrintInorder_Print_txt();
	void Inorder_Print_txt(FILE* file, Database_BST_Node* node);
private:
	Database_BST_Node* root;
	Database_BST_Node* leaf;
	int nodenum; //nodenum should be <=300
};

class Manager
{
private:
	// the filepath for the result log
	const char* RESULT_LOG_PATH = "log.txt";


	std::ofstream fout;


public:
	~Manager();
	void Run(const char* filepath);
	void PrintError(Result result);

private:
	Result Load(const char* filepath);

};


//for Queue and Stack
class Node {
public:
	double value;	//data
	Node* next;
	Node() {
		value = 0; next = NULL;
	}
};

//for EDIT 
class Queue {
public:
	Queue() {
		front = rear = NULL;
		counter = 0;
	}
	~Queue() {
		double value;
		while (!Empty()) Dequeue();
	}
	bool Empty() {
		if (counter)	return false;
		else return true;
	}
	void EditEnqueue(double x, int light);
	double Dequeue();
	void DisplayQueue(void);
private:
	Node* front;	//  front node
	Node* rear;		// last node
	double counter;	//number of elements
};


double Queue::Dequeue() {
	double data = front->value;
	if (Empty()) {
		cout << "Error: the queue is empty." << endl;
		return 0;
	}
	else {
		Node* nextNode = front->next;
		delete front;
		front = nextNode;
		counter--;
		return data;
	}
}

void Queue::EditEnqueue(double x, int light) {// calculate the new rear position (circular) 
	Node* newNode = new Node;
	newNode->value = x + (double)light;	//adjust
	if (newNode->value < 0)
		newNode->value = 0;
	else if (newNode->value > 255)
		newNode->value = 255;
	if (front == NULL) {
		front = newNode;
		rear = newNode;
	}
	else {
		rear->next = newNode;
		rear = rear->next;
	}
	// update counter 
	counter++;
	return;
}

class Stack {
public:
	Stack() { head = NULL; }	// constructor
	~Stack() {}	// destructor  
	double Top() {
		if (head == NULL) {
			cout << "Error: the stack is empty." << endl;
			return -1;
		}
		else
			return head->value;
	}
	void Push(double x) {
		Node* newNode = new Node;
		newNode->value = x;
		newNode->next = NULL;
		if (head == NULL) {
			head = newNode;
		}
		else {
			newNode->next = head;
			head = newNode;
		}
	}

	void Pop() {
		if (head == NULL) {
			cout << "Error: the stack is empty." << endl;
			return;
		}
		else {
			//delete
			double top = Top();
			Node* prevNode = NULL;
			Node* currNode = head;
			int currIndex = 1;
			while (currNode && currNode->value != top) {
				prevNode = currNode;
				currNode = currNode->next;
				currIndex++;
			}
			if (currNode) {
				if (prevNode) {
					prevNode->next = currNode->next;
					delete currNode;
				}
				else {
					head = currNode->next;
					delete currNode;
				}
				return;
			}
		}
	}
	void print() {
		Node* currNode = head;
		while (currNode != NULL) {
			cout << currNode->value << "\t";
			currNode = currNode->next;
		}
	}
private:
	Node* head;

};


//insert directory node
Loaded_List_Node* Loaded_List::InsertDirecNode(string fdirec) {
	Loaded_List_Node* currLoaded_List_Node = head;
	Loaded_List_Node* newLoaded_List_Node = new Loaded_List_Node;
	newLoaded_List_Node->filedirec = fdirec;
	newLoaded_List_Node->next = NULL;
	newLoaded_List_Node->prev = NULL;
	newLoaded_List_Node->up = NULL;
	newLoaded_List_Node->down = NULL;
	newLoaded_List_Node->nodenum = 0;
	if (head == NULL)
	{
		head = newLoaded_List_Node;
		return newLoaded_List_Node;
	}
	else {
		while (currLoaded_List_Node->down)
			currLoaded_List_Node = currLoaded_List_Node->down;
	}
	newLoaded_List_Node->down = currLoaded_List_Node->down;
	newLoaded_List_Node->up = currLoaded_List_Node;
	currLoaded_List_Node->down = newLoaded_List_Node;

	//newLoaded_List_Node->up = currLoaded_List_Node;
	//newLoaded_List_Node->down = currLoaded_List_Node->down;
	//currLoaded_List_Node->down = newLoaded_List_Node;
	//currLoaded_List_Node->up = newLoaded_List_Node->up;

	return newLoaded_List_Node;
}

//1d linked list node INSERT for LOAD
Loaded_List_Node* Loaded_List::Insert1dLoaded_List_Node(string fname, string fdirec, int fnum) {
	Loaded_List_Node* currNode = head;
	Loaded_List_Node* DirectoryNode = head;
	while (currNode->next != NULL) {
		currNode = currNode->next;
	}
	Loaded_List_Node* newLoaded_List_Node = new Loaded_List_Node;
	newLoaded_List_Node->filedirec = fdirec;
	newLoaded_List_Node->filename = fname;
	newLoaded_List_Node->filenum = fnum;
	newLoaded_List_Node->next = NULL;
	newLoaded_List_Node->next = currNode->next;
	currNode->next = newLoaded_List_Node;
	newLoaded_List_Node->prev = currNode;
	DirectoryNode->nodenum = DirectoryNode->nodenum + 1;
	return newLoaded_List_Node;
}

//Putting a file in a new directory
Loaded_List_Node* Loaded_List::Insert2dLoaded_List_Node(string fname, string fdirec, int fnum) {
	//find directory
	Loaded_List_Node* currNode = head;
	return currNode;
}

//insert at last (for MODIFY and ADD)
Loaded_List_Node* Loaded_List::Insert2dLoaded_List_Node_withoutIndex(string fname, string fdirec, int fnum) {
	Loaded_List_Node* prevNode = NULL;
	Loaded_List_Node* currLoaded_List_Node = head;
	Loaded_List_Node* DirectoryNode = head;
	//find the right location
	while (currLoaded_List_Node != NULL) {
		if (currLoaded_List_Node->filedirec == fdirec) {
			DirectoryNode = currLoaded_List_Node;
			break;
		}
		currLoaded_List_Node = currLoaded_List_Node->down;
	}
	currLoaded_List_Node = DirectoryNode;
	while (currLoaded_List_Node) {
		prevNode = currLoaded_List_Node;
		currLoaded_List_Node = currLoaded_List_Node->next;
	}
	//insert
	Loaded_List_Node* newLoaded_List_Node = new Loaded_List_Node;
	newLoaded_List_Node->filedirec = fdirec;
	newLoaded_List_Node->filename = fname;
	newLoaded_List_Node->filenum = fnum;
	newLoaded_List_Node->next = NULL;
	prevNode->next = newLoaded_List_Node;
	newLoaded_List_Node->prev = prevNode;
	DirectoryNode->nodenum++;
	return newLoaded_List_Node;
}

//if node number>100 -> remove the first node
int Loaded_List::DeleteFirstNode(string fdirec) {
	Loaded_List_Node* prevLoaded_List_Node = NULL;
	Loaded_List_Node* currLoaded_List_Node = head;
	while (currLoaded_List_Node->filedirec != fdirec) {
		currLoaded_List_Node = currLoaded_List_Node->down;
	}
	Loaded_List_Node* DirectoryNode = currLoaded_List_Node;
	int currIndex = 1;
	currLoaded_List_Node = DirectoryNode->next;
	if (currLoaded_List_Node) {
		DirectoryNode->next = currLoaded_List_Node->next;
		currLoaded_List_Node->next->prev = DirectoryNode;
		delete currLoaded_List_Node;
		DirectoryNode->nodenum = DirectoryNode->nodenum - 1;
		return currIndex;
	}

	return 0;
}

//Print after LOAD
void Loaded_List::PrintListAfterLOAD() {
	cout << "===============LOAD===============" << endl;
	Loaded_List_Node* currLoaded_List_Node = head;
	while (currLoaded_List_Node != NULL) {
		//test print out
	   //if (currLoaded_List_Node->filename == "\0")
	   //	cout << currLoaded_List_Node->filedirec << endl;
	   //else cout << currLoaded_List_Node->filename<<" / " << currLoaded_List_Node->filenum << endl;
		if (currLoaded_List_Node->filename != "\0")
			cout << currLoaded_List_Node->filename << " / " << currLoaded_List_Node->filenum << endl;
		currLoaded_List_Node = currLoaded_List_Node->next;
	}
	cout << "==================================" << endl << endl;
}

//Print after LOAD at log.txt
void Loaded_List::PrintListAfterLOADatLOADTXT() {
	ofstream load_txt;
	load_txt.open("load.txt");
	load_txt << "===============LOAD===============" << endl;
	Loaded_List_Node* currLoaded_List_Node = head;
	while (currLoaded_List_Node != NULL) {
		//test print out
	   //if (currLoaded_List_Node->filename == "\0")
	   //	cout << currLoaded_List_Node->filedirec << endl;
	   //else cout << currLoaded_List_Node->filename<<" / " << currLoaded_List_Node->filenum << endl;
		if (currLoaded_List_Node->filename != "\0")
			load_txt << currLoaded_List_Node->filename << " / " << currLoaded_List_Node->filenum << endl;
		currLoaded_List_Node = currLoaded_List_Node->next;
	}
	load_txt << "==================================" << endl << endl;
	load_txt.close();
}

//Print Whole List
void Loaded_List::PrintList() {
	cout << "===============Print List===============" << endl;
	Loaded_List_Node* DirectoryNode = head;
	Loaded_List_Node* currNode = DirectoryNode;
	while (DirectoryNode != NULL) {
		currNode = DirectoryNode;
		while (currNode != NULL) {
			if (currNode->filename != "\0")
				cout << currNode->filedirec << " / " << currNode->filename << " / " << currNode->filenum << endl;
			currNode = currNode->next;
		}
		cout << endl;
		DirectoryNode = DirectoryNode->down;
	}
	cout << "========================================" << endl << endl;
}

//Print Whole List at Print.txt
void Loaded_List::PrintListatPrintTXT() {
	ofstream print_txt;
	print_txt.open("print.txt");
	print_txt << "===============Print List===============" << endl;
	Loaded_List_Node* DirectoryNode = head;
	Loaded_List_Node* currNode = DirectoryNode;
	while (DirectoryNode != NULL) {
		currNode = DirectoryNode;
		while (currNode != NULL) {
			if (currNode->filename != "\0")
				print_txt << currNode->filedirec << " / " << currNode->filename << " / " << currNode->filenum << endl;
			currNode = currNode->next;
		}
		print_txt << endl;
		DirectoryNode = DirectoryNode->down;
	}
	print_txt << "========================================" << endl << endl;
	print_txt.close();
}

void Loaded_List::PrintDirectoryFolder() {
	cout << "=====Directory Folder======" << endl;
	Loaded_List_Node* currNode = head;
	while (currNode) {
		cout << currNode->filedirec << " " << currNode->nodenum << endl;
		currNode = currNode->down;
	}
	cout << "===============" << endl << endl;
}

//Save Loaded Linked List into .txt file for MOVE
void Loaded_List::SaveList() {
	ofstream LinkedList("LinkedList.txt");
	Loaded_List_Node* DirectoryNode = head;
	Loaded_List_Node* currNode = head;

	//find tail
	while (DirectoryNode != NULL) {
		currNode = DirectoryNode;
		while (currNode != NULL) {
			if (currNode != NULL)
				tail = currNode;
			currNode = currNode->next;
		}
		DirectoryNode = DirectoryNode->down;
	}
	//directory of tail
	DirectoryNode = head;
	while (DirectoryNode->down != NULL)
		DirectoryNode = DirectoryNode->down;

	//print
	currNode = tail;
	while (DirectoryNode != NULL) {
		while (currNode != NULL) {
			if (currNode->filename != "\0")
				LinkedList << currNode->filedirec << "/" << currNode->filename << "/" << currNode->filenum << "/" << endl;
			currNode = currNode->prev;
		}
		DirectoryNode = DirectoryNode->up;
		//find tail of the directory
		currNode = DirectoryNode;
		while (currNode != NULL && currNode->next != NULL)
			currNode = currNode->next;
	}

	LinkedList.close();

}


//destructor
Loaded_List::~Loaded_List() {
	Loaded_List_Node* currNode = head, * nextNode = NULL;
	while (currNode != NULL)
	{
		nextNode = currNode->next;
		// destroy the current node
		delete currNode;
		currNode = nextNode;
	}
}

//Is it a node that already exists? yes:return 1, no:return 0
int Loaded_List::ExistLoaded_List_Node(string fname, string fdirec, int fnum)
{
	Loaded_List_Node* currLoaded_List_Node = head;
	Loaded_List_Node* DirectoryNode = head;
	while (currLoaded_List_Node != NULL) {
		if (currLoaded_List_Node->filedirec == fdirec) {
			DirectoryNode = currLoaded_List_Node;
			break;
		}
		currLoaded_List_Node = currLoaded_List_Node->down;
	}
	currLoaded_List_Node = DirectoryNode->next;
	while (currLoaded_List_Node != NULL) {
		if (currLoaded_List_Node->filename == fname || currLoaded_List_Node->filenum == fnum) {
			return 1;	//the node already exists
		}
		currLoaded_List_Node = currLoaded_List_Node->next;
	}
	return 0;	//the node doesn't exist
}

//Is it fnum that already exists in fdirec? yes:return 1, no:return 0
int Loaded_List::ExistLoaded_List_Node_FileNum(int fnum) {
	Loaded_List_Node* DirectoryNode = head;
	Loaded_List_Node* currNode = DirectoryNode;
	while (DirectoryNode != NULL) {
		currNode = DirectoryNode;
		while (currNode != NULL) {
			if (currNode->filenum == fnum)
				return 1; //the file number already exists
			currNode = currNode->next;
		}
		DirectoryNode = DirectoryNode->down;
	}
	return 0;	//doesn't exist
}


//Does Loaded List Exists?
string Loaded_List::LoadedListExists() {
	string not_exist = "no";
	string exist = "yes";
	Loaded_List_Node* currLoaded_List_Node = head;
	currLoaded_List_Node = currLoaded_List_Node->next;
	if (currLoaded_List_Node == NULL)
		return not_exist;
	else
		return exist;
}

int Loaded_List::Delete2dNode(string fdirec, string fname) {
	Loaded_List_Node* prevNode = NULL;
	Loaded_List_Node* DirectoryNode = head;
	Loaded_List_Node* currNode = head;
	Loaded_List_Node* DeleteNode = NULL;
	int currIndex = 1;
	//find that node
	while (DirectoryNode != NULL) {
		if (DeleteNode != NULL)
			break;
		currNode = DirectoryNode;
		while (currNode != NULL) {
			if (currNode->filedirec == fdirec && currNode->filename == fname) {
				DeleteNode = currNode;
				break;
			}
			prevNode = currNode;
			currNode = currNode->next;
		}
		DirectoryNode = DirectoryNode->down;
	}
	//delete
	if (DeleteNode) {
		if (prevNode) {
			prevNode->next = DeleteNode->next;
			DeleteNode->next->prev = prevNode;
			delete DeleteNode;
			DirectoryNode->up->nodenum = DirectoryNode->up->nodenum - 1;
			return currIndex;
		}
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////

void Database_BST::InsertNode(string fdirec, string fname, int fnum)
{
	Database_BST_Node* node = new Database_BST_Node();
	Database_BST_Node* newNode = nullptr;

	node->filedirec = fdirec;
	node->filename = fname;
	node->filenum = fnum;

	if (root == nullptr)
		root = node;
	else {
		Database_BST_Node* currNode = root;

		while (currNode != nullptr) {
			newNode = currNode;
			if (node->filenum < currNode->filenum)
				currNode = currNode->left;
			else
				currNode = currNode->right;
		}
		//insert
		if (node->filenum < newNode->filenum)
			newNode->left = node;
		else
			newNode->right = node;
	}
}

string Database_BST::getFileDirec(int fnum)
{
	Database_BST_Node* currNode = root;

	while (currNode != nullptr) {
		if (currNode->filenum == fnum) {
			string file = "./" + currNode->filedirec;
			return file;
		}
		else if (currNode->filenum > fnum) {
			currNode = currNode->left;
		}
		else if (currNode->filenum < fnum) {
			currNode = currNode->right;
		}
	}
	return NULL;
}

string Database_BST::getFileName(int fnum)
{
	Database_BST_Node* currNode = root;

	while (currNode != nullptr) {
		if (currNode->filenum == fnum) {
			string file = currNode->filename;
			return file;
		}
		else if (currNode->filenum > fnum) {
			currNode = currNode->left;
		}
		else if (currNode->filenum < fnum) {
			currNode = currNode->right;
		}
	}
	return NULL;
}

string Database_BST::PreorderFind(int fnum)
{
	Database_BST_Node* currNode = Preorder(root, fnum);
	string file = currNode->filedirec + "/" + currNode->filename;
	return file;

}

Database_BST_Node* Database_BST::Preorder(Database_BST_Node* node, int fnum)
{
	if (node == NULL)
		return NULL;
	else {
		if (node->filenum == fnum)
			return node;
		Preorder(node->left, fnum);
		Preorder(node->right, fnum);
	}
}

Database_BST_Node* Database_BST::FindMinimum(Database_BST_Node* node)
{
	if (node == NULL)
		return NULL;
	else if (node->left == NULL)
		return node;
	else
		return FindMinimum(node->right);
}


Database_BST_Node* Database_BST::DeleteNode(int fnum, Database_BST_Node* node)
{
	Database_BST_Node* temp = NULL;

	if (node == NULL)
		return NULL;
	else if (fnum < node->filenum)
		node->left = DeleteNode(fnum, node->left);
	else if (fnum > node->filenum)
		node->right = DeleteNode(fnum, node->right);
	else if (node->left && node->right) {
		node = FindMinimum(node->right);
		node->filenum = temp->filenum;
		node->right = DeleteNode(node->filenum, node->right);
	}
	else {
		temp = node;
		if (node->left == NULL)
			node = node->right;
		else if (node->right == NULL)
			node = node->left;
		delete temp;
	}

	return node;
}

void Database_BST::RemoveNode(int fnum)
{
	root = DeleteNode(fnum, root);
}

bool Database_BST::CheckNodeExists(string fdirec, string fname, int fnum) {
	Database_BST_Node* currNode = root;

	while (currNode != nullptr) {
		if (currNode->filenum > fnum) {
			currNode = currNode->left;
		}
		else if (currNode->filenum < fnum) {
			currNode = currNode->right;
		}
		else if (currNode->filenum == fnum) {
			if (currNode->filedirec == fdirec && currNode->filename == fname)
				return 1;	//exists
		}
	}
	return 0;	//doesn't exist
}

bool Database_BST::CheckNumberExists(int fnum) {
	Database_BST_Node* currNode = root;

	while (currNode != nullptr) {
		if (currNode->filenum > fnum) {
			currNode = currNode->left;
		}
		else if (currNode->filenum < fnum) {
			currNode = currNode->right;
		}
		else if (currNode->filenum == fnum) {
			return 1;	//exist
		}
	}
	return 0;	//doesn't exist
}

void Database_BST::PrintInorder() {
	cout << "==========PRINT==========" << endl << endl;
	Inorder(root);
	cout << endl << "=========================" << endl << endl;
}

void Database_BST::Inorder(Database_BST_Node* node) {
	if (node != NULL) {
		Inorder(node->left);
		cout << node->filedirec << " / " << "\"" << node->filename << "\"" << " / " << node->filenum << endl;
		Inorder(node->right);
	}
}

void Database_BST::PrintInorder_Print_txt() {
	FILE* print_txt = NULL;
	print_txt = fopen("print.txt", "wt");
	fputs("==========PRINT==========\n", print_txt);
	Inorder_Print_txt(print_txt, root);
	fputs("=========================\n", print_txt);
	fclose(print_txt);
}

void Database_BST::Inorder_Print_txt(FILE* file, Database_BST_Node* node) {
	if (node != NULL) {
		Inorder_Print_txt(file, node->left);
		fputs((node->filedirec + " / " + "\"" + node->filename + "\"" + " / " + to_string(node->filenum) + "\n").c_str(), file);
		Inorder_Print_txt(file, node->right);
	}
}

bool Database_BST::BSTExists() {
	if (root != NULL)
		return true;
	else
		return false;
}

int main(int argc, char* argv[]) {

	FILE* command_txt = NULL;

	Loaded_List List;
	Database_BST BST;

	string direc = "img_files";
	List.InsertDirecNode(direc);

	//Variables to Read in Commands
	string filedirectory = "\0";	//for add and modify
	string new_csvfile = "\0";	//for add
	string filename = "\0";	//for modify
	int filenum = 0;	//for modify and select
	string findword = "\0";	//for search
	//for edit
	string input_image_file = "\0";
	string input_image_filedirec = "\0";
	string input_image_filename = "\0";
	string output_image_file = "\0";
	string edit_option = "\0";
	string edit_light_str = "\0";
	int edit_light = 0;	//brightness level

	//READ THE COMMAND AND WRITE LOG
	ofstream log_txt;
	log_txt.open("log.txt");
	char cmd[1024];
	command_txt = fopen("command.txt", "rb");
	//Create Result Directory
	int result_direc = mkdir("Result", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

	if (command_txt == NULL)
	{
		cout << "Unable to open command.txt" << endl;
	}
	else {
		while (!feof(command_txt)) {
			fgets(cmd, 1024, command_txt);
			//LOAD
			if (cmd[0] == 'L' && cmd[1] == 'O' && cmd[2] == 'A' && cmd[3] == 'D')
			{
				FILE* input_csv = NULL;
				char csv_data[1024];
				//Separate 'num' by ',' in csv_data
				string csv_name;
				string csv_num_str;	//variables for reading csv_num
				int csv_num;	//Elements to actually store in a linked list(filenum)

				//reading .csv file
				input_csv = fopen("./img_files/filesnumbers.csv", "r");
				if (input_csv == NULL)
				{
					//load error code
					PrintErrorCode(100);
					log_txt << "===============ERROR===============" << endl;
					log_txt << 100 << endl;
					log_txt << "===================================" << endl << endl;
				}
				else {
					while (!feof(input_csv)) {
						fgets(csv_data, 1024, input_csv);
						//Save to Linked List, Recognize filename and filenumber based on ",/."
						int i = 0;
						while (csv_data[i] != ',') {
							csv_num_str += csv_data[i];
							i++;
						}
						csv_num = stoi(csv_num_str);
						i++;
						while (csv_data[i] != '.') {
							csv_name += csv_data[i];
							i++;
						}
						//print for test
						//cout << "idx = " << idx << " name = " << csv_name << " num = " << csv_num << endl;
						int CheckExistNode = List.ExistLoaded_List_Node(direc, csv_name, csv_num);
						if (CheckExistNode == 0) {
							List.Insert1dLoaded_List_Node(csv_name, direc, csv_num);
						}
						csv_name = "\0";
						csv_num_str = "\0";
						//print for test
						//cout << csv_data << endl;
					}
					List.PrintListAfterLOAD();
					List.PrintListAfterLOADatLOADTXT();
					//copy load.txt to log.txt
					ifstream load_txt;
					load_txt.open("load.txt");
					while (!load_txt.eof()) {
						string load;
						getline(load_txt, load);
						log_txt << load << endl;
					}
				}

				//print for test
				//List.PrintDirectoryFolder();
				fclose(input_csv);
			}
			//ADD
			else if (cmd[0] == 'A' && cmd[1] == 'D' && cmd[2] == 'D') {
				//cin >> filedirectory;
				int i = 0;
				filedirectory = "\0";
				for (i = 4; cmd[i] != ' ' && cmd[i] != '\0'; i++) {
					filedirectory += cmd[i];
				}
				//cin >> new_csvfile;
				int csvfilename_start = i + 1;
				new_csvfile = "\0";
				for (int i = csvfilename_start; cmd[i] != '\0' && cmd[i] != '\n' && cmd[i] != '\r'; i++)
					new_csvfile += cmd[i];
				//print for test
				//cout<<"csv file Directory: "<<filedirectory<<" filename: "<<new_csvfile<<endl;
				try {
					string CheckLoadedListExists = List.LoadedListExists();
					//if we need more factors
					if (filedirectory == "\0" || new_csvfile == "\0") {
						throw filedirectory;
					}
					//if there isn't Loaded List
					else if (CheckLoadedListExists == "no")
						throw CheckLoadedListExists;
					//reading .csv file
					const char* csvfile = new_csvfile.c_str();
					char csv_data[1024];
					//Separate 'num' by ',' in csv_data
					string csv_name;
					string csv_num_str;	//variables for reading csv_num
					int csv_num;	//Elements to actually store in a linked list(filenum)
					FILE* add_csv = NULL;
					add_csv = fopen(csvfile, "r");
					if (add_csv == NULL)
					{
						//cout << "Unable to open " << csvfile << endl << endl;
						PrintErrorCode(200);
						log_txt << "===============ERROR===============" << endl;
						log_txt << 200 << endl;
						log_txt << "===================================" << endl << endl;
					}
					else {
						//insert
						List.InsertDirecNode(filedirectory);
						//print for test
						//List.PrintDirectoryFolder();
						while (!feof(add_csv)) {
							fgets(csv_data, 1024, add_csv);
							//Save to Linked List, Recognize filename and filenumber based on ",/."
							int i = 0;
							while (csv_data[i] != ',') {
								csv_num_str += csv_data[i];
								i++;
							}
							csv_num = stoi(csv_num_str);
							i++;
							while (csv_data[i] != '.') {
								csv_name += csv_data[i];
								i++;
							}
							//print for test
							//cout << "name = " << csv_name << ", num = " << csv_num << ", file directory: "<<filedirectory<<"!"<<endl;
							int CheckExistNode = List.ExistLoaded_List_Node(filedirectory, csv_name, csv_num);
							if (CheckExistNode == 0) {
								//print for test
								//cout<<"NEW NODE"<<endl;
								List.Insert2dLoaded_List_Node_withoutIndex(csv_name, filedirectory, csv_num);
								//List.PrintDirectoryFolder();
								//List.PrintList();
							}
							csv_name = "\0";
							csv_num_str = "\0";
						}
						//print for test
						//cout<<"******************ADD"<<endl;
						//List.PrintDirectoryFolder();
						//List.PrintList();
						PrintSuccess("ADD");
						//log_txt
						log_txt << "================ADD================ " << endl;
						log_txt << "SUCCESS" << endl;
						log_txt << "===================================" << endl << endl;
						//List.PrintDirectoryFolder();
						fclose(add_csv);
					}

				}
				catch (string error) {
					cout << "===============ERROR===============" << endl;
					cout << "200" << endl;
					cout << "===================================" << endl;
					log_txt << "===============ERROR===============" << endl;
					log_txt << "200" << endl;
					log_txt << "===================================" << endl;
				}
			}
			//MODIFY
			else if (cmd[0] == 'M' && cmd[1] == 'O' && cmd[2] == 'D' && cmd[3] == 'I' && cmd[4] == 'F' && cmd[5] == 'Y') {
				try {
					//reading file directory, file name, file number
					string fdirec, fname, fnum;
					int fnum_int;
					int i;
					for (i = 7; cmd[i] != ' ' && cmd[i] != '\0' && cmd[i] != '"'; i++)
						fdirec += cmd[i];
					if (fdirec == "\0")
						throw fdirec;
					while (cmd[i] != '"')
						i++;
					int start_filename = i + 1;
					for (i = start_filename; cmd[i] != '"' && cmd[i] != '\0'; i++)
						fname += cmd[i];
					if (fname == "\0")
						throw fname;
					for (i = i + 2; cmd[i] != '\0'; i++)
						fnum += cmd[i];
					if (fnum == "\0")
						throw fnum;
					else
						fnum_int = stoi(fnum);
					//print for testing
					//cout << fdirec << " / " << fname << " / " << fnum << endl;
					int CheckExists = List.ExistLoaded_List_Node(fname, fdirec, fnum_int);
					int CheckExists_filenum = List.ExistLoaded_List_Node_FileNum(fnum_int);
					if (CheckExists_filenum == 0) {
						if (CheckExists == 1) {
							List.Delete2dNode(fdirec, fname);
							List.Insert2dLoaded_List_Node_withoutIndex(fname, fdirec, fnum_int);
							PrintSuccess("MODIFY");
							//log_txt
							log_txt << "===============MODIFY============== " << endl;
							log_txt << "SUCCESS" << endl;
							log_txt << "===================================" << endl << endl;
							//print for test
							//List.PrintList();
						}
						else if (CheckExists == 0) {
							PrintErrorCode(300);
							log_txt << "===============ERROR===============" << endl;
							log_txt << 300 << endl;
							log_txt << "===================================" << endl << endl;
						}
					}
					else {
						PrintErrorCode(300);
						log_txt << "===============ERROR===============" << endl;
						log_txt << 300 << endl;
						log_txt << "===================================" << endl << endl;
					}
				}
				catch (string error) {
					PrintErrorCode(300);
					log_txt << "===============ERROR===============" << endl;
					log_txt << 300 << endl;
					log_txt << "===================================" << endl << endl;
				}

			}
			//MOVE
			else if (cmd[0] == 'M' && cmd[1] == 'O' && cmd[2] == 'V' && cmd[3] == 'E') {
				List.SaveList();	//save List into .txt file
				FILE* input_list = NULL;
				char list_data[1024];
				//Separate by '/'
				string node_direc;
				string node_name;
				string node_num_str;	//variables for reading node_num
				int node_num;	//Elements to actually store in BST

				//Read file
				input_list = fopen("LinkedList.txt", "r");
				if (input_list == NULL)
				{
					PrintErrorCode(400);
					log_txt << "===============ERROR===============" << endl;
					log_txt << 400 << endl;
					log_txt << "===================================" << endl << endl;
				}
				else {
					while (!feof(input_list)) {
						fgets(list_data, 1024, input_list);
						//Save to Linked List, Recognize filename and filenumber based on ",/."
						int i = 0;
						while (list_data[i] != '/' && list_data[i] != '\n' && list_data[i] != '\r') {
							node_direc += list_data[i];
							i++;
						}
						i++;
						while (list_data[i] != '/' && list_data[i] != '\n' && list_data[i] != '\r') {
							node_name += list_data[i];
							i++;
						}
						i++;
						while (list_data[i] != '/' && list_data[i] != '\n' && list_data[i] != '\r') {
							node_num_str += list_data[i];
							i++;
						}
						node_num = stoi(node_num_str);	//string to int
						if (node_name != "\0" && node_num_str != "\0") {
							//print for test
							//cout << "direc: " << node_direc << " name: " << node_name << " num: " << node_num << endl;
							bool CheckExistNode = BST.CheckNodeExists(node_direc, node_name, node_num);
							if (CheckExistNode == false) {
								BST.InsertNode(node_direc, node_name, node_num);
							}
						}
						//reset variables
						node_direc = "\0";
						node_name = "\0";
						node_num_str = "\0";
					}
					fclose(input_list);
					PrintSuccess("MOVE");
					//log_txt
					log_txt << "===============MOVE================ " << endl;
					log_txt << "SUCCESS" << endl;
					log_txt << "===================================" << endl << endl;
					//print for test
					//List.PrintList();
					//List.PrintDirectoryFolder();
					//List.PrintListatPrintTXT();
				}
			}
			//PRINT
			else if (cmd[0] == 'P' && cmd[1] == 'R' && cmd[2] == 'I' && cmd[3] == 'N' && cmd[4] == 'T') {
				//List.PrintListatPrintTXT();
				bool BSTExist = BST.BSTExists();	//Is there BSt?
				if (BSTExist == true) {
					BST.PrintInorder();
					BST.PrintInorder_Print_txt();
					//copy print.txt to log.txt
					ifstream print_txt;
					print_txt.open("print.txt");
					while (!print_txt.eof()) {
						string print;
						getline(print_txt, print);
						log_txt << print << endl;
					}
				}
				else {
					PrintErrorCode(500);
					log_txt << "===============ERROR===============" << endl;
					log_txt << 500 << endl;
					log_txt << "===================================" << endl << endl;
				}
			}
			//SEARCH
			else if (cmd[0] == 'S' && cmd[1] == 'E' && cmd[2] == 'A' && cmd[3] == 'R' && cmd[4] == 'C' && cmd[5] == 'H') {
				//cin>>filename;
				filename = "\0";
				int i = 0;
				while (cmd[i] != '\"')
					i++;
				i++;
				while (cmd[i] != '\"' && cmd[i] != '\n' && cmd[i] != '\0' && cmd[i] != '\r') {
					filename += cmd[i];
					i++;
				}
				//print for test
				//cout << filename << endl;

			}
			//SELECT
			else if (cmd[0] == 'S' && cmd[1] == 'E' && cmd[2] == 'L' && cmd[3] == 'E' && cmd[4] == 'C' && cmd[5] == 'T') {
				string filenumber_str = "\0";
				input_image_filedirec = "\0";
				input_image_filename = "\0";
				int i = 6;
				while (cmd[i] != '\0' && cmd[i] != '\n' && cmd[i] != '\r') {
					filenumber_str += cmd[i];
					i++;
				}
				//if number isn't entered
				if (filenumber_str == "\0") {
					PrintErrorCode(700);
					log_txt << "===============ERROR===============" << endl;
					log_txt << 700 << endl;
					log_txt << "===================================" << endl << endl;
				}
				int filenumber = stoi(filenumber_str);	//string -> int
				//print for test
				//cout << "num: " << filenumber << endl;
				if (BST.CheckNumberExists(filenumber) == false) {
					PrintErrorCode(700);
					log_txt << "===============ERROR===============" << endl;
					log_txt << 700 << endl;
					log_txt << "===================================" << endl << endl;
				}
				else {
					input_image_filedirec = BST.getFileDirec(filenumber);
					input_image_filename = BST.getFileName(filenumber);
					//print for test
					//cout << "input_image_filedirec: " << input_image_filedirec << " input_image_filename: " << input_image_filename << endl;
					PrintSuccess("SELECT");
					//log_txt
					log_txt << "==============SELECT=============== " << endl;
					log_txt << "SUCCESS" << endl;
					log_txt << "===================================" << endl << endl;
				}
			}
			//EDIT
			else if (cmd[0] == 'E' && cmd[1] == 'D' && cmd[2] == 'I' && cmd[3] == 'T') {
				edit_option = "\0";
				edit_light_str = "\0";
				edit_light = 0;
				int i = 5;
				//cin>>edit option(-f, -l,-r)
				while (cmd[i] != '\0' && cmd[i] != '\n' && cmd[i] != '\r' && cmd[i] != ' ') {
					edit_option += cmd[i];
					i++;
				}
				if (edit_option == "\0") {
					PrintErrorCode(800);
					log_txt << "===============ERROR===============" << endl;
					log_txt << 800 << endl;
					log_txt << "===================================" << endl << endl;
				}
				//cin>>edit_light when edit option is "-l"
				if (edit_option == "-l") {
					while (cmd[i] != '\0' && cmd[i] != '\n' && cmd[i] != '\r') {
						edit_light_str += cmd[i];
						i++;
					}
					if (edit_light_str == "\0") {
						PrintErrorCode(800);
						log_txt << "===============ERROR===============" << endl;
						log_txt << 800 << endl;
						log_txt << "===================================" << endl << endl;
					}
					else edit_light = stoi(edit_light_str);
				}
				//print for test
				//cout << "edit option: " << edit_option <<"/"<< endl;
				FILE* input_file, * output_file = NULL;
				int width = 256, height = 256;
				unsigned char input_data[256][256];
				unsigned char output_data[256][256];
				//reading .RAW file
				input_image_file = input_image_filedirec + "/" + input_image_filename + ".RAW";
				//print for test
				//cout << "input_image_file: " << input_image_file << endl;
				const char* input_image = input_image_file.c_str();
				input_file = fopen(input_image, "rb");
				if (input_file == NULL)
				{
					cout << input_image_file << " File not found!!" << endl;
				}
				fread(input_data, sizeof(unsigned char), width * height, input_file);
				if (edit_option == "-r")	//resize
				{
					unsigned char output_data[128][128];
					//save input images into resized output images
					for (int i = 0; i < height / 2; i++) {
						for (int j = 0; j < width / 2; j++) {
							output_data[i][j] = (input_data[(2 * i - 1)][(2 * j - 1)] + input_data[(2 * i - 1)][(2 * j)] + input_data[(2 * i)][(2 * j - 1)] + input_data[2 * i][2 * j]) / 4;
						}
					}
					//save output images
					output_image_file = "./Result/" + input_image_filename + "_resized.RAW";
					PrintSuccess("EDIT");
					//log_txt
					log_txt << "==============EDIT=============== " << endl;
					log_txt << "SUCCESS" << endl;
					log_txt << "==================================" << endl << endl;
					//save output images
					const char* output_image = output_image_file.c_str();
					output_file = fopen(output_image, "wb");
					fwrite(output_data, sizeof(unsigned char), width / 2 * height / 2, output_file);
					fclose(input_file);
					fclose(output_file);

				}
				else if (edit_option == "-l") {
					Queue q;
					unsigned char output_data[256][256];
					for (int i = 0; i < height; i++) {
						for (int j = 0; j < width; j++) {
							//queue push
							q.EditEnqueue(input_data[i][j], edit_light);
						}
					}
					for (int i = 0; i < height; i++) {
						for (int j = 0; j < width; j++) {
							//queue pop
							output_data[i][j] = q.Dequeue();
						}
					}
					PrintSuccess("EDIT");
					//log_txt
					log_txt << "==============EDIT=============== " << endl;
					log_txt << "SUCCESS" << endl;
					log_txt << "==================================" << endl << endl;
					//save output images
					output_image_file = "./Result/" + input_image_filename + "_adjusted.RAW";
					const char* output_image = output_image_file.c_str();
					output_file = fopen(output_image, "wb");
					fwrite(output_data, sizeof(unsigned char), width * height, output_file);
					fclose(input_file);
					fclose(output_file);
				}
				else if (edit_option == "-f") {
					unsigned char output_data[256][256];
					Stack s;
					for (int i = 0; i < height; i++) {
						for (int j = 0; j < width; j++) {
							//stack push
							s.Push((double)input_data[i][j]);
						}
					}
					//print for test
					//s.print();
					for (int i = 0; i < height; i++) {
						for (int j = 0; j < width; j++) {
							//stack pop
							output_data[i][j] = s.Top();
							s.Pop();
						}
					}
					PrintSuccess("EDIT");
					//log_txt
					log_txt << "==============EDIT=============== " << endl;
					log_txt << "SUCCESS" << endl;
					log_txt << "==================================" << endl << endl;
					//save output images
					output_image_file = "./Result/" + input_image_filename + "_flipped.RAW";
					const char* output_image = output_image_file.c_str();
					output_file = fopen(output_image, "wb");
					fwrite(output_data, sizeof(unsigned char), width * height, output_file);
					fclose(input_file);
					fclose(output_file);
				}

				//fclose(input_file);
				//fclose(output_file);
			}
			//EXIT
			else if (cmd[0] == 'E' && cmd[1] == 'X' && cmd[2] == 'I' && cmd[3] == 'T') {
				PrintSuccess("EXIT");
				//log_txt
				log_txt << "===============EXIT================ " << endl;
				log_txt << "SUCCESS" << endl;
				log_txt << "===================================" << endl << endl;
				//close the files
				fclose(command_txt);
				log_txt.close();
				break;
			}
			else {
				PrintErrorCode(777);	//Invalid command
				log_txt << "===============ERROR===============" << endl;
				log_txt << 777 << endl;
				log_txt << "===================================" << endl << endl;
			}
		}
	}

	return 0;



}
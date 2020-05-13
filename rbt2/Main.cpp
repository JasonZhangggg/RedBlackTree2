/*
 * Jason Zhang
 * RBT
 * 4/20/2020
 */

#include <iostream>
#include "Node.h"
#include <fstream>
#include <cstring>
#include <cstdlib>

using namespace std;
void rotateLeft(Node*&, Node*&);
void rotateRight(Node*&, Node*&);
void addNode(Node*&, Node*);
void insert(Node*&, int);
void case1(Node*&);
void case2();
void case3(Node*&, Node* &);
void case4(Node*&, Node* &);
void case4Step2(Node *&, Node*&);
void repairTree(Node*&, Node*&);
void traverse(Node*, int);
void replaceNode(Node* &, Node*&);
void DeleteOneChild(Node*&);
void DeleteCase1(Node*&);
void DeleteCase2(Node*&);
void DeleteCase3(Node*&);
void DeleteCase4(Node*&);
void DeleteCase5(Node*&);
void DeleteCase6(Node*&);
Node* search(Node*, int);
void DeleteNode(Node*&, Node*&);
Node* getRoot(Node*);
Node* getSuc(Node*);
int main(){
	//declare head
	Node* head = NULL;
	char inType;
	char input[100];
	//ask for input type

	cout<<"Type 1 for file input and 2 for manual input"<<endl;
	cin>>inType;
	cin.ignore();
	//if file input
	if(inType == '1'){
		//read from file
		cout<<"Input the file name"<<endl;
		char fileName[100];
		cin.getline(fileName, sizeof(fileName));
		ifstream fileStream;
		fileStream.open(fileName);
		if(fileStream){
			fileStream.getline(input, sizeof(input));
		}
		//if file not found
		else{
			cout<<"File does not exist"<<endl;
		}
	}
	//manual input	
	else if(inType == '2'){
		cout<<"Enter the array split by spaces"<<endl;
		cin.getline(input, 100);
	}
	//split by space
	char* list = strtok(input, " ");
	while(list){
		//add node
		insert(head, atoi(list));
		list = strtok(NULL, " ");
	}
	while(true){
		cout<<"Type ADD to add, PRINT to print, SEARCH to search for a value, QUIT to quit, and DELETE to delete a node"<<endl;
		char* input = new char();
		cin.getline(input, sizeof(input));
		for(int i = 0; i<sizeof(input); i++){
			input[i] = toupper(input[i]);
		}
		//Add a node
		if(strcmp(input, "ADD") == 0){
			int val;
			cout<<"Enter the val you want to add: ";
			cin>>val;
			cin.ignore();
			insert(head, val);
		}	
		//display tree
		else if(strcmp(input, "PRINT") == 0){
			traverse(head, 0);
		}
		else if(strcmp(input, "SEARCH") == 0){
			int val;
			cout<<"Enter the val you want to search for: ";
			cin>>val;
			cin.ignore();
			if(search(head, val) == NULL){
				cout<<"The element was not found"<<endl;
			}
			else{
				cout<<"The element was found"<<endl;
			}
		}
		else if(strcmp(input, "DELETE") == 0){
			int val;
			cout<<"Enter the val you want to delete: ";
			cin>>val;
			cin.ignore();
			Node* n = search(head, val);
			if(n == NULL){
				cout<<"The element was not found"<<endl;
			}
			else{
				DeleteNode(head, n);
			}
		}
		else if(strcmp(input, "QUIT") == 0){
			return 0;
		}
		cout<<endl<<"__________________________________________________________________________________________________"<<endl;
	}
}
void insert(Node* &head, int val){
	//create a node with the value and add it to the tree
	Node* n = new Node(val);
	addNode(head, n);
	//repair the tree
	repairTree(n, head);
}
void addNode(Node* &head, Node* n){
	//if head is NULL declare it
	if(head == NULL){
		head = n;
		return;
	}
	//the input val is larger then head
	if(head->getVal()<n->getVal()){
		//if we are at the base of the tree, add the node to the right of the current node
		if(head->getRight() == NULL){
			head->setRight(n);
			head->getRight()->setParent(head);
			return;
		}
		//else recursivly traverse right
		else{
			Node* right = head->getRight();
			addNode(right, n);
		}	
	}
	//if input val is smaller then head
	else{
		//if we are at the end of the tree, add the node to the left of the current node
		if(head->getLeft() == NULL){
			head->setLeft(n);
			head->getLeft()->setParent(head);
			return;
		}
		//otherwise traverse left
		else{
			Node* left = head->getLeft();
			addNode(left, n);
		}
	}
}
//psudo code from https://en.wikipedia.org/wiki/Red-black_tree
void repairTree(Node* &n, Node* &head){
	//if it is the root case
	if(n->getParent() == NULL){
		case1(n);
	}
	//if the parent is red, do nothing
	else if(n->getParent()->getColor() == 2){
		case2();	
	}
	//if the uncle is red
	else if (n->getUncle() != NULL && n->getUncle()->getColor() == 1){
		case3(n, head);
	}
	//otherwise
	else{
		case4(n, head);
	}

}

//set color to reed
void case1(Node* &n){
	n->setColor(2);
}
void case2(){
	return;
}
void case3(Node* &n, Node* &head){
	//set color of parent an uncle to black
	n->getParent()->setColor(2);
	n->getUncle()->setColor(2);
	//set color of grandparent to red
	n->getGp()->setColor(1);
	//rerun repair tree with grandparent
	Node* gp = n->getGp();
	repairTree(gp, head);
}
void case4(Node* &n, Node* &head){
	Node* p = n->getParent();
	Node* g = n->getGp();
	//if the current node is on the right of parent and the parent is on the left of gp
	if (n == p->getRight() && p == g->getLeft()) {
		//rotate tree left
		p->rotateLeft();
		cout<<"test"<<endl;
		n = n->getLeft();
	} 
	//if the current node is on the left of parent and the parent is on the right of gp
	else if (n == p->getLeft() && p == g->getRight()) {
		p->rotateRight();
		n = n->getRight();
	}
	case4Step2(n, head);
}
void case4Step2(Node* &n, Node* &head){
	Node* p = n->getParent();
	Node* g = n->getGp();
	//if the node is on the left
	if (n == p->getLeft()) {
		//rotate right
		g->rotateRight();
	} 
	//if the node is on the right
	else {
		//rotate left
		g->rotateLeft();
	}
	//if it is the root case, set head to parent
	if(g == head) head = p;
	//set parent color to black and grandparent color to red
	p->setColor(2);
	g->setColor(1);
}

//infix traversal
void traverse(Node* head, int depth){
	//recursivly go to the right branch
	if(head == NULL)return;
	if(head->getRight() != NULL) traverse(head->getRight(), depth+1);
	//print out space for formating
	for (int i = 0; i < depth; i++) cout << "      ";
	//depending on the color, print a different color
	if(head->getColor() == 1)cout <<"\033[1;31m"<<head->getVal()<<"\033[0m"<<endl;
	else cout<<"\033[1;30m"<<head->getVal()<<"\033[0m"<<endl;
	//recursivly go to the left branch
	if(head->getLeft() != NULL) traverse(head->getLeft(), depth+1);
}
Node* search(Node* h, int key){
	//if we found the key, return the node
	if(h == NULL || h->getVal() == key){
		return h;
	}
	//if the key is less then the val, search left
	if(key<h->getVal()){
		Node* l = h->getLeft();
		return search(l, key);
	}
	//if the key is greater then the val, search right
	else if(key > h->getVal()){
		Node* r = h->getRight();
		return search(r, key);
	}

}
void DeleteNode(Node*& h, Node* &n){
	//if it is the root case
	if(h == n && n->getLeft() == NULL && n->getRight() == NULL){
		delete n;
		n = NULL;
		return;
	}
	//if there are 2 childern
	else if(n->getLeft() != NULL && n->getRight() != NULL){
		Node* left = n->getLeft();
		left = getSuc(left);
		n->setVal(left->getVal());
		DeleteOneChild(left);
		return;

	}
	DeleteOneChild(n);

}
void replaceNode(Node* &n, Node* &child){
	child->setParent(n->getParent());
	if(n->getParent() == NULL){
		n = child;
	}
	else if(n == n->getParent()->getLeft()){
		n->getParent()->setLeft(child);
	} else{
		n->getParent()->setRight(child);
	}
}
void DeleteOneChild(Node* &n){
	Node* child;
	if(n->getRight() == NULL){
		child = n->getLeft();
	}
	else{
		child = n->getRight();
	}
	if(child == NULL){
		child = new Node(-1);
		child->setColor(2);
	}
	replaceNode(n, child);
	if(n->getColor() == 2){
		if(child->getColor() == 1){
			child->setColor(2);
		}
		else{
			DeleteCase1(child);
		}
	}
	if(child->getVal() == -1){
		if(child->getParent() != NULL){
			if(child == child->getParent()->getLeft()){
				child->getParent()->setLeft(NULL);
			}
			else{
				child->getParent()->setRight(NULL);
			}
			cout<<"bad"<<endl;
		}
	}
}
Node* getRoot(Node* n){
	if(n->getParent() != NULL){
		getRoot(n->getParent());
	}
	return n;
}
void DeleteCase1(Node* &n){
	if(n->getParent() != NULL){
		DeleteCase2(n);
	}
}
void DeleteCase2(Node* &n){
	Node* s = n->getSibling();
	if(s->getColor() == 1){
		n->getParent()->setColor(1);
		s->setColor(2);
		Node* p = n->getParent();
		if(n == n->getParent()->getLeft()){
			n->getParent()->rotateLeft();
		}
		else{
			n->getParent()->rotateRight();
		}
	}
	DeleteCase3(n);
}
void DeleteCase3(Node* &n){
	Node* s = n->getSibling();
	if((n->getParent()->getColor() == 2) && (s->getColor() == 2) && (s->getLeft()->getColor() == 2) && (s->getRight()->getColor() == 2)) {
		s->setColor(1);
		Node* p = n->getParent();
		DeleteCase1(p);
	}
	else{
		DeleteCase4(n);
	}
}
void DeleteCase4(Node* &n){
	Node* s = n->getSibling();
	if((n->getParent()->getColor() == 1) && (s->getColor() == 2) && (s->getLeft()->getColor() == 2) && (s->getRight()->getColor() == 2)){
		s->setColor(1);
		n->getParent()->setColor(2);
	}
	else{
		DeleteCase5(n);
	}
}
void DeleteCase5(Node* &n){
	cout<<n->getSibling()->getRight()->getColor()<<endl;
	cout<<n->getSibling()->getLeft()->getColor()<<endl;
	Node* s = n->getSibling();
	if(s->getColor() == 2){
		if((n == n->getParent()->getLeft()) && (s->getRight()->getColor() == 2) && s->getLeft()->getColor() == 1){
			s->setColor(1);
			s->getLeft()->setColor(2);
			s->rotateRight();
		}
		else if((n==n->getParent()->getRight()) && (s->getLeft()->getColor() == 2) && (s->getRight()->getColor() == 2)){
			s->setColor(1);
			s->getRight()->setColor(2);
			s->rotateLeft();
		}
	}	
	DeleteCase6(n);
}
void DeleteCase6(Node* &n){
	Node* s = n->getSibling();
	s->setColor(n->getParent()->getColor());
	n->getParent()->setColor(2);
	if(n == n->getParent()->getLeft()){
		s->getRight()->setColor(2);
		n->getParent()->rotateLeft();

	}
	else{
		s->getLeft()->setColor(2);
		n->getParent()->rotateRight();
	}

}
Node* getSuc(Node* head){
	if(head->getRight() == NULL){
		return head;
	}
	getSuc(head->getRight());
}

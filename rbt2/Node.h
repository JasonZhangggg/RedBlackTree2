/*
   Jason Zhang
   RBT
   4/21/2020
   */

#include <iostream>
#include <cstring>

#ifndef NODE_H
#define NODE_H

using namespace std;

class Node{
	public:
		//constructor
		Node(int);
		//get the val
		int getVal();
		void setVal(int);
		//get the node to the right
		Node* getRight();
		//get the node to the left
		Node* getLeft();
		Node* getParent();
		//set the node to the right
		void setRight(Node*);
		//set the node to the left
		void setLeft(Node*);
		//set parent
		void setParent(Node*);
		//set color
		void setColor(int);
		//get color
		int getColor();
		//get grandparent
		Node* getGp();
		//get sibling
		Node* getSibling();
		//get uncle
		Node* getUncle();
		//rotate left and right
		void rotateLeft();
		void rotateRight();
		//deconstructor
		~Node();
	private:
		//right and left node
		Node* right;
		Node* left;
		Node* parent;
		//1 if node is red 2 if node is black
		int color;
		//val of node
		int val;	
};
#endif

#pragma once
#include <iostream>
using namespace std;

struct listType {
	int cartId;
	int itemCount;
	int enterQTime;
	int exitQTime;
};
struct Node {
	listType data;
	Node* nextPtr;
};

class LinkedList {
private:
	Node* headPtr;

public:
	static int listCount;

	LinkedList() {
		headPtr = nullptr;
	}

	void addElement(listType item) {                //add cart information to the list (list should probably be ordered)
		Node* newNode = new Node();
		newNode->data = item;

		if (headPtr == nullptr || headPtr->data.enterQTime >= item.enterQTime) {
			newNode->nextPtr = headPtr;
			headPtr = newNode;
		}
		else {
			Node* current = headPtr;
			while (current->nextPtr != nullptr && current->nextPtr->data.enterQTime < item.enterQTime) {
				current = current->nextPtr;
			}

			newNode->nextPtr = current->nextPtr;
			current->nextPtr = newNode;
		}
		listCount++;
	}
	listType peek() {
		return headPtr->data;
	}
	void delElement() {              
		if (headPtr == nullptr) {
			return;
		}
		Node* temp = headPtr;
		headPtr = headPtr->nextPtr;
		delete temp;
		
		listCount--;
	}
	void printList() {
		if (headPtr == nullptr) {
			cout << "List is empty" << endl;
			return;
		}
		Node* current = headPtr;

		while (current != nullptr) {
			cout << "Cart ID: " << current->data.cartId << endl;
			cout << "Item Count: " << current->data.itemCount << endl;
			cout << "Enter Queue Time: " << current->data.enterQTime << endl;
			cout << "Exit Queue Time: " << current->data.exitQTime << endl;

			current = current->nextPtr;
		}
	}
	bool listIsEmpty() {
		return headPtr == nullptr;
	}
};

int LinkedList::listCount = 0;
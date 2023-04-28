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

    LinkedList();
    void addElement(listType item);
    listType peek();
    void delElement();
    void printList();
    bool listIsEmpty();
};
#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

struct queueData {
	int queueCount = 0;			//current queue length
	int totalIdleTime = 0;		//if queueCount == 0; this is incremented
	int totalOverTime = 0;		//increment if current time > 720 & there are people in line
	int maxQueueLength = 0;		//if current queueCount>maxQueueLength, reset
	int currItems = 0;			//update as customers are added/removed from queue
	int totalItems = 0;			//running count of items purchased
	vector<int> cartList;		//running list of carts helped
};

struct queueNodeData {
	int timeAvailable;			//clock time when current
								//customer is dequeued
	int itemCount;				//the number of items for
    							//current customer
};

struct queueNode {
	queueNodeData data;
	queueNode* nextPtr;
};

class CheckoutQueue {
private:
	queueNode* front;
	queueNode* rear;

public:
	CheckoutQueue() {
		front = nullptr;
		rear = nullptr;
	}
	void enQueue(queueNodeData item){      //add the queueNodeData item to the end of the queue
		queueNode* newNode = new queueNode;
		newNode->data = item;
		newNode->nextPtr = nullptr;

		if (rear == nullptr) {
			front = newNode;
		}
		else {
			rear->nextPtr = newNode;
		}
		rear = newNode;
	}
	queueNodeData deQueue() {            //remove a queueNodeData item from the front of the queue
		if (front == nullptr) {
			cout << "Error: queue is empty" << endl;
			return { 0,0 };
		}

		queueNode* temp = front;
		queueNodeData item = front->data;

		front = front->nextPtr;
		delete temp;

		if (front == nullptr) {
			rear = nullptr;
		}
		return item;
	}
	queueNodeData peek() {                //return the contents of the front of the queue (but do not remove)
		if (front == nullptr) {
			cout << "Error: queue is empty" << endl;
			return { 0,0 };
		}

		return front->data;
	}
	bool queueEmpty() {                  //return true if the queue is empty (front = nullptr?), false otherwise
		return front == nullptr;
	}

	void printQueue() {
		if (front == nullptr) {
			cout << "Queue is empty" << endl;
		}

		queueNode* current = front;
		cout << left << setw(15) << "Time Available " << "Item Count" << endl;

		while (current != nullptr) {
			cout << left << setw(15) << current->data.timeAvailable << current->data.itemCount << endl;
			current = current->nextPtr;
		}
	}
};
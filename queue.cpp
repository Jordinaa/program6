#include "queue.h"

CheckoutQueue::CheckoutQueue() {
    front = nullptr;
    rear = nullptr;
}

void CheckoutQueue::enQueue(queueNodeData item) {
    queueNode* newNode = new queueNode;
    newNode->data = item;
    newNode->nextPtr = nullptr;

    if (rear == nullptr) {
        front = newNode;
    } else {
        rear->nextPtr = newNode;
    }
    rear = newNode;
}

queueNodeData CheckoutQueue::deQueue() {
    if (front == nullptr) {
        cout << "Error: queue is empty" << endl;
        return { 0, 0 };
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

queueNodeData CheckoutQueue::peek() {
    if (front == nullptr) {
        cout << "Error: queue is empty" << endl;
        return { 0, 0 };
    }

    return front->data;
}

bool CheckoutQueue::queueEmpty() {
    return front == nullptr;
}

void CheckoutQueue::printQueue() {
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

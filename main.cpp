#include <iostream>
#include <vector>
#include "queue.h"
#include "linkedlist.h"

using namespace std;

int main() {
    srand(time(0));

    int numCheckouts;
    int cartId = 0;

    cout << "Enter the number of checkout lines (1-10): ";
    cin >> numCheckouts;

    while (numCheckouts < 1 || numCheckouts > 10) {
        cout << "Invalid input. Please enter a number between 1 and 10: ";
        cin >> numCheckouts;
    }

    LinkedList store;
    vector<CheckoutQueue> checkouts(numCheckouts);
    vector<queueData> checkoutData(numCheckouts);

    for (int currentTime = 0; currentTime <= 720; ++currentTime) {
        // 1. Decide how many customers arrived at the store (1, 2 or 3?)
        int numCustomers = rand() % 3 + 1;

        // 2. Add the customers to the linked list representing the shoppers in the store
        for (int i = 0; i < numCustomers; ++i) {
            int itemCount;
            int customerType = rand() % 100;

            if (customerType < 40) {
                itemCount = rand() % 11;
            } else if (customerType < 70) {
                itemCount = rand() % 10 + 11;
            } else if (customerType < 90) {
                itemCount = rand() % 10 + 21;
            } else {
                itemCount = rand() % 30 + 31;
            }

            int shoppingTime = itemCount * (rand() % 31 + 30);
            int enterQTime = currentTime + shoppingTime;
            int exitQTime = enterQTime + itemCount * 15;

            listType newCustomer = {cartId++, itemCount, enterQTime, exitQTime};
            store.addElement(newCustomer);
        }

        // 3. Update the checkout lines
        for (int i = 0; i < numCheckouts; ++i) {
            if (!store.listIsEmpty() && store.peek().enterQTime == currentTime) {
                listType customer = store.peek();
                store.delElement();

                int shortestQueue = 0;
                for (int j = 1; j < numCheckouts; ++j) {
                    if (checkoutData[j].currItems < checkoutData[shortestQueue].currItems) {
                        shortestQueue = j;
                    }
                }

                queueNodeData newQueueNode = {customer.exitQTime, customer.itemCount};
                checkouts[shortestQueue].enQueue(newQueueNode);

                checkoutData[shortestQueue].queueCount++;
                checkoutData[shortestQueue].currItems += customer.itemCount;
                checkoutData[shortestQueue].totalItems += customer.itemCount;
                checkoutData[shortestQueue].cartList.push_back(customer.cartId);

                if (checkoutData[shortestQueue].queueCount > checkoutData[shortestQueue].maxQueueLength) {
                    checkoutData[shortestQueue].maxQueueLength = checkoutData[shortestQueue].queueCount;
                }
            }

            if (!checkouts[i].queueEmpty() && checkouts[i].peek().timeAvailable == currentTime) {
                                checkoutData[i].currItems -= checkouts[i].peek().itemCount;
                checkouts[i].deQueue();
                checkoutData[i].queueCount--;
            } else if (checkouts[i].queueEmpty()) {
                checkoutData[i].totalIdleTime++;
            }
        }
    }

    // Continue processing customers after store closing
    while (!store.listIsEmpty()) {
        int currentTime = store.peek().enterQTime;

        for (int i = 0; i < numCheckouts; ++i) {
            if (!store.listIsEmpty() && store.peek().enterQTime == currentTime) {
                listType customer = store.peek();
                store.delElement();

                int shortestQueue = 0;
                for (int j = 1; j < numCheckouts; ++j) {
                    if (checkoutData[j].currItems < checkoutData[shortestQueue].currItems) {
                        shortestQueue = j;
                    }
                }

                queueNodeData newQueueNode = {customer.exitQTime, customer.itemCount};
                checkouts[shortestQueue].enQueue(newQueueNode);

                checkoutData[shortestQueue].queueCount++;
                checkoutData[shortestQueue].currItems += customer.itemCount;
                checkoutData[shortestQueue].totalItems += customer.itemCount;
                checkoutData[shortestQueue].cartList.push_back(customer.cartId);

                if (checkoutData[shortestQueue].queueCount > checkoutData[shortestQueue].maxQueueLength) {
                    checkoutData[shortestQueue].maxQueueLength = checkoutData[shortestQueue].queueCount;
                }
            }

            if (!checkouts[i].queueEmpty() && checkouts[i].peek().timeAvailable == currentTime) {
                checkouts[i].deQueue();
                checkoutData[i].queueCount--;
                checkoutData[i].currItems -= checkouts[i].peek().itemCount;
                checkoutData[i].totalOverTime++;
            }
        }
    }

    // Print checkout statistics
    for (int i = 0; i < numCheckouts; ++i) {
        cout << "Checkout line: " << (i + 1) << endl;
        cout << "    Total Customers Helped: " << checkoutData[i].cartList.size() << endl;
        cout << "    Total Number of Items: " << checkoutData[i].totalItems << endl;
        cout << "    Max Line Length: " << checkoutData[i].maxQueueLength << endl;
        cout << "    Total Idle Time: " << checkoutData[i].totalIdleTime << endl;
        cout << "    Total over time: " << checkoutData[i].totalOverTime << endl << endl;
    }

    return 0;
}

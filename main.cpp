// Authors: Jordan Taranto, Garry Bhullar, Deyanira Chavez

#include "queue.h"
#include "linkedlist.h"

int generateItems() {
    int randomValue = rand() % 100 + 1;

    if (randomValue <= 40) {
        return rand() % 11;
    } else if (randomValue <= 70) {
        return rand() % 10 + 11;
    } else if (randomValue <= 90) {
        return rand() % 10 + 21;
    } else {
        return rand() % 30 + 31;
    }
}

int main() {
    srand(time(0)); // Seed the random number generator

    cout << "Enter the number of checkout lines (1-10): ";
    int numLines;
    cin >> numLines;

    vector<CheckoutQueue> checkouts(numLines);
    vector<queueData> queueStats(numLines);

    LinkedList carts;
    int currentTime = 0;
    int cartId = 0;
    while (true) {
        int customersArriving = rand() % 3 + 1;
        bool customersAdded = false;

        for (int i = 0; i < customersArriving && currentTime <= 720; ++i) {
            int items = generateItems();
            int shoppingTime = items * (rand() % 31 + 30);
            int enterQTime = currentTime + shoppingTime;

            listType cart = { cartId++, items, enterQTime, -1 };
            carts.addElement(cart);
            customersAdded = true;
        }

        bool queuesUpdated = false;
        for (int i = 0; i < numLines; ++i) {
            while (!carts.listIsEmpty() && currentTime >= carts.peek().enterQTime) {
                int minQueueIndex = 0;
                int minQueueLength = queueStats[minQueueIndex].queueCount;

                for (int j = 1; j < numLines; ++j) {
                    if (queueStats[j].queueCount < minQueueLength) {
                        minQueueLength = queueStats[j].queueCount;
                        minQueueIndex = j;
                    }
                }

                listType cart = carts.peek();
                carts.delElement();

                queueNodeData newNodeData = { currentTime + (cart.itemCount * 15), cart.itemCount };
                checkouts[minQueueIndex].enQueue(newNodeData);
                queueStats[minQueueIndex].cartList.push_back(cart.cartId);
                queueStats[minQueueIndex].currItems += cart.itemCount;
                queueStats[minQueueIndex].queueCount++;

                if (queueStats[minQueueIndex].queueCount > queueStats[minQueueIndex].maxQueueLength) {
                    queueStats[minQueueIndex].maxQueueLength = queueStats[minQueueIndex].queueCount;
                }
                queuesUpdated = true;
            }

            while (!checkouts[i].queueEmpty() && currentTime >= checkouts[i].peek().timeAvailable) {
                queueNodeData finishedCart = checkouts[i].deQueue();
                queueStats[i].currItems -= finishedCart.itemCount;
                queueStats[i].queueCount--;
                queueStats[i].totalItems += finishedCart.itemCount;
                queuesUpdated = true;
            }

            if (checkouts[i].queueEmpty()) {
                queueStats[i].totalIdleTime++;
            }

            if (currentTime > 720 && !checkouts[i].queueEmpty()) {
                queueStats[i].totalOverTime++;
            }
        }

        if (!customersAdded && !queuesUpdated) {
            break;
        }

        currentTime++;
    }

    for (int i = 0; i < numLines; ++i) {
        cout << "CHECKOUT LINE: " << i + 1 << endl;
        cout << "    Total Customers Helped: " << queueStats[i].cartList.size() << endl;
        cout << "    Total Number of Items: " << queueStats[i].totalItems << endl;
        cout << "    Max Line Length: " << queueStats[i].maxQueueLength << endl;
        cout << "    Total Idle Time: " << queueStats[i].totalIdleTime << " minutes" << endl;
        cout << "    Total Over Time: " << queueStats[i].totalOverTime << " minutes" << endl;
    }
  return 0;
}

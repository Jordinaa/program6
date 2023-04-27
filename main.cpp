#include <iostream>
#include "queue.h"
#include "linkedlist.h"
#include <random>
using namespace std;

int main(){

	int numQ = 0;

	cout << "Enter the amount of checkout queue(s) you would like to test: ";
	cin >> numQ;

	int timeOpen = 720;
  int currTime = 0;
  

	for (int i = 0; i < timeOpen; i++) {
		currTime++;
		int customersEnter = 0;
    listType person;

		customersEnter = rand() % 3 + 1;

		for (int i = 0; i < customersEnter; i++) {
			LinkedList::listCount++;
      srand(time(0));
      person.cartId = (rand() % 100000);
      const double p1 = 0.4;
      const double p2 = 0.3;
      const double p3 = 0.2;
      const double p4 = 0.1;

      double items_probability = static_cast<double>(rand()) / RAND_MAX;

      if (items_probability < p1){
        person.itemCount = 1 + rand() % 10;
      }
      else if (items_probability < p1 + p2){
        person.itemCount = 1 + 11 + rand() % 10;
      }
      else if (items_probability < p1+ p2 + p3){
        person.itemCount = 21 + rand() % 10;
      }
      else{
        person.itemCount = 31 + rand() % 30;
      }

      double shoppingTime;
      
      for (int i = 0; i < person.itemCount; i++){
        double timeShop = static_cast<double>(rand()) / RAND_MAX;
        double timeShopScale = 0.5 + timeShop * 0.5;
        shoppingTime += timeShopScale;
      }

      int checkoutTime = person.itemCount * 0.25;

      person.enterQTime = currTime + static_cast<int>(shoppingTime);
      person.exitQTime = person.enterQTime + checkoutTime;
		}
	}

	return 0;
}
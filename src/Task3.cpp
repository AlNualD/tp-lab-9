//#include <iostream>
//#include <vector>
//#include <queue>
//#include <mutex>
//#include <thread>

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <thread>
#include <mutex>
#include <queue>
#include <random>
#include <chrono>

using namespace std;

mutex mut;

class Buyer {
public:
	vector<int> goods;
	int number;
};

void Cashbox(queue<Buyer*>* buyers, int num) {
	mut.lock();
	cout << "new cashbox is opened " << num << endl;
	mut.unlock();
	while (true) {
		Buyer* buyer = buyers->front();
		cout << num << " *** Serving " << buyer->number << endl;
		for (int i : buyer->goods) {
			this_thread::sleep_for(chrono::milliseconds(i));
		}
		mut.lock();
		buyers->pop();
		cout << num << "*** buyer served " << buyer->number << endl;
		delete buyer;
		if (buyers->empty()) {
			cout << "cashbox is closed " << num << endl;
			mut.unlock();
			return;
		}
		
		mut.unlock();
	}
}

int main() {
	vector<queue<Buyer*>*> shop;
	vector<thread*> ts;
	vector<Buyer*> all_buyers;
	int number_buyer = 1;
	int number_cashbox = 1;
	for (int i = 0; i < 30; i++) {

		this_thread::sleep_for(chrono::milliseconds((rand() % 101) * 10)); 

		int amount = rand() % 10 + 1;
		Buyer*  buyer = new Buyer;
		//all_buyers.push_back(buyer);
		number_buyer++;
		buyer->number = number_buyer;
		for (int j = 0; j < amount; j++) {
			buyer->goods.push_back((rand() % 51) * 10); 
		}
			mut.lock();
			bool needAnotherCashbox = true;
			cout << "_______queue_______________________" << endl;
			for (int i = 0; i < shop.size(); i++) {
				cout << shop[i]->size() << " ";
				if (needAnotherCashbox && shop[i]->size() < 5) {
					shop[i]->push(buyer);
					needAnotherCashbox = false;
				}
				if (shop[i]->empty()) {
					shop.erase(shop.begin() + i);
					i--;
				}
			}
			cout << "\n___________________________________" << endl;

			if (needAnotherCashbox) {
				queue<Buyer*>* q = new queue<Buyer*>;
				(*q).push(buyer);
				shop.push_back(q);
				ts.push_back(new thread(Cashbox, q, number_cashbox++));
			}
			mut.unlock();
	}

	for (thread* t : ts) {
		t->join();
	}

	//for (Buyer* buyer : all_buyers) {
	//	delete buyer;
	//}

	return 0;
}


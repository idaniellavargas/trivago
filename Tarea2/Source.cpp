#include <iostream>
#include <list>

using namespace std;


int main() {
	list<int> l1, l2;

	l1.push_front(1);
	l1.push_back(2);
	l2.push_front(1);
	l2.push_front(1);
	l2.push_back(1);

	cout << (l1 < l2);
}
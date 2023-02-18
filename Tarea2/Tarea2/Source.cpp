#include "UPC.h"
#include <iostream>

using namespace UPC;
using namespace std;

template <typename T> void invertirPila(stack<T> &s) {
	stack<T> s2;
	int i = s.size();
	while (!s.empty()) {
		s2.push(s.top());
		s.pop();
	}
	s = s2;
}

template<typename T> void invertirCola(queue<T>& q) {
	int s = q.size();
	T* arr = new T[s];
	int i = q.size() - 1;
	while (!q.empty()) {
		arr[i] = q.front();
		q.pop();
		i--;
	}
	for (int i = 0; i < s; i++) {
		q.push(arr[i]);
	}

	delete[]arr;
}

int main() {
	stack <int> x;
	x.push(5);
	x.push(4);
	x.push(3);
	x.push(2);
	x.push(1);

	invertirPila(x);

	while (!x.empty()) {
		cout << x.top() << " ";
		x.pop();
	}
	cout << "\n";

	queue <int> y;
	y.push(5);
	y.push(4);
	y.push(3);
	y.push(2);
	y.push(1);

	invertirCola(y);

	while (!y.empty()) {
		cout << y.front() << " ";
		y.pop();
	}
	cout << "\n";


	x.push(5);
	x.push(4);
	x.push(3);
	x.push(2);
	x.push(1);

	x.eliminarPos(2); //este es un metodo porque necesita permisos

	while (!x.empty()) {
		cout << x.top() << " ";
		x.pop();
	}
	cout << "\n";
	

}
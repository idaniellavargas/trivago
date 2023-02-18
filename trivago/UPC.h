#pragma once
#include <iostream>
#include <functional>
#include <algorithm>

#define func std::function<bool(T&, T&)>

template <typename T> T max2(T a, T b) {
	if (a > b) return a;
	return b;
}


unsigned long long pow2(int x, int y) {
	unsigned long long z = 1;
	while (y--) z *= x;
	return z;
}

namespace UPC {

	//version 5.0: ahora con menos crash
	//version 6.0: agregué los sorts. Insertion sort para lista y vector implementados en las clases.
	//version 6.1: problemas de memoria.
	//version 6.2: copia de listas recursivas implementadas

	template <typename T>  class vector {
	public:
		T* vec;
		int len;
		int capacity;
		bool is_sorted;
		func comp;

		vector() {
			vec = new T[1];
			len = 0;
			capacity = 1;
			is_sorted = true;
			comp = [](T& a, T& b) -> bool {
				return a < b;
			};
		}
		~vector() {
			delete[]vec;
		};

		vector(const vector& nv) {
			vec = new T[nv.capacity];
			len = nv.len;
			capacity = nv.capacity;
			is_sorted = nv.sorted;
			for (int i = 0; i < len; i++) {
				vec[i] = nv.vec[i];
			}
		}

		T& operator[](const int& index) { return vec[index]; }

		vector<T>& operator= (const vector<T>& rhs) {
			if (this == &rhs) return *this;
			delete[]vec;
			vec = new T[rhs.capacity];
			len = rhs.len;
			capacity = rhs.capacity;
			is_sorted = rhs.is_sorted;
			for (int i = 0; i < len; i++) {
				vec[i] = rhs.vec[i];
			}
			return *this;
		}

		bool& operator<(const vector<T>& rhs) {
			if (len < rhs.len) return true;
			else if (len > rhs.len) return false;
			else {
				for (int i = 0; i < len; i++) {
					if (vec[i] < rhs[i]) return true;
					else if (vec[i] > rhs[i]) return false;
				}
				return false;
			}
		}

		bool& operator>(const vector<T>& rhs) {
			return !this < rhs;
		}

		void push_back(T elem) {
			if (len != 0 && comp(elem, vec[len - 1])) is_sorted = false;
			if (len == capacity) {
				capacity *= 2;
				T* aux = new T[capacity];
				for (int i = 0; i < len; i++) aux[i] = vec[i];
				aux[len] = elem;
				vec = aux;
			}
			else {
				vec[len] = elem;
			}
			len++;
		}

		void push_front(T elem) {
			if (len != 0 && !comp(elem, vec[0])) is_sorted = false;
			if (len == capacity) {
				capacity *= 2;
				T* aux = new T[capacity];
				for (int i = 0; i < len; i++) {
					aux[i + 1] = vec[i];
				}
				aux[0] = elem;
				vec = aux;
			}
			else {
				for (int i = len; i > 0; i--) {
					vec[i] = vec[i - 1];
				}
				vec[0] = elem;
			}
			len++;
		}

		void pop_back() {
			if (len == 0) return;
			vec[len - 1] = NULL;
			len--;
		}

		void pop_front() {
			for (int i = 0; i < len - 1; i++) vec[i] = vec[i + 1];
			vec[len - 1] = NULL;
			len--;
		}

		void erase(int x) {
			if (len == 0) return;
			bool erased = false;
			for (int i = 0; i < len; i++) {
				if (i == x) erased = true;
				if (erased) vec[i] = vec[i + 1];
			}
			len--;
		}

		void erase(T* it) {
			if (len == 0) return;
			bool erased = false;
			for (int i = 0; i < len; i++) {
				if (begin() + i == it) erased = true;
				if (erased) vec[i] = vec[i + 1];
			}
			len--;
		}

		void erase(T* ini, T* fin) {
			if (ini > fin || len == 0) return;
			int j = 0;
			bool er = false, erased = false;
			for (int i = 0; i < len; i++) {
				if ((begin() + i) == ini) er = true;
				else if ((begin() + i) == fin) {
					er = false;
					erased = true;
				}
				if (er) j++;
				if (erased) vec[i - j] = vec[i];
			}
			len -= (fin - ini);
		}

		T* begin() { return &vec[0]; }
		T* end() { return &vec[len]; }
		int size() { return len; }

		bool getComp() { return comp; }
		void setComp(func comp) { this->comp = comp; }

		bool sorted() { return sorted; }

		void setSort(bool b) { is_sorted = b; }

		void insert(T elem);
	};

	template<typename T> class list {
	private:
		struct node {
			T data;
			node* next;

			node(T d, node* n = nullptr) {
				data = d;
				next = n;
			}

			node(const node& d) {
				data = d.data;
				next = d.next;

			}
			~node() {
				delete next;
			}

			bool operator>(node rhs) {
				return data > rhs.data;
			}

			bool operator<(node rhs) {
				return data < rhs.data;
			}
		};


		node* ini;
		node* back;
		int len;
		bool is_sorted;
		func comp;
	public:


		list() {
			ini = nullptr;
			back = nullptr;
			len = 0;
			is_sorted = true;
			comp = [](T& a, T& b) { return a < b; };
		}

		~list() {
			delete ini;
		}

		node* copyList(node* nn) {
			if (nn->next == nullptr) {
				back = new node(nn->data);
				return back;
			}
			else {
				return new node(nn->data, copyList(nn->next));
			}
		}

		list(const list& nl) {
			is_sorted = nl.is_sorted;
			len = nl.len;
			if (nl.ini == nullptr) {
				ini = nullptr;
			}
			else {
				if (nl.ini != nullptr) ini = copyList(nl.ini);
			}
		}

		list<T>& operator= (const list<T>& rhs) {
			if (this == &rhs) return *this;
			while (len != 0) pop_front();
			if (rhs.ini == nullptr) {
				ini = nullptr;
				return *this;
			}
			ini = copyList(rhs.ini);
			is_sorted = rhs.is_sorted;
			len = rhs.len;
			return *this;
		}

		class Iterator {
		private:
			node* cn;
		public:
			Iterator() {}

			Iterator(node* n) {
				cn = n;
			}

			Iterator& operator++() {
				if (cn != nullptr) cn = cn->next;
				return *this;
			}

			Iterator& operator++(int) {
				Iterator iterator = *this;
				++* this;
				return iterator;
			}

			Iterator& operator=(node* nn)
			{
				cn = nn;
				return *this;
			}

			Iterator& operator=(T rhs) {
				cn->data = rhs;
				return *this;
			}

			bool operator!= (const Iterator& it) {
				return cn != it.cn;
			}

			T operator*() {
				return cn->data;
			}

			bool operator== (const Iterator& it) {
				return cn == it.cn;
			}

			void newnext(Iterator nn) {
				cn->next = nn.cn->next;
			}

			void erase() {
				cn->next = nullptr;
				delete cn;
			}

		};

		Iterator begin() {
			return Iterator(ini);
		}

		Iterator end() {
			return Iterator(nullptr);
		}

		Iterator rbegin() {
			return Iterator(back);
		}

		bool operator==(list<T>& rhs) {
			if (len != rhs.len) return false;
			else {
				auto it1 = begin(), it2 = rhs.begin();
				while (it1 != end()) {
					if (*it1 != *it2) return false;
				}
				return true;
			}
		}

		bool operator<(list<T>& rhs) {
			if (len < rhs.len) return true;
			else if (len > rhs.len) return false;
			else {
				auto it1 = begin(), it2 = rhs.begin();
				while (it1 != end()) {
					if ((*it1) < (*it2)) return true;
					else if ((*it1) > (*it2)) return false;
					++it1;
					++it2;
				}
				return false;
			}
		}

		bool operator>(list<T>& rhs) {
			return !(this < rhs);
		}

		bool operator<=(list<T>& rhs) {
			return (this < rhs) || (this == rhs);
		}

		bool operator>=(list<T>& rhs) {
			return (this > rhs) || (this == rhs);
		}

		void push_front(T data) {
			if (len == 0) {
				ini = new node(data);
				back = ini;
			}
			else {
				if (!comp(data, ini->data)) is_sorted = false;
				node* n = new node(data);
				n->next = ini;
				ini = n;
			}
			len++;
		}

		void push_back(T data) {
			if (len == 0) {
				ini = new node(data);
				back = ini;
			}
			else {
				if (comp(data, ini->data)) is_sorted = false;
				node* n = new node(data);
				back->next = n;
				back = n;
			}
			len++;
		}

		void pop_back() {
			node* crawler = ini;
			node* prev = ini;

			while (crawler->next != nullptr) {
				prev = crawler;
				crawler = crawler->next;
			}
			prev->next = nullptr;
			crawler->next = nullptr;
			delete crawler;
			len--;
		}

		void pop_front() {
			node* aux = ini;
			ini = ini->next;
			aux->next = nullptr;
			delete aux;
			len--;
		}

		void erase(int x) {
			node* crawler = ini;
			node* prev = ini;
			if (x >= len) {
				return;
			}
			else if (x == 0) {
				pop_front();
				return;
			}
			else if (x == len - 1) {
				pop_back();
				return;
			}

			for (int i = 0; i < x; i++) {
				prev = crawler;
				crawler = crawler->next;
			}
			prev->next = crawler->next;
			crawler->next = nullptr;
			delete crawler;
			len--;
		}

		void erase(Iterator it) {
			Iterator crawler = begin();
			Iterator prev;
			if (it == begin()) {
				pop_front();
				return;
			}
			else if (crawler == end()) return;
			else {
				while (crawler != it && crawler != end()) {
					prev = crawler;
					crawler++;
				}
				if (crawler == end()) return;
				Iterator e = crawler;
				crawler++;
				prev.newnext(crawler);
				e.erase();
			}
		}

		int size() {
			return len;
		}

		void setComp(func comp) { this->comp = comp; }

		void insert(T data);

		void setSorted(bool b) { is_sorted = b; }
	};

	template <typename T> class stack {
	private:
		struct node {
			T data;
			node* next;

			node(T d, node* n = nullptr) {
				data = d;
				next = n;
			}

			node(const node& d) {
				data = d.data;
				next = d.next;
			}

			~node() {
				delete next;
			}
		};

		node* Top;
		int len;

	public:

		stack() {
			Top = nullptr;
			len = 0;
		}
		~stack() { delete Top; }

		node* copyList(node* nn) {
			if (nn->next == nullptr) {
				return new node(nn->data);
			}
			else {
				return new node(nn->data, copyList(nn->next));
			}
		}

		stack(const stack& nl) {
			len = nl.len;
			if (nl.Top == nullptr) Top = nullptr;
			else Top = copyList(nl.Top);
		}

		stack<T>& operator= (const stack<T>& rhs) {
			if (this == &rhs) return *this;
			len = rhs.len;
			while (len != 0) pop();
			if (rhs.Top == nullptr) Top = nullptr;
			else Top = copyList(rhs.Top);
			return *this;
		}


		void push(T data) {
			if (len == 0) Top = new node(data);
			else Top = new node(data, Top);
			len++;
		}

		void pop() {
			if (len == 0) return;
			else {
				node* aux = Top;
				Top = Top->next;
				aux->next = nullptr;
				delete aux;
			}
			len--;
		}

		bool empty() {
			return len == 0;
		}

		T top() {
			return Top->data;
		}

		int size() {
			return len;
		}

		void eliminarPos(int x) {
			if (x >= len || x < 0) return;
			if (x == 0) {
				pop();
				return;
			}
			node* crawler = Top;
			node* prev = nullptr;

			for (int i = 1; i <= x; i++) {
				prev = crawler;
				crawler = crawler->next;
			}
			prev->next = crawler->next;
			crawler->next = nullptr;
			delete crawler;

		}
	};

	template <typename T> class queue {
	private:
		struct node {
			T data;
			node* next;

			node(T d, node* n = nullptr) {
				data = d;
				next = n;
			}
			~node() {
				delete next;
			}
		};

		node* Front;
		node* Back;
		int len;

	public:

		queue() {
			Front = nullptr;
			Back = nullptr;
			len = 0;
		}
		~queue() {
			while (!empty()) pop();
		}

		node* copyList(node* nn) {
			if (nn->next == nullptr) {
				Back = new node(nn->data);
				return Back;
			}
			else {
				return new node(nn->data, copyList(nn->next));
			}
		}

		queue(const queue& nl) {
			if (nl.Front != nullptr) Front = copyList(nl.Front);
			else Front = nullptr;
			len = nl.len;
		}

		queue<T>& operator= (const queue<T>& rhs) {
			if (this == &rhs) return *this;
			while (len != 0) pop();
			len = rhs.len;
			if (rhs.Front != nullptr) Front = copyList(rhs.Front);
			else Front = nullptr;
			return *this;
		}

		void push(T data) {
			if (len == 0) {
				Front = new node(data);
				Back = Front;
			}
			else {
				Back->next = new node(data);
				Back = Back->next;
			}
			len++;
		}

		void pop() {
			if (len == 0) return;
			else {
				node* aux = Front;
				Front = Front->next;
				aux->next = nullptr;
				delete aux;
			}
			len--;
		}

		bool empty() {
			return len == 0;
		}

		T front() {
			return Front->data;
		}

		T back() {
			return Back->data;
		}

		int size() {
			return len;
		}

	};

	template <typename T> class AVLTree {
	private:
		struct Node {
			std::string key;
			T data;
			int height;
			Node* left;
			Node* right;

			Node(const std::string& key, const T& data) : key(key), data(data), height(1), left(nullptr), right(nullptr) {}
		};

		Node* root;
		int len = 0;

		int getHeight(Node* node) {
			if (node == nullptr) {
				return 0;
			}
			return node->height;
		}

		int getBalanceFactor(Node* node) {
			if (node == nullptr) {
				return 0;
			}
			return getHeight(node->left) - getHeight(node->right);
		}

		Node* leftRotate(Node* node) {
			Node* newRoot = node->right;
			Node* temp = newRoot->left;
			newRoot->left = node;
			node->right = temp;

			node->height = 1 + max2(getHeight(node->left), getHeight(node->right));
			newRoot->height = 1 + max2(getHeight(newRoot->left), getHeight(newRoot->right));

			return newRoot;
		}

		Node* rightRotate(Node* node) {
			Node* newRoot = node->left;
			Node* temp = newRoot->right;
			newRoot->right = node;
			node->left = temp;

			node->height = 1 + max2(getHeight(node->left), getHeight(node->right));
			newRoot->height = 1 + max2(getHeight(newRoot->left), getHeight(newRoot->right));

			return newRoot;
		}

		Node* insert(Node* node, const std::string& key, const T& data) {
			if (node == nullptr) {
				return new Node(key, data);
			}
			else if (key < node->key) {
				node->left = insert(node->left, key, data);
			}
			else {
				node->right = insert(node->right, key, data);
			}

			node->height = 1 + max2(getHeight(node->left), getHeight(node->right));
			int balanceFactor = getBalanceFactor(node);

			if (balanceFactor > 1 && key < node->left->key) {
				return rightRotate(node);
			}
			else if (balanceFactor > 1 && key > node->left->key) {
				node->left = leftRotate(node->left);
				return rightRotate(node);
			}
			else if (balanceFactor < -1 && key > node->right->key) {
				return leftRotate(node);
			}
			else if (balanceFactor < -1 && key < node->right->key) {
				node->right = rightRotate(node->right);
				return leftRotate(node);
			}

			return node;
		}
		Node* search(Node* node, const std::string& key) {
			if (node == nullptr || node->key == key) {
				return node;
			}
			if (key < node->key) {
				return search(node->left, key);
			}
			else {
				return search(node->right, key);
			}
		}
		Node* remove(Node* node, const std::string& key) {
			if (node == nullptr) {
				return node;
			}
			if (key < node->key) {
				node->left = remove(node->left, key);
			}
			else if (key > node->key) {
				node->right = remove(node->right, key);
			}
			else {
				if (node->left == nullptr || node->right == nullptr) {
					Node* temp = node->left ? node->left : node->right;
					if (temp == nullptr) {
						temp = node;
						node = nullptr;
					}
					else {
						*node = *temp;
					}
					delete temp;
				}
				else {
					Node* temp = minValueNode(node->right);
					node->key = temp->key;
					node->data = temp->data;
					node->right = remove(node->right, temp->key);
				}
			}

			if (node == nullptr) {
				return node;
			}

			node->height = 1 + max2(getHeight(node->left), getHeight(node->right));
			int balanceFactor = getBalanceFactor(node);

			if (balanceFactor > 1 && getBalanceFactor(node->left) >= 0) {
				return rightRotate(node);
			}
			else if (balanceFactor > 1 && getBalanceFactor(node->left) < 0) {
				node->left = leftRotate(node->left);
				return rightRotate(node);
			}
			else if (balanceFactor < -1 && getBalanceFactor(node->right) <= 0) {
				return leftRotate(node);
			}
			else if (balanceFactor < -1 && getBalanceFactor(node->right) > 0) {
				node->right = rightRotate(node->right);
				return leftRotate(node);
			}

			return node;
		}

		Node* minValueNode(Node* node) {
			Node* current = node;
			while (current->left != nullptr) {
				current = current->left;
			}
			return current;
		}

		void _inOrden(Node* nodo, std::function<void(std::string, T)> procesar) {
			if (nodo == nullptr) return;
			_inOrden(nodo->left, procesar);
			procesar(nodo->key, nodo->data);
			_inOrden(nodo->right, procesar);
		}
	public:
		AVLTree() : root(nullptr) {}
		void insert(const std::string& key, const T& data) {
			len++;
			root = insert(root, key, data);
		}

		void remove(const std::string& key) {
			len--;
			root = remove(root, key);
		}

		T search(const std::string& key) {
			Node* node = search(root, key);
			if (node != nullptr) {
				return node->data;
			}
			else {
				throw std::out_of_range("Key not found.");
			}
		}

		void enOrden(std::function<void(std::string, T)> procesar) {
			_inOrden(root, procesar);
		}

		int size() {
			return len;
		}

		T r(Node* n) {
			int i = rand() % 3;
			switch (i) {
			case 0:
				return n->data;
			case 1:
				if (n->right == nullptr) return n->data;
				return r(n->right);
			case 2:
				if (n->left == nullptr) return n->data;
				return r(n->left);
			}
		}

		T ran() {
			return r(root);
		}

		list<T>& getList(list<T> &l) {
			enOrden([&l](string s, T e) { l.push_back(e); });
			return l;
		}
	};

	template <typename T> class hashAVL {
	private:
		int bucket;
		AVLTree<T>* table;
		int len;

	public:
		hashAVL(int b) {
			bucket = b;
			table = new AVLTree<T>[b];
			len = 0;
		}

		int hash(std::string key) {
			unsigned long long h1 = 0;
			for (int i = 0; i < key.size(); i++) {
				h1 += (key[i] * pow2(37, i)) % bucket;
				h1 %= bucket;
			}
			return h1;
		}

		/*
		int hash(int x) {
			return x % bucket;
		}
		*/

		void insert(std::string key, T data) {
			int index = hash(key);
			AVLTree<T>& t = table[index];
			t.insert(key, data);
			len++;
		}

		void erase(std::string key) {
			int index = hash(key);
			AVLTree<T>& l = table[index];
			l.remove(key);
			len--;
		}

		T get(std::string key) {
			int index = hash(key);
			AVLTree<T>& l = table[index];
			return l.search(key);
		}

		void show() {
			for (int j = 0; j < bucket; j++) {
				std::cout << j << ":\n";
				auto i = &table[j];
				i->enOrden([](std::string s, T x) {cout << " " << s << "->" << x << "\n"; });
			}
		}

		void foreach(std::function<void(std::string, T)> f) {
			for (int j = 0; j < bucket; j++) {
				auto i = &table[j];
				i->enOrden(f);
			}
		}

		void colisions() {
			int zc = 0, sc = 0, nc = 0;
			for (int j = 0; j < bucket; j++) {
				auto i = &table[j];
				if (i->size() == 1) nc++;
				else if (i->size() <= 2) sc++;
				else zc++;
			}
			std::cout << zc << " " << nc << " " << sc << "\n";
		}

		T operator[] (const std::string& rhs) {
			T x = get(rhs);
			return x;
		}

		int size() {
			return len;
		}

		T getRan() {
			int index;
			AVLTree<Hotel*>* temp = nullptr;
			do {
				index = rand() % bucket;
				temp = &table[index];
			} while (temp->size() == 0);
			
			return temp->ran();
		}

		list<T>& getList() {
			list<T> l;
			for (int i = 0; i < bucket; i++) {
				table[i].getList(l);
			}
			return l;
		}

	};


	template<typename T> void lswap(typename list<T>::Iterator a, typename list<T>::Iterator b) {
		T aux = *a;
		a = *b;
		b = aux;
	}

	template<typename T> void shuffle(T arr[], int len) {
		if (!len) return;
		for (int i = len - 1; i > 0; i--) {
			int j = (rand() % (i + 1));
			std::swap(arr[i], arr[j]);
		}
	}

	template <typename T> void shuffle(vector<T>& v) {
		if (!v.size()) return;
		v.setSort(false);
		for (int i = v.size() - 1; i > 0; i--) {
			int j = (rand() % (i + 1));
			std::swap(v[i], v[j]);
		}
	}

	template <typename T> void shuffle(list<T>& l) {
		if (!l.size()) return;
		l.setSorted(false);
		int i = 0;
		for (auto it = l.begin(); it != l.end(); it++) {
			int j = (rand() % (l.size() - i) + i);
			auto ran = l.begin();
			while (j--) ran++;
			/*
			int aux = *it;
			it = *ran;
			ran = aux;
			*/
			lswap<T>(it, ran);
			i++;
		}
	}

	template <typename T, typename L> void esort(T arr[], int len, L comp) {
		for (int i = 0; i < len - 1; i++) {
			for (int j = i + 1; j < len; j++) {
				if (comp(arr[j], arr[i])) std::swap(arr[j], arr[i]);
			}
		}
	}

	template <typename T> void esort(T arr[], int len) {
		for (int i = 0; i < len - 1; i++) {
			for (int j = i + 1; j < len; j++) {
				if (arr[j] < arr[i]) std::swap(arr[j], arr[i]);
			}
		}
	}

	template <typename T> void esort(vector<T>& v) {
		for (int i = 0; i < v.size() - 1; i++) {
			for (int j = i + 1; j < v.size(); j++) {
				if (v[j] < v[i]) std::swap(v[j], v[i]);
			}
		}
	}

	template <typename T, typename L> void esort(vector<T>& v, L comp) {
		for (int i = 0; i < v.size() - 1; i++) {
			for (int j = i + 1; j < v.size(); j++) {
				if (comp(v[j], v[i])) std::swap(v[j], v[i]);
			}
		}
	}

	template <typename T> void esort(list<T>& l) {
		for (auto it = l.begin(); it != l.rbegin(); it++) {
			auto j = it;
			j++;
			for (; j != l.end(); j++) {
				if (*j < *it) lswap<T>(it, j);
			}
		}
	}

	template <typename T, typename L> void esort(list<T>& l, L comp) {
		for (auto it = l.begin(); it != l.rbegin(); it++) {
			auto j = it;
			j++;
			for (; j != l.end(); j++) {
				if (comp(*j, *it)) lswap<T>(it, j);
			}
		}
	}

	template <typename T> void bsort(T arr[], int len) {
		bool ord;
		for (int i = 0; i < len - 1; i++) {
			ord = true;
			for (int j = 0; j < len - i - 1; j++) {
				if (arr[j] > arr[j + 1]) {
					std::swap(arr[j], arr[j + 1]);
					ord = false;
				}
			}
			if (ord) break;
		}
	}

	template <typename T, typename L> void bsort(T arr[], int len, L comp) {
		bool ord;
		for (int i = 0; i < len - 1; i++) {
			ord = true;
			for (int j = 0; j < len - i - 1; j++) {
				if (comp(arr[j], arr[j + 1])) {
					std::swap(arr[j], arr[j + 1]);
					ord = false;
				}
			}
			if (ord) break;
		}
	}

	template <typename T> void bsort(vector<T>& v) {
		bool ord;
		for (int i = 0; i < v.size() - 1; i++) {
			ord = true;
			for (int j = 0; j < v.size() - i - 1; j++) {
				if (v[j] > v[j + 1]) {
					std::swap(v[j], v[j + 1]);
					ord = false;
				}
			}
			if (ord) break;
		}
	}

	template <typename T, typename L> void bsort(vector<T>& v, L comp) {
		bool ord;
		for (int i = 0; i < v.size() - 1; i++) {
			ord = true;
			for (int j = 0; j < v.size() - i - 1; j++) {
				if (comp(v[j], v[j + 1])) {
					std::swap(v[j], v[j + 1]);
					ord = false;
				}
			}
			if (ord) break;
		}
	}

	template <typename T> void bsort(list<T>& l) {
		bool ord;
		auto k = l.rbegin();
		auto aux = l.begin();

		for (auto it = l.begin(); it != k; it++) {
			ord = true;
			for (auto j = l.begin(); j != k; j++) {
				auto l = j;
				++l;
				if (*j > *l) {
					lswap<T>(j, l);
					ord = false;
				}
				if (l == k) aux = l;
			}
			if (ord) break;
			k = aux;

		}
	}

	template <typename T, typename L> void bsort(list<T>& l, L comp) {
		bool ord;
		auto k = l.rbegin();
		auto aux = l.begin();

		for (auto it = l.begin(); it != k; it++) {
			ord = true;
			for (auto j = l.begin(); j != k; j++) {
				auto l = j;
				++l;
				if (comp(*j, *l)) {
					lswap<T>(j, l);
					ord = false;
				}
				if (l == k) aux = l;
			}
			if (ord) break;
			k = aux;

		}
	}

	template <typename T> void ssort(T arr[], int len) {
		int k, menor;
		for (int i = 0; i < len - 1; i++) {
			k = i;
			menor = arr[i];
			for (int j = i + 1; j < len; j++) {
				if (arr[j] < menor) {
					menor = arr[j];
					k = j;
				}
			}
			std::swap(arr[i], arr[k]);
		}
	}

	template <typename T, typename L> void ssort(T arr[], int len, L comp) {
		int k, menor;
		for (int i = 0; i < len - 1; i++) {
			k = i;
			menor = arr[i];
			for (int j = i + 1; j < len; j++) {
				if (comp(arr[j], menor)) {
					menor = arr[j];
					k = j;
				}
			}
			std::swap(arr[i], arr[k]);
		}
	}

	template <typename T> void ssort(vector<T>& v) {
		int k, menor;
		for (int i = 0; i < v.size() - 1; i++) {
			k = i;
			menor = v[i];
			for (int j = i + 1; j < v.size(); j++) {
				if (v[j] < menor) {
					menor = v[j];
					k = j;
				}
			}
			std::swap(v[i], v[k]);
		}
	}

	template <typename T, typename L> void ssort(vector<T>& v, L comp) {
		int k, menor;
		for (int i = 0; i < v.size() - 1; i++) {
			k = i;
			menor = v[i];
			for (int j = i + 1; j < v.size(); j++) {
				if (comp(v[j], menor)) {
					menor = v[j];
					k = j;
				}
			}
			std::swap(v[i], v[k]);
		}
	}

	template <typename T> void ssort(list<T>& l) {
		typename list<T>::Iterator k;
		for (auto it = l.begin(); it != l.rbegin(); it++) {
			k = it;
			auto jt = it;
			++jt;
			for (; jt != l.end(); jt++) {
				if (*jt < *k) {
					k = jt;
				}
			}
			lswap<T>(it, k);
		}
	}

	template <typename T, typename L> void ssort(list<T>& l, L comp) {
		typename list<T>::Iterator k;
		for (auto it = l.begin(); it != l.rbegin(); it++) {
			k = it;
			auto jt = it;
			++jt;
			for (; jt != l.end(); jt++) {
				if (comp(*jt, *k)) {
					k = jt;
				}
			}
			lswap<T>(it, k);
		}
	}

	template <typename T> void isort(T arr[], int len) {
		int aux, k;
		for (int i = 1; i < len; i++) {
			aux = arr[i];
			k = i - 1;
			while (k >= 0 && aux < arr[k]) {
				arr[k + 1] = arr[k];
				k--;
			}
			arr[k + 1] = aux;
		}
	}

	template <typename T, typename L> void isort(T arr[], int len, L comp) {
		int aux, k;
		for (int i = 1; i < len; i++) {
			aux = arr[i];
			k = i - 1;
			while (k >= 0 && comp(aux, arr[k])) {
				arr[k + 1] = arr[k];
				k--;
			}
			arr[k + 1] = aux;
		}
	}

	template <typename T> void isort(vector<T>& v) {
		int aux, k;
		for (int i = 1; i < v.size(); i++) {
			aux = v[i];
			k = i - 1;
			while (k >= 0 && aux < v[k]) {
				v[k + 1] = v[k];
				k--;
			}
			v[k + 1] = aux;
		}
	}

	template <typename T, typename L> void isort(vector<T>& v, L comp) {
		int aux, k;
		for (int i = 1; i < v.size(); i++) {
			aux = v[i];
			k = i - 1;
			while (k >= 0 && comp(aux, v[k])) {
				v[k + 1] = v[k];
				k--;
			}
			v[k + 1] = aux;
		}
	}

	template <typename T> void shsort(T arr[], int len) {
		for (int half = len / 2; half > 0; half /= 2) {
			for (int i = half; i < len; i++) {
				for (int j = i - half; j >= 0; j -= half) {
					int k = j + half;
					if (arr[j] <= arr[k]) j = -1;
					else {
						std::swap(arr[j], arr[k]);
					}
				}
			}
		}
	}

	template <typename T, typename L> void shsort(T arr[], int len, L comp) {
		for (int half = len / 2; half > 0; half /= 2) {
			for (int i = half; i < len; i++) {
				for (int j = i - half; j >= 0; j -= half) {
					int k = j + half;
					if (comp(arr[j], arr[k])) j = -1;
					else {
						std::swap(arr[j], arr[k]);
					}
				}
			}
		}
	}

	template <typename T> void shsort(vector<T>& v) {
		for (int half = v.size() / 2; half > 0; half /= 2) {
			for (int i = half; i < v.size(); i++) {
				for (int j = i - half; j >= 0; j -= half) {
					int k = j + half;
					if (v[j] <= v[k]) j = -1;
					else {
						std::swap(v[j], v[k]);
					}
				}
			}
		}
	}

	template <typename T, typename L> void shsort(vector<T>& v, L comp) {
		for (int half = v.size() / 2; half > 0; half /= 2) {
			for (int i = half; i < v.size(); i++) {
				for (int j = i - half; j >= 0; j -= half) {
					int k = j + half;
					if (comp(v[j], v[k])) j = -1;
					else {
						std::swap(v[j], v[k]);
					}
				}
			}
		}
	}

	template <typename T> void rbsort(vector<T>& v, int n = v.size()) {
		if (n == 1) return;

		bool ok = true;

		for (int i = 0; i < n - 1; i++) {
			if (v[i] > v[i + 1]) {
				swap(v[i], v[i + 1]);
				ok = false;
			}
		}

		if (ok) return;

		rbsort(v, n - 1);
	}

	template <class T>
	class dlist
	{
	private:
		struct Node
		{
			T data;
			Node* next;
			Node* prev;
			Node(T data, Node* next = nullptr, Node* prev = nullptr) : data(data), next(next), prev(prev) { }
			~Node() { };
		};
		Node* head;
		Node* tail;
		size_t sz;

	public:
		dlist()
		{
			this->head = nullptr;
			this->tail = nullptr;
			this->sz = 0;
		}
		dlist(std::initializer_list<T> list)
		{
			this->head = nullptr;
			this->tail = nullptr;
			this->sz = 0;

			for (const T& val : list)
			{
				this->push_back(val);
			}
		}
		~dlist()
		{
			this->_destroyList(this->head);
			this->head = nullptr;
			this->tail = nullptr;
		}
		size_t size() { return this->sz; }
		bool empty() { return this->sz == 0; }
		T& front()
		{
			if (this->head == nullptr) throw "Error: Empty list";
			return this->head->data;
		}
		auto top() { return head; }
		T& back()
		{
			if (this->tail == nullptr) throw "Error: Empty list";
			return this->tail->data;
		}
		T& operator[](size_t i) {
			if (i < 0 || i >= sz) {
				throw std::out_of_range("Index out of range");
			}
			Node* current = head;
			for (size_t j = 0; j < i; ++j) {
				current = current->next;
			}
			return current->data;
		}
		void print() {
			Node* current = head;
			while (current != nullptr) {
				std::cout << current->data << " ";
				current = current->next;
			}
			std::cout << std::endl;
		}
		T& middle()
		{
			if (this->head == nullptr) throw "Error: Empty list";

			Node* it = this->head;
			size_t mid = this->sz / 2;

			for (size_t i = 0; i < mid; ++i) it = it->next;
			return it->data;
		}
		void insert(size_t index, T data)
		{
			if (index < 0 || index > this->sz) return;

			++this->sz;

			if (this->head == nullptr)
			{
				if (index != 0) return;

				this->head = new Node(data, this->head);
				this->tail = this->head;
				return;
			}

			if (index == 0)
			{
				this->head = new Node(data, this->head);
				this->head->next->prev = this->head;
				return;
			}

			if (index == this->sz - 1)
			{
				this->tail->next = new Node(data);
				this->tail->next->prev = this->tail;
				this->tail = this->tail->next;
				return;
			}

			Node* before = nullptr;
			Node* it = this->head;

			for (std::size_t i = 0; i < index; ++i)
			{
				before = it;
				it = it->next;
			}

			before->next = new Node(data, it, before);
			it->prev = before->next;
		}
		void push_front(T data)
		{
			this->head = new Node(data, this->head);

			if (this->sz == 0) this->tail = this->head;

			else this->head->next->prev = this->head;

			++this->sz;
		}
		void push_back(T data)
		{
			++this->sz;

			if (this->head == nullptr)
			{
				this->head = new Node(data);
				this->tail = this->head;
				return;
			}

			this->tail->next = new Node(data, nullptr, this->tail);
			this->tail = this->tail->next;
		}
		void erase(size_t index)
		{
			if (index < 0 || index >= this->sz) return;


			if (index == 0)
			{
				this->pop_front();
				return;
			}

			if (index == this->sz - 1)
			{
				this->pop_back();
				return;
			}

			Node* before = nullptr;
			Node* it = this->head;

			for (std::size_t i = 0; i < index; ++i)
			{
				before = it;
				it = it->next;
			}

			before->next = it->next;
			it->next->prev = before;

			it->next = nullptr;
			it->prev = nullptr;
			delete it;

			--this->sz;
		}
		void reverse(Node* start, Node* end) {
			Node* current = start;
			Node* prev = nullptr;
			Node* next = nullptr;
			while (current != end) {
				next = current->next;
				current->next = prev;
				prev = current;
				current->prev = next;
				current = next;
			}
			end->next = prev;
			if (start == head) {
				head = end;
			}
			else {
				start->prev->next = end;
			}
			Node* temp = start->prev;
			start->prev = end;
			end->prev = temp;
		}
		void pop_front()
		{
			if (this->head == nullptr)
			{
				return;
			}

			--this->sz;
			Node* toDelete = this->head;
			this->head = this->head->next;

			toDelete->next = nullptr;
			delete toDelete;

			if (this->head == nullptr)
			{
				this->tail = nullptr;
			}
			else
			{
				this->head->prev = nullptr;
			}
		}
		void resize(std::size_t new_size)
		{
			if (new_size < 0 || new_size >= this->sz)
			{
				return;
			}

			if (new_size == 0)
			{
				this->clear();
				return;
			}

			Node* before = nullptr;
			Node* it = this->head;

			for (std::size_t i = 0; i < new_size; ++i)
			{
				before = it;
				it = it->next;
			}

			before->next = nullptr;
			it->prev = nullptr;
			this->tail = before;
			this->_destroyList(it);

			this->sz = new_size;
		}
		void clear()
		{
			this->_destroyList(this->head);
			this->head = nullptr;
			this->tail = nullptr;
			this->sz = 0;
		}
		void filter(bool(*condition)(T data), void(*doThis)(T data))
		{
			Node* it = this->head;

			while (it != nullptr)
			{
				if (condition(it->data))
				{
					doThis(it->data);
				}
				it = it->next;
			}
		}
		bool search(T value, bool(*compare)(T first_val, T second_val) = [](T a, T b) { return a == b; })
		{
			Node* it = this->head;

			while (it != nullptr)
			{
				if (compare(it->value, value))
				{
					return true;
				}
				it = it->next;
			}

			return false;
		}
		bool search_if(bool(*condition)(T value))
		{
			Node* it = this->head;

			while (it != nullptr)
			{
				if (condition(it->data))
				{
					return true;
				}
				it = it->next;
			}

			return false;
		}
		T* find(T data, bool(*comparison)(T a, T b) = [](T a, T b) { return a == b; })
		{
			Node* it = this->head;

			while (it != nullptr)
			{
				if (comparison(data, it->data))
				{
					return &it->data;
				}
				it = it->next;
			}

			return nullptr;
		}
		void _destroyList(Node*& node)
		{
			if (node == nullptr)
			{
				return;
			}

			this->_destroyList(node->next);
			delete node;
		}
		void _end(Node*& node)
		{
			while (node->next != nullptr)
			{
				node = node->next;
			}
		}
		void heap_sort() {
			int n = size() + 1;
			n -= 1;
			Node* temp = head;
			for (int i = n / 2 - 1; i >= 0; i--)
				heapify(temp, n, i);

			for (int i = n - 1; i >= 0; i--)
			{
				swap(0, i, temp);


				heapify(temp, i, 0);
			}
		}

		void heapify(Node* temp, int n, int i) {
			int largest = i;
			int l = 2 * i + 1;
			int r = 2 * i + 2;
			Node* largesti = temp;
			for (int k = 0; k < largest; k++) {
				largesti = largesti->next;
			}
			Node* li = temp;
			for (int k = 0; k < l; k++) {
				if (li == NULL)
					break;
				li = li->next;
			}
			Node* ri = NULL;
			if (li != NULL) ri = li->next;

			if (li != NULL)
				if (l < n && li->data > largesti->data) {
					largest = l;
					largesti = li;
				}
			if (ri != NULL)
				if (r < n && ri->data > largesti->data)
					largest = r;

			if (largest != i)
			{
				swap(i, largest, temp);
				heapify(temp, n, largest);
			}
		}

		void quicksort(Node* low, Node* high) {
			if (high != nullptr && low != high && low != high->next) {
				Node* p = partition(low, high);
				quicksort(low, p->prev);
				quicksort(p->next, high);
			}
		}

		void merge(dlist<T>& left, dlist<T>& right)
		{
			dlist<T> result;

			auto left_it = left.top();
			auto right_it = right.top();

			while (left_it != nullptr && right_it != nullptr)
			{
				if (left_it->data < right_it->data)
				{
					result.push_back(left_it->data);
					left_it = left_it->next;
				}
				else
				{
					result.push_back(right_it->data);
					right_it = right_it->next;
				}
			}

			while (left_it != nullptr)
			{
				result.push_back(left_it->data);
				left_it = left_it->next;
			}

			while (right_it != nullptr)
			{
				result.push_back(right_it->data);
				right_it = right_it->next;
			}

			this->head = result.top();
			this->tail = result.top();
			this->sz = result.sz;

			result.head = nullptr;
			result.tail = nullptr;
			result.sz = 0;
		}
		void merge_sort()
		{
			if (this->sz <= 1) return;

			dlist<T> left_half;
			dlist<T> right_half;
			auto it = this->top();
			for (size_t i = 0; i < this->sz; ++i)
			{
				if (i < this->sz / 2) left_half.push_back(it->data);
				else right_half.push_back(it->data);
				it = it->next;
			}

			left_half.merge_sort();
			right_half.merge_sort();

			this->merge(left_half, right_half);
		}
		void swap(int i, int k, Node* swapList) {
			Node* temp1 = swapList, * temp2 = swapList;
			for (int j = 0; j < i; j++) {
				temp1 = temp1->next;
			}
			for (int j = 0; j < k; j++) {
				temp2 = temp2->next;
			}
			int number = temp1->data;
			temp1->data = temp2->data;

			temp2->data = number;

		}
		void printList(Node* node)
		{
			while (node != NULL) {
				std::cout << node->data << " ";
				node = node->next;
			}
		}
		void pop_back() {
			if (sz == 0) {
				return;
			}

			if (sz == 1) {
				delete tail;
				head = tail = nullptr;
			}
			else {
				Node* new_tail = tail->prev;
				new_tail->next = nullptr;
				delete tail;
				tail = new_tail;
			}

			--sz;
		}
		void swap(Node* node1, Node* node2) {
			T temp = node1->data;
			node1->data = node2->data;
			node2->data = temp;
		}


		T quickSelect(int k) {
			if (sz == 0) {
				throw std::out_of_range("List is empty");
			}

			T* arr = new T[sz];
			int i = 0;
			for (Node* node = head; node != nullptr; node = node->next) {
				arr[i++] = node->data;
			}

			T result = quickSelectHelper(arr, 0, sz - 1, k);

			delete[] arr;

			return result;
		}

		T quickSelectHelper(T* arr, int left, int right, int k) {
			if (left == right) {
				return arr[left];
			}

			int pivotIndex = (left + right) / 2;
			pivotIndex = partition(arr, left, right, pivotIndex);

			if (k == pivotIndex) {
				return arr[k];
			}
			else if (k < pivotIndex) {
				return quickSelectHelper(arr, left, pivotIndex - 1, k);
			}
			else {
				return quickSelectHelper(arr, pivotIndex + 1, right, k);
			}
		}

		int partition(T* arr, int left, int right, int pivotIndex) {
			T pivotValue = arr[pivotIndex];

			std::swap(arr[pivotIndex], arr[right]);

			int storeIndex = left;
			for (int i = left; i < right; i++) {
				if (arr[i] < pivotValue) {
					std::swap(arr[i], arr[storeIndex]);
					storeIndex++;
				}
			}
			std::swap(arr[storeIndex], arr[right]);

			return storeIndex;
		}

		void timsort() {
			const int minRun = 32;

			auto mergeRun = [this](Node* start, Node* end) {
				int len = end == nullptr ? sz : (end - start + 1);
				if (len < 2) {
					return;
				}
				int run = 1;
				while (run * run < len) {
					run <<= 1;
				}
				int left = 0, mid = left + run, right = mid + run;
				if (mid >= len) {
					mid = len;
				}
				if (right >= len) {
					right = len;
				}
				if (run < minRun) {
					insertionSort(start);
					return;
				}
				while (right <= len) {
					if (right < len && end != nullptr && end->data < getNode(right)->data) {
						right = len;
					}
					if (end == nullptr || end->data >= getNode(right - 1)->data) {
						reverse(getNode(left), getNode(mid));
						reverse(getNode(mid), getNode(right));
						reverse(getNode(left), getNode(right));
					}
					left += run;
					mid += run;
					right += run;
					if (mid >= len) {
						mid = len;
					}
					if (right >= len) {
						right = len;
					}
				}
			}

			Node * current = head;
			Node* prev = nullptr;
			int count = 1;
			std::vector<Node*> runStack;
			while (current != nullptr) {
				if (prev == nullptr || prev->data <= current->data) {
					count++;
				}
				else {
					if (count > 1) {
						runStack.push_back(prev);
						mergeRun(prev, current->prev);
						prev = current;
						count = 1;
					}
				}
				prev = current;
				current = current->next;
			}
			if (count > 1) {
				runStack.push_back(prev);
				mergeRun(prev, tail);
			}

			while (runStack.size() > 1) {
				Node* right = runStack.back();
				runStack.pop_back();
				Node* left = runStack.back();
				mergeRun(left, right);
			}
		}
	};

	template <typename T> void vector<T>::insert(T data) {
		if (len == 0) {
			push_back(data);
		}
		else if (is_sorted) { //1
			bool ok = false;  //2
			if (capacity < len + 1) {
				capacity *= 2;
				T* aux = new T[capacity]; //1
				for (int i = 0; i <= len; i++) { //n + 2
					if (i > len - 1 && !ok) {
						aux[i] = data;
						break;
					}
					else if (!ok && comp(data, vec[i])) { //bc: 1 | wc: 4
						ok = true; //1
						aux[i] = data; //1
					}
					else {
						aux[i] = vec[i - ok]; //2
					}
				}
				vec = aux; //1
				len++; //1
			}
			else {
				int pos;
				for (int i = 0; i <= len; i++) {
					if (i == len && !ok) {
						pos = i;
						break;
					}
					else if (!ok && comp(data, vec[i])) {
						ok = true;
						pos = i;
						break;
					}
					else {
						vec[i] = vec[i];
					}
				}
				if (ok) {
					for (int i = len - 1; i >= pos; i--) {
						vec[i + 1] = vec[i];
					}
				}
				vec[pos] = data;
				len++;
			}
		}
		else {
			push_back(data); //n
			shsort(*this, comp); //nlog(n)
			is_sorted = true; //1
		}
		//bc: 6n + 6 | wc: nlog(n) + 2
		//if(n <= 68) O(n) else O(nlog(n))
	}

	template <typename T> void list<T>::insert(T data) {
		if (is_sorted) {
			bool ok = false;
			node* prev = nullptr;

			if (len == 0 || comp(data, ini->data)) {
				push_front(data);
				return;
			}
			if (!comp(data, back->data)) {
				push_back(data);
				return;
			}
			for (node* n = ini->next; !comp(data, n->data); n = n->next) {
				prev = n;
			}
			node* nn = new node(data, prev->next);
			prev->next = nn;
			len++;
		}
		else {
			push_back(data);
			ssort(*this, comp);
			is_sorted = true;
		}
	}

}
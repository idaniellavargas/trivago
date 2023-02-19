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

		int partition(int low, int high) {
			T pivot = vec[high];
			int i = low - 1;
			for (int j = low; j <= high - 1; j++) {
				if (comp(vec[j], pivot)) {
					i++;
					std::swap(vec[i], vec[j]);
				}
			}
			auto temp = vec[i + 1];
			vec[i + 1] = vec[high];
			vec[high] = temp;

			return(i + 1);
		}

		void quickSort(int low, int high) {
			if (low < high) {
				int pi = partition(low, high);
				quickSort(low, pi - 1);
				quickSort(pi + 1, high);
			}
		}

		void sort() {
			if (is_sorted) return;
			quickSort(0, len - 1);
			is_sorted = true;
		}
	};

	template<typename T> class list {
	private:
		struct node {
			T data;
			node* next;
			node* prev;


			node(T d, node* n = nullptr, node* p = nullptr) {
				data = d;
				next = n;
				prev = p;
			}

			node(const node& d) {
				data = d.data;
				next = d.next;
				prev = d.prev;

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

			Iterator& operator--() {
				if (cn != nullptr) cn = cn->prev;
				return *this;
			}

			Iterator& operator--(int) {
				Iterator iterator = *this;
				--* this;
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

			void erase() {
				cn->prev->next = cn->next;
				cn->next->prev = cn->prev;
				cn->next = nullptr;
				delete cn;
			}

			void newnext(Iterator rhs) {
				cn->next = rhs.cn;
			}

			void newprev(Iterator rhs) {
				cn->prev = rhs.cn;
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

		node* ida(node* nn) {
			if (nn->next == nullptr) {
				back = new node(nn->data);
				return back;
			}
			else {
				return new node(nn->data, ida(nn->next));
			}
		}

		void copyList(node* nn) {
			ini = ida(nn);
			auto it1 = begin();
			auto it2 = begin()++;
			for (; it2 != end(); it2++) {
				it2.newprev(it1);
				it1++;
			}
		}

		list(const list& nl) {
			is_sorted = nl.is_sorted;
			len = nl.len;
			if (nl.ini == nullptr) {
				ini = nullptr;
			}
			else {
				if (nl.ini != nullptr) copyList(nl.ini);
			}
		}

		list<T>& operator= (const list<T>& rhs) {
			if (this == &rhs) return *this;
			while (len != 0) pop_front();
			if (rhs.ini == nullptr) {
				ini = nullptr;
				return *this;
			}
			copyList(rhs.ini);
			is_sorted = rhs.is_sorted;
			len = rhs.len;
			return *this;
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

		node* getlast(node* rhs) {
			while (rhs != nullptr && rhs.next != nullptr) {
				rhs = rhs->next;
			}
			return rhs;
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
				ini->prev = n;
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
				n->prev = back;
				back = n;
			}
			len++;
		}

		void pop_back() {
			if (len == 0) return;
			node* aux = back;
			back = back->prev;
			if (back != nullptr) back->next = nullptr;
			delete aux;
			len--;
		}

		void pop_front() {
			if (len == 0) return;
			node* aux = ini;
			ini = ini->next;
			if (ini != nullptr) ini->prev = nullptr;
			aux->next = nullptr;
			delete aux;
			len--;
		}

		void erase(int x) {
			node* crawler = ini;
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

			while (x--) crawler = crawler->next;
			crawler->prev->next = crawler->next;
			crawler->next->prev = crawler->prev;
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
					crawler++;
				}
				if (crawler == end()) return;
				crawler.erase();
			}
		}

		int size() {
			return len;
		}

		node* top() {
			return ini;
		}

		void setComp(func comp) { this->comp = comp; }

		void setSorted(bool b) { is_sorted = b; }

		void merge(list<T>& left, list<T>& right)
		{
			list<T> result;

			auto left_it = left.begin();
			auto right_it = right.begin();

			while (left_it != nullptr && right_it != nullptr)
			{
				if (**left_it < **right_it)
				{
					result.push_back(*left_it);
					left_it++;
				}
				else
				{
					result.push_back(*right_it);
					right_it++;
				}
			}

			while (left_it != nullptr)
			{
				result.push_back(*left_it);
				left_it++;
			}

			while (right_it != nullptr)
			{
				result.push_back(*right_it);
				right_it++;
			}

			this->ini = result.ini;
			this->back = result.ini;
			this->len = result.len;

			result.ini = nullptr;
			result.back = nullptr;
			result.len = 0;
		}
		void merge_sort()
		{
			if (len <= 1 || is_sorted) return;

			list<T> left_half;
			list<T> right_half;
			auto it = ini;
			for (int i = 0; i < len; ++i)
			{
				if (i < len / 2) left_half.push_back(it->data);
				else right_half.push_back(it->data);
				it = it->next;
			}

			left_half.merge_sort();
			right_half.merge_sort();

			this->merge(left_half, right_half);
			is_sorted = true;
		}

		void swap(int i, int k, node* swapList) {
			node* temp1 = swapList, * temp2 = swapList;
			for (int j = 0; j < i; j++) {
				temp1 = temp1->next;
			}
			for (int j = 0; j < k; j++) {
				temp2 = temp2->next;
			}
			T number = temp1->data;
			temp1->data = temp2->data;

			temp2->data = number;

		}

		void heapify(node* temp, int n, int i) {
			int largest = i;
			int l = 2 * i + 1;
			int r = 2 * i + 2;
			node* largesti = temp;
			for (int k = 0; k < largest; k++) {
				largesti = largesti->next;
			}
			node* li = temp;
			for (int k = 0; k < l; k++) {
				if (li == NULL)
					break;
				li = li->next;
			}
			node* ri = NULL;
			if (li != NULL) ri = li->next;

			if (li != NULL)
				if (l < n && *(li->data) > *(largesti->data)) {
					largest = l;
					largesti = li;
				}
			if (ri != NULL)
				if (r < n && *(ri->data) > *(largesti->data))
					largest = r;

			if (largest != i)
			{
				swap(i, largest, temp);
				heapify(temp, n, largest);
			}
		}

		void heap_sort() {
			if (len <= 1 || is_sorted) return;
			int n = len + 1;
			n -= 1;
			node* temp = ini;
			for (int i = n / 2 - 1; i >= 0; i--)
				heapify(temp, n, i);

			for (int i = n - 1; i >= 0; i--)
			{
				swap(0, i, temp);


				heapify(temp, i, 0);
			}
			is_sorted = true;
		}

		node* partition(node* head, node* end, node* nhead, node* nend) {
			node* pivot = back;
			node* prev = nullptr, * cur = head, * tail = pivot;

			while (cur != pivot) {
				if (comp(cur->data, pivor->data)) {
					if ((*nhead) == nullptr) (*nhead) = cur;

					prev = cur;
					cur = cur->next;
				}
				else {
					if (prev) prev->next = cur->next;
				node* tmp = cur->next;
				cur->next = nullptr;
				tail->next = cur;
				tail = cur;
				cur = tmp;
				}

			}
			if ((*nhead) == nullptr) (*nhead) = pivot;
			(*newEnd) = tail;
			return pivot;
		}

		node* qsrecur(node* head, node* end) {
			if (!head || head == end) {
				return head;
			}

			node* nhead = nullptr, * nend = nullptr;

			node* pivor = partition(head, end, &nhead, &nend);

			if (nhead != pivor) {
				node* tmp = nhead;
				while (tmp->next != pivor)
					tmp = tmp->next;
				tmp->next = nullptr;

				nhead = qsrecur(nhead, tmp);

				tmp = getlast(nhead);
				tmp->next = pivot;
			}
			pivot->next = qsrecur(pivot->next, nend);

			return nhead;
		}

		void quickSort() {
			if (len <= 1 || is_sorted) return;
			ini = qsrecur(ini, back);
			is_sorted = true;
		}
		
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
			if (key < node->key) {
				node->left = insert(node->left, key, data);
			}
			else if (key > node->key) {
				node->right = insert(node->right, key, data);
			}
			else return node;

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

		list<T>* getList(list<T>* l) {
			enOrden([&l](string s, T e) { l->push_back(e); });
			return l;
		}
	};

	template <typename T> class hashAVL {
	private:
		int bucket;
		AVLTree<T>* table;
		int len;
		func comp;

	public:
		hashAVL(int b) {
			bucket = b;
			table = new AVLTree<T>[b];
			len = 0;
			comp = [](T& a, T& b) {return *a < *b; };
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

		list<T>* getList() {
			list<T>* l = new list<T>;
			l->setComp(comp);
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

}
#pragma once
#include <iostream>
#include <functional>

#define func std::function<bool(T&, T&)>


namespace UPC {

	//version 5.0: ahora con menos crash
	//version 6.0: agregué los sorts. Insertion sort para lista y vector implementados en las clases.
	//version 6.1: problemas de memoria.
	//version 6.2: copia de listas recursivas implementadas

	template <typename T>  class vector {
	public:
		T* vec;
		int len;
		bool is_sorted;
		bool point;
		func comp;

		vector() {
			vec = new T[1];
			len = 0;
			is_sorted = true;
			comp = [](T& a, T& b) -> bool {
				return a < b;
			};
		}
		~vector() {
			delete[]vec;
		};

		vector(const vector& nv) {
			vec = new T[nv.len];
			len = nv.len;
			is_sorted = nv.sorted;
			for (int i = 0; i < len; i++) {
				vec[i] = nv.vec[i];
			}
		}

		T& operator[](const int& index) { return vec[index]; }
		vector<T>& operator= (const vector<T>& rhs) {
			if (this == &rhs) return *this;
			delete[]vec;
			vec = new T[rhs.len];
			len = rhs.len;
			is_sorted = rhs.is_sorted;
			for (int i = 0; i < len; i++) {
				vec[i] = rhs.vec[i];
			}
			return *this;
		}

		void push_back(T elem) {
			T* aux = new T[len + 1];
			if (len != 0 && comp(elem, vec[len - 1])) is_sorted = false;
			for (int i = 0; i < len; i++) {
				aux[i] = vec[i];
			}
			aux[len] = elem;
			vec = aux;
			len++;
		}

		void push_front(T elem) {
			T* aux = new T[len + 1];
			if (len != 0 && !comp(elem, vec[0])) is_sorted = false;
			aux[0] = elem;
			for (int i = 1; i <= len; i++) {
				aux[i] = vec[i - 1];
			}
			vec = aux;
			len++;
		}

		void pop_back() {
			if (len == 0) return;
			T* aux = new T[len - 1];
			for (int i = 0; i < len - 1; i++) {
				aux[i] = vec[i];
			}

			T* to_delete = vec[len - 1];
			delete to_delete;
			vec = aux;
			len--;
		}

		void pop_front() {
			if (len == 0) return;
			T* aux = new T[len - 1];
			for (int i = 1; i < len; i++) {
				aux[i - 1] = vec[i];
			}

			T* to_delete = vec[0];
			delete to_delete;
			vec = aux;
			len--;
		}

		void erase(int x) {
			if (len == 0) return;
			T* aux = new T[len - 1];
			int j = 0;
			for (int i = 0; i < len; i++) {
				if (i == x) continue;
				aux[j] = vec[i];
				j++;
			}
			vec = aux;
			len--;
		}

		void erase(T* it) {
			if (len == 0) return;
			T* aux = new T[len - 1];
			int j = 0;
			for (int i = 0; i < len; i++) {
				if ((begin() + i) == it) continue;
				aux[j] = vec[i];
				j++;
			}

			vec = aux;
			len--;
		}

		void erase(T* ini, T* fin) {
			if (ini > fin || len == 0) return;

			T* aux = new T[len - (fin - ini)];
			int j = 0;
			bool er = false;
			for (int i = 0; i < len; i++) {
				if ((begin() + i) == ini) er = true;
				else if ((begin() + i) == fin) {
					er = false;
					continue;
				}
				if (er) continue;
				aux[j] = vec[i];
				j++;
			}

			vec = aux;
			len -= (fin - ini) + 1;
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
			len = 0;
			is_sorted = true;
			comp = [](T& a, T& b) { return a < b; };
		}

		~list() {
			while (len != 0) pop_front();
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
				ini = copyList(nl.ini);
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
			delete crawler;
			len--;
		}

		void pop_front() {
			node* aux = ini;
			ini = ini->next;
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
		};

		node* Top;
		int len;

	public:

		stack() {
			Top = nullptr;
			len = 0;
		}
		~stack() { while (!empty()) pop(); }

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
		};

		node* Front;
		node* Back;
		int len;

	public:

		queue() {
			Front = nullptr;
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

	template <typename T> void vector<T>::insert(T data) {
		if (is_sorted) { //1
			bool ok = false;  //2
			T* aux = new T[len + 1]; //1
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
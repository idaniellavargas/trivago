#pragma once
namespace UPC {


	template <typename T>  class vector {
	public:
		T* vec;
		int len;

		vector() {
			vec = new T[1];
			len = 0;
		}
		~vector() {
			delete[]vec;
		};

		T& operator[](const int& index) { return vec[index]; }

		void push_back(T elem) {
			T* aux = new T[len + 1];
			for (int i = 0; i < len; i++) {
				aux[i] = vec[i];
			}
			aux[len] = elem;
			vec = aux;
			len++;
		}

		void pop_back() {
			if (len == 0) return;
			T* aux = new T[len - 1];
			for (int i = 0; i < len - 1; i++) {
				aux[i] = vec[i];
			}

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
	};


	template<typename T> class list {
	private:
		struct node {
			T data;
			node* next;

			node(T d) {
				data = d;
				next = nullptr;
			}
		};


		node* ini;
		int len;
	public:

		list() {
			ini = nullptr;
			len = 0;
		}

		~list() {
			while (len != 0) pop_front();
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

		void push_front(T data) {
			node* n = new node(data);
			n->next = ini;
			ini = n;
			len++;
		}

		void push_back(T data) {
			node* n = new node(data);
			if (ini == nullptr) {
				ini = n;
			}
			else {
				node* crawler = ini;

				while (crawler->next != nullptr) {
					crawler = crawler->next;
				}
				crawler->next = n;
				len++;
			}
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

		int lenght() {
			return len;
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
		};

		node* Top;
		int len;

	public:

		stack() {
			Top = nullptr;
			len = 0;
		}
		~stack() {
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
}
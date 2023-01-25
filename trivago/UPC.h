#pragma once
namespace UPC {


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
}
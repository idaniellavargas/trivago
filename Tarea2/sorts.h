#pragma once

namespace UPC {
	template<typename T> void lswap(typename list<T>::Iterator a, typename list<T>::Iterator b) {
		T aux = *a;
		a = *b;
		b = aux;
	}

	template<typename T> void shuffle(T arr[], int len) {
		for (int i = len - 1; i > 0; i--) {
			int j = (rand() % (i + 1));
			std::swap(arr[i], arr[j]);
		}
	}

	template <typename T> void shuffle(vector<T>& v) {
		for (int i = v.size() - 1; i > 0; i--) {
			int j = (rand() % (i + 1));
			std::swap(v[i], v[j]);
		}
	}

	template <typename T> void shuffle(list<T>& l) {
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

	template <typename T> void esort(vector<T> &v) {
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

	template <typename T> void esort(list<T> &l) {
		for (auto it = l.begin();  it != l.rbegin(); it++) {
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

	template <typename T> void bsort(vector<T> &v) {
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

	template <typename T> void ssort(vector<T> &v) {
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

	template <typename T> void isort(vector<T> &v) {
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

	template <typename T, typename L> void isort(vector<T> &v, L comp) {
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

	template <typename T> void shsort(vector<T> &v) {
		for (int half = v.size() / 2; half > 0; half /= 2) {
			for (int i = half; i < v.size(); i++) {
				for (int j = i - half; j >= 0; j-= half) {
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
}
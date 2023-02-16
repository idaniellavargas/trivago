#pragma once
#define ARCHIVO_HOTELES "hoteles.csv"
#include <functional>
class Hotel {
private:
	string nombre, ID, ubicacion, moneda;
	short huespedes, habitaciones;
	long telefono;
	bool wifi, piscina, spa, parking, mascotas, desayuno;
	float precioVIP, precio;
public:
	Hotel() {}
	~Hotel() {};
	string get_nombre() { return nombre; }
	string get_ID() { return ID; }
	string get_ubicacion() { return ubicacion; }
	string get_moneda() { return moneda; }
	short get_huespedes() { return huespedes; }
	short get_habitaciones() { return habitaciones; }
	float get_precioVIP() { return precioVIP; }
	float get_precio() { return precio; }
	long get_telefono() { return telefono; }
	bool get_wifi() { return wifi; }
	bool get_piscina() { return piscina; }
	bool get_spa() { return spa; }
	bool get_parking() { return parking; }
	bool get_mascotas() { return mascotas; }
	bool get_desayuno() { return desayuno; }
	void set_nombre(const string& n) { nombre = n; }
	void set_ID(string id) { ID = id; }
	void set_ubicacion(string ubicacion) { this->ubicacion = ubicacion; }
	void set_moneda(string moneda) { this->moneda = moneda; }
	void set_huespedes(short huespedes) { this->huespedes = huespedes; }
	void set_habitaciones(short habitaciones) { this->habitaciones = habitaciones; }
	void set_wifi(bool b) { wifi = b; }
	void set_piscina(bool b) { piscina = b; }
	void set_spa(bool b) { parking = b; }
	void set_precioVIP(float precio) { this->precioVIP = precio; }
	void set_precio(float precio) { this->precio = precio; }
	void set_desayuno(bool d) { desayuno = d; }
	void set_parking(bool d) { parking = d; }
	void set_mascotas(bool d) { mascotas = d; }
	void set_telefono(int t) { telefono = t; }
	void agregarHabitacion(short cantidad) { habitaciones += cantidad; }
	void quitarHabitacion(short cantidad) { habitaciones -= cantidad; }

	Hotel(const string& nombre, const string& ID, const string& ubicacion, const string& moneda,
		short huespedes, short habitaciones, long telefono, bool wifi, bool piscina,
		bool spa, bool parking, bool mascotas, bool desayuno, float precio, float precioVIP)
		: nombre(nombre), ID(ID), ubicacion(ubicacion), moneda(moneda),
		huespedes(huespedes), habitaciones(habitaciones), telefono(telefono),
		wifi(wifi), piscina(piscina), spa(spa), parking(parking),
		mascotas(mascotas), desayuno(desayuno), precio(precio), precioVIP(precioVIP) {}
	

	function<void(string)> bordes{
		[](string nombre) {
			if (nombre != "") {
				for (auto &s : nombre) s = toupper(s);
				cout << "\n/============  " << nombre << "  ============/"; }}};

	void toString() {
		bordes(nombre);
		cout << "\nNombre: " << nombre;
		cout << "\nID: " << ID;
		cout << "\nUbicacion: " << ubicacion;
		cout << "\nMoneda: " << moneda;
		cout << "\nHuespedes: " << huespedes;
		cout << "\nHabitaciones restantes: " << habitaciones;
		cout << "\nPrecio: " << precio;
		cout << "\nPrecio VIP: " << precioVIP;
		cout << "\nTelefono: " << telefono;
		cout << "\nWiFi: "; (wifi) ? cout << "Si" : cout << "No";
		cout << "\nPiscina: "; (piscina) ? cout << "Si" : cout << "No";
		cout << "\nSpa: "; (spa) ? cout << "Si" : cout << "No";
		cout << "\nParking: "; (parking) ? cout << "Si" : cout << "No";
		cout << "\nMascotas: "; (mascotas) ? cout << "Si" : cout << "No";
		cout << "\nDesayuno: "; (desayuno) ? cout << "Si" : cout << "No";
		cout << endl;
	}


	bool operator>(const Hotel* rhs) const {
		return nombre > rhs->nombre;
	}

	bool operator<(const Hotel*& rhs) const {
		return nombre < rhs->nombre;
	}

	bool operator<(const Hotel* rhs) const {
		return nombre < rhs->nombre;
	}

	bool operator<(const Hotel& rhs) const {
		return nombre < rhs.nombre;
	}

	string guardar() {
		return nombre + "," + ID + "," + ubicacion + "," + moneda + "," +
			to_string(huespedes) + "," + to_string(habitaciones) + "," + to_string(telefono) + "," +
			(wifi ? "1" : "0") + "," + (piscina ? "1" : "0") + "," + (spa ? "1" : "0") + "," +
			(parking ? "1" : "0") + "," + (mascotas ? "1" : "0") + "," + (desayuno ? "1" : "0") +
			"," + to_string(precio) + "," + to_string(precioVIP) + "\n";
	}

};

template <class T, class S> class HashTable
{
public:
	size_t bucketSize;
	vector<list<pair<T, S>>> table;
	HashTable() {}
	HashTable(std::size_t initial_size, bool strict_mode = false)
	{
		this->bucketSize = strict_mode ? initial_size : this->_next_prime(initial_size);
		for (std::size_t i = 0; i < this->bucketSize; ++i)
		{
			list<std::pair<T, S>> l;
			this->table.push_back(l);
		}
	}

	~HashTable() {}

	std::size_t size() { return bucketSize; }

	void insert(T key, S value)
	{
		if (this->search(key)) return;
		std::size_t index = this->_hash_function(key);
		this->table[index].push_back(std::make_pair(key, value));
	}

	void remove(T key)
	{
		std::size_t index = this->_hash_function(key);
		list<std::pair<T, S>>& temp = this->table[index];
		//temp.remove_if([&key](std::pair<T, S> p) { return key == p.first; });
	}

	S get(T key) {
		if (!search(key)) return NULL;
		std::size_t index = _hash_function(key);
		list<std::pair<T, S>>& items = table[index];

		for (std::pair<T, S>& it : items)
		{
			if (it.first == key)
			{
				return it.second;
			}
		}
	}

	void sort_table() {
		for (std::size_t i = 0; i < this->bucketSize; ++i)
		{
			if (this->table[i].size() == 0) continue;


			list<std::pair<std::string, Hotel*>>& temp = this->table[i];

			for (std::pair<std::string, Hotel*>& it : temp)
			{
				if (it.second->get_ubicacion() == "Peru")it.second->toString();
			}
		}
	}

	void print_all() {
		for (std::size_t i = 0; i < this->bucketSize; ++i)
		{
			if (this->table[i].size() == 0) continue;


			list<std::pair<std::string, Hotel*>>& temp = this->table[i];

			for (std::pair<std::string, Hotel*>& it : temp)
			{
				it.second->toString();
			}
		}
	}

	void save() {
		for (std::size_t i = 0; i < this->bucketSize; ++i)
		{
			if (this->table[i].size() == 0) continue;

			list<std::pair<std::string, Hotel*>>& temp = this->table[i];

			for (std::pair<std::string, Hotel*>& it : temp)
			{
				it.second->guardar();
			}
		}
	}

	void reporte_PE() {
		for (std::size_t i = 0; i < this->bucketSize; ++i)
		{
			if (this->table[i].size() == 0) continue;


			list<std::pair<std::string, Hotel*>>& temp = this->table[i];

			for (std::pair<std::string, Hotel*>& it : temp)
			{
				if (it.second->get_ubicacion() == "Peru")it.second->toString();
			}
		}
	}

	void reporte_breakfast() {
		for (std::size_t i = 0; i < this->bucketSize; ++i)
		{
			if (this->table[i].size() == 0) continue;

			list<std::pair<std::string, Hotel*>>& temp = this->table[i];

			for (std::pair<std::string, Hotel*>& it : temp)
			{
				if (it.second->get_desayuno())it.second->toString();
			}
		}
	}

	bool search(T key)
	{
		std::size_t ind = this->_hash_function(key);
		list<std::pair<T, S>>& items = this->table[ind];

		for (std::pair<T, S>& it : items)
		{
			if (it.first == key)
			{
				return true;
			}
		}

		return false;
	}

	std::size_t count_collisions()
	{
		std::size_t count = 0;

		for (std::size_t i = 0; i < this->bucketSize; ++i)
		{
			if (this->table[i].size() == 0)
			{
				continue;
			}
			count += this->table[i].size() - 1;
		}

		return count;
	}

private:
	bool _is_prime(std::size_t num)
	{
		for (std::size_t i = 2; i * i <= num; ++i)
		{
			if (num % i == 0)
			{
				return false;
			}
		}
		return true;
	}

	std::size_t _next_prime(std::size_t num)
	{
		if (num <= 2)
		{
			return 3;
		}

		std::size_t init, end, ans;

		init = num + 1 + (num % 2);
		end = 2 * init - 2;

		for (ans = init; ans < end; ans = ans + 2)
		{
			if (this->_is_prime(ans))
			{
				break;
			}
		}
		return ans;
	}

	std::size_t _hash_function(int key)
	{
		return key % this->bucketSize;
	}

	std::size_t _hash_function(std::string key)
	{
		return this->_horner_polinomial_hash(key);
	}

	std::size_t _horner_polinomial_hash(std::string key)
	{
		for (char& c : key)
		{
			c = tolower(c);
		}

		const int C = 31;
		std::size_t index = key.at(0) - 'a' + 1;
		std::size_t n = key.size();

		for (std::size_t i = 1; i < n; ++i)
		{
			index = (((index % this->bucketSize * C % this->bucketSize) % this->bucketSize) + ((key.at(i) - 'a' + 1) % this->bucketSize)) % this->bucketSize;
		}

		return index % this->bucketSize;
	}
};


class Catalogo {
private:
	HashTable<string, Hotel*>Hoteles;
public:
	Catalogo() {
		this->Hoteles = HashTable<string, Hotel*>(1000);
		ifstream archivo(ARCHIVO_HOTELES);
		string linea;
		char delimitador = ',';
		while (getline(archivo, linea))
		{
			stringstream stream(linea); // Convertir la cadena a un stream
			string nombre, ID, ubicacion, moneda;
			string huespedes, habitaciones;
			string telefono;
			string wifi, piscina, spa, parking, mascotas, desayuno;
			string precio, precioVIP;
			// Extraer todos los valores de esa fila con getline
			getline(stream, nombre, delimitador);
			getline(stream, ID, delimitador);
			getline(stream, ubicacion, delimitador);
			getline(stream, moneda, delimitador);
			getline(stream, huespedes, delimitador);
			getline(stream, habitaciones, delimitador);
			getline(stream, telefono, delimitador);
			getline(stream, wifi, delimitador);
			getline(stream, piscina, delimitador);
			getline(stream, spa, delimitador);
			getline(stream, parking, delimitador);
			getline(stream, mascotas, delimitador);
			getline(stream, desayuno, delimitador);
			getline(stream, precio, delimitador);
			getline(stream, precioVIP, delimitador);

			Hotel* objHotel = new Hotel();
			objHotel->set_nombre(nombre);
			objHotel->set_ID(generarID(1, nombre, 0));
			objHotel->set_ubicacion(ubicacion);
			objHotel->set_moneda(moneda);
			objHotel->set_huespedes(stoi(huespedes));
			objHotel->set_habitaciones(stoi(habitaciones));
			objHotel->set_telefono(stol(telefono));
			objHotel->set_wifi((bool)(stoi(wifi)));
			objHotel->set_piscina((bool)(stoi(piscina)));
			objHotel->set_spa((bool)(stoi(spa)));
			objHotel->set_parking((bool)(stoi(parking)));
			objHotel->set_mascotas((bool)(stoi(mascotas)));
			objHotel->set_desayuno((bool)(stoi(desayuno)));
			objHotel->set_precio((int)(stoi(precio)));
			objHotel->set_precioVIP((int)(stoi(precioVIP)));

			Hoteles.insert(objHotel->get_ID(), objHotel);
		}
	}

	function<void(string)> agregar{
		[](string id) { if (id != "")cout << "\nRegistro de hotel exitoso"; }
	};

	void agregarHotel(Hotel* hotel) {
		Hoteles.insert(hotel->get_ID(), hotel);
		agregar(hotel->get_ID());
	}
	void eliminarPos(string id) {
		Hoteles.remove(id);
	}

	int get_size() { return Hoteles.size(); }

	void actualizar() {
		/*shsort(Hoteles, [](Hotel* hotel1, Hotel* hotel2)
		{
		if (hotel1->get_ID() != hotel2->get_ID()) return hotel1->get_ID() < hotel2->get_ID(); // IDs incrementandose
		else hotel2->set_ID(generarID(2, hotel2->get_nombre(), 0)); }); //rehacer id si son iguales*/
	}

	void mostrar() {
		Hoteles.print_all();
	}

	void HotelesPeruanos() {
		Hoteles.reporte_PE();
	}
	void HotelesDesayuno() {
		Hoteles.reporte_breakfast();
	}
	/*
	*/
	Hotel* BuscarHotel(string id) { //esta funcion devuelve un hotel con la id provista, else devuelve NULL
		return Hoteles.get(id);
	}

	void guardar() {
		ofstream fout;
		fout.open(ARCHIVO_HOTELES);
		Hoteles.save();
		fout.close();
	}
};

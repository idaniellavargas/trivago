#include <functional>
class Hotel {
private:
	string nombre, ID, ubicacion, moneda;
	short huespedes, habitaciones;
	long telefono;
	bool wifi, piscina, spa, parking, mascotas, desayuno;
public:
	Hotel() {}
	~Hotel() {};
	string get_nombre() { return nombre; }
	string get_ID() { return ID; }
	string get_ubicacion() { return ubicacion; }
	string get_moneda() { return moneda; }
	short get_huespedes() { return huespedes; }
	short get_habitaciones() { return habitaciones; }
	long get_telefono() { return telefono; }
	bool get_wifi() { return wifi; }
	bool get_piscina() { return piscina; }
	bool get_spa() { return spa; }
	bool get_parking() { return parking; }
	bool get_mascotas() { return mascotas; }
	bool get_desayuno() { return desayuno; }
	void set_nombre(string n) { nombre = n; }
	void set_ID(string id) { ID = id; }
	void set_ubicacion(string ubicacion) { this->ubicacion = ubicacion; }
	void set_moneda(string moneda) { this->moneda = moneda; }
	void set_huespedes(short huespedes) { this->huespedes = huespedes; }
	void set_habitaciones(short habitaciones) { this->habitaciones = habitaciones; }
	void set_wifi(bool b) { wifi = b; }
	void set_piscina(bool b) { piscina = b; }
	void set_spa(bool b) { parking = b; }
	void set_desayuno(bool d) { desayuno = d; }
	void set_parking(bool d) { parking = d; }
	void set_mascotas(bool d) { mascotas = d; }
	void set_telefono(int t) { telefono = t; }
	Hotel(string nombre, string ID, string ubicacion, string moneda, short huespedes, short habitaciones, long telefono, bool wifi, bool piscina, bool spa, bool parking, bool mascotas, bool desayuno) {
		this->nombre = nombre;
		this->ID = ID;
		this->ubicacion = ubicacion;
		this->huespedes = huespedes;
		this->habitaciones = habitaciones;
		this->telefono = telefono;
		this->piscina = piscina;
		this->spa = spa;
		this->desayuno = desayuno;
		this->parking = parking;
		this->mascotas = mascotas;
		this->wifi = wifi;
	}
	void toString() {
		string aux = nombre;
		transform(aux.begin(), aux.end(), aux.begin(), ::toupper);
		cout << "\n/============  " << aux << "  ============/";
		cout << "\nNombre: " << nombre;
		cout << "\nID: " << ID;
		cout << "\nUbicacion: " << ubicacion;
		cout << "\nMoneda: " << moneda;
		cout << "\nHuespedes: " << huespedes;
		cout << "\nHabitaciones: " << habitaciones;
		cout << "\nTelefono: " << telefono;
		cout << "\nWiFi: "; (wifi) ? cout << "Si" : cout << "No";
		cout << "\nPiscina: "; (piscina) ? cout << "Si" : cout << "No";
		cout << "\nSpa: "; (spa) ? cout << "Si" : cout << "No";
		cout << "\nParking: "; (parking) ? cout << "Si" : cout << "No";
		cout << "\nMascotas: "; (mascotas) ? cout << "Si" : cout << "No";
		cout << "\nDesayuno: "; (desayuno) ? cout << "Si" : cout << "No";
		cout << endl;
	}

	bool operator>(Hotel* rhs) {
		return nombre > rhs->nombre;
	}

	bool operator<(Hotel* rhs) {
		return nombre < rhs->nombre;
	}
};
class Catalogo {
private:
	vector<Hotel*>Hoteles;
public:
	Catalogo() {
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
			Hoteles.insert(objHotel);
		}
	}

	function<void(string)> agregar{
		[](string id) { if (id != "")cout << "\nRegistro de hotel exitoso"; }
	};

	void agregarHotel(Hotel* hotel) {
		Hoteles.insert(hotel);
		agregar(hotel->get_ID());
	}
	void eliminarPos(int pos) {
		Hoteles.erase(Hoteles.begin() + pos);
	}

	int get_size() { return Hoteles.size(); }
	Hotel* get_pos(int i) { return Hoteles[i]; }
	void actualizar() {
		sort(Hoteles.begin(), Hoteles.end(), [](Hotel* hotel1, Hotel* hotel2)
		{
		if (hotel1->get_ID() != hotel2->get_ID()) return hotel1->get_ID() < hotel2->get_ID(); // IDs incrementandose
		else hotel2->set_ID(generarID(2, hotel2->get_nombre(), 0)); }); //rehacer id si son iguales
	}

	
	
	Hotel* modificar(int pos) {
		for (int i = 0; i < Hoteles.size(); i++)
		{
			return Hoteles[pos];
		}

	}

	void mostrar() {
		actualizar();
		for (int i = 0; i < Hoteles.size(); i++) Hoteles[i]->toString();
	}

	Hotel* BuscarHotel(string id) { //esta funcion devuelve un hotel con la id provista, else devuelve NULL
		for (auto h : Hoteles) {
			if (h->get_ID() == id) return h;
		}
		return NULL;
	}
};

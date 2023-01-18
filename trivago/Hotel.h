#include "Recursos.h"

using namespace std;


//getline eliminar demas, getters y setters, llamar objetos
string hotelNombre[7] = { "Marriot","Bolivar","Shell", "Winston", "Paris","Casa Andina", "Trivago" };
string hotelUbicacion[7] = { "Isla de la Cite","San Luis","Barrio Latino", "Montmartre", "La Defensa","Campos Eliseos", "Plaza de la Concordia" };
//getline
class CHotel {
private:
	string nombre, ID, ubicacion, moneda;
	short huespedes, habitaciones;
	int telefono;
	bool wifi, piscina, spa, parking, mascotas, desayuno;
public:
	CHotel();
	~CHotel() {};
	// getters y setters
	string get_nombre() { return nombre; }
	string get_ID() { return ID; }
	string get_ubicacion() { return ubicacion; }
	string get_moneda() { return moneda; }
	short get_huespedes() { return huespedes; }
	short get_habitaciones() { return habitaciones; }
	int get_telefono() { return telefono; }
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
	void set_wifi(bool b){wifi=b;}
	void set_piscina(bool b){piscina=b;}
	void set_spa(bool b){parking=b;}
	void set_desayuno(bool d) { desayuno = d; }
	void set_parking(bool d) { parking = d; }
	void set_mascotas(bool d) { mascotas = d; }

	void set_telefono(int t) { telefono = t; }

	void toString();
	CHotel(string nombre, string ID, string ubicacion, short huespedes, short habitaciones, int telefono, bool piscina, bool spa, bool desayuno, bool parking, bool mascotas) {
		nombre = hotelNombre[rand() % 7];
		ubicacion = hotelUbicacion[rand() % 7];
		desayuno = rand() % 2;
		telefono = rand() % 8000000 + 10000000;
	}
};

CHotel::CHotel() {
	nombre = hotelNombre[rand() % 7];
	ubicacion = hotelUbicacion[rand() % 7];
	desayuno = rand() % 2;
	telefono = rand() % 8000000 + 10000000;
}

void CHotel::toString() { //para imprimir string
	cout << "Nombre: " << nombre << "\n";
	cout << "ID: "<< ID << "\n";
	cout << "Ubicacion: " << ubicacion << "\n";
	cout << "Moneda: " << moneda << "\n";
	cout << "Huespedes: " << huespedes << "\n";
	cout << "Habitaciones: " << habitaciones << "\n";
	cout << "Telefono: " << telefono << "\n";
	cout << "WiFi: "; (wifi == true) ? cout << "Si" : cout << "No";
	cout << endl;
	cout << "Piscina: "; (piscina == true) ? cout << "Si" : cout << "No";
	cout << endl;
	cout << "Spa: "; (spa == true) ? cout << "Si" : cout << "No";
	cout << endl;
	cout << "Parking: "; (parking == true) ? cout << "Si" : cout << "No";
	cout << endl;
	cout << "Mascotas: "; (mascotas == true) ? cout << "Si" : cout << "No";
	cout << endl;
	cout << "Desayuno: "; (desayuno == true) ? cout << "Si" : cout << "No";
	cout << endl;
	cout << "===================" << endl;
}

//clase controladora-->agrega,modifica,elimina, controlar aspectoz de registros y reportes
class ArrHotel {
private:
	vector<CHotel*>Hoteles;
public:
	ArrHotel() {
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
			CHotel* objHotel = new CHotel();
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
			Hoteles.push_back(objHotel);
		}
	}
	void agregarHotel(CHotel* hotel) {
		Hoteles.push_back(hotel);
	}
	int get_size() { return Hoteles.size(); }
	auto get_pos(int i) { return Hoteles[i]; }
	void actualizar() {
		sort(Hoteles.begin(), Hoteles.end(), [](CHotel* hotel1, CHotel* hotel2)
			{
				if (hotel1->get_ID() != hotel2->get_ID()) return hotel1->get_ID() < hotel2->get_ID(); // IDs incrementandose
				else hotel2->set_ID(generarID(2,hotel2->get_nombre(),0)); }); //rehacer id si son iguales
	}


	CHotel* modificar(int pos) {
		for (int i = 0; i < Hoteles.size(); i++)
		{
			return Hoteles[pos];
		}

	}

	void mostrar() {
		actualizar();
		for (int i = 0; i < Hoteles.size(); i++) Hoteles[i]->toString();
	}

	CHotel* BuscarHotel(string id) { //esta funcion devuelve un hotel con la id provista, else devuelve NULL
		for (auto h : Hoteles) {
			if (h->get_ID() == id) return h;
		}
		return NULL;
	}
};


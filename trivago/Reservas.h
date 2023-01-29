#pragma once
#include "Hotel.h"
#include "Recursos.h"
#define ARCHIVO_RESERVAS "reservas.csv"

class Reserva {
private:
	Date* fecha;
	Hotel* hotel;
	string titular, correo, estado, moneda;
	short huespedes, habitacion;
	bool wifi, piscina, spa, parking, mascotas, desayuno, VIP;
public:
	Reserva() {}
	~Reserva() {};
	string get_titular() { return titular; }
	string get_fecha() { return fecha->getDate(); }
	string get_idHotel() { return hotel->get_ID(); }
	string get_correo() { return correo; }
	string get_estado() { return estado; }
	string get_moneda() { return moneda; }
	short get_huespedes() { return huespedes; }
	short get_habitacion() { return habitacion; }
	bool get_wifi() { return wifi; }
	bool get_piscina() { return piscina; }
	bool get_spa() { return spa; }
	bool get_parking() { return parking; }
	bool get_mascotas() { return mascotas; }
	bool get_desayuno() { return desayuno; }
	void set_titular(string n) { titular = n; }
	void set_hotel(Hotel* h) { hotel = h; }
	void set_moneda(string moneda) { this->moneda = moneda; }
	void set_huespedes(short huespedes) { this->huespedes = huespedes; }
	void set_habitacion(short habitaciones) { this->habitacion = habitacion; }
	void set_wifi(bool b) { wifi = b; }
	void set_piscina(bool b) { piscina = b; }
	void set_spa(bool b) { parking = b; }
	void set_desayuno(bool d) { desayuno = d; }
	void set_parking(bool d) { parking = d; }
	void set_mascotas(bool d) { mascotas = d; }
	void set_correo(string d) { correo = d; }

	Reserva(string titular, string ID, bool VIP, string correo) {
		Catalogo* h;
		this->titular = titular;
		hotel = h->BuscarHotel(ID);
		this->moneda = hotel->get_moneda();
		this->piscina = hotel->get_piscina();
		this->spa = hotel->get_spa();
		this->desayuno = hotel->get_desayuno();
		this->parking = hotel->get_parking();
		this->mascotas = hotel->get_mascotas();
		this->wifi = hotel->get_wifi();
		this->correo = correo;
	}
	void toString() {
		cout << "\n::===========================::";
		cout << "\nNombre del titular: " << titular;
		cout << "\nFecha: " << fecha->getDate();
		cout << "\nID del Hotel: " << hotel->get_ID();
		cout << "\nMoneda: " << moneda;
		cout << "\nMaximo de huespedes: " << huespedes;
		cout << "\nHabitacion a reservar: " << habitacion;
		cout << "\nWiFi: "; (wifi) ? cout << "Si" : cout << "No";
		cout << "\nPiscina: "; (piscina) ? cout << "Si" : cout << "No";
		cout << "\nSpa: "; (spa) ? cout << "Si" : cout << "No";
		cout << "\nParking: "; (parking) ? cout << "Si" : cout << "No";
		cout << "\nMascotas: "; (mascotas) ? cout << "Si" : cout << "No";
		cout << "\nDesayuno: "; (desayuno) ? cout << "Si" : cout << "No";
		cout << endl;
	}
};

class Reservas {
private:
	vector<Reserva*>reservas;
public:
	Reservas() {
		ifstream archivo(ARCHIVO_RESERVAS);
		string linea;
		char delimitador = ',';
		while (getline(archivo, linea))
		{
			stringstream stream(linea); // Convertir la cadena a un stream
			string fecha;
			string ID;
			string titular, correo, estado, moneda;
			string huespedes, habitacion;
			string wifi, piscina, spa, parking, mascotas, desayuno, VIP;

			// Extraer todos los valores de esa fila con getline
			getline(stream, fecha, delimitador);
			getline(stream, ID, delimitador);
			getline(stream, titular, delimitador);
			getline(stream, correo, delimitador);
			getline(stream, estado, delimitador);
			getline(stream, moneda, delimitador);
			getline(stream, huespedes, delimitador);
			getline(stream, habitacion, delimitador);
			getline(stream, wifi, delimitador);
			getline(stream, piscina, delimitador);
			getline(stream, spa, delimitador);
			getline(stream, parking, delimitador);
			getline(stream, mascotas, delimitador);
			getline(stream, desayuno, delimitador);
			getline(stream, VIP, delimitador);

			Reserva* objReserva = new Reserva();
			Catalogo* cat = new Catalogo();
			Hotel* ho = new Hotel();
			objReserva->set_titular(titular);
			objReserva->set_hotel(cat->BuscarHotel(ID));
			objReserva->set_correo(correo);
			objReserva->set_moneda(moneda);
			objReserva->set_huespedes(stoi(huespedes));
			objReserva->set_habitacion(stoi(habitacion));
			objReserva->set_wifi((bool)(stoi(wifi)));
			objReserva->set_piscina((bool)(stoi(piscina)));
			objReserva->set_spa((bool)(stoi(spa)));
			objReserva->set_parking((bool)(stoi(parking)));
			objReserva->set_mascotas((bool)(stoi(mascotas)));
			objReserva->set_desayuno((bool)(stoi(desayuno)));
			reservas.push_back(objReserva);
		}
	}

	function<void(string)> agregar{
		[](string id) { if (id != "")cout << "\nRegistro de Reserva exitoso"; }
	};

	void agregarReserva(Reserva* Reserva) {
		reservas.push_back(Reserva);
		agregar(Reserva->get_titular());
	}
	void eliminarPos(int pos) {
		reservas.erase(reservas.begin() + pos);
	}

	int get_size() { return reservas.size(); }
	Reserva* get_pos(int i) { return reservas[i]; }
	void actualizar() {
		sort(reservas.begin(), reservas.end(), [](Reserva* Reserva1, Reserva* Reserva2) {
			return Reserva1->get_fecha() < Reserva2->get_fecha(); });
	}

	Reserva* modificar(int pos) {
		for (int i = 0; i < reservas.size(); i++)
		{
			return reservas[pos];
		}
	}

	void mostrar() {
		actualizar();
		for (int i = 0; i < reservas.size(); i++) reservas[i]->toString();
	}

	Reserva* BuscarReservaTitular(string nombre) { //esta funcion devuelve un Reserva con el nombre provisto, else devuelve NULL
		Catalogo* c;
		for (auto h : reservas) {
			if (h->get_titular() == nombre && h->get_idHotel() == c->BuscarHotel(h->get_idHotel())->get_ID())return h;
		}
		return NULL;
	}

};
  
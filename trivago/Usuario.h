#pragma once
#include "Recursos.h"


using namespace std;
using namespace UPC;

class Usuario
{
private:
	string nombre, correo, contrasena;
public:
	Usuario() {}
	Usuario(string nombre, string correo, string contrasena) {
		this->nombre = nombre;
		this->correo = correo;
		this->contrasena = contrasena;
		confirmar(correo);
	}
	~Usuario() {}
	void Actualizar(string nombre, string correo, string contrasena) {
		this->nombre = nombre;
		this->correo = correo;
		this->contrasena = contrasena;
		confirmar(correo);
	}
	void ActualizarContr(string contra) {
		vector<string> l;
		string linea;
		ifstream larchivo("Cuentas.txt");
		while (getline(larchivo, linea)) {
			l.push_back(linea);
		}
		larchivo.close();

		for (int i = 1; i < l.size(); i += 3)
		{
			if (l[i] == this->correo)
			{
				l[i + 1] = contra;
				this->contrasena = contra;
			}
		}

		ofstream archivo;
		archivo.open("Cuentas.txt", ios::out);
		for (int i = 0; i < l.size(); i++)
		{
			archivo << l[i] << endl;
		}
		archivo.close();
	}	void ActualizarUsuar(string nick) {
		vector<string> l;
		string linea;
		ifstream larchivo("Cuentas.txt");
		while (getline(larchivo, linea)) {
			l.push_back(linea);
		}
		larchivo.close();

		for (int i = 1; i < l.size(); i += 3)
		{
			if (l[i] == this->correo)
			{
				l[i - 1] = nick;
				this->nombre = nick;
			}
		}

		ofstream archivo;
		archivo.open("Cuentas.txt", ios::out);
		for (int i = 0; i < l.size(); i++)
		{
			archivo << l[i] << endl;
		}
		archivo.close();
	}
	function<void(string)> agendacionExitosa{
		[](string id) { if (id != "")cout << "\nAgendacion exitosa"; }
	};
	void ActualizarCorr(string corr) {
		vector<string> l;
		string linea;
		ifstream larchivo("Cuentas.txt");
		while (getline(larchivo, linea)) {
			l.insert(linea);
		}
		larchivo.close();

		for (int i = 1; i < l.size(); i + 3)
		{
			if (l[i] == this->correo)
			{
				l[i] = corr;
				this->correo = corr;
			}
		}

		ofstream archivo;
		archivo.open("Cuentas.txt", ios::out);
		for (int i = 0; i < l.size(); i++)
		{
			archivo << l[i] << endl;
		}
		archivo.close();
	}
	function<void(string)> confirmar{
		[](string correo) { if (correo != "")cout << "\nRegistro de usuario exitoso"; }
	};
	void setnombre(string n) {
		this->nombre = n;
	}
	void setcorreo(string cor) {
		this->correo = cor;
	}
	void setcontraseña(string con) {
		this->contrasena = con;
	};
	string getnombre() {
		return nombre;
	};
	string getcorreo() {
		return correo;
	}
	bool operator>(Usuario* rhs) {
		return correo > rhs->correo;
	}
	bool operator<(Usuario* rhs) {
		return correo < rhs->correo;
	}
};

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

	Reserva(string titular, Hotel* h, bool VIP, string correo) {

		this->titular = titular;
		this->moneda = h->get_moneda();
		this->piscina = h->get_piscina();
		this->spa = h->get_spa();
		this->desayuno = h->get_desayuno();
		this->parking = h->get_parking();
		this->mascotas = h->get_mascotas();
		this->wifi = h->get_wifi();
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
#define ARCHIVO_RESERVAS "reservas.csv"

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

class Cliente : public Usuario {
private:
	list<Reserva*> reservas;
	float cartera;
	//pair
public:
	Cliente(string nombre, string correo, string contrasena, int cartera) {}
	~Cliente() {}
	float get_cartera() { return cartera; }
	void set_cartera(float cartera) { this->cartera = cartera; }
	void sumarCartera(float cartera) { this->cartera += cartera; }
	void restarCartera(float cartera) { this->cartera -= cartera; }
	
	void reservarHotel(Catalogo* lista) {
		Hotel* h = new Hotel();
		string id;
		cout << "Ingrese el dia el mes y el anho para la reserva" << endl;
		int d, m, y;
		std::cin >> d >> m >> y;
		Date* fecha = new Date(d, m, y);
		do {
			cout << "Ingrese el ID del hotel a reservar:" << endl;
			std::cin >> id;
			h = lista->BuscarHotel(id);
			cout <<  "Usted ha elegido: Hotel" << h->get_nombre() << endl;
		} while (h == nullptr);
		//cout<<h->get_ID();
		cout << "El precio del hotel por persona es: " << h->get_precio() << endl;
		cout << "El precio VIP es de: " << h->get_precioVIP() << endl;
		cout << "Nota* el precio VIP incluye atencion y servicios preferenciales, ademas de la posibilidad de poder cancelar o postergar su reserva hasta 24 horas antes de que se consuma" << endl;
		cout << "¿Desea pagar por el precio normal (1) o el VIP (2)?" << endl;
		short categoria;
		cout << "Ingrese su eleccion: "; cin >> categoria;
		cout << endl;
		if (categoria == 1 && get_cartera() - h->get_precio() >= 0)
		{
			Reserva* reserva = new Reserva(getnombre(),h,0,getcorreo());
			reservas.push_front(reserva);
			agendacionExitosa(id);
		}
		else if (categoria == 2 && get_cartera() - h->get_precioVIP() >= 0)
		{
			Reserva* reserva = new Reserva(getnombre(), h, 1, getcorreo());
			reservas.push_front(reserva);
			agendacionExitosa(id);
		}
		else
		{
			cout << "La reserva no se puede ejecutar: " << endl;
			cout << "Saldo insuficiente" << endl;
		}
		_sleep(2000);
	}

	/*
	void cancelarReserva() {
		bool conf = true;
		int ind = 0;
		float newcart = getcartera();
		string nombreh;
		if (reservas.lenght() != 0)
		{
			cout << "Elija que reserva quiere cancelar: " << endl;
			for (auto i : reservas)
			{
				cout << i.first->get_nombre() << endl;
			}
			do {
				std::cin >> nombreh;
				for (auto i : reservas)
				{
					if (nombreh == i.first->get_nombre())
					{
						newcart += i.first->get_precio();
						setcartera(newcart);
						reservas.erase(ind);
						conf = false;
					}
				}
				if (conf)
				{
					cout << "No se encontro el hotel" << endl;
				}
			} while (conf);

		}
		else
		{
			cout << "No hay reservas" << endl;
		}
	}
	void cambiarfecha() {
		bool conf = true;
		string nombreh;
		int d, m, y;
		if (reservas.lenght() != 0)
		{
			cout << "Ingrese el nuevo dia, mes y el anho para la reserva" << endl;
			std::cin >> d >> m >> y;
			Date* fecha = new Date(d, m, y);
			while (!(fecha->dateIsReal()))
			{
				cout << "Fecha invalida " << endl;
				cout << "Ingrese el nuevo dia, mes y el anho para la reserva" << endl;
				std::cin >> d >> m >> y;
				fecha->set_day(d);
				fecha->set_month(m);
				fecha->set_year(y);
			}
			cout << "Elija que reserva quiere cambiar: " << endl;
			for (auto i : reservas)
			{
				cout << i.first->get_nombre() << endl;
			}
			do {
				std::cin >> nombreh;
				for (auto i : reservas)
				{
					if (nombreh == i.first->get_nombre())
					{
						i.second->set_day(d);
						i.second->set_day(m);
						i.second->set_day(y);
						conf = false;
					}
				}
				if (conf)
				{
					cout << "No se encontro el hotel" << endl;
				}
			} while (conf);
		}
		else
		{
			cout << "No hay reservas" << endl;
		}
	}*/
	//void posterreserva() {}

};

class Administrador : public Usuario {
private:
	short credencial;
public:
	void actualizarCatalogo(){}
	void actualizarCorreo() {}
	void actualizarContrasenha() {}
};


class DueñoHotelero : public Usuario {
private:
	int ganancias;
public:
	int get_ganancias() { return ganancias; }
	void set_ganancias(int ganancias) { this->ganancias = ganancias; }
	void sumarGanancias(int monto) { this->ganancias += monto; }
	void restarGanancias(int monto) { this->ganancias -= monto; }
	void aceptarReserva() {}
	void rechazarReserva() {}
	void revisarGananciasPorMes() {}
	void actualizarServicios() {}
};



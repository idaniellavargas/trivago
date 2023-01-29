#pragma once
#include "Recursos.h"
#include <list>

using namespace std;

class Usuario
{
protected:
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
	
	function<void(string)> agendacionExitosa{
		[](string id) { if (id != "")cout << "\nAgendacion exitosa"; }
	};

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
	string fecha;
	Hotel* hotel;
	string titular, correo, estado, moneda;
	short huespedes, habitacion;
	bool wifi, piscina, spa, parking, mascotas, desayuno, VIP;
	float monto;
public:
	Reserva() {}
	~Reserva() {};
	string get_titular() { return titular; }
	float get_monto() {
		return monto;
	}
	void set_monto(float monto) {
		this->monto = monto;
	}
	string get_fecha() { return fecha; }
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

	void set_estado(string estado) {
		this->estado = estado;
	}
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
	void set_fecha(string d) { fecha = d; }
	

	Reserva(string titular, Hotel* h, string f, bool VIP, string correo) {
		this->hotel = h;
		fecha = f;
		this->titular = titular;
		this->moneda = h->get_moneda();
		this->piscina = h->get_piscina();
		this->spa = h->get_spa();
		this->desayuno = h->get_desayuno();
		this->parking = h->get_parking();
		this->mascotas = h->get_mascotas();
		this->wifi = h->get_wifi();
		this->correo = correo;
		if (VIP)monto = h->get_precioVIP();
		else monto = h->get_precio();
		this->estado = "En espera";
	}
	function<void(string)> save{
		[](string correo) { if (correo != "")cout << "\nReserva guardada en el sistema"; }
	};
	string guardar() {
		save(correo);
		_sleep(2000);
		return fecha + "," + hotel->get_ID() + "," + titular + "," + correo + "," + estado + "," + moneda + ","
			+ to_string(huespedes) + "," + to_string(habitacion) + ","  + to_string(wifi)+
			","+to_string(piscina)+","+to_string(spa) + "," + to_string(parking) + "," + to_string(mascotas) +
			"," + to_string(desayuno) + "," + to_string(monto) + "\n";
	}
	void toString() {
		cout << "\n::===========================::";
		cout << "\nNombre del titular: " << titular;
		cout << "\nFecha: " << fecha;
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
		cout << "\nMonto a pagar: " << monto;
		cout<< "\nEstado: " << estado;
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
			string wifi, piscina, spa, parking, mascotas, desayuno;
			string monto;

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
			getline(stream, monto, delimitador);

			Reserva* objReserva = new Reserva();
			Catalogo* cat = new Catalogo();
			objReserva->set_titular(titular);
			objReserva->set_hotel(cat->BuscarHotel(ID));
			objReserva->set_correo(correo);
			objReserva->set_estado(estado);
			objReserva->set_fecha(fecha);
			objReserva->set_moneda(moneda);
			objReserva->set_huespedes(stoi(huespedes));
			objReserva->set_habitacion(stoi(habitacion));
			objReserva->set_wifi((bool)(stoi(wifi)));
			objReserva->set_piscina((bool)(stoi(piscina)));
			objReserva->set_spa((bool)(stoi(spa)));
			objReserva->set_parking((bool)(stoi(parking)));
			objReserva->set_mascotas((bool)(stoi(mascotas)));
			objReserva->set_desayuno((bool)(stoi(desayuno)));
			objReserva->set_monto((stof(monto)));
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
	int buscar(Reserva* elem) {
		for (int i = 0; i < reservas.size(); i++)if (reservas[i] == elem)return i;
	}
	void mostrar() {
		actualizar();
		for (int i = 0; i < reservas.size(); i++) reservas[i]->toString();
	}
	friend class DueñoHotelero;
	void visualizarReservas(string correo) {
		for (int i = 0; i < reservas.size(); i++) {
			if (reservas[i]->get_correo() == correo)
			reservas[i]->toString();
		}

	}

	std::list<Reserva*> BuscarReservaTitular(string nombre) { 
		std::list<Reserva*>l;

		for (auto h : reservas) {
			if (h->get_titular() == nombre)l.push_front(h);
		}
		return l;
	}
	UPC::queue<Reserva*> BuscarWaitingList(string hotel) { 
		UPC::queue<Reserva*>q;

		for (auto r : reservas) {
			if (r->get_idHotel() == hotel)q.push(r);
		}
		return q;
	}
	void delete_record(int o)
	{
		fstream fin, fout;
		fin.open(ARCHIVO_RESERVAS, ios::in);
		fout.open("reservasnew.csv", ios::out);

		int rollnum, roll1, marks, count = 0, i;
		char sub;
		int index, new_marks;
		string line, word;
		vector<string> row;

		rollnum = o;

		while (!fin.eof()) {

			getline(fin, line);
			stringstream s(line);

			while (getline(s, word, ',')) {
				row.push_back(word);
			}

			int row_size = row.size();
			roll1 = stoi(row[0]);
			if (roll1 != rollnum) {
				if (!fin.eof()) {
					for (i = 0; i < row_size - 1; i++) {
						fout << row[i] << ", ";
					}
					fout << row[row_size - 1] << "\n";
				}
			}
			else {
				count = 1;
			}
			if (fin.eof())
				break;
		}

		fin.close();
		fout.close();

		remove(ARCHIVO_RESERVAS);
		rename("reservasnew.csv", ARCHIVO_RESERVAS);
	}

};


class Administrador : public Usuario {
private:
	int credencial;
	bool permisoCatalogo;
public:
	Administrador() {
		nombre = "";
		correo = "";
		contrasena = "";
		credencial = 0;
		permisoCatalogo = false;
	}
	Administrador(string nombre, string correo, string contrasena, int credencial, bool permisoCatalogo) {
		this->nombre = nombre;
		this->correo = correo;
		this->contrasena = contrasena;
		this->credencial = credencial;
		this->permisoCatalogo = permisoCatalogo;
		confirmar(correo);
	}
	int get_credencial() { return credencial; }
	bool actualizarCatalogo() { return permisoCatalogo; }
};

#define ARCHIVO_ADMINS "admins.csv"
class Administradores {
private:
	vector<Administrador*>admins;
public:
	Administradores() {
		ifstream archivo(ARCHIVO_ADMINS);
		string linea;
		char delimitador = ',';
		while (getline(archivo, linea))
		{
			stringstream stream(linea); // Convertir la cadena a un stream
			string nombre, correo, contrasena, credencial, permisoCatalogo;
			// Extraer todos los valores de esa fila con getline
			getline(stream, nombre, delimitador);
			getline(stream, correo, delimitador);
			getline(stream, contrasena, delimitador);
			getline(stream, credencial, delimitador);
			getline(stream, permisoCatalogo, delimitador);

			Administrador* admin = new Administrador(nombre, correo, contrasena, stoi(credencial),(bool)(stoi(permisoCatalogo)));
			admins.insert(admin);
		}
	}

	function<void(string)> agregar{
		[](string correo) { if (correo != "")cout << "\nRegistro de admin exitoso"; }
	};

	void agregarAdmin(Administrador* admin) {
		admins.insert(admin);
		agregar(admin->getcorreo());
	}
	void eliminarPos(int pos) {
		admins.erase(admins.begin() + pos);
	}

	int get_size() { return admins.size(); }
	Administrador* get_pos(int i) { return admins[i]; }


	Administrador* BuscarAdmin(int credencial) { 
		for (auto a : admins) {
			if (a->get_credencial() == credencial) return a;
		}
		return NULL;
	}
};
using namespace UPC;
class DueñoHotelero : public Usuario {
private:
	int ganancias;
	UPC::queue<Reserva*>waitingList;
	string hotel;
public:
	DueñoHotelero(string nombre, string correo, string contrasena, int ganancias, string hotel) {
		Reservas* r = new Reservas();
		waitingList = r->BuscarWaitingList(hotel);
		this->nombre = nombre;
		this->correo = correo;
		this->contrasena = contrasena;
		this->ganancias = ganancias;
		this->hotel = hotel;
		confirmar(correo);
	}
	string get_hotel() { return hotel; }
	int get_ganancias() { return ganancias; }
	void set_ganancias(int ganancias) { this->ganancias = ganancias; }
	void sumarGanancias(int monto) { this->ganancias += monto; }
	void restarGanancias(int monto) { this->ganancias -= monto; }
	void aceptarReserva() {
		waitingList.front()->set_estado("Aceptada");
		waitingList.pop();
	}
	void rechazarReserva() {
		waitingList.front()->set_estado("Rechazada");
		restarGanancias(waitingList.front()->get_monto());
		waitingList.pop();
	}

	void visualizarWaitingList() {
		UPC::queue<Reserva*>q = waitingList;
		while (!q.empty()) {
			q.front()->toString();
			cout << endl;
			q.pop();
		}
	}

	bool actualizarServicios() { return true; }
};

#define ARCHIVO_DUEÑOS "duenhos.csv"
class Dueños {
private:
	vector<DueñoHotelero*>dueños;
public:
	Dueños() {
		ifstream archivo(ARCHIVO_DUEÑOS);
		string linea;
		char delimitador = ',';
		while (getline(archivo, linea))
		{
			stringstream stream(linea); // Convertir la cadena a un stream
			string nombre, correo, contrasena, ganancias, hotel;
			// Extraer todos los valores de esa fila con getline
			getline(stream, nombre, delimitador);
			getline(stream, correo, delimitador);
			getline(stream, contrasena, delimitador);
			getline(stream, ganancias, delimitador);
			getline(stream, hotel, delimitador);

			DueñoHotelero* dueño = new DueñoHotelero(nombre, correo, contrasena, stoi(ganancias), hotel);
			dueños.insert(dueño);
		}
	}

	function<void(string)> agregar{
		[](string correo) { if (correo != "")cout << "\nRegistro de dueño exitoso"; }
	};

	void agregarDueño(DueñoHotelero* dueño) {
		dueños.insert(dueño);
		agregar(dueño->getcorreo());
	}
	void eliminarPos(int pos) {
		dueños.erase(dueños.begin() + pos);
	}

	int get_size() { return dueños.size(); }
	DueñoHotelero* get_pos(int i) { return dueños[i]; }


	DueñoHotelero* BuscarDueño(string hotel) {
		for (auto d : dueños) {
			if (d->get_hotel() == hotel) return d;
		}
		return NULL;
	}

	void pagar(string hotel, float monto) {
		BuscarDueño(hotel)->sumarGanancias(monto);
	}
	void quitar(string hotel, float monto) {
		BuscarDueño(hotel)->restarGanancias(monto);
	}
};

class Cliente : public Usuario {
private:
	std::list<Reserva*> reservas;
	float cartera;
public:
	Cliente(string nombre, string correo, string contrasena, float cartera) {
		this->nombre = nombre;
		this->correo = correo;
		this->contrasena = contrasena;
		this->cartera = cartera;
		Reservas* r = new Reservas();
		reservas = r->BuscarReservaTitular(nombre);
		confirmar(correo);
	}
	~Cliente() {}
	float get_cartera() { return cartera; }
	void set_cartera(float cartera) { this->cartera = cartera; }
	void sumarCartera(float cartera) { this->cartera += cartera; }
	void restarCartera(float cartera) { this->cartera -= cartera; }

	void reservarHotel(Catalogo* lista, Reservas* re) {
		Hotel* h = new Hotel();
		string id;
		cout << "Ingrese el dia el mes y el año para la reserva" << endl;
		int d, m, y;
		std::cin >> d >> m >> y;
		Date* fecha = new Date(d, m, y);
		do {
			cout << "Ingrese el ID del hotel a reservar:" << endl;
			std::cin >> id;
			h = lista->BuscarHotel(id);
			cout << "Usted ha elegido: Hotel" << h->get_nombre() << endl;
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
			Reserva* reserva = new Reserva(getnombre(), h, fecha->getDate(), 0, getcorreo());
			reservas.push_front(reserva);
			agendacionExitosa(id);
			re->agregarReserva(reserva);
			fstream fout;
			fout.open(ARCHIVO_RESERVAS, ios::out | ios::app);
			fout << reserva->guardar();
			fout.close();
			restarCartera(h->get_precio());
			Dueños* d = new Dueños();
			d->pagar(h->get_ID(), h->get_precio());
			h->quitarHabitacion(1);
			agendacionExitosa(id);
		}
		else if (categoria == 2 && get_cartera() - h->get_precioVIP() >= 0)
		{
			Reserva* reserva = new Reserva(getnombre(), h, fecha->getDate(), 1, getcorreo());
			reservas.push_front(reserva);
			agendacionExitosa(id);
			re->agregarReserva(reserva);
			fstream fout;
			fout.open(ARCHIVO_RESERVAS, ios::out | ios::app);
			fout << reserva->guardar();
			fout.close();
			restarCartera(h->get_precioVIP());
			Dueños* d = new Dueños();
			d->pagar(h->get_ID(), h->get_precioVIP());
			h->quitarHabitacion(1);
			agendacionExitosa(id);
		}
		else
		{
			cout << "La reserva no se pudo concretar: " << endl;
			cout << "Saldo insuficiente" << endl;
		}
		_sleep(2000);
	}
	void cancelarReserva(Reservas* r) {
		bool conf = true;
		int ind = 0;
		int n;
		float reembolso;
		if (reservas.size() != 0)
		{
			cout << "Ingrese el número de la reserva que desea cancelar: " << endl;
			for (auto i : reservas)
			{ //here
				i->toString();
				cout << endl;
			}
			std::cin >> n;

			auto it = reservas.begin();
			advance(it, n - 1);
			auto* p = *it;
			Catalogo* h = new Catalogo();
			h->BuscarHotel(p->get_idHotel())->agregarHabitacion(1);
			reembolso = p->get_monto();
			Dueños* d = new Dueños();
			d->quitar(p->get_idHotel(), reembolso);
			reservas.erase(it);
			cartera += reembolso;
			int pos;
			pos = r->buscar(p);
			r->eliminarPos(pos);
			r->delete_record(pos);
			
		}
	}
	// postergar reserva
	void cambiarfecha(Reservas* r) {
		bool conf = true;
		string nombreh;
		int d, m, y;
		if (reservas.size() != 0)
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
			cout << "Ingrese el número de la reserva a la que desea modificar fecha: " << endl;
			for (auto i : reservas)
			{
				i->toString();
				cout << endl;
			}
			short n;
			std::cin >> n;

			auto it = reservas.begin();
			advance(it, n - 1);
			auto* p = *it;
			p->set_fecha(fecha->getDate());
			conf = false;
			int pos;
			pos = r->buscar(p);
			r->delete_record(pos);
			r->agregarReserva(p);
		}
		if (conf)cout << "No hay reservas en el registro" << endl;
	}
};

#define ARCHIVO_CLIENTES "clientes.csv"
class Clientela {
private:
	vector<Cliente*>clientela;
public:
	Clientela() {
		ifstream archivo(ARCHIVO_CLIENTES);
		string linea;
		char delimitador = ',';
		while (getline(archivo, linea))
		{
			stringstream stream(linea); // Convertir la cadena a un stream
			string nombre, correo, contrasena, cartera;
			// Extraer todos los valores de esa fila con getline
			getline(stream, nombre, delimitador);
			getline(stream, correo, delimitador);
			getline(stream, contrasena, delimitador);
			getline(stream, cartera, delimitador);


			Cliente* cliente = new Cliente(nombre, correo, contrasena, stof(cartera));
			clientela.insert(cliente);
		}
	}

	function<void(string)> agregar{
		[](string id) { if (id != "")cout << "\nRegistro de cliente exitoso"; }
	};

	void agregarCliente(Cliente* cliente) {
		clientela.insert(cliente);
		agregar(cliente->getnombre());
	}
	void eliminarPos(int pos) {
		clientela.erase(clientela.begin() + pos);
	}

	int get_size() { return clientela.size(); }
	Cliente* get_pos(int i) { return clientela[i]; }


	Cliente* BuscarCliente(string correo) { //esta funcion devuelve un hotel con la id provista, else devuelve NULL
		for (auto c : clientela) {
			if (c->getcorreo() == correo) return c;
		}
		return NULL;
	}
};

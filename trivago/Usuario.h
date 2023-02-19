#pragma once
#include "Recursos.h"
#include "Datos.h"

#define ARCHIVO_CLIENTES "clientes.csv"
#define ARCHIVO_ADMINS "admins.csv"
#define ARCHIVO_DUEÑOS "duenhos.csv"
#define ARCHIVO_RESERVAS "reservas.csv"

class Clientela;


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
	}
	~Usuario() {}

	function<void(string)> agendacionExitosa{
		[](string id) { if (id != "")cout << "\nAgendacion exitosa"; }
	};

	void setnombre(string n) {
		this->nombre = n;
	}
	void setcorreo(string cor) {
		this->correo = cor;
	}
	string getContrasena() { return contrasena; }
	void setcontraseña(string con) {
		this->contrasena = con;
	};
	string getnombre() {
		return nombre;
	};
	string getcorreo() {
		return correo;
	}
	void ActualizarUsuario(string usua, short numArch) {
		int opc;
		vector<string> l;
		string nomb, corrv, cont, vr1, vr2;
		string nombreArch;
		char delimitador = ',';
		string linea;
		ifstream larchivo1;

		if (numArch == 1)
		{
			ifstream larchivo1(ARCHIVO_CLIENTES);
			getline(larchivo1, linea);
			while (getline(larchivo1, linea)) {
				stringstream stream(linea);
				getline(stream, nomb, delimitador);
				getline(stream, corrv, delimitador);
				getline(stream, cont, delimitador);
				getline(stream, vr1, delimitador);
				getline(stream, vr2, delimitador);
				l.push_back(nomb);
				l.push_back(corrv);
				l.push_back(cont);
				l.push_back(vr1);
				l.push_back(vr2);
			}
			larchivo1.close();
		}
		else if (numArch == 2)
		{
			ifstream larchivo1(ARCHIVO_ADMINS);
			getline(larchivo1, linea);
			while (getline(larchivo1, linea)) {
				stringstream stream(linea);
				getline(stream, nomb, delimitador);
				getline(stream, corrv, delimitador);
				getline(stream, cont, delimitador);
				getline(stream, vr1, delimitador);
				getline(stream, vr2, delimitador);
				l.push_back(nomb);
				l.push_back(corrv);
				l.push_back(cont);
				l.push_back(vr1);
				l.push_back(vr2);
			}
			larchivo1.close();
		}
		else
		{
			ifstream larchivo1(ARCHIVO_DUEÑOS);
			getline(larchivo1, linea);
			while (getline(larchivo1, linea)) {
				stringstream stream(linea);
				getline(stream, nomb, delimitador);
				getline(stream, corrv, delimitador);
				getline(stream, cont, delimitador);
				getline(stream, vr1, delimitador);
				getline(stream, vr2, delimitador);
				l.push_back(nomb);
				l.push_back(corrv);
				l.push_back(cont);
				l.push_back(vr1);
				l.push_back(vr2);
			}
			larchivo1.close();
		}

		for (int i = 1; i < l.size(); i += 5)
		{
			if (l[i] == this->correo)
			{
				l[i - 1] = usua;
				this->nombre = usua;
				break;
			}
		}

		ofstream archivo;
		archivo.open("archivo2.csv", ios::out);

		archivo << endl;

		for (int i = 0; i < l.size(); i += 5)
		{

			//cout << l[i] << "===" << l[i + 1] << "====" << l[i + 2] << "====" << l[i + 3] << "====" << l[i + 4] << endl;
			archivo << l[i] << "," << l[i + 1] << "," << l[i + 2] << "," << l[i + 3] << "," << l[i + 4] << endl;

		}
		archivo.close();
		if (numArch == 1)
		{
			remove(ARCHIVO_CLIENTES);
			rename("archivo2.csv", ARCHIVO_CLIENTES);
		}
		else if (numArch == 2)
		{
			remove(ARCHIVO_ADMINS);
			rename("archivo2.csv", ARCHIVO_ADMINS);
		}
		else
		{
			remove(ARCHIVO_DUEÑOS);
			rename("archivo2.csv", ARCHIVO_DUEÑOS);
		}
	}

	void ActualizarContra(string contra, short numArch) {
		int opc;
		vector<string> l;
		string nomb, corrv, cont, vr1, vr2;
		string nombreArch;
		char delimitador = ',';
		string linea;
		ifstream larchivo1;

		if (numArch == 1)
		{
			ifstream larchivo1(ARCHIVO_CLIENTES);
			getline(larchivo1, linea);
			while (getline(larchivo1, linea)) {
				stringstream stream(linea);
				getline(stream, nomb, delimitador);
				getline(stream, corrv, delimitador);
				getline(stream, cont, delimitador);
				getline(stream, vr1, delimitador);
				getline(stream, vr2, delimitador);
				l.push_back(nomb);
				l.push_back(corrv);
				l.push_back(cont);
				l.push_back(vr1);
				l.push_back(vr2);
			}
			larchivo1.close();
		}
		else if (numArch == 2)
		{
			ifstream larchivo1(ARCHIVO_ADMINS);
			getline(larchivo1, linea);
			while (getline(larchivo1, linea)) {
				stringstream stream(linea);
				getline(stream, nomb, delimitador);
				getline(stream, corrv, delimitador);
				getline(stream, cont, delimitador);
				getline(stream, vr1, delimitador);
				getline(stream, vr2, delimitador);
				l.push_back(nomb);
				l.push_back(corrv);
				l.push_back(cont);
				l.push_back(vr1);
				l.push_back(vr2);
			}
			larchivo1.close();
		}
		else
		{
			ifstream larchivo1(ARCHIVO_DUEÑOS);
			getline(larchivo1, linea);
			while (getline(larchivo1, linea)) {
				stringstream stream(linea);
				getline(stream, nomb, delimitador);
				getline(stream, corrv, delimitador);
				getline(stream, cont, delimitador);
				getline(stream, vr1, delimitador);
				getline(stream, vr2, delimitador);
				l.push_back(nomb);
				l.push_back(corrv);
				l.push_back(cont);
				l.push_back(vr1);
				l.push_back(vr2);
			}
			larchivo1.close();
		}

		for (int i = 1; i < l.size(); i += 5)
		{
			if (l[i] == this->correo)
			{
				l[i + 1] = contra;
				this->contrasena = contra;
				break;
			}
		}

		ofstream archivo;
		archivo.open("archivo2.csv", ios::out);

		archivo << endl;

		for (int i = 0; i < l.size(); i += 5)
		{
			archivo << l[i] << "," << l[i + 1] << "," << l[i + 2] << "," << l[i + 3] << "," << l[i + 4] << endl;

		}
		archivo.close();
		if (numArch == 1)
		{
			remove(ARCHIVO_CLIENTES);
			rename("archivo2.csv", ARCHIVO_CLIENTES);
		}
		else if (numArch == 2)
		{
			remove(ARCHIVO_ADMINS);
			rename("archivo2.csv", ARCHIVO_ADMINS);
		}
		else
		{
			remove(ARCHIVO_DUEÑOS);
			rename("archivo2.csv", ARCHIVO_DUEÑOS);
		}
	}
	void ActualizarCorr(string corr, short numArch) {
		int opc;
		vector<string> l;
		string nomb, corrv, cont, vr1, vr2;
		string nombreArch;
		char delimitador = ',';
		string linea;
		ifstream larchivo1;

		if (numArch == 1)
		{
			ifstream larchivo1(ARCHIVO_CLIENTES);
			getline(larchivo1, linea);
			while (getline(larchivo1, linea)) {
				stringstream stream(linea);
				getline(stream, nomb, delimitador);
				getline(stream, corrv, delimitador);
				getline(stream, cont, delimitador);
				getline(stream, vr1, delimitador);
				getline(stream, vr2, delimitador);
				l.push_back(nomb);
				l.push_back(corrv);
				l.push_back(cont);
				l.push_back(vr1);
				l.push_back(vr2);
			}
			larchivo1.close();
		}
		else if (numArch == 3)
		{
			ifstream larchivo1(ARCHIVO_ADMINS);
			getline(larchivo1, linea);
			while (getline(larchivo1, linea)) {
				stringstream stream(linea);
				getline(stream, nomb, delimitador);
				getline(stream, corrv, delimitador);
				getline(stream, cont, delimitador);
				getline(stream, vr1, delimitador);
				getline(stream, vr2, delimitador);
				l.push_back(nomb);
				l.push_back(corrv);
				l.push_back(cont);
				l.push_back(vr1);
				l.push_back(vr2);
			}
			larchivo1.close();
		}
		else
		{
			ifstream larchivo1(ARCHIVO_DUEÑOS);
			getline(larchivo1, linea);
			while (getline(larchivo1, linea)) {
				stringstream stream(linea);
				getline(stream, nomb, delimitador);
				getline(stream, corrv, delimitador);
				getline(stream, cont, delimitador);
				getline(stream, vr1, delimitador);
				getline(stream, vr2, delimitador);
				l.push_back(nomb);
				l.push_back(corrv);
				l.push_back(cont);
				l.push_back(vr1);
				l.push_back(vr2);
			}
			larchivo1.close();
		}

		//cout << l.size() << endl;
		for (int i = 1; i < l.size(); i += 5)
		{
			//cout << l[i] << "=======" << this->correo << endl;
			if (l[i] == this->correo)
			{
				//cout << "&&&&&" << endl;
				//cout << "se encontro" << endl;
				//cout << l[i + 1] << "=====" << corr << endl;
				l[i] = corr;
				this->correo = corr;
				//cout << l[i + 1] << "=====" << corr << endl;
				//cout << "&&&&&" << endl;
				break;
			}
		}

		ofstream archivo;
		archivo.open("archivo2.csv", ios::out);

		archivo << endl;

		for (int i = 0; i < l.size(); i += 5)
		{

			//cout << l[i] << "===" << l[i + 1] << "====" << l[i + 2] << "====" << l[i + 3] << "====" << l[i + 4] << endl;
			archivo << l[i] << "," << l[i + 1] << "," << l[i + 2] << "," << l[i + 3] << "," << l[i + 4] << endl;

		}
		archivo.close();
		if (numArch == 1)
		{
			remove(ARCHIVO_CLIENTES);
			rename("archivo2.csv", ARCHIVO_CLIENTES);
		}
		else if (numArch == 3)
		{
			remove(ARCHIVO_ADMINS);
			rename("archivo2.csv", ARCHIVO_ADMINS);
		}
		else
		{
			remove(ARCHIVO_DUEÑOS);
			rename("archivo2.csv", ARCHIVO_DUEÑOS);
		}
		//cin>>opc;
	}

	bool operator>(Usuario* rhs) {
		return correo > rhs->correo;
	}
	bool operator<(Usuario* rhs) {
		return correo < rhs->correo;
	}

	virtual string guardar() = 0;
};

class Reserva {
private:
	string fecha;
	Hotel* hotel;
	string titular, correo, estado, moneda;
	int huespedes, habitacion;
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
	int get_huespedes() { return huespedes; }
	int get_habitacion() { return habitacion; }
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
	void set_huespedes(int huespedes) { this->huespedes = huespedes; }
	void set_habitacion(int habitaciones) { this->habitacion = habitacion; }
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
		this->huespedes = h->get_huespedes();
		this->habitacion = rand() % h->get_huespedes() + 1;;
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
	string guardar() {
		return "\n" + fecha + "," + hotel->get_ID() + "," + titular + "," + correo + "," + estado + "," + moneda + ","
			+ to_string(huespedes) + "," + to_string(habitacion) + "," + to_string(wifi) +
			"," + to_string(piscina) + "," + to_string(spa) + "," + to_string(parking) + "," + to_string(mascotas) +
			"," + to_string(desayuno) + "," + to_string(monto);
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
		cout << "\nEstado: " << estado;
		cout << endl;
	}

	bool operator>(Reserva rhs) {
		int dia1, mes1, ano1;
		int dia2, mes2, ano2;
		ano1 = stoi(fecha.substr(6, 4));
		ano2 = stoi(rhs.fecha.substr(6, 4));
		if (ano1 > ano2) return true;
		else if (ano1 < ano2) return false;
		mes1 = stoi(fecha.substr(3, 2));
		mes2 = stoi(rhs.fecha.substr(3, 2));
		if (mes1 > mes2) return true;
		else if (mes1 < mes2) return false;
		dia1 = stoi(fecha.substr(0, 2));
		dia2 = stoi(rhs.fecha.substr(0, 2));
		if (dia1 > dia2) return true;
		else if (dia1 < dia2) return false;
		return false;
	}
	bool operator<(Reserva rhs) {
		int dia1, mes1, ano1;
		int dia2, mes2, ano2;
		string s = rhs.fecha;
		ano1 = stoi(fecha.substr(6, 4));
		ano2 = stoi(rhs.fecha.substr(6, 4));
		if (ano1 > ano2) return false;
		else if (ano1 < ano2) return true;
		mes1 = stoi(fecha.substr(3, 2));
		mes2 = stoi(rhs.fecha.substr(3, 2));
		if (mes1 > mes2) return false;
		else if (mes1 < mes2) return true;
		dia1 = stoi(fecha.substr(0, 2));
		dia2 = stoi(rhs.fecha.substr(0, 2));
		if (dia1 > dia2) return false;
		else if (dia1 < dia2) return true;
		return false;
	}
};

class Reservas {
private:
	vector<Reserva*>reservas;
public:
	Reservas(Catalogo* cat) {
		reservas.setComp([](Reserva* a, Reserva* b) {return *a < *b; });
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
			if (fecha == "") continue;
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

	void deord() {
		shuffle(reservas);
	}

	void sort() {
		reservas.sort();
	}

	void agregarReserva(Reserva* Reserva) {
		reservas.push_back(Reserva);
		agregar(Reserva->get_titular());
	}
	void eliminarPos(int pos) {
		reservas.erase(pos);
	}

	int get_size() { return reservas.size(); }
	Reserva* get_pos(int i) { return reservas[i]; }


	Reserva* modificar(int pos) {
		for (int i = 0; i < reservas.size(); i++)
		{
			return reservas[pos];
		}
	}
	int buscar(Reserva* elem) {
		for (int i = 0; i < reservas.size(); i++)if (reservas[i] == elem)return i;
	}
	friend class DueñoHotelero;
	void visualizarReservas(string correo) {
		for (int i = 0; i < reservas.size(); i++) {
			if (reservas[i]->get_correo() == correo)
				reservas[i]->toString();
		}
		GoBack();
	}

	UPC::list<Reserva*> BuscarReservaTitular(string nombre) {
		UPC::list<Reserva*>l;

		for (Reserva** h = reservas.begin(); h != reservas.end(); h++) {
			if ((*h)->get_titular() == nombre)l.push_back(*h);
		}
		return l;
	}

	UPC::queue<Reserva*> BuscarWaitingList(string hotel) {
		UPC::queue<Reserva*> q;
		for (auto& c : hotel) {
			c = toupper(c);
		}
		for (int i = 0; i < reservas.size(); i++) {
			if (reservas[i]->get_idHotel() == hotel) {
				q.push(reservas[i]);
			}
		}
		return q;
	}

	void delete_record(int o)
	{ // falta hacer esto mas corto
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

	void guardar() {
		fstream fout;
		fout.open(ARCHIVO_RESERVAS);
		for (int i = 0; i < reservas.size(); i++) {
			fout << reservas[i]->guardar();
		}
		fout.close();
	}

	void generardatos(int x, Catalogo* c, Clientela* cl);
};

class Administrador : public Usuario {
private:
	string credencial;
	bool permisoCatalogo;
public:
	Administrador() {
		nombre = "";
		correo = "";
		contrasena = "";
		credencial = "";
		permisoCatalogo = false;
	}
	Administrador(string nombre, string correo, string contrasena, string credencial, bool permisoCatalogo) {
		this->nombre = nombre;
		this->correo = correo;
		this->contrasena = contrasena;
		this->credencial = credencial;
		this->permisoCatalogo = permisoCatalogo;
	}

	string get_credencial() { return credencial; }
	bool actualizarCatalogo() { return permisoCatalogo; }

	string guardar() {
		return "\n" + nombre + "," + correo + "," + contrasena + "," + credencial + "," + to_string(permisoCatalogo);
	}

	bool operator<(const Administrador& rhs) {
		return stoi(credencial) < stoi(rhs.credencial);
	}
};

//#define ARCHIVO_ADMINS "admins.csv"
class Administradores {
private:
	vector<Administrador*>admins;
public:
	Administradores() {
		admins.setComp([](Administrador* a, Administrador* b) {return *a < *b; });
		ifstream archivo(ARCHIVO_ADMINS);
		string linea;
		char delimitador = ',';
		while (getline(archivo, linea))
		{
			stringstream stream(linea); // Convertir la cadena a un stream
			string nombre, correo, contrasena, credencial, permisoCatalogo;
			// Extraer todos los valores de esa fila con getline
			getline(stream, nombre, delimitador);
			if (nombre == "") continue;
			getline(stream, correo, delimitador);
			getline(stream, contrasena, delimitador);
			getline(stream, credencial, delimitador);
			getline(stream, permisoCatalogo, delimitador);

			Administrador* admin = new Administrador(nombre, correo, contrasena, credencial, (bool)(stoi(permisoCatalogo)));
			admins.push_back(admin);
		}
	}

	void deord() {
		shuffle(admins);
	}

	void sort() {
		admins.sort();
	}

	function<void(string)> agregar{
		[](string correo) { if (correo != "")cout << "\nRegistro de admin exitoso"; }
	};

	void agregarAdmin(Administrador* admin) {
		admins.push_back(admin);
		agregar(admin->getcorreo());
	}
	void eliminarPos(int pos) {
		admins.erase(pos);
	}

	int get_size() { return admins.size(); }
	Administrador* get_pos(int i) { return admins[i]; }


	Administrador* BuscarAdmin(string credencial) {
		for (auto a : admins) {
			if (a->get_credencial() == credencial) return a;
		}
		return NULL;
	}

	void guardar() {
		fstream fout;
		fout.open(ARCHIVO_ADMINS);
		for (int i = 0; i < admins.size(); i++) {
			fout << admins[i]->guardar();
		}
		fout.close();
	}

	void generardatos(int x) {
		for (int i = 0; i < x; i++) {
			string temp;
			do {
				temp = generarcredencial();
			} while (BuscarAdmin(temp) != NULL);
			agregarAdmin(new Administrador(generarnombres(), generarcorreo(), generarcontraseña(), generarcredencial(), generarbool()));
		}
	}
};

class DueñoHotelero : public Usuario {
public:
	int ganancias;
	UPC::queue<Reserva*>waitingList;
	string hotel;
public:
	DueñoHotelero(string nombre, string correo, string contrasena, int ganancias, string hotel, Reservas* r) {
		waitingList = r->BuscarWaitingList(hotel);
		this->nombre = nombre;
		this->correo = correo;
		this->contrasena = contrasena;
		this->ganancias = ganancias;
		this->hotel = hotel;
	}
	string get_hotel() { return hotel; }
	int get_ganancias() { return ganancias; }
	void set_ganancias(int ganancias) { this->ganancias = ganancias; }
	void sumarGanancias(int monto) { this->ganancias += monto; }
	void restarGanancias(int monto) { this->ganancias -= monto; }
	void aceptarReserva(DueñoHotelero* d) {
		if (d->waitingList.empty()) return;
		d->waitingList.front()->set_estado("Aceptada");
		d->waitingList.pop();
	}
	void rechazarReserva(DueñoHotelero* d) {
		d->waitingList.front()->set_estado("Rechazada");
		d->restarGanancias(waitingList.front()->get_monto());
		d->waitingList.pop();
	}

	void visualizarWaitingList() {
		UPC::queue<Reserva*>q = waitingList;
		while (!q.empty()) {
			q.front()->toString();
			cout << endl;
			q.pop();
		}
		GoBack();
	}

	bool actualizarServicios() { return true; }

	string guardar() {
		return "\n" + nombre + "," + correo + "," + contrasena + "," + to_string(ganancias) + "," + hotel;
	}

	bool operator<(const DueñoHotelero& rhs) {
		return hotel < rhs.hotel;
	}
};

//#define ARCHIVO_DUEÑOS "duenhos.csv"
class Dueños {
private:
	vector<DueñoHotelero*>dueños;
public:
	Dueños(Reservas* r) {
		dueños.setComp([](DueñoHotelero* a, DueñoHotelero* b) {return *a < *b; });
		ifstream archivo(ARCHIVO_DUEÑOS);
		string linea;
		char delimitador = ',';
		while (getline(archivo, linea))
		{
			stringstream stream(linea); // Convertir la cadena a un stream
			string nombre, correo, contrasena, ganancias, hotel;
			// Extraer todos los valores de esa fila con getline
			getline(stream, nombre, delimitador);
			if (nombre == "") continue;
			getline(stream, correo, delimitador);
			getline(stream, contrasena, delimitador);
			getline(stream, ganancias, delimitador);
			getline(stream, hotel, delimitador);

			DueñoHotelero* dueño = new DueñoHotelero(nombre, correo, contrasena, stoi(ganancias), hotel, r);
			dueños.push_back(dueño);
		}
	}

	void deord() {
		shuffle(dueños);
	}

	void sort() {
		dueños.sort();
	}

	function<void(string)> agregar{
		[](string correo) { if (correo != "")cout << "\nRegistro de dueño exitoso"; }
	};

	void agregarDueño(DueñoHotelero* duenho) {
		dueños.push_back(duenho);

		agregar(duenho->getcorreo());
	}
	void eliminarPos(int pos) {
		dueños.erase(pos);
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
		DueñoHotelero* x = BuscarDueño(hotel);
		if (x != NULL) x->sumarGanancias(monto);
	}
	void quitar(string hotel, float monto) {
		DueñoHotelero* d = BuscarDueño(hotel);
		if (d != NULL) d->restarGanancias(monto);
	}

	void guardar() {
		fstream fout;
		fout.open(ARCHIVO_DUEÑOS);
		for (int i = 0; i < dueños.size(); i++) {
			fout << dueños[i]->guardar();
		}
		fout.close();
	}

	void generardatos(Catalogo* cat, Reservas* r) {
		list<Hotel*>* temp;
		temp = cat->getHoteles();
		for (auto it = temp->begin(); it != temp->end(); it++) {
			agregarDueño(new DueñoHotelero(generarnombres(), generarcorreo(), generarcontraseña(), generarganancias(), (*it)->get_ID(), r));
		}
		delete temp;
	}
};

class Cliente : public Usuario {
private:
	list<Reserva*> reservas;
	int cartera;
public:
	Cliente(string nombre, string correo, string contrasena, float cartera, Reservas* r) {
		this->nombre = nombre;
		this->correo = correo;
		this->contrasena = contrasena;
		this->cartera = 10000;
		reservas = r->BuscarReservaTitular(nombre);
		reservas.merge_sort();
	}
	~Cliente() {}
	int get_cartera() { return cartera; }
	void set_cartera(float cartera) { this->cartera = cartera; }
	void sumarCartera(float cartera) { this->cartera += cartera; }
	void restarCartera(float cartera) { this->cartera -= cartera; }
	void agregarReserva(Reserva* reserva) {
		reservas.push_front(reserva);
	}
	void reservarHotel(Catalogo &lista, Reservas &re, Cliente &c, Dueños &du) {
		Hotel* h = new Hotel();
		string id;
		cout << "Ingrese el dia el mes y el año para la reserva" << endl;
		int d, m, y;
		std::cin >> d >> m >> y;
		Date* fecha = new Date(d, m, y);
		do {
			cout << "Ingrese el ID del hotel a reservar:" << endl;
			std::cin >> id;
			std::transform(id.begin(), id.end(), id.begin(), std::toupper);
			h = lista.BuscarHotel(id);
			if (h != nullptr) cout << "Usted ha elegido: Hotel" << h->get_nombre() << endl;
		} while (h == nullptr);
		//cout<<h->get_ID();
		cout << "Usted tiene:" << c.get_cartera() << endl;

		cout << "El precio del hotel por persona es: " << h->get_precio() << endl;
		cout << "El precio VIP es de: " << h->get_precioVIP() << endl;
		cout << "Nota* el precio VIP incluye atencion y servicios preferenciales, ademas de la posibilidad de poder cancelar o postergar su reserva hasta 24 horas antes de que se consuma" << endl;
		cout << "¿Desea pagar por el precio normal (1) o el VIP (2)?" << endl;
		short categoria;
		cout << "Ingrese su eleccion: "; cin >> categoria;
		float costo;
		if (categoria == 1)costo = h->get_precio();
		else costo = h->get_precioVIP();
		cout << endl;
		float diff;
		diff = cartera - costo;
		if (diff >= 0)
		{
			Reserva* reserva = new Reserva(c.getnombre(), h, fecha->getDate(), 0, c.getcorreo());
			cout << "Reserva creada" << endl;
			_sleep(2000);
			c.agregarReserva(reserva);
			// no se esta guardando
			cout << "Lista de reserva de cliente actualizada" << endl;
			_sleep(2000);

			//agendacionExitosa(id);
			re.agregarReserva(reserva);
			cout << "\n\nReserva agregada al vector" << endl;
			c.restarCartera(costo);
			du.pagar(h->get_ID(), costo);
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
	void cancelarReserva(Reservas* r, Dueños* d) {
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
			n--;
			while (n--) it++;
			auto* p = *it;
			Catalogo* h = new Catalogo();
			h->BuscarHotel(p->get_idHotel())->agregarHabitacion(1);
			reembolso = p->get_monto();
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
			std::cin >> n; //validar imput?

			auto it = reservas.begin();
			n--;
			while (n--) it++;
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

	string guardar() {
		return "\n" + nombre + "," + correo + "," + contrasena + "," + to_string(cartera);
	}

	bool operator<(Cliente rhs) {
		return nombre < rhs.nombre;
	}
};

class Clientela {
private:
	vector<Cliente*>clientela;
public:
	Clientela(Reservas* r) {
		clientela.setComp([](Cliente* a, Cliente* b) {return *a < *b; });
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


			if (nombre != "") {
				Cliente* cliente = new Cliente(nombre, correo, contrasena, stoi(cartera), r);
				clientela.push_back(cliente);

			}
		}
	}

	function<void(string)> agregar{
		[](string id) { if (id != "")cout << "\nRegistro de cliente exitoso"; }
	};

	void deord() {
		shuffle(clientela);
	}

	void sort() {
		clientela.sort();
	}

	void agregarCliente(Cliente* cliente) {
		clientela.push_back(cliente);
		agregar(cliente->getnombre());
	}
	void eliminarPos(int pos) {
		clientela.erase(pos);
	}

	int get_size() { return clientela.size(); }
	Cliente* get_pos(int i) { return clientela[i]; }


	Cliente* BuscarCliente(string correo) { //esta funcion devuelve un hotel con la id provista, else devuelve NULL
		for (auto c : clientela) {
			if (c->getcorreo() == correo) return c;
		}
		return NULL;
	}

	void guardar() {
		fstream fout;
		fout.open(ARCHIVO_CLIENTES);
		for (int i = 0; i < clientela.size(); i++) {
			fout << clientela[i]->guardar();
		}
		fout.close();
	}

	void generardatos(int x, Reservas* r) {
		for (int i = 0; i < x; i++) {
			agregarCliente(new Cliente(generarnombres(), generarcorreo(), generarcontraseña(), generarcartera(), r));
			agregar("a");
		}
	}

	Cliente* getRan() {
		return clientela[rand() % clientela.size()];
	}

};

void Reservas::generardatos(int x, Catalogo* c, Clientela* cl) {
	for (int i = 0; i < x; i++) {
		Cliente* temp = cl->getRan();
		agregarReserva(new Reserva(temp->getContrasena(), c->randH(), generarfecha(), generarbool(), temp->getcorreo()));
	}
	cout << ".\n";
}

#pragma once
#include "Recursos.h"
#include <string>
#include <iostream>
#include "Fecha.h"
#include "UPC.h"

using namespace std;
using namespace UPC;

class Usuario
{
private:
	string nombre;
	string correo;
	string contrasena;
	string ID;
	//UPC::Vector<int> v;
	list<pair<Hotel*,Date*>>reservas;
public:
	Usuario(){}
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

	void ActualizarContra(vector<string>& lista, string contra) {
		for (int i = 1; i < lista.size(); i + 3)
		{
			if (lista[i] == contra)
			{
				lista[i + 1] = contra;
				this->contrasena = contra;
			}
		}
	}
	void ActualizarUsuario(vector<string>& lista, string nick) {
		for (int i = 1; i < lista.size(); i + 3)
		{
			if (lista[i] == nick)
			{
				lista[i - 1] = nick;
				this->nombre = nick;
			}
		}
	}

	function<void(string)> agendacionExitosa{
		[](string id) { if (id != "")cout << "\nAgendacion exitosa"; }
	};

	void reservarHotel(Catalogo* &lista) {
		cout << "Ingrese el dia el mes y el anho para la reserva" << endl;
		int d, m, y;
		std::cin >> d >> m >> y;
		Date*fecha=new Date(d, m, y);
		cout << "Ingrese el ID del hotel a reservar:" << endl;
		string id;
		std::cin >> id;
		lista->BuscarHotel(id);
		reservas.insert(make_pair(lista->BuscarHotel(id),fecha));
		agendacionExitosa(id);
		_sleep(2000);
	}

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
	void setID(string id) {
		this->ID = id;
	};
	string getnombre() {
		return nombre;
	};
	string getID() {
		return ID;
	}
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
class Cliente : public Usuario {
private:
	list<pair<Hotel*, Date*>> reservas = {};
public:
	Cliente(string nombre, string correo, string contrasena, int cartera) {}
	~Cliente() {}/*
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
			cout << h->get_nombre() << endl;
		} while (h == nullptr);
		//cout<<h->get_ID();
		cout << "El precio del hotel es: " << h->get_precio();

		if (getcartera() - h->get_precio() >= 0)
		{
			reservas.push_front(make_pair(h, fecha));
			agendacionExitosa(id);
		}
		else
		{
			cout << "La reserva no se puede ejecutar: " << endl;
			cout << "Saldo insuficiente" << endl;
		}
		_sleep(10000);
	}
	void cancelarreserva() {
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

class Admnistrador : public Usuario {
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



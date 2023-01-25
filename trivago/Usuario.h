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

	void reservarHotel(Catalogo* lista) {
		cout << "Ingrese el dia el mes y el anho para la reserva" << endl;
		int d, m, y;
		cin >> d >> m >> y;
		Date*fecha=new Date(d, m, y);
		cout << "Ingrese el ID del hotel a reservar:" << endl;
		string id;
		cin >> id;
		lista->BuscarHotel(ID);
		reservas.push_back(make_pair(lista->BuscarHotel(ID),fecha));
		agendacionExitosa(ID);
		_sleep(2000);
	}

	void ActualizarCorr(string corr) {
		vector<string> l;
		string linea;
		ifstream larchivo("Cuentas.txt");
		while (getline(larchivo, linea)) {
			l.push_back(linea);
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
	
	~Usuario();
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
};

/*
class Cliente : public Usuario {
private:
	vector<Hotel*>reservas;
public:
	Cliente(){}

	void reservarHotel() {}
	void cancelarreserva(){]
	void adelantarreserva
	void posterreserva
	void actualizarCorreo(){}
	void actualizarContrasenha(){}
};

class Admnistrador : public Usuario {
private:
	short credencial;
public:
	void actualizarCatalogo(){}
	void actualizarCorreo() {}
	void actualizarContrasenha() {}
};*/


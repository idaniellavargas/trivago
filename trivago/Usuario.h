#pragma once
#include "Recursos.h"
#include <string>
#include <iostream>

using namespace std;
using namespace UPC;

class Usuario
{
private:
	string nombre;
	string correo;
	string contrasena;
	string ID;
public:
	Usuario(){}
	Usuario(string nombre, string correo, string contrasena) {
		this->nombre = nombre;
		this->correo = correo;
		this->contrasena = contrasena;
	};
	~Usuario();
	void setnombre(string n) {
		this->nombre = n;
	};
	void setcorreo(string cor) {
		this->correo = cor;
	};
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
};

class Cliente : public Usuario {
private:
	vector<Hotel*>reservas;
public:
	Cliente(){}
	void reservarHotel() {}
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
};


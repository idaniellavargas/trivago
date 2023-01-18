#pragma once
#include <string>
#include <iostream>

using namespace std;


class Usuario
{
private:
	string nombre;
	string correo;
	string contrasena;
	string ID;

public:
	Usuario();
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
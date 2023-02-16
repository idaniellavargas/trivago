#pragma once
#include "Hotel.h"
#include "Recursos.h"
#include "Usuario.h"
using namespace System;

class Oferta {
private:
	string validez;
	string mensaje;
	string monto;
public:
	Oferta(string validez, string mensaje, string monto) {
		this->validez = validez;
		this->mensaje = mensaje;
		this->monto = monto;
	}
	~Oferta() {}

	void toString() {
		cout << "Validez: " << validez << "\n";
		cout << "Mensaje: " << mensaje << "\n";
		cout << "Monto: " << monto << "\n";
		cout << "===================" << endl;
	}
	function<void(string)> save{
		[](string mensaje) { if (mensaje != "")cout << "\nOferta guardada en el sistema"; }
	};
	string guardar() {
		save(mensaje);
		_sleep(2000);
		return validez + "," + mensaje + "," + monto + "\n";
	}
	float getmonto() { return stof(monto); }

};
#define DEALS "ofertas.csv"
class Ofertas {
private:
	UPC::list<Oferta*> ofertas;
public:
	Ofertas() {
		ifstream archivo(DEALS);
		string linea;
		char delimitador = ',';
		while (getline(archivo, linea))
		{
			if (linea == "") continue;
			stringstream stream(linea);
			string validez, mensaje, monto;
			getline(stream, validez, delimitador);
			getline(stream, mensaje, delimitador);
			getline(stream, monto, delimitador);
			Oferta* aux = new Oferta(validez, mensaje, monto);
			ofertas.push_front(aux);
		}
		shuffle(ofertas);
	}

	void toString() {
		for (auto i : ofertas) {
			i->toString();
		}
	}

	void addOferta(Oferta* o) {
		ofertas.push_front(o);
	}


	function<void(string)> agregar{
			[](string mensaje) { if (mensaje != "")cout << "\nRegistro de oferta exitoso"; }
	};


	void NuevaOferta(Ofertas* ofertas) {
		string mensaje;
		string monto;

		Console::Clear();
		while (1) {
			int d, m, y;
			cout << "Ingrese hasta cuándo dura la validez de la oferta en el formato día, mes, año:\n";
			cin >> d >> m >> y;
			Date* fecha = new Date(d, m, y);

			cout << "Ingrese el mensaje de la oferta:\n";
			getline(cin, mensaje);

			cout << "Ingrese el monto de la oferta:\n";
			cin >> monto;
			Oferta* oferta = new Oferta(fecha->getDate(), mensaje, monto);
			ofertas->addOferta(oferta);
			agregar(mensaje);
			_sleep(2000);
			fstream fout;
			fout.open(DEALS, ios::out | ios::app);
			fout << oferta->guardar();
			fout.close();
			break;
		}
		GoBack();
	}


	void mostrarOferta(Ofertas* ofertas) {
		Console::Clear();
		ofertas->toString();
		//GoBack();
	}

	float obtenerOferta() {
		int opc = -1, contador = 0;
		float of;
		do {
			cout << "Seleccione una oferta : " << endl;
			cin >> opc;
			if (opc < 0 || opc > ofertas.size())
			{
				opc = -1;
			}
		} while (opc == -1);
		for (auto i : ofertas)
		{
			if (opc == contador + 1) {
				of = i->getmonto();
				return of;
			}
			contador++;
		}
	}

	int MenuOfertas() {
		Console::Clear();
		int op;
		do {
			cout << " Menu de Opciones " << endl;
			cout << "1.- Mostrar ofertas" << endl;
			cout << "2.- Agregar oferta" << endl;
			cout << " Ingrese opcion: "; cin >> op;
		} while (op < 1 || op > 2);
		return op;
	}
	int MenuOfertasAll() {
		Console::Clear();
		int op;
		do {
			cout << " Menu de Opciones " << endl;
			cout << "1.- Mostrar ofertas" << endl;
			cout << "2.- Salir" << endl;
			cout << " Ingrese opcion: "; cin >> op;
		} while (op < 1 || op > 2);
		return op;
	}
};


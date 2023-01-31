#pragma once
#include "Hotel.h"
#include "Recursos.h"
#include "Usuario.h"
using namespace System;

class Comentario {
private:
	string ID;
	string Usuario;
	short Puntaje;
	string Coment;
public:
	Comentario(string ID, string Usuario, short Puntaje, string Coment) {
		this->ID = ID;
		this->Usuario = Usuario;
		this->Puntaje = Puntaje;
		this->Coment = Coment;
	}
	~Comentario() {}

	void toString() {
		cout << "ID: " << ID << "\n";
		cout << "Usuario: " << Usuario << "\n";
		cout << "Rating: " << Puntaje << "\n";
		if (Coment != "") cout << "Comentario:\n" << Coment << "\n";
		cout << "===================" << endl;
	}
	function<void(short)> save{
		[](short Puntaje) { if (Puntaje != 0)cout << "\Comentario guardado en el sistema"; }
	};
	string guardar() {
		save(Puntaje);
		_sleep(2000);
		return "\n" + ID + "," + Usuario + "," + to_string(Puntaje) + "," + Coment ;
	}

	bool operator<(Comentario* rhs) {
		return Usuario < rhs->Usuario;
	}

	bool operator>(Comentario* rhs) {
		return Usuario > rhs->Usuario;
	}
};

class arrComent {
private:
	vector<Comentario*> arrc;
public:
	arrComent() {
		ifstream archivo(ARCHIVO_COMENT);
		string linea;
		char delimitador = ',';
		while (getline(archivo, linea))
		{
			stringstream stream(linea); // Convertir la cadena a un stream
			string ID, usuario, coment, p;
			short puntaje;
			// Extraer todos los valores de esa fila con getline
			getline(stream, ID, delimitador);
			if (ID == "") continue;
			getline(stream, usuario, delimitador);
			getline(stream, p, delimitador);
			puntaje = stoi(p);
			getline(stream, coment, delimitador);
			Comentario* aux = new Comentario(ID, usuario, puntaje, coment);
			arrc.insert(aux);
		}
	}

	void toString() {
		for (auto i : arrc) {
			i->toString();
		}
	}

	void addComent(Comentario* nc) {
		arrc.insert(nc);
	}
};

function<void(short)> agregar{
		[](short puntaje) { if (puntaje != 0)cout << "\nRegistro de comentario exitoso"; }
};
void NuevoComentario(arrComent* arrc, Usuario* u) {
	Catalogo* arrh = new Catalogo();
	Hotel* h = NULL;
	string id;
	char c;
	short puntaje;
	string coment;

	Console::Clear();
	while (1) {

		cout << "Ingrese ID del Hotel que quiere comentar:\n";
		do {
			cin >> id;

			transform(id.begin(), id.end(), id.begin(), ::toupper);

			h = arrh->BuscarHotel(id);
			Console::Clear();
			if (h == NULL) cout << "ID no encontrada.\n Intente de nuevo:\n";
		} while (h == NULL);

		do {
			Console::Clear();
			h->toString();
			cout << "\n confirma su seleccion? (y/n):\n";
			cin >> c;
		} while (c != 'y' && c != 'n');

		Console::Clear();
		if (c == 'n') continue;
		else {
			do {
				cout << "Ingrese un rating del 1 al 5 (1 = muy malo, 5 = excelente): \n";
				cin >> puntaje;
				Console::Clear();
				if (puntaje < 0 || puntaje > 5) cout << "Puntaje fuera de rango.\n";
			} while (puntaje < 0 || puntaje > 5);

			do {
				Console::Clear();
				cout << "Desea dejar una resena? (y/n):\n";
				cin >> c;
			} while (c != 'y' && c != 'n');

			if (c == 'n') coment = "";
			else {
				cin.ignore();
				getline(cin, coment);
			}

			string nombre = u->getnombre();
			if (nombre == "") nombre = "anonimo";
			Comentario* ncoment = new Comentario(id, nombre, puntaje, coment);
			arrc->addComent(ncoment);
			cout << endl;
			agregar(puntaje);
			fstream fout;
			fout.open(ARCHIVO_COMENT, ios::out | ios::app);
			cout << endl;
			fout << ncoment->guardar();
			fout.close();
			break;
		}
		GoBack();
		break;
	}
}

void mostrarComentario(arrComent* arrc) {
	Console::Clear();
	arrc->toString();
	GoBack();
}

int MenuComent() {
	Console::Clear();
	int op;
	do {
		cout << "=======::Menu de Opciones::=======" << endl;
		cout << "1.- Agregar nuevo Comentario" << endl;
		cout << "2.- Mostrar Comentarios" << endl;
		cout << "Ingrese opcion: "; cin >> op;
	} while (op < 1 || op > 2);
	return op;
}


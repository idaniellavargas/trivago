#pragma once
#include "Hotel.h"
#include "Recursos.h"
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
	

	
	string guardar() {
		_sleep(2000);
		return "\n" + ID + "," + Usuario + "," + to_string(Puntaje) + "," + Coment ;
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
			if (linea == "") continue;
			stringstream stream(linea); // Convertir la cadena a un stream
			string ID, usuario, coment, p;
			short puntaje;
			// Extraer todos los valores de esa fila con getline
			getline(stream, ID, delimitador);
			getline(stream, usuario, delimitador);
			getline(stream, p, delimitador);
			puntaje = stoi(p);
			getline(stream, coment, delimitador);
			Comentario* aux = new Comentario(ID, usuario, puntaje, coment);
			arrc.push_back(aux);
		}
	}

	void toString() {
		for (auto i : arrc) {
			i->toString();
		}
	}

	void addComent(Comentario* nc) {
		arrc.push_back(nc);
	}
};


void NuevoComentario(arrComent* arrc) {
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
				getline(cin, coment);
				getline(cin, coment);
			}

			Comentario* ncoment = new Comentario(id, "anonimo", puntaje, coment);
			arrc->addComent(ncoment);

			fstream fout;
			fout.open(ARCHIVO_COMENT, ios::out | ios::app);
			fout << ncoment->guardar();
			fout.close();
			break;
		}
	}
}

void mostrarComentario(arrComent* arrc) {
	Console::Clear();
	arrc->toString();
	getch();
}

int MenuComent() {
	Console::Clear();
	int op;
	do {
		cout << " Menu de Opciones " << endl;
		cout << "1.- Agregar nuevo Comentario" << endl;
		cout << "2.- Mostrar Comentarios" << endl;
		cout << " Ingrese opcion: "; cin >> op;
	} while (op < 1 || op > 2);
	return op;
}

void FuncionalidadComent() {
	arrComent* objArreglo = new arrComent();

	while (true)
	{
		Console::Clear();
		int op;

		op = MenuComent();
		if (op == 1)
		{
			NuevoComentario(objArreglo);
		}
		else if (op == 2)
		{
			mostrarComentario(objArreglo);
		}
	}
}
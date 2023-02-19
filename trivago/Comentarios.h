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
	string guardar() {
		return "\n" + ID + "," + Usuario + "," + to_string(Puntaje) + "," + Coment;
	}

	bool operator<(const Comentario& rhs) {
		return Usuario < rhs.Usuario;
	}
};

class arrComent {
private:
	vector<Comentario*> arrc;
public:
	arrComent() {
		arrc.setComp([](Comentario* a, Comentario* b) {return *a < *b; });
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
			arrc.push_back(aux);
		}
	}

	void deord() {
		shuffle(arrc);
	}

	void sort() {
		arrc.sort();
	}

	void toString() {
		for (auto i : arrc) {
			i->toString();
		}
	}

	function<void()> agregar{
		[](){ cout << "\nComentario Creado"; }
	};

	void addComent(Comentario* nc) {
		arrc.push_back(nc);
		agregar();
	}

	void guardar() {
		fstream fout;
		fout.open(ARCHIVO_COMENT);
		for (int i = 0; i < arrc.size(); i++) {
			fout << arrc[i]->guardar();
		}
		fout.close();
	}

	void generardatos(int x, Catalogo* cat, Clientela* cl) {
		for (int i = 0; i < x; i++) {
			addComent(new Comentario(cat->randH()->get_ID(), cl->getRan()->getnombre(), generarpuntaje(), generarcomentario()));
		}
	}
};

function<void(short)> agregar{
		[](short puntaje) { if (puntaje != 0)cout << "\nRegistro de comentario exitoso"; }
};

void NuevoComentario(Catalogo* arrh, arrComent* arrc, Usuario* u) {
	Console::Clear;
	Hotel* h = NULL;
	string id;
	char c;
	short puntaje;
	string coment;

	do {
		cout << "Ingrese ID del Hotel que quiere comentar:\n";
		cin >> id;
		transform(id.begin(), id.end(), id.begin(), ::toupper);
		h = arrh->BuscarHotel(id);
		if (h == NULL) cout << "ID no encontrada.\n Intente de nuevo:\n";
	} while (h == NULL);

	while (1) {
		h->toString();
		cout << "\nConfirma su seleccion? (y/n):\n";
		cin >> c;
		if (c == 'n') continue;
		else if (c == 'y') {
			do {
				cout << "Ingrese un rating del 1 al 5 (1 = muy malo, 5 = excelente):\n";
				cin >> puntaje;
				if (puntaje < 1 || puntaje > 5) cout << "Puntaje fuera de rango.\n";
			} while (puntaje < 1 || puntaje > 5);

			cout << "Desea dejar una resena? (y/n):\n";
			cin >> c;
			if (c == 'y') {
				cin.ignore();
				getline(cin, coment);
			}
			else {
				coment = "";
			}

			string nombre = (u->getnombre() == "") ? "anónimo" : u->getnombre();
			Comentario* ncoment = new Comentario(id, nombre, puntaje, coment);
			arrc->addComent(ncoment);
			agregar(puntaje);
			break;
		}
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


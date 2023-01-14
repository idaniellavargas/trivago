#include "Recursos.h"

string hotelNombre[7] = { "Marriot","Bolivar","Shell", "Winston", "Paris","Casa Andina", "Trivago" };
string hotelUbicacion[7] = { "Isla de la Cite","San Luis","Barrio Latino", "Montmartre", "La Defensa","Campos Eliseos", "Plaza de la Concordia" };

class CHotel {
private:
	string nombre;
	int estrellas;
	string ubicacion;
	bool desayuno;
	int telefono;
	bool servicioA; //aeropuerto
public:
	CHotel();
	~CHotel() {};
	void registro() {};
	//metodos de acceso
	//getters
	void set_hotel() {};
	string get_nombre() { return nombre; }
	int get_estrellas() { return estrellas; }
	string get_ubicacion() { return ubicacion; }
	bool get_desayuno() { return desayuno; }
	int get_telefono() { return telefono; }
	bool get_servicioA() { return servicioA; }
	//setters
	void set_nombre(string n) { nombre = n; }
	void set_estrellas(int e) { estrellas = e; }
	void set_ubicacion(string u) { ubicacion = u; }
	void set_desayuno(bool d) { desayuno = d; }
	void set_telefono(int t) { telefono = t; }
	void set_servicioA(bool s) { servicioA = s; }
	//--

	void toString();
};

CHotel::CHotel() {
	nombre = hotelNombre[rand() % 7];
	estrellas = rand() % 6;
	ubicacion = hotelUbicacion[rand() % 7];
	desayuno = rand() % 2;
	telefono = rand() % 8000000 + 10000000;
	servicioA = rand() % 2;
}

void CHotel::toString() { //para imprimir string
	cout << "Nombre: " << nombre << "\t";
	cout << "Estrellas: " << estrellas << "\t";
	cout << "Ubicacion: " << ubicacion << "\t";
	cout << "Desayuno: ";
	if (desayuno)cout << "Si" << "\t";
	else cout << "No" << "\t";
	cout << "Telefono: " << telefono << "\t";
	cout << "Servicio: ";
	if (servicioA)cout << "Si" << "\t";
	else cout << "No" << "\t";
	cout << endl;
}

#include <map>
//clase controladora-->agrega,modifica,elimina, controlar aspectoz de registros y reportes
class ArrHotel {
private:
	map<string, CHotel>Hoteles; //voy a quedarme con esto y reconstruir los metodos con map en lugar de un array
	CHotel** arreglo;
	int N;
	int indice;
public:
	ArrHotel() {
		arreglo = nullptr;
		N = 0;
	}
	void agregarHotel(CHotel* obj) {
		CHotel** aux = new CHotel * [N + 1];
		for (int i = 0; i < N; i++) {
			aux[i] = arreglo[i];
		}
		aux[N] = obj;
		N++;
		if (arreglo != nullptr)

			delete[] arreglo;

		arreglo = aux;
	}
	void mostrar() {
		for (int i = 0; i < N; i++)
		{
			arreglo[i]->toString();
		}
	}
	void eliminarPos(int pos) {
		for (int i = 0; i < N; i++)
		{
			if (i == pos) {
				for (int j = pos; j < N - 1; j++)
				{
					arreglo[j] = arreglo[j + 1]; //sobreescribir
				}
			}
		}
		N--;
	}

	CHotel* modificar(int pos) {
		for (int i = 0; i < N; i++)
		{
			return arreglo[pos];
		}

	}
	//mostrar todos los campos Eliseos
	void reporte1() {
		for (int i = 0; i < N; i++)
		{
			if (arreglo[i]->get_ubicacion() == "Campos Eliseos")
				arreglo[i]->toString();
		}
	}
	//Hoteles que brindan desayuno
	void reporte2() {
		for (int i = 0; i < N; i++)
		{
			if (arreglo[i]->get_desayuno() == true)
				arreglo[i]->toString();
		}
	}
	//hoteles que brindan el servicio de aeropuerto
	void reporte3() {
		for (int i = 0; i < N; i++)
		{
			if (arreglo[i]->get_servicioA())
				arreglo[i]->toString();
		}
	}


};
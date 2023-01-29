#pragma once
#include "Fecha.h"
#include <string>
#include <string.h>
#include <istream>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <locale.h>
#include "UPC.h"
#include <iostream>
//#include <vector>
#include <conio.h>
#include <algorithm>
#define COLUMNAS 52
#define FILAS 40
#define ARCHIVO_HOTELES "hoteles.csv"
#define ARCHIVO_COMENT "coment.csv"


using namespace std;
using namespace System;
using namespace UPC;


int MenuHotel() {
	int op;
	do {
		cout << " Menu de Opciones " << endl;
		cout << "1.- Registrar Hotel" << endl; //nombres compuestas
		cout << "2.- Mostrar Registro de Hoteles " << endl; //monedas
		cout << "3.- Modificar un Registro de Hotel " << endl; //ubicacion
		cout << "4.- Eliminar Un Registro de Hotel " << endl; //
		cout << "5.- Reporte de ubicacion de en Francia" << endl;
		cout << "6.- Reporte de hoteles con desayuno" << endl;
		cout << "7.- Salir " << endl;
		cout << " Ingrese opcion: "; std::cin >> op;
	} while (op < 1 || op > 7);
	return op;
}


template<typename dataType>
dataType Randomizar(dataType lowerBound, dataType upperBound) {
	return lowerBound + rand() % (upperBound + 1 - lowerBound);
}

int busqueRecur(int indi, int ini, int indimax, int cons, vector<string> &lista, string palabra) {
	if (ini == 0) //En caso sea la primera llamada
	{
		if (lista[indi] == palabra) //Validar el dato
		{
			return indi; //Retornar el indice del dato
		}
		else
		{
			return busqueRecur(indi + cons, 1, indimax, cons, lista, palabra); //Volver a llamar a la funcion
		}
	}
	else //En caso ya se haya llamado mas de una vez
	{
		if (indi >= indimax) //En el caso que no se encuentre el dato, retornar -1
		{
			cout << "No se encontro su correo" << endl;
			return -1;
		}
		else if (lista[indi] == palabra) //Validar el dato del dato
		{
			string x = lista[indi];
			return indi; //Retornar el indice
		}
		
		else
		{
			string x = lista[indi];
			return busqueRecur(indi + cons, 1, indimax, cons, lista, palabra); //Volver a llamar a la funcion
		}
	}
}
void Mostrar_Logo() {
	int tecla = 0;
	system("color 7C");
	cout << R"(  
                                                   
                                                   
                                                                                                     
                                                    
                       .;.                          
                     .dKx.                          
            ..      ;0WWd.            ..            
          .l:.     ,0MMM0,             ;l'          
         :Ol       oWMMMW0d:.           lOc         
        lXO.      .xMMMMMMMNO:.         .kNl.       
       :XWd        lWMMMMMMMMWk'         oWXc       
      .OMWo        .OWMMMMMMMMWO'        lWMO'      
      :XMMx.        'kWMMMMMMMMWo       .xWMNc      
      lNMMX:         .c0WMMMMMMMx.      ;KMMWl      
      cNMMM0,          .cKWWMMMWd.     'OMMMNl      
      ,KMMMM0:           ,d0MMMK;     ;0WMMMK;      
      .dWMMMMNx,          .oWMKc    ,xNMMMMWd.      
       .kWMMMMMNOl,.     ..dXk, .'ckNMMMMMWO'       
        'kWMMMMMMMN0xoc::ok0Odox0NMMMMMMMWO'        
         .oXMMMMMMMMMMMMWMMMMMMMMMMMMMMMXo.         
           'dXWMMMMMMMMMMMMMMMMMMMMMMMXx,           
             .lOXWMMMMMMMMMMMMMMMMMNOl'             
                .:ok0XNWWWWWWNX0ko:'                
                    ..',,,,,,'..                                                 
)" << endl;	

	Console::SetCursorPosition(FILAS/2 - 2, 26);
	cout << "Exigete, innova";

	while (true) {
		if (_kbhit()) {
			tecla = getch();
			if (tecla == 13) {
				tecla = 0;
				break;
			}
		}
	}
	fflush(stdin);
	system("color 0F");
	system("cls");
}
string generarID(short caso, string nombre, int i = 0)
{
	string ID;
	char temp[3];
	short cont = 0;
	if (caso == 1) {
		ID = nombre.substr(0, 3);
		for (auto& c : ID) {
			c = toupper(c);
		}
		return ID;
	}
	else if (caso == 2) {
		if (nombre[i] == '\0') return 0; //se termina la cadena
		if (isupper(nombre[i])) {
			temp[cont] = nombre[i];
			cont++;
			if (cont == 3)ID = temp[0] + temp[1] + temp[2];
			return ID;
		}
		return generarID(2, nombre, i + 1);
	}
}
void Imprimir_Trivago() {
	cout << R"(
      _____  ____  _  _     ____  _____ ____ 
     /__ __\/  __\/ \/ \ |\/  _ \/  __//  _ \
       / \  |  \/|| || | //| / \|| |  _| / \|
       | |  |    /| || \// | |-||| |_//| \_/|
       \_/  \_/\_\\_/\__/  \_/ \|\____\\____/)" << endl;
}

void Desplazarse(int x, int y, bool visible) {
	Console::SetCursorPosition(y, x);
	(visible) ? cout << ">" : cout << ' ';
}
void GoBack() {
	int tecla = 0;
	Console::SetCursorPosition(0, 0);
	do {
		if (kbhit()) tecla = getch();
	} while (tecla != 27); // Esc
}


// texto del inicio de Trivago
/*Te damos la bievenida
	Hablemos de las cookies. Tanto nosotros como las webs con las que
	colaboramos compartimos y recopilamos datos y usamos cookies y otros
	elementos tecnológicos con fines de funcionalidad, seguimiento, análisis y
	publicidad personalizada dentro y fuera de trivago. Si estás de acuerdo,
	pulsa "Aceptar todo".

	También puedes obtener más información sobre las cookies que usamos y
	ajustar tu configuración --aquí--.

	Aceptar todo


	----

	Trivago

	Destino:
	Rio de Janeiro
	Fechas: 21 ene - 22 ene
	Habitacones: 2 huésp., 1 hab
	Buscar

	Comparamos varias webs de reserva al mismo tiempo

	Booking.com Hoteles.com Expedia Vrbo ACCOR LIVE LIMITLESS
	Trip.com despegar Más de 100

	¿Buscas un hotel cerca de ti para esta noche?
	Ubicación actual:
	13 ene.- 15 ene. 2 huésp., 1 hab.
	Buscar hoteles cerca

	Relájate. Nosotros nos encargamos.

	Iniciar sesión o crear cuenta


	Alojamientos - Favoritos - Configuración
	*/

// MATRICES DEL MAIN
void Iniciar_Arreglos_Menu(int**& pMenu) {
	/* Inicializamos el arreglo llenándolo de ceros */
	pMenu = new int* [FILAS];

	for (int i = 0; i < FILAS; i++)pMenu[i] = new int[COLUMNAS];
}
void Iniciar_Arreglos_Creditos(int**& pCreditos) {
	pCreditos = new int* [FILAS];

	for (int i = 0; i < FILAS; i++)pCreditos[i] = new int[COLUMNAS];

	for (int i = 0; i < FILAS; i++) {
		for (int j = 0; j < COLUMNAS; j++) {
			pCreditos[i][j] = 0;
		}
	}

	// limitar bordes
	for (int i = 0; i < FILAS; i++) {
		for (int j = 0; j < COLUMNAS; j++) {
			if (i == 0 || i == FILAS - 1 || j == 0 || j == COLUMNAS - 1) pCreditos[i][j] = 1;
		}
	}

	// pinta las celdas de la matriz para escribir "Creditos"
	pCreditos[8][8] = 3; pCreditos[8][9] = 3;
	pCreditos[8][11] = 3; pCreditos[8][12] = 3;
	pCreditos[8][15] = 3; pCreditos[8][16] = 3;
	pCreditos[8][18] = 3; pCreditos[8][19] = 3;
	pCreditos[8][22] = 3; pCreditos[8][24] = 3;
	pCreditos[8][25] = 3; pCreditos[8][26] = 3;
	pCreditos[8][29] = 3; pCreditos[8][32] = 3;
	pCreditos[8][33] = 3; pCreditos[8][34] = 3;
	pCreditos[9][7] = 3; pCreditos[9][11] = 3;
	pCreditos[9][13] = 3; pCreditos[9][15] = 3;
	pCreditos[9][18] = 3; pCreditos[9][20] = 3;
	pCreditos[9][22] = 3; pCreditos[9][25] = 3;
	pCreditos[9][28] = 3; pCreditos[9][30] = 3;
	pCreditos[9][32] = 3;
	pCreditos[10][7] = 3; pCreditos[10][11] = 3;
	pCreditos[10][12] = 3; pCreditos[10][15] = 3;
	pCreditos[10][16] = 3; pCreditos[10][11] = 3;
	pCreditos[10][18] = 3; pCreditos[10][20] = 3;
	pCreditos[10][22] = 3; pCreditos[10][25] = 3;

	pCreditos[10][28] = 3; pCreditos[10][30] = 3;
	pCreditos[10][32] = 3; pCreditos[10][33] = 3;
	pCreditos[10][34] = 3; pCreditos[11][7] = 3;
	pCreditos[11][11] = 3; pCreditos[11][13] = 3;
	pCreditos[11][15] = 3; pCreditos[11][18] = 3;
	pCreditos[11][20] = 3; pCreditos[11][22] = 3;
	pCreditos[11][25] = 3; pCreditos[11][28] = 3;
	pCreditos[11][30] = 3; pCreditos[11][34] = 3;
	pCreditos[12][9] = 3; pCreditos[12][11] = 3;
	pCreditos[12][13] = 3; pCreditos[12][15] = 3;
	pCreditos[12][16] = 3; pCreditos[12][18] = 3;
	pCreditos[12][19] = 3; pCreditos[12][22] = 3;
	pCreditos[12][25] = 3; pCreditos[12][29] = 3;
	pCreditos[12][32] = 3; pCreditos[12][33] = 3;
	pCreditos[12][34] = 3;	pCreditos[12][8] = 3;

}


void escribir(vector<string>& l) {
	ofstream archivo;
	archivo.open("Cuentas.txt", ios::app);
	//Revisamos el vector para ingresar los datos en el .txt
	for (int i = 0; i < l.size(); i++)
	{
		if (i == 0)
		{
			archivo << l[i] << endl;
		}
		else
		{
			archivo << l[i] << endl;
		}
	}
	archivo.close(); //Cerramos el archivo
}

void crearArch() {
	ofstream archivo;
	archivo.open("Cuentas.txt", ios::out);
	archivo.close();
}

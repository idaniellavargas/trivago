#pragma once
#include <iostream>
#include <conio.h>
#include "Fecha.h"
#define FILAS 40
#define COLUMNAS 52

using namespace std;
using namespace System;

template<typename dataType>
dataType Randomizar(dataType lowerBound, dataType upperBound) {
	return lowerBound + rand() % (upperBound + 1 - lowerBound);
}

void Mostrar_Logo(int tecla) {
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

// usando generador de textos gigantes ASCII: https://www.messletters.com/en/big-text/
void Imprimir_Trivago() {
	cout << R"(
      _____  ____  _  _     ____  _____ ____ 
     /__ __\/  __\/ \/ \ |\/  _ \/  __//  _ \
       / \  |  \/|| || | //| / \|| |  _| / \|
       | |  |    /| || \// | |-||| |_//| \_/|
       \_/  \_/\_\\_/\__/  \_/ \|\____\\____/)" << endl;
}


// muestra el cursor en el menú
void Desplazarse(int x, int y, bool visible) {
	Console::SetCursorPosition(y, x);
	(visible) ? cout << ">" : cout << ' ';
}

// regresa
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
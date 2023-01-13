#include "Recursos.h"

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
			if (i == 0 || i == FILAS-1 || j == 0 || j == COLUMNAS-1) pCreditos[i][j] = 1;
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
void Mostrar_favoritos() {
	Console::Clear();
	cout << "Mis favoritos";

	// Tecla
	int tecla = 0;
	Console::SetCursorPosition(0, 0);
	do {
		if (kbhit()) tecla = getch();
	} while (tecla != 27);
}
void Mostrar_Creditos() {
	/* Inicializamos matriz */
	int** pCreditos;
	Iniciar_Arreglos_Creditos(pCreditos);

	/* Limpieza de la consola */
	Console::Clear();

	for (int i = 0; i < FILAS; i++) {
		for (int j = 0; j < COLUMNAS; j++) {
			if (pCreditos[i][j] == 1) {
				Console::ForegroundColor = ConsoleColor::Yellow;
				cout << (char)219;
			}
			else if (pCreditos[i][j] == 3) {
				Console::ForegroundColor = ConsoleColor::White;
				cout << (char)219;
			}
			
			else if (i == 16) {
				if (j == 14) cout << "DESARROLLADO POR:        ";
				else if (j < 27) cout << ' ';
			}
			else if (i == 19) {
				if (j == 14) cout << "x Gustavo De Vivero      ";
				else if (j < 27) cout << ' ';
			}
			else if (i == 21) {
				if (j == 14) cout << "x Marcelo Poggi          ";
				else if (j < 27) cout << ' ';
			}
			else if (i == 23) {
				if (j == 14) cout << "x Daniella  Vargas       ";
				else if (j < 27) cout << ' ';
			}
		
			else if (i == 28) {
				if (j == 8) cout << "PRESIONE 'ESC' PARA REGRESAR AL MENU ";
				else if (j < 15) cout << ' ';
			}
		
			else {
				cout << ' ';
			}
		}

		cout << endl;
	}

	// Tecla
	GoBack();
}
void Iniciar_Arreglos_Menu(int**& pMenu) {
	/* Inicializamos el arreglo llenándolo de ceros */
	pMenu = new int* [FILAS];

	for (int i = 0; i < FILAS; i++)pMenu[i] = new int[COLUMNAS];
}
void Mostrar_Menu() {
	/* Inicializamos matriz */
	int** pMenu;
	Iniciar_Arreglos_Menu(pMenu);

	/* Limpieza de la consola */
	Console::Clear();

	/* Cargamos datos de Menú */
	for (int i = 0; i < FILAS; i++) {
		for (int j = 0; j < COLUMNAS; j++) {
			Console::ForegroundColor = ConsoleColor::Yellow;
		
			if (i == 8) {
				if(j==COLUMNAS/2)Imprimir_Trivago();
			}

			else if (i == 14) {
				if (j == COLUMNAS / 2 - 15) cout << "INICIAR SESION O CREAR CUENTA";
				else if (j < 30) cout << ' ';
			}
			else if (i == 16) {
				if (j == COLUMNAS / 2 - 8) cout << "MIS FAVORITOS";
				else if (j < 30) cout << ' ';
			}
			else if (i == 18) {
				if (j == COLUMNAS / 2 - 6) cout << "CREDITOS";
				else if (j < 30) cout << ' ';
			}
			else if (i == 20) {
				if (j == COLUMNAS / 2 - 5) cout << "SALIR";
				else if (j < 30) cout << ' ';
			}
			else {
				cout << ' ';
			}
		}

		cout << endl;
	}

	/* Teclas */
	int tecla, x = 20, y = 8;
	Desplazarse(x, y, true);
	while (true) {
		if (kbhit()) {
			Desplazarse(x, y, false);

			tecla = getch();
			switch (tecla) {
			case 13: // Enter
				if (x == 22) Mostrar_favoritos();
				if (x == 24) Mostrar_Creditos();
				if (x == 26) exit(0);

				Mostrar_Menu();
				break;
			case 72: // Arriba
				if (x > 20) x = x - 2;
				break;
			case 80: // Abajo
				if (x < 26) x = x + 2;
				break;
			}
			Desplazarse(x, y, true);
		}
	}
}

int main()
{
	Console::SetWindowSize(COLUMNAS, FILAS);
	Console::CursorVisible = false;
	int tecla = 0;
	Mostrar_Logo(tecla);
	Mostrar_Menu();
	system("pause");
	return 0;
}
#include "Recursos.h"
#include "Comentarios.h"
#include "Usuario.h"

void Mostrar_Menu(Usuario*cuenta);
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
		cout << " Ingrese opcion: "; cin >> op;
	} while (op < 1 || op > 7);
	return op;
}
void crearArch() {
	ofstream archivo;
	archivo.open("Cuentas.txt", ios::out);
	archivo.close();
}

void escribir(vector<string> l) {
	ofstream archivo;
	archivo.open("Cuentas.txt", ios::app);

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
	archivo.close();
}
void registrarse(string& n, string& corr, string& cont) {
	cout << "Registrarse:" << endl;
	cout << "Nombre: ";
	cin >> n;
	cout << "Correo: ";
	cin >> corr;
	cout << "Contrasena: ";
	cin >> cont;
}

void FuncionalidadUsuario(Usuario*cuenta) {
	int cont;
	char opc;
	string nom, opc2, cor, con;
	vector<string> lista;

	ifstream Parchivo("Cuentas.txt");
	if (Parchivo.fail())
	{
		crearArch();
	}
	Parchivo.close();

	do
	{
		//Pedimos una de las 2 opciones.
		cout << "Registrarse (R) o Iniciar secion (I)?" << endl;
		cin >> opc;
		opc = toupper(opc);
		Console::Clear();
		if (cuenta->getnombre() != "")
		{
			cout << "Ya su cuenta ya esta iniciada" << endl;
			opc = 'o';
		}
	} while (opc != 'R' && opc != 'I');

	if (opc == 'R')
	{
		cout << "---------Registrarse---------" << endl;
		cout << "Nombre: ";
		cin >> nom;
		cout << "Correo: ";
		cin >> cor;
		cout << "Contraseña: ";
		cin >> con;
		cuenta = new Usuario(nom, cor, con);
		cout << cuenta->getnombre();
		lista.push_back(nom);
		lista.push_back(cor);
		lista.push_back(con);
		escribir(lista);
	}
	else if (opc == 'I')
	{
		int contador = 0;
		bool val1, val2;
		string linea;
		vector<string> lineas;
		ifstream larchivo("Cuentas.txt");

		//obtenemos los datos del archivo en un contenedor
		while (getline(larchivo, linea)) {
			lineas.push_back(linea);
		}

		larchivo.close(); //cerramos el archivo

		do
		{
			cout << "Correo: ";
			cin >> cor;
			for (int i = 1; i < lineas.size(); i += 3)
			{
				val1 = cor == lineas[i];
				if (val1 == true)
				{
					cont = i;
					break;
				}
			}
			if (val1 != true)
			{
				cout << "correo incorrecto" << endl;
			}
		} while (val1 != true);


		do
		{
			cout << "Contraseña: ";
			cin >> con;
			cout << lineas[cont + 1] << endl;
			val2 = con == lineas[cont + 1];
			if (val2 == true)
			{
				cout << "contraseña correcta";
				cuenta = new Usuario(lineas[cont - 1], lineas[cont], lineas[cont + 1]);
				break;
			}
			else
			{
				cout << "contraseña incorrecta" << endl;
			}
		} while (val2 != true);
	}
}

void FuncionalidadHotel(Usuario*cuenta) {
	Catalogo* objArreglo = new Catalogo();
	Hotel* objHotel  = NULL;
	string nombre, ID, ubicacion, moneda;
	string huespedes, habitaciones;
	string telefono;
	bool wifi, piscina, spa, parking, mascotas, desayuno;

	while (true)
	{
		Console::Clear();
		int op;

		op = MenuHotel();
		if (op == 1)
		{
			objHotel = new Hotel();  //instnaciando, lamando a propiedades del objeto
			std::cout << "Ingresar detalles del hotel en el siguiente formato:\n"
				<< "Nombre - Ubicacion - Moneda\n - Cantidad de huespedes - Habitaciones - Telefono\n"
				<< "Si se cuenta con el servicio ingrese un 1, caso contrario, ingrese 0:\n" <<
				"WiFi - Piscina - Spa\n - Parking - Mascotas - Desayuno\n";

			// leer entrada

			

			cin >> nombre >> ubicacion >> moneda >> huespedes >> habitaciones >> telefono
				>> wifi >> piscina >> spa >> parking >> mascotas >> desayuno; //esto necesta getline e vez de cin

			objHotel->set_nombre(nombre); //no deberia todo esto ser echo en un costructor?
			objHotel->set_ubicacion(ubicacion);
			objHotel->set_moneda(moneda);
			objHotel->set_huespedes(huespedes);
			objHotel->set_habitaciones(habitaciones);
			objHotel->set_telefono(telefono);
			objHotel->set_wifi(wifi);
			objHotel->set_piscina(piscina);
			objHotel->set_spa(spa);
			objHotel->set_parking(parking);
			objHotel->set_mascotas(mascotas);
			objHotel->set_desayuno(desayuno);
			objHotel->set_ID(generarID(1, nombre, 0));
			objArreglo->agregarHotel(objHotel);
			fstream fout;
			fout.open(ARCHIVO_HOTELES, ios::out | ios::app);
			//insertar datos en el archivo en formato csv
			
				fout << objArreglo->get_pos(objArreglo->get_size()-1)->get_nombre() << ", " <<
					objArreglo->get_pos(objArreglo->get_size() - 1)->get_ID() << ", " <<
					objArreglo->get_pos(objArreglo->get_size() - 1)->get_ubicacion() << ", "<<
					objArreglo->get_pos(objArreglo->get_size() - 1)->get_moneda() << ", " <<
					objArreglo->get_pos(objArreglo->get_size() - 1)->get_huespedes() << ", " <<
					objArreglo->get_pos(objArreglo->get_size() - 1)->get_habitaciones() << ", " <<
					objArreglo->get_pos(objArreglo->get_size() - 1)->get_telefono() << ", " <<
					objArreglo->get_pos(objArreglo->get_size() - 1)->get_wifi() << ", " <<
					objArreglo->get_pos(objArreglo->get_size() - 1)->get_piscina() << ", " <<
					objArreglo->get_pos(objArreglo->get_size() - 1)->get_spa() << ", " <<
					objArreglo->get_pos(objArreglo->get_size() - 1)->get_parking() << ", " <<
					objArreglo->get_pos(objArreglo->get_size() - 1)->get_mascotas() << ", " <<
					objArreglo->get_pos(objArreglo->get_size() - 1)->get_desayuno() << "\n";
			fout.close();
			Console::Clear();
			MenuHotel();
		}
		if (op == 2)
		{
			objArreglo->mostrar();
		}

		if (op == 3)
		{
			int pos;
			int opcionM;
			cout << "Ingrese la poscion  que desee Modificar "; cin >> pos;
			Hotel* objHotel = objArreglo->modificar(pos);
			string nombre;
			string ubicacion;

			cout << "Que desea Modificar del Objeto: " << endl;
			cout << " 1 .- Nombre el Nombre " << endl;
			cout << " 2 .- Ubicacion " << endl;
			cout << " 3 .- Estrellas" << endl;
	
			cin >> opcionM;

			switch (opcionM)
			{
			case 1:

				cout << " Nombre  : (" << objHotel->get_nombre() << ") :"; cin >> nombre;
				objHotel->set_nombre(nombre);
				break;
			case 2:

				cout << " Ubicacion  : (" << objHotel->get_ubicacion() << ") :"; cin >> ubicacion;
				objHotel->set_ubicacion(ubicacion);
				break;
			
	
			default:
				cout << " Ha digitado un numero invalido " << endl;
				break;
			}


		}

		if (op == 4)
		{

			int pos;

			cout << "Ingrese la posicion que desee Eliminar: "; cin >> pos;
			//objArreglo->eliminarPos(pos);

		}

		if (op == 7)
		{
			//limpio memoria para no maltratar mi ram
			delete objArreglo;
			delete objHotel;
			cout<<"Nos vemos pronto! -- Presiona Esc para volver al menu principal";

		}
		GoBack();
		Mostrar_Menu(cuenta);
	}
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
void Mostrar_Menu(Usuario*cuenta) {
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
				if (j == COLUMNAS / 2 - 6) cout << "HOTELES";
				else if (j < 30) cout << ' ';
			}
			else if (i == 18) {
				if (j == COLUMNAS / 2 - 6) cout << "CREDITOS";
				else if (j < 30) cout << ' ';
			}
			else if (i == 20) {
				if (j == COLUMNAS / 2 - 6) cout << "COMENTS";
				else if (j < 30) cout << ' ';
			}
			else if (i == 22) {
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
				if (x == 20) {
					FuncionalidadUsuario(cuenta);
				}
				if (x == 22) {
					FuncionalidadHotel(cuenta);
				}
				if (x == 24) Mostrar_Creditos();
				if (x == 26) FuncionalidadComent();
				if (x == 28) exit(0);

				Mostrar_Menu(cuenta);
				break;
			case 72: // Arriba
				if (x > 20) x = x - 2;
				break;
			case 80: // Abajo
				if (x < 28) x = x + 2; //wtf
				break;
			}
			Desplazarse(x, y, true);
		}
	}
}

int main()
{
	Usuario* cuenta;
	cuenta = new Usuario("", "", "");
	Console::SetWindowSize(COLUMNAS, FILAS);
	Console::CursorVisible = false;
	int tecla = 0;
	Mostrar_Logo(tecla);
	Mostrar_Menu(cuenta);
	system("pause");
	return 0;
}
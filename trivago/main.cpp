#include "Recursos.h"
#include "Comentarios.h"
#include "Usuario.h"
using namespace std;
// puntero a funcion
typedef void (*fp)();
Usuario* cuenta = new Usuario("", "", "");
UPC::stack<fp>s;
auto funcion=&Mostrar_Logo;
// forward declaration
void Mostrar_Menu();

void FuncionalidadUsuario() {
	Console::Clear();
	char opc;
	string nom, opc2, cor, con;
	vector<string> lista;

	//Revisamos si existe un archivo para las cuentas
	ifstream Parchivo("Cuentas.txt");
	if (Parchivo.fail())
	{
		crearArch(); //Si no existe un archivo se crea
	}
	Parchivo.close(); //Cerramos la validacion de existencia del archivo

	//Pedimos que se registre o inicie sesion
	do
	{
		cout << "�Registrarse (R) o Iniciar sesi�n (I)?" << endl;
		cin >> opc;
		opc = toupper(opc);
		if (cuenta->getnombre() != "") //Revisamos que ya se haya registrado o iniciado sesion
		{
			cout << "Ya se encuentra autenticado en el sistema" << endl;
			_sleep(1000);
			opc = 'o';
			break;
		}
	} while (opc != 'R' && opc != 'I');

	if (opc == 'R')
	{
		//Registramos las variables del usuario
		cout << "---------Registrarse---------" << endl;
		cout << "Nombre: ";
		cin >> nom;
		cout << "Correo: ";
		cin >> cor;
		cout << "Contrase�a: ";
		cin >> con;
		cuenta = new Usuario(nom, cor, con); //Registramos al usuario
		//Ingresamos los datos a un vector
		lista.push_back(nom);
		lista.push_back(cor);
		lista.push_back(con);
		//Registramos los datos en el archivo
		escribir(lista);
	}
	else if (opc == 'I')
	{
		int indi = 0, indice;
		bool val2;
		string linea;
		vector<string> lineas;
		ifstream larchivo("Cuentas.txt");

		//obtenemos los datos del archivo en un contenedor
		while (getline(larchivo, linea)) {
			lineas.push_back(linea);
		}
		larchivo.close(); //cerramos el archivo

		//Verificamos si el correo es correcto
		do
		{
			cout << "Correo: ";
			cin >> cor; //Ingresamos el correo
			indi = lineas.size();
			indice = busqueRecur(1, 0, indi, 3, lineas, cor); //Usamos una funcion recursiva para hallar el correo
		} while (indice == -1);

		//Validamos la contrase�a
		do
		{
			cout << "Contrase�a: ";
			cin >> con; //Ingresamos la contrase�a
			val2 = con == lineas[indice + 1]; //Validamos la contrase�a registrada con la ingresada
			if (val2 == true)
			{
				cout << "Contrase�a correcta";
				_sleep(1000);
				cuenta->Actualizar(lineas[indice - 1], lineas[indice], lineas[indice + 1]); //Registramos al usuario
				_sleep(2000);
				break;
			}
			else
			{
				cout << "Contrase�a incorrecta" << endl;
				_sleep(1000);
			}
		} while (val2 != true);
	}
}
void FuncionalidadHotel() {
	Catalogo* objArreglo = new Catalogo();
	Hotel* objHotel  = NULL;
	string nombre, ID, ubicacion, moneda;
	short huespedes, habitaciones;
	long telefono;
	bool wifi, piscina, spa, parking, mascotas, desayuno;

	while (true)
	{
		Console::Clear();
		int op;

		op = MenuHotel();
		if (op == 1)
		{
			fflush(stdin);
			cin.ignore();
			cout << "Como se llama el hotel?\n";
			getline(cin, nombre);
			cout << "Donde se ubica?\n";
			getline(cin, ubicacion);
			cout << "Que tipo de cambio usa?\n";
			getline(cin, moneda);
			cout << "Ingresar detalles del hotel en el siguiente formato:\n"
				<< "Cantidad de huespedes - Habitaciones - Telefono\n";
				cin >> huespedes >> habitaciones >> telefono;
			cout << "Si se cuenta con el servicio ingrese un 1, caso contrario, ingrese 0:\n" <<
				"WiFi - Piscina - Spa\n - Parking - Mascotas - Desayuno\n";

			cin >> wifi >> piscina >> spa >> parking >> mascotas >> desayuno; 



			objHotel = new Hotel(nombre, generarID(1, nombre, 0), ubicacion, moneda, huespedes, habitaciones, telefono, wifi, piscina, spa, parking, mascotas, desayuno);
			/*objHotel->set_nombre(nombre); //no deberia todo esto ser echo en un costructor?
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
			*/
			objArreglo->agregarHotel(objHotel);
			_sleep(2000);
			//cout<<confirmar(objHotel->get_ID());
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
			_getch();
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
			cout << " 1 .- El Nombre " << endl;
			cout << " 2 .- Ubicacion " << endl;
	
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
			objArreglo->eliminarPos(pos);

		}

		if (op == 7)
		{
			delete objArreglo, objHotel;
			cout << "Nos vemos pronto!";
			_sleep(1000);
			break;
		}break;
	}
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

void FuncionalidadComent() {
	arrComent* objArreglo = new arrComent();

	while (true)
	{
		Console::Clear();
		int op;

		op = MenuComent();
		if (op == 1)
		{
			NuevoComentario(objArreglo, cuenta);
		}
		else if (op == 2)
		{
			mostrarComentario(objArreglo);
		}
		break;
	}
}

void Mostrar_Menu() {
	/* Inicializamos matriz */
	int** pMenu;
	Iniciar_Arreglos_Menu(pMenu);
	bool mostrarMenu = true;
	int tecla, x = 20, y = 8;

	while (1) {

		if (mostrarMenu) {
			mostrarMenu = false;

			/* Limpieza de la consola */
			Console::CursorVisible = false;
			Console::Clear();

			/* Cargamos datos de Men� */
			for (int i = 0; i < FILAS; i++) {
				for (int j = 0; j < COLUMNAS; j++) {
					Console::ForegroundColor = ConsoleColor::Yellow;

					if (i == 8) {
						if (j == COLUMNAS / 2)Imprimir_Trivago();
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
					else if (i == 24) {
						if (j == COLUMNAS / 2 - 10) cout << "ACTUALIZAR DATOS";
						else if (j < 30) cout << ' ';
					}
					else if (i == 26) {
						if (j == COLUMNAS / 2 - 10) cout << "RESERVAR ESTADIA";
						else if (j < 30) cout << ' ';
					}
					else {
						cout << ' ';
					}
				}

				cout << endl;
			}
		}

		/* Teclas */
		
		Desplazarse(x, y, true);

		if (kbhit()) {
			Desplazarse(x, y, false);
			tecla = getch();
			switch (tecla) {
			case 13: // Enter
				if (x == 20) funcion = &FuncionalidadUsuario;
				if (x == 22) funcion = &FuncionalidadHotel;
				if (x == 24) funcion = &Mostrar_Creditos;
				if (x == 26) funcion = &FuncionalidadComent;
				if (x == 28) return;
				if (x == 30) {
					Console::Clear();
					int n;
					string aux;
					cout << "Ingrese el numero de su seleccion: ";
					cout << "\n1.Contrasenha";
					cout << "\n2.Correo";
					cout << "\n3.Usuario";
					cout << endl;
					cin >> n;
					switch (n) {
					case 1:
						cout << endl;
						cin.ignore();
						cout << "Ingrese nuevo correo" << endl;
						cin >> aux;
						cuenta->ActualizarCorr(aux);
						cout << "Listo!";
					}
				}
				if (x == 32) {
					Console::Clear();
					Catalogo* objArreglo = new Catalogo();
					cuenta->reservarHotel(objArreglo);
				}
				s.push(funcion);
				(*funcion)();
				s.pop();
				funcion = s.top(); //menu
				(*funcion)();
				break;
			case 72: // Arriba
				if (x > 20) x = x - 2;
				break;
			case 80: // Abajo
				if (x < 32) x = x + 2;
				break;
			}
			Desplazarse(x, y, true);
		}
	}
}

int main()
{
	setlocale(LC_ALL, "spanish"); 
	SetConsoleCP(1252); 
	SetConsoleOutputCP(1252);
	Console::SetWindowSize(COLUMNAS, FILAS);
	Console::CursorVisible = false;
	s.push(funcion);
	(*funcion)();
	s.pop();
	funcion = &Mostrar_Menu;
	s.push(funcion);
	(*funcion)();
	system("pause");

	delete cuenta;
	return 0;
}
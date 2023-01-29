#include "Recursos.h"
#include "Comentarios.h"
#include "Usuario.h"
using namespace std;
// puntero a funcion
typedef void (*fp)();
Usuario* cuenta = NULL;
Cliente* cliente;
DueñoHotelero* dueño;
Administrador* admin;
bool sesionIniciada = false;
short tipo = 0;

UPC::stack<fp>s;
auto funcion=&Mostrar_Logo;
// forward declaration
void Mostrar_Menu();

void FuncionalidadUsuario() {
	Console::Clear();
	char opc;
	string nom, opc2, cor, con, hot;
	vector<string> lista;
	Clientela* arrCliente;
	Administradores* arrAdmin;
	Dueños* arrHotel;
	Usuario* temp = NULL;
	int id;

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
		cout << "¿Registrarse (R) o Iniciar sesión (I)?" << endl;
		std::cin >> opc;
		opc = toupper(opc);
		if (cuenta != NULL) //Revisamos que ya se haya registrado o iniciado sesion
		{
			cout << "Ya se encuentra autenticado en el sistema" << endl;
			_sleep(1000);
			opc = 'o';
			break;
		}
	} while (opc != 'R' && opc != 'I');

	if (opc == 'R')
	{
		do {
			cout << "¿Desea registrarse como cliente(1), dueño hotelero(2), o administrador(3)?" << endl;
			std::cin >> tipo;
		} while (tipo > 3 || tipo < 0);

		//Registramos las variables del usuario
		cout << "---------Registrarse---------" << endl;
		cout << "Nombre: ";
		std::cin >> nom;
		if (tipo == 2) {
			cout << "ID: ";
			cin >> id;
		}
		else if (tipo == 3) {
			cout << "Hotel: ";
			cin >> hot;
		}
		cout << "Correo: ";
		std::cin >> cor;
		cout << "Contraseña: ";
		std::cin >> con;
		if(cuenta != NULL) delete cuenta;
		if (tipo == 1) {
			cuenta = new Cliente(nom, cor, con, 0); //Registramos al usuario
			ofstream fout;
			fout.open(ARCHIVO_CLIENTES, ios::out | ios::app);
			fout << cuenta->guardar();
			fout.close();
		}
		else if (tipo == 2) {
			cuenta = new Administrador(nom, cor, con, id, true);
			ofstream fout;
			fout.open(ARCHIVO_ADMINS, ios::out | ios::app);
			fout << admin->guardar();
			fout.close();
		}
		else {
			cuenta = new DueñoHotelero(nom, cor, con, 0, hot);
			ofstream fout;
			fout.open(ARCHIVO_DUEÑOS, ios::out | ios::app);
			fout << cuenta->guardar();
			fout.close();
		}
		sesionIniciada = true;
		_sleep(1000);
	}
	else if (opc == 'I')
	{
		do {
			cout << "¿Desea iniciar sesión como cliente(1), dueño hotelero(2), o administrador(3)?" << endl;
			std::cin >> tipo;
		} while (tipo > 3 || tipo < 0);

		switch (tipo) {
		case 1:
			arrCliente = new Clientela();
			break;
		case 2:
			arrAdmin = new Administradores();
			break;
		case 3:
			arrHotel = new Dueños();
			break;
		}
		
		/*
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

		*/
		//Verificamos si el correo es correcto
		do
		{
			switch (tipo) {
			case 1:
				cout << "Correo: ";
				std::cin >> cor; //Ingresamos el correo
				temp = arrCliente->BuscarCliente(cor);
				break;
			case 2:
				cout << "ID: ";
				cin >> id;
				temp = arrAdmin->BuscarAdmin(id);
				break;
			case 3:
				cout << "Hotel: ";
				cin >> hot;
				temp = arrHotel->BuscarDueño(hot);
				break;
			default:
				break;
			}
		} while (temp == NULL);

		//Validamos la contraseña

		cout << "Contraseña: ";
		std::cin >> con; //Ingresamos la contraseña
		if (temp->getContrasena() == con)
		{
			sesionIniciada = true;
			cout << "Contraseña correcta";
			_sleep(1000);
			delete cuenta;
			cuenta = temp;
			cout << "\nInicio de sesion exitoso.";
			_sleep(2000);
		}
		else
		{
			cout << "Contraseña incorrecta" << endl;
			_sleep(1000);
		}
	}
}
void FuncionalidadHotel() {
	Catalogo* objArreglo = new Catalogo();
	Hotel* objHotel  = NULL;
	string nombre, ID, ubicacion, moneda;
	short huespedes, habitaciones;
	long telefono;
	bool wifi, piscina, spa, parking, mascotas, desayuno;
	float precio, precioVIP;

	while (true)
	{
		Console::Clear();
		int op;

		op = MenuHotel();
		if (op == 1)
		{
			if (tipo != 2 && tipo != 3) {
				cout << "ACCESO DENEGADO";
				_sleep(1000);
			}
			fflush(stdin);
			std::cin.ignore();
			cout << "Como se llama el hotel?\n";
			getline(std::cin, nombre);
			cout << "Donde se ubica?\n";
			getline(std::cin, ubicacion);
			cout << "Que tipo de cambio usa?\n";
			getline(std::cin, moneda);
			cout << "Ingresar detalles del hotel en el siguiente formato:\n"
				<< "Cantidad de huespedes - Habitaciones - Telefono\n";
			std::cin >> huespedes >> habitaciones >> telefono;
			cout << "Si se cuenta con el servicio ingrese un 1, caso contrario, ingrese 0:\n" <<
				"WiFi - Piscina - Spa\n - Parking - Mascotas - Desayuno - precio - precioVIP\n";

			std::cin >> wifi >> piscina >> spa >> parking >> mascotas >> desayuno >>precio>>precioVIP;



			objHotel = new Hotel(nombre, generarID(1, nombre, 0), ubicacion, moneda, huespedes, habitaciones, telefono, wifi, piscina, spa, parking, mascotas, desayuno, precio, precioVIP);
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
					objArreglo->get_pos(objArreglo->get_size() - 1)->get_desayuno() << "," <<
					objArreglo->get_pos(objArreglo->get_size() - 1)->get_precio() << ", " <<
					objArreglo->get_pos(objArreglo->get_size() - 1)->get_precioVIP() << "\n";


			fout.close();
			Console::Clear();
			MenuHotel();
		}
		if (op == 2)
		{
			objArreglo->mostrar();
			GoBack();
		}

		if (op == 3)
		{
			int pos;
			int opcionM;
			cout << "Ingrese la poscion  que desee Modificar "; std::cin >> pos;
			Hotel* objHotel = objArreglo->modificar(pos);
			string nombre;
			string ubicacion;

			cout << "Que desea Modificar del Objeto: " << endl;
			cout << " 1 .- El Nombre " << endl;
			cout << " 2 .- Ubicacion " << endl;
	
			std::cin >> opcionM;

			switch (opcionM)
			{
			case 1:

				cout << " Nombre  : (" << objHotel->get_nombre() << ") :"; std::cin >> nombre;
				objHotel->set_nombre(nombre);
				break;
			case 2:

				cout << " Ubicacion  : (" << objHotel->get_ubicacion() << ") :"; std::cin >> ubicacion;
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

			cout << "Ingrese la posicion que desee Eliminar: "; std::cin >> pos;
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

void FuncionalidadReservas() {
	Catalogo* c = new Catalogo();
	Reservas* objArreglo = new Reservas();
	
	while (true)
	{
		Console::Clear();
		int op;

		op = MenuReservas();
		if (op == 1)
		{
			cliente->reservarHotel(c, objArreglo);
		}
		else if (op == 2)
		{
			objArreglo->visualizarReservas(cliente->getcorreo());
		}
		else if (op == 3)
		{
			cliente->cancelarReserva(objArreglo);
		}
		else if(op==4){
			cliente->cambiarfecha(objArreglo);
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

			/* Cargamos datos de Menú */
			for (int i = 0; i < FILAS; i++) {
				for (int j = 0; j < COLUMNAS; j++) {
					Console::ForegroundColor = ConsoleColor::Yellow;

					if (sesionIniciada) {
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
					else {
						if (i == 8) {
							if (j == COLUMNAS / 2)Imprimir_Trivago();
						}

						else if (i == 14) {
							if (j == COLUMNAS / 2 - 15) cout << "INICIAR SESION O CREAR CUENTA";
							else if (j < 30) cout << ' ';
						}
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
				if (x == 28) exit(0);
				if (x == 30) {
					Console::Clear();
					int n;
					string aux;
					cout << "Ingrese el numero de su seleccion: ";
					cout << "\n1.Contrasenha";
					cout << "\n2.Correo";
					cout << "\n3.Usuario";
					cout << endl;
					std::cin >> n;
					switch (n) {
					case 1:
						cout << endl;
						std::cin.ignore();
						cout << "Ingrese nuevo correo" << endl;
						std::cin >> aux;
						//cuenta->ActualizarCorr(aux);
						cout << "Listo!";
					}
				}
				if (x == 32) funcion = &FuncionalidadReservas;
				s.push(funcion);
				(*funcion)();
				s.pop();
				funcion = s.top(); //menu
				(*funcion)();
				break;
			case 72: // Arriba
				if (x > 20 && sesionIniciada) x = x - 2;
				break;
			case 80: // Abajo
				if (x < 32 && sesionIniciada) x = x + 2;
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
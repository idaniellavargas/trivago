#include "Recursos.h"
#include "Comentarios.h"
#include "Usuario.h"
using namespace std;

typedef void (*fp)();
Usuario* cuenta = NULL;
Cliente* cliente;
DueñoHotelero* dueño;
Administrador* admin;
bool sesionIniciada = false;
short tipo = 0;
UPC::stack<fp>s;
auto funcion = &Mostrar_Logo;

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
		if (tipo == 3) {
			cout << "ID: ";
			cin >> id;
		}
		else if (tipo == 2) {
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
		else if (tipo == 3) {
			cuenta = new Administrador(nom, cor, con, id, true);
			ofstream fout;
			fout.open(ARCHIVO_ADMINS, ios::out | ios::app);
			fout << cuenta->guardar();
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
			cout << "¿Desea iniciar sesión como cliente(1), administrador(2), o dueño hotelero(3)?" << endl;
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
		do
		{
			switch (tipo) {
			case 1:
				cout << "Correo: ";
				std::cin >> cor; //Ingresamos el correo
				temp = arrCliente->BuscarCliente(cor);
				cliente = arrCliente->BuscarCliente(cor);
				break;
			case 2:
				cout << "ID: ";
				cin >> id;
				temp = arrAdmin->BuscarAdmin(id);
				admin = arrAdmin->BuscarAdmin(id);
				break;
			case 3:
				cout << "Hotel: ";
				cin >> hot;
				temp = arrHotel->BuscarDueño(hot);
				dueño= arrHotel->BuscarDueño(hot);
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
		short op, pos;
		op = MenuHotel();
		if (op == 1)
		{
			if (tipo != 2 && tipo != 3) {
				cout << "ACCESO DENEGADO";
				_sleep(1000);
				return;
			}
			fflush(stdin);
			cin.ignore();
			cout << "¿Cómo se llama el hotel?\n"; getline(cin, nombre);
			cout << "¿Dónde se ubica?\n"; getline(cin, ubicacion);
			cout << "¿Qué tipo de cambio usa?\n"; getline(cin, moneda);
			cout << "\nIngrese el límite de huéspedes por habitación: "; cin >> huespedes;
			cout << "\nIngrese la cantidad de habitaciones disponibles: "; cin >> habitaciones;
			cout << "\nIngrese un teléfono de contacto: "; cin >> telefono;
			cout << "\nSi se cuenta con el servicio ingrese un 1, caso contrario 0:";
			cout << "\nWiFi: "; cin >> wifi;
			cout << "\nPiscina: "; cin >> piscina;
			cout << "\nSpa: "; cin >> spa;
			cout << "\nParking: "; cin >> parking;
			cout << "\nMascotas: "; cin >> mascotas;
			cout << "\nDesayuno: "; cin >> desayuno;
			cout << "\nAhora, ingrese el precio regular de alojamiento: "; cin >> precio;
			cout << "\nFinalmente, digite el precio de habitaciones VIP: "; cin >> precioVIP;

			objHotel = new Hotel(nombre, generarID(1, nombre, 0), ubicacion, moneda, huespedes, habitaciones, telefono, wifi, piscina, spa, parking, mascotas, desayuno, precio, precioVIP);
			objArreglo->agregarHotel(objHotel);
			_sleep(2000);
			
			fstream fout;
			fout.open(ARCHIVO_HOTELES, ios::out | ios::app);
			
			fout << objArreglo->get_pos(objArreglo->get_size() - 1)->get_nombre() << ", " << objArreglo->get_pos(objArreglo->get_size() - 1)->get_ID() << ", " << objArreglo->get_pos(objArreglo->get_size() - 1)->get_ubicacion() << ", "<< objArreglo->get_pos(objArreglo->get_size() - 1)->get_moneda() << ", " << objArreglo->get_pos(objArreglo->get_size() - 1)->get_huespedes() << ", " << objArreglo->get_pos(objArreglo->get_size() - 1)->get_habitaciones() << ", " << objArreglo->get_pos(objArreglo->get_size() - 1)->get_telefono() << ", " << objArreglo->get_pos(objArreglo->get_size() - 1)->get_wifi() << ", " << objArreglo->get_pos(objArreglo->get_size() - 1)->get_piscina() << ", " << objArreglo->get_pos(objArreglo->get_size() - 1)->get_spa() << ", " << objArreglo->get_pos(objArreglo->get_size() - 1)->get_parking() << ", " << objArreglo->get_pos(objArreglo->get_size() - 1)->get_mascotas() << ", " << objArreglo->get_pos(objArreglo->get_size() - 1)->get_desayuno() << "," << objArreglo->get_pos(objArreglo->get_size() - 1)->get_precio() << ", " << objArreglo->get_pos(objArreglo->get_size() - 1)->get_precioVIP() << "\n";
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
			if (tipo != 2 && tipo != 3) {
				cout << "ACCESO DENEGADO";
				_sleep(1000);
				return;
			}
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
			if (tipo != 2 && tipo != 3) {
				cout << "ACCESO DENEGADO";
				_sleep(1000);
				return;
			}
			cout << "Ingrese la posicion que desee Eliminar: "; std::cin >> pos;
			objArreglo->eliminarPos(pos);
		}
		if (op == 5) //busqueda francia
		{
			if (tipo != 2 && tipo != 3) {
				cout << "ACCESO DENEGADO";
				_sleep(1000);
				return;
			}
			cout << "Ingrese la posicion que desee Eliminar: "; std::cin >> pos;
			objArreglo->eliminarPos(pos);
		}
		if (op == 6) //busqueda desayuno
		{
			cout << "Ingrese la posicion que desee Eliminar: "; cin >> pos;
			objArreglo->eliminarPos(pos);
		}
		if (op == 7) // visualizacion de ofertas
		{
			cout << "Ingrese la posicion que desee Eliminar: "; cin >> pos;
			objArreglo->eliminarPos(pos);
		}
		if (op == 8)
		{
			delete objArreglo, objHotel;
			cout << "Nos vemos pronto!";
			_sleep(1000);
			break;
		}
	}
}
void Mostrar_Creditos() {
	int** pCreditos;
	Iniciar_Arreglos_Creditos(pCreditos);
	Console::Clear();

	for (int i = 0; i < FILAS; i++) {
		for (int j = 0; j < COLUMNAS; j++) {
			if (pCreditos[i][j] == 1) {
				Console::ForegroundColor = ConsoleColor::Yellow;
				cout << (char)219;
			}
			else if (pCreditos[i][j] == 3) {
				Console::ForegroundColor = ConsoleColor::White;
				cout << "@";
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
				if (j == 14) cout << "x Daniella Vargas        ";
				else if (j < 27) cout << ' ';
			}
			else if (i == 25) {
				if (j == 14) cout << "x Juliana Yauricasa      ";
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
	GoBack();
}
void FuncionalidadComent() {
	arrComent* objArreglo = new arrComent();

	while (true)
	{
		int op = MenuComent();
		if (op == 1) NuevoComentario(objArreglo, cuenta);
		else if (op == 2) mostrarComentario(objArreglo);
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
			cliente->reservarHotel(c, objArreglo, cliente);
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

	while (true) {

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
					cout << "Seleccione lo que desee actualizar: ";
					cout << "\n1.Correo";

					cout << endl;
					std::cin >> n;
					switch (n) {
					case 1:
						cout << endl;
						std::cin.ignore();
						cout << "Ingrese el nuevo correo:" << endl;
						std::cin >> aux;
						cuenta->ActualizarCorr(aux, tipo);
						cout << "Listo!";
						_sleep(2000);
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
//funcionalidad reserva, hoteles
//inicio sesion dueño, inicio de sesion admin
//mostrar ofertas

//actualizar datos
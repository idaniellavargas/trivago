#pragma once
#include <string>

//DATOS GENERADOS
string minusculas = "abcdefghijklmnñopqrstuvwxyz";
string mayusculas = "ABCDEFGHIJKLMNÑOPQRSTUVWXYZ";
string numeros = "0123456789";

//====Clientes    nombre, correo, contrasena,cartera

string generarnombres() {
	string x = minusculas + mayusculas;
	string cu = "";
	for (int i = 0; i < 6; i++)
	{
		cu += x.at(rand() % x.size());
	}
	return cu;
}

string generarcorreo() {
	string x = minusculas + mayusculas;
	string cu = "";
	for (int i = 0; i < 7; i++)
	{
		cu += x.at(rand() % x.size());
	}
	string a[] = { "@gmail.com", "@hotmail.com", "@outlook.com" };
	return cu + a[rand() % 3];
}

string generarcontraseña() {
	string con = "";
	for (int i = 0, k = 0; i < 7; ++i) {
		if (k == 0) {
			con += minusculas.at(rand() % minusculas.size());
		}
		if (k == 1) {
			con += mayusculas.at(rand() % mayusculas.size());
		}
		if (k == 2) {
			con += numeros.at(rand() % numeros.size());
		}
		++k;
		if (k == 3) {
			k = 0;
		}
	}
	return con;
}

string generarcartera() {
	//return rand() % 500;
	string x = "";
	for (int i = 0; i < 4; ++i) {
		x += numeros.at(rand() % numeros.size());
	}
	return x;
}

//====Admins	  nombre   si, correo   si, contrasena   si, credencial (ID), bool permisoCatalogo	(1)

string generarcredencial() {  //si son numero, como es string pueden ser letras (falta modificar)
	//return rand() % 500;
	string x = "";
	for (int i = 0; i < 3; ++i) {
		x += numeros.at(rand() % numeros.size());
	}
	return x;
}

//====Dueños	 nombre  si, correo  si, contrasena  si, ganancias, hotel (nombre del hotel)

string generarganancias() {
	//return rand() % 500;
	string x = "";
	for (int i = 0; i < 6; ++i) {
		x += numeros.at(rand() % numeros.size());
	}
	return x;
}

//falta cambiar			  generar ID
string generarhotel() {
	string con = "";
	int cont = 0;
	for (int i = 0, k = 0; i < 10; ++i) {
		k = rand() % 10;
		//cout << "K: " << k << endl;
		if (cont > 3) {
			if (k == 0) {
				con += " ";
			}
		}
		if (k == 1 || k == 2 || k == 3 || k == 4 || k == 5 || k == 6 || k == 7 || k == 8 || k == 9) {
			con += mayusculas.at(rand() % mayusculas.size());
		}
		cont++;
	}
	//cout << "Palabra: " << con << endl;
	return con;
}

string generarIDhotel() {
	string ID = generarID(1, generarhotel(), 0);
	return ID;
}

//====Reservas		  string fecha;	ID (hotel), titular, correo, estado, moneda,  
//Hotel* hotel;
//string titular, correo, estado, moneda;
//int huespedes, habitacion;
//bool wifi, piscina, spa, parking, mascotas, desayuno, VIP;
//float monto;

//fecha
string generarfecha() {
	Date* fecha;
	int d, m, a;
	bool b;
	do{
	d = rand() % 32 + 1;
	m = rand() % 12 + 1;
	a = rand() % 5 + 2019;
	fecha = new Date(d, m, a);
	b = fecha->dateIsReal();
	if (!b) delete fecha;
	} while (!b);
	return fecha->getDate();
}

string generarestado() {
	string a[] = { "En espera", "Aceptada", "Rechazada" };
	return a[rand() % 3];
}

string generarmoneda() {
	string a[] = { "Sol", "Peso", "Dolar", "Euro" };
	return a[rand() % 4];
}

string generarhuesped() {
	return to_string(rand() % 4 + 1);
}

string generarhabitacion() {
	return to_string(rand() % 10);
}

//bool wifi, piscina, spa, parking, mascotas, desayuno,
string generarbool() {
	return to_string(rand() % 1);
}

string generarmonto() {
	string x = "";
	for (int i = 0; i < 3; ++i) {
		x += numeros.at(rand() % numeros.size());
	}
	return x;
}

//====Hoteles 
//string nombre, ID, ubicacion, moneda;
//short huespedes, habitaciones;
//long telefono;
//bool wifi, piscina, spa, parking, mascotas, desayuno;	 (si)
//float precioVIP, precio;

string generarnombrehotel() {
	string con = "";
	int cont = 0;
	for (int i = 0, k = 0; i < 10; ++i) {
		k = rand() % 10;
		//cout << "K: " << k << endl;
		if (cont > 3) {
			if (k == 0) {
				con += " ";
			}
		}
		if (k == 1 || k == 2 || k == 3 || k == 4 || k == 5 || k == 6 || k == 7 || k == 8 || k == 9) {
			con += mayusculas.at(rand() % mayusculas.size());
		}
		cont++;
	}
	return con;
}

string generarubicacion() {
	string a[] = { "Peru", "Argentina", "Espanha", "Canada", "Estados Unidos", "Mexico", "Colombia", "Italia", "Francia", "Brazil" };
	return a[rand() % 10];
}

string generartelefono() {
	string a = "";
	a += "9";
	for (int i = 0; i < 8; ++i) {
		a += numeros.at(rand() % numeros.size());
	}
	return a;
}

string generarprecio() {
	string x = "";
	for (int i = 0; i < 3; ++i) {
		x += numeros.at(rand() % numeros.size());
	}
	return x;
}

string generarpreciovip() {
	int p = stoi(generarmonto()), a;
	string x = "";
	while (true) {
		for (int i = 0; i < 3; ++i) {
			x += numeros.at(rand() % numeros.size());
		}
		a = stoi(x);
		if (p < a) {
			break;
		}
		x.clear();
	}
	return x;
}

//====Comentarios
//string ID; string Usuario; short Puntaje; string Coment;

string generarpuntaje() {
	return to_string(rand() % 5 + 1);
}

string generarcomentario() {
	string con = "";
	int cont = 0;
	string a[] = { ":)", ":(", ":/", ":D", ":p","<3",":0" };
	for (int i = 0, k = 0; i < rand() % 51 + 10; ++i) {
		k = rand() % 15;
		if (cont > 3) {
			if (k == 0 || k == 5 || k == 10) {
				con += " ";
			}
		}
		if (k == 1 || k == 2 || k == 3 || k == 4 || k == 6 || k == 8 || k == 9 || k == 11 || k == 12 || k == 13) {
			con += minusculas.at(rand() % minusculas.size());
		}
		if (cont > 15) {
			if (k == 14 || k == 7) {
				con += " " + a[rand() % 7] + " ";
			}
		}
		cont++;
	}
	return con;
}

//=====Ofertas
//string validez=fecha; string mensaje; string monto ->en Reservas

string generarmensaje() {
	string con = "";
	int cont = 0;
	string a[] = { ":)", "!", "!!", ":D", "*",";","(",")" };
	for (int i = 0, k = 0; i < rand() % 351 + 50; ++i) {
		k = rand() % 15;
		if (cont > 5) {
			if (k == 0 || k == 5 || k == 10) {
				con += " ";
			}
		}
		if (k == 1 || k == 4 || k == 6 || k == 8 || k == 9 || k == 12) {
			con += minusculas.at(rand() % minusculas.size());
		}
		if (k == 2 || k == 3 || k == 11 || k == 13) {
			con += mayusculas.at(rand() % mayusculas.size());
		}
		if (cont > 50) {
			if (k == 14 || k == 7) {
				con += a[rand() % 8] + " ";
			}
		}
		cont++;
	}
	return con;
}

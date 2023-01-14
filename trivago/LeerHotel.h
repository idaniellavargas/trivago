#include <iostream>
#include <sstream>
#include <fstream>
#define ARCHIVO_HOTELES "hoteles.csv"
using namespace std;

void create()
{
    // puntero a archivo
    fstream fout;

    // abrir un archivo csv existente o crear uno nuevo
    fout.open(ARCHIVO_HOTELES, ios::out | ios::app);

    cout << "Ingresar detalles del hotel:"
        << " nombre ubicacion servicio desayuno estrellas telefono\n";
//aqui voy a programar el leer e insertar
}

int main()
{
    create();
    ifstream archivo(ARCHIVO_HOTELES);
    string linea;
    char delimitador = ',';
    // Leemos la primer línea para descartarla, pues es el encabezado
    getline(archivo, linea);
    // Leemos todas las líneas
    while (getline(archivo, linea))
    {
        //aqui sera la lectura y confirmacion de datos
    }

    archivo.close();
}
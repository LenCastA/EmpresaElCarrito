#include <iostream>
#include <string>
#include <limits>
#include <cctype>
#include <vector>
using namespace std;


void msgError(string msg)
{
    cerr << "\033[31m" << msg << "\033[0m" << endl;
}
void msgWarning(string msg)
{
    cerr << "\033[33m" << msg << "\033[0m" << endl;
}

int validarNatural(int n){
    if(cin.fail()){
        msgError("Error: Tiene que colocar un valor correcto.");
        cin.clear();  
        cin.ignore(1024, '\n');
        return -1;
    } else if (cin.peek() != '\n') {
        msgError("Error: Caracter no numerico encontrado despues del primer entero.");
        cin.ignore(1024, '\n');
        return -1;
	} else if (n < 0){
        msgError("Error: El numero no puede ser negativo.");
        return -1;
    } else {
        return n;
    }
}

// Funcion para validar que la entrada sea un string alfabetico
string validarString(string entrada) {
    if (entrada.length() > 2) { // Verifica si la entrada esta vacia
        for (char c : entrada) {
            if (!isalpha(c) && !isspace(c) && c != '.') {
                msgError("Error: La entrada no debe tener caracteres no validos.");
                return ""; // Retorna un string vacio como indicador de error
            }
        }
        return entrada;
    } else {
        msgError("Error: La entrada debe contener al menos 3 caracteres.");
        return "";
    }
}

void printInventario(int inventario[])
{
    for (int i = 1; i < 6; i++) {
        std::cout << inventario[i] << " ";
    }
}

int obtenerTipoDePieza()
{
    int tipoDePieza;
    do {
        std::cout << "Ingrese el tipo de pieza (1-5): "; std::cin >> tipoDePieza;
        tipoDePieza = validarNatural(tipoDePieza); //validamos que tipoDePieza sea un numero entero

        if (tipoDePieza > 5) { //validamos que tipoDePieza sea una de las 5 opciones posibles
            msgError("Tipo de pieza invalido");
            tipoDePieza = -1;
        }
    } while(tipoDePieza == -1);
    return tipoDePieza;
}

int obtenerCantidadDePiezas()
{
    int cantidadDePiezas;
    do{
        std::cout << "Ingrese la cantidad de piezas del pedido: "; std::cin >> cantidadDePiezas;
        cantidadDePiezas = validarNatural(cantidadDePiezas); //validamos que cantidadDePiezas sea un numero entero
    } while (cantidadDePiezas == -1);
    return cantidadDePiezas;
}

string obtenerTipoDeProvedor()
{
    string tipoDeProveedor;
    do{
        std::cout << "Ingrese el tipo de proveedor (A, B o C): "; std::cin >> tipoDeProveedor;
        if (tipoDeProveedor == "0"){
            return "-2";
        } else {
            if (tipoDeProveedor.length() > 1){
                msgError("Ingrese un solo caracter");
                tipoDeProveedor = "";
                continue;
            }

            tipoDeProveedor = toupper(tipoDeProveedor[0]);

            if (tipoDeProveedor != "A" && tipoDeProveedor != "B" && tipoDeProveedor != "C"){
                msgError("Tipo de proveedor invalido");
                tipoDeProveedor = "";
            }
        }

    } while(tipoDeProveedor == "");

    return tipoDeProveedor;
}

int reposicionDeInventario(int minPiezas, int maxPiezas)
{
    std::cout << "-----------------------------------" << endl;
    std::cout << "\tRecepcion de pedidos" << endl;
    std::cout << "-----------------------------------" << endl;

    int cantidadDePiezas; //incializando cantidad de piezas del pedido
    do
    {
        cantidadDePiezas = obtenerCantidadDePiezas();

        if (cantidadDePiezas < minPiezas || cantidadDePiezas > maxPiezas){
            msgError("El pedido debe estar comprendido entre 50 y 100 piezas.");
        }
    } while (cantidadDePiezas < minPiezas || cantidadDePiezas > maxPiezas);

    int tipoDePieza = obtenerTipoDePieza();

    string tipoDeProveedor = obtenerTipoDeProvedor();

    std::cout << "-----------------------------------" << endl;
    std::cout << "\tReporte" << endl;
    std::cout << "Tipo de pieza: " << tipoDePieza << endl;
    std::cout << "Tipo de proveedor: " << tipoDeProveedor << endl;
    std::cout << "Cantidad del pedido recibido: " << cantidadDePiezas << endl;
    std::cout << "-----------------------------------" << endl;
}

int atencionDePedidos(int inventario[])
{
    std::cout << "-----------------------------------" << endl;
    std::cout << "\tAtencion de pedidos" << endl;

    int tipoDePieza = obtenerTipoDePieza();


    if (inventario[tipoDePieza] == 0) {
        msgError("No hay piezas en el inventario");
        return 0;
    }

    int cantidadDePiezas;
    string opcion;

    do {
        cantidadDePiezas = obtenerCantidadDePiezas();
            if (inventario[tipoDePieza] < cantidadDePiezas) {
                msgError("No hay suficientes piezas en el inventario");
                std::cout << "Cantidad de piezas en el inventario: " << inventario[tipoDePieza] << endl;
                do {
                    cout << "Desea continuar con el pedido? (s/n): "; std::cin >> opcion;
                    if (opcion != "s" && opcion != "n" && opcion.length() > 1){
                        msgError("Opcion invalida");
                        continue;
                    } else {
                        opcion = tolower(opcion[0]);
                        if (opcion == "n") {
                            return 0;
                        } else if (opcion == "s") {
                            break;
                        }
                    }
                } while(opcion != "s" && opcion != "n");
            }
    } while(inventario[tipoDePieza] < cantidadDePiezas);

    inventario[tipoDePieza] -= cantidadDePiezas;

    std::cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string nombreDelTaller;
    do {
        std::cout << "Ingrese el nombre del taller: ";
        getline(std::cin, nombreDelTaller);
        nombreDelTaller = validarString(nombreDelTaller);
    } while(nombreDelTaller == "");


    std::cout << "-----------------------------------" << endl;
    std::cout << "\tReporte" << endl;
    std::cout << "Nombre del taller: " << nombreDelTaller << endl;
    std::cout << "Tipo de pieza: " << tipoDePieza << endl;
    std::cout << "Cantidad de pedido: " << cantidadDePiezas << endl;
    std::cout << "-----------------------------------" << endl;

    return 0;
}

int reporte(int inventario[])
{
    std::cout << "-----------------------------------" << endl;
    std::cout << "\tInventario" << endl;
    std::cout << "Piezas: "; printInventario(inventario); std::cout << endl;
    std::cout << "-----------------------------------" << endl;
}

int aviso(int inventario[])
{
    std::cout << "-----------------------------------" << endl;
    std::cout << "\tAviso" << endl;
    for (int i = 0; i < 5; i++) {
        if (inventario[i] == 0) {
            std::cout << "Es necesario reponer la pieza "<< i << endl;
        }
    }
    std::cout << "-----------------------------------" << endl;
}


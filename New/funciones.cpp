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
    for (int i = 0; i < 5; i++) {
        std::cout << "Tipo "<< i + 1 << "-" << inventario[i] << " || ";
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

    tipoDePieza--; //ajustamos el valor de tipoDePieza para que sea un indice valido
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

int obtenerTipoDeProvedor()
{
    int tipoDeProveedor;
    do {
        std::cout << "Ingrese el tipo de proveedor (1-3): "; std::cin >> tipoDeProveedor;
        tipoDeProveedor = validarNatural(tipoDeProveedor);

        if (tipoDeProveedor > 3) { 
            msgError("Tipo de proveedor invalido");
            tipoDeProveedor = -1;
        }
    } while(tipoDeProveedor == -1);

    return tipoDeProveedor;
}

int registrarVentas(int inventario[], int preciosPiezasVenta[], int tipoPieza, int cantidadDePiezas, int& totalGanado)
{
    int ventaTotal = preciosPiezasVenta[tipoPieza] * cantidadDePiezas;
    inventario[tipoPieza] -= cantidadDePiezas; // Disminuir el inventario
    totalGanado += ventaTotal; // Actualizar el total ganado

    std::cout << "Venta realizada. Total ganado en esta venta: S/ " << ventaTotal << std::endl;
    return ventaTotal;
}

int registrarReposicion(int cantidadDePiezas, int preciosPiezasCompra[], int tipoPieza, int& totalPerdido)
{
    int perdidaTotal = preciosPiezasCompra[tipoPieza] * cantidadDePiezas;
    totalPerdido += perdidaTotal; // Actualizar el total perdido

    std::cout << "Total de dinero en la compra: S/ " << perdidaTotal << std::endl;
    return perdidaTotal;
}

void reporteFinal(int totalGanado, int totalPerdido) {
    std::cout << "-----------------------------------" << std::endl;
    std::cout << "\tReporte de Ventas" << std::endl;
    std::cout << "Total ganado: S/ " << totalGanado - totalPerdido << std::endl;
    std::cout << "-----------------------------------" << std::endl;
}

int reposicionDeInventario(int inventario[], int minPiezas, int maxPiezas, int preciosPiezasCompra[], int& totalPerdido)
{
    std::cout << "-----------------------------------" << endl;
    std::cout << "\tRecepcion de pedidos" << endl;
    std::cout << "-----------------------------------" << endl;

    int cantidadDePiezas;
    do
    {
        cantidadDePiezas = obtenerCantidadDePiezas();

        if (cantidadDePiezas < minPiezas || cantidadDePiezas > maxPiezas){
            msgError("El pedido debe estar comprendido entre 50 y 100 piezas.");
        }
    } while (cantidadDePiezas < minPiezas || cantidadDePiezas > maxPiezas);

    int tipoDePieza = obtenerTipoDePieza();

    int tipoDeProveedor = obtenerTipoDeProvedor();

    inventario[tipoDePieza] += cantidadDePiezas;

    int monto = registrarReposicion(cantidadDePiezas, preciosPiezasCompra, tipoDePieza, totalPerdido);

    std::cout << "-----------------------------------" << endl;
    std::cout << "\tReporte" << endl;
    std::cout << "Tipo de pieza: " << tipoDePieza + 1 << endl;
    std::cout << "Tipo de proveedor: " << tipoDeProveedor << endl;
    std::cout << "Cantidad del pedido recibido: " << cantidadDePiezas << endl;
    std::cout << "Monto pagado: S/ " << monto << endl;
    std::cout << "-----------------------------------" << endl;
}

int atencionDePedidos(int inventario[], int preciosPiezasVenta[], int& totalGanado)
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

    int monto =registrarVentas(inventario, preciosPiezasVenta, tipoDePieza, cantidadDePiezas, totalGanado);

    std::cout << "-----------------------------------" << endl;
    std::cout << "\tReporte" << endl;
    std::cout << "Nombre del taller: " << nombreDelTaller << endl;
    std::cout << "Tipo de pieza: " << tipoDePieza + 1<< endl;
    std::cout << "Cantidad de pedido: " << cantidadDePiezas << endl;
    std::cout << "Monto recibido por la venta: S/ " << monto << endl;
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
    std::cout << "\033[1;33m-----------------------------------" << std::endl;
    std::cout << "\tAviso" << std::endl;
    for (int i = 0; i < 5; i++) {
        if (inventario[i] < 8) {
            std::cout << "Es necesario reponer la pieza " << i+1 << std::endl;
        }
    }
    std::cout << "-----------------------------------\033[0m" << std::endl;
}


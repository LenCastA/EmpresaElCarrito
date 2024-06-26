#include <iostream>
#include "funciones.cpp"
using namespace std;

int main()
{
    int opcion = 0; //inicializando opcion del menu
    int num_opciones = 5; //declara numero de opciones del menu
    int minPiezasPedido = 50, maxPiezasPedido = 100;
    int inventario[5] = {100, 7, 98, 256, 4}; //inicializando inventario
    int PRECIOS_PIEZAS_COMPRA [5] = {5, 10, 15, 20, 25}; // Precios de cada tipo de pieza
    int PRECIOS_PIEZAS_VENTA[5] = {10, 20, 30, 40, 50}; // Precios de cada tipo de pieza
    int totalGanado = 0; // Variable global para llevar el total ganado
    int totalPerdido = 0; // Variable global para llevar el total de pedidos
    
    cout << "-----------------------------------" << endl;
    cout << "Bienvenido a la empresa El Carrito" << endl;
    cout << "-----------------------------------" << endl;
    while (opcion != num_opciones) { //opcion final termina el programa
        //Imprimiendo menu
        cout << "\tMenu" << endl;
        cout << "1. Reposicion de inventario" << endl;
        cout << "2. Atencion de pedidos" << endl;
        cout << "3. Consultar inventario" << endl;
        cout << "4. Reporte de ganancias" << endl;
        cout << "5. Salir" << endl;    
        cout << "-----------------" << endl;
        aviso(inventario); //avisar sobre faltas en el inventario

        do {
            cout << "Ingrese una opcion: "; cin >> opcion;
            opcion = validarNatural(opcion); //validando que opcion sea entero positivo
            if (opcion > num_opciones) {
                opcion = -1; // -1 utilizamos como codigo de error de datos
                msgError("Opcion invalida");
            }
        } while (opcion == -1); // se repite hasta que el codigo de error no exista

        switch (opcion){
            case 1:
                reposicionDeInventario(inventario, minPiezasPedido, maxPiezasPedido, PRECIOS_PIEZAS_COMPRA, totalPerdido);
                reporte(inventario);
                break;
            case 2:
                atencionDePedidos(inventario, PRECIOS_PIEZAS_VENTA, totalGanado);
                reporte(inventario);
                break;
            case 3:
                reporte(inventario);
                break;
            case 4:
                reporteFinal(totalGanado, totalPerdido);
                break;
            case 5:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                break;
        }
    }
    return 0;
}
#include <iostream>
#include "funciones.cpp"
using namespace std;

int main()
{
    int opcion = 0; //inicializando opcion del menu
    int num_opciones = 5; //declara numero de opciones del menu
    int minPiezasPedido = 50, maxPiezasPedido = 100;
    int inventario[5] = {0, 0, 0, 0, 0}; //inicializando inventario
    
    cout << "-----------------------------------" << endl;
    cout << "Bienvenido a la empresa El Carrito" << endl;
    cout << "-----------------------------------" << endl;
    while (opcion != num_opciones) { //opcion final termina el programa
        //Imprimiendo menu
        cout << "\tMenu" << endl;
        cout << "1. Reposicion de inventario" << endl;
        cout << "2. Atencion de pedidos" << endl;
        cout << "3. Consultar inventario" << endl;
        cout << "4. Talleres vendidos" << endl;
        cout << "5. Salir" << endl;    
        cout << "-----------------" << endl;
        cout << "\033[34m" << "Presione 0 en cualquier caso para volver al menu principal" << "\033[0m" << endl;
        cout << "-----------------" << endl;
        aviso(inventario); //avisar sobre faltas en el inventario
        cout << "-----------------" << endl;

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
                reposicionDeInventario(inventario, minPiezasPedido, maxPiezasPedido);
                reporte(inventario);
                break;
            case 2:
                atencionDePedidos(inventario);
                reporte(inventario);
                break;
            case 3:
                reporte(inventario);
                break;
            default:
                break;
        }
    }
    return 0;
}
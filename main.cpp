#include "funcionesMenu.cpp"

int main()
{
    int cod_volver; //inicializando una variable para retroceder al menu
    int opcion = 0; //inicializando opcion del menu
    int num_opciones = 5; //declara numero de opciones del menu
    int minPiezasPedido = 50, maxPiezasPedido = 100;

    //variables persistentes (talleres, proveedores, inventario)
    map<int, int> inventario;
    map<string, int> proveedores;
    vector<string> talleres;
    
    //asignando valores a las variables persistentes
    leerDatosMap(inventario, "inventario.txt");
    leerDatosMap(proveedores, "proveedores.txt");
    leerDatosArray(talleres, "talleres.txt");

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
                cod_volver = reposicionDeInventario(inventario, proveedores);
                if (cod_volver == -2) { //si la funcion devuelve -2 se regresa al menu inicial
                    break;
                }
                reporte(inventario, proveedores);
                break;
            case 2:
                cod_volver = atencionDePedidos(inventario, proveedores, talleres);
                if (cod_volver == -2) {
                    break;
                }
                reporte(inventario, proveedores);
                break;
            case 3:
                reporte(inventario, proveedores);
                break;
            case 4:
                talleresVendidos(talleres);
                break;
            default:
                break;
        }
    }
}

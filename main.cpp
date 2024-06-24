#include "funcionesMenu.cpp"

int main()
{
    int cod_volver;
    int opcion = 0;
    map<int, int> map1;
    map<string, int> map2;
    vector<string> talleres;

    leerDatosMap(map1, "inventario.txt");
    leerDatosMap(map2, "proveedores.txt");
    leerDatosArray(talleres, "talleres.txt");

    while (opcion != 5) {
        aviso(map1);

        cout << "\tMenu" << endl;
        cout << "1. Recepcion de pedidos" << endl;
        cout << "2. Atencion de pedidos" << endl;
        cout << "3. Consultar inventario" << endl;
        cout << "4. Talleres vendidos" << endl;
        cout << "5. Salir" << endl;
        cout << "-----------------" << endl;
        cout << "\033[34m" << "Presione 0 en cualquier caso para volver al menu principal" << "\033[0m" << endl;
        cout << "-----------------" << endl;

        do {
            cout << "Ingrese una opcion: "; cin >> opcion;
            opcion = validarNatural(opcion);
            if (opcion > 5) {
                opcion = -1;
                msgError("Opcion invalida");
            }
        } while (opcion == -1);

        switch (opcion){
            case 1:
                cod_volver = recepcionDePedidos(map1, map2);
                if (cod_volver == -2) {
                    break;
                }
                reporte(map1, map2);
                break;
            case 2:
                cod_volver = atencionDePedidos(map1, map2, talleres);
                if (cod_volver == -2) {
                    break;
                }
                reporte(map1, map2);
                break;
            case 3:
                reporte(map1, map2);
                break;
            case 4:
                talleresVendidos(talleres);
                break;
            default:
                break;
        }
// Nota: La opción 5 cortará el bucle automáticamente según la lógica del bucle while que lo contiene.
    }
}
